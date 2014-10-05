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

TH3D** Setup_TH3D_nCorrTyp(const char histoname[], const char histolabel[], int nXBins, double xbins, int nYBins, double ybins, int nZBins, double zbins )
{
	int nPart = 4;
	TH3D *histos[nPart];

	for( int i = 0; i < nPart; i++)
	{
		 histos[i] = new TH3D(Form("%s part %d", histoname, i), histolabel, nXBins, xbins, nYBins, ybins, nZBins, nZBins);
	}

	return histos;
	
}

  TH3D *hmatched   = new TH3D("hmatched",";p_{T};#eta;#phi",  nx,x,neta,etaval,nphi,phival);

int main( int argc, const char *argv[] )
{

  if(argc != 5)
  {
    std::cerr << "Usage: TrackCorrection <.root file to be preprocessed> <sample type> <tag> <nEvents>" << std::endl;
	 exit(1);
  }

 std::string inpFilename    = argv[1];
 std::string str_sampleType = argv[2];
 std::string tag		       = argv[3];
 int nEvMax 	  		       = atoi( argv[4] );
 //TString inpFilename = "../";
 
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

 // tTracksTree
 //TTree *tTracksTree = (TTree*)f->Get("pptTrackss/tTracksTree");
 TTree *tTracksTree = (TTree*)f->Get("ppTrack/tTracksTree");
 Tracks tTracks;
 bool doCheck = true;
 setupTrackTree(tTracksTree, tTracks, doCheck);

 // hiEvtAnalyzer
 TTree *EvtAna= (TTree*)f->Get("hiEvtAnalyzer/HiTree");
 int hiNtTrackss; EvtAna->SetBranchAddress("hiNtTrackss", &hiNtTrackss);
 float vz; EvtAna->SetBranchAddress("vz", &vz);

 // skimanalysis for event selection
 TTree *SkimAna= (TTree*)f->Get("skimanalysis/HltTree");
 int pPAcollisionEventSelection; SkimAna->SetBranchAddress("pPAcollisionEventSelectionPA", &pPAcollisionEventSelection);
 int pileUpBit;                  SkimAna->SetBranchAddress("pVertexFilterCutGplus", &pileUpBit);

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
  
  TH3D **hreco      = Setup_TH3D_nCorrTyp("hreco",      ";p_{T};#eta;#phi", nx,x,neta,etaval,nphi,phival);
  TH3D **hsecondary = Setup_TH3D_nCorrTyp("hsecondary", ";p_{T};#eta;#phi", nx,x,neta,etaval,nphi,phival)
  TH3D **hreal      = Setup_TH3D_nCorrTyp("hreal",      ";p_{T};#eta;#phi", nx,x,neta,etaval,nphi,phival);
  TH3D **hgen       = Setup_TH3D_nCorrTyp("hgen",       ";p_{T};#eta;#phi", nx,x,neta,etaval,nphi,phival);
  TH3D **hmatched   = Setup_TH3D_nCorrTyp("hmatched",   ";p_{T};#eta;#phi", nx,x,neta,etaval,nphi,phival);
  TH3D **heff       = Setup_TH3D_nCorrTyp("heff",       ";p_{T};#eta;#phi", nx,x,neta,etaval,nphi,phival);
  TH3D **hmultrec   = Setup_TH3D_nCorrTyp("hmultrec",   ";p_{T};#eta;#phi", nx,x,neta,etaval,nphi,phival);

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
  
 ///////////////////////////////////////
 //                                   //
 // ***** Calculate corrections ***** //
 //                                   //
 ///////////////////////////////////////

  // Event loop
  if (nEvMax == -1) {if(!hi) nEvMax = SkimAna->GetEntries();
  else nEvMax = tTracksTree->GetEntries();}
  std::cout << "nEvMax = " << nEvMax << std::endl;

  for (int iEvA = 0; iEvA < nEvMax; iEvA++)
  {

   EvtAna->GetEntry (iEvA);
	SkimAna->GetEntry(iEvA);
 
	// Event counter info
	if ( (iEvA % 1000) == 0 )
	{ std::cout << "Event: " << iEvA << std::endl; }

	// Event Selection
	if ( !EventSelection( pPAcollisionEventSelection, pileUpBit) ) continue;
	if ( zvtxbin(vz, nZvtxBins) == -1 ) continue;
	if ( multiplicitybin_Ana(hiNtTrackss, nMultiplicityBins_Ana) == -1) continue;

	 // Check vz
    if( TMath::Abs(c->evt.vz - meanVz) > 15)
	 {
      vzCut++;
      continue;
    }

	// Load in tTrackss
	tTracksTree->GetEntry(iEvA);

	int nTrk = tTracks.nTrk;

	// Track loop
	for (int iTrk = 0; iTrk < nTrk; iTrk++)
	{

      double pt  = tTracks.trkPt [iTrk];
      double eta = tTracks.trkEta[iTrk]; 
      double phi = tTracks.trkPhi[iTrk];
  		float p    = pt * cosh(eta);
		int PID    = GetPID(p, tTracks.dedx[iTrk]);
		bool isPID = (PID != 99);

		// *** Track selection *** //
		if ( !TrackSelection(tTracks, iTrk ) ) continue;

      // You should also require the additional cuts that you apply to choose a given PID
		
		// Fake tracks
      if( tTracks.trkFake[iTrk] )
		{ 
			hfake[0]->Fill(pt, eta, phi);
			if (isPID) { hfake[PID]->Fill(pt, eta, phi);}
		}
		else 
		// Real track
		{ 
		  hreal[0]->Fill(pt,eta,phi);
		  if (isPID) { hreal[PID]->Fill(pt, eta, phi);}
		  // Real secondary track
		  if( tTracks.trkStatus[iTrk] < 0 )
		  {
		    hsecondary[0]->Fill(pt, eta, phi);
		    if (isPID) { hsecondary[PID]->Fill(pt, eta, phi);}
		  };
      }

		// Reconstructed tracks
      hreco[0]->Fill( pt, eta, phi);
		if (isPID) { hreco[PID]->Fill(pt, eta, phi);}
    }

	 // * Particle loop * //
    for(int iTrk=0; iTrk < tTracks.nParticle; iTrk++)
	 {

      double pt  = tTracks.pPt [iTrk];
      double eta = tTracks.pEta[iTrk];
      double phi = tTracks.pPhi[iTrk];

		// particle selection
      if( fabs(eta)>2.4 ) continue;
      if( pt<bin_pt_min ) continue;
      if( fabs(c->tTracks.pPId[iTrk])!=PId ) continue; 

      hgen->Fill( pt,eta,phi );

      if( !( tTracks.mtrkQual[iTrk] && fabs( tTracks.mtrkDxy1[iTrk]/tTracks.mtrkDxyError1[iTrk])<3.0 && fabs(tTracks.mtrkDz1[iTrk]/tTracks.mtrkDzError1[iTrk])<3 && (tTracks.mtrkPtError[iTrk]/tTracks.mtrkPt[iTrk])<0.1) ) continue;

      hmatched->Fill(pt,eta,phi);
      hmultrec->Fill(pt,eta,phi, tTracks.pNRec[iTrk]);
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
