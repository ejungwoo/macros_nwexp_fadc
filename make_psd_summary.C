#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include <fstream>
#include <iostream>
using namespace std;

//#include "style.h"
//using namespace style;

void make_psd_summary()
{
  auto chain = new TChain("EventTree");
  TString fileName;
  ifstream file("runList.txt");
  while (file >> fileName) {
    cout << "Adding file: " << fileName << endl;
    chain -> Add(fileName);
  }

  Int_t NA, NB;
  Int_t Aid[28];
  Int_t Bid[28];
  Double_t AGeoSum[28];
  Double_t BGeoSum[28];
  Double_t AGeoPart[28];
  Double_t BGeoPart[28];

  chain -> SetBranchAddress("NA", &NA);
  chain -> SetBranchAddress("NB", &NB);
  chain -> SetBranchAddress("AID", &Aid);
  chain -> SetBranchAddress("BID", &Bid);
  chain -> SetBranchAddress("AGeoMeanSum", &AGeoSum);
  chain -> SetBranchAddress("BGeoMeanSum", &BGeoSum);
  chain -> SetBranchAddress("AGeoMeanPart",&AGeoPart);
  chain -> SetBranchAddress("BGeoMeanPart",&BGeoPart);

  auto outfile = new TFile("/mnt/WD/MonData/summary_psd.root","recreate");
  auto outtree = new TTree("psd","");

  bool AorB;
  Int_t channelID;
  Double_t geoSum, geoPart;

  outtree -> Branch("isA", &AorB);
  outtree -> Branch("channelID", &channelID);
  outtree -> Branch("total", &geoSum);
  outtree -> Branch("part",  &geoPart);

  auto numEvents = chain -> GetEntries();
  for (Long64_t eventID = 0; eventID < numEvents; ++eventID) {
    chain -> GetEntry(eventID);
    if (eventID % 200000 == 0)
      cout << eventID << endl;

    for (auto i = 0; i < NA; ++i) {
      AorB = true;
      channelID = Aid[i];
      geoSum = AGeoSum[i];
      geoPart = AGeoPart[i];
      outtree -> Fill();
    }

    for (auto i = 0; i < NB; ++i) {
      AorB = false;
      channelID = Bid[i];
      geoSum = BGeoSum[i];
      geoPart = BGeoPart[i];
      outtree -> Fill();
    }
  }

  outfile -> cd();
  outtree -> Write();
  outfile -> Close();

  /*
  auto h2 = new TH2D("Asumpart","PSA Wall-A;Total (ADC);Part (ADC)",xn,x1,x2,xn,x1,x2); free(make(h2));
       h2 = new TH2D("Bsumpart","PSA Wall-B;Total (ADC);Part (ADC)",xn,x1,x2,xn,x1,x2); free(make(h2));
  auto h1 = new TH1D("Asumovpart","Part/Sum Wall-A;ADC Total/Part",200,0.5,2);          free(make(h1));
       h1 = new TH1D("Bsumovpart","Part/Sum Wall-B;ADC Total/Part",200,0.5,2);          free(make(h1));

  auto cvs = cc(); chain -> Draw("AGeoMeanPart:AGeoMeanSum>>Asumpart","","colz"); cvs -> SetLogz();
       cvs = cc(); chain -> Draw("BGeoMeanPart:BGeoMeanSum>>Bsumpart","","colz"); cvs -> SetLogz();
       cvs = cc(); chain -> Draw("BGeoMeanPart/BGeoMeanSum>>Asumovpart","",""); cvs -> SetLogz();
       cvs = cc(); chain -> Draw("BGeoMeanPart/BGeoMeanSum>>Asumovpart","",""); cvs -> SetLogz();
       */
}

