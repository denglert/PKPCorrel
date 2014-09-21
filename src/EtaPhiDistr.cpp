#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TNtuple.h>
#include <iostream>
#include <deque>
#include "AnalysisFW.h"
#include "AnalysisBinning.h"
#include "PIDUtils.h"
#include "SetupCustomTrackTree.h"

int main( int argc, const char *argv[] )
{ 

  if(argc != 4)
  {
    std::cerr << "Usage: process <.root file to be preprocessed> <tag> <nEvents>" << std::endl;
	 exit(1);
  }


 TString inpFilename   = argv[1];
 std::string tag		  = argv[2];
 int nEvMax 	  		  = atoi( argv[3] );
 //TString inpFilename = "../";

 // Binning
 int nCorrTyp			  = nCorrTyp_; 
 int *nPtBins = new int[nCorrTyp_];

 for(int TypBin = 0; TypBin < nCorrTyp; TypBin++)
 { nPtBins[TypBin] = nPtBins_[TypBin]; }

 int nMultiplicityBins_Ana = nMultiplicityBins_Ana_HDR;
 int nMultiplicityBins_EvM = nMultiplicityBins_EvM_HDR;
 int nZvtxBins 		      = nZvtxBins_; 

 //////////////////////////////////////
 //                                  //
 // ****** Opening input file ****** //
 //                                  //
 //////////////////////////////////////

 // Open file
 TFile *f = TFile::Open(inpFilename);
 // TFile *f = new TFile(inpFilename, "READ");
 if ( f->IsZombie() ) {std::cerr << "Error opening file: " << inpFilename << std::endl; exit(-1);}
 else {std::cout << "File successfully opened." << std::endl;}

 // trackTree
 TTree *trackTree = (TTree*)f->Get("pptracks/trackTree");
 Tracks tTracks;
 bool doCheck = true;
 setupTrackTree(trackTree, tTracks, doCheck);

 // hiEvtAnalyzer
 TTree *EvtAna= (TTree*)f->Get("hiEvtAnalyzer/HiTree");
 int hiNtracks; EvtAna->SetBranchAddress("hiNtracks", &hiNtracks);
 float vz; EvtAna->SetBranchAddress("vz", &vz);

 // skimanalysis for event selection
 TTree *SkimAna= (TTree*)f->Get("skimanalysis/HltTree");
 int pPAcollisionEventSelection; SkimAna->SetBranchAddress("pPAcollisionEventSelection", &pPAcollisionEventSelection);
 int pileUpBit;                  SkimAna->SetBranchAddress("pVertexFilterCutGplus", &pileUpBit);

 ////////////////////////////////
 //                            //
 // ***** Setting output ***** //
 //                            //
 ////////////////////////////////
 
 TFile *output = new TFile(Form("./EtaPhi_distr_%s.root", tag.c_str() ),"RECREATE");
 output->cd();

 //////////////////////////////
 //                          //
 // ***** Initializing ***** //
 //                          //
 //////////////////////////////
 
 TH1::SetDefaultSumw2( );
 TH2::SetDefaultSumw2( );

 AnalysisFW *AnaFW = new AnalysisFW();
 AnaFW->Setup();

 // dEdxvsp map
 TH2D *dEdxvsplinlintyp[4];
 TH2D *dEdxvsploglogtyp[4];

 double l10 = TMath::Log(10);

 int    npBinslog    = 100;
 int    ndEdxBinslog = 100;
 double pBins[npBinslog+1];
 double dEdxBins[ndEdxBinslog+1];

 double pminlog    = 0.1;
 double pmaxlog    = 2.0;
 double dEdxminlog = 0.1;
 double dEdxmaxlog = 20;

 double pminlin    = 0.1;
 double pmaxlin    = 2.0;
 double dEdxminlin = 0.1;
 double dEdxmaxlin = 20;

 double dplog   = ( TMath::Log(pmaxlog)   -TMath::Log(pminlog)    )/npBinslog/l10;
 double ddEdxlog = ( TMath::Log(dEdxmaxlog)-TMath::Log(dEdxminlog) )/ndEdxBinslog/l10;

 std::cout << "l10: " << l10 << std::endl; 
 std::cout << "dplog: " << dplog << std::endl; 
 std::cout << "ddEdxlog: " << ddEdxlog << std::endl; 


 for (int i=0; i<=npBinslog; i++)
 { pBins[i] = TMath::Exp(l10*(i*dplog + TMath::Log(pminlog)/l10));
   std::cout << "pbins: " << pBins[i] << std::endl;
 }

 for (int i=0; i<=ndEdxBinslog; i++)
 { dEdxBins[i] = TMath::Exp(l10*(i*ddEdxlog+ TMath::Log(dEdxminlog)/l10));
   std::cout << "dEdxBins: " << dEdxBins[i] << std::endl;
 }



 for (int i = 0; i < 4 ; i++)
 {
 dEdxvsplinlintyp[i] = new TH2D (Form("dEdxVsP lin-lin %s", particletype(i).c_str()) ,";p(GeV/c);dE/dx", npBins, pminlin, pmaxlin, ndEdxBins, dEdxminlin, dEdxmaxlin);
 dEdxvsploglogtyp[i] = new TH2D (Form("dEdxVsP log-log %s", particletype(i).c_str()) ,";p(GeV/c);dE/dx", npBinslog, pBins, ndEdxBinslog, dEdxBins);
 }

 TH2D* dEdxvsplinlinall = new TH2D ("dEdxVsP lin-lin " ,";p(GeV/c);dE/dx", npBins, pminlin, pmaxlin, ndEdxBins, dEdxminlin, dEdxmaxlin);
 TH2D* dEdxvsploglogall = new TH2D ("dEdxVsP log-log " ,";p(GeV/c);dE/dx", npBinslog, pBins, ndEdxBinslog, dEdxBins);

 /////////////

 int nParticles = 4;

 int nEtaBins  = 100;
 int nPhiBins  = 100;
 double EtaMin = -2.4;
 double EtaMax =  2.4;
 double PhiMin = -TMath::Pi();
 double PhiMax =  TMath::Pi();

 TH1D ***EtaDistr;
 TH2D ***EtaPhiDistr;

 EtaPhiDistr = new TH2D **[nParticles];
 EtaDistr    = new TH1D **[nParticles];

 for (int pid = 0; pid < nParticles; pid++)
 {
	EtaPhiDistr[pid] = new TH2D*[nPtBins[pid]];
	EtaDistr   [pid] = new TH1D*[nPtBins[pid]];

 	for (int ptBin = 0; ptBin < nPtBins[pid]; ptBin++)
	{ EtaPhiDistr[pid][ptBin]  = new TH2D (Form("EtaPhiDistribution id = %d, pt [%.2f - %.2f]", pid, pt(pid, ptBin, 0), pt(pid, ptBin, 1)),";#eta;#Phi [rad]", nEtaBins, EtaMin, EtaMax, nPhiBins, PhiMin, PhiMax); 
  	     EtaDistr[pid][ptBin]  = new TH1D (Form("EtaDistribution id = %d, pt [%.2f - %.2f]", pid, pt(pid, ptBin, 0), pt(pid, ptBin, 1)),";#eta;Entries", nEtaBins, EtaMin, EtaMax); }
 }

 std::cout << "Initialization completed." << std::endl;

 ///////////////////////////
 //                       //
 // ***** ANALYISIS ***** //
 //                       //
 ///////////////////////////
 
 if (nEvMax == -1) {nEvMax = trackTree->GetEntries();}
 for (int iEvA = 0; iEvA < nEvMax; iEvA++)
 {
	
	// Event counter info
	if ( (iEvA % 1000) == 0 )
	{ std::cout << "Event: " << iEvA << std::endl; }

	// Get current event info
	EvtAna->GetEntry(iEvA);
	SkimAna->GetEntry(iEvA);

	AnaFW->CountProcessedEvent();

	// Event Selection
	if ( !EventSelection( pPAcollisionEventSelection, pileUpBit) ) continue;
	if ( zvtxbin(vz, nZvtxBins) == -1 ) continue;
	if ( multiplicitybin_Ana(hiNtracks, nMultiplicityBins_Ana) == -1) continue;

	AnaFW->CountPassedEvent();

	AnaFW->FillnTrk(hiNtracks);

	// Load in tracks
	trackTree->GetEntry(iEvA);


	int nTrk = tTracks.nTrk;

	for (int iTrk = 0; iTrk < nTrk; iTrk++)
	{

  		float p = tTracks.trkPt[iTrk] * cosh(tTracks.trkEta[iTrk]);

		// *** Track selection *** //
		if ( !TrackSelection(tTracks, iTrk ) ) continue;

		int PID   = GetPID(p, tTracks.dedx[iTrk]);

		int ptBin_ID = ptbin( PID , tTracks.trkPt[iTrk]);
		int ptBin_CH = ptbin(   0 , tTracks.trkPt[iTrk]);

		bool isOutsideIdentifHadronPtRange = ( ptBin_ID == -1);
		bool isOutsideChargedHadronPtRange = ( ptBin_CH == -1);

		double Eta = tTracks.trkEta[iTrk];
		double Phi = tTracks.trkPhi[iTrk];

		// chadron
		if( !isOutsideChargedHadronPtRange )
		{ 
			EtaPhiDistr[0][ptBin_CH]->Fill(Eta,Phi);
		   EtaDistr[0][ptBin_CH]->Fill(Eta);
			dEdxvsplinlintyp[0]->Fill( p, tTracks.dedx[iTrk] );
			dEdxvsploglogtyp[0]->Fill( p, tTracks.dedx[iTrk] );
		}

		// pid particle
		if( (PID != 99) && !isOutsideIdentifHadronPtRange )
		{
			EtaPhiDistr[PID][ptBin_ID]->Fill(Eta,Phi);
		  	EtaDistr[PID][ptBin_ID]->Fill(Eta);
			dEdxvsplinlintyp[PID]->Fill( p, tTracks.dedx[iTrk] );
			dEdxvsploglogtyp[PID]->Fill( p, tTracks.dedx[iTrk] );
		}

		dEdxvsploglogall->Fill( p, tTracks.dedx[iTrk] );
		dEdxvsplinlinall->Fill( p, tTracks.dedx[iTrk] );
		// *** Track selection *** //


	}

 }

 ////////////////////////////
 //                        //
 // **** Plot Figures **** //
 //                        //
 ////////////////////////////

 gStyle->SetOptStat(0);

 // (Eta,Phi) distribution
 for (int pid = 0; pid < nParticles; pid++)
 for (int ptBin = 0; ptBin < nPtBins[pid]; ptBin++)
 {
	TCanvas canvas_EtaPhiDistr ("EtaPhiDistr", ";Eta;Phi", 800, 600);
 	EtaPhiDistr[pid][ptBin]->Draw("COLZ");

 	std::string EtaPhiDistrFigBase = Form("EtaPhiDistr_typ_%d_pt_%.2f-%.2f", pid, pt(pid, ptBin, 0), pid, pt(pid, ptBin, 1));

 	std::string EtaPhiDistrFigPNG = EtaPhiDistrFigBase+".png";
 	std::string EtaPhiDistrFigPDF = EtaPhiDistrFigBase+".pdf";

 	canvas_EtaPhiDistr.SaveAs(EtaPhiDistrFigPNG.c_str() );
 	canvas_EtaPhiDistr.SaveAs(EtaPhiDistrFigPDF.c_str() );
 }

 // Eta distribution
 for (int pid = 0; pid < nParticles; pid++)
 for (int ptBin = 0; ptBin < nPtBins[pid]; ptBin++)
 {
	TCanvas canvas_EtaDistr ("EtaDistr", ";Eta;Phi", 800, 600);
 	EtaDistr[pid][ptBin]->Draw("COLZ");

 	std::string EtaDistrFigBase = Form("EtaDistr_typ_%d_pt_%.2f-%.2f", pid, pt(pid, ptBin, 0), pid, pt(pid, ptBin, 1));

 	std::string EtaDistrFigPNG = EtaDistrFigBase+".png";
 	std::string EtaDistrFigPDF = EtaDistrFigBase+".pdf";

 	canvas_EtaDistr.SaveAs(EtaDistrFigPNG.c_str() );
 	canvas_EtaDistr.SaveAs(EtaDistrFigPDF.c_str() );
 }

 /////////////////
 // dEdx vs p plots
 for (int i = 0; i < 4; i++)
 {
 	TCanvas canvas_dEdxvsplin ("dEdx", ";p [GeV/c];dE/dx", 800, 600);

	//canvas_dEdxvsplin.GetXaxis()->SetRangeUser(0.15,5);
	//canvas_dEdxvsplin.GetYaxis()->SetRangeUser(1,20);

	canvas_dEdxvsplin.SetLogz(1);
	dEdxvsplinlintyp[i]->Draw("COLZ");

 	std::string dEdxvsplinlinFigBase = Form("dEdxvspLin_typ_%d", i);

 	std::string dEdxvspFigPNG = dEdxvsplinlinFigBase+".png";
 	std::string dEdxvspFigPDF = dEdxvsplinlinFigBase+".pdf";

 	canvas_dEdxvsplin.SaveAs(dEdxvspFigPNG.c_str() );
 	canvas_dEdxvsplin.SaveAs(dEdxvspFigPDF.c_str() );
 }

 for (int i = 0; i < 4; i++)
 {
 	TCanvas canvas_dEdxvsplog ("dEdx", ";p [GeV/c];dE/dx", 800, 600);
	canvas_dEdxvsplog.SetLogz(1);
	canvas_dEdxvsplog.SetLogx(1);
	canvas_dEdxvsplog.SetLogy(1);

	dEdxvsploglogtyp[i]->Draw("COLZ");

 	std::string dEdxvsploglogFigBase = Form("dEdxvspLog_typ_%d", i);

 	std::string dEdxvspFigPNG = dEdxvsploglogFigBase+".png";
 	std::string dEdxvspFigPDF = dEdxvsploglogFigBase+".pdf";

 	canvas_dEdxvsplog.SaveAs(dEdxvspFigPNG.c_str() );
 	canvas_dEdxvsplog.SaveAs(dEdxvspFigPDF.c_str() );
 }

 	std::string dEdxvsplinlinallFigBase = "dEdxvspLin_typ_all";
 	std::string dEdxvsploglogallFigBase = "dEdxvspLog_typ_all";
 	std::string dEdxvsplinFigallPNG = dEdxvsplinlinallFigBase+".png";
 	std::string dEdxvsplinFigallPDF = dEdxvsplinlinallFigBase+".pdf";
 	std::string dEdxvsplogFigallPNG = dEdxvsploglogallFigBase+".png";
 	std::string dEdxvsplogFigallPDF = dEdxvsploglogallFigBase+".pdf";

	makedEdxvspFigloglog(dEdxvsploglogall, dEdxvsplogFigallPNG);
	makedEdxvspFigloglog(dEdxvsploglogall, dEdxvsplogFigallPDF);
	makedEdxvspFiglinlin(dEdxvsplinlinall, dEdxvsplinFigallPNG);
	makedEdxvspFiglinlin(dEdxvsplinlinall, dEdxvsplinFigallPDF);


 //////////////////////
 //                  //
 // **** OUTPUT **** //
 //                  //
 //////////////////////
 
 output->Write();
 output->Close();

}
