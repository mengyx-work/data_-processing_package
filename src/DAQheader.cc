/*

  

 */


#include "DAQheader.hh"
#include <fstream>
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>

using namespace std;


extern const int FileNameSize = 300;

extern const int    IntTypeSize = 4;
extern const int DoubleTypeSize = 8;

//==================================================================================================

void DAQheader::LoadFileName(std::string File){
    
  sprintf(FileName, "%s", File.c_str());
    
  binary_file.open(FileName,ios::in|ios::binary);
}


//==================================================================================================

bool DAQheader::FormatTest(){

  int      LocalIntVariable;
  double   LocalDoubleVariable;

  if(sizeof(LocalIntVariable)!=4){
    std::cout<<"The Int Type Variable Size Doesn't Match! "<<std::endl;
    return false;
  }
  else if(sizeof(LocalDoubleVariable)!=8){
    std::cout<<"The Double Type Variable Size Doesn't Match! "<<std::endl;
    return false;
  }
  else 
    return true;


}


//==================================================================================================

void DAQheader::WriteHeaderContent(){


  binary_file.write(FileName,sizeof(FileName));

  binary_file.write((char*)&TotEventNbr,sizeof(TotEventNbr));
  binary_file.write((char*)&TotSampleNbr,sizeof(TotSampleNbr));

  binary_file.write((char*)&TimeInterval,sizeof(TimeInterval));
  binary_file.write((char*)&TimeDelay,sizeof(TimeDelay));
  binary_file.write((char*)&TriggerLevel,sizeof(TriggerLevel));

  binary_file.write((char*)&TotWorkingChannelNbr,sizeof(TotWorkingChannelNbr));
  binary_file.write((char*)&TriggerChannelNbr,sizeof(TriggerChannelNbr));


  if(int(WorkingChannelNbr.size())!=TotWorkingChannelNbr){
    std::cout<<"ERROR! \n In DAQ output configueration, the working channel# are NOT consistent! "<<std::endl;
    abort();
  }


  for(int i=0; i<TotWorkingChannelNbr; i++){

    int	     tempChannelNbr = WorkingChannelNbr[i];
    double   tempChannelScale = WorkingChannelFullScale[i];
    double   tempChannelOffset = WorkingChannelOffset[i];


    binary_file.write((char*)&tempChannelNbr,	      sizeof(tempChannelNbr));
    binary_file.write((char*)&tempChannelScale,       sizeof(tempChannelScale));
    binary_file.write((char*)&tempChannelOffset,      sizeof(tempChannelOffset));
  }

    
    
}



//==================================================================================================

/*
  void DAQheader::WriteEvtTime(){


  //---------------- Event Time Stamp ------------------

  time_t localtime;

  struct _timeb tstruct;


  char UTCstring[20];
  char PluseSecStrin[10];

  long long UTCtime;	
  int PluseMilliSec;


  time( &localtime );
  _ftime( &tstruct );


  sprintf( UTCstring, "%ld", localtime );
  sprintf( PluseSecStrin, "%u", tstruct.millitm );


  UTCtime = atol(UTCstring);
  PluseMilliSec = atol(PluseSecStrin);

  //-----------------------------------------------------

  binary_file.write((char*)&UTCtime,sizeof(UTCtime));
  binary_file.write((char*)&PluseMilliSec,sizeof(PluseMilliSec));


  }
*/

//==================================================================================================


void DAQheader::ReadHeaderContent(){


  binary_file.read(FileName,sizeof(FileName));
    
  binary_file.read((char*)&TotEventNbr,sizeof(TotEventNbr));
  binary_file.read((char*)&TotSampleNbr,sizeof(TotSampleNbr));
    
  binary_file.read((char*)&TimeInterval,sizeof(TimeInterval));
  binary_file.read((char*)&TimeDelay,sizeof(TimeDelay));
  binary_file.read((char*)&TriggerLevel,sizeof(TriggerLevel));
    
  binary_file.read((char*)&TotWorkingChannelNbr,sizeof(TotWorkingChannelNbr));
  binary_file.read((char*)&TriggerChannelNbr,sizeof(TriggerChannelNbr));
    
  HeaderSize = DoubleTypeSize*3 + IntTypeSize*4 + FileNameSize;
    

  for(int i=0; i<TotWorkingChannelNbr; i++){
        
    int	     tempChannelNbr; 
    double   tempChannelScale;
    double   tempChannelOffset;
        
        
    binary_file.read((char*)&tempChannelNbr,	 sizeof(tempChannelNbr));
    binary_file.read((char*)&tempChannelScale,   sizeof(tempChannelScale));
    binary_file.read((char*)&tempChannelOffset,  sizeof(tempChannelOffset));
        
    WorkingChannelNbr.push_back(tempChannelNbr);
    WorkingChannelFullScale.push_back(tempChannelScale);
    WorkingChannelOffset.push_back(tempChannelOffset);
        
    HeaderSize += (2*DoubleTypeSize+IntTypeSize);
        
  }
    
  //---- single channel includes #1. the vGain, #2. the vOffset, #3.samples from waveform ----------
  ChannelDataSize = (TotSampleNbr + 2*DoubleTypeSize);	

  //---- single event includes all channels data, also the time stamp: #1. UTC time, #2, plus milli-seconds ------			
  EventDataSize = ChannelDataSize*TotWorkingChannelNbr + DoubleTypeSize + IntTypeSize;										


}


