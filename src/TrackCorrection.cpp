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
//#include "../HiForestAnalysis/hiForest.h"
#include "AnalysisBinning.h"
#include "PIDUtils.h"
#include "AnalysisFW.h"
#include "SetupCustomTrackTree.h"
#include "dataType.h"
#include "EvtSelection.h"
#include "EvtAnalyzer.h"

// zvtx distribution parameters
const int nZvtxDistrBins  =  13;
const int nPart = 4;
const double zVtxDistrMin = -13;
const double zVtxDistrMax =  13;

const int npt[4]      = {20,    10,   5,  5};
const double ptMin[4] = {0.1, 0.15, 0.15, 0.15};
const double ptMax[4] = {3.0, 1.00, 1.00, 1.8 };

// const int npt[4]      = {1,    1,   1,  1};
// const double ptMin[4] = {0.3, 0.15, 0.15, 0.15};
// const double ptMax[4] = {0.5, 0.40, 0.40, 0.4 };


const double ptGlobalMin = 0.1;

const int neta = 48;
const double etaMin = -2.3;
const double etaMax =  2.3;

const int nphi = 70;
const double phiMin = -TMath::Pi();
const double phiMax =  TMath::Pi();


TH3D** Setup_TH3D_nCorrTyp(const char histoname[], const char histolabel[], const int nXBins[], const double xmin[], const double xmax[], int nYBins, double ymin, double ymax, int nZBins, double zmin, double zmax )
{
	TH3D **histos = new TH3D*[nPart];

	for( int i = 0; i < nPart; i++)
	{
		 histos[i] = new TH3D( Form("%s typ %d", histoname, i), histolabel, nXBins[i], xmin[i], xmax[i], nYBins, ymin, ymax, nZBins, zmin, zmax);
	}

	return histos;
};

TH2D** Setup_TH2D_nCorrTyp(const char histoname[], const char histolabel[], const int nXBins[], const double xmin[], const double xmax[], int nYBins, double ymin, double ymax, int nZBins, double zmin, double zmax )
{
	TH2D **histos = new TH2D*[nPart];

	for( int i = 0; i < nPart; i++)
	{
		 histos[i] = new TH3D( Form("%s typ %d", histoname, i), histolabel, nXBins[i], xmin[i], xmax[i], nYBins, ymin, ymax, nZBins, zmin, zmax);
	}

	return histos;
};


