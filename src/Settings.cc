#include "Settings.hh"

using namespace std;

Settings::Settings(){
  cout << "not filename " << endl;
}
Settings::Settings(const char* filename){
  SetFile( filename );
  ReadSettings();
  if(fVerboseLevel>1)
    PrintSettings();
}
Settings::~Settings(){
  cout << "destructor" << endl;
}
void Settings::ReadSettings(){
  //char* defaultfile = (char*)"~/analysis/settings/nocal.dat";

  TEnv *set = new TEnv(fInputFile.data()); 
  fVerboseLevel = set->GetValue("VerboseLevel",0);

  fElectronEnergy = set->GetValue("Electron.Energy",1000.);
  fElectronDirection = set->GetValue("Electron.Direction",0);
  fElectronTheta = set->GetValue("Electron.Direction.Theta",0.);
  fElectronPhi = set->GetValue("Electron.Direction.Phi",0.);
  
  fPosX = set->GetValue("Source.Position.X",0.0);
  fPosY = set->GetValue("Source.Position.Y",0.0);
  fPosZ = set->GetValue("Source.Position.Z",-10.0);

  for(int i=0;i<NDET;i++){
    fDetR[i] = set->GetValue(Form("Detector.%d.Resulution",i),12.0);
    fDetP[i] = set->GetValue(Form("Detector.%d.Position"  ,i),0.0);
    fDetZ[i]    = set->GetValue(Form("Detector.%d.Depth"  ,i),1.0);
    fDetY[i]    = set->GetValue(Form("Detector.%d.Height" ,i),40.0);
    fDetX[i]    = set->GetValue(Form("Detector.%d.Width"  ,i),60.0);
  }
}
void Settings::PrintSettings(){
  cout << "VerboseLevel\t" << fVerboseLevel << endl;
  
  cout << "Electron.Energy\t" << fElectronEnergy << endl;
  cout << "Electron.Direction\t" << fElectronDirection << endl;
  cout << "Electron.Direction.Theta\t" << fElectronTheta << endl;
  cout << "Electron.Direction.Phi\t" << fElectronPhi << endl;
  
  cout << "Source.Position.X\t" << fPosX << endl; 
  cout << "Source.Position.Y\t" << fPosY << endl; 
  cout << "Source.Position.Z\t" << fPosZ << endl; 
  for(int i=0;i<NDET;i++){
    cout << "Detector."<< i <<".Resolution\t" << fDetR[i] << endl; 
    cout << "Detector."<< i <<".Position\t"   << fDetP[i] << endl; 
    cout << "Detector."<< i <<".Depth\t"      << fDetZ[i] << endl;
    cout << "Detector."<< i <<".Height\t"     << fDetY[i] << endl;
    cout << "Detector."<< i <<".Width\t"      << fDetX[i] << endl;
  }
  
}
