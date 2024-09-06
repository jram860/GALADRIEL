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

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
    G4int NoDetectors = fDetector->GetNbOfDetectors();
    // keep run condition
    if ( fPrimary ) { 
        G4ParticleDefinition* particle 
        = fPrimary->GetParticleGun()->GetParticleDefinition();
        G4double energy = fPrimary->GetParticleGun()->GetParticleEnergy();
        fRun->SetPrimary(particle, energy);

        fTimer.Start(); // begin timer
    }

    fTimer.Start(); // Start time
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{
    fTimer.Stop();
    if (isMaster) {
            fRun->EndOfRun(aRun);
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