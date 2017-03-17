// -*- C++ -*-
//
// Package:    Demo/DemoAnalyzer
// Class:      DemoAnalyzer
// 
/**\class DemoAnalyzer DemoAnalyzer.cc Demo/DemoAnalyzer/plugins/DemoAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  emily macdonald
//         Created:  Tue, 14 Mar 2017 19:49:09 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

//#include "DataFormats/TrackReco/interface/Track.h"
//#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/PatCandidates/interface/MET.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1F.h"
#include "TTree.h"
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
  //slimmedMETs
  edm::InputTag slimmedmetTag_;
  edm::EDGetTokenT<edm::View<pat::MET> > slimmedmetTok_ ;
  //TH1F * h_met;
  //patPFMet
  edm::InputTag PFmetTag_;
  edm::EDGetTokenT<edm::View<pat::MET> > PFmetTok_ ;
  //TH1F * h_pfmet;
  //patPFMetT1
  edm::InputTag PFmetT1Tag_;
  edm::EDGetTokenT<edm::View<pat::MET> > PFmetT1Tok_ ;
  //patPFMetT1JetResDown
  edm::InputTag metResDTag_;
  edm::EDGetTokenT<edm::View<pat::MET> > metResDTok_ ;
  //TH1F * h_metresd;
  //patPFMetT1JetResUp
  edm::InputTag metResUTag_;
  edm::EDGetTokenT<edm::View<pat::MET> > metResUTok_ ;
  //TH1F * h_metresu;
  //patPFMetT1Puppi
  edm::InputTag metPuppiTag_;
  edm::EDGetTokenT<edm::View<pat::MET> > metPuppiTok_ ;
  //TH1F * h_metpuppi;
  //patPFMetT1Smear
  edm::InputTag metSmearTag_;
  edm::EDGetTokenT<edm::View<pat::MET> > metSmearTok_ ;
  //TH1F * h_metsmear;
  //patPFMetT1SmearDown
  edm::InputTag metSmearDTag_;
  edm::EDGetTokenT<edm::View<pat::MET> > metSmearDTok_ ;
  //TH1F * h_metsmeard;
  //patPFMetT1SmearUp
  edm::InputTag metSmearUTag_;
  edm::EDGetTokenT<edm::View<pat::MET> > metSmearUTok_ ;
  //TH1F * h_metsmearu;
  /**
  //relative plots
  TH1F * hrel_metresd;
  TH1F * hrel_metresu;
  TH1F * hrel_metpuppi;
  TH1F * hrel_metsmear;
  TH1F * hrel_metsmearu;
  TH1F * hrel_metsmeard;
  **/
  float slimmedmet;
  float pfmet;
  float pfmett1;
  float metresd;
  float metresu;
  float metpuppi;
  float metsmear;
  float metsmeard;
  float metsmearu;
  TTree * tree;


      // ----------member data ---------------------------
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
   tree->Branch("slimmedMETs", &slimmedmet);
   tree->Branch("patPFMet", &pfmet);
   tree->Branch("patPFMetT1", &pfmett1);
   tree->Branch("patPFMetT1JetResDown", &metresd);
   tree->Branch("patPfMetT1JesResUp", &metresu);
   tree->Branch("patPFMetT1Puppi", &metpuppi);
   tree->Branch("patPFMetT1Smear", &metsmear);
   tree->Branch("patPFMetT1SmearJetResDown", &metsmeard);
   tree->Branch("patPFMetT1SmearJetResUp", &metsmearu);   




   //slimmedMETs
   // h_met    = fs->make<TH1F>( "slimmedMET"  , "slimmedMET", 100,  0., 500 );
   slimmedmetTag_ = iConfig.getParameter<edm::InputTag> ("slimmedMETTag");
   slimmedmetTok_ = consumes<edm::View<pat::MET> >(slimmedmetTag_);
   //patPFMet
   //h_pfmet    = fs->make<TH1F>( "PFMet"  , "PFMet", 100,  0., 500 );
   PFmetTag_ = iConfig.getParameter<edm::InputTag> ("PFMETTag");
   PFmetTok_ = consumes<edm::View<pat::MET> >(PFmetTag_);

   //patPFMetT1
   PFmetT1Tag_ = iConfig.getParameter<edm::InputTag> ("PFMETT1Tag");
   PFmetT1Tok_ = consumes<edm::View<pat::MET> >(PFmetT1Tag_);

   //patPFMetT1JetResDown
   //h_metresd    = fs->make<TH1F>( "PFMetT1JetResDown"  , "PFMetT1JetResDown", 100,  0., 500 );
   metResDTag_ = iConfig.getParameter<edm::InputTag> ("PFMETResDTag");
   metResDTok_ = consumes<edm::View<pat::MET> >(metResDTag_);
   //patPFMetT1JetResUp
   //h_metresu    = fs->make<TH1F>( "PFMetT1JetResUp"  , "PFMetT1JetResUp", 100,  0., 500 );
   metResUTag_ = iConfig.getParameter<edm::InputTag> ("PFMETResUTag");
   metResUTok_ = consumes<edm::View<pat::MET> >(metResUTag_);
   //patPFMetT1Puppi
   //h_metpuppi    = fs->make<TH1F>( "PFMetT1Puppi"  , "PFMetT1Puppi", 100,  0., 500 );
   metPuppiTag_ = iConfig.getParameter<edm::InputTag> ("PFMETPuppiTag");
   metPuppiTok_ = consumes<edm::View<pat::MET> >(metPuppiTag_);
   //patPFMetT1Smear
   //h_metsmear    = fs->make<TH1F>( "PFMetT1Smear"  , "PFMetT1Smear", 100,  0., 500 );
   metSmearTag_ = iConfig.getParameter<edm::InputTag> ("PFMETSmearTag");
   metSmearTok_ = consumes<edm::View<pat::MET> >(metSmearTag_);
   //patPFMetT1SmearDown
   //h_metsmeard    = fs->make<TH1F>( "PFMetT1SmearJetResDown"  , "PFMetT1SmearJetResDown", 100,  0., 500 );
   metSmearDTag_ = iConfig.getParameter<edm::InputTag> ("PFMETSmearDTag");
   metSmearDTok_ = consumes<edm::View<pat::MET> >(metSmearDTag_);
   //patPFMetT1SmearUp
   //h_metsmearu    = fs->make<TH1F>( "PFMetT1SmearJetResUp"  , "PFMetT1SmearJetResUp", 100,  0., 500 );
   metSmearUTag_ = iConfig.getParameter<edm::InputTag> ("PFMETSmearUTag");
   metSmearUTok_ = consumes<edm::View<pat::MET> >(metSmearUTag_);
   /**
   //relative plots
   //hrel_metresd = fs->make<TH1F>( "PFMetT1JetResDown_relative"  , "PFMetT1JetResDown_relative", 100,  0., 5 );
   hrel_metresu = fs->make<TH1F>( "PFMetT1JetResUp_relative"  , "PFMetT1JetResUp_relative", 100,  0., 5 );
   hrel_metpuppi = fs->make<TH1F>( "PFMetT1Puppi_relative"  , "PFMetT1Puppi_relative", 100,  0., 5 );
   hrel_metsmear = fs->make<TH1F>( "PFMetT1Smear_relative"  , "PFMetT1Smear_relative", 100,  0., 5 );
   hrel_metsmeard    = fs->make<TH1F>( "PFMetT1SmearJetResDown_relative"  , "PFMetT1SmearJetResDown_relative", 100,  0., 5 );
   hrel_metsmearu    = fs->make<TH1F>( "PFMetT1SmearJetResUp_relative"  , "PFMetT1SmearJetResUp_relative", 100,  0., 5 );
   **/
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

   //  Handle<reco::TrackCollection> tracks;
   //  iEvent.getByLabel("generalTracks", tracks); 

   //slimmedMETs
   edm::Handle< edm::View<pat::MET> > slimmedMETs;
   iEvent.getByToken(slimmedmetTok_, slimmedMETs);
   //   LogInfo("Demo") << "slimmedMETs "<<slimmedMETs->at(0).pt();
   //h_met->Fill(slimmedMETs->at(0).pt());
   slimmedmet=slimmedMETs->at(0).pt();

   //patPFMet  
   edm::Handle< edm::View<pat::MET> > patPFMet;
     iEvent.getByToken(PFmetTok_, patPFMet);
     // LogInfo("Demo") << "patPFMet "<<patPFMet->at(0).pt();
     //h_pfmet->Fill(patPFMet->at(0).pt());
     pfmet=patPFMet->at(0).pt();
 
     //patPFMetT1
     edm::Handle< edm::View<pat::MET> > patPFMetT1;
     iEvent.getByToken(PFmetT1Tok_, patPFMetT1);
     pfmett1=patPFMetT1->at(0).pt();

     //patPFMetT1JetResDown
     edm::Handle< edm::View<pat::MET> > patPFMetT1JetResDown;
     iEvent.getByToken(metResDTok_, patPFMetT1JetResDown);
     // LogInfo("Demo") << "patPFMetT1JetResDown "<<patPFMetT1JetResDown->at(0).pt();
     //h_metresd->Fill(patPFMetT1JetResDown->at(0).pt());
     metresd=patPFMetT1JetResDown->at(0).pt();

     //patPFMetT1JetResUp
     edm::Handle< edm::View<pat::MET> > patPFMetT1JetResUp;
     iEvent.getByToken(metResUTok_, patPFMetT1JetResUp);
     // LogInfo("Demo") << "patPFMetT1JetResUp "<<patPFMetT1JetResUp->at(0).pt();
     //h_metresu->Fill(patPFMetT1JetResUp->at(0).pt());
     metresu=patPFMetT1JetResUp->at(0).pt();

     //patPFMetT1Puppi
     edm::Handle< edm::View<pat::MET> > patPFMetT1Puppi;
     iEvent.getByToken(metPuppiTok_, patPFMetT1Puppi);
     // LogInfo("Demo") << "patPFMetT1Puppi "<<patPFMetT1Puppi->at(0).pt();
     //h_metpuppi->Fill(patPFMetT1Puppi->at(0).pt());
     metpuppi=patPFMetT1Puppi->at(0).pt();

     //patPFMetT1Smear
     edm::Handle< edm::View<pat::MET> > patPFMetT1Smear;
     iEvent.getByToken(metSmearTok_, patPFMetT1Smear);
     // LogInfo("Demo") << "patPFMetT1Smear "<<patPFMetT1Smear->at(0).pt();
     //h_metsmear->Fill(patPFMetT1Smear->at(0).pt());
     metsmear=patPFMetT1Smear->at(0).pt();

     //patPFMetT1SmearDown
     edm::Handle< edm::View<pat::MET> > patPFMetT1SmearJetResDown;
     iEvent.getByToken(metSmearDTok_, patPFMetT1SmearJetResDown);
     // LogInfo("Demo") << "patPFMetT1SmearDown "<<patPFMetT1SmearDown->at(0).pt();
     //h_metsmeard->Fill(patPFMetT1SmearJetResDown->at(0).pt());
     metsmeard=patPFMetT1SmearJetResDown->at(0).pt();

     //patPFMetT1Smear
     edm::Handle< edm::View<pat::MET> > patPFMetT1SmearJetResUp;
     iEvent.getByToken(metSmearUTok_, patPFMetT1SmearJetResUp);
     // LogInfo("Demo") << "patPFMetT1SmearUp "<<patPFMetT1SmearUp->at(0).pt();
     //h_metsmearu->Fill(patPFMetT1SmearJetResUp->at(0).pt());
     metsmearu=patPFMetT1SmearJetResUp->at(0).pt();

     
    

     tree->Fill();


     /**
     //relative plots
     hrel_metresd->Fill((patPFMetT1JetResDown->at(0).pt()-patPFMet->at(0).pt())/patPFMet->at(0).pt());
     hrel_metresu->Fill((patPFMetT1JetResUp->at(0).pt()-patPFMet->at(0).pt())/patPFMet->at(0).pt());
     hrel_metpuppi->Fill((patPFMetT1Puppi->at(0).pt()-patPFMet->at(0).pt())/patPFMet->at(0).pt());
     hrel_metsmear->Fill((patPFMetT1Smear->at(0).pt()-patPFMet->at(0).pt())/patPFMet->at(0).pt());
     hrel_metsmeard->Fill((patPFMetT1SmearJetResDown->at(0).pt()-patPFMet->at(0).pt())/patPFMet->at(0).pt());
     hrel_metsmearu->Fill((patPFMetT1SmearJetResUp->at(0).pt()-patPFMet->at(0).pt())/patPFMet->at(0).pt());
     **/


#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
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
