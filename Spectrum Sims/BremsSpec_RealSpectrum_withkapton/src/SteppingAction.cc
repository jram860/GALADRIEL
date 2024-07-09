#include "SteppingAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"

#include "G4UnitsTable.hh"

#include "DetectorConstruction.hh"

SteppingAction::SteppingAction()
{}
SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step) {

    if(!fBremsVolume) {
        const auto detConstruction = static_cast<const DetectorConstruction*>(
            G4RunManager::GetRunManager()->GetUserDetectorConstruction());
            fBremsVolume = detConstruction->GetBremsVolume();
    }

    G4LogicalVolume* currentVolume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

    if (currentVolume != fBremsVolume) { return; }

    G4int absNTupleID = 0;
    
    G4int nSecondaryParticle = step->GetNumberOfSecondariesInCurrentStep();
    if (nSecondaryParticle == 0) { return; }

    G4double electronEnergy = step->GetPreStepPoint()->GetKineticEnergy();
    const std::vector<const G4Track*>* secondaries = step->GetSecondaryInCurrentStep();

    for (G4int i=0; i<secondaries->size();i++) {
        const G4Track* track = (*secondaries)[i];

        G4String particleName = track->GetParticleDefinition()->GetParticleName();
        if (particleName == "gamma") {
            G4double energy = track->GetKineticEnergy();
            auto analysisManager = G4AnalysisManager::Instance();
            analysisManager->FillNtupleDColumn(absNTupleID,0,energy);
            analysisManager->AddNtupleRow(absNTupleID);
            analysisManager->FillH1(1,energy);
        }
    }
}