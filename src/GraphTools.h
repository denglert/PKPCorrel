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

// Graph variables
const int figuretextsize = 21;

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

// Graph Functions
void plotTH2D (TH2D *histo, const char titlelabels[], const char figbasename[], const char drawmode[] );

#endif
