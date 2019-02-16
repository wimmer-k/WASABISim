/*************************************************************************
 * 
 *  fill histogramms at the end of an event
 * 
 *************************************************************************/

#include "EventAction.hh"

using namespace std;
using namespace CLHEP;

EventAction::EventAction(DataManager* data, Settings* set){
  // store the pointer to the data class locally, in order to be able to acess all information later
  fdata = data;
  fset = set;
  fRand = new TRandom();
}
EventAction::~EventAction(){
}
void EventAction::BeginOfEventAction(const G4Event*){
  //cout << __PRETTY_FUNCTION__  << endl;
}
void EventAction::EndOfEventAction(const G4Event* evt){
  //cout << __PRETTY_FUNCTION__  << endl;

  // get the hits collection (HC) of the current event
  G4HCofThisEvent * HCE = evt->GetHCofThisEvent();

  // temporary storage for all the energies
  G4double en[NDET];
  G4double strX[NDET][NXSTRIPS];
  G4double strY[NDET][NYSTRIPS];
  G4double etot =0;

  WASABI *wasabi = new WASABI();
  
   // loop over all detectors
  for(int i=0;i<NDET;i++){
    // reset the energy of the current crystal
    en[i] =0;
    for(int s=0;s<NXSTRIPS;s++)
      strX[i][s] = 0;
    for(int s=0;s<NYSTRIPS;s++)
      strY[i][s] = 0;
    
    // get all hits in this current crystal
    HitsCollection* collection = (HitsCollection*)(HCE->GetHC(i));

  
  // loop over all the hits in this crystal
    for(int j=0;j<collection->entries();j++){
      // add the energy to the energy of the current cyrstal (en[i]) and the total energy (etot)
      //cout << (*collection)[j]->GetEdep()*MeV << "\t"<< (*collection)[j]->GetEdep()*keV << "\t"<< (*collection)[j]->GetEdep() << endl;
      en[i] += (*collection)[j]->GetEdep()*1000;
      etot+=(*collection)[j]->GetEdep()*1000;
      G4ThreeVector pos = (*collection)[j]->GetPos();
      //cout << i <<"\t" << j <<"\t" << pos.x()*mm << "\t" << pos.y()*mm << "\t" << pos.z()*mm << endl;
      //cout << i <<"\t" << j <<"\t" << pos.x()*mm << "\t" << (pos.x()*mm+fset->DetectorWidth(i)/2) << "\t" << (int)((pos.x()*mm+fset->DetectorWidth(i)/2)/fset->DetectorWidth(i)*NXSTRIPS) << endl;
      int xs = (int)((pos.x()*mm+fset->DetectorWidth(i)/2)/fset->DetectorWidth(i)*NXSTRIPS);
      int ys = (int)((pos.y()*mm+fset->DetectorHeight(i)/2)/fset->DetectorHeight(i)*NYSTRIPS);
      if(xs<0 || xs >NXSTRIPS-1){
	cout << "strange xposition: "<<xs << endl;
	cout << "DSSSD: "<< i <<",\tHit: " << j <<",\tx = " << pos.x()*mm << ",\tstrip = " << (int)((pos.x()*mm+fset->DetectorWidth(i)/2)/fset->DetectorWidth(i)*NXSTRIPS) << endl;
      }
      else
	strX[i][xs] += (*collection)[j]->GetEdep()*1000;

      if(ys<0 || ys >NYSTRIPS-1){
	cout << "strange yposition:" <<ys << endl;
	cout << "DSSSD: "<< i <<",\tHit: " << j <<",\ty = " << pos.y()*mm << ",\tstrip = " << (int)((pos.y()*mm+fset->DetectorHeight(i)/2)/fset->DetectorHeight(i)*NYSTRIPS) << endl;
      }
      else
	strY[i][ys] += (*collection)[j]->GetEdep()*1000;
      
    }//loop over all hits

    for(int s=0;s<NXSTRIPS;s++){
      if(strX[i][s]>0)
	strX[i][s] += fRand->Gaus(0,fset->DetectorResolution(i));
      if(strX[i][s]>0)
	wasabi->GetDSSSD(i)->AddHitX(new WASABIHit(s,strX[i][s],true));
    }
    for(int s=0;s<NYSTRIPS;s++){
      if(strY[i][s]>0)
	strY[i][s] += fRand->Gaus(0,fset->DetectorResolution(i));
      if(strY[i][s]>0)
	wasabi->GetDSSSD(i)->AddHitY(new WASABIHit(s,strY[i][s],true));
    }
    wasabi->GetDSSSD(i)->Addback();
  }//loop detectors

  // fill the tree in the datamanager object, this saves the event to the ouput file
  if(etot>0)
    fdata->FillTree(wasabi,en,etot);


  //status output:
  // get current event number
  G4int event_id = evt->GetEventID();
  //cout << " ^^^^ " << event_id << endl;
  // output every 10000 events
  if(event_id%10000 ==0){ 
    cout << event_id <<"/"<<fdata->GetNevents() << " done..." << endl;
  }
  

}
