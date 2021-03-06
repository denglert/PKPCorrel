#include <TLatex.h>
#include <TF1.h>
#include <TStyle.h>
#include <TMath.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include "GraphStyles.h"
#include "GraphTools.h"
#include "CorrelationUtils.h"
#include "AnalysisBinning.h"
#include "CMSres.h"
#include "ALICERes.h"
#include "HIN14002res.h"

/////////////////
// StoreInTGraph
//void CorrelationFramework::StoreInTGraph()
//{
//
//	TGraphErrors_v2vspt_StatError = new TGraphErrors**[nMultiplicityBins_Ana];
//	TGraphErrors_v2vspt_SystError = new TGraphErrors**[nMultiplicityBins_Ana];
//
//	double ptw = 0.02;
//
// 	for(int multBin = 0; multBin < nMultiplicityBins_Ana; multBin++)
//	{
//
//		TGraphErrors_v2vspt_StatError[multBin] = new TGraphErrors*[nCorrTyp];
//		TGraphErrors_v2vspt_SystError[multBin] = new TGraphErrors*[nCorrTyp];
//
// 		for(int TypBin  = 0; TypBin < nCorrTyp; TypBin++)
//		{
//
//			int nPoints          = nPtBins[TypBin];
//			double *pt  			= new double[nPoints];
//			double *pt_StatError = new double[nPoints];
//			double *dpt 			= new double[nPoints];
//			double *v2  			= new double[nPoints];
//			double *v2_StatError = new double[nPoints];
//			double *v2_SystError = new double[nPoints];
//			
//		   std::vector< double > ptvec = CorrelationFramework::Getptvec(TypBin, 0.);
//		   std::vector< double > v2vec = CorrelationFramework::Getv2vec(TypBin, multBin);
//		   std::vector< double > v2_StatErrorvec = CorrelationFramework::Getv2_StatErrorvec(TypBin, multBin);
//		   std::vector< double > v2_SystErrorvec = CorrelationFramework::Getv2_SystErrorvec(TypBin, multBin);
//		
//			for(int ptBin = 0; ptBin < nPtBins[TypBin]; ptBin++)
//			{
//				pt 			[ptBin] = ptvec[ptBin];
//				pt_StatError[ptBin] = 0;
//				dpt 			[ptBin] = ptw;
//				v2 			[ptBin] = v2vec[ptBin];
//				v2_StatError[ptBin] = v2_StatErrorvec[ptBin];
//				v2_SystError[ptBin] = v2_SystErrorvec[ptBin];
//			};
//		
//			TGraphErrors_v2vspt_StatError[multBin][TypBin] = new TGraphErrors(nPoints, pt, v2, pt_StatError, v2_StatError);
//			TGraphErrors_v2vspt_SystError[multBin][TypBin] = new TGraphErrors(nPoints, pt, v2, pt_StatError, v2_SystError);
//
//			delete pt;
//			delete dpt;
//			delete v2;
//			delete v2_StatError;
//			delete v2_SystError;
//			
//		}
//	}
//}

////////////////////////////////////////
// - makeFigv2vspT_allparticles
void CorrelationFramework::makeFigv2vspT_allparticles(int multBin, std::string tag)
{

	gStyle->SetOptStat(0);

	double ptw = 0.02;

	double **pt;
	double **dpt;
	double **v2;
	double **v2_StatError;
	double **v2_SystError;

	pt       	 = new double*[nCorrTyp];
	dpt       	 = new double*[nCorrTyp];
	v2       	 = new double*[nCorrTyp];
	v2_StatError = new double*[nCorrTyp];
	v2_SystError = new double*[nCorrTyp];

 	for(int TypBin=0; TypBin < nCorrTyp; TypBin++)
	{
		pt      [TypBin] = new double[nPtBins[TypBin]];
		dpt     [TypBin] = new double[nPtBins[TypBin]];
		v2      [TypBin] = new double[nPtBins[TypBin]];
		v2_StatError[TypBin] = new double[nPtBins[TypBin]];
		v2_SystError[TypBin] = new double[nPtBins[TypBin]];

   	std::vector< double > ptvec = CorrelationFramework::Getptvec(TypBin, 0.);
   	std::vector< double > v2vec = CorrelationFramework::Getv2vec(TypBin, multBin);
   	std::vector< double > v2_StatErrorvec = CorrelationFramework::Getv2_StatErrorvec(TypBin, multBin);
   	std::vector< double > v2_SystErrorvec = CorrelationFramework::Getv2_SystErrorvec(TypBin, multBin);

		for(int ptBin = 0; ptBin < nPtBins[TypBin]; ptBin++)
		{
			pt[TypBin][ptBin]        = ptvec[ptBin];
			dpt[TypBin][ptBin]       = ptw;
			v2[TypBin][ptBin]        = v2vec[ptBin];
			v2_StatError[TypBin][ptBin]  = v2_StatErrorvec[ptBin];
			v2_SystError[TypBin][ptBin]  = v2_SystErrorvec[ptBin];
		};

	}

	// *** Plotting the graphs *** //
	//
	gStyle->SetPadTickY(1);
	gStyle->SetPadTickX(1);
	TCanvas canvas_v2_vs_pT ("v2 vs pT", "v_{2} values as a function of p_{T}; p_{T} [GeV/c];v_{2}", 1024, 768);

	canvas_v2_vs_pT.SetLeftMargin(0.10);
   canvas_v2_vs_pT.SetBottomMargin(0.12);
   canvas_v2_vs_pT.SetRightMargin(0.05);
   canvas_v2_vs_pT.SetTopMargin(0.05);
	
	TGraphErrors cparv2 = cpar_v2(nPtBins[0], pt[0], v2[0], 0, v2_StatError[0] );
	TGraphErrors pionv2 = pion_v2(nPtBins[1], pt[1], v2[1], 0, v2_StatError[1] );
	TGraphErrors kaonv2 = kaon_v2(nPtBins[2], pt[2], v2[2], 0, v2_StatError[2] );
	TGraphErrors protv2 = prot_v2(nPtBins[3], pt[3], v2[3], 0, v2_StatError[3] );

	TGraphErrors cparv2_syst = cpar_v2_syst(nPtBins[0], pt[0], v2[0], dpt[0], v2_SystError[0] );
	TGraphErrors pionv2_syst = pion_v2_syst(nPtBins[1], pt[1], v2[1], dpt[1], v2_SystError[1] );
	TGraphErrors kaonv2_syst = kaon_v2_syst(nPtBins[2], pt[2], v2[2], dpt[2], v2_SystError[2] );
	TGraphErrors protv2_syst = prot_v2_syst(nPtBins[3], pt[3], v2[3], dpt[3], v2_SystError[3] );

	double v2vspt_ptmin = 0.0;
	double v2vspt_ptmax = 2.5;
	double v2vspt_v2min = 0.0;
	double v2vspt_v2max = 0.16;
	//double v2vspt_v2max = 0.6;
	
	// Remove 1st point
	cparv2.SetPoint(0, -50, -5);
	pionv2.SetPoint(0, -50, -5);
	kaonv2.SetPoint(0, -50, -5);
	protv2.SetPoint(0, -50, -5);

	cparv2_syst.SetPoint(0, -50, -5);
	pionv2_syst.SetPoint(0, -50, -5);
	kaonv2_syst.SetPoint(0, -50, -5);
	protv2_syst.SetPoint(0, -50, -5);

	cparv2.SetTitle("");
   cparv2.GetXaxis()->SetLimits(v2vspt_ptmin,v2vspt_ptmax);
	cparv2.GetXaxis()->SetTitle("p_{T} [GeV/c]");                              			  
	cparv2.GetXaxis()->CenterTitle(1);
	cparv2.GetXaxis()->SetTitleOffset(1.2);
	cparv2.GetXaxis()->SetTitleSize(v2vspt_xlabelsize);
	cparv2.GetYaxis()->SetRangeUser(v2vspt_v2min,v2vspt_v2max);
	cparv2.GetYaxis()->SetTitle("v_{2}");
	cparv2.GetYaxis()->CenterTitle(1);
	cparv2.GetYaxis()->SetTitleOffset(1.2);
	cparv2.GetYaxis()->SetTitleSize(v2vspt_ylabelsize);

// No fit.

//	TF1 *cparv2_fit = new TF1 ("cparv2_fit", "[1]*x+[2]*x*x",0,3);
//	TF1 *pionv2_fit = new TF1 ("pionv2_fit", "[1]*x+[2]*x*x",0,0.9);
//	TF1 *kaonv2_fit = new TF1 ("kaonv2_fit", "[1]*x+[2]*x*x",0,0.9);
//	TF1 *protv2_fit = new TF1 ("protv2_fit", "[1]*x+[2]*x*x",0,1.5);
//
//	cparv2_fit->SetLineColor(kBlack);
//	pionv2_fit->SetLineColor(kRed);
//	kaonv2_fit->SetLineColor(kGreen);
//	protv2_fit->SetLineColor(kBlue);
//
//	cparv2_fit->SetLineStyle(9);
//	pionv2_fit->SetLineStyle(9);
//	kaonv2_fit->SetLineStyle(9);
//	protv2_fit->SetLineStyle(9);
//
//	cparv2.Fit("cparv2_fit", "R");
//	pionv2.Fit("pionv2_fit", "R");
//	kaonv2.Fit("kaonv2_fit", "R");
//	protv2.Fit("protv2_fit", "R");
//

	cparv2.Draw("AP");
	pionv2.Draw("P");
	kaonv2.Draw("P");
	protv2.Draw("P");

	cparv2_syst.Draw("2 SAME");
	pionv2_syst.Draw("2 SAME");
	kaonv2_syst.Draw("2 SAME");
	protv2_syst.Draw("2 SAME");

//	TGraphErrors cms = CMSres_v2_chadron_120_150();
//	g3->SetMarkerStyle(8);
//	cms.SetMarkerColor(5);
//	cms.SetLineColor(6);
//	cms.Draw("LP");

//	TGraphAsymmErrors alice_0_20_cpar = ALICE_pPB_0_20_cpar();
//	TGraphAsymmErrors alice_0_20_pion = ALICE_pPB_0_20_pion();
//	TGraphAsymmErrors alice_0_20_kaon = ALICE_pPB_0_20_kaon();
//	TGraphAsymmErrors alice_0_20_prot = ALICE_pPB_0_20_prot();
//
//
//	alice_0_20_cpar.Draw("P");
//	alice_0_20_pion.Draw("P");
//	alice_0_20_kaon.Draw("P");
//	alice_0_20_prot.Draw("P");

	double legend_x1=.14;
	double legend_y1=0.56;
	double legend_x2=legend_x1+.20;
	double legend_y2=legend_y1+.20;
	double CMSsystemlabelposx = 0.14;
	double CMSsystemlabelposy = 0.84;
	double multlabelposx = 0.62;
	double multlabelposy = 0.24;

	TLegend v2vsptlegend (legend_x1, legend_y1, legend_x2, legend_y2);
	v2vsptlegend.SetFillStyle(0);
	v2vsptlegend.SetBorderSize(0);
	v2vsptlegend.SetTextSize(v2vspt_legendtextsize);
	v2vsptlegend.AddEntry(&cparv2,"charged", "P");
	v2vsptlegend.AddEntry(&pionv2,"#pi", "P");
	v2vsptlegend.AddEntry(&kaonv2,"K", "P");
	v2vsptlegend.AddEntry(&protv2,"p", "P");

//	v2vsptlegend.AddEntry(&cms,"# CMS HIN 13-002 c.p - c.p nTrk [120-150]", "L");
//	v2vsptlegend.AddEntry(&alice_0_20_cpar,"# ALICE [0-20] c.p - c.p", "P");
//	v2vsptlegend.AddEntry(&alice_0_20_pion,"# ALICE [0-20] #pi - c.p", "P");
//	v2vsptlegend.AddEntry(&alice_0_20_kaon,"# ALICE [0-20] K - c.p", "P");
//	v2vsptlegend.AddEntry(&alice_0_20_prot,"# ALICE [0-20] p - c.p", "P");

	v2vsptlegend.Draw("SAME");

   int mult1 = multiplicity_Ana(multBin, 0, nMultiplicityBins_Ana);
	int mult2 = multiplicity_Ana(multBin, 1, nMultiplicityBins_Ana);

	std::string CMSsystemlabel = Form("#splitline{CMS Preliminary pPb}{#sqrt{s_{NN}} = 5.02 TeV L_{int} = 35 nb^{-1}}", mult1, mult2);
	std::string multlabel = Form("%3d #leq N_{trk}^{offline} < %3d", mult1, mult2);

	TLatex tCMSsystemlabel( CMSsystemlabelposx,CMSsystemlabelposy, CMSsystemlabel.c_str()); 
	tCMSsystemlabel.SetTextSize(v2vspt_figuretextsize);
	tCMSsystemlabel.SetNDC(kTRUE);
	tCMSsystemlabel.Draw();

	TLatex tmultlabel( multlabelposx,multlabelposy, multlabel.c_str()); 
	tmultlabel.SetTextSize(v2vspt_figuretextsize);
	tmultlabel.SetNDC(kTRUE);
	tmultlabel.Draw();
	
	std::string dir  = Form("./results/%s/v2/", tag.c_str());
	std::string label = Form("v2vspt_all_nTrk_%03d-%03d", mult1, mult2); 
	std::string	pngfigure = dir+label+".png";
	std::string	pdffigure = dir+label+".pdf";
	canvas_v2_vs_pT.SaveAs( pngfigure.c_str() );
	canvas_v2_vs_pT.SaveAs( pdffigure.c_str() );

	// Save TGraphErrors to dump.root file
	cparv2.SetName( Form("cpar_Ntrk_%03d-%03d", mult1, mult2) );
	pionv2.SetName( Form("pion_Ntrk_%03d-%03d", mult1, mult2) );
	kaonv2.SetName( Form("kaon_Ntrk_%03d-%03d", mult1, mult2) );
	protv2.SetName( Form("prot_Ntrk_%03d-%03d", mult1, mult2) );

	cparv2_syst.SetName( Form("cpar_syst_Ntrk_%03d-%03d", mult1, mult2) );
	pionv2_syst.SetName( Form("pion_syst_Ntrk_%03d-%03d", mult1, mult2) );
	kaonv2_syst.SetName( Form("kaon_syst_Ntrk_%03d-%03d", mult1, mult2) );
	protv2_syst.SetName( Form("prot_syst_Ntrk_%03d-%03d", mult1, mult2) );

	cparv2.Write(); 
	pionv2.Write();
	kaonv2.Write();
	protv2.Write();

	cparv2_syst.Write();
	pionv2_syst.Write();
	kaonv2_syst.Write();
	protv2_syst.Write();

}


