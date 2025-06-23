#include <fstream>
#include <TFile.h>
#include <TH1.h>

void exportHisto(const char* rootFileName, const char* histName, const char* outputFileName) {
    // Open the .root file
    TFile file(rootFileName, "READ");
    if (!file.IsOpen()) {
        std::cerr << "Error opening file " << rootFileName << std::endl;
        return;
    }

    // Get the histogram by name
    TH1* hist = dynamic_cast<TH1*>(file.Get(histName));
    if (!hist) {
        std::cerr << "Histogram " << histName << " not found in file " << rootFileName << std::endl;
        return;
    }

    // Open output file
    std::ofstream outFile(outputFileName);
    if (!outFile.is_open()) {
        std::cerr << "Error opening output file " << outputFileName << std::endl;
        return;
    }

    // Write headers
    outFile << "BinCenter,BinContent\n";

    // Loop over histogram bins and write data to file
    for (int bin = 1; bin <= hist->GetNbinsX(); ++bin) {
        double binCenter = hist->GetBinCenter(bin);
        double binContent = hist->GetBinContent(bin);
        outFile << binCenter << "," << binContent << "\n";
    }

    // Close files
    outFile.close();
    file.Close();

    std::cout << "Data exported to " << outputFileName << std::endl;
}