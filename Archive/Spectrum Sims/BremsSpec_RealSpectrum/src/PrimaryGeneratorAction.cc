#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4UnitsTable.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    //G4int nParticles = 1;
    //fParticleGun = new G4ParticleGun(nParticles);
    fParticleGun = new G4GeneralParticleSource();
    const G4String& particleName = "e-";

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle(particleName);

    fParticleGun->SetParticleDefinition(particle);
    G4ThreeVector momentumDir = G4ThreeVector(0,0,1);
    // if using particle gun -> // fParticleGun->SetParticleMomentumDirection(momentumDir);

    G4double energy = 1*MeV;
    // if using particle gun -> // fParticleGun->SetParticleEnergy(energy);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    G4ThreeVector position = G4ThreeVector(0,0,-5* cm);
    fParticleGun->SetParticlePosition(position);
    fParticleGun->GeneratePrimaryVertex(event);
    G4double energy = fParticleGun->GetParticleEnergy();
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillH1(0,energy);

}