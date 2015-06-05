#include "ZeroSuppressor.hh"

#include <cmath>
#include <algorithm>
#include <vector>


ZeroSuppressor::ZeroSuppressor(CfgReader const& cfg):
  module_name("ZeroSuppressor"),
  _enabled(cfg.getParam<bool>(module_name, "enabled", true)),
  _threshold(cfg.getParam<double>(module_name, "threshold", 0)),
  _edge_threshold(cfg.getParam<double>(module_name, "edge_threshold", 0))
{ }


int ZeroSuppressor::Process(EventData* event)
{
  if (!_enabled)
    return 0;

  event->zero_suppressed_waveforms.resize(event->nchans);

  // Loop over the channels
  for (int idx = 0; idx<event->nchans; ++idx) {

    vector<double> const& bs_wfm = event->baseline_subtracted_waveforms[idx];
    vector<double> & zs_wfm = event->zero_suppressed_waveforms[idx];

    // initialize the waveform to zeros
    zs_wfm.clear();
    zs_wfm.resize(bs_wfm.size());

    if (!event->baseline_validities[idx])
      continue;

    // Look for regions that are past _threshold. If in such a region,
    // (1) search back to the last sample that is within _edge_threshold, and
    // (2) search forward to the first sample that is within _edge_threshold.
    // These define endpoints for un-zero-suppressed regions; everything
    // else is zero-suppressed.
    int start_samp=0, end_samp=0;
    int samp=0;
    while (samp < event->nsamps) {
      if (std::fabs(bs_wfm[samp]) > _threshold) {


        // now search back to last sample that is within _edge_threshold
        int tmp_samp = samp;
        while ( tmp_samp >= 0 && std::fabs(bs_wfm[tmp_samp]) > _edge_threshold ) {
          --tmp_samp;
          start_samp = tmp_samp;
        }
        
        // and search forward to first sample that is within _edge_threshold
        tmp_samp = samp;
        while ( tmp_samp < event->nsamps && std::fabs(bs_wfm[tmp_samp]) > _edge_threshold ) {
          ++tmp_samp;
          end_samp = tmp_samp;
        }
        
        // now copy the non-zero-suppressed region to the waveform
        for (tmp_samp=start_samp; tmp_samp<=end_samp; tmp_samp++)
          zs_wfm[tmp_samp] = bs_wfm[tmp_samp];
        
        // continue the algorithm from the last non-zero-suppressed point
        samp = end_samp+1;
      }
      else //this sample is below threshold -- keep zs_wfm at the initialized zero
        ++samp;
      
    }// end loop over samps


  }// end loop over channels
  

  return 1;
}
