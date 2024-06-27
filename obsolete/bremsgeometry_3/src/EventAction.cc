#include "EventAction.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"

EventAction::EventAction()
 : G4UserEventAction(),
   fEnergyDepositMap(new std::map<std::string, G4double>())
{ }

EventAction::~EventAction()
{
    delete fEnergyDepositMap;
}

void EventAction::BeginOfEventAction(const G4Event*)
{
    fEnergyDepositMap->clear();
}

void EventAction::EndOfEventAction(const G4Event*)
{
    // At the end of the event, we can perform any final processing
}

std::map<std::string, G4double>* EventAction::GetEnergyDepositMap()
{
    return fEnergyDepositMap;
}





