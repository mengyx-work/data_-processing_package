#include "PulseFinder.hh"
#include <algorithm> //min
#include <numeric>   //accumulate
#include <cmath>

PulseFinder::PulseFinder(CfgReader const& cfg):
  module_name("PulseFinder"),
  _enabled(cfg.getParam<bool>(module_name, "enabled", true)),
  _mode(cfg.getParam<std::string>(module_name, "mode", "THRESHOLD")),
  _down_sample_factor(cfg.getParam<int>(module_name, "down_sample_factor", 10)),
  _pulse_start_threshold(cfg.getParam<double>(module_name, "pulse_start_threshold", 0)),
  _pulse_start_amp(cfg.getParam<double>(module_name, "pulse_start_amp", 0)),
  _pulse_end_threshold(cfg.getParam<double>(module_name, "pulse_end_threshold", 0))
{ }

int PulseFinder::Process(EventData* event)
{
  if (!_enabled)
    return 0;

  int npulses = 0;
  if (_mode=="THRESHOLD")
    npulses = ThresholdSearch(event);
  else if (_mode=="INTEGRAL")
    npulses = IntegralSearch(event);
  else {
    std::cout << "PulseFinder mode not recognized. Using THRESHOLD."<<std::endl;
    npulses = ThresholdSearch(event);
  }

  if (npulses>0)
    EvaluatePulses(event);

  return 1;

}


void PulseFinder::EvaluatePulses(EventData* event)
{
  vector<double> const& waveform = event->sum_waveform;
  
  for (int i=0; i<event->npulses; i++) {
    int start_index = event->TimeToSample(event->pulse_start_times[i]);
    int end_index = event->TimeToSample(event->pulse_end_times[i]);
    int peak_index = std::min_element(waveform.begin() + start_index, waveform.begin() + end_index)-waveform.begin();
    event->pulse_peak_times.push_back(event->SampleToTime(peak_index));
    event->pulse_peak_amps.push_back(waveform[peak_index]);
    event->pulse_integrals.push_back(event->sum_integral[start_index-1] - event->sum_integral[end_index-1]);
  }
    
    vector<double> Pulse_5samp_Extended_Integral;
    vector<double> Pulse_10samp_Extended_Integral;
    vector<double> Pulse_Integral;
    
    for(unsigned int ch=0; ch<event->baseline_subtracted_waveforms.size();ch++){
     
        Pulse_Integral.clear();
        Pulse_5samp_Extended_Integral.clear();
        Pulse_10samp_Extended_Integral.clear();
        
    vector<double> SingleIntegral = event->integrals[ch];
        int start_point, end_point;
        
        for (int i=0; i<event->npulses; i++) {
            unsigned int start_index = event->TimeToSample(event->pulse_start_times[i]);
            unsigned int   end_index = event->TimeToSample(event->pulse_end_times[i]);
            

            /*
             The integral from each channel is the integration of zero-supressed waveform.
             
            the pulse area calculated on individual channels is converted into #PE. 
             */
            
                        
            //double Pulse_Area = SingleIntegral[start_index-1] - SingleIntegral[end_index-1]; //--- the ADC counts from zero-supressed wavform ---
            double Pulse_Area = (SingleIntegral[start_index-1] - SingleIntegral[end_index-1])*event->adc_gains[ch]*1000*2/event->spe_means[ch]; //--- #PE ----

            Pulse_Integral.push_back(Pulse_Area);
            //std::cout<<"Channel#: "<<ch<<", Pulse#: "<<i<<", Area: "<<Pulse_Area<<std::endl;

            
            if((start_index-5)>1)
                start_point = start_index-5;
            else
                start_point = 1;
            if(end_index+5<=(SingleIntegral.size()-1))
                end_point = end_index+5;
            else
                end_point = SingleIntegral.size()-1;
            
            //double Pulse_5samp_Extended_Area = -std::accumulate(SingleWaveform.begin()+start_point, SingleWaveform.begin()+end_point, 0.0);
            //double Pulse_5samp_Extended_Area = SingleIntegral[start_point-1] - SingleIntegral[end_point-1]; //--- the ADC counts from zero-supressed wavform ---
            double Pulse_5samp_Extended_Area = (SingleIntegral[start_point-1] - SingleIntegral[end_point-1])*event->adc_gains[ch]*1000*2/event->spe_means[ch];

            Pulse_5samp_Extended_Integral.push_back(Pulse_5samp_Extended_Area);
            
            
            
            if((start_index-10)>1)
                start_point = start_index-10;
            else
                start_point = 1;
            if(end_index+10<=(SingleIntegral.size()-1))
                end_point = end_index+10;
                else
                end_point = SingleIntegral.size()-1;
            
            //double Pulse_10samp_Extended_Area = -std::accumulate(SingleWaveform.begin()+start_point, SingleWaveform.begin()+end_point, 0.0);
            //double Pulse_10samp_Extended_Area = SingleIntegral[start_point-1] - SingleIntegral[end_point-1]; //--- the ADC counts from zero-supressed wavform ---
            double Pulse_10samp_Extended_Area = (SingleIntegral[start_point-1] - SingleIntegral[end_point-1])*event->adc_gains[ch]*1000*2/event->spe_means[ch];
            Pulse_10samp_Extended_Integral.push_back(Pulse_10samp_Extended_Area);
        }
        
    event->ch_pulse_integrals.push_back(Pulse_Integral);
    event->ch_5samp_extended_pulse_integrals.push_back(Pulse_5samp_Extended_Integral);
    event->ch_10samp_extended_pulse_integrals.push_back(Pulse_10samp_Extended_Integral);

    }
    
   
}

