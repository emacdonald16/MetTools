//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Apr  2 16:48:31 2017 by ROOT version 6.06/01
// from TTree tree/tree
// found on file: MET.root
//////////////////////////////////////////////////////////

#ifndef test_h
#define test_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

class test {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<float>   *jt_pt;
   vector<float>   *jt_eta;
   vector<float>   *jt_phi;
   vector<float>   *jt_e;
   vector<float>   *jt_ptJECUp;
   vector<float>   *jt_etaJECUp;
   vector<float>   *jt_phiJECUp;
   vector<float>   *jt_eJECUp;
   vector<float>   *jt_ptJECDown;
   vector<float>   *jt_etaJECDown;
   vector<float>   *jt_phiJECDown;
   vector<float>   *jt_eJECDown;
   Float_t         patPFMet;
   Float_t         patPFMetT1;
   Float_t         patPFMetT1_phi;
   Float_t         patPFMetT1_et;

   // List of branches
   TBranch        *b_jt_pt;   //!
   TBranch        *b_jt_eta;   //!
   TBranch        *b_jt_phi;   //!
   TBranch        *b_jt_e;   //!
   TBranch        *b_jt_ptJECUp;   //!
   TBranch        *b_jt_etaJECUp;   //!
   TBranch        *b_jt_phiJECUp;   //!
   TBranch        *b_jt_eJECUp;   //!
   TBranch        *b_jt_ptJECDown;   //!
   TBranch        *b_jt_etaJECDown;   //!
   TBranch        *b_jt_phiJECDown;   //!
   TBranch        *b_jt_eJECDown;   //!
   TBranch        *b_patPFMet;   //!
   TBranch        *b_patPFMetT1;   //!
   TBranch        *b_patPFMetT1_phi;   //!
   TBranch        *b_patPFMetT1_et;   //!

   test(TTree *tree=0);
   virtual ~test();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef test_cxx
test::test(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("TTBarFiles/MET_NuInfo.root");
      //      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("MET_new.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("TTBarFiles/MET_NuInfo.root");
	 // f = new TFile("MET_new.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("TTBarFiles/MET_NuInfo.root:/demo");
      //      TDirectory * dir = (TDirectory*)f->Get("MET_new.root:/demo");
      dir->GetObject("tree",tree);

   }
   Init(tree);
}

test::~test()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t test::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t test::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void test::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   jt_pt = 0;
   jt_eta = 0;
   jt_phi = 0;
   jt_e = 0;
   jt_ptJECUp = 0;
   jt_etaJECUp = 0;
   jt_phiJECUp = 0;
   jt_eJECUp = 0;
   jt_ptJECDown = 0;
   jt_etaJECDown = 0;
   jt_phiJECDown = 0;
   jt_eJECDown = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("jt_pt", &jt_pt, &b_jt_pt);
   fChain->SetBranchAddress("jt_eta", &jt_eta, &b_jt_eta);
   fChain->SetBranchAddress("jt_phi", &jt_phi, &b_jt_phi);
   fChain->SetBranchAddress("jt_e", &jt_e, &b_jt_e);
   fChain->SetBranchAddress("jt_ptJECUp", &jt_ptJECUp, &b_jt_ptJECUp);
   fChain->SetBranchAddress("jt_etaJECUp", &jt_etaJECUp, &b_jt_etaJECUp);
   fChain->SetBranchAddress("jt_phiJECUp", &jt_phiJECUp, &b_jt_phiJECUp);
   fChain->SetBranchAddress("jt_eJECUp", &jt_eJECUp, &b_jt_eJECUp);
   fChain->SetBranchAddress("jt_ptJECDown", &jt_ptJECDown, &b_jt_ptJECDown);
   fChain->SetBranchAddress("jt_etaJECDown", &jt_etaJECDown, &b_jt_etaJECDown);
   fChain->SetBranchAddress("jt_phiJECDown", &jt_phiJECDown, &b_jt_phiJECDown);
   fChain->SetBranchAddress("jt_eJECDown", &jt_eJECDown, &b_jt_eJECDown);
   fChain->SetBranchAddress("patPFMet", &patPFMet, &b_patPFMet);
   fChain->SetBranchAddress("patPFMetT1", &patPFMetT1, &b_patPFMetT1);
   fChain->SetBranchAddress("patPFMetT1_phi", &patPFMetT1_phi, &b_patPFMetT1_phi);
   fChain->SetBranchAddress("patPFMetT1_et", &patPFMetT1_et, &b_patPFMetT1_et);
   Notify();
}

Bool_t test::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void test::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t test::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef test_cxx
