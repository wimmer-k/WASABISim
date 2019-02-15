#ifndef Settings_h
#define Settings_h 1

#include <iostream>
#include <fstream>
#include <string>

class Settings;
#include "TSystem.h"
#include "TEnv.h"
#include "TObject.h"
#include "TMath.h"
using namespace std;

#define deg2rad TMath::Pi()/180.
#define rad2deg 180./TMath::Pi()
#define NDET 3
#define NXSTRIPS 60
#define NYSTRIPS 40

class Settings{
public:
  Settings();//default ctor
  Settings(const char*);
  ~Settings();

  void ReadSettings();
  void PrintSettings();
  void SetFile(const char* filename){fInputFile = filename;}
  const string InputFile(){return fInputFile;}

  int VLevel(){return fVerboseLevel;}
 
  double ElectronEnergy(){return fElectronEnergy;}
  int ElectronDirection(){return fElectronDirection;}
  double ElectronDirectionTheta(){return fElectronTheta;}
  double ElectronDirectionPhi(){return fElectronPhi;}

  double SourcePositionX(){return fPosX;} 
  double SourcePositionY(){return fPosY;} 
  double SourcePositionZ(){return fPosZ;} 

  double DetectorResolution(int d){return fDetR[d];} 
  double DetectorPosition(int d){return fDetP[d];} 
  double DetectorDepth(int d){return fDetZ[d];}
  double DetectorHeight(int d){return fDetY[d];}
  double DetectorWidth(int d){return fDetX[d];}

protected:
  int fVerboseLevel;
  string fInputFile;
  double fElectronEnergy;
  int fElectronDirection;
  double fElectronTheta;
  double fElectronPhi;
  double fPosX;
  double fPosY;
  double fPosZ;
  double fDetR[NDET];
  double fDetP[NDET];
  double fDetZ[NDET];
  double fDetY[NDET];
  double fDetX[NDET];

};
#endif
