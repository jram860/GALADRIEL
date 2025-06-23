#include "Run.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

#include"G4ParticleDefinition.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

#include <iomanip>

Run::Run(DetectorConstruction* det): G4Run(),
    fDetector(det),
    fParticle(0), 
    energyDepositionDetector(0.),
    kDet(0)
{
    kDet = fDetector->GetNbOfDetectors();
    energyDepositionDetector.resize(kDet);
    std::fill(energyDepositionDetector.begin(),energyDepositionDetector.end(),0.0);
    fEnergyDetectorTot=0.;
}

Run::~Run() {}

// void Run::SetPrimary(G4ParticleDefinition* particle, G4double energy)
// {
//     fParticle = particle;
    // fEkin = energy;
// }

void Run::SumEvents(G4int iDetector, G4double Edet)
{
    energyDepositionDetector[iDetector] += Edet;
}

void Run::SumEvents2(G4double etot)
{
    fEnergyDetectorTot+=etot;
}

void Run::Merge(const G4Run* run)
{
    const Run* localRun = static_cast<const Run*>(run);

    // pass information about the primary particle
    // fParticle = localRun->fParticle;
    fEkin = localRun->fEkin;

    // accumulate the sums

    for (G4int k=0; k<kDet; k++){
        energyDepositionDetector[k] += localRun->energyDepositionDetector[k];
    }

    fEnergyDetectorTot += localRun->fEnergyDetectorTot;

    G4Run::Merge(run);
}

void Run::EndOfRun(const G4Run *run)
{
    // G4String partName = fParticle->GetParticleName();
    // G4int nbEvent = numberOfEvent;

    // G4int prec = G4cout.precision(3);

    // G4cout << "The run was " << nbEvent << " " << partName << " of "
    //        << G4BestUnit(fEkin,"Energy") << " through the detector stack" << G4endl;
    // G4cout << "-----------------------------------------------------"
    //         << G4endl;
    // if (nbEvent == 0) return;

    std::ios::fmtflags mode = G4cout.flags();
    G4cout << "Total energy deposited in: " << G4endl;

    for (G4int im = 0; im<kDet; im++){
        G4cout
            << "\n   Detector " << im << ": "
            << std::setprecision(5)
            << std::setw(6) << G4BestUnit(energyDepositionDetector[im],"Energy");
    }
    G4cout << G4endl;
    G4cout
            << "\n total Fiter Stack: "
            << std::setprecision(5)
            << std::setw(6) << G4BestUnit(fEnergyDetectorTot,"Energy"); 
    G4cout  << "\n-----------------------------------------------------"
            << G4endl;


    // output text file
    G4cout << std::string(80,'-') << G4endl;
    if (run->GetRunID()==0){
        std::ofstream outFile("energy_deposition.txt");
        outFile << std::string(80,'#') << G4endl;
        outFile << "### Normalized dose (MeV) per detector over a range of monoenergetic beams.\n"
                << std::string(80,'#')
                << "\n";
        outFile << "Run_No " << "E_init " << "E_tot ";
        for (G4int k=0; k<kDet; k++) {
            outFile << "Detector_" << k << " "; 
        }
        outFile <<"\n";
        outFile << run->GetRunID() << " " << fEkin << " " << std::setprecision(5)<< fEnergyDetectorTot << " ";
        for (G4int k=0; k<kDet; k++){
            outFile << std::setprecision(5) << energyDepositionDetector[k]/MeV << " ";
        }
        outFile << "\n";
    } else {
        std::ofstream outFile("energy_deposition.txt", std::ios::app);
            outFile << run->GetRunID() << " " << fEkin << " " << fEnergyDetectorTot/MeV << " ";
            for (G4int k=0; k<kDet; k++){
                outFile << energyDepositionDetector[k]/MeV << " ";
            }
            outFile << "\n";
            outFile.close();
    }
}