/////////////////////////////////////////////////////
// - makeFigv2vspT_allparticles_ALICE_comparison()
void CorrelationFramework::makeFigv2vspT_allparticles_ALICE_comparison(int multBin, std::string tag)
{

	gStyle->SetOptStat(0);

	double ptw = 0.02;

	double **pt;
	double **dpt;
	double **v2;
	double **v2_StatError;
	double **v2_SystError;

	pt       	 = new double*[nCorrTyp];
	dpt       	 = new double*[nCorrTyp];
	v2       	 = new double*[nCorrTyp];
	v2_StatError = new double*[nCorrTyp];
	v2_SystError = new double*[nCorrTyp];

 	for(int TypBin=0; TypBin < nCorrTyp; TypBin++)
	{
		pt      [TypBin] = new double[nPtBins[TypBin]];
		dpt     [TypBin] = new double[nPtBins[TypBin]];
		v2      [TypBin] = new double[nPtBins[TypBin]];
		v2_StatError[TypBin] = new double[nPtBins[TypBin]];
		v2_SystError[TypBin] = new double[nPtBins[TypBin]];

   	std::vector< double > ptvec = CorrelationFramework::Getptvec(TypBin, 0.);
   	std::vector< double > v2vec = CorrelationFramework::Getv2vec(TypBin, multBin);
   	std::vector< double > v2_StatErrorvec = CorrelationFramework::Getv2_StatErrorvec(TypBin, multBin);
   	std::vector< double > v2_SystErrorvec = CorrelationFramework::Getv2_SystErrorvec(TypBin, multBin);

		for(int ptBin = 0; ptBin < nPtBins[TypBin]; ptBin++)
		{
			pt[TypBin][ptBin]        = ptvec[ptBin];
			dpt[TypBin][ptBin]       = ptw;
			v2[TypBin][ptBin]        = v2vec[ptBin];
			v2_StatError[TypBin][ptBin]  = v2_StatErrorvec[ptBin];
			v2_SystError[TypBin][ptBin]  = v2_SystErrorvec[ptBin];
		};


	}

	// *** Plotting the graphs *** //
	//
	gStyle->SetPadTickY(1);
	gStyle->SetPadTickX(1);
	TCanvas canvas_v2_vs_pT ("v2 vs pT", "v_{2} values as a function of p_{T}; p_{T} [GeV/c];v_{2}", 1024, 768);

	canvas_v2_vs_pT.SetLeftMargin(0.10);
   canvas_v2_vs_pT.SetBottomMargin(0.12);
   canvas_v2_vs_pT.SetRightMargin(0.05);
   canvas_v2_vs_pT.SetTopMargin(0.05);
	
	TGraphErrors cparv2 = cpar_v2(nPtBins[0], pt[0], v2[0], 0, v2_StatError[0] );
	TGraphErrors pionv2 = pion_v2(nPtBins[1], pt[1], v2[1], 0, v2_StatError[1] );
	TGraphErrors kaonv2 = kaon_v2(nPtBins[2], pt[2], v2[2], 0, v2_StatError[2] );
	TGraphErrors protv2 = prot_v2(nPtBins[3], pt[3], v2[3], 0, v2_StatError[3] );

	TGraphErrors cparv2_syst = cpar_v2_syst(nPtBins[0], pt[0], v2[0], dpt[0], v2_SystError[0] );
	TGraphErrors pionv2_syst = pion_v2_syst(nPtBins[1], pt[1], v2[1], dpt[1], v2_SystError[1] );
	TGraphErrors kaonv2_syst = kaon_v2_syst(nPtBins[2], pt[2], v2[2], dpt[2], v2_SystError[2] );
	TGraphErrors protv2_syst = prot_v2_syst(nPtBins[3], pt[3], v2[3], dpt[3], v2_SystError[3] );

	double v2vspt_ptmin = 0.0;
	double v2vspt_ptmax = 2.5;
	double v2vspt_v2min = 0.0;
	double v2vspt_v2max = 0.16;

//	cparv2.SetPoint(0, -50, -5);
//	pionv2.SetPoint(0, -50, -5);
//	kaonv2.SetPoint(0, -50, -5);
//	protv2.SetPoint(0, -50, -5);
//
//	cparv2_syst.SetPoint(0, -50, -5);
//	pionv2_syst.SetPoint(0, -50, -5);
//	kaonv2_syst.SetPoint(0, -50, -5);
//	protv2_syst.SetPoint(0, -50, -5);

	cparv2.SetTitle("");
   cparv2.GetXaxis()->SetLimits(v2vspt_ptmin,v2vspt_ptmax);
	cparv2.GetXaxis()->SetTitle("p_{T} [GeV/c]");                              			  
	cparv2.GetXaxis()->CenterTitle(1);
	cparv2.GetXaxis()->SetTitleOffset(1.2);
	cparv2.GetXaxis()->SetTitleSize(figuretextsize);
	cparv2.GetYaxis()->SetRangeUser(v2vspt_v2min,v2vspt_v2max);
	cparv2.GetYaxis()->SetTitle("v_{2}");
	cparv2.GetYaxis()->CenterTitle(1);
	cparv2.GetYaxis()->SetTitleOffset(1.2);
	cparv2.GetYaxis()->SetTitleSize(figuretextsize);

	pionv2.SetTitle("");
   pionv2.GetXaxis()->SetLimits(v2vspt_ptmin,v2vspt_ptmax);
	pionv2.GetXaxis()->SetTitle("p_{T} [GeV/c]");                              			  
	pionv2.GetXaxis()->CenterTitle(1);
	pionv2.GetXaxis()->SetTitleOffset(1.2);
	pionv2.GetXaxis()->SetTitleSize(figuretextsize);
	pionv2.GetYaxis()->SetRangeUser(v2vspt_v2min,v2vspt_v2max);
	pionv2.GetYaxis()->SetTitle("v_{2}");
	pionv2.GetYaxis()->CenterTitle(1);
	pionv2.GetYaxis()->SetTitleOffset(1.2);
	pionv2.GetYaxis()->SetTitleSize(figuretextsize);

	kaonv2.SetTitle("");
   kaonv2.GetXaxis()->SetLimits(v2vspt_ptmin,v2vspt_ptmax);
	kaonv2.GetXaxis()->SetTitle("p_{T} [GeV/c]");                              			  
	kaonv2.GetXaxis()->CenterTitle(1);
	kaonv2.GetXaxis()->SetTitleOffset(1.2);
	kaonv2.GetXaxis()->SetTitleSize(figuretextsize);
	kaonv2.GetYaxis()->SetRangeUser(v2vspt_v2min,v2vspt_v2max);
	kaonv2.GetYaxis()->SetTitle("v_{2}");
	kaonv2.GetYaxis()->CenterTitle(1);
	kaonv2.GetYaxis()->SetTitleOffset(1.2);
	kaonv2.GetYaxis()->SetTitleSize(figuretextsize);

	protv2.SetTitle("");
   protv2.GetXaxis()->SetLimits(v2vspt_ptmin,v2vspt_ptmax);
	protv2.GetXaxis()->SetTitle("p_{T} [GeV/c]");                              			  
	protv2.GetXaxis()->CenterTitle(1);
	protv2.GetXaxis()->SetTitleOffset(1.2);
	protv2.GetXaxis()->SetTitleSize(figuretextsize);
	protv2.GetYaxis()->SetRangeUser(v2vspt_v2min,v2vspt_v2max);
	protv2.GetYaxis()->SetTitle("v_{2}");
	protv2.GetYaxis()->CenterTitle(1);
	protv2.GetYaxis()->SetTitleOffset(1.2);
	protv2.GetYaxis()->SetTitleSize(figuretextsize);

//	cparv2.Draw("AP");
//	pionv2.Draw("AP");
//	kaonv2.Draw("AP");
	protv2.Draw("AP");

//	cparv2_syst.Draw("2 SAME");
//	pionv2_syst.Draw("2 SAME");
//	kaonv2_syst.Draw("2 SAME");
	protv2_syst.Draw("2 SAME");

	// TGraphErrors cms = CMSres_v2_chadron_120_150();
	// g3->SetMarkerStyle(8);
	// cms.SetMarkerColor(5);
	// cms.SetLineColor(6);
	// cms.Draw("LP");

	TGraphAsymmErrors alice_0_20_cpar = ALICE_pPB_0_20_cpar();
	TGraphAsymmErrors alice_0_20_pion = ALICE_pPB_0_20_pion();
	TGraphAsymmErrors alice_0_20_kaon = ALICE_pPB_0_20_kaon();
	TGraphAsymmErrors alice_0_20_prot = ALICE_pPB_0_20_prot();

//	alice_0_20_cpar.Draw("P");
//	alice_0_20_pion.Draw("P");
//	alice_0_20_kaon.Draw("P");
	alice_0_20_prot.Draw("P");

	TF1 *cparv2_fit = new TF1 ("cparv2_fit", "[1]*x+[2]*x*x",0,3);
	TF1 *pionv2_fit = new TF1 ("pionv2_fit", "[1]*x+[2]*x*x",0,0.9);
	TF1 *kaonv2_fit = new TF1 ("kaonv2_fit", "[1]*x+[2]*x*x",0,0.9);
	TF1 *protv2_fit = new TF1 ("protv2_fit", "[1]*x+[2]*x*x",0,1.5);

	cparv2_fit->SetLineColor(kBlack);
	pionv2_fit->SetLineColor(kRed);
	kaonv2_fit->SetLineColor(kGreen);
	protv2_fit->SetLineColor(kBlue);

	cparv2_fit->SetLineStyle(9);
	pionv2_fit->SetLineStyle(9);
	kaonv2_fit->SetLineStyle(9);
	protv2_fit->SetLineStyle(9);

//	cparv2.Fit("cparv2_fit", "R");
//	pionv2.Fit("pionv2_fit", "R");
//	kaonv2.Fit("kaonv2_fit", "R");
//	protv2.Fit("protv2_fit", "R");

	double legend_x1=.55;
	double legend_y1=0.14;
	double legend_x2=legend_x1+.20;
	double legend_y2=legend_y1+.32;
	double CMSsystemlabelposx = 0.14;
	double CMSsystemlabelposy = 0.86;
	double multlabelposx = 0.15;
	double multlabelposy = 0.70;

   int mult1 = multiplicity_Ana(multBin, 0, nMultiplicityBins_Ana);
	int mult2 = multiplicity_Ana(multBin, 1, nMultiplicityBins_Ana);

	TLegend v2vsptlegend (legend_x1, legend_y1, legend_x2, legend_y2);
	v2vsptlegend.SetFillStyle(0);
	v2vsptlegend.SetBorderSize(0);
	v2vsptlegend.AddEntry(&cparv2,Form("CMS charged"), "P");
	v2vsptlegend.AddEntry(&pionv2,Form("CMS #pi"), "P");
	v2vsptlegend.AddEntry(&kaonv2,Form("CMS K" ), "P");
	v2vsptlegend.AddEntry(&protv2,Form("CMS p" ), "P");
//	v2vsptlegend.AddEntry(&cms,"# CMS HIN 13-002 c.p - c.p nTrk [120-150]", "L");
	v2vsptlegend.AddEntry(&alice_0_20_cpar,"ALICE (0-20\%) charged ", "P");
	v2vsptlegend.AddEntry(&alice_0_20_pion,"ALICE (0-20\%) #pi ", "P");
	v2vsptlegend.AddEntry(&alice_0_20_kaon,"ALICE (0-20\%) K ", "P");
	v2vsptlegend.AddEntry(&alice_0_20_prot,"ALICE (0-20\%) p ", "P");
	v2vsptlegend.SetTextSize(figuretextsize);
	v2vsptlegend.Draw("SAME");



	std::string CMSsystemlabel = Form("#splitline{CMS Preliminary pPb}{#sqrt{s_{NN}} = 5.02 TeV L_{int} = 35 nb^{-1}}", mult1, mult2);
	std::string multlabel = Form("%3d #leq N_{trk}^{offline} < %3d", mult1, mult2);

	TLatex tCMSsystemlabel( CMSsystemlabelposx,CMSsystemlabelposy, CMSsystemlabel.c_str()); 
	tCMSsystemlabel.SetTextSize(figuretextsize);
	tCMSsystemlabel.SetNDC(kTRUE);
	tCMSsystemlabel.Draw();

	TLatex tmultlabel( multlabelposx,multlabelposy, multlabel.c_str()); 
	tmultlabel.SetTextSize(figuretextsize);
	tmultlabel.SetNDC(kTRUE);
	tmultlabel.Draw();
	
	std::string dir  = Form("./results/%s/v2/", tag.c_str());
	std::string label = Form("v2vspt_all_nTrk_%03d-%03d_ALICE_comparison", mult1, mult2); 
	std::string	pngfigure = dir+label+".png";
	std::string	pdffigure = dir+label+".pdf";
	canvas_v2_vs_pT.SaveAs( pngfigure.c_str() );
	canvas_v2_vs_pT.SaveAs( pdffigure.c_str() );

}

