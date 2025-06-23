void plotHisto() {
    gROOT->Reset();

  
  // Draw histos filled by Geant4 simulation 
  //   
  ///TFile f("hadr05.root");
  TFile *f = TFile::Open("EnergySpectrum.root");
  TCanvas* c1 = new TCanvas("canvas", "Energy Deposition Profiles", 800, 600);
  //c1->Divide(2,1);

  //TH1D* hist1 = (TH1D*)f->Get("sourceESpectrum");
  TH1D* hist2 = (TH1D*)f->Get("photonESpectrum");
  //c1->cd(1);
  //hist1->Draw("HIST");
  //c1->cd(2);
  hist2->Draw("HIST");
  // c1->cd(2);
  // hist2->Draw("HIST");
  //hist1->Print("all");
}
