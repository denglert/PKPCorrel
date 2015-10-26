#include "GraphTools.h"

//TGraphStyle TGraphStyle_vnvspt_StatError[] =
//{
//	{21, 1.0, kBlack, kBlack, 0, 0},
//	{22, 1.5,   kRed,   kRed, 0, 0},
//	{29, 2.0, kGreen, kGreen, 0, 0},
//	{20, 1.0,  kBlue,  kBlue, 0, 0}
//};
//
//TGraphStyle TGraphStyle_vnvspt_SystError[] =
//{
//	{21, 0.0, kBlack, kBlack, 2, 0},
//	{22, 0.0,   kRed,   kRed, 2, 0},
//	{29, 0.0, kGreen, kGreen, 2, 0},
//	{20, 0.0,  kBlue,  kBlue, 2, 0}
//};


/////////////////////////////////////////////////////////////////////////
double xpt ( double center, int npts, int ipt, double dx )
{
	double icenter = double(npts-1.)/2.;
	double retxpt = center + (ipt-icenter)*dx;
	return retxpt;

}

//void SetupTGraphStyle ( TGraphErrors* graph, TGraphStyle &gs)
//{
//	graph->SetMarkerStyle( gs.MarkerStyle );
//	graph->SetMarkerSize ( gs.MarkerSize  );
//	graph->SetMarkerColor( gs.MarkerColor );
//	graph->SetLineColor  ( gs.LineColor   );
//	graph->SetLineWidth  ( gs.LineWidth   );
//	graph->SetFillStyle  ( gs.FillStyle   );
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void plotTH2D (TH2D *histo, const char titlelabels[], const char figbasename[], const char drawmode[] )
{

	gStyle->SetOptStat(0);

	TCanvas canvas ("canvas", "", canvas_res_x, canvas_res_y);

	canvas.SetLeftMargin(   canvas_margin_left   );
   canvas.SetBottomMargin( canvas_margin_bottom );
   canvas.SetRightMargin(  canvas_margin_right  );
   canvas.SetTopMargin(    canvas_margin_top    );

	histo->SetTitle( titlelabels );

	histo->GetXaxis()->SetTitleSize( xtitle_size );
	histo->GetYaxis()->SetTitleSize( ytitle_size );

	histo->GetXaxis()->SetTitleOffset( xtitle_offset );
	histo->GetYaxis()->SetTitleOffset( ytitle_offset );

	std::string outPNG = Form("%s.png", figbasename);
	std::string outPDF = Form("%s.pdf", figbasename);

	if ( ! (strcmp( drawmode, "-1") == 0 ) )
	{

	histo->Draw( drawmode );
 	canvas.SaveAs( outPNG.c_str() );
	canvas.SaveAs( outPDF.c_str() ); 

	}


}


