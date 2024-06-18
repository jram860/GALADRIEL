#include "Run.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4ParticleDefinition.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

#include <iomanip>

Run::Run(DetectorConstruction* det): G4Run(),
    fDetector(det), 
    fParticle(0),
    kMod(0),
    EdetTot(0.), Edet2Tot(0.)
{
    kMod = fDetector->GetNbOfLayers();
    kMod = kMod;

    EdetMod.resize(kMod); EdetMod2.resize(kMod);
    for (G4int k=0; k<=kMod;k++) {
        EdetMod[k] = EdetMod2[k] =0.;
    }

    EdetTot = Edet2Tot = 0.;
}

Run::~Run()
{}

void Run::SetPrimary(G4ParticleDefinition* particle, G4double energy)
{
    fParticle = particle;
    fEkin = energy;
}

void Run::SumEvents(G4int iLayer, G4double Edet)
{
    EdetMod[iLayer] += Edet; EdetMod2[iLayer] += Edet*Edet;
}

void Run::SumEvents2(G4double etot)
{
    EdetTot += etot; Edet2Tot +=etot*etot;
}

void Run::Merge(const G4Run* run)
{
    const Run* localRun = static_cast<const Run*>(run);

    //pass information about primary particle
    fParticle = localRun->fParticle;
    fEkin = localRun->fEkin;

    // accumulate the sums

    for (G4int k=1; k<=kMod;k++){
        EdetMod[k] += localRun->EdetMod[k];
        EdetMod2[k] += localRun->EdetMod2[k];
    }

    EdetTot += localRun->EdetTot;
    Edet2Tot += localRun->Edet2Tot;

    G4Run::Merge(run);
}

void Run::EndOfRun()
{
    //Print stack parameters
    // fDetector->PrintStackParameters();

    G4String partName = fParticle->GetParticleName();
    G4int nbEvents = numberOfEvent;

    G4int prec = G4cout.precision(3);

    G4cout << "The run was " << nbEvents << " " << partName << " of "
           << G4BestUnit(fEkin,"Energy") << " through the detector stack" << G4endl;

    G4cout << "----------------------------------------------------------------"
           << G4endl;

    if (nbEvents == 0) return;

    std::ios::fmtflags mode = G4cout.flags();

    G4cout << "\n           "
           << "Total Energy         (rms/mean)      " << G4endl;
    //G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    G4double meanEdetMod, meanEdetMod2, varianceEdetMod, rmsEdetMod, resEdetMod;
    G4double meanEdetTot, meanEdetTot2, varianceEdetTot, rmsEdetTot, resEdetTot;

    for (G4int im =1; im<=kMod;im++){
        meanEdetMod = EdetMod[im]/nbEvents;
        meanEdetMod2 = EdetMod2[im]/nbEvents;
        varianceEdetMod = meanEdetMod2-meanEdetMod*meanEdetMod;
        resEdetMod = rmsEdetMod = 0.;
        if (varianceEdetMod > 0.) rmsEdetMod = std::sqrt(varianceEdetMod);
        if (meanEdetMod > 0.) resEdetMod = 100*rmsEdetMod/meanEdetMod;
        //analysisManager->FillH1(0, im+0.5, meanEdetMod);

        //print
        G4cout
            << "\n   layer " << im << ": "
            << std::setprecision(5)
            << std::setw(6) << G4BestUnit(meanEdetMod,"Energy") << " +- "
            << std::setprecision(4)
            << std::setw(5) << G4BestUnit(rmsEdetMod,"Energy") << "  ("
            << std::setprecision(2)
            << std::setw(3) << resEdetMod << " %)";
    }
    G4cout << G4endl;

    // total energy in filter stack
    meanEdetTot = EdetTot/nbEvents;
    meanEdetTot2 = Edet2Tot/nbEvents;
    varianceEdetTot = meanEdetTot2 - meanEdetTot*meanEdetTot;
    resEdetTot = rmsEdetTot = 0.;
    if (varianceEdetTot > 0.) rmsEdetTot = std::sqrt(varianceEdetTot);
    if (meanEdetTot >0.) resEdetTot = 100*rmsEdetTot/meanEdetTot;

    G4cout
            << "\n total Fiter Stack: "
            << std::setprecision(5)
            << std::setw(6) << G4BestUnit(meanEdetTot,"Energy") << " +- "
            << std::setprecision(4)
            << std::setw(5) << G4BestUnit(rmsEdetTot,"Energy") << "  ("
            << std::setprecision(2)
            << std::setw(3) << resEdetTot << " %)";
    G4cout  << "\n----------------------------------------------------------------"
            << G4endl;



}