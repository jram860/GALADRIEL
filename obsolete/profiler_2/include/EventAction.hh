#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include <G4UserEventAction.hh>
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include <vector>

class EventAction : public G4UserEventAction {
public:
    EventAction();
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event* event) override;
    virtual void EndOfEventAction(const G4Event* event) override;

    void AddDose(G4int detectorID, G4double dose);

private:
    std::vector<G4double> fDoses;
};

#endif