////////////////////////////////////////
// - makeFigv2vspT_HIN14002_comparison()
void CorrelationFramework::makeFigv2vspT_HIN14002_comparison( )
{

	const int multBins = 2;

	TGraphAsymmErrors *HIN14002_k0s = new TGraphAsymmErrors[multBins];
	TGraphAsymmErrors *HIN14002_lam = new TGraphAsymmErrors[multBins];

	//HIN14002_k0s[0] = HIN14002_pPb_000_035_k0s();
	//HIN14002_lam[0] = HIN14002_pPb_000_035_lam();
	//HIN14002_lam[1] = HIN14002_pPb_060_120_lam();
	//HIN14002_k0s[1] = HIN14002_pPb_060_120_k0s();
	
	//HIN14002_k0s[0] = HIN14002_pPb_000_035_k0s();
	//HIN14002_lam[0] = HIN14002_pPb_000_035_lam();
	//HIN14002_lam[1] = HIN14002_pPb_060_120_lam();
	//HIN14002_k0s[1] = HIN14002_pPb_060_120_k0s();


	int multMap[multBins] = {0,1};


	// HighMult
	HIN14002_k0s[0] = HIN14002_pPb_120_150_k0s();
	HIN14002_k0s[1] = HIN14002_pPb_150_185_k0s();
	HIN14002_lam[0] = HIN14002_pPb_120_150_lam();
	HIN14002_lam[1] = HIN14002_pPb_150_185_lam();

	for (int multBin = 0; multBin < multBins; multBin++)
	{
		gStyle->SetOptStat(0);


		double ptw = 0.02;

		double **pt;
		double **dpt;
		double **v2;
		double **v2_StatError;
		double **v2_SystError;

		pt       	 = new double*[nCorrTyp];
		dpt       	 = new double*[nCorrTyp];
		v2       	 = new double*[nCorrTyp];
		v2_StatError = new double*[nCorrTyp];
		v2_SystError = new double*[nCorrTyp];

 		for(int TypBin=0; TypBin < nCorrTyp; TypBin++)
		{
			pt      [TypBin] = new double[nPtBins[TypBin]];
			dpt     [TypBin] = new double[nPtBins[TypBin]];
			v2      [TypBin] = new double[nPtBins[TypBin]];
			v2_StatError[TypBin] = new double[nPtBins[TypBin]];
			v2_SystError[TypBin] = new double[nPtBins[TypBin]];

   		std::vector< double > ptvec = CorrelationFramework::Getptvec(TypBin, 0.);
   		std::vector< double > v2vec = CorrelationFramework::Getv2vec(TypBin, multMap[multBin]);
   		std::vector< double > v2_StatErrorvec = CorrelationFramework::Getv2_StatErrorvec(TypBin, multMap[multBin]);
   		std::vector< double > v2_SystErrorvec = CorrelationFramework::Getv2_SystErrorvec(TypBin, multMap[multBin]);

			for(int ptBin = 0; ptBin < nPtBins[TypBin]; ptBin++)
			{
				pt[TypBin][ptBin]        = ptvec[ptBin];
				dpt[TypBin][ptBin]       = ptw;
				v2[TypBin][ptBin]        = v2vec[ptBin];
				v2_StatError[TypBin][ptBin]  = v2_StatErrorvec[ptBin];
				v2_SystError[TypBin][ptBin]  = v2_SystErrorvec[ptBin];
			};


	}

	// *** Plotting the graphs *** //
	gStyle->SetPadTickY(1);
	gStyle->SetPadTickX(1);

	TCanvas canvas_v2_vs_pT ("v2vspT", "; p_{T} [GeV/c];v_{2}", 1024, 768);
	TPad *pad = new TPad("pad", "this is a pad", 0.05, 0.05, 0.95, 0.95);

	canvas_v2_vs_pT.SetLeftMargin(0.10);
   canvas_v2_vs_pT.SetBottomMargin(0.12);
   canvas_v2_vs_pT.SetRightMargin(0.05);
   canvas_v2_vs_pT.SetTopMargin(0.05);
	
	TGraphErrors cparv2 = cpar_v2(nPtBins[0], pt[0], v2[0], 0, v2_StatError[0] );
	TGraphErrors pionv2 = pion_v2(nPtBins[1], pt[1], v2[1], 0, v2_StatError[1] );
	TGraphErrors kaonv2 = kaon_v2(nPtBins[2], pt[2], v2[2], 0, v2_StatError[2] );
	TGraphErrors protv2 = prot_v2(nPtBins[3], pt[3], v2[3], 0, v2_StatError[3] );

	TGraphErrors cparv2_syst = cpar_v2_syst(nPtBins[0], pt[0], v2[0], dpt[0], v2_SystError[0] );
	TGraphErrors pionv2_syst = pion_v2_syst(nPtBins[1], pt[1], v2[1], dpt[1], v2_SystError[1] );
	TGraphErrors kaonv2_syst = kaon_v2_syst(nPtBins[2], pt[2], v2[2], dpt[2], v2_SystError[2] );
	TGraphErrors protv2_syst = prot_v2_syst(nPtBins[3], pt[3], v2[3], dpt[3], v2_SystError[3] );

	cparv2.SetPoint(0, -50, -5);
	pionv2.SetPoint(0, -50, -5);
	kaonv2.SetPoint(0, -50, -5);
	protv2.SetPoint(0, -50, -5);

	cparv2_syst.SetPoint(0, -50, -5);
	pionv2_syst.SetPoint(0, -50, -5);
	kaonv2_syst.SetPoint(0, -50, -5);
	protv2_syst.SetPoint(0, -50, -5);

	double v2vspt_ptmin = 0.0;
	double v2vspt_ptmax = 2.5;
	double v2vspt_v2min = 0.0;
	double v2vspt_v2max = 0.16;

	kaonv2.SetTitle("");
   kaonv2.GetXaxis()->SetLimits(v2vspt_ptmin,v2vspt_ptmax);
	kaonv2.GetXaxis()->SetTitle("p_{T} [GeV/c]");                              			  
	kaonv2.GetXaxis()->CenterTitle(1);
	kaonv2.GetXaxis()->SetTitleOffset(1.2);
	kaonv2.GetXaxis()->SetTitleSize(figuretextsize);
	kaonv2.GetYaxis()->SetRangeUser(v2vspt_v2min,v2vspt_v2max);
	kaonv2.GetYaxis()->SetTitle("v_{2}");
	kaonv2.GetYaxis()->CenterTitle(1);
	kaonv2.GetYaxis()->SetTitleOffset(1.2);
	kaonv2.GetYaxis()->SetTitleSize(figuretextsize);

	protv2.SetTitle("");
   protv2.GetXaxis()->SetLimits(v2vspt_ptmin,v2vspt_ptmax);
	protv2.GetXaxis()->SetTitle("p_{T} [GeV/c]");                              			  
	protv2.GetXaxis()->CenterTitle(1);
	protv2.GetXaxis()->SetTitleOffset(1.2);
	protv2.GetXaxis()->SetTitleSize(figuretextsize);
	protv2.GetYaxis()->SetRangeUser(v2vspt_v2min,v2vspt_v2max);
	protv2.GetYaxis()->SetTitle("v_{2}");
	protv2.GetYaxis()->CenterTitle(1);
	protv2.GetYaxis()->SetTitleOffset(1.2);
	protv2.GetYaxis()->SetTitleSize(figuretextsize);

   int mult1 = multiplicity_Ana(multMap[multBin], 0, nMultiplicityBins_Ana);
	int mult2 = multiplicity_Ana(multMap[multBin], 1, nMultiplicityBins_Ana);


	double legend_x1=.65;
	double legend_y1=0.14;
	double legend_x2=legend_x1+.20;
	double legend_y2=legend_y1+.32;
	double CMSsystemlabelposx = 0.14;
	double CMSsystemlabelposy = 0.86;
	double multlabelposx = 0.15;
	double multlabelposy = 0.70;

	TLegend v2vsptlegend (legend_x1, legend_y1, legend_x2, legend_y2);
	v2vsptlegend.SetFillStyle(0);
	v2vsptlegend.SetBorderSize(0);
	v2vsptlegend.SetTextSize(figuretextsize);

	std::string CMSsystemlabel = Form("#splitline{CMS Preliminary pPb}{#sqrt{s_{NN}} = 5.02 TeV L_{int} = 35 nb^{-1}}", mult1, mult2);
	std::string multlabel = Form("%3d #leq N_{trk}^{offline} < %3d", mult1, mult2);

	TLatex tCMSsystemlabel( CMSsystemlabelposx,CMSsystemlabelposy, CMSsystemlabel.c_str()); 
	tCMSsystemlabel.SetTextSize(figuretextsize);
	tCMSsystemlabel.SetNDC(kTRUE);

	TLatex tmultlabel( multlabelposx,multlabelposy, multlabel.c_str()); 
	tmultlabel.SetTextSize(figuretextsize);
	tmultlabel.SetNDC(kTRUE);



	kaonv2.Draw("AP");
	protv2.Draw("P");

	kaonv2_syst.Draw("2 SAME");
	protv2_syst.Draw("2 SAME");

	HIN14002_k0s[multBin].Draw("P SAME");
	HIN14002_lam[multBin].Draw("P SAME");

	v2vsptlegend.AddEntry(&kaonv2,Form("HIN-15-007 K^{#pm}" ), "P");
	v2vsptlegend.AddEntry(&protv2,Form("HIN-15-007 p^{#pm}" ), "P");
	v2vsptlegend.AddEntry(&HIN14002_k0s[multBin],"HIN-14-002 K_{S}^{0}", "P");
	v2vsptlegend.AddEntry(&HIN14002_lam[multBin],"HIN-14-002 #Lambda", "P");
	v2vsptlegend.Draw("SAME");

	tCMSsystemlabel.Draw();

	tmultlabel.Draw();
	
	std::string dir  = Form("./results/%s/v2/", tag.c_str());
	std::string label = Form("v2vspt_all_nTrk_%03d-%03d_HIN14002_comparison", mult1, mult2); 
	std::string	pngfigure = dir+label+".png";
	std::string	pdffigure = dir+label+".pdf";
	canvas_v2_vs_pT.SaveAs( pngfigure.c_str() );
	canvas_v2_vs_pT.SaveAs( pdffigure.c_str() );

	}

}

