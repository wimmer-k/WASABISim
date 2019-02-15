/*************************************************************************
 * 
 *  fill histogramms at the end of an event
 * 
 *************************************************************************/

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "globals.hh"
#include "TRandom.h"

class EventAction;

#include "SensitiveDetector.hh"
#include "DataManager.hh"
#include "WASABI.hh"


class EventAction : public G4UserEventAction
{
public:
  EventAction(DataManager* data, Settings* set);
  ~EventAction();

public:
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
        
private:
  DataManager* fdata;
  Settings* fset;
  //! radom generator for smearing ADC values
  TRandom* fRand;
};

#endif

    
