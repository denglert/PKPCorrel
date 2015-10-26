#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include "PIDUtils.h"
#include "AnalysisFW.h"
#include "EvtAnalyzer.h"
#include "EvtSelection.h"

int main( int argc, const char *argv[] )
{

  if(argc != 5)
  {
    std::cerr << "Usage: PIDStudy <sample source> <isMC> <PIDconfig> <nEvents> " << std::endl;
	 exit(1);
  }

 std::string inpFilename = argv[1];
 std::string isMC 		 = argv[2];
 int nEvMax 	  		    = atoi( argv[3] );
 std::string PIDconfig	 = argv[4];

 // Open file
 TFile *f = TFile::Open( inpFilename.c_str() );
 if ( f->IsZombie() ) {std::cerr << "Error opening file: " << inpFilename << std::endl; exit(-1);}

 //////////////////
 // Initializing //
 //////////////////
 
 PIDUtil *pidutil = new PIDUtil;
 pidutil->ReadInConfig(PIDconfig);

 LogFile log("log");
 log.repeat = 1000;

 TTree *trackTree;

 // trackTree
 if ( isMC == "no" )
 { trackTree = (TTree*)f->Get("pptracks/trackTree"); }
 else if ( isMC == "yes" )
 { trackTree = (TTree*)f->Get("ppTrack/trackTree");  }


 Tracks tTracks;

 bool doMC;
 if (isMC == "no")
 { doMC = false; }
 else if ( isMC == "yes")
 { doMC = true;  }
 
 setupTrackTree(trackTree, tTracks);

 // EventAnalyzer
 EvtAnalyzer EvAna;
 EvAna.setupEvtAnaTree( f );

 log.wr(Form("EvtAna.vz:  [ %.2f - %.2f ] ", EvAna.vz_min, EvAna.vz_max));
 log.wr(Form("EvtAna.Ntr: [ %d - %d ] ",     EvAna.Ntrk_min, EvAna.Ntrk_max));

 // Event Selection (SkimAnalysis)
 EvtSelection EvSel;
 EvSel.setupSkimTree_pPb( f, doMC);


 PIDStudy *pidstudy = new PIDStudy();
 pidstudy->nMultiplicityBins = nMultiplicityBins_Ana_HDR;
 pidstudy->SetupOut();
 pidstudy->Setup();
 
 // Analysis specific //
 
 ////////////////
 // Event loop //
 ////////////////
 
 if (nEvMax == -1) {nEvMax = trackTree->GetEntries();}

 for (int iEvA = 0; iEvA < nEvMax; iEvA++)
 //for (int iEvA = 96966; iEvA < nEvMax; iEvA++)
 {

 	// EventCounter
 	log.EventCounter(iEvA);
 	EvAna.GetEntry  (iEvA);

 	

 	// Event Selection
 	if ( !EvSel.isGoodEv_pPb( iEvA ) ) continue;
// 	if ( !EvAna.isEvPass( )          ) continue;
 	
 	// Tracks & particles
 	trackTree->GetEntry(iEvA);


	int noff = EvAna.gethiNtracks();
   int multBin = multiplicitybin_Ana(noff, nMultiplicityBins_Ana_HDR);

	if (multBin == -1) continue;
 	
 	int nTrk = tTracks.nTrk;
 	
 	// Track loop
 	for (int iTrk = 0; iTrk < nTrk; iTrk++)
 	{



 		// *** Track selection *** //
 		if ( !TrackSelection(tTracks, iTrk ) ) continue;

		float pt   = tTracks.trkPt[iTrk];
		float eta  = tTracks.trkEta[iTrk];
		float p    = pt*cosh(eta);
		float dEdx = tTracks.dedx[iTrk];

		double ptMin = 0.3; 
		if (pt < ptMin) continue;
		
		double ptcut1 = 0.8;	
		double ptcut2 = 0.9;	

//		if ( (pt < ptcut1) || (ptcut2 < pt)) continue;	

		pidstudy->dEdxvsPMap_lin[multBin]->Fill(p,dEdx);
		pidstudy->dEdxvsPMap_log[multBin]->Fill(p,dEdx);

		int pBin = pidstudy->GetpBin(p);

		if ( pBin == -1 ) continue;
		pidstudy->dEdxDistr_lin[multBin][pBin]->Fill(dEdx);
		pidstudy->dEdxDistr_log[multBin][pBin]->Fill(dEdx);

 	}

 	
 }

 pidstudy->Write();

}
