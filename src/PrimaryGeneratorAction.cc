#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Proton.hh"
#include "G4Deuteron.hh"
#include "G4Triton.hh"
#include "G4Alpha.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"

#include "Randomize.hh"

using namespace std;
using namespace CLHEP;

PrimaryGeneratorAction::PrimaryGeneratorAction(Settings* set, DataManager* data){
  // store the pointer to the data class locally, in order to be able to acess all information later
  fdata = data;
  fset = set;
  TFile *input = new TFile(fset->PosHistFile());
  fposdistribution = NULL;
  if(input->IsOpen())
    fposdistribution = (TH2F*)input->Get(fset->PosHistName());

  // in each event one gamma ray is emitted
  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

  // definition of the particle type
  particleGun->SetParticleDefinition(G4Electron::ElectronDefinition());

}
PrimaryGeneratorAction::~PrimaryGeneratorAction(){
  delete particleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
  //set position
  double x,y;
  int impdet = 0;
  if(fposdistribution){
    fposdistribution->GetRandom2(x,y);
    x = x/NXSTRIPS*fset->DetectorWidth(impdet)-fset->DetectorWidth(impdet)/2;
    y = y/NYSTRIPS*fset->DetectorHeight(impdet)-fset->DetectorHeight(impdet)/2;
  }
  else{
    x = fset->SourcePositionX()*mm;
    y = fset->SourcePositionY()*mm;
  }
  double z = fset->SourcePositionZ()*mm;
  if(fset->SourceWidthZ()>0)
    z+=RandGauss::shoot(0,fset->SourceWidthZ())*mm;

  particleGun->SetParticlePosition(G4ThreeVector(x,y,z));
  
  particleGun->SetParticleEnergy(fset->ElectronEnergy()*keV);
  fdata->SetSim(fset->ElectronEnergy(), TVector3(x,y,z));
  //----------set the particle direction
  // create a vector
  G4ThreeVector v(0.0,0.0,1.0);
  double theta = fset->ElectronDirectionTheta()*deg2rad;
  double phi = fset->ElectronDirectionPhi()*deg2rad;
  if(fset->ElectronDirection()!=2){
    // random cos(theta)  = -1..1
    theta = RandFlat::shoot(-1,1);
    // theta = random in 0..180 degree
    theta = acos(theta)*radian;
    // phi is random between -pi..pi = -180..180 degree
    phi = RandFlat::shoot(-M_PI, M_PI)*radian;
	
  }
  // set the vectors theta and phi. length doesn't matter only direction
  v.setTheta(theta);
  v.setPhi(phi);
  // set the particle gun in the direction
  particleGun->SetParticleMomentumDirection(v);
  particleGun->GeneratePrimaryVertex(anEvent);

}

