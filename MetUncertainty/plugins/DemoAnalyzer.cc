// Package:    Demo/DemoAnalyzer
// Class:      DemoAnalyzer
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
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

// ROOT include files
#include "TH1F.h"
#include "TTree.h"
#include "TCanvas.h"


using std::vector;
 using namespace std;
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
   edm::EDGetTokenT<edm::View<pat::PackedGenParticle> > packedGenToken_;
   edm:: Handle<edm::View<pat::PackedGenParticle> > packed;

  //  edm::EDGetTokenT<edm::View<reco::GenParticle> > prunedGenToken_;
  //edm::Handle<edm::View<reco::GenParticle> > pruned;

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
   vector<float> jteta;
   vector<float> jtphi;
   vector<float> jte;
   vector<float> jtptJECUp;
   vector<float> jtetaJECUp;
   vector<float> jtphiJECUp;
   vector<float> jteJECUp;
   vector<float> jtptJECDown;
   vector<float> jtetaJECDown;
   vector<float> jtphiJECDown;
   vector<float> jteJECDown;
   float slimmedmet;
   float slimmedmetJECUp;
   float slimmedmetJECDown;
   float pfmet;
   float pfmett1_phi;
   float pfmett1_e;
   float pfmett1;
   float metresd;
   float metresu;
   float metpuppi;
   float metsmear;
   float metsmeard;
   float metsmearu;
  //gen stuff
  int numNeutrinos;
  const reco::Candidate * mom;
  /**
  vector<int> gen_pdgId;
  vector<int> gen_status;
  vector<float> gen_pt, gen_eta, gen_phi, gen_mass;
  vector<float> gen_vx, gen_vy, gen_vz;
  vector<int> gen_charge;
  vector<int> gen_numDaughters;
  vector<int> d_pdgId;
  vector<float> d_pt, d_eta, d_phi, d_mass;
  vector<int> d_charge;
  vector<int> d_status;
  vector<reco::Candidate> gen_mother;
			      **/
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

   /**   tree->Branch("gen_pdgId",        "vector<int>", &gen_pdgId);
   tree->Branch("gen_status",        "vector<int>", &gen_status);
   tree->Branch("gen_pt",        "vector<float>", &gen_pt);
   tree->Branch("gen_eta",        "vector<float>", &gen_eta);
   tree->Branch("gen_phi",        "vector<float>", &gen_phi);
   tree->Branch("gen_mass",        "vector<float>", &gen_mass);
   tree->Branch("gen_vx",        "vector<float>", &gen_vx);
   tree->Branch("gen_vy",        "vector<float>", &gen_vy);
   tree->Branch("gen_vz",        "vector<float>", &gen_vz);
   tree->Branch("gen_numDaughters ",        "vector<int>", &gen_numDaughters);
   tree->Branch("gen_charge",        "vector<int>", &gen_charge);
   tree->Branch("gen_mother_pdgId", "vector<int>", &gen_mother);
   tree->Branch("d_pdgId",        "vector<int>", &d_pdgId);
   tree->Branch("d_status",        "vector<int>", &d_status);
   tree->Branch("d_pt",        "vector<float>", &d_pt);
   tree->Branch("d_eta",        "vector<float>", &d_eta);
   tree->Branch("d_phi",        "vector<float>", &d_phi);
   tree->Branch("d_mass",        "vector<float>", &d_mass);
   tree->Branch("d_charge",        "vector<int>", &d_charge);
   **/
   tree->Branch("numNeutrinos",  &numNeutrinos);//here!!!!!!!!!
   tree->Branch("jt_pt",        "vector<float>", &jtpt);
   tree->Branch("jt_eta",       "vector<float>", &jteta);
   tree->Branch("jt_phi",       "vector<float>", &jtphi);
   tree->Branch("jt_e",         "vector<float>", &jte);
   tree->Branch("jt_ptJECUp",   "vector<float>", &jtptJECUp);
   tree->Branch("jt_etaJECUp",   "vector<float>", &jtetaJECUp);
   tree->Branch("jt_phiJECUp",   "vector<float>", &jtphiJECUp);
   tree->Branch("jt_eJECUp",    "vector<float>", &jteJECUp);
   tree->Branch("jt_ptJECDown", "vector<float>", &jtptJECDown);
   tree->Branch("jt_etaJECDown", "vector<float>", &jtetaJECDown);
   tree->Branch("jt_phiJECDown", "vector<float>", &jtphiJECDown);
   tree->Branch("jt_eJECDown",  "vector<float>", &jteJECDown);
   //tree->Branch("slimmedMETs",        &slimmedmet);
   //tree->Branch("slimmedMETsJECUp",   &slimmedmetJECUp);
   //tree->Branch("slimmedMETsJECDown", &slimmedmetJECDown);
   tree->Branch("patPFMet", &pfmet);
   tree->Branch("patPFMetT1", &pfmett1);
   tree->Branch("patPFMetT1_phi", &pfmett1_phi);
   tree->Branch("patPFMetT1_et", &pfmett1_e);
   //tree->Branch("patPFMetT1JetResDown", &metresd);
   //tree->Branch("patPfMetT1JesResUp", &metresu);
   //tree->Branch("patPFMetT1Puppi", &metpuppi);
   //tree->Branch("patPFMetT1Smear", &metsmear);
   //tree->Branch("patPFMetT1SmearJetResDown", &metsmeard);
   //tree->Branch("patPFMetT1SmearJetResUp", &metsmearu);

   packedGenToken_ = consumes<edm::View<pat::PackedGenParticle> >(iConfig.getParameter<edm::InputTag> ("packed"));
   // prunedGenToken_ = consumes<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag> ("pruned"));
   jetTok_         = consumes<edm::View<pat::Jet> >(iConfig.getParameter<edm::InputTag> ("jetTag"));
   jetTokJECUp_    = consumes<edm::View<pat::Jet> >(iConfig.getParameter<edm::InputTag> ("jetTagJECUp"));
   jetTokJECDown_  = consumes<edm::View<pat::Jet> >(iConfig.getParameter<edm::InputTag> ("jetTagJECDown"));
   slimmedmetTok_  = consumes<edm::View<pat::MET> >(iConfig.getParameter<edm::InputTag> ("slimmedMETTag"));
   PFmetTok_       = consumes<edm::View<pat::MET> >(iConfig.getParameter<edm::InputTag> ("PFMETTag"));
   PFmetT1Tok_     = consumes<edm::View<pat::MET> >(iConfig.getParameter<edm::InputTag> ("PFMETT1Tag"));
   metResDTok_     = consumes<edm::View<pat::MET> >(iConfig.getParameter<edm::InputTag> ("PFMETResDTag"));
   metResUTok_     = consumes<edm::View<pat::MET> >(iConfig.getParameter<edm::InputTag> ("PFMETResUTag"));
   metPuppiTok_    = consumes<edm::View<pat::MET> >(iConfig.getParameter<edm::InputTag> ("PFMETPuppiTag"));
   metSmearTok_    = consumes<edm::View<pat::MET> >(iConfig.getParameter<edm::InputTag> ("PFMETSmearTag"));
   metSmearDTok_   = consumes<edm::View<pat::MET> >(iConfig.getParameter<edm::InputTag> ("PFMETSmearDTag"));
   metSmearUTok_   = consumes<edm::View<pat::MET> >(iConfig.getParameter<edm::InputTag> ("PFMETSmearUTag"));
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
   jteta.clear();
   jtphi.clear();
   jte.clear();
   jtptJECUp.clear();
   jtetaJECUp.clear();
   jtphiJECUp.clear();
   jteJECUp.clear();
   jtptJECDown.clear();
   jtetaJECDown.clear();
   jtphiJECDown.clear();
   jteJECDown.clear();
   /**
   //gen stuff
   gen_pdgId.clear();
   gen_status.clear();
   gen_pt.clear();
   gen_eta.clear();
   gen_phi.clear();
   gen_mass.clear();
   gen_vx.clear();
   gen_vy.clear();
   gen_vz.clear();
   gen_charge.clear();
   gen_numDaughters.clear();
   gen_mother.clear();
   d_pdgId.clear();
   d_status.clear();
   d_pt.clear();
   d_eta.clear();
   d_phi.clear();
   d_mass.clear();
   d_charge.clear();
   **/
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
      jtetaJECUp.push_back(jetIter->eta());
      jtphiJECUp.push_back(jetIter->phi());
      jteJECUp.push_back(jetIter->energy());
      sumJetJECUp+=jetIter->p4();
   }
   iEvent.getByToken(jetTokJECDown_, jetsJECDown);
   for (edm::View<pat::Jet>::const_iterator jetIter = jetsJECDown->begin(); jetIter != jetsJECDown->end(); ++jetIter) {
      jtptJECDown.push_back(jetIter->pt());
      jtetaJECDown.push_back(jetIter->eta());
      jtphiJECDown.push_back(jetIter->phi());
      jteJECDown.push_back(jetIter->energy());
      sumJetJECDown+=jetIter->p4();
   }
   //gen stuff


   iEvent.getByToken(packedGenToken_,packed);
   numNeutrinos = 0;
    for(size_t i = 0; i < packed->size(); ++ i) {
      const pat::PackedGenParticle & p = (*packed)[i];
	mom=p.mother(0);
      if ((p.pdgId()==12 || p.pdgId()==14 || p.pdgId()==16 || p.pdgId()==-12 || p.pdgId()==-14 || p.pdgId()==-16) && (mom->pdgId()==24 || mom->pdgId()==-24)){
	cout<<"Found neutrino!!"<<endl;
	numNeutrinos++;
      }//end neutrino if

  //  gen_pdgId.push_back(p.pdgId());
  /**    gen_status.push_back(genIter->status());
     gen_pt.push_back(genIter->pt());
     gen_eta.push_back(genIter->eta());
     gen_phi.push_back(genIter->phi());
     gen_mass.push_back(genIter->mass());
     gen_vx.push_back(genIter->vx());
     gen_vy.push_back(genIter->vy());
     gen_vz.push_back(genIter->vz());
     gen_charge.push_back(genIter->charge());
    gen_numDaughters.push_back(genIter->numberOfDaughters());
  **/ //  mom=p.mother(0);
  //gen_mother.push_back(mom);
     /** int n = genIter->numberOfDaughters();
     for(signed j = 0; j < n; ++ j) {
       const reco::Candidate * d = genIter->daughter(j);
       d_pdgId.push_back(d->pdgId());
       d_status.push_back(d->status());
       d_pt.push_back(d->pt());
       d_eta.push_back(d->eta());
       d_phi.push_back(d->phi());
       d_mass.push_back(d->mass());
       d_charge.push_back(d->charge());
     }
  **/
     }
   /**
   iEvent.getByToken(prunedGenToken_,pruned);
   numNeutrinos=0;

   for(size_t i=0; i<pruned->size();i++){
     //     if(abs((*pruned)[i].pdgId()) > 500 && abs((*pruned)[i].pdgId()) <600){
       const reco::Candidate * prune = &(*pruned)[i];
       const pat::PackedGenParticle & p = (*packed)[i];
       if (prune->pdgId()==12 || prune->pdgId()==14 || prune->pdgId()==16 || prune->pdgId()==-12 || prune->pdgId()==-14 || prune->pdgId()==-16){
	 mom=(*packed)[i].mother(0);
	 cout<<"Mom pdgId: " <<mom->pdgId()<<endl;
	 if(mom->pdgId()==24 || mom->pdgId()==-24){
	   numNeutrinos++;
	   cout<<"Found a W!!!!!! THIS IS FUCKING AWESOME!!!" <<endl;
	 }
	 // }
     }
   }
   **/




   //std::cout << "PdgID: " << bMeson->pdgId() << " pt " << bMeson->pt() << " eta: " << bMeson->eta() << " phi: " << bMeson->phi() << std::endl;
   //  std::cout << "  found daugthers: " << std::endl;
   //  for(size_t j=0; j<packed->size();j++){
	 //get the pointer to the first survied ancestor of a given packed GenParticle in the prunedCollection
   //	 const reco::Candidate * motherInPrunedCollection = (*packed)[j].mother(0) ;

   //  }
   // }

   // }
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
   pfmett1_phi=patPFMetT1->at(0).phi();
   pfmett1_e=patPFMetT1->at(0).et();//Transverse energy
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
