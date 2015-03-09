#include <TMath.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <TFile.h>
#include "AnalysisFW.h"
#include "AnalysisBinning.h"
#include "PIDUtils.h"
#include "SetupCustomTrackTree.h"

const int nMixEv = 10;

const double normalizationRegionMassMin = 1.0400;
const double normalizationRegionMassMax = 1.0495;

/////////////////////////////
// *** EventData class *** //
/////////////////////////////
void EventData::AddTrack(const track& p) { tracks.push_back(p); }
int  EventData::GetnTracks () { return tracks.size(); }

void EventData::SetzVtx(float zVtx_) { zVtx = zVtx_; }
void EventData::SetnTrk(int nTrk_) { nTrk  = nTrk_; }

int EventData::GetzVtxBin()         { return zvtxbin(zVtx, nZvtxBins_); }
int EventData::GetMultiplicityBin_Ana( int nMultiplicityBins_Ana) { int bin = multiplicitybin_Ana(nTrk, nMultiplicityBins_Ana); return bin;}
int EventData::GetMultiplicityBin_EvM() { return multiplicitybin_EvM(nTrk); }

LogFile::LogFile(const char filename[])
{ ofs.open( filename ); }

void LogFile::wr( const char str[])
{
	      ofs << str << std::endl;
	std::cout << str << std::endl;
}

void LogFile::EventCounter( int iEv)
{
  if ( (iEv % repeat) == 0 )
  { 
	 std::cout << Form("%s Event: %d", label.c_str(), iEv ) << std::endl; 
    ofs       << Form("%s Event: %d", label.c_str(), iEv ) << std::endl;
  }
}

void LogFile::Close()
{
	ofs.close();
}

void EventData::Clear(int nCorrTyp, int *nPtBins)
{
	tracks.clear();
	zVtx=50;
	nTrk=-1;

	for(int TypBin=0; TypBin < nCorrTyp; TypBin++)
	for(int ptBin=0; ptBin < nPtBins[TypBin]; ptBin++)
	{
		nTriggerParticles[TypBin][ptBin] = 0; 
	}

	nTriggerParticles_cpar_ref = 0;
}


// Setup_nTriggerParticles
void EventData::Setup_nTriggerParticles(int nCorrTyp, int *nPtBins)
{
	nTriggerParticles = new int*[nCorrTyp];

	for( int TypBin=0; TypBin < nCorrTyp; TypBin++)
	{
		 nTriggerParticles[TypBin] = new int[nPtBins[TypBin]];
		 for(int ptBin=0; ptBin < nPtBins[TypBin]; ptBin++)
		{
			nTriggerParticles[TypBin][ptBin] = 0;
		}
	
	}
	
	nTriggerParticles_cpar_ref = 0;

}


// EventSelection()
bool EventSelection( const int &pPAcollisionEventSelection, const int &pileUpBit )
{

	if ( pPAcollisionEventSelection != 1 ) {return false;}
	if ( pileUpBit != 1 ) {return false;}

	return true;
}

double trackWeight (TH3D **trackCorr, int PID, double pt, double eta, double phi, bool doTable)
{		
	if( doTable )
	{ 

		if( (PID == 0))
		{ 
			double value = trackCorr[0]->GetBinContent(trackCorr[0]->FindBin(pt,eta,phi));
			if (value == 0) {return 1;}
			else {return value;}
		}
		else if( (PID != 99) )
		 {
			double value = trackCorr[PID]->GetBinContent(trackCorr[PID]->FindBin(pt,eta,phi));
			if (value == 0) {return 1;}
		 	else {return value;}
		 }
	}	
	else
	{return 1;}
}

// TrackSelection()
bool TrackSelection( const Tracks &tTracks, int iTrk )
{
	// *** Track selection *** //
	if ( tTracks.highPurity[iTrk] == false ) {return false;}
	if ( 2.4 < abs(tTracks.trkEta[iTrk]) ) {return false;}

	float z_sep_significance  = tTracks.trkDz1 [iTrk] / tTracks.trkDzError1  [iTrk];
	if ( 3   < abs(z_sep_significance)   ) {return false;}

	float impact_significance = tTracks.trkDxy1[iTrk] / tTracks.trkDxyError1 [iTrk];
	if ( 3   < abs(impact_significance)  ) {return false;}

	float pt_rel_uncertainty  = tTracks.trkPtError[iTrk] / tTracks.trkPt     [iTrk];
	if ( 0.1 < abs(pt_rel_uncertainty)   ) {return false;}

	return true;
}