void CorrelationFramework::makeFigv2ptNtrk()
{

	int nPtBins_proj[5] = {14, 6, 6, 10};

 	for(int TypBin=0; TypBin < nCorrTyp; TypBin++)
	{
		TCanvas canvas_v2ptNtrk ("v2 vs pT", "v_{2} values as a function of p_{T}; p_{T} [GeV/c];v_{2}", 1024, 768);
	
		canvas_v2ptNtrk.SetLeftMargin(0.10);
	   canvas_v2ptNtrk.SetBottomMargin(0.12);
	   canvas_v2ptNtrk.SetRightMargin(0.1);

		v2ptNtrkhisto[TypBin]->Draw("LEGO2");

		std::string dir  = Form("./results/%s/v2/", tag.c_str());
		std::string label = Form("v2ptNtrk_%d", TypBin); 
		std::string	pngfigure = dir+label+".png";
		std::string	pdffigure = dir+label+".pdf";

		canvas_v2ptNtrk.SaveAs( pngfigure.c_str() );
		canvas_v2ptNtrk.SaveAs( pdffigure.c_str() );


		TCanvas canvas_v2Ntrk ("v2 vs pT", "v_{2} values as a function of p_{T}; p_{T} [GeV/c];v_{2}", 1024, 768);
		TH1D *proj = v2ptNtrkhisto[TypBin]->ProjectionY(Form("proj_%d"), 2, nPtBins_proj[TypBin]);

		canvas_v2Ntrk.SetLeftMargin(0.10);
	   canvas_v2Ntrk.SetBottomMargin(0.12);
	   canvas_v2Ntrk.SetRightMargin(0.1);

		proj->Draw("");

		dir  = Form("./results/%s/v2/", tag.c_str());
		label = Form("v2Ntrk_%d", TypBin); 
		pngfigure = dir+label+".png";
		pdffigure = dir+label+".pdf";

		canvas_v2Ntrk.SaveAs( pngfigure.c_str() );
		canvas_v2Ntrk.SaveAs( pdffigure.c_str() );



	}
}


