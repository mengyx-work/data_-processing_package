#ifndef RootGraphix_hh
#define RootGraphix_hh

#include "TMutex.h"
#include "TThread.h"
#include "TApplication.h"

#include <memory>

class TCanvas;
class TGMainFrame;

class RootGraphix
{
public:
  RootGraphix();

  void Initialize();
  void Finalize();

  typedef std::auto_ptr<TLockGuard> Lock;
  Lock AcquireLock();


  TCanvas* GetCanvas(const char* title=0, bool preventclose=true, bool hidemenu=false);

private:
  TMutex _mutex;
  TThread _thread;

  std::vector<TCanvas*> _canvases;
  TGMainFrame* _mainframe;
  bool _single_window;
  int _window_w;
  int _window_h;
  

};


#endif
