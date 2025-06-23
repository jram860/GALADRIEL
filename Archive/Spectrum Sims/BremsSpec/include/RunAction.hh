#ifndef RunAction_h
#define RunAction_h

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Timer.hh"

class HitsCollection;

class RunAction : public G4UserRunAction
{
    public:
        RunAction();
        ~RunAction();

        void BeginOfRunAction(const G4Run* aRun) override;
        void EndOfRunAction(const G4Run* aRun) override;
    
    private:
        G4Timer fTimer;
        void PrintTime();
};
#endif