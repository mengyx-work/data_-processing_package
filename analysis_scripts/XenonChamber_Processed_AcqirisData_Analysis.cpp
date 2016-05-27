#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

#include "TFile.h"
#include "TROOT.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TF1.h"
#include "TString.h"

#include "THStack.h"
#include "TMath.h"
#include "TH2F.h"
#include "TLegend.h"

#include "ScENE_Analysis.h"


//void ScENE_G4_ProcessedData_20keVNeutron_SpectrumAnalysis(char *argv)
void XenonChamber_Processed_AcqirisData_Analysis()
{
    using namespace std;
    
    
    /*
     string rootFile;
     cin>>rootFile;
     
     
     if(rootFile.empty())
     {
     cout<<"ABORT!"<<endl;
     cout<<" the root file is missing! "<<endl;
     cout<<"./Executable File + ROOT File Name "<<endl;
     exit(0);
     }
     */
    
    /*
     if(argc!=2)
     {
     cout<<"ABORT!"<<endl;
     cout<<" argument# is NOT correct "<<endl;
     cout<<"./Executable File + ROOT File Name "<<endl;
     exit(0);
     }
     */
    
    
    
    /*
     TFile     *f = new TFile(argv, "READ");
     TTree *tData = (TTree*)f->Get("tData");
     */
    

    
    string ROOT_File = "Run021_Co57_ProcessedData.root";

    TFile     *f = new TFile(ROOT_File.c_str(), "READ");
    TTree *tData = (TTree*)f->Get("Events");
    
    
    //gROOT->ProcessLine("#include <vector>");
    gStyle->SetOptFit();
    
    int run_id;
    int event_id;
    int nchans;
    int nsamps;
    double us_per_samp;
    int trigger_index;
    int trigger_index_offset; //for top-channels only
    int npulses;

    
    vector<int> channel_nums; // DAQ channel number. check that this is same in every event
    vector<int> channel_ids; // global channel ID to be used by all modules
    vector<double> *adc_gains = new vector<double>; // volts per ADC-count
    vector<double> *adc_offsets = new vector<double>;
    vector<double> *adc_ranges = new vector<double>;
    vector<double> *spe_means = new vector<double>;
    vector<double> *baseline_means = new vector<double>;
    vector<double> *baseline_sigmas = new vector<double>;

    
    vector<double> *sum_waveform = new vector<double>;
    vector<double> *sum_integral;
    vector<double> *pulse_start_times = new vector<double>;
    vector<double> *pulse_end_times = new vector<double>;
    vector<double> *pulse_peak_times = new vector<double>;
    vector<double> *pulse_peak_amps = new vector<double>;
    vector<double> *pulse_integrals = new vector<double>;
    
    vector<bool> *saturated = new vector<bool>;
    
    vector< vector<double> > *ch_pulse_integrals = new vector< vector<double> >;
    vector< vector<double> > *ch_pulse_peak_amps = new vector< vector<double> >;
    vector< vector<double> > *ch_5samp_extended_pulse_integrals = new vector< vector<double> >;
    vector< vector<double> > *ch_10samp_extended_pulse_integrals = new vector< vector<double> >;
    
    
       
    tData->SetBranchAddress("run_id",              &run_id);
    tData->SetBranchAddress("event_id",            &event_id);
    tData->SetBranchAddress("nchans",              &nchans);
    tData->SetBranchAddress("nsamps",              &nsamps);
    tData->SetBranchAddress("us_per_samp",         &us_per_samp);
    tData->SetBranchAddress("trigger_index",       &trigger_index);
    tData->SetBranchAddress("trigger_index_offset",&trigger_index_offset);
    tData->SetBranchAddress("adc_gains",           &adc_gains);
    tData->SetBranchAddress("adc_offsets",         &adc_offsets);
    tData->SetBranchAddress("adc_ranges",          &adc_ranges);
    tData->SetBranchAddress("spe_means",           &spe_means);
    tData->SetBranchAddress("baseline_means",      &baseline_means);
    tData->SetBranchAddress("baseline_sigmas",     &baseline_sigmas);
    //tData->SetBranchAddress("baseline_validities", &baseline_validities);
    tData->SetBranchAddress("npulses",             &npulses);
    tData->SetBranchAddress("pulse_start_times",   &pulse_start_times);
    tData->SetBranchAddress("pulse_end_times",     &pulse_end_times);
    tData->SetBranchAddress("pulse_peak_times",    &pulse_peak_times);
    tData->SetBranchAddress("pulse_peak_amps",     &pulse_peak_amps);
    tData->SetBranchAddress("pulse_integrals",     &pulse_integrals);
    
    tData->SetBranchAddress("saturated",                               &saturated);
    tData->SetBranchAddress("ch_pulse_integrals",                      &ch_pulse_integrals);
    tData->SetBranchAddress("ch_5samp_extended_pulse_integrals",      &ch_5samp_extended_pulse_integrals);
    tData->SetBranchAddress("ch_10samp_extended_pulse_integrals",     &ch_10samp_extended_pulse_integrals);
    

    
    TCanvas *c0 = new TCanvas("c0", "c0", 2000, 1000);
    TCanvas *c1 = new TCanvas("c1", "c1", 2000, 1000);

    TH1F    *hist_S1 = new TH1F("hist_S1", "", 500, 0, 2000);
    
    //hist_S1->SetStats(0);
    hist_S1->SetTitleSize(0.05);
    hist_S1->SetLineWidth(1);
    hist_S1->GetXaxis()->SetTitle("S1 [PE]");
    hist_S1->GetXaxis()->CenterTitle(false);
    hist_S1->GetXaxis()->SetTitleSize(0.03);
    hist_S1->GetYaxis()->SetTitle("[Counts/Bin]");
    hist_S1->GetYaxis()->CenterTitle(false);
    hist_S1->GetYaxis()->SetTitleSize(0.03);
    hist_S1->SetTitle("Run021 S1 from ^{57}Co Calibration ");
    hist_S1->SetLineColor(38);

    
    TH1F    *hist_max_amp = new TH1F("hist_max_amp", "", 1000, 0, 10000);

    const int  HistNbr = 8;
    const int  BinNbr = 1000;
    
    Float_t  Hist_StartValue = 0;
    Float_t  Hist_EndValue   = 4000;
    
    //gStyle->SetHistLineWidth(3);
    
    TH1F         *Hist_Channel_S1 = new TH1F[HistNbr];
    
    
     for(int t=0; t<HistNbr; t++){
     
         
        Hist_Channel_S1[t] = OneDimHist(Form("Hist_Channel_S1_%i", t),  //--- Hist Name ---
                                                        "S1 Spectrum",  //--- Title ---
                                                            "S1 [PE]",  //--- xAxis Uit ---
                                                               BinNbr,  //--- BinNbr ---
                                                      Hist_StartValue,
                                                        Hist_EndValue,
                                                                (t+2),  //--- Line Color ---
                                                                   0);
         
     
     }
     

    
    
    TF1* Gaus_Func = new TF1("Gaus_Func","gaus",800,1500);
    
    TF1* Gaus_Co57_xRay_Func = new TF1("Gaus_Func","gaus",200,400);
    
    
    Int_t EntryNbr = (Int_t)tData->GetEntries();
    
    for (Int_t i=0; i<EntryNbr; i++)
    {
        
        tData->GetEntry(i);
        
        //std::cout<<"Evt#: "<<i<<std::endl;
        
        
        bool Ch_Saturated = false;
        
        //--- because when the baseline if not found, the saturation check will not be proceeded. ---
        //--- check the array size ---
        if(saturated->size()==nchans){
     
            for(int t=0; t<nchans; t++){
                bool value = saturated->at(t);
                if(value==true){
                    Ch_Saturated = true;
                    break;
                }
            
            }
        }
        
        //if((!Ch_Saturated)&&(npulses==1)){
        if((!Ch_Saturated)&&(npulses>0)){
            
            double area = pulse_integrals->at(0);
            hist_S1->Fill(area);
            
             for(int t=0; t<HistNbr; t++){
                 
                 vector<double> *channel_pulse_area = &ch_pulse_integrals->at(t);
                 double ch_pulse_area = channel_pulse_area->at(0);
                 Hist_Channel_S1[t].Fill(ch_pulse_area);
                 //std::cout<<ch_pulse_integrals.size()<<std::endl;
                 //std::cout<<"Channel# "<<t<<", "<<ch_pulse_area<<std::endl;
             }
        
        }
    }//--- end of event loop ---

    ///*
    c0->cd();
    hist_S1->Fit(Gaus_Func,"R+");
    hist_S1->Fit(Gaus_Co57_xRay_Func,"R+");
    hist_S1->Draw("SAMES");

    c0->SaveAs("ScENE_XenonChamber_Run021_Co57_S1_Spectrum.pdf");
    c0->SaveAs("ScENE_XenonChamber_Run021_Co57_S1_Spectrum.eps");
    //*/
    
    
    
    c1->cd();
    //c1->SetLogy();
    /*
    Double_t norm = 1000;
    Double_t scale;
    
    for(int t=0; t<HistNbr; t++){
        std::cout<<Hist_Channel_S1[t].Integral()<<std::endl;
        scale = norm/(Hist_Channel_S1[t].Integral());
        Hist_Channel_S1[t].Scale(scale);
    }
    */
    ///*
    
    Hist_Channel_S1[0].SetMaximum(5000.);
    Hist_Channel_S1[0].SetMinimum(0.);
    
    Hist_Channel_S1[0].SetStats(0);
    Hist_Channel_S1[0].Draw("");

    
        for(int t=1; t<HistNbr; t++)
        Hist_Channel_S1[t].Draw("SAME");
    
    
    
    TLegend* leg0 = new TLegend(0.7,0.55,0.9,0.9);
    leg0->SetFillColor(0);
    
    for(int t=0; t<HistNbr; t++)
    leg0->AddEntry(&Hist_Channel_S1[t],   Form("Channel_%i S1 Spectrum", t), "L");

    leg0->SetTextSize(0.02);
    leg0->Draw("SAME");

    
    
}
