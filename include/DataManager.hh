#ifndef DataManager_h
#define DataManager_h 1

#include "G4UnitsTable.hh"
#include "globals.hh"
#include "Settings.hh"
#include "WASABI.hh"

class DataManager;

#include <TROOT.h>
#include <TObject.h>
#include <TFile.h>
#include <TTree.h>


class DataManager{
public:
  DataManager();
  DataManager(const char* filename, int nevents);
  ~DataManager();
  void Init(const char* filename);
  void SetSim(double e, double z);
  void FillTree(WASABI* wasabi, double *en, double etot);
  void Clear(const Option_t* option="");
  void Close();
  int GetNevents(){return fnevents;};

private:
  int fnevents;
  double fesim;
  double fzsim;
  double fedet[NDET];
  double fetot;
  WASABI *fwasabi;
  TTree* ftree;
  TFile* ffile;
};

#endif

