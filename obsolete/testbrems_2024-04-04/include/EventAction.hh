#ifndef EventAction_h
#define EventAction_h

#include "DetectorConstruction.hh"

#include "G4UserEventAction.hh"
#include "globals.hh"

#include <vector>


class EventAction : public G4UserEventAction
{
    public:
        EventAction(DetectorConstruction*);
        ~EventAction();

        void BeginOfEventAction(const G4Event* anEvent) override;
        void EndOfEventAction(const G4Event* anEvent) override;

        void AddEdep(G4int, G4double);
    
    private:
        DetectorConstruction* detector;

        G4int NbOfLayers;
        std::vector<G4double> EdetMod; // total energy deposition in each module's detector

        G4double EdetTot;
};

#endif