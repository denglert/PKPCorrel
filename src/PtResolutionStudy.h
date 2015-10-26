#ifndef PTRESOLUTIONSTUDY_H
#define PTRESOLUTIONSTUDY_H

#include <string>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TH3D.h>
#include <TRandom3.h>
#include <TVectorD.h>
#include <iostream>
#include <TVector.h>
#include "GraphTools.h"
#include "PIDUtils.h"
#include "SetupCustomTrackTree.h"
#include "UtilFunctions.h"
#include "AnalysisBinning.h"

#define loop2(x, y, nx, ny) for( int x = 0; x < nx; x++)for( int y = 0; y < ny; y++)

const float ptbounds[4][2] =
{
	{0.2,3.0},
	{0.2,1.0},
	{0.2,0.9},
	{0.2,1.6}
};

class PtRes
{
	public:

	PtRes();
	~PtRes();

	// -- -- //
	std::string tag;
	TFile *f_inp;
	TFile *f_out;

	// -- Setup function -- //
	void SetupForProcess();
	void SetupForFit();
	void SetupForSmearing();

	// -- Processing -- //
	void OpenFile(const char filename[]);
	void SetupOutFile();
	void WriteFitResultsToFile ( );

	void Fit();

	// -- make figure -- //
	
	void makeFigPtRecPtSim();
	void makeFigSigmaPtDep();

	// -- Distribution -- // 
	
	TRandom3 *randgen;
	double GetRand( int TypBin, int ptBin);
	void testRand();

	// -- Binning -- //
	
	int nCorrTyp;
	int nPtBins ;
	
	int *nPtBins_;

	float PtMin;
	float PtMax;
	float PtBinWidth;
	double **PtBinCenter;

	// -- RelDiffPt- - //
	
	TH1D ***RelDiffPt;
	TF1  ***RelDiffPt_Func;

	double **RelDiffPtSigma;
	double **RelDiffPtMean ;

	TVectorD ***PtResolutionParams;

	int nRelDiffPtBins ;
	double RelDiffPtMin;
	double RelDiffPtMax;

	// -- PtRecSimMatrix -- //
	TH2D **PtRecSimMatrix;

	int    PtRecSimMatrix_nxBins;
	double PtRecSimMatrix_xMin  ;
	double PtRecSimMatrix_xMax  ;

	int    PtRecSimMatrix_nyBins;
	double PtRecSimMatrix_yMin  ;
	double PtRecSimMatrix_yMax  ;

	// -- Util functions -- //
	
	void StdPrintBinning();
	int GetPtBin(float pt);
	float PtBinLow ( int ptBin );
	float PtBinHigh( int ptBin );

};

#endif
