/*

  Defines the PulseFinder class module.
  Searches through the sum channel waveform to find pulses.

 */


#ifndef PulseFinder_hh
#define PulseFinder_hh

#include "EventData.hh"
#include "CfgReader.hh"
#include <string>
#include <vector>

class PulseFinder
{
public:
  PulseFinder(CfgReader const& cfg);
  //void Initialize(); //Add an Initialize function only if necessary.
  int Process(EventData* event);

  std::string module_name;

private:
  bool _enabled;

  std::string _mode;

  int _down_sample_factor;
  double _pulse_start_threshold;
  double _pulse_start_amp;
  double _pulse_end_threshold;

  void EvaluatePulses(EventData* event);

  int ThresholdSearch(EventData* event);
  int IntegralSearch(EventData* event);
};


#endif
