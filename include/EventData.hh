/*

  define EventData class.
  contains all processed information for each event
  

  v0.1 AFan 2013-05-01
  
 */

#ifndef EventData_hh
#define EventData_hh

#include "Rtypes.h" // has the ClassDef macros
#include <vector>
#include <map>

using namespace std;

#define BOT_CHANNEL_ID 0

class TMultiGraph;

class EventData
{

public:
  EventData() {Clear();}
  
  void Clear() {
    run_id = -1;
    event_id = -1;
    nchans = -1;
    nsamps = -1;
    us_per_samp = -1.0;
    trigger_index = -1;
    adc_bits = -1;
    
    channel_nums.clear();
    channel_ids.clear();
    adc_gains.clear();
    adc_offsets.clear();
    adc_ranges.clear();
    spe_means.clear();
    raw_waveforms.clear();
    baseline_means.clear();
    baseline_sigmas.clear();
    baseline_validities.clear();
    baseline_subtracted_waveforms.clear();
    integrals.clear();
    zero_suppressed_waveforms.clear();
    sum_waveform.clear();
    sum_integral.clear();
    npulses = 0;
    pulse_start_times.clear();
    pulse_end_times.clear();
    pulse_peak_times.clear();
    pulse_peak_amps.clear();
    pulse_integrals.clear();
      
      //------------------
      saturated.clear();
      ch_pulse_integrals.clear();
      ch_pulse_peak_amps.clear();
      ch_5samp_extended_pulse_integrals.clear();
      ch_10samp_extended_pulse_integrals.clear();
      //------------------

  }

  // all the data for a single event  
  int run_id;
  int event_id;
  int nchans;
  int nsamps;
  double us_per_samp;
  int trigger_index;
  int trigger_index_offset; //for top-channels only
  int adc_bits; //number of ADC bits


  vector<int> channel_nums; // DAQ channel number. check that this is same in every event
  vector<int> channel_ids; // global channel ID to be used by all modules
  vector<double> adc_gains; // volts per ADC-count
  vector<double> adc_offsets;
  vector<double> adc_ranges;
  vector<double> spe_means;
  vector< vector<double> > raw_waveforms;
  vector<double> baseline_means;
  vector<double> baseline_sigmas;
  vector<bool> baseline_validities;
  vector< vector<double> > baseline_subtracted_waveforms; // unit: ADC counts
  vector< vector<double> > integrals;
  vector< vector<double> > zero_suppressed_waveforms;

  vector<double> sum_waveform;
  vector<double> sum_integral;
  int npulses;
  vector<double> pulse_start_times;
  vector<double> pulse_end_times;
  vector<double> pulse_peak_times;
  vector<double> pulse_peak_amps;
  vector<double> pulse_integrals;
  //vector<double> pulse_fixed_int1;
  //vector<double> pulse_fixed_int2;

  //vector< vector<double> > ch_pulse_peak_times;
  //vector< vector<double> > ch_pulse_peak_amps;
  //vector< vector<double> > ch_pulse_integrals;
  //vector< vector<double> > ch_pulse_fixed_int1;
  //vector< vector<double> > ch_pulse_fixed_int2;

  //------------------
    
    vector<bool> saturated;
    
    vector< vector<double> > ch_pulse_integrals;
    vector< vector<double> > ch_pulse_peak_amps;
    vector< vector<double> > ch_5samp_extended_pulse_integrals;
    vector< vector<double> > ch_10samp_extended_pulse_integrals;
    
  //------------------

    
    
  double SampleToTime(int samp) const;
  int TimeToSample(double time, bool checkrange=true) const;

  TMultiGraph* GetTMultiGraph(int ch);
  TMultiGraph* GetTMultiGraph_sumch();

private:

  
  ClassDef(EventData, 1)
};


#endif

