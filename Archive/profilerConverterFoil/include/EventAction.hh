#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "RunAction.hh"
#include "G4Event.hh"
#include "DetectorConstruction.hh"
#include <vector>

class PrimaryGeneratorAction;

class EventAction : public G4UserEventAction
{
public:
    EventAction(DetectorConstruction*);
    virtual ~EventAction();
    
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);
    
    void AddEnergyDeposition(G4int,G4double);
    void AddEnergyProfile(G4int,G4double,G4double);
    
private:
    DetectorConstruction* detector;
    PrimaryGeneratorAction* primary;

    G4int NbOfDetectors;
    G4int kLayer;
    std::vector<G4double> fEnergyDepositedDetector;

    G4double fEnergyDepositedTot;
};

#endif // EVENTACTION_HH
