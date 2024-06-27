#include "EventAction.hh"
#include "Run.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"



EventAction::EventAction(DetectorConstruction* det, PrimaryGeneratorAction* prim)
:detector(det), primary(prim)
{
    NbOfModules = (detector->GetNbOfModules());
    kMod = NbOfModules +1;
    EdetTot = 0.;
}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* anEvent)
{
    EdetMod.resize(kMod);
    for (G4int k=0; k<kMod;k++){
        EdetMod[k] = 0.;
    }
}

void EventAction::AddEdep(G4int iModule, G4double edep)
{
    if (iModule >0){
        EdetTot += edep;
        EdetMod[iModule] += edep;
    }
}

void EventAction::EndOfEventAction(const G4Event*)
{
    Run* run = static_cast<Run*>(
        G4RunManager::GetRunManager()->GetNonConstCurrentRun()
    );

    for (G4int k=0; k<kMod;k++) {
        run->SumEvents(k,EdetMod[k]);
    }

    run->SumEvents2(EdetTot);
}
