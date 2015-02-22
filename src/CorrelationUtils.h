#ifndef CORRELATIONUTILS_H
#define CORRELATIONUTILS_H
#include <TH2D.h>
#include <deque>
#include <string>
#include "AnalysisBinning.h"
#include "AnalysisFW.h"
#include <TGraphErrors.h>

//////////////////////////////////////
//   *  Correl1DfitResultsData  *   //
//////////////////////////////////////

struct Correl1DfitResultsData
{
	double chisqrdperndf;
	
	double a0;
	double V1;
	double V2;
	double V3;

	double a0_Error;
	double V1_Error;
	double V2_Error;
	double V3_Error;
};

/////////////////////////////
//   *  CorrelResults  *   //
/////////////////////////////


struct CorrelResults
{
	double v2;
	double v2_SystError;
	double v2_StatError;

	double v3;
	double v3_SystError;
	double v3_StatError;
};

/////////////////
// * dEtacut * //
/////////////////
struct detacut
{
	int negdEtaCut1Bin;
	int negdEtaCut2Bin;
	int posdEtaCut1Bin;
	int posdEtaCut2Bin;
};

/////////////////////////////////////////
//                                     //
//  *  class CorrelationFramework  *   //
//                                     //
/////////////////////////////////////////

class CorrelationFramework
{
	public:

	// === Constructor === //
	CorrelationFramework( int nCorrTyp_a, int *nPtBins_a, int nMultiplicityBins_Ana_, int nMultiplicityBins_EvM_);

	// === Variables === //
	
	bool DoSelfCorrelation;
	bool DoTrackWeight;

	// Project tag
	std::string tag;

	// AnalysisBinning
	AnalysisBinning *AnaBin;

	// Output dump
	TFile *Corr_Results;
	
	// correl2D current event
 	TH2D ***correl2D_currev_signal;
 	TH2D ***correl2D_currev_backgr;

	TH2D ***correl2D_self_currev_signal;
 	TH2D ***correl2D_self_currev_backgr;

 	TH2D *correl2D_currev_cpar_ref_signal;
 	TH2D *correl2D_currev_cpar_ref_backgr;

	// correl2D all event
	TH2D ****correl2D_functi;
 	TH2D ****correl2D_signal;
 	TH2D ****correl2D_backgr;

 	TH2D ****correl2D_self_functi;
 	TH2D ****correl2D_self_signal;
 	TH2D ****correl2D_self_backgr;

 	TH2D **correl2D_cpar_ref_functi;
 	TH2D **correl2D_cpar_ref_signal;
 	TH2D **correl2D_cpar_ref_backgr;

	// correl1D
 	TH1D ****correl1D;
 	TH1D ****correl1D_self;
 	TH1D   **correl1D_cpar_ref;

	// Log
	LogFile *log;

	// TrackCorrection table
	TH3D **trkCorr;

	// number of events counter
	TH1D  *nEvents_Processed_signal_total;
 	TH1D  *nEvents_Processed_backgr_total;
 	TH1D **nEvents_Processed_signal;
 	TH1D **nEvents_Processed_backgr;

	// variables holding the results
	CorrelResults 			  ***correl_Results;
	CorrelResults 			  ***correl_Results_self;
	CorrelResults 			    *correl_Results_cpar_ref;

	Correl1DfitResultsData ***correl1D_FitResults;
	Correl1DfitResultsData ***correl1D_FitResults_self;
	Correl1DfitResultsData   *correl1D_FitResults_cpar_ref;

	// === Functions === //
	void SetupForProcess();
	void SetupForPreprocess();
	void ReadIn_CorrelationFuncs( TFile *f );
	void Set_dEtacut( int negdEtaCut1Bin, int negdEtaCut2Bin, int posdEtaCut1Bin, int posdEtaCut2Bin );
	void Set_dEtacut( );

	double trackWeight(int PID, float pt, float eta, float phi);

	void SignalCorrelation(EventData *ev);
	void MixedCorrelation( EventData *ev, std::deque< EventData > ***EventCache);
	void AddCurrentEventCorrelation( EventData* ev);
	void ResetCurrentEventCorrelation();
	void doAnalysis();

	void Calcvns();

	void ReBin();
	void display_v2s();

	void makeFigCorrel1D(std::string tag);
	void makeFigCorrel2D( std::string tag );
	void makeFigv2vspT(int TypBin, int multBin, std::string tag);
	void makeFigv2vspT_allparticles(int multBin, std::string tag);
	void makeFigv2vspT_allparticles_ALICE_comparison(int multBin, std::string tag);
	void makeFigv2vspT_HIN13002(std::string tag);
	void makeFigv3vspT_allparticles(int multBin, std::string tag);
	void makeFigv2vspT_allparticles_with_selfcorrelation(int multBin, std::string tag);
	void makeFigv2vsnTrk_cpar_ref( std::string tag );
	void makeFigv2vsnTrk_allparticles( std::string tag );

	TGraphErrors Getv2TGraphError (int TypBin, int multBin);
	std::vector< double > Getptvec      ( int TypBin, double offset );
	std::vector< double > GetnTrkvec  ( double offset );
	std::vector< double > Get_cpar_ref_v2vec_nTrk ();
	std::vector< double > Get_cpar_ref_v2_StatError_vec_nTrk ();

	std::vector< double > GetV2vec      ( int TypBin, int multBin);
	std::vector< double > GetV2_Errorvec( int TypBin, int multBin);

	std::vector< double > Getv2vec      ( int TypBin, int multBin);
	std::vector< double > Getv3vec      ( int TypBin, int multBin);

