#include "EventAction.hh"
#include "Run.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"



EventAction::EventAction(DetectorConstruction* det) : detector(det)
{
    NbOfLayers = (detector->GetNbOfLayers()); //just for counter, change later.
    EdetTot = 0.;
}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* anEvent)
{
    EdetMod.resize(NbOfLayers);
    for (G4int k=1; k<=NbOfLayers;k++){
        EdetMod[k] = 0.;
    }
}

void EventAction::AddEdep(G4int iLayer, G4double edep)
{
    if (iLayer >=1){
        EdetTot += edep;
        EdetMod[iLayer] += edep;
    }
}

void EventAction::EndOfEventAction(const G4Event*)
{
    Run* run = static_cast<Run*>(
        G4RunManager::GetRunManager()->GetNonConstCurrentRun()
    );

    for (G4int k=1; k<=NbOfLayers;k++) {
        run->SumEvents(k,EdetMod[k]);
    }

    run->SumEvents2(EdetTot);
}
