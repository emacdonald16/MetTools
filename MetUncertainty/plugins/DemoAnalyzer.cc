// Package:    Demo/DemoAnalyzer
// Class:      DemoAnalyzer
// 
// Original Author:  emily macdonald
//         Created:  Tue, 14 Mar 2017 19:49:09 GMT


// system include files
#include <memory>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Math/interface/LorentzVector.h"

// ROOT include files
#include "TH1F.h"
#include "TTree.h"

using std::vector;

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class DemoAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
   explicit DemoAnalyzer(const edm::ParameterSet&);
   ~DemoAnalyzer();
   
   static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
   
   
private:
   virtual void beginJob() override;
   virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
   virtual void endJob() override;

   // ----------member data ---------------------------
   /*
   edm::InputTag jetTag_;
   edm::InputTag jetTagJECUp_;
   edm::InputTag jetTagJECDown_;
   edm::InputTag slimmedmetTag_;
   edm::InputTag PFmetTag_;
   edm::InputTag PFmetT1Tag_;
   edm::InputTag metResDTag_;
   edm::InputTag metResUTag_;
   edm::InputTag metPuppiTag_;
   edm::InputTag metSmearTag_;
   edm::InputTag metSmearDTag_;
   edm::InputTag metSmearUTag_;
   */

   edm::EDGetTokenT<edm::View<pat::Jet> > jetTok_;
   edm::EDGetTokenT<edm::View<pat::Jet> > jetTokJECUp_;
   edm::EDGetTokenT<edm::View<pat::Jet> > jetTokJECDown_;
   edm::EDGetTokenT<edm::View<pat::MET> > slimmedmetTok_ ;
   edm::EDGetTokenT<edm::View<pat::MET> > PFmetTok_ ;
   edm::EDGetTokenT<edm::View<pat::MET> > PFmetT1Tok_ ;
   edm::EDGetTokenT<edm::View<pat::MET> > metResDTok_ ;
   edm::EDGetTokenT<edm::View<pat::MET> > metResUTok_ ;
   edm::EDGetTokenT<edm::View<pat::MET> > metPuppiTok_ ;
   edm::EDGetTokenT<edm::View<pat::MET> > metSmearTok_ ;
   edm::EDGetTokenT<edm::View<pat::MET> > metSmearDTok_ ;
   edm::EDGetTokenT<edm::View<pat::MET> > metSmearUTok_ ;

   edm::Handle< edm::View<pat::Jet> > jets;
   edm::Handle< edm::View<pat::Jet> > jetsJECUp;
   edm::Handle< edm::View<pat::Jet> > jetsJECDown;
   edm::Handle< edm::View<pat::MET> > slimmedMETs;
   edm::Handle< edm::View<pat::MET> > patPFMet;
   edm::Handle< edm::View<pat::MET> > patPFMetT1;
   edm::Handle< edm::View<pat::MET> > patPFMetT1JetResDown;
   edm::Handle< edm::View<pat::MET> > patPFMetT1JetResUp;
   edm::Handle< edm::View<pat::MET> > patPFMetT1Puppi;
   edm::Handle< edm::View<pat::MET> > patPFMetT1Smear;
   edm::Handle< edm::View<pat::MET> > patPFMetT1SmearJetResDown;
   edm::Handle< edm::View<pat::MET> > patPFMetT1SmearJetResUp;
   
   vector<float> jtpt;
   vector<float> jtptJECUp;
   vector<float> jtptJECDown;
   vector<float> jteta;
   vector<float> jtphi;
   vector<float> jte;
   vector<float> jteJECUp;
   vector<float> jteJECDown;   
   float slimmedmet;
   float slimmedmetJECUp;
   float slimmedmetJECDown;
   float pfmet;
   float pfmett1;
   float metresd;
   float metresu;
   float metpuppi;
   float metsmear;
   float metsmeard;
   float metsmearu;
   TTree * tree;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
