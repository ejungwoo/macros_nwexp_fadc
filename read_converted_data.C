void read_converted_data() 
{
  auto file = new TFile("/mnt/Data0/ConvData/RUN_110_fadc_4_conv.root","read");
  auto tree = (TTree *) file -> Get("Tree_0");
  FADC *channel = nullptr;
  tree -> SetBranchAddress("wave", &channel);

  tree -> GetEntry(0);
}
