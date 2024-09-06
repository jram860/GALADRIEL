#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Timer.hh"
#include "globals.hh"
#include <vector>

class Run;
class EventAction;
class DetectorConstruction;
class PrimaryGeneratorAction;

class RunAction : public G4UserRunAction
{
public:
    RunAction(DetectorConstruction* det, PrimaryGeneratorAction* prim=0);
    virtual ~RunAction();
    
    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
    
    void AddEnergyDeposition(G4double energy, G4int detectorIndex);
    const std::vector<G4double>& GetEnergyDeposited() const;
    
private:
    DetectorConstruction* fDetector;
    PrimaryGeneratorAction* fPrimary;
    Run* fRun;

    G4Timer fTimer;
    void PrintTime();
};

#endif // RUNACTION_HH
