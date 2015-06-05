/*
//========== Y. Meng Mar. 5th, DAQ header format for UCLA Acqiris Digitizer ==============

 Class DAQheader contains necessray parameters for header section of digitied raw data.
 
 void DAQheader::WriteHeaderContent()
 specifically to save necessary information into header section of raw data file in correct 
 order. 
 
 
 void DAQheader::ReadHeaderContent()
 To correctly read header section, function will read and save corresponding parameters into
 oject parameters.
 
 
 DAQheader::LoadFileName(std::string File)
 used to faciliate the raw data reading process
 
 
 
 std::vector<double> DAQheader::ReadSingleEvent(int EventNbr)
 return a double array of single event samples.

 long long type variable size: 8 byte in Windows C++, the sam as double type
 
//========================================================================================
*/

#ifndef DAQheader_hh
#define DAQheader_hh

#include <fstream>
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
using namespace std;





class DAQheader{


public:

  char FileName[300];                               //---- Binary File Name -----

  int HeaderSize;                                   //---- Header Section Size (unit: byte), include information on file level (TotEvtNbr, TriggerLevel etc.) ----

  int EventDataSize;				    //---- single event includes all channels data, also the time stamp: #1. UTC time, #2, plus milli-seconds ------				
  int ChannelDataSize;				    //---- single channel includes #1. the vGain, #2. the vOffset, #3.samples from waveform ----------
    
  int TotWorkingChannelNbr;
  int TriggerChannelNbr;

  int TotEventNbr;                                   //---- total event numbers in raw data file ------
  int TotSampleNbr;                                  //---- total sample number of single event ------

  double TimeInterval;                               //---- sampling rate (unit: sec) --------
  double TimeDelay;                                  //---- the trigger position within event (unit: percentage, 50 indicates 50%) ----

  double TriggerLevel;                               //---- Trigger Threshold (unit: mV, default sign is negtive)

  std::vector<int>     WorkingChannelNbr;
  std::vector<double>  WorkingChannelFullScale;
  std::vector<double>  WorkingChannelOffset;

  fstream binary_file;
	

  bool FormatTest();
    
  void WriteHeaderContent();
    
  void LoadFileName(std::string File);

  void ReadHeaderContent();

  //void WriteEvtTime();

  std::vector<double> ReadSingleChannel(int EventNbr, int ChannelNbr, double & gain, double & offset);
    
  std::vector< std::vector<double> > ReadEvent(int EventNbr);

  int getNchans() const { return TotWorkingChannelNbr; }
  int getTotSampleNbr() const { return TotSampleNbr; }
  double getTimeInterval_us() const { return TimeInterval*1.e6; }
  double getTimeDelay() const { return TimeDelay; }
  int getTriggerIndex() const { return getTotSampleNbr()*(int)TimeDelay/100; }
};




#endif
