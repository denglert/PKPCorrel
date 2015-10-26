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
#include "TLatex.h"
#include "GraphTools.h"
#include "ContMatrix.h"


const int    npt   = 14;
const double ptMin = 0.2;
const double ptMax = 1.6;
const double ptbw  = 0.1;

// -- Shifting Contamination matrix -- //
bool doShift = true;
double pionshift = 0.01;
double kaonshift = 0.20;
double protshift = 0.20;


const int nRegions = 3;
double ShiftMatrix[nRegions][3][3] =
									{
										{
										{-pionshift/1.0,+pionshift/1.0,0.000000000000},
										{+kaonshift/1.0,-kaonshift/1.0,0.000000000000},
										{+protshift/2.0,+protshift/2.0,-protshift/1.0}
										},

										{
										{-pionshift/1.0,+pionshift/1.0,0.000000000000},
										{+protshift/1.0,-protshift/1.0,0.000000000000},
										{0.000000000000,0.000000000000,0.000000000000},
										},

										{
										{-protshift/1.0,+protshift/1.0,0.000000000000},
										{0.000000000000,0.000000000000,0.000000000000},
										{0.000000000000,0.000000000000,0.000000000000}
										}

									};

int main( int argc, const char *argv[] )
{ 


 gStyle->SetOptStat(0);

 TH1::SetDefaultSumw2( );
 TH2::SetDefaultSumw2( );

 if(argc != 3)
 {
   std::cerr << "Usage: MC_Contamination_viewer <trkCorr.root file to be displayed> <PIDConfig>" << std::endl;
   exit(1);
 }

 TString inpFilename     = argv[1];
 std::string PIDconfig	 = argv[2];

 // Open file
 TFile *f = TFile::Open(inpFilename);
 if ( f->IsZombie() ) {std::cerr << "Error opening file: " << inpFilename << std::endl; exit(-1);}
 else {std::cout << "File successfully opened." << std::endl;}

 ////////////////////////
 // Read In histograms //
 ////////////////////////
 
 TH2D *dEdxvsPMapsLin[npt];
 TH2D *dEdxvsPMapsLog[npt];

 TH2D *matrix[npt];

 TH2D *ptres = (TH2D*)f->Get("ptres");

 for( int ptBin = 0; ptBin < npt; ptBin++ )
 {

   double pt1 = (ptMin + (ptBin  ) * ptbw);
	double pt2 = (ptMin + (ptBin+1) * ptbw);

	matrix[ptBin] = (TH2D*)f->Get(Form("contmatrix_pt_%.2f-%.2f", pt1, pt2));

	dEdxvsPMapsLin[ptBin] = (TH2D*)f->Get(Form("dEdxvsPMapsLin_pt_%.2f-%.2f", pt1, pt2) );
	dEdxvsPMapsLog[ptBin] = (TH2D*)f->Get(Form("dEdxvsPMapsLog_pt_%.2f-%.2f", pt1, pt2) );

 }


 //const int nTypBins = 5;
 //TH1D *identi[nTypBins];
 //TH1D *contam[nTypBins];
 //TH1D *purity[nTypBins];

 //identi[0] = (TH1D*)f->Get("identi-char");
 //identi[1] = (TH1D*)f->Get("identi-pion");
 //identi[2] = (TH1D*)f->Get("identi-kaon");
 //identi[3] = (TH1D*)f->Get("identi-prot");
 //identi[4] = (TH1D*)f->Get("identi-nonprot");
 //
 //purity[0] = (TH1D*)f->Get("purity-char");
 //purity[1] = (TH1D*)f->Get("purity-pion");
 //purity[2] = (TH1D*)f->Get("purity-kaon");
 //purity[3] = (TH1D*)f->Get("purity-prot");
 //purity[4] = (TH1D*)f->Get("purity-nonprot");
 //            
 //contam[0] = (TH1D*)f->Get("contam-char");
 //contam[1] = (TH1D*)f->Get("contam-pion");
 //contam[2] = (TH1D*)f->Get("contam-kaon");
 //contam[3] = (TH1D*)f->Get("contam-prot");
 //contam[4] = (TH1D*)f->Get("contam-nonprot");
 //
 //for(int TypBin=0; TypBin<nTypBins; TypBin++)
 //{
 //	purity[TypBin]->Divide(identi[TypBin]);
 //	contam[TypBin]->Divide(identi[TypBin]);
 //}

 //TH1D *nPions 			= (TH1D*)f->Get("nPions");  

 //{
 //TCanvas canvas("canvas", "e #rightarrow# #pi fraction;p_{T} [GeV/c];", 1024, 780);
 //nPions->Draw("");

 //std::string figbasename = "nPions";
 //std::string outPNG = Form("%s.png", figbasename.c_str());
 //std::string outPDF = Form("%s.pdf", figbasename.c_str());
 //
 //canvas.SaveAs(outPDF.c_str());
 //canvas.SaveAs(outPNG.c_str());
 //}

 //TH1D *Electron2Pion = (TH1D*)f->Get("Electron2Pion");

 //{
 //TCanvas canvas("canvas", "e #rightarrow# #pi fraction;p_{T} [GeV/c];", 1024, 780);
 //Electron2Pion->Draw("");

 //std::string figbasename = "Electron2Pion";
 //std::string outPNG = Form("%s.png", figbasename.c_str());
 //std::string outPDF = Form("%s.pdf", figbasename.c_str());
 //
 //canvas.SaveAs(outPDF.c_str());
 //canvas.SaveAs(outPNG.c_str());
 //}

 //Electron2Pion->Divide(nPions);

 ////////////////////////////////
 //                            //
 // ***** Setting output ***** //
 //                            //
 ////////////////////////////////
 
 TFile *output = new TFile( "./Cont_Matrix.root", "RECREATE");
 output->cd();

 /////////////////////////
 //                     //
 // ***** Prepare ***** //
 //                     //
 /////////////////////////

 TH2D *cont_matrix_nor_TH2D[CM::nPt];
 TH2D *cont_matrix_inv_TH2D[CM::nPt];
 TMatrix *cont_matrix_nor_TMatrix[CM::nPt];
 TMatrix *cont_matrix_inv_TMatrix[CM::nPt];

 for( int RgnBin = 0; RgnBin < CM::nRegions; RgnBin++ )
 for( int i = 0; i < CM::nPtBins[RgnBin]; i++ )
 {

		int ptBin = CM::PtBins[1][RgnBin][i];

   	double pt1 = (CM::ptMin + (ptBin  ) * CM::PtBw);
		double pt2 = (CM::ptMin + (ptBin+1) * CM::PtBw);

		std::string matrixname = Form("cont_matrix_pt_%.2f-%.2f", pt1, pt2);

		CM::CopyTH2DtoTH2D   ( matrix[ptBin], cont_matrix_nor_TH2D[ptBin],    matrixname.c_str(), CM::Indices[RgnBin] );
		CM::normalizeMatrix_TH2D( cont_matrix_nor_TH2D[ptBin] );


		int nSize = cont_matrix_nor_TH2D[ptBin]->GetNbinsX();
		if (doShift == true)
		{
		for (int i=1; i<(nSize+1); i++)
		for (int j=1; j<(nSize+1); j++)
		{
			double tempval = cont_matrix_nor_TH2D[ptBin]->GetBinContent(i,j);	
			double newval = tempval + ShiftMatrix[RgnBin][i-1][j-1]; 
			cont_matrix_nor_TH2D[ptBin]->SetBinContent(i,j,newval);
		}
		}

		// -- //

		CM::CopyTH2DtoTMatrix( cont_matrix_nor_TH2D[ptBin], cont_matrix_nor_TMatrix[ptBin],   CM::Indices_red[RgnBin] );
		cont_matrix_inv_TMatrix[ptBin] = (TMatrix*)cont_matrix_nor_TMatrix[ptBin]->Clone();
		cont_matrix_inv_TMatrix[ptBin]->Invert();

		CM::plotContMatrix( cont_matrix_nor_TH2D[ptBin], CM::Indices[RgnBin], matrixname.c_str() );

		CM::displayMatrix_TH2D( matrix[ptBin] );
		CM::displayMatrix_TH2D( cont_matrix_nor_TH2D[ptBin] );
		CM::displayMatrix_TMatrix( cont_matrix_nor_TMatrix[ptBin] );
		CM::displayMatrix_TMatrix( cont_matrix_inv_TMatrix[ptBin] );
 }


 TH2D *th2D_matrix[CM::nPt];

 ////////////////////////

// for( int ptBin = 0; ptBin < npt; ptBin++ )
// {
//   double pt1 = (ptMin + (ptBin  ) * ptbw);
//	double pt2 = (ptMin + (ptBin+1) * ptbw);
//
//	TCanvas canvas_matrix ("contmatrix", ";RECO;GEN", 800, 600);
//
//	gStyle->SetOptStat(0);
//	gStyle->SetPaintTextFormat("2.2f");
//	matrix[ptBin]->SetMarkerSize(2);
//
//	matrix[ptBin]->Draw("TEXT");
//
// 	matrix[ptBin]->GetXaxis()->SetRange(1, 3);
// 	matrix[ptBin]->GetYaxis()->SetRange(1, 3);
//
// 	matrix[ptBin]->GetXaxis()->SetLabelSize(0.05);
// 	matrix[ptBin]->GetYaxis()->SetLabelSize(0.05);
//
//	matrix[ptBin]->GetXaxis()->SetBinLabel(1, "#pi");
//	matrix[ptBin]->GetXaxis()->SetBinLabel(2, "K");
//	matrix[ptBin]->GetXaxis()->SetBinLabel(3, "p");
//	matrix[ptBin]->GetYaxis()->SetBinLabel(1, "#pi");
//	matrix[ptBin]->GetYaxis()->SetBinLabel(2, "K");
//	matrix[ptBin]->GetYaxis()->SetBinLabel(3, "p");
//
//	std::string filebasename = Form("matrix_pt_%.2f-%.2f", pt1, pt2);
//	std::string outPDF = filebasename+".pdf"; 
//	std::string outPNG = filebasename+".png";
//
//	canvas_matrix.SaveAs(outPDF.c_str());
//	canvas_matrix.SaveAs(outPNG.c_str());
//
// 	std::string dEdxvsplinFigBase = Form( "dEdxvspLin_typ_%.2f-%.2f", pt1, pt2 	);
// 	std::string dEdxvsplogFigBase = Form( "dEdxvspLog_typ_%.2f-%.2f", pt1, pt2 	);
//
// 	std::string dEdxvsplinFigPNG = dEdxvsplinFigBase+".png";
// 	std::string dEdxvsplinFigPDF = dEdxvsplinFigBase+".pdf";
// 	std::string dEdxvsplogFigPNG = dEdxvsplogFigBase+".png";
// 	std::string dEdxvsplogFigPDF = dEdxvsplogFigBase+".pdf";
//
//	makedEdxvspFigloglog( dEdxvsPMapsLog[ptBin], PIDconfig, dEdxvsplogFigPNG);
//	makedEdxvspFigloglog( dEdxvsPMapsLog[ptBin], PIDconfig ,dEdxvsplogFigPDF);
//	makedEdxvspFiglinlin( dEdxvsPMapsLin[ptBin], PIDconfig, dEdxvsplinFigPNG);
//	makedEdxvspFiglinlin( dEdxvsPMapsLin[ptBin], PIDconfig, dEdxvsplinFigPDF);
//
// }


  for( int ptBin = 0; ptBin < npt; ptBin++ )
  {

  	double pt1 = (ptMin + (ptBin  ) * ptbw);
 	double pt2 = (ptMin + (ptBin+1) * ptbw);


 	std::string dEdxvsplinFigBase = Form( "dEdxvspLin_typ_%.2f-%.2f", pt1, pt2 	);
 	std::string dEdxvsplogFigBase = Form( "dEdxvspLog_typ_%.2f-%.2f", pt1, pt2 	);

 	std::string dEdxvsplinFigPNG = dEdxvsplinFigBase+".png";
 	std::string dEdxvsplinFigPDF = dEdxvsplinFigBase+".pdf";
 	std::string dEdxvsplogFigPNG = dEdxvsplogFigBase+".png";
 	std::string dEdxvsplogFigPDF = dEdxvsplogFigBase+".pdf";

	makedEdxvspFigloglog( dEdxvsPMapsLog[ptBin], PIDconfig, dEdxvsplogFigPNG);
	makedEdxvspFigloglog( dEdxvsPMapsLog[ptBin], PIDconfig ,dEdxvsplogFigPDF);
	makedEdxvspFiglinlin( dEdxvsPMapsLin[ptBin], PIDconfig, dEdxvsplinFigPNG);
	makedEdxvspFiglinlin( dEdxvsPMapsLin[ptBin], PIDconfig, dEdxvsplinFigPDF);

  }

 plotTH2D(ptres, ";p_{T,gen} [GeV/c];p_{T,reco} [GeV/c]", "ptgenreco", "COLZ");

 output->cd();

 for( int RgnBin = 0; RgnBin < CM::nRegions; RgnBin++ )
 for( int i = 0; i < CM::nPtBins[RgnBin]; i++ )
 {
	int ptBin = CM::PtBins[1][RgnBin][i];

   double pt1 = (CM::ptMin + (ptBin  ) * CM::PtBw);
	double pt2 = (CM::ptMin + (ptBin+1) * CM::PtBw);

	std::string str_cont_matrix_nor_TH2D    = Form("cont_matrix_nor_TH2D_pt_%.2f-%2.2f", pt1, pt2);
	std::string str_cont_matrix_nor_TMatrix = Form("cont_matrix_nor_TMatrix_pt_%.2f-%2.2f", pt1, pt2);
	std::string str_cont_matrix_inv_TMatrix = Form("cont_matrix_inv_TMatrix_pt_%.2f-%2.2f", pt1, pt2);

	cont_matrix_nor_TH2D[ptBin]->Write(str_cont_matrix_nor_TH2D.c_str());
	cont_matrix_nor_TMatrix[ptBin]->Write(str_cont_matrix_nor_TMatrix.c_str());
	cont_matrix_inv_TMatrix[ptBin]->Write(str_cont_matrix_inv_TMatrix.c_str());

 }

// {
// TCanvas canvas("canvas", "e #rightarrow# #pi fraction;p_{T} [GeV/c];", 1024, 780);
//
//// Electron2Pion->GetXaxis()->SetLimits(0.2,1.0);
//// Electron2Pion->GetXaxis()->SetRangeUser(0.2,1.0);
// // Debuggg 
// float pt;
//
// pt = 0.25; std::cerr << Form("pt: %.2f value: %.5f ", pt, Electron2Pion->GetBinContent( Electron2Pion->FindBin(pt) )) << std::endl;
// pt = 0.35; std::cerr << Form("pt: %.2f value: %.5f ", pt, Electron2Pion->GetBinContent( Electron2Pion->FindBin(pt) )) << std::endl;
// pt = 0.45; std::cerr << Form("pt: %.2f value: %.5f ", pt, Electron2Pion->GetBinContent( Electron2Pion->FindBin(pt) )) << std::endl;
// pt = 0.76; std::cerr << Form("pt: %.2f value: %.5f ", pt, Electron2Pion->GetBinContent( Electron2Pion->FindBin(pt) )) << std::endl;
// pt = 0.84; std::cerr << Form("pt: %.2f value: %.5f ", pt, Electron2Pion->GetBinContent( Electron2Pion->FindBin(pt) )) << std::endl;
//
// Electron2Pion->Scale(100);
// // Debuggg 
// std::cerr << "after scale " << std::endl;
// pt = 0.25; std::cerr << Form("pt: %.2f value: %.5f ", pt, Electron2Pion->GetBinContent( Electron2Pion->FindBin(pt) )) << std::endl;
// pt = 0.35; std::cerr << Form("pt: %.2f value: %.5f ", pt, Electron2Pion->GetBinContent( Electron2Pion->FindBin(pt) )) << std::endl;
// pt = 0.45; std::cerr << Form("pt: %.2f value: %.5f ", pt, Electron2Pion->GetBinContent( Electron2Pion->FindBin(pt) )) << std::endl;
// pt = 0.76; std::cerr << Form("pt: %.2f value: %.5f ", pt, Electron2Pion->GetBinContent( Electron2Pion->FindBin(pt) )) << std::endl;
// pt = 0.84; std::cerr << Form("pt: %.2f value: %.5f ", pt, Electron2Pion->GetBinContent( Electron2Pion->FindBin(pt) )) << std::endl;
// pt = 1.21; std::cerr << Form("pt: %.2f value: %.5f ", pt, Electron2Pion->GetBinContent( Electron2Pion->FindBin(pt) )) << std::endl;
// pt = 1.19; std::cerr << Form("pt: %.2f value: %.5f ", pt, Electron2Pion->GetBinContent( Electron2Pion->FindBin(pt) )) << std::endl;
//
// gStyle->SetOptStat(0);
// Electron2Pion->GetYaxis()->SetTitle("e contamination to #pi [%]");
// Electron2Pion->GetXaxis()->SetTitle("p_{T} [GeV/c]");
// Electron2Pion->GetYaxis()->SetRangeUser(0.0,2.0);
// Electron2Pion->Draw("");
//
// std::string figbasename = "electron2pion";
// std::string outPNG = Form("%s.png", figbasename.c_str());
// std::string outPDF = Form("%s.pdf", figbasename.c_str());
// 
// canvas.SaveAs(outPDF.c_str());
// canvas.SaveAs(outPNG.c_str());
// }

// for(int TypBin=0; TypBin<nTypBins; TypBin++)
// {
//
//	{
// 	 TCanvas canvas("canvas", "", 1024, 780);
// 	 purity[TypBin]->Scale(100);
// 	 purity[TypBin]->GetYaxis()->SetRangeUser(0.0,100.);
//	 purity[TypBin]->Draw("E1");
//
//	 std::string figbasename = Form("purity_%d", TypBin);
//	 std::string outPNG = Form("%s.png", figbasename.c_str());
//	 std::string outPDF = Form("%s.pdf", figbasename.c_str());
//	 
//	 canvas.SaveAs(outPDF.c_str());
//	 canvas.SaveAs(outPNG.c_str());
//	}
//
//	{
// 	 TCanvas canvas("canvas", "", 1024, 780);
// 	 contam[TypBin]->Scale(100);
// 	 contam[TypBin]->GetYaxis()->SetRangeUser(0.0,100.);
//	 contam[TypBin]->Draw("E1");
//
//	 std::string figbasename = Form("contam_%d", TypBin);
//	 std::string outPNG = Form("%s.png", figbasename.c_str());
//	 std::string outPDF = Form("%s.pdf", figbasename.c_str());
//	 
//	 canvas.SaveAs(outPDF.c_str());
//	 canvas.SaveAs(outPNG.c_str());
//	}
//
// }

 output->Close();

 
}
