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
        // get the target volume and backsurface position on first call
        const auto detConstruction = static_cast<const DetectorConstruction*>(
            G4RunManager::GetRunManager()->GetUserDetectorConstruction());
            fBremsVolume = detConstruction->GetBremsVolume();
            fTargetBackZ = detConstruction->GetTargetBackZ();
    }

    // Check if there are secondaries generated in this step
    G4LogicalVolume* currentVolume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    if (currentVolume != fBremsVolume) { return; }

    G4int absNTupleID = 0;
    
    G4int nSecondaryParticle = step->GetNumberOfSecondariesInCurrentStep();
    if (nSecondaryParticle == 0) { return; }

    G4double electronEnergy = step->GetPreStepPoint()->GetKineticEnergy();
    const std::vector<const G4Track*>* secondaries = step->GetSecondaryInCurrentStep();

    // for (G4int i=0; i<secondaries->size();i++) {
    //     const G4Track* track = (*secondaries)[i];
    //     G4ThreeVector prePoint = step->GetPreStepPoint()->GetPosition();
    //     G4ThreeVector postPoint = step->GetPostStepPoint()->GetPosition();
    //     G4ThreeVector momentumDir = track->GetMomentumDirection();

    //     //only record secondaries that are exit from the back (positive z-direction)
    //     if(postPoint.z()>=fTargetBackZ && momentumDir.z() > 0) {
    //         G4String particleName = track->GetParticleDefinition()->GetParticleName();
    //         G4double energy = track->GetKineticEnergy();
    //         auto analysisManager = G4AnalysisManager::Instance();

    //         if (particleName == "gamma") {
    //             analysisManager->FillH1(1,energy);
    //         }

    //         if (particleName == "e-") {
    //             analysisManager->FillH1(2,energy);
    //         }
    //     }

        // G4String particleName = track->GetParticleDefinition()->GetParticleName();
        // if (particleName == "gamma") {
        //     G4double energy = track->GetKineticEnergy();
        //     auto analysisManager = G4AnalysisManager::Instance();
        //     analysisManager->FillNtupleDColumn(absNTupleID,0,energy);
        //     analysisManager->AddNtupleRow(absNTupleID);
        //     analysisManager->FillH1(1,energy);
        // }

        // if (particleName == "e-") {
        //     G4double energy = track->GetKineticEnergy();
        //     auto analysisManager = G4AnalysisManager::Instance();
        //     analysisManager->FillH1(2,energy);
        // }
    // }
}