/*
*********************************
Trig_num  : Trig_num/l           
  5540395 : Total  Size=   443308
       74 : Basket Size=    25446
.................................
Trig_ttime : Trig_ttime/l        
  5540395 : Total  Size=   443310
       74 : Basket Size=    25446
.................................
nWAVE     : nWAVE/I              
  5540395 : Total  Size=   221671
       54 : Basket Size=    19056
.................................
Channel   : Channel[nWAVE]/s     
  5540395 : Total  Size=   252475
       77 : Basket Size=    19962
.................................
WAVE      : WAVE[nWAVE][240]/s   
  5540395 : Total  Size=  7607975
      744 : Basket Size=   256000
.................................
nSPWAVE   : nSPWAVE/I            
  5540395 : Total  Size=   221672
       54 : Basket Size=    19056
.................................
SPChannel : SPChannel[nSPWAVE]/s 
  5540395 : Total  Size=   307717
       82 : Basket Size=    21565
.................................
SPWAVE    : SPWAVE[nSPWAVE][240]/
5540395 : Total  Size= 2086570035
     2002 : Basket Size=   256000
.................................
SPWAVETime : SPWAVETime[nSPWAVE]/
  5540395 : Total  Size=   565768
      105 : Basket Size=    29040
.................................
NA        : NA/I                 
  5540395 : Total  Size=   221669
       54 : Basket Size=    19056
.................................
AID       : AID[NA]/I            
  5540395 : Total  Size=   228011
       75 : Basket Size=    19261
.................................
AGeoMeanSum : AGeoMeanSum[NA]/D  
  5540395 : Total  Size=   234333
       75 : Basket Size=    19450
.................................
AGeoMeanPart : AGeoMeanPart[NA]/D
  5540395 : Total  Size=   234334
       75 : Basket Size=    19450
.................................
AMeanTime : AMeanTime[NA]/D      
  5540395 : Total  Size=   234331
       75 : Basket Size=    19450
.................................
ASubTime  : ASubTime[NA]/D       
  5540395 : Total  Size=   234331
       75 : Basket Size=    19450
.................................
AModSum   : AModSum[NA][2]/D     
  5540395 : Total  Size=   246961
       76 : Basket Size=    19824
.................................
AModPart  : AModPart[NA][2]/D    
  5540395 : Total  Size=   246963
       77 : Basket Size=    19829
.................................
AModTime  : AModTime[NA][2]/D    
  5540395 : Total  Size=   246963
       77 : Basket Size=    19829
.................................
AModPeak  : AModPeak[NA][2]/D    
  5540395 : Total  Size=   246963
       77 : Basket Size=    19829
.................................
AModPed   : AModPed[NA][2]/D     
  5540395 : Total  Size=   246961
       76 : Basket Size=    19824
.................................
AModCH    : AModCH[NA][2]/I      
  5540395 : Total  Size=   234329
       75 : Basket Size=    19450
.................................
NB        : NB/I                 
  5540395 : Total  Size=   221669
       54 : Basket Size=    19056
.................................
BID       : BID[NB]/I            
  5540395 : Total  Size=   222600
       74 : Basket Size=    19097
.................................
BGeoMeanSum : BGeoMeanSum[NB]/D  
  5540395 : Total  Size=   223512
       74 : Basket Size=    19128
.................................
BGeoMeanPart : BGeoMeanPart[NB]/D
  5540395 : Total  Size=   223513
       74 : Basket Size=    19128
.................................
BMeanTime : BMeanTime[NB]/D      
  5540395 : Total  Size=   223511
       74 : Basket Size=    19128
.................................
BSubTime  : BSubTime[NB]/D       
  5540395 : Total  Size=   223510
       74 : Basket Size=    19128
.................................
BModSum   : BModSum[NB][2]/D     
  5540395 : Total  Size=   225320
       74 : Basket Size=    19179
.................................
BModPart  : BModPart[NB][2]/D    
  5540395 : Total  Size=   225322
       75 : Basket Size=    19179
.................................
BModTime  : BModTime[NB][2]/D    
  5540395 : Total  Size=   225322
       75 : Basket Size=    19179
.................................
BModPeak  : BModPeak[NB][2]/D    
  5540395 : Total  Size=   225322
       75 : Basket Size=    19179
.................................
BModPed   : BModPed[NB][2]/D     
  5540395 : Total  Size=   225320
       74 : Basket Size=    19179
.................................
BModCH    : BModCH[NA][2]/I      
  5540395 : Total  Size=   234329
       75 : Basket Size=    19450
*/
