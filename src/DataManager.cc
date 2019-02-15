#include "DataManager.hh"

using namespace std;
using namespace CLHEP;

DataManager::DataManager(){
  cout << "bla" << endl;
}
DataManager::DataManager(const char* filename, int nevents){
  fwasabi = new WASABI();
  fnevents = nevents;
  ffile = new TFile(filename,"RECREATE");
  ffile->cd();
  ftree = new TTree("tr","simulation data");
  ftree->Branch("esim",&fesim,"esim/D");
  ftree->Branch("zsim",&fzsim,"zsim/D");
  ftree->Branch("edet",&fedet,Form("edet[%d]/D",NDET));
  ftree->Branch("etot",&fetot,"etot/D");
  ftree->Branch("wasabi",&fwasabi,320000);
  ftree->BranchRef();
}
DataManager::~DataManager(){
  this->Close();
  delete ftree;
  delete ffile;
}
void DataManager::SetSim(double e, double z){
  fesim = e;
  fzsim = z;
}
void DataManager::FillTree(WASABI *wasabi, double* en, double etot){
  for(int i=0;i<NDET;i++)
    fedet[i] = en[i];
  fwasabi = (WASABI*)wasabi->Clone();
  fetot = etot;
  ftree->Fill();
  Clear();
}
void DataManager::Clear(const Option_t*){
  fesim = 0;
  fzsim = 0;
  for(int i=0;i<NDET;i++)
    fedet[i] = 0;
  fetot = 0;
  fwasabi->Clear();
}
void DataManager::Close(){
  ffile->cd();
  ftree->Write();
  ffile->Close();
}



