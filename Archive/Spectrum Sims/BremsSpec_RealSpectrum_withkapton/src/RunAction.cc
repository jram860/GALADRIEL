#include "RunAction.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

RunAction::RunAction()
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetDefaultFileType("root");
    analysisManager->SetNtupleMerging(true);
    analysisManager->SetVerboseLevel(0);
    analysisManager->SetFileName("EnergySpectrum");

    // create nTuple to store the absolute energies
    const G4int ntupleId1 = analysisManager->CreateNtuple("Absolute Energies", "Gamma Energies");
    analysisManager->CreateNtupleDColumn(ntupleId1, "AbsEnergy"); //   id = 0
    analysisManager->FinishNtuple(ntupleId1);

    analysisManager->CreateH1("sourceESpectrum", "E Beam Energy Spectrum", 200, 0, 5 * MeV);
	analysisManager->SetH1XAxisTitle(0, "Energy (MeV)");
	analysisManager->SetH1YAxisTitle(0, "Number of particles");

    analysisManager->CreateH1("photonESpectrum", "Bremsstrahlung Energy Spectrum", 1000, 0, 5 * MeV);
	analysisManager->SetH1XAxisTitle(1, "Energy (MeV)");
	analysisManager->SetH1YAxisTitle(1, "Number of particles");
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
