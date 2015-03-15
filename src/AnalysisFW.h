#ifndef ANALYSISFW_H
#define ANALYSISFW_H
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include "PIDUtils.h"
#include <TFile.h>
#include <TH3D.h>
//#include "../HiForestAnalysis/hiForest.h"
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

class LogFile
{
	public:
   LogFile(const char filename[]);
   ~LogFile(){};

	std::ofstream ofs;
	int repeat;
	std::string label;

	void wr( const char str[]);
	void EventCounter( int iEv);
	void Close();
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

	void ReadInDATA(const Tracks &tTracks, TH2D *dEdxvsP, PIDUtil *pidutil);
	void ReadInMC  (Tracks &tTracks);

	void Clear(int nCorrTyp, int *nPtBins);
};

 
extern const int nMixEv;

// Event & TrackSelection
bool EventSelection( const int &pPAcollisionEventSelection, const int &pileUpBit );
bool TrackSelection( const Tracks &tTracks, int iTrk );
bool TrackSelection_c( const Tracks_c &tTracks, int iTrk );
bool mTrackSelection_c( const Tracks_c &tTracks, int iTrk );
double trackWeight (TH3D **trackCorr, int PID, double pt, double eta, double phi, bool doTable);

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

TH3D **Read_TH3D_1Darray(TFile *f, const char histoname[], const int nBins);
TH2D **Read_TH2D_1Darray(TFile *f, const char histoname[], const int nBins);
TH1D **Read_TH1D_1Darray(TFile *f, const char histoname[], const int nBins);
///////////////////////////////
// AnalysisFW functions

//void plotEtaDistr(TH1D *EtaDistrHisto, std::string path, std::string label)

void prepareDIR( std::string tag );

#endif
