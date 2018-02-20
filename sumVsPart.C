#include "style.h"
using namespace style;

void sumVsPart(
  //TString header = "Cosmic_Jan",
  //Int_t runID = 5
  TString header = "NS",
  Int_t runID = 5,
  Int_t selectChannel = 22,
  bool saveFigures = false
)
{
  zcolor(1); // rainbow
  auto xn = 200;
  auto x1 = 0.;
  auto x2 = 6000.;

  TString dataPath;
  if (header == "NS")         dataPath = "/mnt/SData0/";
  if (header == "Cosmic_Jan") dataPath = "/mnt/Data0/nscl/Cosmic_jan/";

  TString fullID = header+"_"+TString::Itoa(runID,10);
  TString eventFileName = dataPath+fullID+"_event.root";
  if (header == "Cosmic_Jan")
    eventFileName = dataPath+fullID+"_event_small.root";
  cout << "Input file: " << eventFileName << endl;

  auto file = new TFile(eventFileName,"read");
  auto tree = (TTree *) file -> Get("EventTree");

  for (auto channelID = 1; channelID <= 112; ++channelID)
  {
    if ((channelID > 48 && channelID <= 56) || channelID > 104) continue;
    if (selectChannel != -1 && selectChannel != channelID) continue;

    TString name = TString("TotalVSPart_")+fullID+Form("_Ch%d",channelID);
    cout << name << endl;

    auto hist = make(new TH2D(name,";Total (ADC);Part (ADC)",xn,x1,x2,xn,x1,x2));
    free(hist);

    auto cvs = cc(name);
    tree -> Draw(TString("Part:Sum>>")+name,Form("Channel==%d",channelID),"colz");
    cvs -> SetLogz();
    if(saveFigures) save(cvs,"png");
  }
}
