/*                                                                                                                         
Author:    Mohit Gola 10th July 2023                                                                                       
*/

#include "generator.hh"
#include "MyPrimaryGeneratorMessenger.hh"
#include "constructMultiPMT.hh"
#include "G4VSolid.hh"
#include "G4Navigator.hh"
#include "G4GeneralParticleSource.hh"
#include "G4PVPlacement.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
  fParticleGun = new G4ParticleGun(1);
  fMessenger = new MyPrimaryGeneratorMessenger(this);
  angleDegrees = 0.0;
  angleRadians = angleDegrees * CLHEP::degree;
  particleEnergy = 3.3509;
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
  delete fMessenger;
  delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
  
  G4cout<<"FOUND THE Optical Photon!!!\n"<<G4endl;
  G4cout<<"THE ENERGY SET VALUE IS == "<< particleEnergy << G4endl;
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName="opticalphoton";
  G4ParticleDefinition *particle = particleTable->FindParticle(particleName);
  G4cout<<"THE VALUE OF ANGLE IN RADIANS == "<< angleRadians << G4endl;
  /*
  G4ThreeVector initialPosition(0.0, 0.0, 47.*mm);

  G4cout<<"Angle in degrees = "<<angleDegrees<<G4endl;

  // Define the target Z coordinate                                                                                       
  double targetZ = 44.40 * mm;

  // Calculate the difference in Z coordinates                                                                            
  double deltaZ = targetZ - initialPosition.z();

  // Calculate the new Y coordinate based on the angle and deltaZ                                                          
    double newY = initialPosition.y() + deltaZ * std::tan(angleRadians);

  // Create the new position vector                                                                                       
  G4ThreeVector newPosition(initialPosition.x(), newY, initialPosition.z());

  // Calculate the direction vector towards the point (0, 0, 35.903)                                                        
  G4ThreeVector direction = (G4ThreeVector(0.0, 0.0, targetZ) - newPosition).unit();
  // Print the new position and direction                                                                                  
  G4cout << "New Position: (" << newPosition.x() / mm << ", " << newPosition.y() / mm << ", " << newPosition.z() / mm << ")mm" << G4endl;

  G4cout << "Direction: (" << direction.x() << ", " << direction.y() << ", " << direction.z() << ")" << G4endl;


  G4double  particleEnergy = 2.47999*eV;

  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(direction);
  fParticleGun->SetParticleEnergy(particleEnergy);
  fParticleGun->SetParticlePosition(newPosition);


  G4PrimaryVertex* vertex = new G4PrimaryVertex(newPosition, 0.0);
  G4PrimaryParticle* primary = new G4PrimaryParticle(particle);
  
  G4ThreeVector momentun = direction * particleEnergy;

  vertex->SetPrimary(primary);
  G4double checkEnergy = fParticleGun->GetParticleEnergy();
  G4cout<<"PARTICLE ENERGY IS:  "<<checkEnergy<<G4endl;
  G4cout<<"GENERATED THE OPTICAL PHOTON!!!\n"<<G4endl;
  
  fParticleGun->GeneratePrimaryVertex(anEvent);
  */

  //  G4double particleEnergy = 2.47999 * eV;
  //  G4double particleEnergy = 1.7968 * eV;

  //  G4double discRadius = 38. * mm; 
  G4double discRadius = 160. * mm; 
  //  G4ThreeVector discPosition(0.0,0.0,100.0*mm);
  /*
  ConstructMultiPMT myDetector;
  G4LogicalVolume *mainWorld = myDetector.GetWorldVolume();
  G4VSolid *mainWorldSolid = mainWorld->GetSolid();


  G4Navigator navigator;
  navigator.SetWorldVolume(mainWorld); // Assuming mainWorldVolume is your main volume           

  G4ThreeVector randomPosition;
  bool validPosition = false;
  */
  /*
  ConstructMultiPMT* multiPMT = new ConstructMultiPMT();
  G4VPhysicalVolume* physWorld = multiPMT->GetphysWorld();

  G4ThreeVector physWorldTranslation(0.0, 0.0, 600.0*mm);

  G4PVPlacement* physWorldPlacement = dynamic_cast<G4PVPlacement*>(physWorld);
  if (physWorldPlacement) {
    physWorldTranslation = physWorldPlacement->GetTranslation();
  } else {
    G4cerr << "Error: physWorld is not a G4PVPlacement." << G4endl;
    // Handle the error or exit the function                                                                             
    return;
  }
  */
  G4double randomPhi = G4UniformRand() * 360.0 * deg;

  G4double xShift = (100.0 * mm) * std::tan(angleRadians);
  G4double yShift = 0.0;
  G4double zShift = 100.0 * mm;

  G4ThreeVector discPosition(xShift, yShift, zShift);

  G4double randomRadius = std::sqrt(G4UniformRand()) * discRadius;
  G4ThreeVector newPosition(discPosition.x() + randomRadius * std::cos(randomPhi), discPosition.y() +  randomRadius * std::sin(randomPhi), discPosition.z());

  G4ThreeVector direction(0.0,0.0,-1.0);
  direction.rotateY(angleRadians);
  
  //G4ThreeVector newPosition = discPosition  + physWorldTranslation;
  
  // Set particle properties                                                                                               
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(particleEnergy*eV);
  fParticleGun->SetParticlePosition(newPosition);
  //  fParticleGun->SetParticlePosition(finalPosition);
  fParticleGun->SetParticleMomentumDirection(direction);
  
  G4PrimaryVertex *vertex = new G4PrimaryVertex(newPosition, 0.0);
  G4PrimaryParticle *primary = new G4PrimaryParticle(particle);
  
  vertex->SetPrimary(primary);
  //  anEvent->AddPrimaryVertex(vertex);
  G4double checkEnergy = fParticleGun->GetParticleEnergy();
  G4cout << "PARTICLE ENERGY IS:  " << checkEnergy << G4endl;
  G4cout << "GENERATED THE OPTICAL PHOTON!!!" << G4endl;
  
  fParticleGun->GeneratePrimaryVertex(anEvent);


}
void MyPrimaryGenerator::SetAngle(G4double angle)
{
  angleDegrees = angle;
  angleRadians = angleDegrees * CLHEP::degree;
}

void MyPrimaryGenerator::SetEnergy(G4double energy)
{
  particleEnergy=energy;
}
