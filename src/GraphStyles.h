#ifndef GRAPHSTYLES_H
#define GRAPHSTYLES_H

#include "TGraphErrors.h"
#include "TLatex.h"
#include "AnalysisFW.h"
#include "AnalysisBinning.h"

const double figuretextsize = 0.043;
const double figuretextsize_correl1D = 0.035;
const int fillstyle = 3009;

///////////////////////////////
// cpar_v2
TGraphErrors cpar_v2 (int npoint, double *pt, double *v2, double *pt_Error, double *v2_Error )
{ 
	TGraphErrors graph (npoint, pt, v2, pt_Error, v2_Error);
	graph.SetLineColor(kBlack);
	graph.SetMarkerColor(kBlack);
	// full circle
	graph.SetMarkerStyle(21);
	graph.SetMarkerSize(1);
	return graph;
};

TGraphErrors cpar_v2_syst (int npoint, double *pt, double *v2, double *pt_Error, double *v2_Error )
{ 
	TGraphErrors graph (npoint, pt, v2, pt_Error, v2_Error);
	graph.SetFillStyle(0);
	graph.SetMarkerSize(0);
	graph.SetLineColor(16);
	graph.SetLineWidth(2);
	return graph;
};

//////////////////////////////////
// pion_v2
TGraphErrors pion_v2 (int npoint, double *pt, double *v2, double *pt_Error, double *v2_Error )
{
	// pion
	TGraphErrors graph(npoint, pt, v2, pt_Error, v2_Error);
	graph.SetLineColor(kRed);
	graph.SetMarkerColor(kRed);
	// full square
	graph.SetMarkerStyle(22);
	graph.SetMarkerSize(1.5);
	return graph;
};

TGraphErrors pion_v2_syst (int npoint, double *pt, double *v2, double *pt_Error, double *v2_Error )
{ 
	TGraphErrors graph (npoint, pt, v2, pt_Error, v2_Error);
	graph.SetFillStyle(0);
	graph.SetMarkerSize(0);
	graph.SetLineColor(46);
	graph.SetLineWidth(2);
	return graph;
};

//////////////////////////////////
// kaon_v2
TGraphErrors kaon_v2 (int npoint, double *pt, double *v2, double *pt_Error, double *v2_Error )
{
	// kaon
	TGraphErrors graph (npoint, pt, v2, pt_Error, v2_Error);
	graph.SetLineColor(kGreen);
	graph.SetMarkerColor(kGreen);
	graph.SetMarkerStyle(29);
	graph.SetMarkerSize(2);
	return graph;
};

TGraphErrors kaon_v2_syst (int npoint, double *pt, double *v2, double *pt_Error, double *v2_Error )
{ 
	TGraphErrors graph (npoint, pt, v2, pt_Error, v2_Error);
	graph.SetFillStyle(0);
	graph.SetMarkerSize(0);
	graph.SetLineColor(8);
	graph.SetLineWidth(2);
	return graph;
};

//////////////////////////////////
// prot_v2
TGraphErrors prot_v2 (int npoint, double *pt, double *v2, double *pt_Error, double *v2_Error )
{
	// prot
	TGraphErrors graph (npoint, pt, v2, pt_Error, v2_Error);
	graph.SetLineColor(kBlue);
	graph.SetMarkerColor(kBlue);
	graph.SetMarkerStyle(20);
	graph.SetMarkerSize(1);
	return graph;
};

TGraphErrors prot_v2_syst (int npoint, double *pt, double *v2, double *pt_Error, double *v2_Error )
{ 
	TGraphErrors graph (npoint, pt, v2, pt_Error, v2_Error);
	graph.SetFillStyle(0);
	graph.SetMarkerSize(0);
	graph.SetLineColor(38);
	graph.SetLineWidth(2);
	return graph;
};


///////////////////////////////
// cpar_self_v2
TGraphErrors cpar_self_v2 (int npoint, double *pt, double *v2, double *pt_Error, double *v2_Error )
{ 
	TGraphErrors graph (npoint, pt, v2, pt_Error, v2_Error);
	graph.SetLineColor(kBlack);
	graph.SetMarkerColor(kBlack);
	graph.SetMarkerStyle(24);
	return graph;
};

//////////////////////////////////
// pion_self_v2
TGraphErrors pion_self_v2 (int npoint, double *pt, double *v2, double *pt_Error, double *v2_Error )
{
	// pion
	TGraphErrors graph (npoint, pt, v2, pt_Error, v2_Error);
	graph.SetLineColor(kRed);
	graph.SetMarkerColor(kRed);
	graph.SetMarkerStyle(25);
	return graph;
};

//////////////////////////////////
// kaon_self_v2
TGraphErrors kaon_self_v2 (int npoint, double *pt, double *v2, double *pt_Error, double *v2_Error )
{
	// kaon
	TGraphErrors graph (npoint, pt, v2, pt_Error, v2_Error);
	graph.SetLineColor(kGreen);
	graph.SetMarkerColor(kGreen);
	graph.SetMarkerStyle(25);
	return graph;
};

//////////////////////////////////
// prot_self_v2
TGraphErrors prot_self_v2 (int npoint, double *pt, double *v2, double *pt_Error, double *v2_Error )
{
	// prot
	TGraphErrors graph (npoint, pt, v2, pt_Error, v2_Error);
	graph.SetLineColor(kBlue);
	graph.SetMarkerColor(kBlue);
	graph.SetMarkerStyle(25);
	return graph;
}

///////////////////////
// label_CMS_pPb
TLatex label_CMS_pPb(double posx, double posy, double figuretextsize)
{
	std::string CMSsystemlabel = "#splitline{CMS Preliminary pPb}{#sqrt{s_{NN}} = 5.02 TeV L_{int} = 35 nb^{-1}}";

	TLatex tCMSsystemlabel( posx, posy, CMSsystemlabel.c_str()); 
	tCMSsystemlabel.SetTextSize(figuretextsize);
	tCMSsystemlabel.SetNDC(kTRUE);

	return tCMSsystemlabel;
}

///////////////////////
// label_Ntrk_pt
TLatex label_Ntrk_pt(double posx, double posy, double figuretextsize, int TypBin, int multBin, int ptBin)
{

	double pt1 = pt(TypBin, ptBin, 0);
	double pt2 = pt(TypBin, ptBin, 1);
	int mult1 = multiplicity_Ana(multBin, 0, nMultiplicityBins_Ana_HDR);
	int mult2 = multiplicity_Ana(multBin, 1, nMultiplicityBins_Ana_HDR);

	std::string binlabel  = Form("#splitline{#splitline{  %d #leq N_{trk}^{offline} #leq %d}{ %.1f < p_{T}^{trig}  < %.1f GeV/c}}{ %.1f < p_{T}^{assoc} < %.1f GeV/c}", mult1, mult2, pt1, pt2, ptref1, ptref2);

	TLatex tlabel( posx, posy, binlabel.c_str()); 
	tlabel.SetTextSize(figuretextsize);
	tlabel.SetNDC(kTRUE);

	return tlabel;
}

///////////////////////
// label_CorrTyp
TLatex label_CorrTyp(double posx, double posy, double figuretextsize, int TypBin)
{

	std::string rightlabel = Form("%s - charged", particletype(TypBin).c_str());

	std::string binlabel = Form("%s - charged", particletype(TypBin).c_str());

	TLatex tlabel( posx, posy, binlabel.c_str()); 
	tlabel.SetTextSize(figuretextsize);
	tlabel.SetNDC(kTRUE);

	return tlabel;
}


#endif