	std::vector< double > Getv2_StatErrorvec( int TypBin, int multBin);
	std::vector< double > Getv3_StatErrorvec( int TypBin, int multBin);
	std::vector< double > Getv2_SystErrorvec( int TypBin, int multBin);
	std::vector< double > Getv3_SystErrorvec( int TypBin, int multBin);

	std::vector< double > Get_self_v2vec ( int TypBin, int multBin);
	std::vector< double > Get_self_v2_StatErrorvec ( int TypBin, int multBin);

	// Setup functions
	void Setup_TH2D_nCorrnPt(TH2D ***&correl2D, const char histoname[], const char tag[]);
	void Setup_TH2D_nCorrnPtnMult( TH2D ****&correl2D, const char histoname[], const char tag[]);
	void Setup_TH2D_nMult( TH2D **&correl2D, const char histoname[], const char tag[], double pt1, double pt2);

	private:
	detacut dEtacut;
	int nCorrTyp;
	int *nPtBins;
	int nMultiplicityBins_Ana;
	int nMultiplicityBins_EvM;

};


////////////////////////////////////////////
//                                        // 
//  *  Correlation analysis functions  *  //
//                                        //
////////////////////////////////////////////

Correl1DfitResultsData doAnalysisSteps(TH2D *correl_signal, TH2D *correl_backgr, TH2D *correl_functi, TH1D *correl_1D, TH1D *nEvents_Processed_signal, TH1D *nEvents_Processed_backgr, detacut dEtacut);

void normalizeBynEvents(TH2D* correl, TH1D* nEvents_Processed);

void makeCorrelationFunction (TH2D* correl_signal, TH2D* correl_backgr, TH2D* correl_functi);
void sum_and_project2Dto1D(TH2D *correl_signal, TH2D *correl_backgr, TH1D* correl_1D, detacut dEtacut);
void project2Dto1D(TH2D *correl_functi, TH1D* correl_1D, detacut dEtacut);
void project2Dto1D_weightedmean(TH2D *correl_functi, TH1D* correl_1D, detacut dEtacut);

void fit1DCorrelation(TH1D *correl_1D, CorrelationFramework *results, int TypBin, int ptBin, int multBin, std::string figurename, std::string label);
Correl1DfitResultsData fit1DCorrelation_noplot(TH1D *correl_1D);
Correl1DfitResultsData fit1DCorrelation(TH1D *correl_1D, std::string figurename, std::string label);

void makeFig2DCorrel(TH2D ****correl_signal, TH2D ****correl_backgr, TH2D ****correl_functi, std::string tag, int nCorrTyp, int *nPtBins, int nMultiplicityBins);

void plot2DCorrelation_custom(TH2D* correl, std::string figurename, std::string title);
void plot2DCorrelation       (TH2D* correl, std::string figurename, std::string title, std::string zaxistitle, std::string leftlabel, std::string rightlabel);
void plotV2vspT(struct correlationinfo CorrelationInfo, std::string path, int nPtBins, std::string label);

///////////////////////////////////////
// Utility functions
double dEta (double Eta1, double Eta2);
double dPhi (double Phi1, double Phi2);


///////////////////////////////
//                           //
//  *  Read In functions  *  //
//                           //
///////////////////////////////

void Read_CorrelationFuncs(TFile *f, TH2D ****&correl2D_signal, TH2D ****&correl2D_backgr, TH2D **&correl2D_cpar_ref_signal, TH2D **&correl2D_cpar_ref_backgr, int nCorrTyp, int *nPtBins, int nMultiplicityBins);
void ReadIn_TH2Ds_nCorrnPtnMult(TFile *f, TH2D ****&correl2D, int nCorrTyp, int *nPtBins, int nMultiplicityBins, const char histoname[], const char tag[]);
void ReadIn_TH2Ds_nMult(TFile *f, TH2D **&correl2D, int nMultiplicityBins, const char histoname[], const char tag[], double pt1, double pt2);

////////////////////////////////
//                            //
//   *  Setup functions  *    //
//                            //
////////////////////////////////

void Setup_EventCache( std::deque< EventData > **&EventCache, int nMultiplicityBins, int nZvtxBins);

void Setup_TH2Ds_nCorrnPt( TH2D ***&correl2D, int nCorrTyp, int *nPtBins, const char histoname[], const char tag[]);
void Setup_TH2Ds_nCorrnPtnMult( TH2D ****&correl2D, int nCorrTyp, int *nPtBins, int nMultiplicityBins, const char histoname[], const char tag[]);
void Setup_TH2Ds_nMult( TH2D **&correl2D, int nMultiplicityBins, const char histoname[], const char tag[], double pt1, double pt2);


void Setup_TH1Ds_nCorrnPtnMult( TH1D ****&correl1D, int nCorrTyp, int *nPtBins, int nMultiplicityBins, const char histoname[], const char tag[]);
void Setup_TH1Ds_nMult( TH1D **&correl1D, int nMultiplicityBins, const char histoname[], const char tag[]);


void Setup_Correl1DfitResultsData_nCorrnPtnMult( Correl1DfitResultsData ***&correl1D_FitResults, int nCorrTyp, int *nPtBins, int nMultiplicityBins );
void Setup_CorrelResults_nCorrnPtnMult( CorrelResults ***&correl_Results, int nCorrTyp, int *nPtBins, int nMultiplicityBins );
void Setup_correl2D_currev_cpar_ref( TH2D *&correl2D_currev_cpar_ref, const char tag[], double pt1, double pt2);

#endif
