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
#include "AnalysisBinning.h"
#include "PIDUtils.h"
#include "AnalysisFW.h"
#include "SetupCustomTrackTree.h"
#include "dataType.h"
#include "EvtSelection.h"
#include "EvtAnalyzer.h"


int main( int argc, const char *argv[] )
{

  if(argc != 5)
  {
    std::cerr << "Usage: StudyMCinfo <MC sample> <tag> <nEvents> <PIDconfig>" << std::endl;
	 exit(1);
  }

 std::string inpFilename 	  = argv[1];
 std::string tag		        = argv[2];
 int nEvMax 	  		        = atoi( argv[3] );
 std::string PIDconfig		  = argv[4];
 
 PIDUtil *pidutil = new PIDUtil;
 pidutil->ReadInConfig(PIDconfig);

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

 ///////////////
 // Open file //
 ///////////////
 
 TFile *f = NULL;
 f = TFile::Open(inpFilename.c_str());
 if ( (f == NULL) || (f->IsZombie()) ) {std::cerr << "Error opening file: " << inpFilename << std::endl; exit(-1);}

 //////////////////
 // Initializing //
 //////////////////
 
 EvtAnalyzer EvAna;
 EvAna.setupEvtAnaTree( f );

 EvtSelection EvSelMC;
 EvSelMC.setupSkimTree_pPb( f, true);
 
 ////////////////////
 // Setting output //
 ////////////////////

 TFile *output = new TFile(Form("./MCinfo_%s.root", tag.c_str() ),"RECREATE");
 output->cd();

 ///////////////
 // Open file //
 ///////////////

 TTree *trackTree = (TTree*)f->Get("ppTrack/trackTree");
 Tracks_c tTracks;
 setupTrackTree_c(trackTree, tTracks, true);

 //////////////////////////////
 //                          //
 // ***** Initializing ***** //
 //                          //
 //////////////////////////////
 
 const int protonID = 3;
 const int    nBins = 13;
 const double ptMin = 0.3;
 const double ptMax = 1.6;

 TH1D *nProtonsRECO 	   	= new TH1D("nProtonsRECO",      ";p_{T} [GeV/c];Entries", nBins, ptMin, ptMax);
 TH1D *nProtonsGENE 	   	= new TH1D("nProtonsGENE",      ";p_{T} [GeV/c];Entries", nBins, ptMin, ptMax);
 TH1D *nLambda2ProtonTP 	= new TH1D("nLambda2ProtonTP", ";p_{T} [GeV/c];Entries", nBins, ptMin, ptMax);
 TH1D *nLambda2ProtonGM 	= new TH1D("nLambda2ProtonGM", ";p_{T} [GeV/c];Entries", nBins, ptMin, ptMax);
 TH1D *trkStatusDistr   	= new TH1D("trkStatusDistr", ";trkStatus;Entries", 200, -100, 100);
 TH1D *negtrkStatusPtDistr = new TH1D("negtrkStatusPtDistr", ";p_{T} [GeV/c];Entries", nBins, ptMin, ptMax);
 TH1D *n99trkStatusPtDistr = new TH1D("n99trkStatusPtDistr", ";p_{T} [GeV/c];Entries", nBins, ptMin, ptMax);

 TH1D *MotherPIdDistrGM	 = new TH1D("MotherPIdDistrGM", ";PDG Id;Entries", 20000, -10000, 10000);
 TH1D *MotherPIdDistrM 	 = new TH1D("MotherPIdDistrM", ";PDG Id;Entries", 20000, -10000, 10000);
 
 ////////////////////////////
 //                        //
 // ***** Event loop ***** //
 //                        //
 ////////////////////////////
 
 log.wr( "Starting to process MC sample..." );

  // Event loop 
  if ( nEvMax == -1 )
  { nEvMax = trackTree->GetEntries(); }

  log.wr( Form("nEvMax: %d", nEvMax));

  for (int iEvA = 0; iEvA < nEvMax; iEvA++)
  {

		// EventCounter
		log.EventCounter(iEvA);

		// Event zvtx
		EvAna.GetEntry( iEvA );
		float vz = EvAna.getvz();
		
		// Event Selection
		if ( !EvSelMC.isGoodEv_pPb( iEvA ) ) continue;
		if ( zvtxbin(vz, nZvtxBins) == -1 ) continue;
	
		// Tracks & particles
		trackTree->GetEntry(iEvA);
		// === TrackingParticle loop === //
		for(int iTrk = 0; iTrk < tTracks.nTrk; iTrk++)
		{

			// particle selection
		//	if ( !(TrackSelection(tTracks, iTrk)) ) continue;

			float pt = tTracks.trkPt[iTrk];
			int PID = pidutil->GetID( tTracks, iTrk);
			float trkStatus = tTracks.trkStatus[iTrk];

			// If it is NOT a proton, then skip
			if ( PID != protonID ) continue;

			trkStatusDistr->Fill( trkStatus );
			nProtonsRECO->Fill(pt);

			int genPID = tTracks.trkPId[iTrk];
			int GMPID  = tTracks.trkGMPId[iTrk];
			int  MPID  = tTracks.trkMPId[iTrk];


			// negative track status
			if ( trkStatus < 0)
			{  negtrkStatusPtDistr->Fill( pt ); }
			
			if ( trkStatus = -99)
			{
				n99trkStatusPtDistr->Fill( pt ); 
//				std::cerr <<  std::endl;
//				std::cerr << "trkStatus: " << trkStatus << std::endl;
//				std::cerr << "trkFake: " << tTracks.trkFake[iTrk] << std::endl;
//				std::cerr << "genPID: "  << genPID << std::endl;
//				std::cerr << "motherinfo" << std::endl;
//				std::cerr << "GMPID: "   << GMPID << std::endl;
//				std::cerr << "MPID: "    << MPID << std::endl;
//				std::cerr <<  std::endl;
			} 

		
			MotherPIdDistrM ->Fill(MPID);
			MotherPIdDistrGM->Fill(GMPID);
			
			if ( (genPID == 2212) || (genPID == -2212) )
			{ nProtonsGENE->Fill(pt); }

			if ( (GMPID == 3122) || (GMPID == -3122) )
			{ 
				nLambda2ProtonGM->Fill(pt);

			}

			if ( (MPID == 3122) || (MPID == -3122) )
			{ 
				nLambda2ProtonTP->Fill(pt);
			}

		}
		
  }

 //////////////////////
 //                  //
 // **** OUTPUT **** //
 //                  //
 //////////////////////
  
  output->cd();
  output->Write();
  
  log.Close();
  
  output->Close();
  delete output;

  printf("Done.\n");

}

//				std::cerr << "trkStatus: " << trkStatus << std::endl;
//				std::cerr << "trkFake: " << tTracks.trkFake[iTrk] << std::endl;
//				std::cerr << "genPID: "  << genPID << std::endl;
//				std::cerr << "GMPID: "   << GMPID << std::endl;
//				std::cerr << "MPID: "    << MPID << std::endl;