int PulseFinder::ThresholdSearch(EventData* event)
{
  vector<double> const& waveform = event->sum_waveform;

  bool in_pulse = false;
  for (size_t i=1; i<waveform.size(); i++) {
    if (!in_pulse) {
      if (waveform[i] < _pulse_start_threshold) {
        in_pulse = true;
        event->pulse_start_times.push_back(event->SampleToTime(i));
      }
    }
    else { //in_pulse
      if (waveform[i] > _pulse_start_threshold) {
        in_pulse = false;
        event->pulse_end_times.push_back(event->SampleToTime(i));
      }
    }
  }
  event->npulses = std::min(event->pulse_start_times.size(), event->pulse_end_times.size());
  return event->npulses;
}

int PulseFinder::IntegralSearch(EventData* event)
{

  vector<double> const& waveform = event->sum_waveform;
  vector<double> const& integral = event->sum_integral;

  // create down-sampled integral waveform
  int ds_wfm_nsamps = (int) event->nsamps / _down_sample_factor;

  std::vector<double> ds_integral(ds_wfm_nsamps);
  bool in_pulse = false;
    
  for (int i=0; i<ds_wfm_nsamps; i++) {
    ds_integral[i] = integral[i*_down_sample_factor];
    
    // If two consecuative pulses in the down-sampled integral are vertically separated by
    // more than _pulse_start_threshold, then there's a pulse somewhere nearby
      
    if ( i>2 && !in_pulse && (ds_integral[i]-ds_integral[i-1] < _pulse_start_threshold) ) {
      in_pulse = true;
      //now do fine-grained search for pulse start point
      for (int ii=(i-2)*_down_sample_factor; ii<i*_down_sample_factor; ii++) {
        if (waveform[ii] < _pulse_start_amp) {
          event->pulse_start_times.push_back(event->SampleToTime(ii-1));
          break;
        }
      }//end fine-grained search
    }
    else if (in_pulse && (std::fabs(ds_integral[i]-ds_integral[i-1]) < std::fabs(_pulse_end_threshold)) ) {
      in_pulse = false;
      event->pulse_end_times.push_back(event->SampleToTime(i*_down_sample_factor));
    }

    if(in_pulse &&(i==ds_wfm_nsamps-1)){
        in_pulse = false;
        event->pulse_end_times.push_back(i*_down_sample_factor);
    }

  }// end loop over down-sampled integral

  event->npulses = event->pulse_start_times.size();
    
  if(event->pulse_start_times.size()!=event->pulse_end_times.size())
    std::cout<<"the size of pulse_start_times is not equal to pulse_end_times!"<<std::endl;

  return event->npulses;
        
}
