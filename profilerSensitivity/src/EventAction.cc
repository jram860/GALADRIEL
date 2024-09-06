#include "EventAction.hh"
#include "Run.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"

#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

EventAction::EventAction(DetectorConstruction* det)
:detector(det)
{}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event* event)
{
   NbOfDetectors = detector->GetNbOfDetectors();
   fEnergyDepositedTot = 0.;
   fEnergyDepositedDetector.resize(NbOfDetectors); 
    // Initialize energy deposition for this event
    std::fill(fEnergyDepositedDetector.begin(), fEnergyDepositedDetector.end(), 0.0);
}

void EventAction::EndOfEventAction(const G4Event* event)
{
    Run* run = static_cast<Run*>(
        G4RunManager::GetRunManager()->GetNonConstCurrentRun()
    );

    for (G4int k=0; k<NbOfDetectors; k++) {
        run->SumEvents(k,fEnergyDepositedDetector[k]);
    }

    run->SumEvents2(fEnergyDepositedTot);
}

void EventAction::AddEnergyDeposition(G4int detectorIndex, G4double edep)
{
    if (detectorIndex < NbOfDetectors)
    {
        fEnergyDepositedDetector[detectorIndex] += edep;
        fEnergyDepositedTot +=edep;
    }
}