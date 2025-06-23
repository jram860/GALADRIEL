#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4UnitsTable.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    //G4int nParticles = 1;
    //fParticleGun = new G4ParticleGun(nParticles);
    fParticleSource = new G4GeneralParticleSource();
    const G4String& particleName = "e-";

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle(particleName);

    fParticleSource->SetParticleDefinition(particle);
    fParticleSource->GetCurrentSource()->GetEneDist()->SetMonoEnergy(100*MeV);
    fParticleSource->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector(0.,0.,-10.*cm));
    fParticleSource->GetCurrentSource()->GetAngDist()->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleSource;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    fParticleSource->GeneratePrimaryVertex(event);
}