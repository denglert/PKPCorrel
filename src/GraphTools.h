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

// 0.032

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
