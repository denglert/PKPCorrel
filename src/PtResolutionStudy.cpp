#include "PtResolutionStudy.h"


//////////////////
// PtRes::PtRes()
PtRes::PtRes()
{
	// Initializing variables
	//nPtBins    = 26;
	nPtBins    = 56;

	PtMin 	  = 0.2;
	//PtMax      = 1.6;
	PtMax      = 3.0;
	PtBinWidth = (PtMax-PtMin)/float(nPtBins);
	nCorrTyp   = 4;

	nPtBins_ = new int[nCorrTyp];
	
	nRelDiffPtBins  = 300;
	RelDiffPtMin = -0.3;
	RelDiffPtMax =  0.3;

	PtRecSimMatrix_nxBins = 100;
	PtRecSimMatrix_xMin   = 0.3;
	PtRecSimMatrix_xMax   = 1.6;

	PtRecSimMatrix_nyBins = 100;
	PtRecSimMatrix_yMin   = 0.3;
	PtRecSimMatrix_yMax   = 1.6;
};

////////////////////////////////
// void PtRes::SetupForProcess()
	void PtRes::SetupForProcess()
{

	RelDiffPt           = new TH1D**[nCorrTyp];
	PtRecSimMatrix = new TH2D*[nCorrTyp];

	for(int CorrTyp = 0; CorrTyp < nCorrTyp; CorrTyp++)
	{

		RelDiffPt[CorrTyp] = new TH1D*[nPtBins];

		PtRecSimMatrix[CorrTyp] = new TH2D(Form("PtRecSimMatrix_CorrTyp[%d]", CorrTyp),";p_{T}^{gen};p_{T}^{reco};",
					PtRecSimMatrix_nxBins, PtRecSimMatrix_xMin, PtRecSimMatrix_xMax, PtRecSimMatrix_nyBins, PtRecSimMatrix_yMin, PtRecSimMatrix_yMax);


		for(int ptBin = 0; ptBin < nPtBins; ptBin++)
		{
			RelDiffPt[CorrTyp][ptBin] = new TH1D(Form("RelDiffPt_CorrTyp[%d]ptBin[%d]", CorrTyp, ptBin),";#frac{p_{T}^{reco}-p_{T}^{gen}}{p_{T}^{gen}};Entries;", nRelDiffPtBins, RelDiffPtMin, RelDiffPtMax);
		}
	}

} 

/////////////////////////////
// void PtRes::SetupForFit()
	void PtRes::SetupForFit()
{

	// If seed is 0, the seed is automatically computed via a TUUID object.
	// In this case the seed is guaranteed to be unique in space and time.
	randgen = new TRandom3(0);

	PtBinCenter = CreateArray2<double> (nCorrTyp, nPtBins);

	RelDiffPt           = new TH1D**[nCorrTyp];
	RelDiffPt_Func      = new TF1**[nCorrTyp];
	PtRecSimMatrix 	  = new TH2D*[nCorrTyp];
	PtResolutionParams  = new TVectorD**[nCorrTyp];

	RelDiffPtSigma = new double*[nCorrTyp];
	RelDiffPtMean  = new double*[nCorrTyp];

	for(int CorrTyp = 0; CorrTyp < nCorrTyp; CorrTyp++)
	{

		RelDiffPt     [CorrTyp] 	 = new TH1D*[nPtBins];
		RelDiffPt_Func[CorrTyp] 	 = new TF1*[nPtBins];
		PtResolutionParams[CorrTyp] = new TVectorD*[nPtBins];

		RelDiffPtSigma[CorrTyp] = new double[nPtBins];
		RelDiffPtMean [CorrTyp] = new double[nPtBins];

		PtRecSimMatrix[CorrTyp] = (TH2D*)f_inp->Get(Form("PtRecSimMatrix_CorrTyp[%d]", CorrTyp));

		for(int ptBin = 0; ptBin < nPtBins; ptBin++)
		{

			float pt1 = PtRes::PtBinLow(  ptBin);
			float pt2 = PtRes::PtBinHigh( ptBin);

			PtBinCenter[CorrTyp][ptBin] = (pt1+pt2)/2.0;
			
			RelDiffPt     [CorrTyp][ptBin] = (TH1D*)f_inp->Get( Form("RelDiffPt_CorrTyp[%d]ptBin[%d]", CorrTyp, ptBin) );
			RelDiffPt_Func[CorrTyp][ptBin] = new TF1 ( Form("RelDiffPt_Func_CorrTyp[%d]ptBin[%d]", CorrTyp, ptBin), "gaus(0)", RelDiffPtMin, RelDiffPtMax );
			PtResolutionParams[CorrTyp][ptBin] = new TVectorD(2);

			RelDiffPtSigma[CorrTyp][ptBin] = 0.0;
			RelDiffPtMean [CorrTyp][ptBin] = 0.0;
		}
	}
}


