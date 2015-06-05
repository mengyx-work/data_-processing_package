/*
  Event viewer code for data from UCLA EXACT TPCs. Can overlay analysis

  Two parts to code:
  1. Event by event processing, including baseline finding, pulse finding, etc
  2. Apply cuts and generate histograms and average waveforms
  
  Compile with Makefile
  
  v0.1 AFan 2013-04-21
    - base code adapted from tpcanalysis.cc
  v0.2 AFan 2013-08-17
    - TApplication works as expected now:
    - GUI is responsive, cmd line entry works, event stepping works
  v0.3 AFan 2014-01-21
    - Better event viewer. Uses multithreading.

 */


#include <iostream>
#include <string>
#include <fstream>


#include "TApplication.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TSystem.h"
#include "TTimer.h"
#include "TRootCanvas.h"

#include "DAQheader.hh"
#include "CfgReader.hh"
#include "EventData.hh"
#include "Converter.hh"
#include "BaselineFinder.hh"
#include "ZeroSuppressor.hh"
#include "Integrator.hh"
#include "SumChannel.hh"
#include "PulseFinder.hh"
#include "ProcessedPlotter.hh"
#include "RootGraphix.hh"

#include <string>

using namespace std;



int ProcessEvents(DAQheader& DAQ_header, string cfgFile )
{

    
  // Instantiate CfgReader
  CfgReader cfg;
  if (!cfg.readCfgFile(cfgFile)) {
    std::cout << "ERROR reading cfg file" << std::endl;
    return 0;
  }


  // Repopulate these objects for each new event
  EventData* event = new EventData();
  TCanvas* c = new TCanvas("c", "c");

  
  //------------------- INSTANTIATE ALL MODULES -------------------
  Converter converter(cfg);
  BaselineFinder baselineFinder(cfg);
  ZeroSuppressor zeroSuppressor(cfg);
  SumChannel sumChannel(cfg);
  Integrator integrator(cfg);
  PulseFinder pulseFinder(cfg);

  ProcessedPlotter plotter(cfg);


  //---------------- INITIALIZE MODULES (AS NEEDED) ---------------
  RootGraphix* graphix = new RootGraphix;
  graphix->Initialize();
  plotter.Initialize(c, graphix);
  
  
  //---------------------- DRAW AN EVENT --------------------------
  int evt = 1;
  std::string line;
  while (line!="q") {
    
    event->Clear();
    event->run_id = 0;
    event->event_id = evt;

    // Run all the modules. ORDER MATTERS!
    converter.Process(event, DAQ_header);
    baselineFinder.Process(event);
    zeroSuppressor.Process(event);
    sumChannel.Process(event);
    integrator.Process(event);
    pulseFinder.Process(event);
    plotter.Process(event);
    gPad->Modified();
    gPad->Update();


    // Decide what to do next
    cout << "Enter option: " << endl
         << "  <enter> for next event" << endl
         << "  b for prev event" << endl
         << "  # for event_id #" << endl
         << "  q to quit" << endl;
    
    getline(std::cin, line);

    // read and interpret command line input
    if (line=="")
      evt++;
    else if (line=="b")
      evt--;
    else if (line=="q"||line=="Q")
      break;
    else
      evt = atoi(line.c_str());

  }


  
  graphix->Finalize();
  if (c) delete c;
  return 1;
}


//----------------------------------------------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------


int main(int args, char* argv[]) {

  if (args!=3) {
    std::cout << "Use correct command: ./eventviewer <cfg file> <rawdatafile>"
              << std::endl;
    return 1;
  }
  
  // initialize ROOT application
  TApplication *theApp = new TApplication("app", 0, 0);
  theApp->SetReturnFromRun(true);
  //theApp->ProcessFile(".rootstart.C");

  // initialize DAQheader
  DAQheader DAQ_header;
  if (DAQ_header.FormatTest()==false)
    std::cout << "ALARM! Variable size doesn't match!" << std::endl;

  // open raw data file
  string datafile = argv[2];
  DAQ_header.LoadFileName(datafile.c_str());
  if (!DAQ_header.binary_file.is_open()) {
    std::cout << std::endl << "Can't open datafile: "
              << datafile.c_str() << std::endl;
    return 1;
  }
  DAQ_header.ReadHeaderContent();

  return ProcessEvents(DAQ_header, argv[1]);
}
