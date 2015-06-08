/*
  Defines the ProcessedPlotter class to plot rwa waveforms
  and some processed results for each channel

  borrowed mostly from genroot


 */

#ifndef ProcessedPlotter_hh
#define ProcessedPlotter_hh

#include "EventData.hh"
#include "CfgReader.hh"
#include "RootGraphix.hh"
#include <string>
#include <iostream>

// Forward declarations
class TCanvas;
class TLegend;

class ProcessedPlotter
{
public:
  ProcessedPlotter(CfgReader const& cfg);
  void Initialize(TCanvas* canvas, RootGraphix* graphix);
  int Process(EventData* event);
  void Finalize();
  
  const TCanvas* GetCanvas() { return _canvas; }

  std::string module_name;  

private:

  bool _enabled;
  int _chans_per_pad;
  RootGraphix* _graphix;
  TCanvas* _canvas;
  std::vector<TLegend*> _legends;



};


#endif
