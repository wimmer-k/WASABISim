#include "DetectorConstruction.hh"

using namespace std;

DetectorConstruction::DetectorConstruction(){
}

DetectorConstruction::~DetectorConstruction(){
}

G4VPhysicalVolume* DetectorConstruction::Construct(){

  //------------------------------------------------------ materials

  G4NistManager* NistManager = G4NistManager::Instance();

  //creating materials
  //G4double aldensity = 2.700*g/cm3;
  //G4double a = 26.98*g/mole;
  //G4Material* Al = new G4Material("Aluminum", 13., a, aldensity);
  // G4Element* Cs  = NistManager->FindOrBuildElement("Cs");
  // G4Element* I  = NistManager->FindOrBuildElement("I");
  // G4double csidensity = 4.51*g/cm3;
  // G4Material* CsI = new G4Material("CsI", csidensity, 2);
  // CsI->AddElement(Cs, 0.5);
  // CsI->AddElement(I, 0.5);

  G4Material* Al = NistManager->FindOrBuildMaterial("G4_Al");
  G4Material* Si = NistManager->FindOrBuildMaterial("G4_Si");

  //creating air for the world volume, this is just a dummy
  G4Element* O  = NistManager->FindOrBuildElement("O");
  G4Element* N  = NistManager->FindOrBuildElement("N");

  G4double density = 1.290*mg/cm3;
  G4Material* Air = new G4Material("Air", density, 2);
  Air->AddElement(N, 0.7);
  Air->AddElement(O, 0.3);

 
  G4double vac_density = 1.225e-7*mg/cm3; 
  G4double pressure    = 1.e-7*bar;
  G4double temperature = STP_Temperature + 20*kelvin;
  G4Material* Vacuum = new G4Material("Vacuum_7", vac_density, 1,kStateGas, temperature, pressure);
  Vacuum->AddMaterial(Air, 1.); 

#ifdef G4VIS_USE
  // usefull colors
  G4VisAttributes* HallVisAtt = new G4VisAttributes(false,G4Colour(0.,1.,0.));
  G4VisAttributes* detectorVisAtt = new G4VisAttributes(true,G4Colour(0.89,0.45,0.13));
#endif

  //------------------------------ experimental hall (world volume)
  G4double expHall_x = 3.0*m;
  G4double expHall_y = 3.0*m;
  G4double expHall_z = 3.0*m;
  G4Box* experimentalHall_box = new G4Box("expHall_box",expHall_x,expHall_y,expHall_z);
  G4LogicalVolume *experimentalHall_log = new G4LogicalVolume(experimentalHall_box,Vacuum,"expHall_log",0,0,0);
#ifdef G4VIS_USE
  experimentalHall_log->SetVisAttributes(HallVisAtt);
#endif
  G4VPhysicalVolume *experimentalHall_phys = new G4PVPlacement(0,G4ThreeVector(),experimentalHall_log,"expHall",0,false,0);



  //------------------------------ detector array
  //needs sensitive detector manager
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  //G4Box for the sensitive detectors
  G4Box* detector_box[NDET];
  G4LogicalVolume* detector_log[NDET];
  G4VPhysicalVolume* detector_phys[NDET];
  SensitiveDetector* sensitive_detector[NDET];
  
  for(int i=0;i<NDET;i++){
    detector_box[i] = new G4Box(Form("detector_box_%d",i),fset->DetectorWidth(i)*mm/2,fset->DetectorHeight(i)*mm/2,fset->DetectorDepth(i)*mm/2);
  
    detector_log[i] = new G4LogicalVolume(detector_box[i], Si,Form("detector_log_%d",i));
    
#ifdef G4VIS_USE
    detector_log[i]->SetVisAttributes(detectorVisAtt);
#endif
    
    detector_phys[i] = new G4PVPlacement(NULL,G4ThreeVector(0,0,fset->DetectorPosition(i)),detector_log[i],Form("detector_phys_%d",i),experimentalHall_log,false,0);
    
    // -----creating sensisitve detectors and adding them to the sensitive detector manager
    sensitive_detector[i] = new SensitiveDetector(Form("detector_%d",i));
    SDman->AddNewDetector(sensitive_detector[i]);
    detector_log[i]->SetSensitiveDetector(sensitive_detector[i]);
  }

  return experimentalHall_phys;
}