/////////////////////////////
// void PtRes::SetupForSmearing()
void PtRes::SetupForSmearing()
{

	randgen = new TRandom3(0);

	PtResolutionParams  = new TVectorD**[nCorrTyp];
	RelDiffPtSigma 	  = new double*[nCorrTyp];
	RelDiffPtMean  	  = new double*[nCorrTyp];

	for(int TypBin = 0; TypBin < nCorrTyp; TypBin++)
	{

		PtResolutionParams[TypBin] = new TVectorD*[nPtBins];
		RelDiffPtSigma[TypBin] 	 = new double[nPtBins];
		RelDiffPtMean [TypBin] 	 = new double[nPtBins];

		for(int ptBin = 0; ptBin < nPtBins; ptBin++)
		{

			PtResolutionParams[TypBin][ptBin] = (TVectorD*)f_inp->Get( Form("PtResolutionParams[%d][%d]", TypBin, ptBin) );

			RelDiffPtSigma[TypBin][ptBin] = (*PtResolutionParams[TypBin][ptBin])[0];
			RelDiffPtMean [TypBin][ptBin] = (*PtResolutionParams[TypBin][ptBin])[1];

		}

	}

	f_inp->Close();
		
}


/////////////////////////////
// void PtRes::Fit()
   void PtRes::Fit()
{

	loop2(TypBin, ptBin, nCorrTyp, nPtBins)
	{

		float pt1 = PtRes::PtBinLow(  ptBin);
		float pt2 = PtRes::PtBinHigh( ptBin);

		gStyle->SetOptStat(0);

		double nEntries = RelDiffPt[TypBin][ptBin]->Integral();
		RelDiffPt[TypBin][ptBin]->Scale(1./nEntries);

		RelDiffPt_Func[TypBin][ptBin]->SetParameter(1, 0.0);
		RelDiffPt_Func[TypBin][ptBin]->SetParameter(2, 0.1);
		RelDiffPt[TypBin][ptBin]->Fit( RelDiffPt_Func[TypBin][ptBin] );

		TCanvas canv ("canv",";lel;",1024,768);

		canv.SetLeftMargin  ( RelDiffPt_leftmargin   );
		canv.SetRightMargin ( RelDiffPt_rightmargin  );
		canv.SetTopMargin   ( RelDiffPt_topmargin    );
		canv.SetBottomMargin( RelDiffPt_bottommargin );

		RelDiffPt[TypBin][ptBin]->SetTitle("");
		//RelDiffPt[TypBin][ptBin]->GetXaxis()->CenterTitle(1);
		RelDiffPt[TypBin][ptBin]->GetXaxis()->SetTitleSize( RelDiffPt_xlabelsize );
		RelDiffPt[TypBin][ptBin]->GetXaxis()->SetTitle( "x = #frac{p_{T}^{reco}-p_{T}^{gen}}{p_{T}^{gen}}" );
		RelDiffPt[TypBin][ptBin]->GetYaxis()->SetTitleSize( RelDiffPt_ylabelsize );
		RelDiffPt[TypBin][ptBin]->GetYaxis()->SetTitle( "occurance" );
		RelDiffPt[TypBin][ptBin]->SetTitleOffset( RelDiffPt_xlabeloffset ,"X");
		RelDiffPt[TypBin][ptBin]->SetTitleOffset( RelDiffPt_ylabeloffset ,"Y");
		RelDiffPt[TypBin][ptBin]->GetYaxis()->CenterTitle(1);

		double amp   = abs(RelDiffPt_Func[TypBin][ptBin]->GetParameter(0));
		double x0    = abs(RelDiffPt_Func[TypBin][ptBin]->GetParameter(1));
		double sigma = abs(RelDiffPt_Func[TypBin][ptBin]->GetParameter(2));

		double amp_Err   = abs(RelDiffPt_Func[TypBin][ptBin]->GetParError(0));
		double x0_Err    = abs(RelDiffPt_Func[TypBin][ptBin]->GetParError(1));
		double sigma_Err = abs(RelDiffPt_Func[TypBin][ptBin]->GetParError(2));

		RelDiffPtSigma[TypBin][ptBin] = sigma; 
		RelDiffPtMean [TypBin][ptBin] = x0;

		(*PtResolutionParams[TypBin][ptBin])[0] = sigma;
		(*PtResolutionParams[TypBin][ptBin])[1] = x0;

		TLatex tres( RelDiffPt_tres_upperleftposx, RelDiffPt_tres_upperleftposy , Form("#splitline{#splitline{amp = %.3f #pm %.3f}{x_{0} = %.3f #pm %.3f}}{#sigma = %.3f #pm %.3f}", amp, amp_Err, x0, x0_Err, sigma, sigma_Err) ); 
		tres.SetTextSize( RelDiffPt_figuretextsize );
		tres.SetNDC(kTRUE);

		TLatex ttype( RelDiffPt_ttype_upperleftposx, RelDiffPt_ttype_upperleftposy , Form("#splitline{%s}{p_{T} = [%.2f - %.2f] GeV/c}", particletype(TypBin).c_str(), pt1, pt2 ) ); 
		ttype.SetTextSize( RelDiffPt_figuretextsize );
		ttype.SetNDC(kTRUE);


		RelDiffPt[TypBin][ptBin]->Draw("");
		tres.Draw();
		ttype.Draw();

		std::string dir   = Form("./figures/");
		std::string filePDF = Form("PtRelDiff_%d_pt_%.2f-%.2f.pdf", TypBin, pt1, pt2);
		std::string filePNG = Form("PtRelDiff_%d_pt_%.2f-%.2f.png", TypBin, pt1, pt2);

		std::string figurePNG = dir+filePNG;
		std::string figurePDF = dir+filePDF;

		canv.SaveAs( figurePNG.c_str() );
		canv.SaveAs( figurePDF.c_str() );

		canv.Clear();

	}
}