int main( int argc, const char *argv[] )
{

  if(argc != 7)
  {
    std::cerr << "Usage: TrackCorrection <MC sample> <DATA sample> <sample type> <tag> <nEventsDATA> <nEventsMC>" << std::endl;
	 exit(1);
  }

 std::string inpFilenameDATA = argv[1];
 std::string inpFilenameMC   = argv[2];
 std::string str_sampleType  = argv[3];
 std::string tag		        = argv[4];
 int nEvMaxDATA 	  		     = atoi( argv[5] );
 int nEvMaxMC 	  		        = atoi( argv[6] );

 sampleType sType = str2enumSampleTyp(str_sampleType);
 
 // Binning
 int nCorrTyp = nCorrTyp_; 
 int *nPtBins = new int[nCorrTyp_];

 for(int TypBin = 0; TypBin < nCorrTyp; TypBin++)
 { nPtBins[TypBin] = nPtBins_[TypBin]; }

 int nMultiplicityBins_Ana = nMultiplicityBins_Ana_HDR;
 int nMultiplicityBins_EvM = nMultiplicityBins_EvM_HDR;
 int nZvtxBins 		      = nZvtxBins_; 

 LogFile log("log");
 log.repeat = 1000;

 ///////////////////////////
 // Global initialization //
 ///////////////////////////

 TH1D *zvtxDistrMC   = new TH1D("zvtxDistrMC  ",";zvtx;nEvents", nZvtxDistrBins, zVtxDistrMin, zVtxDistrMax);
 TH1D *zvtxDistrDATA = new TH1D("zvtxDistrDATA",";zvtx;nEvents", nZvtxDistrBins, zVtxDistrMin, zVtxDistrMax);
 TH1D *ratiozvtx;

/////////////////////////////////////
//                                 //
// ====== zvtx distribution ====== //
//                                 //
/////////////////////////////////////

 ////////////////////////
 // === DATA z-vtx === //
 ////////////////////////

 ///////////////
 // Open file //
 ///////////////
 
 TFile *fdt = TFile::Open(inpFilenameDATA.c_str());
 if ( fdt->IsZombie() ) {std::cerr << "Error opening file: " << inpFilenameDATA << std::endl; exit(-1);}

 //////////////////
 // Initializing //
 //////////////////
 
 EvtAnalyzer EvAnaDATA;
 EvAnaDATA.setupEvtAnaTree( fdt );

 EvtSelection EvSelDATA;
 EvSelDATA.setupSkimTree_pPb( fdt, true);

 ////////////////
 // Event loop //
 ////////////////
 
 log.wr( "Starting to process DATA for zvtx distribution." );

 if (nEvMaxDATA == -1)
 { nEvMaxDATA = EvSelDATA.SkimAna->GetEntries(); }

 log.wr( Form("nEvMaxDATA: %d", nEvMaxDATA) );

 for (int iEv = 0; iEv < nEvMaxDATA; iEv++)
 {

	// EventCounter
	log.EventCounter(iEv);

	// EventSelection
	if ( !EvSelDATA.isGoodEv_pPb( iEv ) ) continue;
	
	EvAnaDATA.GetEntry( iEv );
   zvtxDistrDATA->Fill( EvAnaDATA.getvz() );

 } 


 log.wr( "DATA processed." );
 log.wr( "zVtx distribution." );
 fdt->Close();
 delete fdt;

 //////////////////////
 // === MC z-vtx === //
 //////////////////////
 
  ///////////////
 // Open file //
 ///////////////
 
 TFile *fmc = TFile::Open(inpFilenameMC.c_str());
 if ( fmc->IsZombie() ) {std::cerr << "Error opening file: " << inpFilenameMC << std::endl; exit(-1);}

 //////////////////
 // Initializing //
 //////////////////
 
 EvtAnalyzer EvAnaMC;
 EvAnaMC.setupEvtAnaTree( fmc );

 EvtSelection EvSelMC;
 EvSelMC.setupSkimTree_pPb( fmc, false);

 
 ////////////////
 // Event loop //
 ////////////////
 
 log.wr( "Starting to process MC for zvtx distribution." );
 
 if (nEvMaxMC == -1)
 { nEvMaxMC = EvSelMC.SkimAna->GetEntries(); }

 log.wr( Form("nEvMaxMC: %d", nEvMaxMC) );


 for (int iEv = 0; iEv < nEvMaxMC; iEv++)
 {

	// Event counter info
	log.EventCounter(iEv);

	// EventSelection
	if ( !EvSelMC.isGoodEv_pPb( iEv ) ) continue;
	
	EvAnaMC.GetEntry( iEv );
   zvtxDistrMC->Fill( EvAnaMC.getvz() );

 }

 ////////////////////
 // Setting output //
 ////////////////////

 TFile *output = new TFile(Form("./trkCorrections_%s.root", tag.c_str() ),"RECREATE");
 output->cd();

 ratiozvtx = (TH1D*)zvtxDistrDATA->Clone("zvtxratio");
 ratiozvtx->Divide( zvtxDistrMC );

//////////////////////////////////////
//                                  //
// ====== MC eff calculation ====== //
//                                  //
//////////////////////////////////////

 ///////////////
 // Open file //
 ///////////////

 TTree *trackTree = (TTree*)fmc->Get("ppTrack/trackTree");
 Tracks tTracks;
 setupTrackTree(trackTree, tTracks, true);

 //////////////////////////////
 //                          //
 // ***** Initializing ***** //
 //                          //
 //////////////////////////////
 
  TH3D **hfake      = Setup_TH3D_nCorrTyp("hfake",      ";p_{T};#eta;#phi", npt,ptMin,ptMax,neta,etaMin,etaMax,nphi,phiMin,phiMax);
  TH3D **hreco      = Setup_TH3D_nCorrTyp("hreco",      ";p_{T};#eta;#phi", npt,ptMin,ptMax,neta,etaMin,etaMax,nphi,phiMin,phiMax);
  TH3D **hsecondary = Setup_TH3D_nCorrTyp("hsecondary", ";p_{T};#eta;#phi", npt,ptMin,ptMax,neta,etaMin,etaMax,nphi,phiMin,phiMax);
  TH3D **hreal      = Setup_TH3D_nCorrTyp("hreal",      ";p_{T};#eta;#phi", npt,ptMin,ptMax,neta,etaMin,etaMax,nphi,phiMin,phiMax);
  TH3D **hgen       = Setup_TH3D_nCorrTyp("hgen",       ";p_{T};#eta;#phi", npt,ptMin,ptMax,neta,etaMin,etaMax,nphi,phiMin,phiMax);
  TH3D **hmatched   = Setup_TH3D_nCorrTyp("hmatched",   ";p_{T};#eta;#phi", npt,ptMin,ptMax,neta,etaMin,etaMax,nphi,phiMin,phiMax);
  TH3D **hmultrec   = Setup_TH3D_nCorrTyp("hmultrec",   ";p_{T};#eta;#phi", npt,ptMin,ptMax,neta,etaMin,etaMax,nphi,phiMin,phiMax);
  TH3D *heff[nPart];
  TH3D *hmultrecrate[nPart];
  TH3D **hcorr   = Setup_TH3D_nCorrTyp("hcorr",   ";p_{T};#eta;#phi", npt,ptMin,ptMax,neta,etaMin,etaMax,nphi,phiMin,phiMax);


 ///////////////////////////////////////
 //                                   //
 // ***** Calculate corrections ***** //
 //                                   //
 ///////////////////////////////////////
 
 log.wr( "Starting to process MC to calclulate track corrrections..." );

  // Event loop 
  if ( nEvMaxMC == -1 )
  { nEvMaxMC = trackTree->GetEntries(); }

  log.wr( Form("nEvMaxMC: %d", nEvMaxMC));

  for (int iEvA = 0; iEvA < nEvMaxMC; iEvA++)
  {

		// EventCounter
		log.EventCounter(iEvA);
		
		// Event Selection
		if ( !EvSelMC.isGoodEv_pPb( iEvA ) ) continue;;
		
		// Event zvtx
		EvAnaMC.GetEntry( iEvA );
		float vz = EvAnaMC.getvz();
		int vzB = ratiozvtx->FindBin(vz) ;
		int wzvtx = ratiozvtx->GetBinContent(vzB);

		if ( (vzB == -1) || ((nZvtxDistrBins) == vzB)) continue;
	
		// Tracks & particles
		trackTree->GetEntry(iEvA);
		
		int nTrk = tTracks.nTrk;
		
		// Track loop
		for (int iTrk = 0; iTrk < nTrk; iTrk++)
		{

			// *** Track selection *** //
			if ( !TrackSelection(tTracks, iTrk ) ) continue;

			double pt  = tTracks.trkPt [iTrk];
			double eta = tTracks.trkEta[iTrk]; 
			double phi = tTracks.trkPhi[iTrk];
			float p    = pt * cosh(eta);
			int PID    = GetPID(p, tTracks.dedx[iTrk], tTracks.trkEta[iTrk]);
			bool isPID = (PID != 99);
			
			// Fake tracks
			if( tTracks.trkFake[iTrk] )
			{ 
				           hfake[ 0 ]->Fill(pt,eta,phi, wzvtx);
				if (isPID) hfake[PID]->Fill(pt,eta,phi, wzvtx);
			}
			else 
			// Real track
			{ 
			             hreal[ 0 ]->Fill(pt,eta,phi, wzvtx);
			  if (isPID) hreal[PID]->Fill(pt,eta,phi, wzvtx);
			  // Real secondary track
			  if( tTracks.trkStatus[iTrk] < 0 )
			  {
			               hsecondary[ 0 ]->Fill(pt,eta,phi,wzvtx);
			    if (isPID) hsecondary[PID]->Fill(pt,eta,phi,wzvtx);
			  };
		   }
		
			// Reconstructed tracks
		              hreco[ 0 ]->Fill(pt,eta,phi,wzvtx);
			if (isPID) hreco[PID]->Fill(pt,eta,phi,wzvtx);
		}
		
		// === Particle loop === //
		for(int iPart = 0; iPart < tTracks.nParticle; iPart++)
		{

			double pt  = tTracks.pPt [iPart];
			double eta = tTracks.pEta[iPart];
			double phi = tTracks.pPhi[iPart];
		
			// No eta cut
			int PID = McPID2AnaPID( tTracks.pPId[iPart] , 2.0);
			bool isPID = (PID != 99);
		
			// particle selection
			if( fabs(eta) > 2.4 ) continue;
			if( pt < ptGlobalMin      ) continue;
		
								hgen[ 0 ]->Fill( pt,eta,phi,wzvtx );
			if ( isPID ) { hgen[PID]->Fill( pt,eta,phi,wzvtx ); }

			// matched track selection
			if( !( mTrackSelection( tTracks, iPart) )) continue;

			double mpt  = tTracks.mtrkPt [iPart];
			double meta = tTracks.pEta[iPart]; 
			float  mp   = mpt * cosh(meta);
			int    mPID = GetPID(mp, tTracks.mtrkdedx[iPart], eta);
			bool   misPID = (mPID != 99);
		
				hmatched[ 0 ]->Fill(pt,eta,phi,wzvtx); 
				hmultrec[ 0 ]->Fill(pt,eta,phi,wzvtx*tTracks.pNRec[iPart]);
			if ( misPID )
			{ 
				hmatched[mPID]->Fill(pt,eta,phi,wzvtx); 
				hmultrec[mPID]->Fill(pt,eta,phi,wzvtx*tTracks.pNRec[iPart]);
			}
		
		   }
		
  }

  for( int iPar = 0; iPar < nPart; iPar++)
  {
   	hfake     [iPar] -> Divide( hreco   [iPar] );
   	hsecondary[iPar] -> Divide( hreal   [iPar] );
   	heff      [iPar]  = (TH3D*)hmatched [iPar]->Clone(Form("heff part %d", iPar));
   	heff      [iPar] -> Divide( hgen    [iPar] );
   	hmultrecrate [iPar] = (TH3D*)hmultrec [iPar]->Clone(Form("hmultrecrate part %d", iPar));
   	hmultrecrate [iPar] -> Divide( hmatched[iPar] );
  }

  // Filling track correction table
  double ptbw[4];
  for(int i = 0; i < nPart; i++)
  {
	ptbw[i] = (ptMax[i]-ptMin[i])/npt[i];
  }
  const double etabw = (etaMax-etaMin)/neta;
  const double phibw = (phiMax-phiMin)/nphi;

  for(int i = 0; i < nPart; i++)
  for(int x = 1; x < npt[i]  +1; x++)
  for(int y = 1; y < neta +1; y++)
  for(int z = 1; z < nphi +1; z++)
  {
	  double pt  = ptMin[i]+x*ptbw[i]; 
	  double eta = etaMin+y*etabw; 
	  double phi = phiMin+z*phibw; 

     double value = (1.0-hfake[i]->GetBinContent(x,y,z))*(1.0-hsecondary[i]->GetBinContent(x,y,z)) / ((heff[i]->GetBinContent(x,y,z)) * (hmultrec[i]->GetBinContent(x,y,z)));
	  hcorr[i]->SetBinContent(x,y,z,value);
 	  log.wr(Form("%d %.3f %.2f %.2f : %.4f", i, pt, eta, phi, value));
  }

 //////////////////////
 //                  //
 // **** OUTPUT **** //
 //                  //
 //////////////////////
  
  output->cd();
  output->Write();
  
  //heff->wr();
  //hfake->wr();
  //hmultrec->wr();
  //hsecondary->wr();
  
  log.Close();
  
  output->Close();
  delete output;

  printf("Done.\n");
}
