#include "style.h"
using namespace style; 

Long64_t fNumEvents;
Long64_t fCurrentEventID = 0;

TTree *fTree;
Int_t numChannels, channelIDs[112];
Short_t rawADC[112][240];
Double_t total[112], part[112], halfTime[112];

bool saveFlag = true;

vector<TCanvas*> pads;
TString fFullID;

Int_t n(Long64_t eventID = -1);
void w();

void channel(
  TString header = "NS",
  Int_t runID = 2
)
{
  gstat(0);

  TString dataPath;
  if (header == "NS")         dataPath = "/mnt/SData0/";
  if (header == "Cosmic_Jan") dataPath = "/mnt/Data0/nscl/Cosmic_jan/";

  fFullID = header+"_"+TString::Itoa(runID,10);
  TString eventFileName = dataPath+fFullID+"_event.root";
  if (header == "Cosmic_Jan")
    eventFileName = dataPath+fFullID+"_event_small.root";
  cout << "Input file: " << eventFileName << endl;

  auto file = new TFile(eventFileName,"read");
  fTree = (TTree *) file -> Get("EventTree");
  fTree -> SetBranchAddress("nFADC",&numChannels);
  fTree -> SetBranchAddress("Channel",&channelIDs);
  fTree -> SetBranchAddress("FADC",&rawADC);
  fTree -> SetBranchAddress("Time",&halfTime);
  fTree -> SetBranchAddress("Sum",&total);
  fTree -> SetBranchAddress("Part",&part);

  auto nw = new NWDetector();
  nw -> AddParameterFile("NeutronWall.par");
  nw -> Init();

  auto plane = nw -> GetDetectorPlane(0);
  auto histPlane = plane -> GetHist();

  fNumEvents = fTree -> GetEntries();
}

Int_t n(Long64_t eventID)
{
  if (eventID >= fNumEvents) {
    cout << "Total number of events are: " << fNumEvents << endl;
    return 0;
  }
  else if (eventID < 0)
    fCurrentEventID = fCurrentEventID+1;
  else
    fCurrentEventID = eventID;

  fTree -> GetEntry(fCurrentEventID);

  cout << "Event-" << fCurrentEventID << " Channel-" << numChannels << endl;
  if (numChannels == 0) {
    cout << "No channels!" << endl;
    return n();
  }

  for (auto pad : pads)
    pad -> Close();
  pads.clear();

  auto trueCount = 0;
  for (auto iChannel = 0; iChannel < numChannels; ++iChannel)
  {
    Int_t tb = Int_t(halfTime[iChannel]);
    if (tb < 50 || tb > 200)
      continue;

    if (part[iChannel]<-total[iChannel]+1100)
      continue;

    auto channelID = channelIDs[iChannel];
    auto channelID2 = channelID; 

    if (channelID2 > 48) channelID2 = channelID - 56;
    if (channelID2 < 24) channelID2 = channelID + 24;
    else                 channelID2 = channelID - 24;

    auto channel = new KBChannelBufferS();
    cout << "Channel-" << channelID << "(" << channelID2 << ") ";
    channel -> SetID(fCurrentEventID*1000+channelID);
    channel -> Set(240);
    for (Int_t tb = 0; tb < 240; ++tb)
      channel -> SetAt(rawADC[iChannel][tb],tb);

    TString tovp = "Neutron";
    if (part[iChannel]/total[iChannel] > 0.8)
      tovp = "Gamma";

    TString name = TString("ADC_")+fFullID+"_"+tovp+Form("_Ev%lld_Ch%d_T%d",fCurrentEventID,channelID,tb);

    auto cvs = c(name);
    pads.push_back(cvs);
    channel -> Draw();
    if (saveFlag) 
      save(cvs,"png");

    ++trueCount;
  }
  cout << endl;

  return trueCount;
}

void w(Int_t ncount)
{
  for (auto count = 0; count < ncount;) {
    count += n();
  }
}
