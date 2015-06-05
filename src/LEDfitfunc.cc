/*

  fit function for spe spectrum, including spe, pedestal and multiple pe peaks

  liberally adapting from JBrodsky's FitOverROI

 */

#ifndef LEDfitfunc_HH
#define LEDfitfunc_HH


#include "LEDfitfunc.hh"

#include "TMath.h"
#include "TROOT.h"
#include "TFitResult.h"
#include "TSpectrum.h"
#include "TTree.h"
#include "TFile.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLine.h"
#include "TAxis.h"

#include "TList.h"
#include "TCut.h"
#include <algorithm>
#include <numeric>
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "TMatrixDSym.h"
#include "TGraph.h"
#include <fstream>

using namespace std;

#define HISTOGRAMWIDTH 7
#define NPEAKS 7

#define mCON params[CONSTANT]
#define mLAM params[LAMBDA]
#define mMEAN params[MEAN]
#define mSIG params[SIGMA]
#define mAMP params[AMP_E]
#define mPE params[P_E]
#define mSHT params[SHOTNOISE]
#define mPDM params[PEDMEAN]

const char* names[] = {"constant","lambda", "spe_mean", "spe_sigma", "amp_E",
                       "P_E", "shotnoise" ,"pedmean","npar"};



LEDfitfunc::LEDfitfunc(CfgReader cfg)
{
  moduleName = "LEDfitfunc";

  fitParams.lambda_init = cfg.getParam<double>(moduleName, "lambda_init", 0.1);
  fitParams.spemean_init = cfg.getParam<double>(moduleName, "spemean_init", 10.);
  fitParams.spesigma_init = cfg.getParam<double>(moduleName, "spesigma_init", 5.);
  fitParams.amp_E_init = cfg.getParam<double>(moduleName, "amp_E_init", 0.5);
  fitParams.p_E_init = cfg.getParam<double>(moduleName, "p_E_init", 0.1);
  fitParams.shotnoise_init = cfg.getParam<double>(moduleName, "shotnoise_init", 0.1);

  fitParams.lambda_min = cfg.getParam<double>(moduleName, "lambda_min", 0);
  fitParams.lambda_max = cfg.getParam<double>(moduleName, "lambda_max", 1);
  fitParams.spemean_min = cfg.getParam<double>(moduleName, "spemean_min", 0);
  fitParams.spemean_max = cfg.getParam<double>(moduleName, "spemean_max", 100);
  fitParams.spesigma_min = cfg.getParam<double>(moduleName, "spesigma_min", 0);
  fitParams.spesigma_max = cfg.getParam<double>(moduleName, "spesigma_max", 100.);
  fitParams.amp_E_min = cfg.getParam<double>(moduleName, "amp_E_min", 0);
  fitParams.amp_E_max = cfg.getParam<double>(moduleName, "amp_E_max", 100);
  fitParams.p_E_min = cfg.getParam<double>(moduleName, "p_E_min", 0.0001);
  fitParams.p_E_max = cfg.getParam<double>(moduleName, "p_E_max", 1.);
  fitParams.shotnoise_min = cfg.getParam<double>(moduleName, "shotnoise_min", 0);
  fitParams.shotnoise_max = cfg.getParam<double>(moduleName, "shotnoise_max", 100);

  pedrange_min = cfg.getParam<double>(moduleName, "pedrange_min", -0.4);
  pedrange_max = cfg.getParam<double>(moduleName, "pedrange_max", 0.3);

  fitfunc_min = cfg.getParam<double>(moduleName, "fitfunc_min", -0.4);
  fitfunc_max = cfg.getParam<double>(moduleName, "fitfunc_max", 20);
}




double LEDfitfunc::response_0(double* x, double* params)
{
  double y = x[0] - mPDM;
  return mCON*TMath::Poisson(0,mLAM)*TMath::Gaus(y, 0, mSHT, true);
}

