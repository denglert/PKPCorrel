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
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TSpline.h"
#include "GraphStyles.h"

const int mult1 = 50;
const int mult2 = 80;

int main( int argc, const char *argv[] )
{ 

 int nFiles = 5;

 std::string inpFilenames[5];
 std::string       labels[5];

 inpFilenames[0] = "/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/PIDscan_MinBias_config_looser_2_trkCorr_no/dump.root";
 inpFilenames[1] = "/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/PIDscan_MinBias_config_looser_1_trkCorr_no/dump.root";
 inpFilenames[2] = "/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/PIDscan_MinBias_config_default_trkCorr_no/dump.root";
 inpFilenames[3] = "/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/PIDscan_MinBias_config_strict_2_trkCorr_no/dump.root";
 inpFilenames[4] = "/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/PIDscan_MinBias_config_strict_2_trkCorr_no/dump.root";

 labels[0] = "looser_2";
 labels[1] = "looser_1";
 labels[2] = "default";
 labels[3] = "strict_1";
 labels[4] = "strict_2";

 std::string CMSsystemlabel = Form("#splitline{CMS (work in progress)}{pPb MinBias}", mult1, mult2);
 std::string multlabel = Form("%3d #leq N_{trk}^{offline} #leq %3d", mult1, mult2);

 double fit_interval[4][2] = {
									  {0.2, 3.0},
									  {0.2, 0.9},
									  {0.2, 0.9},
									  {0.2, 1.4}
 									  };

 // Plot style
 int MarkerStyles[5] = {     20,    23,    21,       22,   34 };
 int   LineStyles[5] = {      9,     9,     9,        9,    9 };
 int       Colors[5] = { kGreen, kCyan, kBlue, kMagenta, kRed };

 // Binning
 int nCorrTyp			  = nCorrTyp_; 
 int *nPtBins = new int[nCorrTyp_];

 for(int TypBin = 0; TypBin < nCorrTyp; TypBin++)
 { nPtBins[TypBin] = nPtBins_[TypBin]; }

 int nMultiplicityBins_Ana = nMultiplicityBins_Ana_HDR;
 int nMultiplicityBins_EvM = nMultiplicityBins_EvM_HDR;
 int nZvtxBins 		      = nZvtxBins_; 


 ///////////////////////////////////////
 //                                   //
 // ****** Opening input files ****** //
 //                                   //
 ///////////////////////////////////////
 
 TFile *inpFiles[nFiles];

 for(int i = 0; i < nFiles; i++)
 { 
	inpFiles[i] = new TFile( inpFilenames[i].c_str(), "READ");
	if ( inpFiles[i]->IsZombie() ) {std::cerr << "Error opening file : " << inpFilenames[i] << std::endl; exit(-1); }
 }
 
 //////////////////////////////
 //                          //
 // ***** Initializing ***** //
 //                          //
 //////////////////////////////
 
 // Declare data points holders (TGraphErrors)
 TGraphErrors *data[nCorrTyp][nFiles];

 // Declare fit functions (TF1)
 TF1 *fit[nCorrTyp][nFiles];

 // Read in data points
 for(int i = 0; i < nCorrTyp; i++)
 for(int j = 0; j < nFiles; j++)
 {
   std::string dataname = Form("%s_Ntrk_%03d-%03d", particletypelabel(i).c_str(),  mult1, mult2 );
 	data[i][j] = (TGraphErrors*)inpFiles[j]->Get( dataname.c_str() );
 }


 //////////////////////
 //                  //
 // ***** Plot ***** //
 //                  //
 //////////////////////
 
 // Debuggg 
 std::cout << "Plotting section." << std::endl;

 for(int i = 0; i < nCorrTyp; i++)
 for(int j = 0; j < nFiles; j++)
 {

 	// Discard fit that is in the file
   // data[i][j] -> GetFunction(Form("%sv2_fit", particletypelabel(i).c_str() ))->SetBit(TF1::kNotDraw);

	std::cout << Form("%s_fit_%d", particletypelabel(i).c_str(), j) << std::endl;
	// Create new fit functions
	fit[i][j] = new TF1 (Form("%s_fit_%d", particletypelabel(i).c_str(), j), "[0]+[1]*x+[2]*x*x", fit_interval[i][0], fit_interval[i][1]);

 	// Cosmetics
	data[i][j]->SetMarkerStyle( MarkerStyles[j] );
	data[i][j]->SetMarkerColor( Colors[j] );
	data[i][j]->SetLineColor(   Colors[j] );

	fit[i][j]->SetLineColor( Colors[j] );
	fit[i][j]->SetLineStyle( LineStyles[j] );

	// Fit the data
   data[i][j]->Fit( Form("%s_fit_%d", particletypelabel(i).c_str(), j), "R");

 }


 // *** Plotting the graphs *** //
 gStyle->SetPadTickY(1);
 gStyle->SetPadTickX(1);
 
 for(int i = 0; i < nCorrTyp; i++)
 {

 	TCanvas canvas_v2_vs_pT ("v2 vs pT", "v_{2} values as a function of p_{T}; p_{T} [GeV/c];v_{2}", 1024, 768);
 	
 	canvas_v2_vs_pT.SetLeftMargin(0.10);
 	canvas_v2_vs_pT.SetBottomMargin(0.12);
 	canvas_v2_vs_pT.SetRightMargin(0.05);
 	canvas_v2_vs_pT.SetTopMargin(0.05);
 	
 	double v2vspt_ptmin = 0.0;
 	double v2vspt_ptmax = 2.5;
 	double v2vspt_v2min = 0.0;
 	double v2vspt_v2max = 0.16;
 	
 	data[i][0]->SetTitle("");
 	data[i][0]->GetXaxis()->SetLimits(v2vspt_ptmin,v2vspt_ptmax);
 	data[i][0]->GetXaxis()->SetTitle("p_{T} [GeV/c]");                              			  
 	data[i][0]->GetXaxis()->CenterTitle(1);
 	data[i][0]->GetXaxis()->SetTitleOffset(1.2);
 	data[i][0]->GetXaxis()->SetTitleSize(figuretextsize);
 	data[i][0]->GetYaxis()->SetRangeUser(v2vspt_v2min,v2vspt_v2max);
 	data[i][0]->GetYaxis()->SetTitle("v_{2}");
 	data[i][0]->GetYaxis()->CenterTitle(1);
 	data[i][0]->GetYaxis()->SetTitleOffset(1.2);
 	data[i][0]->GetYaxis()->SetTitleSize(figuretextsize);
 
 	////////////////////
 	// Making figures //
	
	data[i][0]->Draw("AP");
	for(int j = 1; j < nFiles; j++)
	{data[i][j]->Draw("P"); }

	double gr_legend_x1=0.6;
	double gr_legend_y1=0.4;
	double gr_legend_x2=gr_legend_x1+.20;
	double gr_legend_y2=gr_legend_y1+.20;

	double CMSsystemlabelposx = 0.14;
	double CMSsystemlabelposy = 0.84;
	double multlabelposx = 0.62;
	double multlabelposy = 0.24;

	TLegend gr_legend (gr_legend_x1, gr_legend_y1, gr_legend_x2, gr_legend_y2);
	gr_legend.SetFillStyle(0);
	gr_legend.SetBorderSize(0);
	for(int j = 0; j < nFiles; j++)
	{ gr_legend.AddEntry(data[i][j], labels[j].c_str(), "P");}
	gr_legend.SetTextSize(figuretextsize);
	gr_legend.Draw("SAME");



	TLatex tCMSsystemlabel( CMSsystemlabelposx,CMSsystemlabelposy, CMSsystemlabel.c_str()); 
	tCMSsystemlabel.SetTextSize(figuretextsize);
	tCMSsystemlabel.SetNDC(kTRUE);
	tCMSsystemlabel.Draw();

	TLatex tmultlabel( multlabelposx,multlabelposy, multlabel.c_str()); 
	tmultlabel.SetTextSize(figuretextsize);
	tmultlabel.SetNDC(kTRUE);
	tmultlabel.Draw();

	
 	std::string label = Form("v2vspt_%s_nTrk_%03d-%03d", particletypelabel(i).c_str(), mult1, mult2); 
	std::string	pngfigure = label+".png";
	std::string	pdffigure = label+".pdf";
	canvas_v2_vs_pT.SaveAs( pngfigure.c_str() );
	canvas_v2_vs_pT.SaveAs( pdffigure.c_str() );

	}

}