DemoAnalyzer::DemoAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   usesResource("TFileService");
   edm::Service<TFileService> fs;

   tree = fs->make<TTree>("tree","tree");
   tree->Branch("jtpt",        "vector<float>", &jtpt);
   tree->Branch("jtptJECUp",   "vector<float>", &jtptJECUp);
   tree->Branch("jtptJECDown", "vector<float>", &jtptJECDown);
   tree->Branch("jteta",       "vector<float>", &jteta);
   tree->Branch("jtphi",       "vector<float>", &jtphi);
   tree->Branch("jte",         "vector<float>", &jte);
   tree->Branch("jteJECUp",    "vector<float>", &jteJECUp);
   tree->Branch("jteJECDown",  "vector<float>", &jteJECDown);
   tree->Branch("slimmedMETs",        &slimmedmet);
   tree->Branch("slimmedMETsJECUp",   &slimmedmetJECUp);
   tree->Branch("slimmedMETsJECDown", &slimmedmetJECDown);
   tree->Branch("patPFMet", &pfmet);
   tree->Branch("patPFMetT1", &pfmett1);
   tree->Branch("patPFMetT1JetResDown", &metresd);
   tree->Branch("patPfMetT1JesResUp", &metresu);
   tree->Branch("patPFMetT1Puppi", &metpuppi);
   tree->Branch("patPFMetT1Smear", &metsmear);
   tree->Branch("patPFMetT1SmearJetResDown", &metsmeard);
   tree->Branch("patPFMetT1SmearJetResUp", &metsmearu);   

   jetTok_        = consumes<edm::View<pat::Jet> >(iConfig.getParameter<edm::InputTag> ("jetTag"));
   jetTokJECUp_   = consumes<edm::View<pat::Jet> >(iConfig.getParameter<edm::InputTag> ("jetTagJECUp"));
   jetTokJECDown_ = consumes<edm::View<pat::Jet> >(iConfig.getParameter<edm::InputTag> ("jetTagJECDown"));
   slimmedmetTok_ = consumes<edm::View<pat::MET> >(iConfig.getParameter<edm::InputTag> ("slimmedMETTag"));
   PFmetTok_      = consumes<edm::View<pat::MET> >(iConfig.getParameter<edm::InputTag> ("PFMETTag"));
   PFmetT1Tok_    = consumes<edm::View<pat::MET> >(iConfig.getParameter<edm::InputTag> ("PFMETT1Tag"));
   metResDTok_    = consumes<edm::View<pat::MET> >(iConfig.getParameter<edm::InputTag> ("PFMETResDTag"));
   metResUTok_    = consumes<edm::View<pat::MET> >(iConfig.getParameter<edm::InputTag> ("PFMETResUTag"));
   metPuppiTok_   = consumes<edm::View<pat::MET> >(iConfig.getParameter<edm::InputTag> ("PFMETPuppiTag"));
   metSmearTok_   = consumes<edm::View<pat::MET> >(iConfig.getParameter<edm::InputTag> ("PFMETSmearTag"));
   metSmearDTok_  = consumes<edm::View<pat::MET> >(iConfig.getParameter<edm::InputTag> ("PFMETSmearDTag"));
   metSmearUTok_  = consumes<edm::View<pat::MET> >(iConfig.getParameter<edm::InputTag> ("PFMETSmearUTag"));
}


DemoAnalyzer::~DemoAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
DemoAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   
   // Reset the vectors
   jtpt.clear();
   jtptJECUp.clear();
   jtptJECDown.clear();
   jteta.clear();
   jtphi.clear();
   jte.clear();
   jteJECUp.clear();
   jteJECDown.clear();

   //jets
   math::XYZTLorentzVector sumJet;
   math::XYZTLorentzVector sumJetJECUp;
   math::XYZTLorentzVector sumJetJECDown;
   iEvent.getByToken(jetTok_, jets);
   for (edm::View<pat::Jet>::const_iterator jetIter = jets->begin(); jetIter != jets->end(); ++jetIter) { 
      jtpt.push_back(jetIter->pt());
      jteta.push_back(jetIter->eta());
      jtphi.push_back(jetIter->phi());
      jte.push_back(jetIter->energy());
      sumJet+=jetIter->p4();
   }
   iEvent.getByToken(jetTokJECUp_, jetsJECUp);
   for (edm::View<pat::Jet>::const_iterator jetIter = jetsJECUp->begin(); jetIter != jetsJECUp->end(); ++jetIter) { 
      jtptJECUp.push_back(jetIter->pt());
      jteJECUp.push_back(jetIter->energy());
      sumJetJECUp+=jetIter->p4();
   }
   iEvent.getByToken(jetTokJECDown_, jetsJECDown);
   for (edm::View<pat::Jet>::const_iterator jetIter = jetsJECDown->begin(); jetIter != jetsJECDown->end(); ++jetIter) { 
      jtptJECDown.push_back(jetIter->pt());
      jteJECDown.push_back(jetIter->energy());
      sumJetJECDown+=jetIter->p4();
   }

   //slimmedMETs
   iEvent.getByToken(slimmedmetTok_, slimmedMETs);
   slimmedmet=slimmedMETs->at(0).pt();
   math::XYZTLorentzVector metP4 = slimmedMETs->at(0).p4();

   //slimmesMETsJECUp
   slimmedmetJECUp = (metP4 + (sumJet-sumJetJECUp)).Pt();

   //slimmesMETsJECDown
   slimmedmetJECDown = (metP4 + (sumJet-sumJetJECDown)).Pt();

   //patPFMet  
   iEvent.getByToken(PFmetTok_, patPFMet);
   pfmet=patPFMet->at(0).pt();
   
   //patPFMetT1
   iEvent.getByToken(PFmetT1Tok_, patPFMetT1);
   pfmett1=patPFMetT1->at(0).pt();
   
   //patPFMetT1JetResDown
   iEvent.getByToken(metResDTok_, patPFMetT1JetResDown);
   metresd=patPFMetT1JetResDown->at(0).pt();
   
   //patPFMetT1JetResUp
   iEvent.getByToken(metResUTok_, patPFMetT1JetResUp);
   metresu=patPFMetT1JetResUp->at(0).pt();
   
   //patPFMetT1Puppi
   iEvent.getByToken(metPuppiTok_, patPFMetT1Puppi);
   metpuppi=patPFMetT1Puppi->at(0).pt();
   
   //patPFMetT1Smear
   iEvent.getByToken(metSmearTok_, patPFMetT1Smear);
   metsmear=patPFMetT1Smear->at(0).pt();
   
   //patPFMetT1SmearDown
   iEvent.getByToken(metSmearDTok_, patPFMetT1SmearJetResDown);
   metsmeard=patPFMetT1SmearJetResDown->at(0).pt();
   
   //patPFMetT1Smear
   iEvent.getByToken(metSmearUTok_, patPFMetT1SmearJetResUp);
   metsmearu=patPFMetT1SmearJetResUp->at(0).pt();
   
   tree->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void 
DemoAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DemoAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DemoAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(DemoAnalyzer);