double LEDfitfunc::background_func(double* x, double* params)
{
  double y = x[0] - mPDM;
  
  //mathematica version (my own (JBrodsky's) convolution)
  double exp_term = (TMath::Power(TMath::E(),(-2*mAMP*y + mSHT*mSHT)/(2.*mAMP*mAMP))*mPE
                     *(1 + TMath::Erf(((mAMP*y)/mSHT - mSHT)/(sqrt(2)*mAMP))))/(2.*mAMP);
  
  return mCON*TMath::Poisson(1,mLAM)*exp_term;
}

double LEDfitfunc::gauss_func(double* x, double* params)
{
  double y = x[0] - mPDM;
  double sigma_1 = sqrt(mSHT*mSHT + mSIG*mSIG);	
  
  double gauss_term = (1-mPE)*(TMath::Power(TMath::E(), - (mMEAN-y)*(mMEAN-y)/(2*sigma_1*sigma_1))
                               *(1 + TMath::Erf((mMEAN*mSHT*mSHT + mSIG*mSIG*y)/(sqrt(2) * mSIG*mSHT *sigma_1))) /
                               (sqrt(2*TMath::Pi())*sigma_1 * (1+ TMath::Erf(mMEAN/(sqrt(2)*mSIG)))));
  
  double response = mCON*TMath::Poisson(1,mLAM)*gauss_term;
  
  return response;
}  

double LEDfitfunc::response_1(double* x, double* params)
{
    double exp_term = background_func(x, params);
    
    double gauss_term = gauss_func(x, params);
    
    
    double response=gauss_term+exp_term;
    return response;
}

double LEDfitfunc::response_2(double* x, double* params)
{
  double y = x[0] - mPDM;
  double response=((TMath::Power(TMath::E(),(-2*mAMP*y + TMath::Power(mSHT,2))/
                                 (2.*TMath::Power(mAMP,2)))*mPE*mPE*
                    (mAMP*y - TMath::Power(mSHT,2)))/TMath::Power(mAMP,3) + 
                   (2*TMath::Power(-1 + mPE,2)*sqrt(2/TMath::Pi()))/
                   (TMath::Power(TMath::E(),TMath::Power(-2*mMEAN + y,2)/
                                 (2.*(TMath::Power(mSHT,2) + 
                                      2*TMath::Power(mSIG,2))))*mSHT*
                    sqrt(2/TMath::Power(mSHT,2) + TMath::Power(mSIG,-2))*
                    mSIG*TMath::Power(1 + TMath::Erf(mMEAN/(sqrt(2)*mSIG)),2)) 
                   + (2*TMath::Power(TMath::E(),
                                     (2*mAMP*mMEAN - 2*mAMP*y + TMath::Power(mSHT,2) + 
                                      TMath::Power(mSIG,2))/(2.*TMath::Power(mAMP,2)))*
                      (-1 + mPE)*mPE*
                      (-1 + TMath::Erf((mAMP*(mMEAN - y) + 
                                        TMath::Power(mSHT,2) + TMath::Power(mSIG,2))/
                                       (mAMP*sqrt(2*TMath::Power(mSHT,2) + 
                                                  2*TMath::Power(mSIG,2))))))
                   /(mAMP*(1 + TMath::Erf(mMEAN/(sqrt(2)*mSIG)))));
    
  return TMath::Poisson(2,mLAM)*mCON*response;
}

	
double LEDfitfunc::m_n(const double* params)
{
  return mMEAN + mAMP*mPE - mMEAN*mPE + 
    (sqrt(2/TMath::Pi())*mSIG*
     (1/(1 + TMath::Erf(mMEAN/(sqrt(2)*mSIG))) + 
      mPE/(-2 + TMath::Erfc(mMEAN/(sqrt(2)*mSIG)))))/
    TMath::Power(TMath::E(),TMath::Power(mMEAN,2)/(2.*TMath::Power(mSIG,2)));
}

