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
#include <TRandom.h>
#include <iostream>
#include <TVector.h>
#include "GraphTools.h"
#include "AnalysisBinning.h"
#include "PIDUtils.h"
#include "AnalysisFW.h"
#include "SetupCustomTrackTree.h"
#include "EvtSelection.h"
#include "EvtAnalyzer.h"

#define loop2(x, y, nx, ny) for( int x = 0; x < nx; x++)for( int y = 0; y < ny; y++)

class PtRes
{
	public:

	PtRes();
	~PtRes();

	TFile *f_inp;
	TFile *f_out;

	void OpenFile(const char filename[]);
	void SetupForProcess();
	void SetupForFit();
	void StdPrintBinning();
	void makeFigPtRecPtSim();

	void Fit();

	TRandom3 rand;
	double GetRand;
	void testRand();

	int nPtBins ;
	float PtMin;
	float PtMax;
	float PtBinWidth;
	int nCorrTyp;
	
	int nRelDiffPtBins ;
	double RelDiffPtMin;
	double RelDiffPtMax;

	int    PtRecSimMatrix_nxBins;
	double PtRecSimMatrix_xMin  ;
	double PtRecSimMatrix_xMax  ;

	int    PtRecSimMatrix_nyBins;
	double PtRecSimMatrix_yMin  ;
	double PtRecSimMatrix_yMax  ;

	TH1D ***RelDiffPt;
	TF1  ***RelDiffPt_Func;
	double **RelDiffPtSigma;
	double **RelDiffPtMean ;

	TH2D **PtRecSimMatrix;

	TVectorD ***PtResolutionParams;

	int ptBin(float pt);
	float PtBinLow ( int ptBin );
	float PtBinHigh( int ptBin );

};

#endif