///////////////////////////////////////////
// void SetupOutFile(const char filename[])
	void PtRes::SetupOutFile( )
{
	f_out = new TFile(Form("./PtResolutions_Params_%s.root", tag.c_str() ),"RECREATE");
	f_out->cd();
}


///////////////////////////////////////////
//	void WriteToFile (const char filename[])
	void PtRes::WriteFitResultsToFile ( )
{
	loop2(TypBin, ptBin, nCorrTyp, nPtBins)
	{
		PtResolutionParams[TypBin][ptBin]->Write( Form("PtResolutionParams[%d][%d]", TypBin, ptBin) );
	}
}


//////////////////////////////
// void PtRes::makeFigPtRecPtSim()
	void PtRes::makeFigPtRecPtSim()
{
	for( int TypBin = 0; TypBin < nCorrTyp; TypBin++)	
	{

		gStyle->SetOptStat(0);

		TCanvas canv ("canv","",1024,768);

		canv.SetLeftMargin  ( PtRecSimMatrix_leftmargin   );
		canv.SetRightMargin ( PtRecSimMatrix_rightmargin  );
		canv.SetTopMargin   ( PtRecSimMatrix_topmargin    );
		canv.SetBottomMargin( PtRecSimMatrix_bottommargin );


		canv.SetLogz();

		PtRecSimMatrix[TypBin]->SetTitle("");
		PtRecSimMatrix[TypBin]->GetXaxis()->CenterTitle(1);
		PtRecSimMatrix[TypBin]->GetYaxis()->CenterTitle(1);
		PtRecSimMatrix[TypBin]->GetXaxis()->SetTitleSize( PtRecSimMatrix_xlabelsize);
		PtRecSimMatrix[TypBin]->GetYaxis()->SetTitleSize( PtRecSimMatrix_ylabelsize);
		PtRecSimMatrix[TypBin]->SetTitleOffset( PtRecSimMatrix_xlabeloffset ,"X");
		PtRecSimMatrix[TypBin]->SetTitleOffset( PtRecSimMatrix_ylabeloffset ,"Y");
		PtRecSimMatrix[TypBin]->GetXaxis()->SetTitle( "p_{T}^{gen} [GeV/c]");
		PtRecSimMatrix[TypBin]->GetYaxis()->SetTitle( "p_{T}^{reco} [GeV/c]" );

		canv.SetBottomMargin( PtRecSimMatrix_bottommargin );

		TLatex ttype( PtRecSimMatrix_ttype_upperleftposx, PtRecSimMatrix_ttype_upperleftposy , Form("#splitline{%s}{}", particletype(TypBin).c_str()) ); 
		ttype.SetTextSize( PtRecSimMatrix_figuretextsize );
		ttype.SetNDC(kTRUE);

		PtRecSimMatrix[TypBin]->Draw("COLZ");
		ttype.Draw();

		std::string dir   = Form("./figures/");
		std::string filePDF = Form("PtRecSimMatrix_%d.pdf", TypBin);
		std::string filePNG = Form("PtRecSimMatrix_%d.png", TypBin);

		std::string figurePNG = dir+filePNG;
		std::string figurePDF = dir+filePDF;

		canv.SaveAs( figurePNG.c_str() );
		canv.SaveAs( figurePDF.c_str() );

		canv.Clear();

	}
}

