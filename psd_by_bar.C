#include "style.h"
using namespace style;

void psd_by_bar()
{
  zcolor(1); // rainbow
  auto xn = 500;
  auto x1 = 0.;
  auto x2 = 10000.;

  auto file = new TFile("/mnt/WD/MonData/summary_psd.root","read");
  auto tree = (TTree *) file -> Get("psd");
  cout << tree -> GetEntries() << endl;

  auto h2 = new TH2D("Asumpart","PSA Wall-A;Total (ADC);Part (ADC)",xn,x1,x2,xn,x1,x2); free(make(h2));
       h2 = new TH2D("Bsumpart","PSA Wall-B;Total (ADC);Part (ADC)",xn,x1,x2,xn,x1,x2); free(make(h2));
  auto h1 = new TH1D("Asumovpart","Part/Sum Wall-A;ADC Total/Part",200,0.5,2);          free(make(h1));
       h1 = new TH1D("Bsumovpart","Part/Sum Wall-B;ADC Total/Part",200,0.5,2);          free(make(h1));

  auto c2 = cc(); tree -> Draw("part:total>>Asumpart"," isA","colz"); c2 -> SetLogz();
       c2 = cc(); tree -> Draw("part:total>>Bsumpart","!isA","colz"); c2 -> SetLogz();
       c2 = cc(); tree -> Draw("part/sum>>Asumovpart"," isA","");
       c2 = cc(); tree -> Draw("part/sum>>Asumovpart","!isA","");

  for (bool isA : {true, false}) {
    TString abname = Form("psd%s",isA?"A":"B");
    auto cvs = new TCanvas(abname,"",1800,1200);
    cvs -> SetLogz();
    cvs -> Divide(6,4);
    for (auto id = 1; id <= 24; ++id) {
      TString name = abname + Form("-%d",id);
      cout << name << endl;
      cvs -> cd(id);
      auto hist = new TH2D(name,name+";Total (ADC);Part (ADC)",xn,x1,x2,xn,x1,x2);
      free(make(hist));
      if (isA) tree -> Draw(TString("part:total>>")+name,Form(" isA&&channelID==%d",id),"colz");
      else     tree -> Draw(TString("part:total>>")+name,Form("!isA&&channelID==%d",id),"colz");
    }
  }
}
