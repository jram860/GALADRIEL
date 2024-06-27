#ifndef RunAction_hh
#define RunAction_hh

#include "G4UserRunAction.hh"
#include "globals.hh"


class Run;
class EventAction;
class DetectorConstruction;
class PrimaryGeneratorAction;

class RunAction : public G4UserRunAction
{
    public:
        RunAction(DetectorConstruction* det, PrimaryGeneratorAction* prim=0);
        ~RunAction();
        
        virtual G4Run* GenerateRun();
        virtual void BeginOfRunAction(const G4Run*);
        virtual void   EndOfRunAction(const G4Run*);

    private:
        DetectorConstruction* fDetector;
        PrimaryGeneratorAction* fPrimary;
        Run* fRun;

};

#endif