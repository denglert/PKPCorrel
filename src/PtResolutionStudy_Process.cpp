#include "EvtSelection.h"
#include "EvtAnalyzer.h"
#include "PtResolutionStudy.h"
#include "AnalysisFW.h"

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

 TFile *output = new TFile(Form("./PtResolutions_%s.root", tag.c_str() ),"RECREATE");
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
 
 PtRes *ptres = new PtRes();
 ptres->SetupForProcess();
 ptres->StdPrintBinning();

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
		for(int iTP = 0; iTP < tTracks.nParticle; iTP++)
		{

			// Track selection on matched track associated with current tracking particle
			if ( !(mTrackSelection_c(tTracks, iTP)) ) continue;

			float mtrkPt = tTracks.mtrkPt[iTP]; // matched track Pt

			float trpaPt = tTracks.pPt[iTP];       //          trackingParticle Pt
			int   ptBin  = ptres->GetPtBin( trpaPt ); // ptBin of trackingParticle Pt

			if ( ptBin   == -999 ) continue;

			int mtrkPID = pidutil->GetIDmTrk_trkCorr( tTracks, iTP ); // get reco-level PID
			int trpaPID = tTracks.pPId[iTP]; 								 // get ID of tracking particle

			if ( mtrkPID ==    4 ) continue;

			float PtRelDiff = (mtrkPt-trpaPt)/(trpaPt);
			ptres->PtRecSimMatrix[0]->Fill(trpaPt,mtrkPt);
			ptres->RelDiffPt          [0][ptBin]->Fill(PtRelDiff);

			if ( mtrkPID == 99 ) continue;
			ptres->PtRecSimMatrix[mtrkPID]->Fill(trpaPt,mtrkPt);
			ptres->RelDiffPt          [mtrkPID][ptBin]->Fill(PtRelDiff);

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
