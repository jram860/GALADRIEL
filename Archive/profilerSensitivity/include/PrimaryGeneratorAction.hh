#ifndef PrimaryGenerator_hh
#define PrimaryGenerator_hh

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
    public:
        PrimaryGeneratorAction();
        ~PrimaryGeneratorAction();

        virtual void GeneratePrimaries(G4Event*);
        const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
        G4ParticleGun* fParticleGun;
};

#endif