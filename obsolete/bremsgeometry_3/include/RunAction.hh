#ifndef RUNACTION_HH
#define RUNACTION_HH

#include <G4UserRunAction.hh>
#include <vector>

class RunAction : public G4UserRunAction {
public:
    RunAction();
    virtual ~RunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

    void AddDose(G4int detectorID, G4double dose);
    const std::vector<G4double>& GetDoses() const;

private:
    std::vector<G4double> fTotalDoses;
};

#endif