////////////////////////////////
// - makeFigv3vspT_allparticles
void CorrelationFramework::makeFigv3vspT_allparticles(int multBin, std::string tag)
{

	gStyle->SetOptStat(0);
	double ptw = 0.02;

	double **pt;
	double **dpt;
	double **v3;
	double **v3_StatError;
	double **v3_SystError;

	pt       = new double*[nCorrTyp];
	dpt       	 = new double*[nCorrTyp];
	v3       = new double*[nCorrTyp];
	v3_StatError = new double*[nCorrTyp];
	v3_SystError = new double*[nCorrTyp];

 	for(int TypBin=0; TypBin < nCorrTyp; TypBin++)
	{
		pt      [TypBin] = new double[nPtBins[TypBin]];
		dpt     [TypBin] = new double[nPtBins[TypBin]];
		v3      [TypBin] = new double[nPtBins[TypBin]];
		v3_StatError[TypBin] = new double[nPtBins[TypBin]];
		v3_SystError[TypBin] = new double[nPtBins[TypBin]];


   	std::vector< double > ptvec = CorrelationFramework::Getptvec(TypBin, 0.);
   	std::vector< double > v3vec = CorrelationFramework::Getv3vec(TypBin, multBin);
   	std::vector< double > v3_StatErrorvec = CorrelationFramework::Getv3_StatErrorvec(TypBin, multBin);
   	std::vector< double > v3_SystErrorvec = CorrelationFramework::Getv3_SystErrorvec(TypBin, multBin);

		for(int ptBin = 0; ptBin < nPtBins[TypBin]; ptBin++)
		{
			pt[TypBin][ptBin]        = ptvec[ptBin];
			dpt[TypBin][ptBin]       = ptw;
			v3[TypBin][ptBin]        = v3vec[ptBin];
			v3_StatError[TypBin][ptBin]  = v3_StatErrorvec[ptBin];
			v3_SystError[TypBin][ptBin]  = v3_SystErrorvec[ptBin];
		};

	}

	// *** Plotting the graphs *** //
	gStyle->SetPadTickY(1);
	gStyle->SetPadTickX(1);
	TCanvas canvas_v3_vs_pT ("v3 vs pT", "v_{3} values as a function of p_{T}; p_{T} [GeV/c];v_{2}", 800, 600);

	canvas_v3_vs_pT.SetLeftMargin(0.10);
   canvas_v3_vs_pT.SetBottomMargin(0.12);
   canvas_v3_vs_pT.SetRightMargin(0.05);
   canvas_v3_vs_pT.SetTopMargin(0.05);
	
	TGraphErrors cparv3 = cpar_v2(nPtBins[0], pt[0], v3[0], 0, v3_StatError[0] );
	TGraphErrors pionv3 = pion_v2(nPtBins[1], pt[1], v3[1], 0, v3_StatError[1] );
	TGraphErrors kaonv3 = kaon_v2(nPtBins[2], pt[2], v3[2], 0, v3_StatError[2] );
	TGraphErrors protv3 = prot_v2(nPtBins[3], pt[3], v3[3], 0, v3_StatError[3] );

	TGraphErrors cparv3_syst = cpar_v2_syst(nPtBins[0], pt[0], v3[0], dpt[0], v3_SystError[0] );
	TGraphErrors pionv3_syst = pion_v2_syst(nPtBins[1], pt[1], v3[1], dpt[1], v3_SystError[1] );
	TGraphErrors kaonv3_syst = kaon_v2_syst(nPtBins[2], pt[2], v3[2], dpt[2], v3_SystError[2] );
	TGraphErrors protv3_syst = prot_v2_syst(nPtBins[3], pt[3], v3[3], dpt[3], v3_SystError[3] );

	double v3vspt_ptmin = 0.0;
	double v3vspt_ptmax = 2.5;
	double v3vspt_v3min = 0.0;
	double v3vspt_v3max = 0.08;

	cparv3.SetPoint(0, -50, -5);
	pionv3.SetPoint(0, -50, -5);
	kaonv3.SetPoint(0, -50, -5);
	protv3.SetPoint(0, -50, -5);

	cparv3_syst.SetPoint(0, -50, -5);
	pionv3_syst.SetPoint(0, -50, -5);
	kaonv3_syst.SetPoint(0, -50, -5);
	protv3_syst.SetPoint(0, -50, -5);

	cparv3.SetTitle("");
   cparv3.GetXaxis()->SetLimits(v3vspt_ptmin,v3vspt_ptmax);
	cparv3.GetXaxis()->SetTitle("p_{T} [GeV/c]");                              			  
	cparv3.GetXaxis()->CenterTitle(1);
	cparv3.GetXaxis()->SetTitleOffset(1.2);
	cparv3.GetXaxis()->SetTitleSize(figuretextsize);
	cparv3.GetYaxis()->SetRangeUser(v3vspt_v3min,v3vspt_v3max);
	cparv3.GetYaxis()->SetTitle("v_{3}");
	cparv3.GetYaxis()->CenterTitle(1);
	cparv3.GetYaxis()->SetTitleOffset(1.2);
	cparv3.GetYaxis()->SetTitleSize(figuretextsize);

	TF1 *cparv3_fit = new TF1 ("cparv3_fit", "[1]*x+[2]*x*x",0.2,3);
	TF1 *pionv3_fit = new TF1 ("pionv3_fit", "[1]*x+[2]*x*x",0.2,0.9);
	TF1 *kaonv3_fit = new TF1 ("kaonv3_fit", "[1]*x+[2]*x*x",0.2,0.9);
	TF1 *protv3_fit = new TF1 ("protv3_fit", "[1]*x+[2]*x*x",0.2,1.5);

	cparv3_fit->SetLineColor(kBlack);
	pionv3_fit->SetLineColor(kRed);
	kaonv3_fit->SetLineColor(kGreen);
	protv3_fit->SetLineColor(kBlue);

	cparv3_fit->SetLineStyle(9);
	pionv3_fit->SetLineStyle(9);
	kaonv3_fit->SetLineStyle(9);
	protv3_fit->SetLineStyle(9);

	cparv3.Fit("cparv2_fit", "0R");
	pionv3.Fit("pionv2_fit", "0R");
	kaonv3.Fit("kaonv2_fit", "0R");
	protv3.Fit("protv2_fit", "0R");

	cparv3.Draw("AP");
	pionv3.Draw("P");
	kaonv3.Draw("P");
	protv3.Draw("P");

	cparv3_syst.Draw("2 SAME");
	pionv3_syst.Draw("2 SAME");
	kaonv3_syst.Draw("2 SAME");
	protv3_syst.Draw("2 SAME");

	double legend_x1=.14;
	double legend_y1=0.56;
	double legend_x2=legend_x1+.20;
	double legend_y2=legend_y1+.20;
	double CMSsystemlabelposx = 0.14;
	double CMSsystemlabelposy = 0.84;
	double multlabelposx = 0.62;
	double multlabelposy = 0.24;

	TLegend v3vsptlegend (legend_x1, legend_y1, legend_x2, legend_y2);
	v3vsptlegend.SetFillStyle(0);
	v3vsptlegend.SetBorderSize(0);
	v3vsptlegend.AddEntry(&cparv3,"charged", "P");
	v3vsptlegend.AddEntry(&pionv3,"#pi", "P");
	v3vsptlegend.AddEntry(&kaonv3,"K", "P");
	v3vsptlegend.AddEntry(&protv3,"p", "P");

	v3vsptlegend.SetTextSize(figuretextsize);
	v3vsptlegend.Draw("SAME");

   int mult1 = multiplicity_Ana(multBin, 0, nMultiplicityBins_Ana);
	int mult2 = multiplicity_Ana(multBin, 1, nMultiplicityBins_Ana);

	std::string CMSsystemlabel = Form("#splitline{CMS Preliminary pPb}{#sqrt{s_{NN}} = 5.02 TeV L_{int} = 35 nb^{-1}}", mult1, mult2);
	std::string multlabel = Form("%3d #leq N_{trk}^{offline} < %3d", mult1, mult2);

	TLatex tCMSsystemlabel( CMSsystemlabelposx,CMSsystemlabelposy, CMSsystemlabel.c_str()); 
	tCMSsystemlabel.SetTextSize(figuretextsize);
	tCMSsystemlabel.SetNDC(kTRUE);
	tCMSsystemlabel.Draw();

	TLatex tmultlabel( multlabelposx,multlabelposy, multlabel.c_str()); 
	tmultlabel.SetTextSize(figuretextsize);
	tmultlabel.SetNDC(kTRUE);
	tmultlabel.Draw();
	
	std::string dir  = Form("./results/%s/v3/", tag.c_str());
	std::string label = Form("v3vspt_all_nTrk_%03d-%03d", mult1, mult2); 
	std::string	pngfigure = dir+label+".png";
	std::string	pdffigure = dir+label+".pdf";
	canvas_v3_vs_pT.SaveAs( pngfigure.c_str() );
	canvas_v3_vs_pT.SaveAs( pdffigure.c_str() );
}

//////////////////////////////////
// makeFigv2vsnTrk_allparticles
void CorrelationFramework::makeFigv2vsnTrk_allparticles( std::string tag )
{

	gStyle->SetOptStat(0);

	double offset = 0;

   std::vector< double > nTrkvec = CorrelationFramework::GetnTrkvec(offset);
   std::vector< double > v2vec = CorrelationFramework::Get_cpar_ref_v2vec_nTrk();
   std::vector< double > v2_StatErrorvec = CorrelationFramework::Get_cpar_ref_v2_StatError_vec_nTrk();

	double nTrk[nMultiplicityBins_Ana];
	double v2[nMultiplicityBins_Ana];
	double v2_StatError[nMultiplicityBins_Ana];

	for(int multBin = 0; multBin < nMultiplicityBins_Ana; multBin++)
	{
		nTrk[multBin] = nTrkvec[multBin];
		v2[multBin] = v2vec[multBin];
		v2_StatError[multBin] = v2_StatErrorvec[multBin];
	}

	// *** Plotting the graphs *** //
	TCanvas canvas_pPb_v2_vs_nTrk ("cpar v2 vs nTrk", "v_{2} values as a function of p_{T}; p_{T} [GeV/c];v_{2}", 800, 600);
	
	TGraphErrors *g1 = new TGraphErrors(nMultiplicityBins_Ana, nTrk, v2, 0, v2_StatError);
	g1->SetTitle("Azimuthal correlations, charged particle v2 coefficient nTrk dependence");
	g1->GetXaxis()->SetLimits(0,300);
	g1->GetXaxis()->SetTitle("nTrk");
	g1->GetXaxis()->SetTitleOffset(1.3);
	g1->GetYaxis()->SetRangeUser(0.000,0.2);
	g1->GetYaxis()->SetTitle("v_{2}");
	g1->GetYaxis()->SetTitleOffset(1.4);
	g1->SetLineColor(kMagenta);
	// 8 = full circle
	g1->SetMarkerStyle(2);
	// 6 = magenta
	g1->SetMarkerColor(4);
	g1->Draw("AP");

	TGraphErrors cms = CMSres_v2_chadron_nTrkdep();
	cms.SetMarkerStyle(8);
	cms.SetMarkerColor(1);
	cms.SetLineColor(1);
	cms.Draw("P");

	Double_t xl1=.10, yl1=0.75, xl2=xl1+.45, yl2=yl1+.15;
	TLegend v2vsptlegend (xl1,yl1,xl2,yl2);
	v2vsptlegend.AddEntry(g1,"# Ana c.p - c.p", "P");
	v2vsptlegend.AddEntry(&cms,"# HIN 13-002 pPb", "P");
	v2vsptlegend.SetTextSize(0.032);
	v2vsptlegend.Draw("SAME");

	std::string dir  = Form("./results/%s/v2/", tag.c_str());
	std::string label = "v2_cpar_ref_nTrk_dep"; 
	std::string	pngfigure = dir+label+".png";
	std::string	pdffigure = dir+label+".pdf";
	canvas_pPb_v2_vs_nTrk.SaveAs( pngfigure.c_str() );
	canvas_pPb_v2_vs_nTrk.SaveAs( pdffigure.c_str() );

}

//////////////////////////////////
// makeFigv2vsnTrk_cpar_ref
void CorrelationFramework::makeFigv2vsnTrk_cpar_ref( std::string tag )
{

	gStyle->SetOptStat(0);

	double offset = 0;

   std::vector< double > nTrkvec = CorrelationFramework::GetnTrkvec(offset);
   std::vector< double > v2vec = CorrelationFramework::Get_cpar_ref_v2vec_nTrk();
   std::vector< double > v2_StatErrorvec = CorrelationFramework::Get_cpar_ref_v2_StatError_vec_nTrk();

	double nTrk[nMultiplicityBins_Ana];
	double v2[nMultiplicityBins_Ana];
	double v2_StatError[nMultiplicityBins_Ana];

	for(int multBin = 0; multBin < nMultiplicityBins_Ana; multBin++)
	{
		nTrk[multBin] = nTrkvec[multBin];
		v2[multBin] = v2vec[multBin];
		v2_StatError[multBin] = v2_StatErrorvec[multBin];
	}

	// *** Plotting the graphs *** //
	TCanvas canvas_pPb_v2_vs_nTrk ("cpar v2 vs nTrk", "v_{2} values as a function of p_{T}; p_{T} [GeV/c];v_{2}", 800, 600);
	
	TGraphErrors *g1 = new TGraphErrors(nMultiplicityBins_Ana, nTrk, v2, 0, v2_StatError);
	g1->SetTitle("Azimuthal correlations, charged particle v2 coefficient nTrk dependence");
	g1->GetXaxis()->SetLimits(0,300);
	g1->GetXaxis()->SetTitle("nTrk");
	g1->GetXaxis()->SetTitleOffset(1.3);
	g1->GetYaxis()->SetRangeUser(0.000,0.2);
	g1->GetYaxis()->SetTitle("v_{2}");
	g1->GetYaxis()->SetTitleOffset(1.4);
	g1->SetLineColor(kMagenta);
	// 8 = full circle
	g1->SetMarkerStyle(2);
	// 6 = magenta
	g1->SetMarkerColor(4);
	g1->Draw("AP");

	TGraphErrors cms = CMSres_v2_chadron_nTrkdep();
	cms.SetMarkerStyle(8);
	cms.SetMarkerColor(1);
	cms.SetLineColor(1);
	cms.Draw("P");

	Double_t xl1=.10, yl1=0.75, xl2=xl1+.45, yl2=yl1+.15;
	TLegend v2vsptlegend (xl1,yl1,xl2,yl2);
	v2vsptlegend.AddEntry(g1,"# Ana c.p - c.p", "P");
	v2vsptlegend.AddEntry(&cms,"# HIN 13-002 pPb", "P");
	v2vsptlegend.SetTextSize(0.032);
	v2vsptlegend.Draw("SAME");

	std::string dir  = Form("./results/%s/v2/", tag.c_str());
	std::string label = "v2_cpar_ref_nTrk_dep"; 
	std::string	pngfigure = dir+label+".png";
	std::string	pdffigure = dir+label+".pdf";
	canvas_pPb_v2_vs_nTrk.SaveAs( pngfigure.c_str() );
	canvas_pPb_v2_vs_nTrk.SaveAs( pdffigure.c_str() );

}

