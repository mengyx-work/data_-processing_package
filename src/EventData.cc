#include "EventData.hh"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TAxis.h"
#include "TLine.h"
#include "TBox.h"
#include "TPad.h"
#include "TList.h"
#include "TGaxis.h"
#include "TMarker.h"
#include "TStyle.h"
#include <complex> //abs
#include <algorithm> //min_element
#include <iostream>  // std::cerr
#include <stdexcept> // std::out_of_range
#include <vector>

double EventData::SampleToTime(int samp) const
{
  return (samp-trigger_index)*us_per_samp;
}

int EventData::TimeToSample(double time, bool checkrange) const
{
  int samp = (int)(time/us_per_samp)+trigger_index;
  if (samp > nsamps)
    samp = nsamps;
  else if (samp < 0)
    samp = 0;

  return samp;
}


TMultiGraph* EventData::GetTMultiGraph(int ch)
{

  //int idx = ch;
  char name[30];
  sprintf(name, "r%ie%ich%i", run_id, event_id, channel_ids[ch]);
  TMultiGraph* mg = new TMultiGraph(name, name);

  
  // set the x axis
  std::vector<double> x(nsamps);
  for(int i=0; i<nsamps; i++)
    x[i] = (i - trigger_index) * us_per_samp;


  try {
    std::vector<double> const& raw = raw_waveforms.at(ch);
    //std::vector<double> const& raw = baseline_subtracted_waveforms[idx];
    TGraph* gr_raw = new TGraph(nsamps, &x[0], &raw[0]);
    gr_raw->SetTitle(name);
    gr_raw->SetName(name);
    gr_raw->SetMarkerStyle(7);
    mg->Add(gr_raw);
    
    mg->Draw("alp");
    mg->GetXaxis()->SetTitle("time [#mus]");
    mg->GetYaxis()->SetTitle("amp [counts]");
  }
  catch (const std::out_of_range& oor) {
    //std::cerr << "Out of Range error: " << oor.what() << '\n';
  }
  
  try { 
    std::vector<double> baseline = baseline_subtracted_waveforms.at(ch);
    std::vector<double> const& raw = raw_waveforms.at(ch);
    for (size_t i=0; i<baseline.size(); i++)
      baseline[i] = raw[i] - baseline[i];
    TGraph* gr_baseline = new TGraph(nsamps, &x[0], &baseline[0]);
    gr_baseline->SetMarkerColor(kRed);
    gr_baseline->SetLineColor(kRed);
    mg->Add(gr_baseline);
  }
  catch (const std::out_of_range& oor) {
    //std::cerr << "Out of Range error: " << oor.what() << '\n';
  }

  
  // need to adjust size of integral so it fits
  try {
    std::vector<double> adjusted_integral(nsamps); 
    double integral_offset = baseline_means.at(ch); //(draw_baseline_subtracted ? 0 : bs_info.mean);
    double x1,x2,y1,y2;
    gPad->Update();
    gPad->GetRangeAxis(x1,y1,x2,y2);
    double raw_ratio = (y2 - integral_offset) / (integral_offset - y1);
    double integral_max = *std::max_element(integrals.at(ch).begin(), integrals.at(ch).end());
    double integral_min = *std::min_element(integrals.at(ch).begin(), integrals.at(ch).end());
    double integral_ratio = std::abs(integral_max) / std::abs(integral_min);
    double integral_scale;
    if (raw_ratio < integral_ratio)
      integral_scale = (y2 - integral_offset) / std::abs(integral_max) * 0.9;
    else
      integral_scale = (integral_offset - y1) / std::abs(integral_min) * 0.9;
  
  
    for(int i = 0; i<nsamps; i++)
      adjusted_integral[i] = integral_scale*integrals.at(ch)[i] + integral_offset;
  
    int integral_color = kBlue;
  
    TGraph* integral_gr = new TGraph(nsamps, &x[0], &adjusted_integral[0]);
    integral_gr->SetLineColor(integral_color);
    integral_gr->SetMarkerColor(integral_color);
    mg->Add(integral_gr);
  }
  catch (const std::out_of_range& oor) {
    //std::cerr << "Out of Range error: " << oor.what() << '\n';
  }


  
  return mg;
}


TMultiGraph* EventData::GetTMultiGraph_sumch()
{

  char name[30];
  sprintf(name, "r%ie%ichSUM", run_id, event_id);
  TMultiGraph* mg = new TMultiGraph(name, name);
  
  if (sum_waveform.empty())
    return mg;
  int nsamps = sum_waveform.size();
  std::vector<double> x(nsamps);


  // set the x axis
  for(int i=0; i<nsamps; i++)
    x[i] = (i - trigger_index) * us_per_samp;

  TGraph* gr_raw = new TGraph(nsamps, &x[0], &sum_waveform[0]);
  gr_raw->SetTitle(name);
  gr_raw->SetName(name);
  mg->Add(gr_raw);

  mg->Draw("alp");
  mg->GetXaxis()->SetTitle("time [#mus]");
  mg->GetYaxis()->SetTitle("amp [arb]");

  
  
  
  std::vector<double> baseline = sum_waveform;
  for (size_t i=0; i<baseline.size(); i++)
    baseline[i] = sum_waveform[i] - baseline[i];
  TGraph* gr_baseline = new TGraph(nsamps, &x[0], &baseline[0]);
  gr_baseline->SetMarkerColor(kRed);
  gr_baseline->SetLineColor(kRed);
  mg->Add(gr_baseline);


  if (sum_integral.empty())
    return mg;
  
  // need to adjust size of integral so it fits
  std::vector<double> adjusted_integral(nsamps); 
  double integral_offset = 0; 
  double x1,x2,y1,y2;
  gPad->Update();
  gPad->GetRangeAxis(x1,y1,x2,y2);
  double raw_ratio = (y2 - integral_offset) / (integral_offset - y1);
  double integral_max = *std::max_element(sum_integral.begin(), sum_integral.end());
  double integral_min = *std::min_element(sum_integral.begin(), sum_integral.end());
  double integral_ratio = std::abs(integral_max) / std::abs(integral_min);
  double integral_scale;
  if (raw_ratio < integral_ratio)
    integral_scale = (y2 - integral_offset) / std::abs(integral_max) * 0.9;
  else
    integral_scale = (integral_offset - y1) / std::abs(integral_min) * 0.9;
  
  
  for(int i = 0; i<nsamps; i++)
    adjusted_integral[i] = integral_scale*sum_integral[i] + integral_offset;
  
  int integral_color = kBlue;
  
  TGraph* integral_gr = new TGraph(nsamps, &x[0], &adjusted_integral[0]);
  integral_gr->SetLineColor(integral_color);
  integral_gr->SetMarkerColor(integral_color);
  mg->Add(integral_gr);
  

  for (size_t i=0; i<pulse_start_times.size(); i++) {
    double base = 0;
    double peak_y = base + pulse_peak_amps[i];
    TBox* pbox = new TBox( pulse_start_times[i], base,
                           pulse_end_times[i], peak_y );
    pbox->SetBit(TObject::kCanDelete,true);
    pbox->SetLineColor(kGreen);
    pbox->SetFillStyle(0);
    pbox->Draw();
    //TLine* pline = new TLine( x[pulse_param.peak_index], base,
    //                          x[pulse_param.peak_index], peak_y);
    //pline->SetBit(TObject::kCanDelete,true);
    //pline->SetLineColor(kMagenta);
    //pline->Draw();
  }//end loop over pulses

  
  return mg;
}

