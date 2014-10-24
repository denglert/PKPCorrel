#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TNtuple.h>
#include <iostream>
#include <deque>
#include <TLorentzVector.h>
#include "AnalysisFW.h"
#include "AnalysisBinning.h"
#include "PIDUtils.h"
#include "CorrelationUtils.h"
#include "SetupCustomTrackTree.h"
#include "EvtSelection.h"

int main( int argc, const char *argv[] )
{ 

  if(argc != 6)
  {
    std::cerr << "Usage: preprocess <.root file to be preprocessed> <tag> <nEvents>" << std::endl;
	 exit(1);

  }

 TString inpFilename     = argv[1];
 TString dotrkCorr_str 	 = argv[2];
 TString trkCorrFilename = argv[3];
 std::string tag		    = argv[4];
 int nEvMax 	  		    = atoi( argv[5] );

 // Binning
 int nCorrTyp			  = nCorrTyp_; 
 int *nPtBins = new int[nCorrTyp_];

 for(int TypBin = 0; TypBin < nCorrTyp; TypBin++)
 { nPtBins[TypBin] = nPtBins_[TypBin]; }

 int nMultiplicityBins_Ana = nMultiplicityBins_Ana_HDR;
 int nMultiplicityBins_EvM = nMultiplicityBins_EvM_HDR;
 int nZvtxBins 		      = nZvtxBins_; 

 std::cout << "dotrkCorr: " << dotrkCorr_str << std::endl;

 bool dotrkCorr;
      if( dotrkCorr_str == "yes" ) { dotrkCorr =  true; }
 else if( dotrkCorr_str == "no" ) { dotrkCorr = false; }
 else {std::cerr << "dotrkCorr not defined." << std::endl; exit(-1);}

 //////////////////////////////////////
 //                                  //
 // ****** Opening input file ****** //
 //                                  //
 //////////////////////////////////////
 
 // Open file
 TFile *f = TFile::Open(inpFilename);
 if ( f->IsZombie() ) {std::cerr << "Error opening file: " << inpFilename << std::endl; exit(-1);}

 // trackTree
 TTree *trackTree = (TTree*)f->Get("pptracks/trackTree");
 Tracks tTracks;
 bool doMC = false;
 setupTrackTree(trackTree, tTracks, doMC);

 // hiEvtAnalyzer
 TTree *EvtAna= (TTree*)f->Get("hiEvtAnalyzer/HiTree");
 int hiNtracks; EvtAna->SetBranchAddress("hiNtracks", &hiNtracks);
 float vz; EvtAna->SetBranchAddress("vz", &vz);

 // Event Selection
 EvtSelection EvSel;
 EvSel.setupSkimTree_pPb( f, true);

 ////////////////////////////////
 //                            //
 // ***** Setting output ***** //
 //                            //
 ////////////////////////////////
 
 TFile *output = new TFile(Form("./correl_analysis_%s.root", tag.c_str() ),"RECREATE");
 output->cd();

 //////////////////////////////
 //                          //
 // ***** Initializing ***** //
 //                          //
 //////////////////////////////
 
 TH1::SetDefaultSumw2( );
 TH2::SetDefaultSumw2( );

 // EventCache
 std::deque< EventData > **EventCache;
 Setup_EventCache(EventCache, nMultiplicityBins_EvM, nZvtxBins);

 // dEdxvsp map
 TH2D *dEdxvsp  = new TH2D ("dEdxVsP",";p(GeV/c);dE/dx", npBins, pMin, pMax, ndEdxBins, dEdxMin, dEdxMax);

 // Number of tracks distribution
 TH1D *nTrkDistr_signal = new TH1D("nTrkDistr_signal","Track distribution;Multiplicity", 350, 0, 350);

 // Correlation Framework
 CorrelationFramework CFW(nCorrTyp, nPtBins, nMultiplicityBins_Ana, nMultiplicityBins_EvM);
 std::cout << "Correlation Analysis Framework loaded." << std::endl;

 CFW.DoSelfCorrelation = false;
 if ( CFW.DoSelfCorrelation ) { std::cout << "Analysis includes self correlation computation." << std::endl;}

 CFW.DoTrackWeight = dotrkCorr;
 CFW.SetupForPreprocess();

 // TrackCorrection file
 TFile *f_trkCorr = new TFile(trkCorrFilename, "READ");
 if ( f_trkCorr->IsZombie() ) {std::cerr << "Error opening file: " << trkCorrFilename << std::endl; exit(-1);}
 else {std::cout << "trkCorr File successfully opened." << std::endl;}

 CFW.trkCorr = Read_trkEff(f_trkCorr, "hcorr typ");

 for (int i = 0; i < nCorrTyp; i++)
 { CFW.trkCorr[i]->SetDirectory(0); }

 f_trkCorr->Close();

 // EventData
 EventData *ev;
 ev = new EventData;

 ev->Setup_nTriggerParticles(nCorrTyp, nPtBins);

 ///////////////////////////////////////////
 //                                       //
 // **** PRELOAD MIXEVENTS IN MEMORY **** //
 //                                       //
 ///////////////////////////////////////////
 
 std::cout << "Preloading events in memory..." << std::endl;
 for(int multBin = 0; multBin < nMultiplicityBins_EvM; multBin++)
 for(int zvtxBin = 0; zvtxBin < nZvtxBins_; zvtxBin++)
 {
	
	int count = 0;
	int nev = 10;
	
	int iEv = 0;

 	while ( (count < (nev+1)) && (iEv < trackTree->GetEntries() )) 
	{

		// Get current event info
		EvtAna->GetEntry(iEv);

		// EventSelection

		if ( EvSel.isGoodEv_pPb( iEv ) )
		if (     zvtxbin(vz, nZvtxBins_)    == zvtxBin )
		if ( multiplicitybin_EvM(hiNtracks) == multBin )
		{


			trackTree->GetEntry(iEv);
			int nTrk = tTracks.nTrk;

	 		for (int iTrk = 0; iTrk < nTrk; iTrk++)
			{

				// TRACK SELECTION //
				if ( !TrackSelection(tTracks, iTrk ) ) continue;

  				float p = tTracks.trkPt[iTrk] * cosh(tTracks.trkEta[iTrk]);
				int PID   = GetPID(p, tTracks.dedx[iTrk], tTracks.trkEta[iTrk]);

				int ptBin_CH = ptbin(   0 , tTracks.trkPt[iTrk]);
				int ptBin_ID = ptbin( PID , tTracks.trkPt[iTrk]);
		
				bool isOutsideReferencePartPtRange = ( ( tTracks.trkPt[iTrk] < ptref1 ) || ( ptref2 < tTracks.trkPt[iTrk] ) );
				bool isOutsideIdentifHadronPtRange = ( ptBin_ID == -1);
				bool isOutsideChargedHadronPtRange = ( ptBin_CH == -1);
		
				if ( isOutsideReferencePartPtRange && isOutsideChargedHadronPtRange && isOutsideIdentifHadronPtRange ) continue;	
				// TRACK SELECTION //
	
				// Track fill up
				track trk;
				trk.charge  = tTracks.trkCharge[iTrk];
				trk.pid  	= PID;
				trk.pt      = tTracks.trkPt[iTrk];
				trk.phi     = tTracks.trkPhi[iTrk];
				trk.eta     = tTracks.trkEta[iTrk];
	
				ev->AddTrack(trk);
			}

					
			ev->EventID = iEv;
			EventCache[multBin][zvtxBin].push_back( (*ev) );
			count++;

			ev->Clear(nCorrTyp, nPtBins);

		}

		// Event counter info
		if ( ((iEv % 10000) == 0) || (count == 11) )
		{ std::cout << Form("multBin: %02d, zvtxBin: %02d, event: %05d, found: %02d/10", multBin, zvtxBin, iEv, count) << std::endl; }


		iEv++;
	 }

 }

 std::cout << "Preloading completed." << std::endl << std::endl;
 std::cout << "EventCache statistics:" << std::endl;

 // Deleting first elements of deque
 for(int multBin = 0; multBin < nMultiplicityBins_EvM; multBin++)
 for(int zvtxBin = 0; zvtxBin < nZvtxBins_; zvtxBin++)
 { 
	EventCache[multBin][zvtxBin].pop_front();
   std::cout << Form("multBin: %3d, zvtxBin: %3d, found: %2d/10", multBin, zvtxBin, EventCache[multBin][zvtxBin].size()) << std::endl;
 }


 ///////////////////////////
 //                       //
 // ***** ANALYISIS ***** //
 //                       //
 ///////////////////////////
 
 if (nEvMax == -1) {nEvMax = trackTree->GetEntries();}
 for (int iEvA = 0; iEvA < nEvMax; iEvA++)
 {
	
	// Event counter info
	if ( (iEvA % 1000) == 0 )
	{ std::cout << "Event: " << iEvA << std::endl; }

	// Get current event info
	EvtAna->GetEntry(iEvA);

	// Event Selection
	if ( !EvSel.isGoodEv_pPb( iEvA ) ) continue;
	if ( zvtxbin(vz, nZvtxBins) == -1 ) continue;
	CFW.nEvents_Processed_signal_total->Fill(0.);
	if ( multiplicitybin_Ana(hiNtracks, nMultiplicityBins_Ana) == -1) continue;
	CFW.nEvents_Processed_signal[ multiplicitybin_Ana(hiNtracks, nMultiplicityBins_Ana) ]->Fill(0.);

 	ev->Clear(nCorrTyp, nPtBins);

	ev->EventID = iEvA;
	ev->SetnTrk(hiNtracks);
	ev->SetzVtx(vz);

	// Statistics
	CFW.nEvents_Processed_signal_total->Fill(1.);
	CFW.nEvents_Processed_signal[ multiplicitybin_Ana(hiNtracks, nMultiplicityBins_Ana) ]->Fill(1.);
	nTrkDistr_signal->Fill( hiNtracks );
	
	CFW.ResetCurrentEventCorrelation();

	// Load in tracks
	trackTree->GetEntry(iEvA);

	// Read in event
	ev->ReadInDATA(tTracks, dEdxvsp);

	CFW.SignalCorrelation(ev);
	CFW.MixedCorrelation(ev, EventCache);
	CFW.AddCurrentEventCorrelation(ev);

 }
 
 //////////////////////
 //                  //
 // **** OUTPUT **** //
 //                  //
 //////////////////////
 
 output->Write();
 output->Close();


}
