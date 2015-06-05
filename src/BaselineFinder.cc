#include "BaselineFinder.hh"
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>

#define BASELINE_INIT -999

using namespace std;


BaselineFinder::BaselineFinder(CfgReader const& cfg):
  module_name("BaselineFinder"),
  _enabled(cfg.getParam<bool>(module_name, "enabled", true)),
  _mode(cfg.getParam<string>(module_name, "mode", "FIXED")),
  _start_time(cfg.getParam<double>(module_name, "start_time", -0.1)),
  _end_time(cfg.getParam<double>(module_name, "end_time", 0.0)),
  _threshold(cfg.getParam<double>(module_name, "threshold", 1.0)),
  _pre_samps(cfg.getParam<int>(module_name, "pre_samps", 10)),
  _post_samps(cfg.getParam<int>(module_name, "post_samps", 10)),
  _max_sigma(cfg.getParam<double>(module_name, "max_sigma", 1)),
  _max_amplitude(cfg.getParam<double>(module_name, "max_amplitude", 1))
{ }


int BaselineFinder::Process(EventData* event)
{
  if (!_enabled)
    return 0;

  event->baseline_subtracted_waveforms.resize(event->nchans);
  
  if (_mode == "FIXED")
    fixed_baseline(event);
  else if (_mode == "MOVING")
    moving_baseline(event);
  else {
    std::cout << "BaselineFinder mode not recognized. Using FIXED."<<std::endl;
    fixed_baseline(event);
  }

  
  return 1;
}



void BaselineFinder::fixed_baseline(EventData* event)
{
  // Loop over channels
  for (int idx = 0; idx<event->nchans; ++idx) {
    vector<double> const& raw = event->raw_waveforms[idx];
    double sum = 0;
    double var = 0;
    int start_samp = event->TimeToSample(_start_time);
    int end_samp = event->TimeToSample(_end_time);
    for (int i = start_samp; i<end_samp; ++i) {
      sum += raw[i];
      var += raw[i]*raw[i];
    }
      
      // parameters used for saturation search
      int saturating_count = -128;
      bool ch_saturated = false;
      
    double mean = sum/(end_samp-start_samp);
    event->baseline_means.push_back(mean);
    event->baseline_sigmas.push_back( sqrt(var/(end_samp - start_samp) - mean*mean) );
    
    vector<double> & bs_wfm = event->baseline_subtracted_waveforms[idx];
    bs_wfm.resize(raw.size());
    
      if (event->baseline_sigmas[idx] < _threshold) {        
      event->baseline_validities.push_back(true);


      // compute the baseline-subtracted and inverted waveform
        for (size_t i=0; i<raw.size(); ++i){
            bs_wfm[i] = raw[i] - mean;
        
            if(raw[i]==saturating_count){
                ch_saturated = true;
	//	std::cout<<"found saturation!"<<std::endl;
	    }
        }

     event->saturated.push_back(ch_saturated);

    }
    else
      event->baseline_validities.push_back(false);
  } // end loop over channels
}

void BaselineFinder::interpolate_baseline(vector<double> & baseline, int start, int end)
{
  double m = (baseline[end] - baseline[start])/(end-start);
  double b = baseline[start] - m*start;
  for (int samp = start+1; samp<end; samp++)
    baseline[samp] = m*samp+b;
}


void BaselineFinder::moving_baseline(EventData* event)
{
  // Loop over channels
    
    const int saturating_count = -128;
         bool ch_saturated = false;

  for (size_t idx=0; idx<event->raw_waveforms.size(); idx++) {

    vector<double> const& raw = event->raw_waveforms[idx];
    int const nsamps = event->nsamps;
    vector<double> baseline(nsamps, BASELINE_INIT);
    bool in_baseline = false;
    int baseline_start = -1; // start point of baseline. fill in waveform start to baseline_start after main loop.
    double mean = 0;
    double variance = 0;
    bool baseline_valid = false;
    int window_size = _pre_samps+_post_samps+1;
    double last_baseline_samp = 0;

      if(raw[idx]==saturating_count)
          ch_saturated = true;

    // start the mean off with the very beginning of the waveform

    for (int i=0; i<_pre_samps+_post_samps+1; i++) {
      mean += raw[i]/window_size;
      variance += raw[i]*raw[i]/window_size;
    }

    // now traverse through the waveform
    for (int samp = _pre_samps; samp<nsamps-_post_samps-1; samp++) {
      if (!in_baseline) { // previously not in baseline

        // determine if now in baseline
        if (variance < _max_sigma*_max_sigma) {
          //now in baseline
          in_baseline = true;
          if (!baseline_valid)
            baseline_valid = true;
          if (baseline_start == -1)
            baseline_start = samp;
          baseline[samp] = mean;
          last_baseline_samp = samp;
        }
      }
    
      else { // previously in baseline

        // determine if still in baseline
        if (std::abs(raw[samp+_post_samps]-baseline[samp-1]) > _max_amplitude) {
          //no longer in baseline
          in_baseline = false;
        }

        else {
          //still in baseline
          baseline[samp] = mean;
          last_baseline_samp = samp;
        }
        
      }

      mean = mean + (raw[samp+_post_samps] - raw[samp-_pre_samps])/window_size;
      variance = variance + (raw[samp+_post_samps]*raw[samp+_post_samps] -
                             raw[samp-_pre_samps]*raw[samp-_pre_samps])/window_size;
    }// end loop over waveform


    // fill in the beginning of the baseline
    for (int samp=0; samp<baseline_start; samp++)
      baseline[samp] = baseline[baseline_start];

    // fill in the end of the baseline
    for (int samp=last_baseline_samp+1; samp<nsamps; samp++)
      baseline[samp] = baseline[last_baseline_samp];

    
    // subtract off the baseline
    vector<double> & bswfm = event->baseline_subtracted_waveforms[idx];
    
    for (int samp=0; samp<nsamps; samp++) {

      // interpolate the regions that are not yet set.
      if (baseline[samp] == BASELINE_INIT) {
        bool interpolate = true;
        int start = samp-1;
        int end = samp;
        while (interpolate) {
          ++end;
          if (end >= nsamps) {
            std::cout << "AHHH interpolating the end!"<<std::endl;
            break;
          }
          if (baseline[end] != BASELINE_INIT) {
            interpolate = false;
          }
        }
        interpolate_baseline(baseline, start, end);
      }

      bswfm[samp] = raw[samp] - baseline[samp];
     
    }
    
    event->saturated.push_back(ch_saturated);
    event->baseline_means.push_back(1);
    event->baseline_sigmas.push_back(1);
    event->baseline_validities.push_back(true);
    //event->baseline_subtracted_waveforms.push_back(bswfm);

    
  }// end loop over channels
}
