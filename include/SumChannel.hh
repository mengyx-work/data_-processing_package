/*

  Create the sum channel.

  NOTE: currently just blind sum; will need to:
  - account for channel-to-channel SPE means
  - account for channel-to-channel timing alignment
	
	YMENG 05-23-2014
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
