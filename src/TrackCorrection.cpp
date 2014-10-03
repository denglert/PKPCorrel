#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TNtuple.h>
#include <iostream>
#include <deque>
#include <TLorentzVector.h>
//#include "AnalysisFW.h"
#include "../HiForestAnalysis/hiForest.h"
#include "AnalysisBinning.h"
#include "PIDUtils.h"
//#include "SetupCustomTrackTree.h"
#include "dataType.h"
// #include "stdlib.h"
// #include <iostream>
// #include <fstream>


int main( int argc, const char *argv[] )
{


  if(argc != 5)
  {
    std::cerr << "Usage: process <.root file to be preprocessed> <tag> <nEvents>" << std::endl;
	 exit(1);
  }

 
 std::string inpFilename    = argv[1];
 std::string str_sampleType = argv[2];
 std::string tag		       = argv[3];
 int nEvMax 	  		       = atoi( argv[4] );
 //TString inpFilename = "../";
 //
 
 sampleType sType = str2enumSampleTyp(str_sampleType);
 
 // Binning
 int nCorrTyp = nCorrTyp_; 
 int *nPtBins = new int[nCorrTyp_];

 for(int TypBin = 0; TypBin < nCorrTyp; TypBin++)
 { nPtBins[TypBin] = nPtBins_[TypBin]; }

 int nMultiplicityBins_Ana = nMultiplicityBins_Ana_HDR;
 int nMultiplicityBins_EvM = nMultiplicityBins_EvM_HDR;
 int nZvtxBins 		      = nZvtxBins_; 

 //////////////////////////////////////
 //                                  //
 // ****** Opening input file ****** //
 //                                  //
 //////////////////////////////////////

 // Open file
 TFile *f = TFile::Open(inpFilename.c_str());
 // TFile *f = new TFile(inpFilename, "READ");
 if ( f->IsZombie() ) {std::cerr << "Error opening file: " << inpFilename << std::endl; exit(-1);}

// // trackTree
// //TTree *trackTree = (TTree*)f->Get("pptracks/trackTree");
// TTree *trackTree = (TTree*)f->Get("ppTrack/trackTree");
// Tracks tTracks;
// bool doCheck = true;
// setupTrackTree(trackTree, tTracks, doCheck);
//
// // hiEvtAnalyzer
// TTree *EvtAna= (TTree*)f->Get("hiEvtAnalyzer/HiTree");
// int hiNtracks; EvtAna->SetBranchAddress("hiNtracks", &hiNtracks);
// float vz; EvtAna->SetBranchAddress("vz", &vz);
//
// // skimanalysis for event selection
// TTree *SkimAna= (TTree*)f->Get("skimanalysis/HltTree");
// int pPAcollisionEventSelection; SkimAna->SetBranchAddress("pPAcollisionEventSelectionPA", &pPAcollisionEventSelection);
// int pileUpBit;                  SkimAna->SetBranchAddress("pVertexFilterCutGplus", &pileUpBit);

 ////////////////////////////////
 //                            //
 // ***** Setting output ***** //
 //                            //
 ////////////////////////////////
 
 TFile *output = new TFile(Form("./trkCorrections_%s.root", tag.c_str() ),"RECREATE");
 output->cd();

 //////////////////////////////
 //                          //
 // ***** Initializing ***** //
 //                          //
 //////////////////////////////

  Bool_t montecarlo = isMonteCarlo(sType);
  Bool_t hi = isHI(sType);

  int PId = 211;

  std::cout << "sampleType: " << sType << std::endl;
  std::cout << "montecarlo: " << montecarlo << std::endl;

  collisionType cType = getCType(sType);


  double bin_pt_min = 0.2;
  double bin_pt_max = 50;
  const int nx=20;
  double x[nx+1];
  double inix=log(bin_pt_min)/log(10);
  double delta=(log(bin_pt_max)-log(bin_pt_min))/(nx*log(10));
  for(int ix=0; ix<nx+1;ix++)
  {
   x[ix]=pow(10,inix);
   inix+=delta;
  } 
  
  int neta = 20;
  double eta_min = -2.4;
  double eta_max =  2.4;
  double deta=(eta_max-eta_min)/((double)neta);
  double etaval[neta+1];
  for(int ieta = 0; ieta<neta+1; ieta++)
  { etaval[ieta]=eta_min+((double)ieta)*deta; }
  
  int nphi = 20;
  double phi_min = -2.4;
  double phi_max =  2.4;
  double dphi=(phi_max-phi_min)/((double)nphi);
  double phival[nphi+1];
  for(int iphi=0; iphi<nphi+1; iphi++)
  { phival[iphi]=phi_min+((double)iphi)*dphi; }
  
  TH3D * hfake = new TH3D("hfake",";p_{T};#eta;#phi",nx,x,neta,etaval,nphi,phival);
  TH3D * hreco = new TH3D("hreco",";p_{T};#eta;#phi",nx,x,neta,etaval,nphi,phival);
  TH3D * hsecondary = new TH3D("hsecondary",";p_{T};#eta;#phi",nx,x,neta,etaval,nphi,phival);
  TH3D * hreal = new TH3D("hreal",";p_{T};#eta;#phi",nx,x,neta,etaval,nphi,phival);
  TH3D * hgen = new TH3D("hgen",";p_{T};#eta;#phi",nx,x,neta,etaval,nphi,phival);
  TH3D * hmatched = new TH3D("hmatched",";p_{T};#eta;#phi",nx,x,neta,etaval,nphi,phival);
  TH3D * heff = new TH3D("heff",";p_{T};#eta;#phi",nx,x,neta,etaval,nphi,phival);
  TH3D * hmultrec = new TH3D("hmultrec",";p_{T};#eta;#phi",nx,x,neta,etaval,nphi,phival);

  HiForest *c = new HiForest( inpFilename.c_str(), "Forest", cType, montecarlo);
  c->InitTree();
  c->LoadNoTrees();
  c->hasSkimTree = true;
  c->hasEvtTree = true;
  c->hasTrackTree = true;

  Float_t meanVz = 0;
  
  //This part needs to be checked for the MC production you will use
  if(sType == kHIMC){
    c->hasGenParticleTree = true;
    //mean mc .16458, mean data -.337
    meanVz = .16458 + .337;
  }
  else if(sType == kPPMC){
    c->hasGenParticleTree = true;
    //MC vz = .4205,  Data vz = .6953
    meanVz = .4205 - .6953;
  }
  
  Long64_t nentries = nEvMax; 


  Int_t totEv = 0;
  Int_t selectCut = 0;
  Int_t vzCut = 0;

 ///////////////////////////////////////
 //                                   //
 // ***** Calculate corrections ***** //
 //                                   //
 ///////////////////////////////////////

  // Event loop
  if (nEvMax == -1) {if(!hi)
    nentries = c->skimTree->GetEntries();
  else
    nentries = c->GetEntries();}
  std::cout << "nentries = "<<nentries << std::endl;
  for(Long64_t jentry = 0; jentry < nentries; jentry++)
  {
    c->GetEntry(jentry);
    
    totEv++;

    if(jentry%1000 == 0)
      std::cout << jentry << std::endl;

    if( !c->selectEvent() )
	 {
      selectCut++;
      continue;
    }

    if( TMath::Abs(c->evt.vz - meanVz) > 15)
	 {
      vzCut++;
      continue;
    }

	 // Track loop
    for(int itrk=0; itrk<(c->track.nTrk) ;itrk++)
	 {
				
      double pt=c->track.trkPt[itrk];
      double eta=c->track.trkEta[itrk]; 
      double phi=c->track.trkPhi[itrk];

		// Debuggg 
		std::cerr << "pt: "  << pt << std::endl;
		std::cerr << "eta: " << eta << std::endl;

		// Track selection
      if( fabs(eta)>2.4) continue;
      if(pt<bin_pt_min) continue;
      if(!(c->track.highPurity[itrk] && fabs(c->track.trkDxy1[itrk]/c->track.trkDxyError1[itrk])<3.0 && fabs(c->track.trkDz1[itrk]/c->track.trkDzError1[itrk])<3 && (c->track.trkPtError[itrk]/c->track.trkPt[itrk])<0.1)) continue;
      //You should also require the additional cuts that you apply to choose a given PID
		
		// Debuggg 
		std::cerr << "filled. " << std::endl;

      if(c->track.trkFake){
       hfake->Fill(pt,eta,phi);
      }else{
       hreal->Fill(pt,eta,phi);
       if(c->track.trkStatus[itrk]<0) hsecondary->Fill(pt,eta,phi);
      }
      hreco->Fill(pt,eta,phi);
    }

	 // Particle loop
    for(int itrk=0;itrk<(c->track.nParticle);itrk++)
	 {
      double pt=c->track.pPt[itrk];
      double eta=c->track.pEta[itrk];
      double phi=c->track.pPhi[itrk];

		// particle selection
      if(fabs(eta)>2.4) continue;
      if(pt<bin_pt_min) continue;
      if(fabs(c->track.pPId[itrk])!=PId) continue; 
      hgen->Fill(pt,eta,phi);
      if(!(c->track.mtrkQual[itrk] && fabs(c->track.mtrkDxy1[itrk]/c->track.mtrkDxyError1[itrk])<3.0 && fabs(c->track.mtrkDz1[itrk]/c->track.mtrkDzError1[itrk])<3 && (c->track.mtrkPtError[itrk]/c->track.mtrkPt[itrk])<0.1)) continue;

      hmatched->Fill(pt,eta,phi);
      hmultrec->Fill(pt,eta,phi,c->track.pNRec[itrk]);
    }


  }
  
  hfake->Divide(hreco);
  hsecondary->Divide(hreal);
  heff=(TH3D*)hmatched->Clone("heff");
  heff->Divide(hgen);
  hmultrec->Divide(hmatched);

 //////////////////////
 //                  //
 // **** OUTPUT **** //
 //                  //
 //////////////////////
  
  output->cd();
  
  heff->Write();
  hfake->Write();
  hmultrec->Write();
  hsecondary->Write();
  
  delete c;
  output->Close();
  delete output;

  printf("Done.\n");
}