// TrackSelection()
bool TrackSelection_c( const Tracks_c &tTracks, int iTrk )
{
	// *** Track selection *** //
	if ( tTracks.highPurity[iTrk] == false ) {return false;}
	if ( 2.4 < abs(tTracks.trkEta[iTrk]) ) {return false;}

	float z_sep_significance  = tTracks.trkDz1 [iTrk] / tTracks.trkDzError1  [iTrk];
	if ( 3   < abs(z_sep_significance)   ) {return false;}

	float impact_significance = tTracks.trkDxy1[iTrk] / tTracks.trkDxyError1 [iTrk];
	if ( 3   < abs(impact_significance)  ) {return false;}

	float pt_rel_uncertainty  = tTracks.trkPtError[iTrk] / tTracks.trkPt     [iTrk];
	if ( 0.1 < abs(pt_rel_uncertainty)   ) {return false;}

	return true;
}

// mTrackSelection_c()
bool mTrackSelection_c( const Tracks_c &tTracks, int iTrk )
{
	// *** Track selection *** //
	if ( tTracks.mtrkQual[iTrk] == false ) {return false;}
	
	if ( 2.4 < abs(tTracks.pEta[iTrk]) ) {return false;}

	float z_sep_significance  = tTracks.mtrkDz1 [iTrk] / tTracks.mtrkDzError1  [iTrk];
	if ( 3   < abs(z_sep_significance)   ) {return false;}

	float impact_significance = tTracks.mtrkDxy1[iTrk] / tTracks.mtrkDxyError1 [iTrk];
	if ( 3   < abs(impact_significance)  ) {return false;}

	float pt_rel_uncertainty  = tTracks.mtrkPtError[iTrk] / tTracks.mtrkPt     [iTrk];
	if ( 0.1 < abs(pt_rel_uncertainty)   ) {return false;}

	return true;
}


// ReadInDATA
void EventData::ReadInDATA( Tracks &tTracks, TH2D *dEdxvsP, PIDUtil *pidutil)
{
	int nTrk = tTracks.nTrk;

	for (int iTrk = 0; iTrk < nTrk; iTrk++)
	{

  		float p = tTracks.trkPt[iTrk] * cosh(tTracks.trkEta[iTrk]);


		// *** Track selection *** //
		if ( !TrackSelection(tTracks, iTrk ) ) continue;

		int PID = pidutil->GetID(p, tTracks.dedx[iTrk], tTracks.trkEta[iTrk]);

		int ptBin_CH = ptbin(   0 , tTracks.trkPt[iTrk]);
		int ptBin_ID = ptbin( PID , tTracks.trkPt[iTrk]);

		bool isOutsideReferencePartPtRange = ( ( tTracks.trkPt[iTrk] < ptref1 ) || ( ptref2 < tTracks.trkPt[iTrk] ) );
		bool isOutsideIdentifHadronPtRange = ( ptBin_ID == -1);
		bool isOutsideChargedHadronPtRange = ( ptBin_CH == -1);

		if ( isOutsideReferencePartPtRange && isOutsideChargedHadronPtRange && isOutsideIdentifHadronPtRange ) continue;
		// *** Track selection *** //
		
		dEdxvsP->Fill( p, tTracks.dedx[iTrk] );

  		// Track fill up
  		track trk;
  		trk.charge  = tTracks.trkCharge[iTrk];
  		trk.pid  	= PID;
  		trk.pt      = tTracks.trkPt[iTrk];
  		trk.phi     = tTracks.trkPhi[iTrk];
  		trk.eta     = tTracks.trkEta[iTrk];

		EventData::AddTrack(trk);

		// chadron
		if( !isOutsideChargedHadronPtRange )
		{ nTriggerParticles[0][ ptBin_CH ]++; }
 
		// reference
		if ( !isOutsideReferencePartPtRange )
		{ nTriggerParticles_cpar_ref++; }

		// pid particle
		if( (trk.pid != 99) && !isOutsideIdentifHadronPtRange )
		{ nTriggerParticles[ trk.pid ][ ptBin_ID ]++; }

	}

}

