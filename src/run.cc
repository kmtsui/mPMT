/*                                                                                                                        
Author:    Mohit Gola 10th July 2023                                                                                      
*/

#include "run.hh"

MyRunAction::MyRunAction()
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  //  G4AnalysisManager *man1 = G4AnalysisManager::Instance();
  /*  
  man->CreateNtuple("Position", "Position");
  man->CreateNtupleDColumn("PosX");
  man->CreateNtupleDColumn("PosY");
  man->CreateNtupleDColumn("PosZ");
  man->CreateNtupleIColumn("eventID");
  man->FinishNtuple(0);
  */
  man->CreateNtuple("Photons", "Photons");
  man->CreateNtupleDColumn("Angle");
  man->CreateNtupleIColumn("Absorbed");
  man->CreateNtupleIColumn("Transmitted");
  man->CreateNtupleIColumn("Reflected");
  //  man->FinishNtuple(1);
  man->FinishNtuple(0);
  /*
  man->CreateNtuple("Steps", "Steps");
  man->CreateNtupleIColumn("photonSteps");
  man->CreateNtupleIColumn("eventID");
  man->CreateNtupleIColumn("TotalPhotons");
  man->CreateNtupleSColumn("PreStepVolume");
  man->FinishNtuple(2);
  */
}

MyRunAction::~MyRunAction() 
{

}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
  TotalNumAbsorbed=0;
  TotalNumReflected=0;
  TotalNumTransmitted=0;
  totalPhotons =0;
  eventOnTop = 0;  

  G4AnalysisManager *man = G4AnalysisManager::Instance();

  //  G4cout<<"CHECK!!!"<<G4endl;
  G4int runID = run->GetRunID();


  std::stringstream strRunID;
  strRunID << runID;

  man->OpenFile("output"+strRunID.str()+".root");

}

void MyRunAction::EndOfRunAction(const G4Run*)
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->Write();
  man->CloseFile();


  G4RunManager* runManager = G4RunManager::GetRunManager();
  const G4UserEventAction* eventAction = runManager->GetUserEventAction();
  if (eventAction) {
    MyEventAction* myEventAction = dynamic_cast<MyEventAction*>(const_cast<G4UserEventAction*>(eventAction));
    if (myEventAction) {
      myEventAction->ResetCounters();
    }

  }


}
