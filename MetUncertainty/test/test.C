#define test_cxx
#include "test.h"
#include <TH2.h>
#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include <TProfile.h>
#include <TPaveStats.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TLine.h>
#include <TAxis.h>
#include <TGaxis.h>
#include <TRandom.h>
#include <TEfficiency.h>
#include <TLegend.h>
#include <TLorentzVector.h>
#include <iostream>
#include <fstream>
#include <cstdlib>


void test::Loop()
{
  if (fChain == 0) return;
  int nentries = int(fChain->GetEntries());
  int nbytes = 0, nb = 0;
  //Define hList
  // TFile* outfile = new TFile("JEC_MET_final.root", "recreate");
  // TList* hList = new TList();

  //Define variables
  double MET_pt = 0;
  double MET_phi = 0;
  double MET_et = 0;
  double jet_pt = 0;
  double jet_eta = 0;
  double jet_phi = 0;
  double jet_e = 0;
  double jetUp_pt = 0;
  double jetUp_eta = 0;
  double jetUp_phi = 0;
  double jetUp_e = 0;
  double jetDown_pt = 0;
  double jetDown_eta = 0;
  double jetDown_phi = 0;
  double jetDown_e = 0;
  double newMETUp = 0;
  double newMETDown = 0;
  double newMETUp_phi = 0;
  double newMETDown_phi = 0;
  TLorentzVector MET;
  TLorentzVector MET_corrUp;
  TLorentzVector MET_corrDown;
  TLorentzVector jet;
  TLorentzVector jetUp;
  TLorentzVector jetDown;
  TLorentzVector sumUp(0,0,0,0);
  TLorentzVector sumDown(0,0,0,0);

  double diffMetUp;
  double diffMetDown;
  float bins[]={0,15,23,30,37,45,54,66,83,111,200};
  int binnum = 10;

  //Define histograms
  TH1F *MET1 = new TH1F("Met1","MET; pfMetT1 (GeV);Events", 505, -5,500);
  TH1F *MET2 = new TH1F("Met2","MET > 20 GeV; pfMetT1 (GeV);Events", 505, -5,500);
  TH1F *METUp2 = new TH1F("MetUp2","MetUp > 20 GeV; pfMetT1JECUp (GeV);Events", 505, -5,500);
  TH1F *METDown2 = new TH1F("MetDown2","MetDown > 20 GeV; pfMetT1JECDown (GeV);Events", 505, -5,500);
  TH2F *MET2DUp = new TH2F("MET2DUp","pfMetT1JECUp; MET(GeV);MET-MET_{corr,Up}",30, 0,400,20,-20,20);
  TH2F *MET2DDown = new TH2F("MET2DDown","pfMetT1JECDown; MET(GeV);MET-MET_{corr,Down}",30, 0,400,20,-20,20);
  TH1F *METUp = new TH1F("MetUp","MetUp; pfMetT1JECUp (GeV);Events", 505, -5,500);
  TH1F *METDown = new TH1F("MetDown","MetDown; pfMetT1JECDown (GeV);Events", 505, -5,500);


  //Absolute MET
  //TH1F *MET10Up = new TH1F("Met10Up","#DeltaMET: 10 #leq MET < 20 GeV; pfMetT1JECUp - pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET20Up = new TH1F("Met20Up","#DeltaMET: 20 #leq MET < 100 GeV; pfMetT1JECUp - pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET100Up = new TH1F("Met100Up","#DeltaMET: 100 #leq MET < 200 GeV; pfMetT1JECUp - pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET200Up = new TH1F("Met200Up","#DeltaMET: MET #geq 200 GeV; pfMetT1JECUp - pfMetT1 (GeV);Events", 500, -15,15);

  //TH1F *MET10Down = new TH1F("Met10Down","#DeltaMET: 10 #leq MET < 20 GeV; pfMetT1JECDown - pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET20Down = new TH1F("Met20Down","#DeltaMET: 20 #leq MET < 100 GeV; pfMetT1JECDown - pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET100Down = new TH1F("Met100Down","#DeltaMET: 100 #leq MET < 200 GeV; pfMetT1JECDown - pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET200Down = new TH1F("Met200Down","#DeltaMET: MET #geq 200 GeV; pfMetT1JECDown - pfMetT1 (GeV);Events", 500, -15,15);

  TH1F *METallUp = new TH1F("MetallUp","#DeltaMET; pfMetT1JECUp - pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *METallDown = new TH1F("MetallDown","#DeltaMET; pfMetT1JECDown - pfMetT1 (GeV);Events", 500, -15,15);

  //Change in MET_phi
  TH1F *METUp_phi20 = new TH1F("MetUp_phi20","#Delta#phi_{MET}: 20 #leq MET < 100 GeV; #phi_{MET} - #phi_{MET,corr};Events", 500, -3.15,3.15);
  TH1F *METUp_phi200 = new TH1F("MetUp_phi200","#Delta#phi_{MET}: MET #geq 200 GeV; #phi_{MET} - #phi_{MET,corr};Events", 500, -3.15,3.15);
  TH1F *METDown_phi20 = new TH1F("MetDown_phi20","#Delta#phi_{MET}: 20 #leq MET < 100 GeV; #phi_{MET} - #phi_{MET,corr};Events", 500, -3.15,3.15);
  TH1F *METDown_phi200 = new TH1F("MetDown_phi200","#Delta#phi_{MET}: MET #geq 200 GeV; #phi_{MET} - #phi_{MET,corr};Events", 500, -3.15,3.15);

  //Ricardo's 2D plots
  TH2F *METdiff20Up  = new TH2F("METdiff20Up" ,"#vec{MET}_{corr} - #vec{MET}: 20 #leq MET < 100 GeV;  MET_{x}(GeV);MET_{y}(GeV)",20, -15,15,20,-15,15);
  TH2F *METdiff200Up = new TH2F("METdiff200Up","#vec{MET}_{corr} - #vec{MET}: MET #geq 200 GeV; MET_{x}(GeV);MET_{y}(GeV)",20, -15,15,20,-15,15);
  TH2F *METdiff20Down  = new TH2F("METdiff20Down" ,"#vec{MET}_{corr} - #vec{MET}: 20 #leq MET < 100 GeV  MET_{x}(GeV);MET_{y}(GeV)",20, -15,15,20,-15,15);
  TH2F *METdiff200Down = new TH2F("METdiff200Down","#vec{MET}_{corr} - #vec{MET}: MET #geq 200 GeV; MET_{x}(GeV);MET_{y}(GeV)",20, -15,15,20,-15,15);

  //Resolution plots of mean shift
  TH1F *MET1Up = new TH1F("Met1Up","#DeltaMET: 0 < MET < 15 GeV; pfMetT1JECUp - pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET2Up = new TH1F("Met2Up","#DeltaMET: 15 #leq MET < 23 GeV; pfMetT1JECUp - pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET3Up = new TH1F("Met3Up","#DeltaMET: 23 #leq MET < 30 GeV; pfMetT1JECUp - pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET4Up = new TH1F("Met4Up","#DeltaMET: 30 #leq MET < 37 GeV; pfMetT1JECUp - pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET5Up = new TH1F("Met5Up","#DeltaMET: 37 #leq MET < 45 GeV; pfMetT1JECUp - pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET6Up = new TH1F("Met6Up","#DeltaMET: 45 #leq MET < 54 GeV; pfMetT1JECUp - pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET7Up = new TH1F("Met7Up","#DeltaMET: 54 #leq MET < 66 GeV; pfMetT1JECUp - pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET8Up = new TH1F("Met8Up","#DeltaMET: 66 #leq MET < 83 GeV; pfMetT1JECUp - pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET9Up = new TH1F("Met9Up","#DeltaMET: 83 #leq MET < 111 GeV; pfMetT1JECUp - pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET10Up = new TH1F("Met10Up","#DeltaMET: MET #geq 111 GeV; pfMetT1JECUp - pfMetT1 (GeV);Events", 500, -15,15);

  TH1F *MET1Down = new TH1F("Met1Down","#DeltaMET: 0 < MET < 15 GeV; (pfMetT1JECDown - pfMetT1)/pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET2Down = new TH1F("Met2Down","#DeltaMET: 15 #leq MET < 23 GeV; (pfMetT1JECDown - pfMetT1)/pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET3Down = new TH1F("Met3Down","#DeltaMET: 23 #leq MET < 30 GeV; (pfMetT1JECDown - pfMetT1)/pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET4Down = new TH1F("Met4Down","#DeltaMET: 30 #leq MET < 37 GeV; (pfMetT1JECDown - pfMetT1)/pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET5Down = new TH1F("Met5Down","#DeltaMET: 37 #leq MET < 45 GeV; (pfMetT1JECDown - pfMetT1)/pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET6Down = new TH1F("Met6Down","#DeltaMET: 45 #leq MET < 54 GeV; (pfMetT1JECDown - pfMetT1)/pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET7Down = new TH1F("Met7Down","#DeltaMET: 54 #leq MET < 66 GeV; (pfMetT1JECDown - pfMetT1)/pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET8Down = new TH1F("Met8Down","#DeltaMET: 66 #leq MET < 83 GeV; (pfMetT1JECDown - pfMetT1)/pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET9Down = new TH1F("Met9Down","#DeltaMET: 83 #leq MET < 111 GeV; (pfMetT1JECDown - pfMetT1)/pfMetT1 (GeV);Events", 500, -15,15);
  TH1F *MET10Down = new TH1F("Met10Down","#DeltaMET: MET #geq 111 GeV; (pfMetT1JECDown - pfMetT1)/pfMetT1 (GeV);Events", 500, -15,15);


//Relative resolution
TH1F *MET1Up_rel = new TH1F("Met1Up_rel","#DeltaMET: 0 < MET < 15 GeV; (pfMetT1JECUp - pfMetT1)/pfMetT1 (GeV);Events", 500, -15,15);
TH1F *MET2Up_rel = new TH1F("Met2Up_rel","#DeltaMET: 15 #leq MET < 23 GeV; (pfMetT1JECUp - pfMetT1)/pfMetT1 (GeV);Events", 500, -15,15);
TH1F *MET3Up_rel = new TH1F("Met3Up_rel","#DeltaMET: 23 #leq MET < 30 GeV; (pfMetT1JECUp - pfMetT1)/pfMetT1 (GeV);Events", 500, -15,15);
TH1F *MET4Up_rel = new TH1F("Met4Up_rel","#DeltaMET: 30 #leq MET < 37 GeV; (pfMetT1JECUp - pfMetT1)/pfMetT1 (GeV);Events", 500, -15,15);
TH1F *MET5Up_rel = new TH1F("Met5Up_rel","#DeltaMET: 37 #leq MET < 45 GeV; (pfMetT1JECUp - pfMetT1)/pfMetT1 (GeV);Events", 500, -15,15);
TH1F *MET6Up_rel = new TH1F("Met6Up_rel","#DeltaMET: 45 #leq MET < 54 GeV; (pfMetT1JECUp - pfMetT1)/pfMetT1 (GeV);Events", 500, -15,15);
TH1F *MET7Up_rel = new TH1F("Met7Up_rel","#DeltaMET: 54 #leq MET < 66 GeV; (pfMetT1JECUp - pfMetT1)/pfMetT1 (GeV);Events", 500, -15,15);
TH1F *MET8Up_rel = new TH1F("Met8Up_rel","#DeltaMET: 66 #leq MET < 83 GeV; (pfMetT1JECUp - pfMetT1)/pfMetT1 (GeV);Events", 500, -15,15);
TH1F *MET9Up_rel = new TH1F("Met9Up_rel","#DeltaMET: 83 #leq MET < 111 GeV; (pfMetT1JECUp - pfMetT1)/pfMetT1 (GeV);Events", 500, -15,15);
TH1F *MET10Up_rel = new TH1F("Met10Up_rel","#DeltaMET: MET #geq 111 GeV; (pfMetT1JECUp - pfMetT1)/pfMetT1 (GeV);Events", 500, -15,15);

TH1F *MET1Down_rel = new TH1F("Met1Down_rel","#DeltaMET: 0 < MET < 15 GeV; pfMetT1JECDown - pfMetT1 (GeV);Events", 500, -15,15);
TH1F *MET2Down_rel = new TH1F("Met2Down_rel","#DeltaMET: 15 #leq MET < 23 GeV; pfMetT1JECDown - pfMetT1 (GeV);Events", 500, -15,15);
TH1F *MET3Down_rel = new TH1F("Met3Down_rel","#DeltaMET: 23 #leq MET < 30 GeV; pfMetT1JECDown - pfMetT1 (GeV);Events", 500, -15,15);
TH1F *MET4Down_rel = new TH1F("Met4Down_rel","#DeltaMET: 30 #leq MET < 37 GeV; pfMetT1JECDown - pfMetT1 (GeV);Events", 500, -15,15);
TH1F *MET5Down_rel = new TH1F("Met5Down_rel","#DeltaMET: 37 #leq MET < 45 GeV; pfMetT1JECDown - pfMetT1 (GeV);Events", 500, -15,15);
TH1F *MET6Down_rel = new TH1F("Met6Down_rel","#DeltaMET: 45 #leq MET < 54 GeV; pfMetT1JECDown - pfMetT1 (GeV);Events", 500, -15,15);
TH1F *MET7Down_rel = new TH1F("Met7Down_rel","#DeltaMET: 54 #leq MET < 66 GeV; pfMetT1JECDown - pfMetT1 (GeV);Events", 500, -15,15);
TH1F *MET8Down_rel = new TH1F("Met8Down_rel","#DeltaMET: 66 #leq MET < 83 GeV; pfMetT1JECDown - pfMetT1 (GeV);Events", 500, -15,15);
TH1F *MET9Down_rel = new TH1F("Met9Down_rel","#DeltaMET: 83 #leq MET < 111 GeV; pfMetT1JECDown - pfMetT1 (GeV);Events", 500, -15,15);
TH1F *MET10Down_rel = new TH1F("Met10Down_rel","#DeltaMET: MET #geq 111 GeV; pfMetT1JECDown - pfMetT1 (GeV);Events", 500, -15,15);



  TH1F *histoFinal1 = new TH1F("histoFinal1", ";MET (GeV);#sigma_{MET} (GeV)", binnum, bins);
  TH1F *histoFinal2 = new TH1F("histoFinal2", ";MET (GeV);#sigma_{MET} (GeV)", binnum, bins);

  TH1F *histoFinal3 = new TH1F("histoFinal3", ";MET (GeV);#sigma_{MET} (GeV)", binnum, bins);
  TH1F *histoFinal4 = new TH1F("histoFinal4", ";MET (GeV);#sigma_{MET} (GeV)", binnum, bins);

  for (int jentry=0; jentry<nentries;jentry++) {//Over all entries
    GetEntry(jentry);
    int ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    MET_pt = patPFMetT1;
    MET_phi = patPFMetT1_phi;
    MET_et = patPFMetT1_et;
    MET.SetPtEtaPhiE(MET_pt,0,MET_phi,MET_et);

    for ( unsigned j=0; j<jt_pt->size(); j++){//Over all jets
      jet_pt=jt_pt->at(j); jet_eta=jt_eta->at(j); jet_phi=jt_phi->at(j); jet_e=jt_e->at(j);
      jetUp_pt=jt_ptJECUp->at(j); jetUp_eta=jt_etaJECUp->at(j); jetUp_phi=jt_phiJECUp->at(j); jetUp_e=jt_eJECUp->at(j);
      jetDown_pt=jt_ptJECDown->at(j); jetDown_eta=jt_etaJECDown->at(j); jetDown_phi=jt_phiJECDown->at(j); jetDown_e=jt_eJECDown->at(j);

      jet.SetPtEtaPhiE(jet_pt, jet_eta, jet_phi, jet_e);
      jetUp.SetPtEtaPhiE(jetUp_pt, jetUp_eta, jetUp_phi, jetUp_e);
      jetDown.SetPtEtaPhiE(jetDown_pt, jetDown_eta, jetDown_phi, jetDown_e);
      TLorentzVector diffUp = jet - jetUp;
      TLorentzVector diffDown = jet - jetDown;
      sumUp+=diffUp;
      sumDown+=diffDown;

    }//end per jet
    MET_corrUp = MET + sumUp;
    MET_corrDown= MET + sumDown;
    diffMetUp = MET_corrUp.Pt()-MET.Pt();
    diffMetDown = MET_corrDown.Pt()-MET.Pt();


    //Fill histograms
    MET1->Fill(MET.Pt());
    METUp->Fill(MET_corrUp.Pt());
    METDown->Fill(MET_corrDown.Pt());
    METallUp->Fill(diffMetUp);
    METallDown->Fill(diffMetDown);
    //diffMetUp = diffMetUp*100.0;
    //diffMetDown = diffMetDown*100.0;

    if (MET_pt>0 && MET_pt<15) {MET1Up->Fill(diffMetUp);MET1Down->Fill(diffMetDown); MET1Up_rel->Fill(diffMetUp/MET_pt);MET1Down_rel->Fill(diffMetDown/MET_pt);}
    else if (MET_pt>=15 && MET_pt<23) {MET2Up->Fill(diffMetUp);MET2Down->Fill(diffMetDown); MET2Up_rel->Fill(diffMetUp/MET_pt);MET2Down_rel->Fill(diffMetDown/MET_pt);}
    else if (MET_pt>=23 && MET_pt<30) {MET3Up->Fill(diffMetUp);MET3Down->Fill(diffMetDown); MET3Up_rel->Fill(diffMetUp/MET_pt);MET3Down_rel->Fill(diffMetDown/MET_pt);}
    else if (MET_pt>=30 && MET_pt<37) {MET4Up->Fill(diffMetUp);MET4Down->Fill(diffMetDown); MET4Up_rel->Fill(diffMetUp/MET_pt);MET4Down_rel->Fill(diffMetDown/MET_pt);}
    else if (MET_pt>=37 && MET_pt<45) {MET5Up->Fill(diffMetUp);MET5Down->Fill(diffMetDown); MET5Up_rel->Fill(diffMetUp/MET_pt);MET5Down_rel->Fill(diffMetDown/MET_pt);}
    else if (MET_pt>=45 && MET_pt<54) {MET6Up->Fill(diffMetUp);MET6Down->Fill(diffMetDown); MET6Up_rel->Fill(diffMetUp/MET_pt);MET6Down_rel->Fill(diffMetDown/MET_pt);}
    else if (MET_pt>=54 && MET_pt<66) {MET7Up->Fill(diffMetUp);MET7Down->Fill(diffMetDown); MET7Up_rel->Fill(diffMetUp/MET_pt);MET7Down_rel->Fill(diffMetDown/MET_pt);}
    else if (MET_pt>=66 && MET_pt<83) {MET8Up->Fill(diffMetUp);MET8Down->Fill(diffMetDown); MET8Up_rel->Fill(diffMetUp/MET_pt);MET8Down_rel->Fill(diffMetDown/MET_pt);}
    else if (MET_pt>=83 && MET_pt<111) {MET9Up->Fill(diffMetUp);MET9Down->Fill(diffMetDown); MET9Up_rel->Fill(diffMetUp/MET_pt);MET9Down_rel->Fill(diffMetDown/MET_pt);}
    else if (MET_pt>=111) {MET10Up->Fill(diffMetUp);MET10Down->Fill(diffMetDown); MET10Up_rel->Fill(diffMetUp/MET_pt);MET10Down_rel->Fill(diffMetDown/MET_pt);}

    sumUp.SetPtEtaPhiE(0,0,0,0);
    sumDown.SetPtEtaPhiE(0,0,0,0);
  }//end per entry

  // const int nq1 = 100000;
  // double xq1[nq1]; // position where to compute the quantiles in [0,1]
  // double yq1[nq1]; // array to contain the quantiles
  // for (int i=0;i<nq1;i++) xq1[i] = float(i+1)/nq1;
  //
  // MET1->GetQuantiles(nq1,yq1,xq1);
  // cout<<"10\%: "<<yq1[10000]<<", 20\%: "<<yq1[20000]<<", 30\%: "<<yq1[30000]<<", 40\%: "<<yq1[40000]<<", 50\%: "<<yq1[50000]
  // <<", 60\%: "<<yq1[60000]<<", 70\%: "<<yq1[70000]<<", 80\%: "<<yq1[80000]<<", 90\%: "<<yq1[90000]<<endl;

  double mean1a = MET1Up->GetMean(); double error1a = MET1Up->GetRMS();   double mean1b = MET1Down->GetMean(); double error1b = MET1Down->GetRMS();
  double mean2a = MET2Up->GetMean(); double error2a = MET2Up->GetRMS();   double mean2b = MET2Down->GetMean(); double error2b = MET2Down->GetRMS();
  double mean3a = MET3Up->GetMean(); double error3a = MET3Up->GetRMS();   double mean3b = MET3Down->GetMean(); double error3b = MET3Down->GetRMS();
  double mean4a = MET4Up->GetMean(); double error4a = MET4Up->GetRMS();   double mean4b = MET4Down->GetMean(); double error4b = MET4Down->GetRMS();
  double mean5a = MET5Up->GetMean(); double error5a = MET5Up->GetRMS();   double mean5b = MET5Down->GetMean(); double error5b = MET5Down->GetRMS();
  double mean6a = MET6Up->GetMean(); double error6a = MET6Up->GetRMS();   double mean6b = MET6Down->GetMean(); double error6b = MET6Down->GetRMS();
  double mean7a = MET7Up->GetMean(); double error7a = MET7Up->GetRMS();   double mean7b = MET7Down->GetMean(); double error7b = MET7Down->GetRMS();
  double mean8a = MET8Up->GetMean(); double error8a = MET8Up->GetRMS();   double mean8b = MET8Down->GetMean(); double error8b = MET8Down->GetRMS();
  double mean9a = MET9Up->GetMean(); double error9a = MET9Up->GetRMS();   double mean9b = MET9Down->GetMean(); double error9b = MET9Down->GetRMS();
  double mean10a = MET10Up->GetMean(); double error10a = MET10Up->GetRMS();   double mean10b = MET10Down->GetMean(); double error10b = MET10Down->GetRMS();

  double mean1c = MET1Up_rel->GetMean(); double error1c = MET1Up_rel->GetRMS();   double mean1d = MET1Down_rel->GetMean(); double error1d = MET1Down_rel->GetRMS();
  double mean2c = MET2Up_rel->GetMean(); double error2c = MET2Up_rel->GetRMS();   double mean2d = MET2Down_rel->GetMean(); double error2d = MET2Down_rel->GetRMS();
  double mean3c = MET3Up_rel->GetMean(); double error3c = MET3Up_rel->GetRMS();   double mean3d = MET3Down_rel->GetMean(); double error3d = MET3Down_rel->GetRMS();
  double mean4c = MET4Up_rel->GetMean(); double error4c = MET4Up_rel->GetRMS();   double mean4d = MET4Down_rel->GetMean(); double error4d = MET4Down_rel->GetRMS();
  double mean5c = MET5Up_rel->GetMean(); double error5c = MET5Up_rel->GetRMS();   double mean5d = MET5Down_rel->GetMean(); double error5d = MET5Down_rel->GetRMS();
  double mean6c = MET6Up_rel->GetMean(); double error6c = MET6Up_rel->GetRMS();   double mean6d = MET6Down_rel->GetMean(); double error6d = MET6Down_rel->GetRMS();
  double mean7c = MET7Up_rel->GetMean(); double error7c = MET7Up_rel->GetRMS();   double mean7d = MET7Down_rel->GetMean(); double error7d = MET7Down_rel->GetRMS();
  double mean8c = MET8Up_rel->GetMean(); double error8c = MET8Up_rel->GetRMS();   double mean8d = MET8Down_rel->GetMean(); double error8d = MET8Down_rel->GetRMS();
  double mean9c = MET9Up_rel->GetMean(); double error9c = MET9Up_rel->GetRMS();   double mean9d = MET9Down_rel->GetMean(); double error9d = MET9Down_rel->GetRMS();
  double mean10c = MET10Up_rel->GetMean(); double error10c = MET10Up_rel->GetRMS();   double mean10d = MET10Down_rel->GetMean(); double error10d = MET10Down_rel->GetRMS();

  double mean1a_array[10]={mean1a,mean2a,mean3a,mean4a,mean5a,mean6a,mean7a,mean8a,mean9a,mean10a};
  double mean1b_array[10]={mean1b,mean2b,mean3b,mean4b,mean5b,mean6b,mean7b,mean8b,mean9b,mean10b};
  double error1a_array[10]={error1a,error2a,error3a,error4a,error5a,error6a,error7a,error8a,error9a,error10a};
  double error1b_array[10]={error1b,error2b,error3b,error4b,error5b,error6b,error7b,error8b,error9b,error10b};

  double mean1c_array[10]={mean1c,mean2c,mean3c,mean4c,mean5c,mean6c,mean7c,mean8c,mean9c,mean10c};
  double mean1d_array[10]={mean1d,mean2d,mean3d,mean4d,mean5d,mean6d,mean7d,mean8d,mean9d,mean10d};
  double error1c_array[10]={error1c,error2c,error3c,error4c,error5c,error6c,error7c,error8c,error9c,error10c};
  double error1d_array[10]={error1d,error2d,error3d,error4d,error5d,error6d,error7d,error8d,error9d,error10d};

  for(int i=1;i<=10;i++){
    histoFinal1->SetBinContent(i,mean1a_array[i-1]);
    histoFinal1->SetBinError(i,error1a_array[i-1]);
    histoFinal2->SetBinContent(i,mean1b_array[i-1]);
    histoFinal2->SetBinError(i,error1b_array[i-1]);

    histoFinal3->SetBinContent(i,mean1c_array[i-1]);
    histoFinal3->SetBinError(i,error1c_array[i-1]);
    histoFinal4->SetBinContent(i,mean1d_array[i-1]);
    histoFinal4->SetBinError(i,error1d_array[i-1]);
  }

  //Line color and legend
  METUp->SetLineColor(kRed+1);
  METUp->SetLineWidth(4);
  MET10Up->SetLineColor(kRed+1);
  MET20Up->SetLineColor(kRed+1);
  MET100Up->SetLineColor(kRed+1);
  MET200Up->SetLineColor(kRed+1);
  METUp_phi20->SetLineColor(kRed+1);
  METUp_phi200->SetLineColor(kRed+1);

  METDown->SetLineColor(kAzure-4);
  METDown->SetLineWidth(4);
  MET10Down->SetLineColor(kAzure-4);
  MET20Down->SetLineColor(kAzure-4);
  MET100Down->SetLineColor(kAzure-4);
  MET200Down->SetLineColor(kAzure-4);
  METDown_phi20->SetLineColor(kAzure-4);
  METDown_phi200->SetLineColor(kAzure-4);
  TLegend *leg1 = new TLegend(0.13,0.73,0.4,0.9);
  leg1->SetTextSize(0.05);
  leg1->AddEntry(METUp,"JECUp","l");
  leg1->AddEntry(METDown,"JECDown","l");

  TCanvas *cFinalRes = new TCanvas("cFinalRes","cFinalRes", 800,600);
  histoFinal1->SetTitle("Mean shift in MET: MET_{corr} - MET");
  histoFinal1->SetMaximum(5);
  histoFinal1->SetMinimum(-5);
  histoFinal1->GetYaxis()->SetTitle("Shift in MET (GeV)");
  histoFinal1->GetXaxis()->SetTitle("trueMET (GeV)");
  histoFinal1->SetStats(0);//JECUp
  histoFinal1->SetMarkerStyle(8);
  histoFinal1->SetMarkerSize(0.7);
  histoFinal1->SetMarkerColor(kRed+1);
  histoFinal1->SetLineColor(kRed+1);
  histoFinal1->Draw();

  histoFinal2->SetStats(0);//JECDown
  histoFinal2->SetMarkerStyle(8);
  histoFinal2->SetMarkerSize(0.7);
  histoFinal2->SetMarkerColor(kAzure-4);
  histoFinal2->SetLineColor(kAzure-4);
  histoFinal2->Draw("SAME");
  leg1->Draw("SAME");
  cFinalRes->SaveAs("res_METshift.root");

  TCanvas *cFinalRes_rel = new TCanvas("cFinalRes_rel","cFinalRes_rel", 800,600);
  histoFinal3->SetTitle("Relative shift in MET: (MET_{corr} - MET)/MET");
  histoFinal3->SetMaximum(1);
  histoFinal3->SetMinimum(-1);
  histoFinal3->GetYaxis()->SetTitle("Shift in MET (\%)");
  histoFinal3->GetXaxis()->SetTitle("trueMET (GeV)");
  histoFinal3->SetStats(0);//JECUp
  histoFinal3->SetMarkerStyle(8);
  histoFinal3->SetMarkerSize(0.7);
  histoFinal3->SetMarkerColor(kRed+1);
  histoFinal3->SetLineColor(kRed+1);
  histoFinal3->Scale(100);
  histoFinal3->Draw();

  histoFinal4->SetStats(0);//JECDown
  histoFinal4->SetMarkerStyle(8);
  histoFinal4->SetMarkerSize(0.7);
  histoFinal4->SetMarkerColor(kAzure-4);
  histoFinal4->SetLineColor(kAzure-4);
  histoFinal4->Scale(100);

  histoFinal4->Draw("SAME");
  leg1->Draw("SAME");
  cFinalRes_rel->SaveAs("resRel_METshift.root");



  /**
  TCanvas *cDiff10 = new TCanvas("cDiff10","cDiff10", 800, 600);
  cDiff10->SetLogy();
  gStyle->SetOptStat("rm");
  MET10Up->Draw();
  cDiff10->Update();
  TPaveStats *ps1 = (TPaveStats*)MET10Up->GetListOfFunctions()->FindObject("stats");
  ps1->SetTextColor(kRed+1);
  ps1->SetX1NDC(0.7); ps1->SetX2NDC(0.9); ps1->SetY1NDC(0.8); ps1->SetY2NDC(0.9);
  cDiff10->Modified();
  MET10Down->Draw("SAMES");
  cDiff10->Update();
  TPaveStats *ps2 = (TPaveStats*)MET10Down->GetListOfFunctions()->FindObject("stats");
  ps2->SetX1NDC(0.7); ps2->SetX2NDC(0.9); ps2->SetY1NDC(0.7); ps2->SetY2NDC(0.8);
  ps2->SetTextColor(kAzure-4);
  leg1->Draw("SAME");
  cDiff10->SaveAs("absMET10.root");

  TCanvas *cDiff20 = new TCanvas("cDiff20","cDiff20", 800, 600);
  cDiff20->SetLogy();
  gStyle->SetOptStat("rm");
  MET20Up->Draw();
  cDiff20->Update();
  TPaveStats *ps3 = (TPaveStats*)MET20Up->GetListOfFunctions()->FindObject("stats");
  ps3->SetTextColor(kRed+1);
  ps3->SetX1NDC(0.7); ps3->SetX2NDC(0.9); ps3->SetY1NDC(0.8); ps3->SetY2NDC(0.9);
  cDiff20->Modified();
  MET20Down->Draw("SAMES");
  cDiff20->Update();
  TPaveStats *ps4 = (TPaveStats*)MET20Down->GetListOfFunctions()->FindObject("stats");
  ps4->SetX1NDC(0.7); ps4->SetX2NDC(0.9); ps4->SetY1NDC(0.7); ps4->SetY2NDC(0.8);
  ps4->SetTextColor(kAzure-4);
  leg1->Draw("SAME");
  cDiff20->SaveAs("absMET20.root");

  TCanvas *cDiff100 = new TCanvas("cDiff100","cDiff100", 800, 600);
  cDiff100->SetLogy();
  gStyle->SetOptStat("rm");
  MET100Up->Draw();
  cDiff100->Update();
  TPaveStats *ps5 = (TPaveStats*)MET100Up->GetListOfFunctions()->FindObject("stats");
  ps5->SetTextColor(kRed+1);
  ps5->SetX1NDC(0.7); ps5->SetX2NDC(0.9); ps5->SetY1NDC(0.8); ps5->SetY2NDC(0.9);
  cDiff100->Modified();
  MET100Down->Draw("SAMES");
  cDiff100->Update();
  TPaveStats *ps6 = (TPaveStats*)MET100Down->GetListOfFunctions()->FindObject("stats");
  ps6->SetX1NDC(0.7); ps6->SetX2NDC(0.9); ps6->SetY1NDC(0.7); ps6->SetY2NDC(0.8);
  ps6->SetTextColor(kAzure-4);
  leg1->Draw("SAME");
  cDiff100->SaveAs("absMET100.root");

  TCanvas *cDiff200 = new TCanvas("cDiff200","cDiff200", 800, 600);
  cDiff200->SetLogy();
  gStyle->SetOptStat("rm");
  MET200Up->Draw();
  cDiff200->Update();
  TPaveStats *ps7 = (TPaveStats*)MET200Up->GetListOfFunctions()->FindObject("stats");
  ps7->SetTextColor(kRed+1);
  ps7->SetX1NDC(0.7); ps7->SetX2NDC(0.9); ps7->SetY1NDC(0.8); ps7->SetY2NDC(0.9);
  cDiff200->Modified();
  MET200Down->Draw("SAMES");
  cDiff200->Update();
  TPaveStats *ps8 = (TPaveStats*)MET200Down->GetListOfFunctions()->FindObject("stats");
  ps8->SetX1NDC(0.7); ps8->SetX2NDC(0.9); ps8->SetY1NDC(0.7); ps8->SetY2NDC(0.8);
  ps8->SetTextColor(kAzure-4);
  leg1->Draw("SAME");
  cDiff200->SaveAs("absMET200.root");

  TCanvas *cPhi20 = new TCanvas("cPhi20","cPhi20", 800, 600);
  cPhi20->SetLogy();
  gStyle->SetOptStat("rm");
  METUp_phi20->Draw();
  cPhi20 ->Update();
  TPaveStats *ps9 = (TPaveStats*)METUp_phi20->GetListOfFunctions()->FindObject("stats");
  ps9->SetTextColor(kRed+1);
  ps9->SetX1NDC(0.7); ps9->SetX2NDC(0.9); ps9->SetY1NDC(0.8); ps9->SetY2NDC(0.9);
  cPhi20 ->Modified();
  METDown_phi20->Draw("SAMES");
  cPhi20 ->Update();
  TPaveStats *ps10 = (TPaveStats*)METDown_phi20->GetListOfFunctions()->FindObject("stats");
  ps10->SetX1NDC(0.7); ps10->SetX2NDC(0.9); ps10->SetY1NDC(0.7); ps10->SetY2NDC(0.8);
  ps10->SetTextColor(kAzure-4);
  leg1->Draw("SAME");
  cPhi20 ->SaveAs("Phi20.root");

  TCanvas *cPhi200 = new TCanvas("cPhi200","cPhi200", 800, 600);
  cPhi200->SetLogy();
  gStyle->SetOptStat("rm");
  METUp_phi200->Draw();
  cPhi200 ->Update();
  TPaveStats *ps11 = (TPaveStats*)METUp_phi200->GetListOfFunctions()->FindObject("stats");
  ps11->SetTextColor(kRed+1);
  ps11->SetX1NDC(0.7); ps11->SetX2NDC(0.9); ps11->SetY1NDC(0.8); ps11->SetY2NDC(0.9);
  cPhi200 ->Modified();
  METDown_phi200->Draw("SAMES");
  cPhi200 ->Update();
  TPaveStats *ps12 = (TPaveStats*)METDown_phi200->GetListOfFunctions()->FindObject("stats");
  ps12->SetX1NDC(0.7); ps12->SetX2NDC(0.9); ps12->SetY1NDC(0.7); ps12->SetY2NDC(0.8);
  ps12->SetTextColor(kAzure-4);
  leg1->Draw("SAME");
  cPhi200 ->SaveAs("Phi200.root");

  TCanvas *cMETdiff20Up = new TCanvas("cMETdiff20Up","cMETdiff20Up", 800,600);
  cMETdiff20Up->SetLogz();
  METdiff20Up->Draw("colz");
  TCanvas *cMETdiff200Up = new TCanvas("cMETdiff200Up","cMETdiff200Up", 800,600);
  cMETdiff200Up->SetLogz();
  METdiff200Up->Draw("colz");
  TCanvas *cMETdiff20Down = new TCanvas("cMETdiff20Down","cMETdiff20Down", 800,600);
  cMETdiff20Down->SetLogz();
  METdiff20Down->Draw("colz");
  TCanvas *cMETdiff200Down = new TCanvas("cMETdiff200Down","cMETdiff200Down", 800,600);
  cMETdiff200Down->SetLogz();
  METdiff200Down->Draw("colz");

  cMETdiff20Up->SaveAs("METdiff20Up.root");
  cMETdiff200Up->SaveAs("METdiff200Up.root");
  cMETdiff20Down->SaveAs("METdiff20Down.root");
  cMETdiff200Down->SaveAs("METdiff200Down.root");
  **/



  // hList->Write();
  // outfile->Close();
}//end loop
