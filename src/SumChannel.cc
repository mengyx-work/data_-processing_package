#include "SumChannel.hh"

#include <vector>

SumChannel::SumChannel(CfgReader const& cfg):
  module_name("SumChannel"),
  _enabled(cfg.getParam<bool>(module_name, "enabled", true))
{ }


int SumChannel::Process(EventData* event)
{
  if (!_enabled)
    return 0;

  std::vector<double> & sum = event->sum_waveform;
  std::vector<std::vector<double> > const& wfms = event->zero_suppressed_waveforms;

  
  //Loop over the channels
  for (size_t idx = 0; idx<wfms.size(); ++idx) {
    
    vector<double> const& wfm = wfms[idx];

    // size the sum channel appropriately
    if (idx == 0) {
      sum.resize(wfm.size());
    }

    if (!event->baseline_validities[idx]) {
      sum.clear();
      sum.resize(wfm.size());
      return 0;
    }

      //std::cout<<event->spe_means[idx]<<std::endl;
      
    // add waveform to sum channel
    for (size_t i=0; i<wfm.size(); ++i) {
      sum[i] += wfm[i]*event->adc_gains[idx]*1000*2/event->spe_means[idx]; // ADC gain in V, the sum channel is in unit of PE
    }
    
  }// end loop over channels

  //event->raw_waveform.push_back(sum);
  
  return 1;
}