// ReadInMC
void EventData::ReadInMC( Tracks &tTracks)
{
	int nPart = tTracks.nParticle;

	for (int iPar = 0; iPar < nPart; iPar++)
	{

  		float p = tTracks.pPt[iPar] * cosh(tTracks.pEta[iPar]);

		int PID = McPID2AnaPID ( tTracks.pPId[iPar], tTracks.pEta[iPar]);
		int ptBin_CH = ptbin(   0 , tTracks.pPt[iPar]);
		int ptBin_ID = ptbin( PID , tTracks.pPt[iPar]);

		bool isOutsideReferencePartPtRange = ( ( tTracks.pPt[iPar] < ptref1 ) || ( ptref2 < tTracks.pPt[iPar] ) );
		bool isOutsideIdentifHadronPtRange = ( ptBin_ID == -1);
		bool isOutsideChargedHadronPtRange = ( ptBin_CH == -1);

		if ( isOutsideReferencePartPtRange && isOutsideChargedHadronPtRange && isOutsideIdentifHadronPtRange ) continue;
		// *** Track selection *** //
		
  		// Track fill up
  		track part;
  		part.charge  = 0;
  		part.pid  	 = PID;
  		part.pt      = tTracks.pPt[iPar];
  		part.phi     = tTracks.pPhi[iPar];
  		part.eta     = tTracks.pEta[iPar];

		EventData::AddTrack(part);

		// chadron
		if( !isOutsideChargedHadronPtRange )
		{ nTriggerParticles[0][ ptBin_CH ]++; }
 
		// reference
		if ( !isOutsideReferencePartPtRange )
		{ nTriggerParticles_cpar_ref++; }

		// pid particle
		if( (part.pid != 99) && !isOutsideIdentifHadronPtRange )
		{ nTriggerParticles[ part.pid ][ ptBin_ID ]++; }

	}

}

////////////////////////////
// *** Setup function *** //
////////////////////////////

void Setup_nEvents_Processed(TH1D *&nEvents_Processed_signal_total, TH1D *&nEvents_Processed_backgr_total, TH1D **&nEvents_Processed_signal, TH1D **&nEvents_Processed_backgr, int nMultiplicityBins )
{

 int multtot1 = multiplicity_Ana(0, 0, 1);
 int multtot2 = multiplicity_Ana(0, 1, 1);

 nEvents_Processed_signal_total = new TH1D( Form("nEvents_Processed_signal_total_nTrk_%3d-%3d", 
				  multtot1, multtot2), Form("Processed Events - signal, nTrk [%d - %d];", multtot1, multtot2), 2, -0.5, 1.5);

 nEvents_Processed_backgr_total = new TH1D( Form("nEvents_Processed_backgr_total_nTrk_%3d-%3d", 
				  multtot1, multtot2), Form("Processed Events - backgr, nTrk [%d - %d];", multtot1, multtot2), 2, -0.5, 1.5);


	nEvents_Processed_signal = new TH1D*[nMultiplicityBins];
	nEvents_Processed_backgr = new TH1D*[nMultiplicityBins];

 for(int multiplicityBin=0; multiplicityBin < nMultiplicityBins; multiplicityBin++)
 { int mult1 = multiplicity_Ana(multiplicityBin, 0, nMultiplicityBins);
	int mult2 = multiplicity_Ana(multiplicityBin, 1, nMultiplicityBins);

	nEvents_Processed_signal[multiplicityBin] = new TH1D( Form("nEvents_Processed_signal_nTrk_%3d-%3d",
																		                                         mult1, mult2),
		                                                      Form("Processed Events - signal, nTrk [%d - %d];",
																		                                        mult1, mult2),
																				                              2, -0.5, 1.5);
	nEvents_Processed_backgr[multiplicityBin] = new TH1D( Form("nEvents_Processed_backgr_nTrk_%3d-%3d",
																		                                         mult1, mult2),
		                                                      Form("Processed Events - backgr, nTrk [%d - %d];",
																		                                        mult1, mult2),
																				                              2, -0.5, 1.5);
 }
	
}


///////////////////////////////
// *** Read In functions *** //
///////////////////////////////

TH3D **Read_TH3D_1Darray(TFile *f, const char histoname[], const int nBins)
{
	TH3D **h3Darr = new TH3D*[nBins];
	
	for ( int Bin = 0; Bin < nBins; Bin++)
	{ h3Darr[Bin] = (TH3D*)f->Get( Form("%s %d", histoname, Bin) ); }

	return h3Darr;
}

TH2D **Read_TH2D_1Darray(TFile *f, const char histoname[], const int nBins)
{
	TH2D **h2Darr = new TH2D*[nBins];
	
	for ( int Bin = 0; Bin < nBins; Bin++)
	{ h2Darr[Bin] = (TH2D*)f->Get( Form("%s %d", histoname, Bin) ); }

	return h2Darr;
}

