#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TNtuple.h>
#include <iostream>
#include <deque>
#include "AnalysisFW.h"
#include "AnalysisBinning.h"
#include "PIDUtils.h"
#include "SetupCustomTrackTree.h"

void plottable( TH3D **table, const char figbasename[] )
{
	int nParticles = 4;
	const int npt[4]      = {20,    10,   5,  5};
	const double ptMin[4] = {0.1, 0.15, 0.15, 0.15};
	const double ptMax[4] = {3.0, 1.00, 1.00, 1.8 };
	
	double ptbw[4];
	for(int i = 0; i < nParticles; i++)
	{ ptbw[i] = (ptMax[i]-ptMin[i])/npt[i]; }
	
	for (int pid = 0; pid < nParticles; pid++)
	for (int ptBin = 1; ptBin < npt[pid]; ptBin++)
	{
	  TCanvas canvas_table ("trkTable", ";Eta;Phi", 900, 600);
	  canvas_table.Divide(2,1);
	
	  table[pid]->GetXaxis()->SetRange(ptBin, ptBin+1);
	  TH2D *histo = (TH2D*)table[pid]->Project3D("zy");
	
	  canvas_table.cd(1);
		histo->Draw("SURF1");
	  canvas_table.cd(2);
		histo->Draw("COLZ");
	
		std::string tableFigBase = Form("%s_typ_%d_pt_%d-%d", figbasename, pid, ptBin, ptBin+1);
	
		std::string tableFigPNG = tableFigBase+".png";
		std::string tableFigPDF = tableFigBase+".pdf";
	
		canvas_table.SaveAs(tableFigPNG.c_str() );
		canvas_table.SaveAs(tableFigPDF.c_str() );
	}
}

int main( int argc, const char *argv[] )
{ 

 if(argc != 2)
 {
   std::cerr << "Usage: TrackCorrection_viewer <trkCorr.root file to be displayed>" << std::endl;
   exit(1);
 }

 TString inpFilename     = argv[1];

 // Open file
 TFile *f = TFile::Open(inpFilename);
 if ( f->IsZombie() ) {std::cerr << "Error opening file: " << inpFilename << std::endl; exit(-1);}
 else {std::cout << "File successfully opened." << std::endl;}

 TH3D **trkCorr    = Read_trkEff( f, "hcorr typ" );
 TH3D **hfake      = Read_trkEff( f, "hfake typ" );
 TH3D **hreco      = Read_trkEff( f, "hreco typ" );
 TH3D **hsecondary = Read_trkEff( f, "hsecondary typ" );
 TH3D **hreal      = Read_trkEff( f, "hreal typ" );
 TH3D **hgen       = Read_trkEff( f, "hgen typ" );
 TH3D **hmatched   = Read_trkEff( f, "hmatched typ" );
 TH3D **hmultrec   = Read_trkEff( f, "hmultrec typ" );

 plottable( trkCorr,    "trkCorr");
 plottable( hfake,      "hfake");
 plottable( hreco,      "hreco");
 plottable( hsecondary, "hsecondary");
 plottable( hreco,      "hreal");
 plottable( hgen,       "hgen");
 plottable( hmatched,   "hmatched");
 plottable( hmultrec,   "hmultrec");

}
