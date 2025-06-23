#include "SensitiveDetector.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

SensitiveDetector::SensitiveDetector(const G4String& name) : G4VSensitiveDetector(name) {}

G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
    if (step->IsFirstStepInVolume()) {
        G4Track* track = step->GetTrack();
        G4String particleName = track->GetParticleDefinition()->GetParticleName();
        G4double energy = track->GetKineticEnergy();

        auto analysisManager = G4AnalysisManager::Instance();
        if (particleName == "gamma") {
            analysisManager->FillH1(1,energy/MeV);
        }
        if (particleName == "e-") {
            analysisManager->FillH1(2,energy/MeV);
        }
    }
    

    return true;
}