////////////////////////////////////////
// - makeFigv2vspT_HIN13002
void CorrelationFramework::makeFigv2vspT_HIN13002(std::string tag)
{

	gStyle->SetOptStat(0);

	std::string dir  = Form("./results/%s/v2/", tag.c_str());
	std::string label;

	std::string CMSsystemlabel = "#splitline{CMS Preliminary pPb}{#sqrt{s_{NN}} = 5.02 TeV L_{int} = 35 nb^{-1}}";

	// Get the graphs
	TGraphErrors cpar_120150 = CorrelationFramework::Getv2TGraphError(0, 5);
	TGraphErrors cpar_150185 = CorrelationFramework::Getv2TGraphError(0, 6);
	TGraphErrors cpar_185220 = CorrelationFramework::Getv2TGraphError(0, 7);
	TGraphErrors cmsr_120150 = CMSres_v2_chadron_120_150();
	TGraphErrors cmsr_150185 = CMSres_v2_chadron_150_185();
	TGraphErrors cmsr_185220 = CMSres_v2_chadron_185_220();

	// *** Plotting the graphs *** //
	gStyle->SetPadTickY(1);
	gStyle->SetPadTickX(1);


	double v2vspt_ptmin = 0.0;
	double v2vspt_ptmax = 2.5;
	double v2vspt_v2min = 0.0;
	double v2vspt_v2max = 0.16;

	cmsr_120150.SetMarkerStyle(24);
	cmsr_120150.SetMarkerSize(1.4);
	cmsr_120150.SetMarkerColor(6);
	cmsr_120150.SetLineColor(6);

	double legend_x1 = .44;
	double legend_y1 = 0.25;
	double legend_x2 = legend_x1+.20;
	double legend_y2 = legend_y1+.14;
	double CMSsystemlabelposx = 0.14;
	double CMSsystemlabelposy = 0.84;
	double multlabelposx = 0.62;
	double multlabelposy = 0.24;

	TLatex tCMSsystemlabel( CMSsystemlabelposx,CMSsystemlabelposy, CMSsystemlabel.c_str()); 
	tCMSsystemlabel.SetTextSize(figuretextsize);
	tCMSsystemlabel.SetNDC(kTRUE);

	// 120-150
	TCanvas canvas_v2_vs_pT_120_150 ("v2 vs pT", "v_{2} values as a function of p_{T}; p_{T} [GeV/c];v_{2}", 800, 600);
	canvas_v2_vs_pT_120_150.SetLeftMargin(0.10);
   canvas_v2_vs_pT_120_150.SetBottomMargin(0.12);
   canvas_v2_vs_pT_120_150.SetRightMargin(0.05);
   canvas_v2_vs_pT_120_150.SetTopMargin(0.05);
	cpar_120150.Draw("ALP");
	cmsr_120150.Draw("LP");
	tCMSsystemlabel.Draw();

	TLegend v2vsptlegend_120_150 (legend_x1, legend_y1, legend_x2, legend_y2);
	v2vsptlegend_120_150.SetFillStyle(0);
	v2vsptlegend_120_150.SetBorderSize(0);
	v2vsptlegend_120_150.AddEntry(&cpar_120150,"charged    N_{trk}^{offline} = 120-150", "P");
	v2vsptlegend_120_150.AddEntry(&cmsr_120150,"HIN 13-002 N_{trk}^{offline} = 120-150", "P");
	v2vsptlegend_120_150.SetTextSize(figuretextsize);
	v2vsptlegend_120_150.Draw("SAME");

	label = "v2vspt_HIN13002_comparison_nTrk_120-150"; 
	std::string	pngfigure = dir+label+".png";
	std::string	pdffigure = dir+label+".pdf";
	canvas_v2_vs_pT_120_150.SaveAs( pngfigure.c_str() );
	canvas_v2_vs_pT_120_150.SaveAs( pdffigure.c_str() );

	// 150-185
	TCanvas canvas_v2_vs_pT_150_185 ("v2 vs pT", "v_{2} values as a function of p_{T}; p_{T} [GeV/c];v_{2}", 800, 600);
	canvas_v2_vs_pT_150_185.SetLeftMargin(0.10);
   canvas_v2_vs_pT_150_185.SetBottomMargin(0.12);
   canvas_v2_vs_pT_150_185.SetRightMargin(0.05);
   canvas_v2_vs_pT_150_185.SetTopMargin(0.05);
	cpar_150185.Draw("LP");
	cmsr_150185.Draw("LP");
	tCMSsystemlabel.Draw();

	TLegend v2vsptlegend_150_185 (legend_x1, legend_y1, legend_x2, legend_y2);
	v2vsptlegend_150_185.SetFillStyle(0);
	v2vsptlegend_150_185.SetBorderSize(0);
	v2vsptlegend_150_185.AddEntry(&cpar_120150,"analysis 150-185", "P");
	v2vsptlegend_150_185.AddEntry(&cmsr_120150,"13-002   150-185", "P");
	v2vsptlegend_150_185.SetTextSize(figuretextsize);
	v2vsptlegend_150_185.Draw("SAME");

	label = "v2vspt_HIN13002_comparison_nTrk_150-185"; 
	pngfigure = dir+label+".png";
	pdffigure = dir+label+".pdf";
	canvas_v2_vs_pT_150_185.SaveAs( pngfigure.c_str() );
	canvas_v2_vs_pT_150_185.SaveAs( pdffigure.c_str() );

	// 185-220
	TCanvas canvas_v2_vs_pT_185_220 ("v2 vs pT", "v_{2} values as a function of p_{T}; p_{T} [GeV/c];v_{2}", 800, 600);
	canvas_v2_vs_pT_185_220.SetLeftMargin(0.10);
   canvas_v2_vs_pT_185_220.SetBottomMargin(0.12);
   canvas_v2_vs_pT_185_220.SetRightMargin(0.05);
   canvas_v2_vs_pT_185_220.SetTopMargin(0.05);
	cpar_185220.Draw("ALP");
	cmsr_185220.Draw("LP");
	tCMSsystemlabel.Draw();

	TLegend v2vsptlegend_185_220 (legend_x1, legend_y1, legend_x2, legend_y2);
	v2vsptlegend_185_220.SetFillStyle(0);
	v2vsptlegend_185_220.SetBorderSize(0);
	v2vsptlegend_185_220.AddEntry(&cpar_120150,"analysis 185-220", "P");
	v2vsptlegend_185_220.AddEntry(&cmsr_120150,"13-002   185-220", "P");
	v2vsptlegend_185_220.SetTextSize(figuretextsize);
	v2vsptlegend_185_220.Draw("SAME");

	label = "v2vspt_HIN13002_comparison_nTrk_185-220"; 
	pngfigure = dir+label+".png";
	pdffigure = dir+label+".pdf";
	canvas_v2_vs_pT_185_220.SaveAs( pngfigure.c_str() );
	canvas_v2_vs_pT_185_220.SaveAs( pdffigure.c_str() );
}

///////////////////////////////////////////////////////
// makeFigv2vspT_allparticles_with_selfcorrelation
void CorrelationFramework::makeFigv2vspT_allparticles_with_selfcorrelation(int multBin, std::string tag)
{

	gStyle->SetOptStat(0);

	double pt               [nCorrTyp][nPtBinsMax_];
	double v2	     	      [nCorrTyp][nPtBinsMax_];
	double v2_StatError     [nCorrTyp][nPtBinsMax_];
	double v2_self          [nCorrTyp][nPtBinsMax_];
	double v2_self_StatError[nCorrTyp][nPtBinsMax_];

 	for(int TypBin=0; TypBin < nCorrTyp; TypBin++)
	{

   	std::vector< double > ptvec = CorrelationFramework::Getptvec(TypBin, 0.);
   	std::vector< double > v2vec = CorrelationFramework::Getv2vec(TypBin, multBin);
   	std::vector< double > v2_StatErrorvec = CorrelationFramework::Getv2_StatErrorvec(TypBin, multBin);
   	std::vector< double > v2_self_vec = CorrelationFramework::Get_self_v2vec(TypBin, multBin);
   	std::vector< double > v2_self_StatErrorvec = CorrelationFramework::Get_self_v2_StatErrorvec(TypBin, multBin);

		for(int ptBin = 0; ptBin < nPtBins[TypBin]; ptBin++)
		{
			pt[TypBin][ptBin]                = ptvec[ptBin];
			v2[TypBin][ptBin]                = v2vec[ptBin];
			v2_StatError[TypBin][ptBin]      = v2_StatErrorvec[ptBin];
			v2_self[TypBin][ptBin]           = v2_self_vec[ptBin];
			v2_self_StatError[TypBin][ptBin] = v2_self_StatErrorvec[ptBin];
		}


	}

	// *** Plotting the graphs *** //
	TCanvas canvas_v2_vs_pT ("v2 vs pT", "v_{2} values as a function of p_{T}; p_{T} [GeV/c];v_{2}", 800, 600);

	TGraphErrors cparv2 = cpar_v2(nPtBins[0], pt[0], v2[0], 0, v2_StatError[0] );
	TGraphErrors pionv2 = pion_v2(nPtBins[1], pt[1], v2[1], 0, v2_StatError[1] );
	TGraphErrors kaonv2 = kaon_v2(nPtBins[2], pt[2], v2[2], 0, v2_StatError[2] );
	TGraphErrors protv2 = prot_v2(nPtBins[3], pt[3], v2[3], 0, v2_StatError[3] );
	TGraphErrors cparv2_self = cpar_self_v2(nPtBins[0], pt[0], v2_self[0], 0, v2_self_StatError[0] );
	TGraphErrors pionv2_self = pion_self_v2(nPtBins[1], pt[1], v2_self[1], 0, v2_self_StatError[1] );
	TGraphErrors kaonv2_self = kaon_self_v2(nPtBins[2], pt[2], v2_self[2], 0, v2_self_StatError[2] );
	TGraphErrors protv2_self = prot_self_v2(nPtBins[3], pt[3], v2_self[3], 0, v2_self_StatError[3] );

	cparv2.SetTitle("Azimuthal correlations, v2 coefficient p_{T} dependence");
	cparv2.GetXaxis()->SetLimits(0,3.5);
	cparv2.GetXaxis()->SetTitle("p_{T} [GeV/c]");                              			  
	cparv2.GetXaxis()->SetTitleOffset(1.3);
	cparv2.GetYaxis()->SetRangeUser(-0.01,0.25);
	cparv2.GetYaxis()->SetTitle("v_{2}");
	cparv2.GetYaxis()->SetTitleOffset(1.4);
	cparv2.Draw("APL");

	pionv2.Draw("LP");
	kaonv2.Draw("LP");
	protv2.Draw("LP");
	cparv2_self.Draw("LP");
	pionv2_self.Draw("LP");
	kaonv2_self.Draw("LP");
	protv2_self.Draw("LP");


	TGraphErrors cms = CMSres_v2_chadron_120_150();
	cms.SetMarkerStyle(8);
	cms.SetMarkerColor(6);
	cms.SetLineColor(6);
	cms.Draw("LP");

	Double_t xl1=.10, yl1=0.67, xl2=xl1+.30, yl2=yl1+.22;
	TLegend v2vsptlegend (xl1,yl1,xl2,yl2);
	v2vsptlegend.AddEntry(&cparv2,"# c. p. - c. p", "P");
	v2vsptlegend.AddEntry(&pionv2,"# #pi - c.p", "P");
	v2vsptlegend.AddEntry(&kaonv2,"# K - c.p", "P");
	v2vsptlegend.AddEntry(&protv2,"# p - c.p", "P");
	v2vsptlegend.AddEntry(&cparv2,"# c. p. - c. p self", "P");
	v2vsptlegend.AddEntry(&pionv2,"# #pi - c.p self", "P");
	v2vsptlegend.AddEntry(&kaonv2,"# K - c.p self", "P");
	v2vsptlegend.AddEntry(&protv2,"# p - c.p self", "P");
	v2vsptlegend.AddEntry(&cms,"# CMS HIN 13-002 c.p - c.p nTrk [120-150]", "L");
	v2vsptlegend.SetTextSize(0.032);
	v2vsptlegend.Draw("SAME");

   int mult1 = multiplicity_Ana(multBin, 0, nMultiplicityBins_Ana);
	int mult2 = multiplicity_Ana(multBin, 1, nMultiplicityBins_Ana);

	std::string figlabel = Form("nTrk [ %03d - %03d ]", mult1, mult2);

	double upperleftposx = 0.65;
	double upperleftposy = 0.15;

	TLatex tlabel( upperleftposx,upperleftposy, figlabel.c_str()); 
	tlabel.SetTextSize(0.032);
	tlabel.SetNDC(kTRUE);
	tlabel.Draw();
	
	std::string dir  = Form("./results/%s/v2/", tag.c_str());
	std::string label = Form("v2vspt_all_self_incl_nTrk_%03d-%03d", mult1, mult2); 
	std::string	pngfigure = dir+label+".png";
	std::string	pdffigure = dir+label+".pdf";
	canvas_v2_vs_pT.SaveAs( pngfigure.c_str() );
	canvas_v2_vs_pT.SaveAs( pdffigure.c_str() );

}


