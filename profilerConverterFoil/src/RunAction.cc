#include "RunAction.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "Run.hh"


#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

#include <iomanip>

RunAction::RunAction(DetectorConstruction* det, PrimaryGeneratorAction*kin)
:G4UserRunAction(),fDetector(det),fPrimary(kin),fRun(nullptr)
{}

RunAction::~RunAction()
{}

G4Run*RunAction::GenerateRun()
{
    fRun = new Run(fDetector);
    return fRun;
}

void RunAction::BeginOfRunAction(const G4Run*)
{
    auto analysisManager = G4AnalysisManager::Instance();

    //Default Settings
    analysisManager->SetDefaultFileType("root");
    analysisManager->SetVerboseLevel(0);
    analysisManager->SetFileName("deposition_profiles");

    G4int NoDetectors = fDetector->GetNbOfDetectors();
    //set up h1's
    for (G4int i = 0; i < NoDetectors; i++)
    {
        G4cout << "Creating histogram for detector " << i << G4endl;
        analysisManager->CreateH1("Detector_" + std::to_string(i), "Energy deposition in detector " + std::to_string(i), 200, -25*mm, 25*mm);
        analysisManager->SetH1XAxisTitle(i, "Location (mm)");
		analysisManager->SetH1YAxisTitle(i, "Dose (keV)");

        //analysisManager->SetH1Activation(i, false);
    }

   //analysisManager->SetActivation(true);

    //auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile();
    // keep run condition
    // if ( fPrimary ) { 
    //     G4ParticleDefinition* particle 
    //     = fPrimary->GetParticleGun()->GetParticleDefinition();
    //     G4double energy = fPrimary->GetParticleGun()->GetParticleEnergy();
    //     fRun->SetPrimary(particle, energy);

    //     fTimer.Start(); // begin timer
    // }

    fTimer.Start(); // Start time
}

void RunAction::EndOfRunAction(const G4Run*)
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
    fTimer.Stop();
    if (isMaster) {
            fRun->EndOfRun();
            PrintTime();
        }
}

void RunAction::PrintTime()
{
    auto time = fTimer.GetRealElapsed();

    G4cout << "Elapsed Simulation Time: "
           << time
           << " Seconds."
           << G4endl;
}