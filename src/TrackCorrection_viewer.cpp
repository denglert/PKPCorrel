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
	gStyle->SetOptStat(0);
	int nParticles = 4;
const int npt[4]      = {20,    10,   5,  5};
const double ptMin[4] = {0.1, 0.15, 0.15, 0.15};
const double ptMax[4] = {3.0, 1.00, 1.00, 1.8 };
//const int npt[4]      = {1,    1,   1,  1};
//const double ptMin[4] = {0.3, 0.15, 0.15, 0.15};
//const double ptMax[4] = {0.5, 0.40, 0.40, 0.4 };

	
	double ptbw[4];
	for(int i = 0; i < nParticles; i++)
	{ ptbw[i] = (ptMax[i]-ptMin[i])/npt[i]; }
	
	for (int pid = 0; pid < nParticles; pid++)
	for (int ptBin = 1; ptBin < (npt[pid]+1); ptBin++)
	{
		TCanvas canvas_table ("trkTable", ";Eta;Phi", 900, 600);
	  	canvas_table.Divide(2,1);
	
	  	table[pid]->GetXaxis()->SetRange(ptBin, ptBin);
	  	TH2D *histo = (TH2D*)table[pid]->Project3D("zy");

		histo->SetTitle("");
		histo->GetXaxis()->SetTitleOffset(1.6);
		histo->GetYaxis()->SetTitleOffset(1.6);
		histo->GetZaxis()->SetTitleOffset(1.6);
	
	  	canvas_table.cd(1);

		if ( pid != 0)
		{ histo->GetXaxis()->SetRangeUser(-0.8,0.75); }

	  	histo->Draw("SURF1");
	  	canvas_table.cd(2);
	   histo->Draw("COLZ");

		double pt1 = ptMin[pid] + ptbw[pid] * (ptBin-1);
		double pt2 = ptMin[pid] + ptbw[pid] * (ptBin );
	
		std::string tableFigBase = Form("%s_typ_%d_pt_%.3f-%.3f", figbasename, pid, pt1, pt2);
		
		std::string tableFigPNG = tableFigBase+".png";
		std::string tableFigPDF = tableFigBase+".pdf";
		
		canvas_table.SaveAs(tableFigPNG.c_str() );
		canvas_table.SaveAs(tableFigPDF.c_str() );

//	  	canvas_table.cd(1);
//	  	histo->GetXaxis()->SetRangeUser(-1.0,1.0);
//	  	histo->Draw("SURF1");
//	  	canvas_table.cd(2);
//	   histo->Draw("COLZ");
//
//		tableFigBase = Form("etacut_1_%s_typ_%d_pt_%.3f-%.3f", figbasename, pid, pt1, pt2);
// 	
//		tableFigPNG = tableFigBase+".png";
//		tableFigPDF = tableFigBase+".pdf";
//		
//		canvas_table.SaveAs(tableFigPNG.c_str() );
//		canvas_table.SaveAs(tableFigPDF.c_str() );

//	  	canvas_table.cd(1);
//
//		{ histo->GetXaxis()->SetRangeUser(-0.8,0.75); }
//
//	  	histo->Draw("SURF1");
//	  	canvas_table.cd(2);
//	   histo->Draw("COLZ");
//
//		tableFigBase = Form("%s_typ_%d_pt_%.3f-%.3f_etacut_0.8", figbasename, pid, pt1, pt2);
//		
//		tableFigPNG = tableFigBase+".png";
//		tableFigPDF = tableFigBase+".pdf";
//		
//		canvas_table.SaveAs(tableFigPNG.c_str() );
//		canvas_table.SaveAs(tableFigPDF.c_str() );

//	  	canvas_table.cd(1);
//	  	histo->GetXaxis()->SetRangeUser(-1.5,1.5);
//	  	histo->Draw("SURF1");
//	  	canvas_table.cd(2);
//	   histo->Draw("COLZ");
//
//		tableFigBase = Form("etacut_1.5_%s_typ_%d_pt_%.3f-%.3f", figbasename, pid, pt1, pt2);
//		
//		tableFigPNG = tableFigBase+".png";
//		tableFigPDF = tableFigBase+".pdf";
//		
//		canvas_table.SaveAs(tableFigPNG.c_str() );
//		canvas_table.SaveAs(tableFigPDF.c_str() );

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

 TH3D **trkCorr      = Read_trkEff( f, "hcorr typ" );
 TH3D **hfake        = Read_trkEff( f, "hfake typ" );
 TH3D **hreco        = Read_trkEff( f, "hreco typ" );
 TH3D **hsecondary   = Read_trkEff( f, "hsecondary typ" );
 TH3D **hreal        = Read_trkEff( f, "hreal typ" );
 TH3D **hgen         = Read_trkEff( f, "hgen typ" );
 TH3D **hmatched     = Read_trkEff( f, "hmatched typ" );
 TH3D **hmultrec     = Read_trkEff( f, "hmultrec typ" );
 TH3D **hmultrecrate = Read_trkEff( f, "hmultrecrate part" );
 TH3D **heff         = Read_trkEff( f, "heff part" );

 hmultrecrate[0]->GetXaxis()->SetRange(3, 3);
 TH1D* multrecratex = (TH1D*)hmultrecrate[0]->Project3D("y");
 TCanvas canvas_multrec ("multrec", ";Eta", 800, 600);
 multrecratex->Draw();
 multrecratex->GetXaxis()->SetRangeUser(-2.3,2.3);
 canvas_multrec.SaveAs( "multrecrate.png");

 plottable( hgen,       "hgen");
 plottable( trkCorr,    "trkCorr");
 plottable( heff,       "heff");
 plottable( hfake,      "hfake");
 plottable( hreco,      "hreco");
 plottable( hsecondary, "hsecondary");
 plottable( hreco,      "hreal");
 plottable( hmatched,   "hmatched");
 plottable( hmultrec,   "hmultrec");
 plottable( hmultrecrate, "hmultrecrate");

}
