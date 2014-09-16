#ifndef ANALYSISFW_H
#define ANALYSISFW_H
#include <vector>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include "PIDUtils.h"
#include <TFile.h>
#include "SetupCustomTrackTree.h"

////////////////////
// Event Data Class
class track
{
	public:
	int pid;
	int charge;
   float pt;        
   float phi;			
   float eta;			
};

class EventData
{
	public:
	int EventID;
   std::vector<track> tracks;

   int **nTriggerParticles;
   int nTriggerParticles_cpar_ref;

	float zVtx; 
	int   nTrk;

	void AddTrack(const track& p);
	int GetnTracks ();

	void Setup_nTriggerParticles(int nCorrTyp, int *nPtBins);
	void SetzVtx(float zVtx_);
	void SetnTrk(int nTrk_);

	int GetzVtxBin();
	int GetMultiplicityBin();
	int GetMultiplicityBin_Ana(int nMultiplicityBins_Ana);
	int GetMultiplicityBin_EvM();

	void ReadIn(Tracks &tTracks, TH2D *dEdxvsP);

	void Clear(int nCorrTyp, int *nPtBins);
};

 
extern const int nMixEv;

// Event & TrackSelection
bool EventSelection( const int &pPAcollisionEventSelection, const int &pileUpBit );
bool TrackSelection( const Tracks &tTracks, int iTrk );


class AnalysisFW
{
	public:

	// === Constructor === //
	AnalysisFW();

	// === Variables === //
	
	TH1D *nEvents_Processed_total;
 	TH1D *nTrk_Distr;

	// === Functions === //
	void Setup();
	void CountPassedEvent();
	void CountProcessedEvent();
	void FillnTrk( int nTrk);

};

/////////////////////////////////
// Setup function
void Setup_nEvents_Processed (TH1D *&nEvents_Processed_signal_total, TH1D *&nEvents_Processed_backgr_total, TH1D **&nEvents_Processed_signal, TH1D **&nEvents_Processed_backgr, int nMultiplicityBins );

///////////////////////
// Read In function
void Read_nEvents_Processed(TFile *f, TH1D **&nEvents_Processed_signal, TH1D **&nEvents_ProcessedBit_backgr, int nMultiplicityBins );

///////////////////////////////
// AnalysisFW functions

//void plotEtaDistr(TH1D *EtaDistrHisto, std::string path, std::string label)

void prepareDIR( std::string tag );

#endif
