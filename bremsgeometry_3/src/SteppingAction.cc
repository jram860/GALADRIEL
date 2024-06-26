#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

SteppingAction::SteppingAction()
 : G4UserSteppingAction(),
   fEnergyDepositMap(new std::map<std::string, G4double>())
{ }

SteppingAction::~SteppingAction()
{
    delete fEnergyDepositMap;
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    G4String volumeName = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName();
    G4double edep = step->GetTotalEnergyDeposit();
    if (volumeName.contains("detector")) {
        (*fEnergyDepositMap)[volumeName] += edep;
    }
}

void SteppingAction::Report() const
{
    G4double totalEdep = 0;
    for (const auto& pair : *fEnergyDepositMap) {
        totalEdep += pair.second;
        G4cout << pair.first << ": " << pair.second/keV << " keV" << G4endl;
    }
    G4cout << "Total energy deposit: " << totalEdep/keV << " keV" << G4endl;
}