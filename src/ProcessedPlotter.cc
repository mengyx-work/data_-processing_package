#include "ProcessedPlotter.hh"
#include "TCanvas.h"
#include "TColor.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TList.h"

int colors[] = {kBlack, kRed, kGreen, kCyan, kBlue, kMagenta, kYellow, kGray+2,
		kOrange-3, kGreen+3, kCyan+3, kMagenta-5, kRed-2};
int ncolors = sizeof(colors)/sizeof(int);

ProcessedPlotter::ProcessedPlotter(CfgReader const& cfg):
  module_name("ProcessedPlotter"),
  _enabled(cfg.getParam<bool>(module_name, "enabled", 0)),
  _chans_per_pad(cfg.getParam<int>(module_name, "chans_per_pad", 1)),
  _graphix(0),
  _canvas(0)

{ }

void ProcessedPlotter::Initialize(TCanvas* canvas, RootGraphix* graphix)
{
  _canvas = canvas;
  _graphix = graphix;
}


int ProcessedPlotter::Process(EventData* event)
{
  if (!_enabled)
    return 1;
  RootGraphix::Lock glock = _graphix->AcquireLock();
  _canvas->Clear();
  char title[30];
  sprintf(title, "Run %d - Event %d", event->run_id, event->event_id);
  _canvas->SetTitle(title);

  int nchans = event->nchans;

  int cpp = _chans_per_pad;
  if(cpp < 1)
    cpp = (nchans > 0 ? nchans : 1);
  int total_pads = (nchans+cpp-1)/cpp+1; //extra pad for sum channel
      
  if(total_pads == 0)
    return 0;
  else if(total_pads == 1) {}
  else if(total_pads == 2)
    _canvas->Divide(2,1);
  else if(total_pads < 5)
    _canvas->Divide(2,2);
  else if(total_pads < 7)
    _canvas->Divide(3,2);
  else if(total_pads < 10)
    _canvas->Divide(3,3);
  else if(total_pads < 13)
    _canvas->Divide(4,3);
  else if(total_pads < 17)
    _canvas->Divide(4,4);
  else
    _canvas->Divide(5,4);


  //TODO clean up: remove chans_per_pad
  for (int pad=0; pad<total_pads; pad++) {
    _canvas->cd( (total_pads == 1 ? 0 : pad+1 ) );
    if( cpp == 1 || nchans == 1 ) {
      if (pad != total_pads-1) {
        event->GetTMultiGraph(event->channel_ids[pad]);
        gPad->Modified();
      }
      else {
        event->GetTMultiGraph_sumch();
        gPad->Modified();
      }
    }
      
    
  }

  _canvas->cd(0);
  _canvas->Update();

  return 1;
}