//////////////////////////////
// void PtRes::makeFigSigmaPtDep()
	void PtRes::makeFigSigmaPtDep()
{

 for( int TypBin = 0; TypBin < nCorrTyp; TypBin++)	
 {

	TCanvas canv ("canv","",1024,768);

	canv.SetLeftMargin  ( PtRecSimMatrix_leftmargin   );
	canv.SetRightMargin ( PtRecSimMatrix_rightmargin  );
	canv.SetTopMargin   ( PtRecSimMatrix_topmargin    );
	canv.SetBottomMargin( PtRecSimMatrix_bottommargin );

	TGraphErrors graph (nPtBins, PtBinCenter[TypBin], RelDiffPtSigma[TypBin], 0, 0);
	graph.SetLineColor(kBlue);
	graph.SetMarkerColor(kBlue);
	graph.SetMarkerStyle(22);
	graph.SetMarkerSize(1.5);
	graph.SetTitle("");

	graph.GetYaxis()->SetRangeUser( 0, 0.1);
	graph.GetXaxis()->SetRangeUser( ptbounds[TypBin][0], ptbounds[TypBin][1]);

	graph.GetXaxis()->SetTitleOffset(1.4);
	graph.GetYaxis()->SetTitleOffset(1.4);
	graph.GetXaxis()->SetTitle("p_{T} [GeV/c]");
	graph.GetYaxis()->SetTitle("#sigma(x)");
	
		TLatex ttype( PtRecSimMatrix_ttype_upperleftposx, PtRecSimMatrix_ttype_upperleftposy , Form("#splitline{}{%s}", particletype(TypBin).c_str()) ); 
		ttype.SetTextSize( 0.040);
		ttype.SetNDC(kTRUE);

		graph.Draw("AP");
		ttype.Draw("SAME");

		std::string dir   = Form("./figures/");
		std::string filePDF = Form("SigmaPtDep_%d.pdf", TypBin);
		std::string filePNG = Form("SigmaPtDep_%d.png", TypBin);

		std::string figurePNG = dir+filePNG;
		std::string figurePDF = dir+filePDF;

		canv.SaveAs( figurePNG.c_str() );
		canv.SaveAs( figurePDF.c_str() );

		canv.Clear();

 	}
}

///////////////////////////////////////////
void PtRes::OpenFile(const char filename[])
{
	 f_inp = new TFile( filename, "READ" );
	 if ( (f_inp == NULL) || (f_inp->IsZombie()) ) {std::cerr << "Error opening file: " << filename << std::endl; exit(-1);}
}

/////////////////////////////
void PtRes::StdPrintBinning()
{
	std::cerr << Form("nPtBins: %d", nPtBins) << std::endl;
	std::cerr << Form("PtMin: %f", PtMin) << std::endl;
	std::cerr << Form("PtMax: %f", PtMax) << std::endl;
	std::cerr << Form("PtBinWidth: %f", PtBinWidth) << std::endl;
	std::cerr << Form("nCorrTyp: %d", nCorrTyp) << std::endl;
	std::cerr << Form("nRelDiffPtBins: %d", nRelDiffPtBins) << std::endl;
	std::cerr << Form("RelDiffPtMin: %f", RelDiffPtMin) << std::endl;
	std::cerr << Form("RelDiffPtMax: %f", RelDiffPtMax) << std::endl;
	std::cerr << Form("PtRecSimMatrix_nxBins: %d", PtRecSimMatrix_nxBins) << std::endl;
	std::cerr << Form("PtRecSimMatrix_xMin: %f", PtRecSimMatrix_xMin) << std::endl;
	std::cerr << Form("PtRecSimMatrix_xMax: %f", PtRecSimMatrix_xMax) << std::endl;
	std::cerr << Form("PtRecSimMatrix_yMin: %f", PtRecSimMatrix_yMin) << std::endl;
	std::cerr << Form("PtRecSimMatrix_yMax: %f", PtRecSimMatrix_yMax) << std::endl;
	std::cerr << Form("PtRecSimMatrix_nyBins: %d", PtRecSimMatrix_nyBins) << std::endl;
};


