#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "TF1.h"
#include "TChain.h"
#include "TTree.h"

TH1F* OneDimHist(std::string HistName, std::string Title="Title", std::string xAxisTitle="xAxisTitle", Int_t BinNbr=500, Float_t StartValue=0, Float_t EndValue=100,  Float_t LineColorNbr=38, Float_t FillColorNbr=0){
    
    TH1F   *hist = new TH1F(HistName.c_str(), HistName.c_str(), BinNbr, StartValue, EndValue);
    
    hist->GetXaxis()->SetTitle(xAxisTitle.c_str());
    hist->GetXaxis()->CenterTitle(true);
    hist->GetXaxis()->SetTitleSize(0.02);
    hist->GetYaxis()->SetTitle("Event/Bin");
    hist->GetYaxis()->CenterTitle(true);
    hist->GetYaxis()->SetTitleSize(0.03);
    hist->SetTitle(Title.c_str());
    hist->SetTitleSize(0.05);
    hist->SetFillColor(FillColorNbr);
    hist->SetLineColor(LineColorNbr);
    hist->SetLineWidth(3);
    
    return hist;
    
}