#ifndef GRAPHSTYLES_H
#define GRAPHSTYLES_H

#include "TGraphErrors.h"

const double figuretextsize = 0.043;

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
#endif
