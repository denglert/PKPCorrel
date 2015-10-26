void SetupHisto( TH1D *histo )
{
	histo->Sumw2();
	histo->SetMinimum(0);
	histo->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	histo->GetXaxis()->SetTitleOffset(1.3);
	histo->GetYaxis()->SetTitleOffset(1.5);
	histo->GetYaxis()->SetTitle("Entries");
	histo->SetTitle("");
}

void plot()
{
	// filename
	//std::string filename = "./HiForest/HiForest_DmesonAna_5_1_Yx5.root";
	//	std::string filename = "./HiForest/HiForestDmeson_PbPbdata_test.root";
	gStyle->SetOptStat(0);
	std::string filename = "./MCinfo_HIJING.root";
	
	TFile *f = NULL;
	std::cerr << Form("f: %d", f) << std::endl;
	f = new TFile (filename.c_str(), "READ");
	std::cerr << Form("f: %d", f) << std::endl;

	// list contents
	f->ls();
	// TBrowser *brow = new TBrowser;

	// directory
	// std::string dirname = "HFtree";
	// TDirectory *dir = (TDirectory*)f->Get(dirname.c_str());
	// dir->ls();

	// TTree
	// std::string treename = "HFtree/hftree";
	// TTree *tree = (TTree*)f->Get(treename.c_str());

	// tree->GetListOfBranches()->Print();

	// Draw variables
	TCanvas canvas ("canvas", "canvas;;", 1024, 768);

	TH1D *nProtonsRECO = (TH1D*)f->Get("nProtonsRECO");
	TH1D *nProtonsGENE = (TH1D*)f->Get("nProtonsGENE");
	TH1D *nLambda2ProtonTP  = (TH1D*)f->Get("nLambda2ProtonTP");
	TH1D *nLambda2ProtonGM  = (TH1D*)f->Get("nLambda2ProtonGM");
	TH1D *MotherPIdDistrGM  = (TH1D*)f->Get("MotherPIdDistrGM");
	TH1D *MotherPIdDistrM   = (TH1D*)f->Get("MotherPIdDistrM");
	TH1D *trkStatusDistr    = (TH1D*)f->Get("trkStatusDistr");
	TH1D *negtrkStatusPtDistr = (TH1D*)f->Get("negtrkStatusPtDistr");

	SetupHisto( nProtonsRECO );
	SetupHisto( nProtonsGENE );
	SetupHisto( nLambda2ProtonGM );
	SetupHisto( nLambda2ProtonTP );
	SetupHisto( negtrkStatusPtDistr );

	nProtonsRECO->Draw("");
	canvas.SaveAs("./figures/nProtonsRECO.pdf");
	canvas.Clear();

	nProtonsGENE->Draw("");
	canvas.SaveAs("./figures/nProtonsGENE.pdf");
	canvas.Clear();

	nLambda2ProtonTP->Draw("");
	canvas.SaveAs("./figures/nLambda2ProtonTP.pdf");
	canvas.Clear();

	nLambda2ProtonGM->Draw("");
	canvas.SaveAs("./figures/nLambda2ProtonGM.pdf");
	canvas.Clear();

	MotherPIdDistrGM->Draw("");
	canvas.SaveAs("./figures/MotherPIdDistrGM.pdf");
	canvas.Clear();

	MotherPIdDistrM->Draw("");
	canvas.SaveAs("./figures/MotherPIdDistrM.pdf");
	canvas.Clear();

	trkStatusDistr->Draw("");
	canvas.SaveAs("./figures/trkStatusDistr.pdf");
	canvas.Clear();

	negtrkStatusPtDistr->Draw("");
	canvas.SaveAs("./figures/negtrkStatusPtDistr.pdf");
	canvas.Clear();

	TH1D *LambdaFeedDownRatio = (TH1D*)nLambda2ProtonTP->Clone("LambdaFeedDownRatio");
	LambdaFeedDownRatio->Divide( nProtonsRECO );
	LambdaFeedDownRatio->Scale( 100 );
	LambdaFeedDownRatio->GetYaxis()->SetTitle("#Lambda #rightarrow p feeddown ratio [%]");

	LambdaFeedDownRatio->Draw("E0");
	canvas.SaveAs("./figures/lambdafeeddownratio.pdf");
	canvas.Clear();

}
