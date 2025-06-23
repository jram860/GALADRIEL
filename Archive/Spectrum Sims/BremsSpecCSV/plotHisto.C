{
    gROOT->Reset();
  
  // Draw histos filled by Geant4 simulation 
  //   
  ///TFile f("hadr05.root");
  TFile f("EnergySpectrum.root");
  TCanvas* c1 = new TCanvas("c1", "  ");
  TH1D* hist1 = (TH1D*)f.Get("photonESpectrum");
  hist1->Draw("HIST");
  hist1->Print("all");
}