double LEDfitfunc::sigma_n(const  double* params)
{
  return sqrt(-(TMath::Power(mMEAN,2)*(-1 + mPE)) + 
              2*TMath::Power(mAMP,2)*mPE  - 
              (-1 + mPE)*TMath::Power(mSIG,2) - 
              TMath::Power(mMEAN + mAMP*mPE - mMEAN*mPE + 
                           (sqrt(2/TMath::Pi())*mSIG*
                            (1/(1 + TMath::Erf(mMEAN/(sqrt(2)*mSIG))) + 
                             mPE/(-2 + TMath::Erfc(mMEAN/(sqrt(2)*mSIG)))
                             ))/
                           TMath::Power(TMath::E(),TMath::Power(mMEAN,2)/
                                        (2.*TMath::Power(mSIG,2))),2) + 
              (mMEAN*sqrt(2/TMath::Pi())*mSIG*
               (1/(1 + TMath::Erf(mMEAN/(sqrt(2)*mSIG))) + 
                mPE/(-2 + TMath::Erfc(mMEAN/(sqrt(2)*mSIG)))))
              /TMath::Power(TMath::E(),TMath::Power(mMEAN,2)/
                            (2.*TMath::Power(mSIG,2))));
}

double LEDfitfunc::pdfmean_approximate(TFitResultPtr& fitresult)
{
  const double* params = fitresult->GetParams();
  return mPE*mAMP+(1-mPE)*mMEAN;
}


double LEDfitfunc::response_multi(double* x, double* params)
{	
  double y = x[0] - mPDM;
	
		
  double response=0;
	
  for(int i=3; i<=NPEAKS; i++)
    {
      response += TMath::Poisson(i,mLAM)*
        TMath::Gaus(y,m_n(params)*i,sqrt(i*sigma_n(params)*sigma_n(params)+TMath::Power(mSHT,2)),true);
    }
  return mCON*response;
}	

double LEDfitfunc::SPEfunc(double* x, double* params)
{
  double sig = (response_0(x, params)+response_1(x,params)+response_2(x,params)+response_multi(x,params));
  
  return sig;
}


double LEDfitfunc::pdfmean_error_corr(TFitResultPtr& fitresult)
{
  TMatrixDSym cov = fitresult->GetCovarianceMatrix();
  const double* params = fitresult->GetParams();
  const double* errors = fitresult->GetErrors();
  //leaving out small correction factor from cut-off gaussian
  double pdfmean_error_uncorr_sq = TMath::Power((mAMP-mMEAN)*errors[P_E],2)
    +TMath::Power((1-mPE)*errors[MEAN],2)
    +TMath::Power(mPE*errors[AMP_E],2);
  
  return sqrt(pdfmean_error_uncorr_sq + (2*(mAMP-mMEAN)*(1-mPE)*cov[P_E][MEAN] 
                                         + 2*(mAMP-mMEAN)*mPE*cov[P_E][AMP_E] 
                                         + 2*(1-mPE)*mPE*cov[MEAN][AMP_E]));
}


double LEDfitfunc::myGaussian(double* x, double* params)
{
  double amp = params[0];
  double mu = params[1];
  double sigma = params[2];
  double y = x[0];

  double gaus = amp * TMath::Exp( -(y-mu)*(y-mu) / (2*sigma*sigma) ) /
    (sigma*TMath::Sqrt(2*TMath::Pi()));
  
  return gaus; 
}