// makeFigCorrel2D
void CorrelationFramework::makeFigCorrel2D( std::string tag )
{

	gStyle->SetOptStat(0);

 std::cout << "Making Correl2D figures... " << std::endl;

 // Displaying
 for(int TypBin=0; TypBin < nCorrTyp; TypBin++)
 for(int ptBin=0; ptBin < nPtBins[TypBin]; ptBin++)
 for(int multiplicityBin=0; multiplicityBin < nMultiplicityBins_Ana; multiplicityBin++)
 {	

  double pt1 = pt(TypBin, ptBin, 0);
  double pt2 = pt(TypBin, ptBin, 1);
  int mult1 = multiplicity_Ana(multiplicityBin, 0, nMultiplicityBins_Ana);
  int mult2 = multiplicity_Ana(multiplicityBin, 1, nMultiplicityBins_Ana);

   std::string fig_correl2D_signal = Form("./results/%s/correl2D/correl2D_signal_typ_%d_pt_%.2f-%.2f_nTrk_%03d-%03d", tag.c_str(), TypBin, pt1, pt2, mult1, mult2 );
	std::string fig_correl2D_backgr = Form("./results/%s/correl2D/correl2D_backgr_typ_%d_pt_%.2f-%.2f_nTrk_%03d-%03d", tag.c_str(), TypBin, pt1, pt2, mult1, mult2 );
	std::string fig_correl2D_functi = Form("./results/%s/correl2D/correl2D_functi_typ_%d_pt_%.2f-%.2f_nTrk_%03d-%03d", tag.c_str(), TypBin, pt1, pt2, mult1, mult2 );

	std::string title_correl2D_signal = Form("CMS Preliminary pPb #sqrt{s_{NN}} = 5.02 TeV L_{int} = 35 nb^{-1}"     , TypBin, pt1, pt2, mult1, mult2 );
	std::string title_correl2D_backgr = Form("CMS Preliminary pPb #sqrt{s_{NN}} = 5.02 TeV L_{int} = 35 nb^{-1}", TypBin, pt1, pt2, mult1, mult2 );
	std::string title_correl2D_functi = Form("CMS Preliminary pPb #sqrt{s_{NN}} = 5.02 TeV L_{int} = 35 nb^{-1}",    TypBin, pt1, pt2, mult1, mult2 );

	std::string zaxistitle_correl2D_signal = "S(#Delta #eta, #Delta #phi)";
	std::string zaxistitle_correl2D_backgr = "B(#Delta #eta, #Delta #phi)";
	std::string zaxistitle_correl2D_functi = "#frac{1}{N_{trig}} #frac{d^{2}N^{pair}}{d#Delta#eta d#Delta#phi}";

   std::string fig_correl2D_self_signal = Form("./results/%s/correl2D/correl2D_self_signal_typ_%d_pt_%.2f-%.2f_nTrk_%03d-%03d", tag.c_str(), TypBin, pt1, pt2, mult1, mult2 );
	std::string fig_correl2D_self_backgr = Form("./results/%s/correl2D/correl2D_self_backgr_typ_%d_pt_%.2f-%.2f_nTrk_%03d-%03d", tag.c_str(), TypBin, pt1, pt2, mult1, mult2 );
	std::string fig_correl2D_self_functi = Form("./results/%s/correl2D/correl2D_self_functi_typ_%d_pt_%.2f-%.2f_nTrk_%03d-%03d", tag.c_str(), TypBin, pt1, pt2, mult1, mult2 );

	std::string title_correl2D_self_signal = Form("Signal 2D Correlation function - Typ = %d, p_{T} = [%.2f - %.2f], nTrk = [%d-%d]"     , TypBin, pt1, pt2, mult1, mult2 );
	std::string title_correl2D_self_backgr = Form("Background 2D Correlation function - Typ = %d, p_{T} = [%.2f - %.2f], nTrk = [%d-%d];", TypBin, pt1, pt2, mult1, mult2 );
	std::string title_correl2D_self_functi = Form("2D Correlation function - m = %d, p_{T} = [%.2f - %.2f], nTrk = [%d-%d]",               TypBin, pt1, pt2, mult1, mult2 );

	std::string leftlabel  = Form("#splitline{#splitline{  %d #leq N_{trk}^{offline} < %d}{ %.1f < p_{T}^{trig}  < %.1f GeV/c}}{ %.1f < p_{T}^{assoc} < %.1f GeV/c}", mult1, mult2, pt1, pt2, ptref1, ptref2);
	std::string rightlabel = Form("%s - charged", particletype(TypBin).c_str());


	plot2DCorrelation(correl2D_signal	  [TypBin][ptBin][multiplicityBin],  fig_correl2D_signal     , title_correl2D_signal     , zaxistitle_correl2D_signal, leftlabel, rightlabel);
	plot2DCorrelation(correl2D_backgr	  [TypBin][ptBin][multiplicityBin],  fig_correl2D_backgr     , title_correl2D_backgr     , zaxistitle_correl2D_backgr, leftlabel, rightlabel);
	plot2DCorrelation(correl2D_functi	  [TypBin][ptBin][multiplicityBin],  fig_correl2D_functi     , title_correl2D_functi     , zaxistitle_correl2D_functi, leftlabel, rightlabel);
//	plot2DCorrelation(correl2D_self_signal[TypBin][ptBin][multiplicityBin],  fig_correl2D_self_signal, title_correl2D_self_signal, zaxistitle_correl2D_signal, leftlabel, rightlabel);
//	plot2DCorrelation(correl2D_self_backgr[TypBin][ptBin][multiplicityBin],  fig_correl2D_self_backgr, title_correl2D_self_backgr, zaxistitle_correl2D_backgr, leftlabel, rightlabel);
//	plot2DCorrelation(correl2D_self_functi[TypBin][ptBin][multiplicityBin],  fig_correl2D_self_functi, title_correl2D_self_functi, zaxistitle_correl2D_functi, leftlabel, rightlabel);



 }
}


