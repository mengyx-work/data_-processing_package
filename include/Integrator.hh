/*

  Defines the Integral class module.
  Integrates a waveform, scaling the integral by spe_mean

  v0.1 AFan 2013-08-17

 */

#ifndef Integrator_hh
#define Integrator_hh

#include "EventData.hh"
#include "CfgReader.hh"
#include <string>
#include <vector>

class Integrator
{
public:
  Integrator(CfgReader const& cfg);
  //void Initialize(); //Add an Initialize function only if necessary.
  int Process(EventData* event);

  std::string module_name;

private:
  bool _enabled;

  void integrate(std::vector<double> const& wfm, std::vector<double> & result);
};

#endif