TFitResultPtr LEDfitfunc::FitSPE(TH1F* spe, TCanvas* c, int ntriggers, bool allow_bg)
{
  TF1* spefunc = (TF1*) gROOT->GetFunction("spefunc");
  int nEvtsInRange = (int) spe->Integral("width");

  
  // set range of histogram
  double speRangeMin = spe->GetXaxis()->GetXmin();
  double speRangeMax = spe->GetXaxis()->GetXmax();
  spe->GetXaxis()->SetRangeUser(speRangeMin, speRangeMax);
  

  // determine range for fit function
  double fitmin, fitmax;
  fitmin = spe->GetBinLowEdge(spe->GetXaxis()->GetFirst());
  fitmax = 0;
  //find last non-zero bin
  int bin = spe->GetXaxis()->GetLast();
  while (spe->GetBinContent(bin) == 0) {bin--;}
  fitmax = spe->GetBinLowEdge(bin);
  fitmax = fitmax*1;

  double params[NPAR];

  //initial parameter values
  params[CONSTANT] = nEvtsInRange;
  params[LAMBDA] = fitParams.lambda_init;
  params[MEAN] = fitParams.spemean_init;
  params[SIGMA] = fitParams.spesigma_init;
  params[AMP_E] = fitParams.amp_E_init;
  params[P_E] = fitParams.p_E_init;
  params[SHOTNOISE] = fitParams.shotnoise_init;

  spefunc = new TF1("spefunc", SPEfunc, fitmin, fitmax, NPAR);
  spefunc->SetParameters(params);
  for (int i=0; i<NPAR; i++)
    spefunc->SetParName(i, names[i]);

  //parameter bounds
  double lambda_min = fitParams.lambda_min;
  double lambda_max = fitParams.lambda_max;
  double spemean_min = fitParams.spemean_min;
  double spemean_max = fitParams.spemean_max;
  double spesigma_min = fitParams.spesigma_min;
  double spesigma_max = fitParams.spesigma_max;
  double amp_E_min = fitParams.amp_E_min;
  double amp_E_max = fitParams.amp_E_max;
  double p_E_min = fitParams.p_E_min;
  double p_E_max = fitParams.p_E_max;
  double shotnoise_min = fitParams.shotnoise_min;
  double shotnoise_max = fitParams.shotnoise_max;

  spefunc->SetParLimits(LAMBDA, lambda_min, lambda_max);
  spefunc->SetParLimits(MEAN, spemean_min, spemean_max);
  spefunc->SetParLimits(SIGMA, spesigma_min, spesigma_max);
  spefunc->SetParLimits(AMP_E, amp_E_min, amp_E_max);
  spefunc->SetParLimits(P_E, p_E_min, p_E_max);
  spefunc->SetParLimits(SHOTNOISE, shotnoise_min, shotnoise_max);

  //optionally suppress exponential bg
  if (!allow_bg) {
    cout << "Disallowing exponential background for this fit" << endl;
    spefunc->SetParameter(AMP_E, 1.);
    spefunc->SetParameter(P_E, 0);
    spefunc->FixParameter(AMP_E, 1.);
    spefunc->FixParameter(P_E, 0);
  }

  spefunc->SetLineStyle(1);
  spefunc->SetLineColor(kBlue);
  
  
  // Pedestal centering
  double pedmean;
  cout << "Fitting pedestal in range [" << pedrange_min << ", " << pedrange_max << "]" << endl;
  spe->GetXaxis()->SetRangeUser(pedrange_min, pedrange_max);
  TFitResultPtr pedfit = spe->Fit("gaus", "MIS");
  if (pedfit.Get())
    pedmean = pedfit->Value(1);
  else
    pedmean = 0;
  spefunc->FixParameter(PEDMEAN, pedmean);

  
  // Fix the total area (CONSTANT)
  //spefunc->FixParameter(CONSTANT, nEvtsInRange);


  // reset func and hist ranges for full fit
  spe->GetXaxis()->SetRangeUser(speRangeMin, speRangeMax);
  fitmin = fitfunc_min;
  fitmax = fitfunc_max;
  spefunc->SetRange(fitmin, fitmax);
  

  // do the fit
  cout << endl << "Fitting entire spectrum" << endl << endl;
  TFitResultPtr fitresult = spe->Fit(spefunc, "MRELS");
  
  cout << endl << "Fit Results: " << endl
       << "Chi2/NDF = " << spefunc->GetChisquare()<<"/"<<spefunc->GetNDF()<<endl
       << "Prob = " << spefunc->GetProb() << endl << endl;
  
  
  
  
  // overlay components of fitted function
  for (int i=0; i<NPAR; i++)
    params[i] = spefunc->GetParameter(i);

  TList* funclist = spe->GetListOfFunctions();
  
  static TF1* background = new TF1("background",background_func,fitmin,fitmax,NPAR);
  background->SetRange(fitmin, fitmax);
  background->SetLineColor(kRed);
  background->SetParameters(spefunc->GetParameters());
  funclist->Add(background->Clone());
  
  static TF1* gauss_curve = new TF1("gause_curve",gauss_func,fitmin,fitmax,NPAR);
  gauss_curve->SetRange(fitmin, fitmax);
  gauss_curve->SetLineColor(kRed);
  gauss_curve->SetParameters(spefunc->GetParameters());
  funclist->Add(gauss_curve->Clone());

  
  TF1* response_0_f = (TF1*)gROOT->GetFunction("response_0_f");	
  if(!response_0_f){response_0_f = new TF1("response_0_f",response_0,fitmin,fitmax,NPAR);}
  response_0_f->SetRange(fitmin, 1.);
  response_0_f->SetLineColor(kGreen); 
  response_0_f->SetParameters(spefunc->GetParameters());
  if(response_0_f){funclist->Add(response_0_f->Clone());}
  
  
  TF1* response_1_f = (TF1*)gROOT->GetFunction("response_1_f");	
  if(!response_1_f){response_1_f = new TF1("response_1_f",response_1,fitmin,fitmax,NPAR);}
  response_1_f->SetRange(fitmin, fitmax);
  response_1_f->SetLineColor(kMagenta); 
  response_1_f->SetParameters(spefunc->GetParameters());
  if(response_1_f){funclist->Add(response_1_f->Clone());}
	
  TF1* response_2_f = (TF1*)gROOT->GetFunction("response_2_f");	
  if(!response_2_f){response_2_f = new TF1("response_2_f",response_2,fitmin,fitmax,NPAR);}
  response_2_f->SetRange(fitmin, fitmax);
  response_2_f->SetLineColor(kGreen); 
  response_2_f->SetParameters(spefunc->GetParameters());
  if(response_2_f){funclist->Add(response_2_f->Clone());}

  TF1* response_multi_f = (TF1*)gROOT->GetFunction("response_multi_f");	
  if(!response_multi_f){response_multi_f = new TF1("response_multi_f",response_multi,fitmin,fitmax,NPAR);}
  response_multi_f->SetRange(fitmin, fitmax);
  response_multi_f->SetLineColor(kGreen); 
  response_multi_f->SetParameters(spefunc->GetParameters());
  if(response_multi_f){funclist->Add(response_multi_f->Clone());}
  


  // print results
  cout<<"Valid Events collected: "<<ntriggers<<std::endl;
  cout<<"Events Passing Cuts: " <<spe->GetEntries()<<std::endl;
  cout<<"Noise fraction: "
      <<spefunc->GetParameter(AMP_E)/spefunc->GetParameter(CONSTANT)
      <<std::endl;
  cout<<"Exponential fraction: "<<spefunc->GetParameter(P_E)<<std::endl;
  cout<<"Average photoelectrons per trigger: "<<spefunc->GetParameter(LAMBDA)
      <<std::endl;
  cout<<"Pedestal Mean: "<<spefunc->GetParameter(PEDMEAN)<<" count*samples"<<endl;
  cout<<"Pedestal Width: "<<spefunc->GetParameter(SHOTNOISE)<<" count*samples"<<endl;


  cout << endl << "spe_mean = " << mMEAN << endl;
  cout << "m_n(params) = " << m_n(params) << endl;
  double pdfmean_approx = mPE*mAMP+(1-mPE)*mMEAN;
  cout << "Approximated pdfmean: " << pdfmean_approx << " +- " << pdfmean_error_corr(fitresult) << endl;
  
  // draw the histogram and function (can do later?)
  c->cd();
  spe->Draw();
  spefunc->Draw("same");


  
  return fitresult;



}

#endif