/////////////////////////////////////////////
// MakeFig1DCorrel
// - fits the 1D correlation function with
//   a Fourier series
void CorrelationFramework::makeFigCorrel1D(std::string tag)
{

	gStyle->SetOptStat(0);

	std::cout << "Making Correl1D figures..." << std::endl;


	for(int TypBin=0; TypBin < nCorrTyp; TypBin++)
 	for(int ptBin=0; ptBin < nPtBins[TypBin]; ptBin++)
 	for(int multBin=0; multBin < nMultiplicityBins_Ana; multBin++)
 	{

	double pt1 = pt(TypBin, ptBin, 0);
	double pt2 = pt(TypBin, ptBin, 1);
	int mult1 = multiplicity_Ana(multBin, 0, nMultiplicityBins_Ana);
	int mult2 = multiplicity_Ana(multBin, 1, nMultiplicityBins_Ana);

	std::string corrtypelabel = Form("%s - charged", particletype(TypBin).c_str());

	double chisqrdperndf_ = correl1D_FitResults[TypBin][ptBin][multBin].chisqrdperndf;

	double a0_ = correl1D_FitResults[TypBin][ptBin][multBin].a0;
	double V1_ = correl1D_FitResults[TypBin][ptBin][multBin].V1;
	double V2_ = correl1D_FitResults[TypBin][ptBin][multBin].V2;
	double V3_ = correl1D_FitResults[TypBin][ptBin][multBin].V3;

	double a0_Error_ = correl1D_FitResults[TypBin][ptBin][multBin].a0_Error;
	double V1_Error_ = correl1D_FitResults[TypBin][ptBin][multBin].V1_Error;
	double V2_Error_ = correl1D_FitResults[TypBin][ptBin][multBin].V2_Error;
	double V3_Error_ = correl1D_FitResults[TypBin][ptBin][multBin].V3_Error;

   double phimin = -TMath::Pi()/2;
   double phimax = 3*TMath::Pi()/2;
   
	TCanvas canvas_correl_1D ("canvas_correl_1D","",800,600);

   canvas_correl_1D.SetLeftMargin  (correl1D_leftmargin  );
   canvas_correl_1D.SetRightMargin (correl1D_rightmargin );
   canvas_correl_1D.SetTopMargin  (correl1D_topmargin   );
   canvas_correl_1D.SetBottomMargin(correl1D_bottommargin);

	correl1D[TypBin][ptBin][multBin]->SetTitle(";#Delta#phi;#frac{1}{N_{trig}} #frac{dN^{pair}}{#Delta#phi}");
	correl1D[TypBin][ptBin][multBin]->GetXaxis()->CenterTitle(1);
	correl1D[TypBin][ptBin][multBin]->GetXaxis()->SetTitleSize(correl1D_xlabelsize);
	correl1D[TypBin][ptBin][multBin]->SetTitleOffset(1.2,"X");
	correl1D[TypBin][ptBin][multBin]->GetYaxis()->CenterTitle(1);
	correl1D[TypBin][ptBin][multBin]->GetYaxis()->SetTitleSize(correl1D_ylabelsize);
	correl1D[TypBin][ptBin][multBin]->SetTitleOffset(1.8,"Y");

	gStyle->SetOptStat(0);

	TF1 fitFunc = TF1 ("fitFunc", "[0] * ( 1 + 2*[1]*cos(x) + 2*[2]*cos(2*x) + 2*[3]*cos(3*x) )");

	fitFunc.SetParameter(0, a0_); 
	fitFunc.SetParameter(1, V1_);
	fitFunc.SetParameter(2, V2_);
	fitFunc.SetParameter(3, V3_);

	fitFunc.SetParError(0, a0_Error_);
	fitFunc.SetParError(1, V1_Error_);
	fitFunc.SetParError(2, V2_Error_);
	fitFunc.SetParError(3, V3_Error_);
	
	TF1 baseline = TF1 (  "baseline", "[0]", phimin, phimax);
	baseline.SetLineColor(kBlack);
	baseline.SetLineStyle(3);
	baseline.SetLineWidth(1);
	baseline.SetParameter(0, a0_);

	TF1 Fourier1 = TF1 ("Fourier1th", "[0]*( 1 + 2*[1]*cos(1*x) )", phimin, phimax);
	Fourier1.SetLineColor(8);
	Fourier1.SetLineWidth(1);
	Fourier1.SetLineStyle(6);
	Fourier1.SetParameter(0, a0_);
	Fourier1.SetParameter(1, V1_);

	TF1 Fourier2 = TF1 ("Fourier2th", "[0]*( 1 + 2*[1]*cos(2*x) )", phimin, phimax);
	Fourier2.SetLineColor(kMagenta);
	Fourier2.SetLineWidth(1);
	Fourier2.SetLineStyle(2);
	Fourier2.SetParameter(0, a0_);
	Fourier2.SetParameter(1, V2_);

	TF1 Fourier3 = TF1 ("Fourier3th", "[0]*( 1 + 2*[1]*cos(3*x) )", phimin, phimax);
	Fourier3.SetLineColor(kBlue);
	Fourier3.SetLineWidth(1);
	Fourier3.SetLineStyle(8);
	Fourier3.SetParameter(0, a0_);
	Fourier3.SetParameter(1, V3_);

	correl1D[TypBin][ptBin][multBin]->Draw("P");
	fitFunc.Draw("SAME");
	baseline.Draw("SAME");
	Fourier1.Draw("SAME");
	Fourier2.Draw("SAME");
	Fourier3.Draw("SAME");

	double upperleftposx = 0.66;
	double upperleftposy = 0.33;
	double shift = 0.04;

	TLatex label1 = label_CMS_pPb(correl1D_label_CMS_pPb_posx, correl1D_label_CMS_pPb_posy, correl1D_figuretextsize);
	TLatex label2 = label_CorrTyp(correl1D_label_corrtyp_posx, correl1D_label_corrtyp_posy, correl1D_figuretextsize, TypBin);
	TLatex label3 = label_Ntrk_pt(correl1D_label_bin_posx, correl1D_label_bin_posy, correl1D_figuretextsize, TypBin, multBin, ptBin);

	label1.Draw(); label2.Draw(); label3.Draw();

	// Legend
	Double_t correl1D_xl2=correl1D_xl1+.15, correl1D_yl2=correl1D_yl1+.15;
	TLegend v2vsptlegend (correl1D_xl1,correl1D_yl1,correl1D_xl2,correl1D_yl2);
	v2vsptlegend.SetFillStyle(0);
	v2vsptlegend.SetTextSize(v2vspt_legendtextsize);
	v2vsptlegend.SetBorderSize(0);
	v2vsptlegend.AddEntry(&fitFunc,"Fit function","L");
	v2vsptlegend.AddEntry(&baseline,"baseline","L");
	v2vsptlegend.AddEntry(&Fourier1,"V_{1}","L");
	v2vsptlegend.AddEntry(&Fourier2,"V_{2}","L");
	v2vsptlegend.AddEntry(&Fourier3,"V_{3}","L");
	v2vsptlegend.Draw("SAME");


	TLatex tchndf( correl1D_upperleftposx,correl1D_upperleftposy-correl1D_shift, Form("#chi^{2} /n.d.f  = %f", chisqrdperndf_)); 
	tchndf.SetTextSize(correl1D_figuretextsize);
	tchndf.SetNDC(kTRUE);
	tchndf.Draw();

	TLatex t1( correl1D_upperleftposx,correl1D_upperleftposy-2*correl1D_shift,Form("V_{1} = %.4f #pm %.4f ", V1_, V1_Error_) ); 
	t1.SetTextSize(correl1D_figuretextsize);
	t1.SetNDC(kTRUE);
	t1.Draw();

	TLatex t2( correl1D_upperleftposx,correl1D_upperleftposy-3*correl1D_shift,Form("V_{2} = %.4f #pm %.4f ", V2_, V2_Error_) ); 
	t2.SetTextSize(correl1D_figuretextsize);
	t2.SetNDC(kTRUE);
	t2.Draw();

	TLatex t3( correl1D_upperleftposx,correl1D_upperleftposy-4*correl1D_shift,Form("V_{3} = %.5f #pm %.5f ", V3_, V3_Error_) ); 
	t3.SetTextSize(0.032);
	t3.SetNDC(kTRUE);
	t3.Draw();

	std::string dir   = Form("./results/%s/correl1D/", tag.c_str());
	std::string filePDF = Form("correl1D_typ_%d_pt_%.2f-%.2f_nTrk_%03d-%03d.pdf", TypBin, pt1, pt2, mult1, mult2);
	std::string filePNG = Form("correl1D_typ_%d_pt_%.2f-%.2f_nTrk_%03d-%03d.png", TypBin, pt1, pt2, mult1, mult2);

	std::string figurePNG = dir+filePNG;
	std::string figurePDF = dir+filePDF;

	canvas_correl_1D.SaveAs( figurePNG.c_str() );
	canvas_correl_1D.SaveAs( figurePDF.c_str() );

	}

};

/////////////////////////////////////////////
// plot2DCorrelation
// 
//

void plot2DCorrelation(TH2D* correl, std::string figurename, std::string title, std::string zaxistitle, std::string leftlabel, std::string rightlabel)
{

	gStyle->SetOptStat(0);

	TCanvas canvas_correl ("canvas_correl","",800,600);

   canvas_correl.SetLeftMargin  (correl2D_leftmargin  );
   canvas_correl.SetRightMargin (correl2D_rightmargin );
   canvas_correl.SetTopMargin   (correl2D_topmargin   );
   canvas_correl.SetBottomMargin(correl2D_bottommargin);
   canvas_correl.SetTheta(60.839);
   canvas_correl.SetPhi(38.0172);

	correl->SetTitle("");

	correl->GetXaxis()->SetRangeUser( dEtaMin_plot, dEtaMax_plot);
	correl->GetXaxis()->SetTitle("#Delta #eta");
	correl->GetXaxis()->SetTitleSize(correl2D_xlabelsize);
	correl->GetXaxis()->CenterTitle(1);
	correl->SetTitleOffset(1.6,"X");

	correl->GetYaxis()->CenterTitle(1);
	correl->GetYaxis()->SetTitle("#Delta #phi [rad]");
	correl->GetYaxis()->SetTitleSize(correl2D_ylabelsize);
	correl->SetTitleOffset(1.6,"Y");

	correl->GetZaxis()->CenterTitle(1);
	correl->GetZaxis()->SetTitleSize(correl2D_zlabelsize);
	correl->SetTitleOffset(2.0,"Z");
	correl->GetZaxis()->SetTitle( zaxistitle.c_str() );

	correl->Draw("SURF1 FB");

	TLatex ttitle ( 0.06,0.94, title.c_str() ); 
	ttitle.SetTextSize(correl2D_figuretextsize);
	ttitle.SetNDC(kTRUE);
	ttitle.Draw();

	TLatex tleftlabel ( 0.06,0.8, leftlabel.c_str() ); 
	tleftlabel.SetTextSize(correl2D_figuretextsize);
	tleftlabel.SetNDC(kTRUE);
	tleftlabel.Draw();

	TLatex trightlabel ( 0.75,0.85, rightlabel.c_str() ); 
	trightlabel.SetTextSize(correl2D_figuretextsize);
	trightlabel.SetNDC(kTRUE);
	trightlabel.Draw();

	std::string pdffigure = figurename+".pdf";
	std::string pngfigure = figurename+".png";
	canvas_correl.SaveAs( pdffigure.c_str() );
	canvas_correl.SaveAs( pngfigure.c_str() );

};


//////////////////////////////////////////////////
// plot2DCorrelation_custom
void plot2DCorrelation_custom(TH2D* correl, std::string figurename, std::string title)
{

	gStyle->SetOptStat(0);

	TCanvas canvas_correl ("canvas_correl","",800,600);
	correl->SetTitle( title.c_str() );
	correl->GetXaxis()->SetRangeUser( -2., 2.);
	correl->GetXaxis()->SetTitle("#Delta #eta");
	correl->GetXaxis()->SetTitleOffset(1.3);
	correl->GetYaxis()->SetTitle("#Delta #phi [rad]");
	correl->GetYaxis()->SetTitleOffset(1.3);
	correl->GetYaxis()->SetRangeUser( TMath::Pi()-1.5,TMath::Pi()+1.5);
	correl->Draw("SURF1");
	canvas_correl.SaveAs( figurename.c_str() );

};


TGraphErrors CorrelationFramework::Getv2TGraphError (int TypBin, int multBin)
{
	gStyle->SetOptStat(0);

	double *pt;
	double *v2;
	double *v2_StatError;

	pt       	 = new double[nPtBins[TypBin]];
	v2       	 = new double[nPtBins[TypBin]];
	v2_StatError = new double[nPtBins[TypBin]];

   std::vector< double > ptvec = CorrelationFramework::Getptvec(TypBin, 0.);
   std::vector< double > v2vec = CorrelationFramework::Getv2vec(TypBin, multBin);
   std::vector< double > v2_StatErrorvec = CorrelationFramework::Getv2_StatErrorvec(TypBin, multBin);

	for(int ptBin = 0; ptBin < nPtBins[TypBin]; ptBin++)
	{
		pt[ptBin]           = ptvec[ptBin];
		v2[ptBin]           = v2vec[ptBin];
		v2_StatError[ptBin] = v2_StatErrorvec[ptBin];
	};

	TGraphErrors cparv2 = cpar_v2(nPtBins[0], pt, v2, 0, v2_StatError );

	double v2vspt_ptmin = 0.0;
	double v2vspt_ptmax = 2.5;
	double v2vspt_v2min = 0.0;
	double v2vspt_v2max = 0.16;

	cparv2.SetTitle("");
   cparv2.GetXaxis()->SetLimits(v2vspt_ptmin,v2vspt_ptmax);
	cparv2.GetXaxis()->SetTitle("p_{T} [GeV/c]");                              			  
	cparv2.GetXaxis()->CenterTitle(1);
	cparv2.GetXaxis()->SetTitleOffset(1.2);
	cparv2.GetXaxis()->SetTitleSize(figuretextsize);
	cparv2.GetYaxis()->SetRangeUser(v2vspt_v2min,v2vspt_v2max);
	cparv2.GetYaxis()->SetTitle("v_{2}");
	cparv2.GetYaxis()->CenterTitle(1);
	cparv2.GetYaxis()->SetTitleOffset(1.2);
	cparv2.GetYaxis()->SetTitleSize(figuretextsize);

	return cparv2;

}
