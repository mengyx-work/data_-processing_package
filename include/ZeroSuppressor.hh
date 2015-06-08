/*

  Perform zero-suppression on the waveforms.
  Use simple threshold value to determine if sample is
  to be zero-suppressed.

	YMENG 04-44-2014
 */

#ifndef ZeroSuppressor_hh
#define ZeroSuppressor_hh

#include "EventData.hh"
#include "CfgReader.hh"
#include <string>


class ZeroSuppressor
{
public:
  ZeroSuppressor(CfgReader const& cfg);
  // void Initialize(); //Add an Initialize function only if necessary
  int Process(EventData* event);

  std::string module_name;

private:
  bool _enabled;

  // main threshold to decide if a portion of the waveform should
  // be zero-suppressed
  double _threshold;

  // once a portion of the waveform is determined to be zero-suppressed,
  // suppress those samples up to the first sample and past the last sample
  // that are beyond this threshold
  double _edge_threshold;

};



#endif
