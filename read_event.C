#include "style.h"
using namespace style;

void read_event()
{
  auto file = new TFile("MonData/RUN_200_event.root");
  auto tree = (TTree *) file -> Get("EventTree");
  tree -> Print("");

  gstat(0);

  cc();
  auto hist = new TH1D("hist","",512,0,512);
  tree -> Draw("SPWAVETime>>hist");

  cc();
  auto hista = new TH2D("asumpart","",1000,0,1000,1000,0,1000);
  tree -> Draw("AModSum:AModPart>>sumpart","","colz");

  cc();
  auto histb = new TH2D("bsumpart","",1000,0,1000,1000,0,1000);
  tree -> Draw("AModSum:AModPart>>bsumpart","","colz");

  cc();
  auto histt =  new TH2D("histt","",25,0,25,400,-20,20);
  tree -> Draw("AModTime[][0]-AModTime[][1]:AID>>histt");

  //tree -> Draw("AGeoMeanSum");
  //tree -> Draw("AGeoMeanPart");
  //tree -> Draw("AMeanTime");
  //tree -> Draw("ASubTime");
  //tree -> Draw("AModTime");
  //tree -> Draw("AModPeak");
  //tree -> Draw("AModPed");
}