/////////////////////////////
void PtRes::testRand()
{

	std::cerr << "Generating random distributions." << std::endl;

	
	loop2(TypBin, ptBin, nCorrTyp, nPtBins)
	{

		float pt1 = PtRes::PtBinLow ( ptBin );
		float pt2 = PtRes::PtBinHigh( ptBin );

		//double mean  = RelDiffPtMean [TypBin][ptBin];
		double mean  = 0.0;
		double sigma = RelDiffPtSigma[TypBin][ptBin]; 

		TH1D randHist("","", nRelDiffPtBins, RelDiffPtMin, RelDiffPtMax);

		randHist.SetTitle("");
		randHist.GetXaxis()->SetTitleSize( RelDiffPt_xlabelsize );
		randHist.GetXaxis()->SetTitle( "x = #frac{p_{T}^{reco}-p_{T}^{gen}}{p_{T}^{gen}}" );
		randHist.GetYaxis()->SetTitleSize( RelDiffPt_ylabelsize );
		randHist.GetYaxis()->SetTitle( "occurance" );
		randHist.SetTitleOffset( RelDiffPt_xlabeloffset ,"X");
		randHist.SetTitleOffset( RelDiffPt_ylabeloffset ,"Y");
		randHist.GetYaxis()->CenterTitle(1);

		for( int i=0; i < 1000; i++ )			  
		{
			double rand = PtRes::GetRand(TypBin, ptBin);
			randHist.Fill( rand );
		}

		TCanvas canv ("canv",";lel;",1024,768);

		canv.SetLeftMargin  ( RelDiffPt_leftmargin   );
		canv.SetRightMargin ( RelDiffPt_rightmargin  );
		canv.SetTopMargin   ( RelDiffPt_topmargin    );
		canv.SetBottomMargin( RelDiffPt_bottommargin );

		TLatex tres( RelDiffPt_tres_upperleftposx, RelDiffPt_tres_upperleftposy , Form("#splitline{x_{0} = %.3f}{#sigma = %.3f}", 0.0, sigma) ); 
		tres.SetTextSize( RelDiffPt_figuretextsize );
		tres.SetNDC(kTRUE);

		TLatex ttype( RelDiffPt_ttype_upperleftposx, RelDiffPt_ttype_upperleftposy , Form("#splitline{%s}{p_{T} = [%.2f - %.2f] GeV/c}", particletype(TypBin).c_str(), pt1, pt2 ) ); 
		ttype.SetTextSize( RelDiffPt_figuretextsize );
		ttype.SetNDC(kTRUE);

		randHist.Draw("");
		tres.Draw();
		ttype.Draw();

		std::string dir   = Form("./figures/");
		std::string filePDF = Form("PtRelDiff_Gen_%d_pt_%.2f-%.2f.pdf", TypBin, pt1, pt2);
		std::string filePNG = Form("PtRelDiff_Gen_%d_pt_%.2f-%.2f.png", TypBin, pt1, pt2);

		std::string figurePNG = dir+filePNG;
		std::string figurePDF = dir+filePDF;

		canv.SaveAs( figurePNG.c_str() );
		canv.SaveAs( figurePDF.c_str() );

		canv.Clear();

	}
};

//////////////////////////////////////
double PtRes::GetRand( int TypBin, int ptBin )
{
	return randgen->Gaus( 0.0, RelDiffPtSigma[TypBin][ptBin] );
}

/////////////////////////////
float PtRes::PtBinLow ( int ptBin )
{
	float pt = PtMin + (ptBin)*PtBinWidth ;
	return pt;
};

/////////////////////////////
float PtRes::PtBinHigh( int ptBin )
{

	// Debuggg 
//	std::cerr << "ptBin: " << ptBin << std::endl; // Debuggg 
//	std::cerr << "ptMin: " << PtMin << std::endl; // Debuggg 
//	std::cerr << "PtBinWidth: " << PtBinWidth << std::endl; // Debuggg 
//	std::cerr << "pt: " << pt << ptBin << std::endl; // Debuggg 

	float pt = PtMin + (ptBin+1)*PtBinWidth ;
	return pt;
};

////////////////////////////////////////////////////////
int PtRes::GetPtBin( float pt )
{
	int ptBin = floor( (pt-PtMin)/PtBinWidth );

	if ( (ptBin < 0) || ( nPtBins <= ptBin ) )
	{ ptBin = -999; };

	return ptBin;
};
