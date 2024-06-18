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
:G4UserRunAction(),fDetector(det),fPrimary(kin),fRun(0)
{
    auto analysisManager = G4AnalysisManager::Instance();

    //default settings
    analysisManager->SetDefaultFileType("root");
    analysisManager->SetVerboseLevel(0);
    analysisManager->SetFileName("outputFigures");

    // Set up  1d histogram

    //analysisManager->CreateH1("LayerEdep", "Edep Per Layer", 6)

    // G4String title;
    // G4int NbOfLayers = fDetector->GetNbOfLayers();
    // analysisManager->CreateH1("EdepTot", "Total Edep in Stack",100,0,100);
    // analysisManager->CreateH1("EdepProf", "Energy Deposition Profile", NbOfLayers,0,100);
    
    // for (G4int k=1;k< NbOfLayers;k++) {
    //     title = "Face On Spatial Edep profile in Detector" + k;
    //     analysisManager->CreateH2("HeatMapXY",title,200,-10*cm,10*cm,200,-10*cm,10*cm);
    // }

    // analysisManager->CreateH2("HeatMapYZ","Side-On Edep Spatial Distribution",200,-10*cm,10*cm,200,-10*cm,10*cm);
}

RunAction::~RunAction()
{}

G4Run*RunAction::GenerateRun()
{
    fRun = new Run(fDetector);
    return fRun;
}

void RunAction::BeginOfRunAction(const G4Run*)
{
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

void RunAction::EndOfRunAction(const G4Run*)
{
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