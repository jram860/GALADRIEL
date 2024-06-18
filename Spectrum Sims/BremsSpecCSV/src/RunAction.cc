#include "RunAction.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

RunAction::RunAction()
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetDefaultFileType("csv");
    analysisManager->SetNtupleMerging(true);
    analysisManager->SetVerboseLevel(0);
    analysisManager->SetFileName("EnergySpectrum");

    analysisManager->CreateH1("photonESpectrum", "Bremsstrahlung Energy Spectrum", 200, 0, 1 * MeV);
	analysisManager->SetH1XAxisTitle(0, "Energy (MeV)");
	analysisManager->SetH1YAxisTitle(0, "Number of particles");
}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile();
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();

}
