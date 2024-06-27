// void plotHisto() {
//     gROOT->Reset();

  
//   // Draw histos filled by Geant4 simulation 
//   //   
//   ///TFile f("hadr05.root");
//   TFile f("deposition_profiles.root");
//   TCanvas* c1 = new TCanvas("c1", "  ");
//   TH1D* hist1 = (TH1D*)f.Get("Detector_1");
//   hist1->Draw("HIST");
//   //hist1->Print("all");
// }


void plotHisto() {
    // Open the ROOT file
    TFile *file = TFile::Open("deposition_profiles.root");

    // Create a canvas
    TCanvas *canvas = new TCanvas("canvas", "Energy Deposition Profiles", 800, 600);
    canvas->Divide(2, 2); // Adjust division as per number of detectors

    // Read the histograms and draw them
    std::vector<TH1F*> histograms;
    for (int i = 0; i < 2; ++i) { // Adjust the loop as per number of detectors
        // Get the histogram
        histograms.push_back((TH1F*)file->Get(("Detector_" + std::to_string(i)).c_str()));

        // Draw the histogram
        canvas->cd(i + 1);
        histograms[i]->Draw("HIST");
    }

    // canvas->SaveAs("energy_deposition_profiles.pdf");
    // delete canvas;
    // file->Close();
}