#ifndef GRAPHTOOLS_H
#define GRAPHTOOLS_H

#include <TH1D.h>
#include <TH2D.h>
#include <TLatex.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <string.h>

//struct TGraphStyle
//{
//	int MarkerStyle;
//	double MarkerSize;
//	int MarkerColor;
//	int LineColor;
//	int LineWidth;
//	int FillStyle;
//};

//extern struct TGraphStyle TGraphStyle_vnvspt_StatError[];
//extern struct TGraphStyle TGraphStyle_vnvspt_SystError[];

//void SetupTGraphStyle ( TGraphErrors* graph, TGraphStyle gs );

// TGraphError_vnvspt styles
//const int    TGraphErrors_vnvspt_MarkerStyle[4] = {21, 22, 29, 20}; 
//const double TGraphErrors_vnvspt_MarkerSize [4] = {1, 1.5, 2, 1}; 
//const int    TGraphErrors_vnvspt_MarkerColor[4] = {kBlack, kRed, kGreen, kBlue}; 
//const int    TGraphErrors_vnvspt_LineColor  [4] = {kBlack, kRed, kGreen, kBlue}; 
//const int    TGraphErrors_vnvspt_SystErr_FillStyle[4] = {0, 0, 0, 0}; 
//const double TGraphErrors_vnvspt_SystErr_MarkerSize[4] = {0, 0, 0, 0}; 
//const int    TGraphErrors_vnvspt_SystErr_LineColor [4] = {kBlack, kRed, kGreen, kBlue}; 
//const int    TGraphErrors_vnvspt_SystErr_LineWidth [4] = {2, 2, 2, 2}; 

// correl2D graphs
const double correl2D_leftmargin   = 0.20;
const double correl2D_rightmargin  = 0.04;
const double correl2D_topmargin    = 0.1;
const double correl2D_bottommargin = 0.05;

const double correl2D_xlabelsize = 0.05;
const double correl2D_ylabelsize = 0.05;
const double correl2D_zlabelsize = 0.05;
const double correl2D_figuretextsize = 0.039;

// correl1D graphs
const double correl1D_leftmargin   = 0.20;
const double correl1D_rightmargin  = 0.01;
const double correl1D_topmargin    = 0.01;
const double correl1D_bottommargin = 0.15;
const double correl1D_xlabelsize = 0.05;
const double correl1D_ylabelsize = 0.05;
const double correl1D_zlabelsize = 0.05;
const double correl1D_legendtextsize = 0.039;
const double correl1D_figuretextsize = 0.042;

const double correl1D_xl1                = 0.24;
const double correl1D_yl1                = 0.67;
const double correl1D_label_CMS_pPb_posx = 0.24;
const double correl1D_label_CMS_pPb_posy = 0.89;
const double correl1D_label_corrtyp_posx = 0.65;
const double correl1D_label_corrtyp_posy = 0.87;
const double correl1D_label_bin_posx     = 0.42;
const double correl1D_label_bin_posy     = 0.69;
const double correl1D_upperleftposx = 0.69;
const double correl1D_upperleftposy = 0.34;
const double correl1D_shift = 0.04;

// v2vspt graphs
const double v2vspt_xlabelsize = 0.05;
const double v2vspt_ylabelsize = 0.05;
const double v2vspt_zlabelsize = 0.05;
const double v2vspt_legendtextsize = 0.042;
const double v2vspt_figuretextsize = 0.042;

// zvtxdistr graph
const double zvtxdistr_xlabelsize = 0.10;
const double zvtxdistr_ylabelsize = 0.10;
const double zvtxdistr_figuretextsize = 0.10;

// trackcorrection graph
const double trkcorr2D_xlabelsize = 0.15;
const double trkcorr2D_ylabelsize = 0.15;
const double trkcorr2D_zlabelsize = 0.15;
const double trkcorr2D_figuretextsize = 0.10;

// PtResolution graphs

const double RelDiffPt_leftmargin   = 0.20;
const double RelDiffPt_rightmargin  = 0.04;
const double RelDiffPt_topmargin    = 0.05;
const double RelDiffPt_bottommargin = 0.20;
                      
const double RelDiffPt_xlabelsize = 0.030;
const double RelDiffPt_ylabelsize = 0.030;
                       
const double RelDiffPt_xlabeloffset = 2.3;
const double RelDiffPt_ylabeloffset = 1.8;
                       
const double RelDiffPt_tres_upperleftposx = 0.75;
const double RelDiffPt_tres_upperleftposy = 0.40;

const double RelDiffPt_ttype_upperleftposx = 0.25;
const double RelDiffPt_ttype_upperleftposy = 0.80;

const double RelDiffPt_figuretextsize = 0.030;

// PtRecSimMatrix
const double PtRecSimMatrix_leftmargin   = 0.10;
const double PtRecSimMatrix_rightmargin  = 0.15;
const double PtRecSimMatrix_topmargin    = 0.05;
const double PtRecSimMatrix_bottommargin = 0.10;

const double PtRecSimMatrix_xlabelsize = 0.03;
const double PtRecSimMatrix_ylabelsize = 0.03;

const double PtRecSimMatrix_xlabeloffset = 1.2;
const double PtRecSimMatrix_ylabeloffset = 1.2;

const double PtRecSimMatrix_tres_upperleftposx = 0.75;
const double PtRecSimMatrix_tres_upperleftposy = 0.40;

const double PtRecSimMatrix_ttype_upperleftposx = 0.25;
const double PtRecSimMatrix_ttype_upperleftposy = 0.80;

const double PtRecSimMatrix_figuretextsize = 0.030;

// Graph variables
const double figuretextsize = 0.043;

const int canvas_res_x = 800;
const int canvas_res_y = 600;

const double canvas_margin_left   = 0.1;
const double canvas_margin_right  = 0.15;
const double canvas_margin_bottom = 0.12;
const double canvas_margin_top    = 0.05;

const double xtitle_offset = 1.3;
const double ytitle_offset = 1.1;

const double xtitle_size = 0.043;
const double ytitle_size = 0.043;

const double xpoint_pt_dx = 0.005;

// Graph Functions
double xpt ( double center, int npts, int ipt, double dx = xpoint_pt_dx);

void plotTH2D (TH2D *histo, const char titlelabels[], const char figbasename[], const char drawmode[] );

#endif