TH1D **Read_TH1D_1Darray(TFile *f, const char histoname[], const int nBins)
{
	TH1D **h1Darr = new TH1D*[nBins];
	
	for ( int Bin = 0; Bin < nBins; Bin++)
	{ h1Darr[Bin] = (TH1D*)f->Get( Form("%s %d", histoname, Bin) ); }

	return h1Darr;
}

void Read_nEvents_Processed(TFile *f, TH1D **&nEvents_Processed_signal, TH1D **&nEvents_Processed_backgr, int nMultiplicityBins )
{

	nEvents_Processed_signal = new TH1D*[nMultiplicityBins];
	nEvents_Processed_backgr = new TH1D*[nMultiplicityBins];
	
	for(int multiplicityBin=0; multiplicityBin < nMultiplicityBins; multiplicityBin++)
	{
		nEvents_Processed_signal[multiplicityBin] = (TH1D*)f->Get(
		Form("nEvents_Processed_signal_nTrk_%3d-%3d",
		multiplicity_Ana(multiplicityBin, 0, nMultiplicityBins), multiplicity_Ana(multiplicityBin, 1, nMultiplicityBins))
   	);

		nEvents_Processed_backgr[multiplicityBin] = (TH1D*)f->Get(
		Form("nEvents_Processed_backgr_nTrk_%3d-%3d",
		multiplicity_Ana(multiplicityBin, 0, nMultiplicityBins), multiplicity_Ana(multiplicityBin, 1, nMultiplicityBins))
		);
	}
}

AnalysisFW::AnalysisFW()
{
}

void AnalysisFW::Setup()
{
	nEvents_Processed_total = new TH1D("nEvents_Processed_total", "Processed Events;", 2, -0.5, 1.5);
 	nTrk_Distr			 		= new TH1D("nTrkDistr", "Track distribution;Multiplicity", 350, 0, 350);
}

void AnalysisFW::FillnTrk( int nTrk)
{
	nTrk_Distr->Fill(nTrk);
}

void AnalysisFW::CountPassedEvent()
{
	nEvents_Processed_total->Fill(1.);
}

void AnalysisFW::CountProcessedEvent()
{
	nEvents_Processed_total->Fill(0.);
}

/////////////////////////////
// *** Folder handling *** //
/////////////////////////////

void prepareDIR( std::string tag )
{

 std::string dir = "./results/"+tag;
 mkdir( dir.c_str(), 0755 );

 std::string correl2Ddir 	 	 = "./results/"+tag+"/correl2D/";
 std::string correl1Ddir 	 	 = "./results/"+tag+"/correl1D/";
 std::string v2vsptdir 	 	 	 = "./results/"+tag+"/v2/";
 std::string v3vsptdir 	 	 	 = "./results/"+tag+"/v3/";
 std::string fitlogdir 			 = "./results/"+tag+"/fit/";

 mkdir( correl2Ddir.c_str(),  	 0755 );
 mkdir( correl1Ddir.c_str(),  	 0755 );
 mkdir( v2vsptdir.c_str(),    	 0755 );
 mkdir( v3vsptdir.c_str(),    	 0755 );
 mkdir( fitlogdir.c_str(), 0755 );

}


//void plotEtaDistr(TH1D *EtaDistrHisto, std::string path, std::string label)
//{
// TCanvas canvas_etadistr("canvas_etadistr",";#eta;Entries",800,600);
// gStyle->SetOptStat(0);
//
// EtaDistrHisto->GetXaxis()->SetRangeUser(-3,3);
// EtaDistrHisto->GetXaxis()->SetTitle("#eta");
// EtaDistrHisto->GetYaxis()->SetTitle("Entries");
//
// // Label
// double labelpos_x = 0.5;
// double labelpos_y = 0.2;
// TLatex tlabel( labelpos_x, labelpos_y, label.c_str()); 
// tlabel.SetTextSize(0.030);
// tlabel.SetNDC(kTRUE);
//
// EtaDistrHisto->Draw();
// tlabel.Draw("SAME");
//
// std::string pngfigure = path+".png";
// std::string pdffigure = path+".pdf";
// canvas_etadistr.SaveAs( pngfigure.c_str() );
// canvas_etadistr.SaveAs( pdffigure.c_str() );
//}
