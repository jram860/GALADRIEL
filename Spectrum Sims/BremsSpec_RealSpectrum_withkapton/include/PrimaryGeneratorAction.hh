#ifndef PrimaryGenerator_h
#define PrimaryGenerator_h

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
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
        // G4ParticleGun* fParticleGun; // using the particle gun
        G4GeneralParticleSource* fParticleGun = nullptr;
};
#endif