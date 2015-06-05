/*

  Create the sum channel.

  v0.1 AFan 2014-02-03

  NOTE: currently just blind sum; will need to:
  - account for channel-to-channel SPE means
  - account for channel-to-channel timing alignment

 */


#ifndef SumChannel_hh
#define SumChannel_hh

#include "EventData.hh"
#include "CfgReader.hh"

#include <string>

class SumChannel
{
public:
  SumChannel(CfgReader const& cfg);
  // void Initialize(); //Add an Initialize function only if necessary
  int Process(EventData* event);

  std::string module_name;

private:
  bool _enabled;

};

#endif
