/*

  Defines the BaselineFinder class module.
  Finds the baseline on some user defined region, computes
  a baseline-subtracted and inverted waveform.
  
  v0.1 YMeng

 */

#ifndef BaselineFinder_hh
#define BaselineFinder_hh

#include "EventData.hh"
#include "CfgReader.hh"
#include <string>

class BaselineFinder
{
public:
  BaselineFinder(CfgReader const& cfg);
  int Process(EventData* event);

  std::string module_name;


  // Produces baseline vector using a fixed search region.
  void fixed_baseline(EventData* event);

  void moving_baseline(EventData* event);

private:
  bool   _enabled;
  std::string _mode;
  std::string adc_saturation_count;
    
  // fixed baseline parameters
  double _start_time;
  double _end_time;
  double _threshold;


  // moving baseline parameters
  int _pre_samps;
  int _post_samps;
  double _max_sigma;
  double _max_amplitude;


  void interpolate_baseline(vector<double> & baseline, int start, int end);

};


#endif
