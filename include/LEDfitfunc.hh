/*

  fit function for spe spectrum, including spe, pedestal and multiple pe peaks

  liberally adapting from JBrodsky's FitOverROI
  
 */

#ifndef LEDfitfunc_hh
#define LEDfitfunc_hh

#include "TFitResultPtr.h"
#include "TH1F.h"
#include "TCanvas.h"
#include <string>

#include "CfgReader.hh"


class LEDfitfunc
{
    
public:

  LEDfitfunc(CfgReader cfg);
  
  //declare function to do fit here
  TFitResultPtr FitSPE(TH1F* spe, TCanvas* c, int ntriggers, bool allow_bg=true);


  
private:
  string moduleName;
  
  enum PARAMETERS {CONSTANT, LAMBDA, MEAN, SIGMA, AMP_E, P_E, SHOTNOISE, PEDMEAN, NPAR };

  static double background_func(double* x, double* params);
  static double gauss_func(double* x, double* params);
  static double response_0(double* x, double* params);
  static double response_1(double* x, double* params);
  static double response_2(double* x, double* params);
  static double m_n(const double* params);
  static double sigma_n(const double* params);
  static double response_multi(double* x, double* params);
  static double SPEfunc(double* x, double* params);
  static double pdfmean_approximate(TFitResultPtr& fitresult);
  static double pdfmean_error_corr(TFitResultPtr& fitresult);
  
  double myGaussian(double* x, double* params);

  struct FitParams {
    double lambda_init; 
    double spemean_init; 
    double spesigma_init; 
    double amp_E_init; 
    double p_E_init; 
    double shotnoise_init;

    double lambda_min;
    double lambda_max;
    double spemean_min;
    double spemean_max;
    double spesigma_min;
    double spesigma_max;
    double amp_E_min;
    double amp_E_max;
    double p_E_min;
    double p_E_max;
    double shotnoise_min;
    double shotnoise_max;
  };

  double pedrange_min;
  double pedrange_max;

  double fitfunc_min;
  double fitfunc_max;
  
  FitParams fitParams;

  
  //declare error function

};





#endif
