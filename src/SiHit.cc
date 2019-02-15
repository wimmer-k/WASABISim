/*************************************************************************
 *
 *    Si hit
 * 
 *************************************************************************/

#include "SiHit.hh"

G4Allocator<SiHit> HitAllocator;

SiHit::SiHit()
  :trackID(0), edep(0), pos(0), posindet(0)
{;}

SiHit::~SiHit() 
{;}

SiHit::SiHit(const SiHit& right)
  : G4VHit()
{
  trackID     = right.trackID;
  parentID    = right.parentID;
  edep        = right.edep;
  pos         = right.pos;
  posindet    = right.posindet;
  track.CopyTrackInfo(right.track);
  procName    = right.procName;
  step        = right.step;
  vol         = right.vol;
  ID          = right.ID;
}

const SiHit& SiHit::operator=(const SiHit& right)
{
  trackID     = right.trackID;
  parentID    = right.parentID;
  edep        = right.edep;
  pos         = right.pos;
  posindet    = right.posindet;
  track.CopyTrackInfo(right.track);
  procName    = right.procName;
  step        = right.step;
  vol         = right.vol;
  ID          = right.ID;
  return *this;
}

int SiHit::operator==(const SiHit&) const
{
  return 0;
}

void SiHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();

  if(pVVisManager)
  {
    G4Circle circle(pos);
    circle.SetScreenSize(0.04);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

void SiHit::Print()
{
  G4cout << " Si: " << G4endl;
  G4cout << "  trackID: " << trackID 
         << "  energy deposit: " << G4BestUnit(edep,"Energy")
	 << "  position: " << G4BestUnit(pos,"Length") << G4endl;
}