//==================================================================================================


std::vector<double> DAQheader::ReadSingleChannel(int EventNbr, int ChannelNbr, double & gain, double & offset)
{
    
  std::vector<double> SampleArray;
    
  const int ChannelDataLength = (TotSampleNbr + 2*DoubleTypeSize);
    
  const int EventDataLength = ChannelDataLength*TotWorkingChannelNbr + DoubleTypeSize + IntTypeSize;
    
  int  ChannelOrder = 0;
    
    
  if(EventNbr>TotEventNbr){
    std::cout<<"ERROR! \n the expected event exceeds the TotEventNbr! "<<std::endl;
    abort();
  }
    
  //----------- Check channel whether exist ---------- 
    
  bool ChannelExist = false;
    
  for(int k=0; k<TotWorkingChannelNbr; k++){
        
    if(WorkingChannelNbr[k]==ChannelNbr){
                
      ChannelOrder = k;
      ChannelExist = true;
      break;
    }
  }
    
  if(!ChannelExist){
            
    std::cout<<"ERROR! \n the expected channel is not recorded! "<<std::endl;
    abort();
  }
  //---------------------------------------------------
        
  const long int StartPoint = HeaderSize + (EventNbr-1)*EventDataLength + ChannelDataLength*ChannelOrder + (IntTypeSize + DoubleTypeSize);

        
  double vGain;
  double vOffset;
    
  binary_file.seekg(StartPoint);
    
  binary_file.read((char*)&vGain,   sizeof(vGain));
  binary_file.read((char*)&vOffset, sizeof(vOffset));
    
  //std::cout<<"Gain: "<<vGain<<", Offset: "<<vOffset<<std::endl;
    
  for(long int k=0; k<TotSampleNbr; k++){
           
    char Sample;
        
    binary_file.read((char*)&Sample,  sizeof(Sample));
        
    //double Value = (vGain*int(Sample)- vOffset)*1000;
    double Value = 1.0*int(Sample);

    SampleArray.push_back(Value);
        

  }

  gain = vGain;
  offset = vOffset;
  return SampleArray;
}


//==================================================================================================





//==================================================================================================


std::vector< std::vector<double> > DAQheader::ReadEvent(int EventNbr){
    
    
  std::vector< std::vector<double> > DataArray;
  std::vector<double>         SingleWaveform;
    
  DataArray.clear();
    
    
  const int ChannelDataLength = (TotSampleNbr + 2*DoubleTypeSize);
    
  const int EventDataLength = ChannelDataLength*TotWorkingChannelNbr + DoubleTypeSize + IntTypeSize;
    
    
  if( (EventNbr<0)||(EventNbr>TotEventNbr) ){
    std::cout<<"ERROR! \n the expected event exceeds the TotEventNbr! "<<std::endl;
    abort();
  }
    
    
  const long int StartPoint = HeaderSize + (EventNbr-1)*EventDataLength + (IntTypeSize + DoubleTypeSize);
    
  binary_file.seekg(StartPoint);
    
    
  double vGain;
  double vOffset;
    
    
  for(int channel=0; channel<TotWorkingChannelNbr; channel++){

        
    binary_file.read((char*)&vGain,   sizeof(vGain));
    binary_file.read((char*)&vOffset, sizeof(vOffset));
        
    SingleWaveform.clear();
        
    for(int samp=0; samp<TotSampleNbr; samp++){
                                                           
      char Sample;
        
      /*
        StartPoint = 2*IntTypeSize + channel*(2*DoubleTypeSize +  Data_nbrSamples) + 2*DoubleTypeSize + SampleInterval*samp;
        binary_file.seekg(StartPoint);
      */
            
      binary_file.read((char*)&Sample,  sizeof(Sample));
                                                           
      //double Value = (vGain*int(Sample)-vOffset)*1000;
      double Value = 1.0*int(Sample);    
            
      SingleWaveform.push_back(Value);

    }
                                                       
    DataArray.push_back(SingleWaveform);
  }
    
  return DataArray;
        
  /*
    binary_file.seekg(StartPoint);
    
    binary_file.read((char*)&vGain,		    sizeof(vGain));
    binary_file.read((char*)&vOffset,		sizeof(vOffset));
    
    std::cout<<"Gain: "<<vGain<<", Offset: "<<vOffset<<std::endl;
    
    for(long int k=0; k<TotSampleNbr; k++){
        
    char Sample;
        
    binary_file.read((char*)&Sample,  sizeof(Sample));
        
    double Value = (vGain*int(Sample)- vOffset)*1000;
    SampleArray.push_back(Value);
    }
    
    return SampleArray;
  */
}


//==================================================================================================
