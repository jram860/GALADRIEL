#include "EventAction.hh"
#include "RunAction.hh"
#include <G4Event.hh>
#include <G4RunManager.hh>

EventAction::EventAction() : G4UserEventAction(), fDoses(2, 0.0) {}
EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event*) {
    std::fill(fDoses.begin(), fDoses.end(), 0.0);
}

void EventAction::EndOfEventAction(const G4Event*) {
    auto runAction = dynamic_cast<RunAction*>(G4RunManager::GetRunManager()->GetUserRunAction());
    for (size_t i = 0; i < fDoses.size(); ++i) {
        runAction->AddDose(i, fDoses[i]);
    }
}

void EventAction::AddDose(G4int detectorID, G4double dose) {
    fDoses[detectorID] += dose;
}