#ifndef Run_hh
#define Run_hh

#include "DetectorConstruction.hh"

#include "G4Run.hh"
#include "G4VProcess.hh"
#include "globals.hh"
#include <map>

class DetectorConstruction;
class G4ParticleDefinition;


class Run : public G4Run {
    public:
        Run(DetectorConstruction*);
        ~Run();

        void SetPrimary(G4ParticleDefinition* particle, G4double energy);
        void SumEvents(G4int, G4double);
        void SumEvents2(G4double);

        virtual void Merge(const G4Run*);
        void EndOfRun(const G4Run* run);

    private:
        DetectorConstruction* fDetector = nullptr;
        G4ParticleDefinition* fParticle = nullptr;
        G4double fEkin;

        G4int NbOfDetectors;
        G4int kDet;
        std::vector<G4double> energyDepositionDetector;
        G4double fEnergyDetectorTot;
};

#endif