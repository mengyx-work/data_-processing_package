/*
  Analysis code for event reconstruction in UCLA EXACT TPCs.

  Two parts to code:
  1. Event by event processing, including baseline finding, pulse finding, etc
  2. Apply cuts and generate histograms and average waveforms
  
  Compile with Makefile
  
  v0.1 AFan 2013-04-21

  v0.2 AFan 2014-02-07
  - Multiple files implemented.
  - 

*/


#include <iostream>
#include <string>
#include <fstream>
#include <time.h> 


#include "TROOT.h"

#include "TApplication.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"

#include "DAQheader.hh"
#include "CfgReader.hh"
#include "EventData.hh"
#include "Converter.hh"
#include "BaselineFinder.hh"
#include "ZeroSuppressor.hh"
#include "Integrator.hh"
#include "SumChannel.hh"
#include "PulseFinder.hh"

#include <string>

using namespace std;


int ProcessEvents(string fileList, string cfgFile, string outputfile)
{

  // Instantiate DAQheader
  DAQheader DAQ_header;
  if (DAQ_header.FormatTest()==false)
    std::cout << "ALARM! Variable size doesn't match!" << std::endl;
    
  // Instantiate CfgReader
  CfgReader cfg;
  if (!cfg.readCfgFile(cfgFile)) {
    std::cout << "ERROR reading cfg file" << std::endl;
    return 0;
  }

  // Create TTree to hold all processd info and open a file
  // to hold the TTree.
  TTree* tree = new TTree("Events", "EventData");
  TFile* rootfile = new TFile(outputfile.c_str(), "RECREATE");
  std::cout << "Saving output to "<<outputfile<<std::endl;


  // Instantiate EventData; will repopulate this object for each
  // event. Create a branch for each variable we want to save.
  EventData* event = new EventData();
  tree->Branch("run_id",              &(event->run_id));
  tree->Branch("event_id",            &(event->event_id));
  tree->Branch("nchans",              &(event->nchans));
  tree->Branch("nsamps",              &(event->nsamps));
  tree->Branch("us_per_samp",         &(event->us_per_samp));
  tree->Branch("trigger_index",       &(event->trigger_index));
  tree->Branch("trigger_index_offset",&(event->trigger_index_offset));
  tree->Branch("adc_gains",           &(event->adc_gains));
  tree->Branch("adc_offsets",         &(event->adc_offsets));
  tree->Branch("adc_ranges",          &(event->adc_ranges));
  tree->Branch("spe_means",           &(event->spe_means));
  tree->Branch("baseline_means",      &(event->baseline_means));
  tree->Branch("baseline_sigmas",     &(event->baseline_sigmas));
  tree->Branch("baseline_validities", &(event->baseline_validities));
  tree->Branch("npulses",             &(event->npulses));
  tree->Branch("pulse_start_times",   &(event->pulse_start_times));
  tree->Branch("pulse_end_times",     &(event->pulse_end_times));
  tree->Branch("pulse_peak_times",    &(event->pulse_peak_times));
  tree->Branch("pulse_peak_amps",     &(event->pulse_peak_amps));
  tree->Branch("pulse_integrals",     &(event->pulse_integrals));

    tree->Branch("saturated",                               &(event->saturated));
    tree->Branch("ch_pulse_integrals",                      &(event->ch_pulse_integrals));
    tree->Branch("ch_5samp_extended_pulse_integrals",      &(event->ch_5samp_extended_pulse_integrals));
    tree->Branch("ch_10samp_extended_pulse_integrals",     &(event->ch_10samp_extended_pulse_integrals));

  
  
  // ------------------ INSTANTIATE ALL MODULES -------------------
  Converter converter(cfg);
  BaselineFinder baselineFinder(cfg);
  ZeroSuppressor zeroSuppressor(cfg);
  SumChannel sumChannel(cfg);
  Integrator integrator(cfg);
  PulseFinder pulseFinder(cfg);
  

  //---------------- INITIALIZE MODULES (AS NEEDED) ---------------



  // -------------------- LOOP OVER FILES -------------------------


  // Do a quick loop through the files to find the total number of events.
  std::ifstream infile(fileList.c_str());
  std::string datafile;
  int total_events=0;
  
  while (infile >> datafile) {
    DAQ_header.LoadFileName(datafile.c_str());
    if (!DAQ_header.binary_file.is_open()) {
      std::cout << "\nCan't open datafile: "<< datafile.c_str() << std::endl;
      return 1;
    }
    DAQ_header.ReadHeaderContent();
    total_events+= DAQ_header.TotEventNbr;
    DAQ_header.binary_file.close();
  }
  infile.close();

  // Determine start and end of event loop.
  int min_evt = cfg.getParam<int>("tpcanalysis", "min", 1);
  int max_evt = cfg.getParam<int>("tpcanalysis", "max", total_events);
  int evt = 0;
  int subfile = -1;
  int nevents = 0;
  std::cout << "\nBeginning loop over events.\n" << std::endl;
  
  // Now loop through files...for real this time.
  infile.open(fileList.c_str());
  while (infile >> datafile) {

    if (evt>max_evt)
      break;

    // Open new data file. We've already looped through the files
    // once, so we know we can open them.
    DAQ_header.LoadFileName(datafile.c_str());
    std::cout << "Opening file "<<datafile<<std::endl;
    ++subfile;
    DAQ_header.ReadHeaderContent();

  
    // -------------------- LOOP OVER EVENTS ------------------------

    //while (evt++ < max_evt) {
    for (int n=1; n<DAQ_header.TotEventNbr; n++) {
      evt++;
      if (evt<min_evt)
        continue;
      if (evt>max_evt)
        break;
      if (evt%10000 == 0)
        std::cout << "Processing event " << evt << std::endl;
      event->Clear();
      event->run_id = subfile;
      event->event_id = n; //evt;
    
      // Run processing modules on event. ORDER MATTERS!
      converter.Process(event, DAQ_header); 
      baselineFinder.Process(event);
      zeroSuppressor.Process(event);
      sumChannel.Process(event);
      integrator.Process(event);
      pulseFinder.Process(event);


    
      tree->Fill();
    
      nevents++;
    }// end loop over events

  }// end loop over files
  //----------------- FINALIZE MODULES (AS NEEDED) ---------------


  // write TTree to file
  tree->Write();
  rootfile->Close();

  //return 1;
  return nevents;
}


//----------------------------------------------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------


int main(int args, char* argv[]) {

  // argv[1] is cfg file
  // argv[2] is input text file with list of raw data files
  // argv[3] (optional) is output file

  std::string outputfile = "output.root";

  if (args!=3 && args!=4) {
    std::cout << "Use correct command: ./tpcanalysis <cfg file> <rawdatafile> <output ROOT filename>"
              << std::endl;
    return 1;
  }
  if (args==4)
    outputfile = argv[3];
  
  // initialize ROOT application
  TApplication *theApp = new TApplication("app", 0, 0);
  theApp->SetReturnFromRun(false);


  clock_t t = clock();
  
  int nevents = ProcessEvents(argv[2], argv[1], outputfile);

  t = clock() - t;
  std::cout << "Processed "<<nevents<<" events in "<<((float)t)/CLOCKS_PER_SEC<<" s." << std::endl;
  
  return 1;
}
