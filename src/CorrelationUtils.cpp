#include <string>
#include <deque>
#include <sstream>
#include <fstream>
#include <TLatex.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include "AnalysisBinning.h"
#include <TCanvas.h>
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"
#include "CorrelationUtils.h"
#include "AnalysisFW.h"

/////////////////////////////////////////
//                                     //
//  *  class CorrelationFramework  *   //
//                                     //
/////////////////////////////////////////

CorrelationFramework::CorrelationFramework( int nCorrTyp_a, int *nPtBins_a, int nMultiplicityBins_Ana_, int nMultiplicityBins_EvM_)
{

	nCorrTyp 			= nCorrTyp_a;
	nMultiplicityBins_Ana = nMultiplicityBins_Ana_;
	nMultiplicityBins_EvM = nMultiplicityBins_EvM_;

	nPtBins  			= new int[nCorrTyp]; 

	for(int TypBin=0; TypBin < nCorrTyp; TypBin++)
	{ nPtBins[TypBin] = nPtBins_a[TypBin]; }

}


////////////////////////////////
// - SetupForProcess()
void CorrelationFramework::SetupForProcess()
{

	std::cout << "Initializing Correlation Framework." << std::endl;
	std::cout << "Setting up for process." << std::endl;
	std::cout << "Project tag: " << tag << std::endl;

	if ( DoSelfCorrelation )
	{
		Setup_TH2Ds_nCorrnPtnMult( correl2D_self_functi, nCorrTyp, nPtBins, nMultiplicityBins_Ana, "correl2D_self", "functi");
		Setup_TH1Ds_nCorrnPtnMult( correl1D_self, nCorrTyp, nPtBins, nMultiplicityBins_Ana, "correl1D_self", "");
		Setup_CorrelResults_nCorrnPtnMult          (correl_Results_self,      nCorrTyp, nPtBins, nMultiplicityBins_Ana);
		Setup_Correl1DfitResultsData_nCorrnPtnMult (correl1D_FitResults_self, nCorrTyp, nPtBins, nMultiplicityBins_Ana);
	}


	Setup_TH2Ds_nCorrnPtnMult( correl2D_functi, nCorrTyp, nPtBins, nMultiplicityBins_Ana, "correl2D"     , "functi");
	Setup_TH2Ds_nMult( correl2D_cpar_ref_functi, nMultiplicityBins_Ana, "correl2D", "cpar_ref_functi", ptref1, ptref2 );

	Setup_TH1Ds_nCorrnPtnMult( correl1D, nCorrTyp, nPtBins, nMultiplicityBins_Ana, "correl1D", "");
	Setup_TH1Ds_nMult( correl1D_cpar_ref, nMultiplicityBins_Ana, "correl1D", "cpar_ref" );

	Setup_CorrelResults_nCorrnPtnMult          (correl_Results,      nCorrTyp, nPtBins, nMultiplicityBins_Ana);
	Setup_Correl1DfitResultsData_nCorrnPtnMult (correl1D_FitResults, nCorrTyp, nPtBins, nMultiplicityBins_Ana);

	correl_Results_cpar_ref      = new          CorrelResults  [nMultiplicityBins_Ana];
	correl1D_FitResults_cpar_ref = new  Correl1DfitResultsData [nMultiplicityBins_Ana];

	Corr_Results = new TFile( Form("./results/%s/dump.root", tag.c_str() ), "RECREATE" );
 	Corr_Results->cd( );

}


/////////////////////////
// - SetupForPreprocess()
void CorrelationFramework::SetupForPreprocess()
{
	log = new LogFile("correl_log");

	// current event
	Setup_TH2Ds_nCorrnPt( correl2D_currev_signal, nCorrTyp, nPtBins, "correl2D_currev", "signal" );
	Setup_TH2Ds_nCorrnPt( correl2D_currev_backgr, nCorrTyp, nPtBins, "correl2D_currev", "backgr" );


	if ( DoSelfCorrelation )
	{
		Setup_TH2Ds_nCorrnPt( correl2D_self_currev_signal, nCorrTyp, nPtBins, "correl2D_self_currev", "signal" );
		Setup_TH2Ds_nCorrnPt( correl2D_self_currev_backgr, nCorrTyp, nPtBins, "correl2D_self_currev", "backgr" );
		Setup_TH2Ds_nCorrnPtnMult ( correl2D_self_signal, nCorrTyp, nPtBins, nMultiplicityBins_Ana, "correl2D_self", "signal" );
		Setup_TH2Ds_nCorrnPtnMult ( correl2D_self_backgr, nCorrTyp, nPtBins, nMultiplicityBins_Ana, "correl2D_self", "backgr" );
	}

	Setup_correl2D_currev_cpar_ref( correl2D_currev_cpar_ref_signal, "signal", ptref1, ptref2);
	Setup_correl2D_currev_cpar_ref( correl2D_currev_cpar_ref_backgr, "backgr", ptref1, ptref2);

	// all event
	Setup_TH2Ds_nCorrnPtnMult ( correl2D_signal, nCorrTyp, nPtBins, nMultiplicityBins_Ana, "correl2D", "signal" );
	Setup_TH2Ds_nCorrnPtnMult ( correl2D_backgr, nCorrTyp, nPtBins, nMultiplicityBins_Ana, "correl2D", "backgr" );


	Setup_TH2Ds_nMult( correl2D_cpar_ref_signal, nMultiplicityBins_Ana, "correl2D_cpar_ref", "signal", ptref1, ptref2 ); 
	Setup_TH2Ds_nMult( correl2D_cpar_ref_backgr, nMultiplicityBins_Ana, "correl2D_cpar_ref", "backgr", ptref1, ptref2 ); 


	// event counter
	Setup_nEvents_Processed( nEvents_Processed_signal_total, nEvents_Processed_backgr_total,  nEvents_Processed_signal, nEvents_Processed_backgr, nMultiplicityBins_Ana );
}

/////////////////////////////////
// - ReadIn_CorrelationFuncs()
void CorrelationFramework::ReadIn_CorrelationFuncs( TFile *f )
{

	std::cout << "Starting to read in correl2D signal and backgr" << std::endl;
	ReadIn_TH2Ds_nCorrnPtnMult(f, correl2D_signal, nCorrTyp, nPtBins, nMultiplicityBins_Ana, "correl2D", "signal");
	ReadIn_TH2Ds_nCorrnPtnMult(f, correl2D_backgr, nCorrTyp, nPtBins, nMultiplicityBins_Ana, "correl2D", "backgr");

	if ( DoSelfCorrelation )
	{
	std::cout << "Starting to read in correl2D self signal and backgr" << std::endl;
	ReadIn_TH2Ds_nCorrnPtnMult(f, correl2D_self_signal, nCorrTyp, nPtBins, nMultiplicityBins_Ana, "correl2D_self", "signal");
	ReadIn_TH2Ds_nCorrnPtnMult(f, correl2D_self_backgr, nCorrTyp, nPtBins, nMultiplicityBins_Ana, "correl2D_self", "backgr");
	}

	std::cout << "Starting to read in correl2D cpar signal and backgr" << std::endl;
	ReadIn_TH2Ds_nMult(f, correl2D_cpar_ref_signal, nMultiplicityBins_Ana, "correl2D", "cpar_ref_signal", ptref1, ptref2);
	ReadIn_TH2Ds_nMult(f, correl2D_cpar_ref_backgr, nMultiplicityBins_Ana, "correl2D", "cpar_ref_backgr", ptref1, ptref2);

 	Read_nEvents_Processed(f, nEvents_Processed_signal, nEvents_Processed_backgr, nMultiplicityBins_Ana );

}



////////////////////////////////////////////
// Set_dEtacut
void CorrelationFramework::Set_dEtacut(int negdEtaCut1Bin, int negdEtaCut2Bin, int posdEtaCut1Bin, int posdEtaCut2Bin )
{
	dEtacut.negdEtaCut1Bin = negdEtaCut1Bin;	
	dEtacut.negdEtaCut2Bin = negdEtaCut2Bin;	
	dEtacut.posdEtaCut1Bin = posdEtaCut1Bin;	
	dEtacut.posdEtaCut2Bin = posdEtaCut2Bin;	
}

/////////////////////////
// Set_dEtacut()
void CorrelationFramework::Set_dEtacut()
{
	dEtacut.negdEtaCut1Bin = negdEtaCut1Bin_;	
	dEtacut.negdEtaCut2Bin = negdEtaCut2Bin_;	
	dEtacut.posdEtaCut1Bin = posdEtaCut1Bin_;	
	dEtacut.posdEtaCut2Bin = posdEtaCut2Bin_;	
}


///////////////////////
// - trackWeight
double CorrelationFramework::trackWeight(int PID, float pt, float eta, float phi)
{

	if( DoTrackWeight )
	{ 
		if( (PID == 0))
		{ 
			double value = trkCorr[0]->GetBinContent(trkCorr[0]->FindBin(pt,eta,phi));
			return value;
		}
		else if( (PID != 99) )
		 {
			double value = trkCorr[PID]->GetBinContent(trkCorr[PID]->FindBin(pt,eta,phi));
		 	return value;
		 }
	}	
	else
	{ return 1; }
}

//////////////////////////////////////////
// - SignalCorrelation( EventData *ev )
void CorrelationFramework::SignalCorrelation(EventData *ev)
{
	int nTrkA = (*ev).tracks.size();
	for (int iTrkA = 0; iTrkA < nTrkA; iTrkA++)
	{

		double iPID = (*ev).tracks[iTrkA].pid;
		double ipt  = (*ev).tracks[iTrkA].pt;
		double ieta = (*ev).tracks[iTrkA].eta;
		double iphi = (*ev).tracks[iTrkA].phi;

		int ptBin_TriggerCh = ptbin(  0  , ipt );
		int ptBin_TriggerID = ptbin( iPID, ipt );

		bool IsTriggerPIDparticle = ( iPID != 99 );

		bool IsTriggerInsideReferencePtRange =  ( (ptref1 < ipt) && ( ipt < ptref2 ));
		bool IsTriggerInsideChParticlPtRange =  ( ptBin_TriggerCh != -1 );
		bool IsTriggerInsideIDParticlPtRange =  ( ptBin_TriggerID != -1 );
		bool IsTriggertruePID                =  (IsTriggerPIDparticle && IsTriggerInsideIDParticlPtRange);
		

		double iw0 = CorrelationFramework::trackWeight( 0 , ipt, ieta, iphi); 
		double iw;
		if ( IsTriggertruePID )
		{iw  = CorrelationFramework::trackWeight( iPID , ipt, ieta, iphi); }

	for (int jTrkA = 0; jTrkA < nTrkA; jTrkA++)
	{

		if( iTrkA == jTrkA ) continue;

		double jpt  = (*ev).tracks[jTrkA].pt;
		double jeta = (*ev).tracks[jTrkA].eta;
		double jphi = (*ev).tracks[jTrkA].phi;

		bool IsAssociaInsideReferencePtRange =  ( ptref1 < jpt) && ( jpt < ptref2 );

		double  jw0 = CorrelationFramework::trackWeight(    0 , jpt, jeta, jphi); 

		double w0 = iw0 * jw0;
		double w;
		if (IsTriggertruePID)
		{ w  = iw  * jw0; }

		//// Debuggg 
		//std::cerr << "IsTriggertruePID: " << IsTriggertruePID << std::endl;
		//std::cerr << "ieta: " << ieta << std::endl;
		//std::cerr << "ipt: " << ipt << std::endl;
		//std::cerr << "jpt: " << jpt << std::endl;
		//std::cerr << "iw0: " << iw0 << std::endl;
		//std::cerr << "iw : " << iw << std::endl;
		//std::cerr << "jw0 : " << jw0 << std::endl;
		//std::cerr << "w : " << w << std::endl;
		//std::cerr << "w0 : " << w0 << std::endl;

		double dEtaA = dEta( ieta, jeta );
		double dPhiA = dPhi( iphi, jphi );

		// Associated particle pt is in reference range
		if ( IsAssociaInsideReferencePtRange )
		{		  
			// charged particle reference
			if ( IsTriggerInsideReferencePtRange )
			{ correl2D_currev_cpar_ref_signal->Fill(dEtaA, dPhiA, w0); }

			// charged particle
			if ( IsTriggerInsideChParticlPtRange )
			{ correl2D_currev_signal[ 0 ][ ptBin_TriggerCh ]->Fill(dEtaA, dPhiA, w0); }

			// PID particle
			if ( IsTriggertruePID )
			{  correl2D_currev_signal[ (*ev).tracks[iTrkA].pid ][ ptBin_TriggerID ]->Fill(dEtaA, dPhiA, w);};
		}

// Commented out, need to be reviewed if you want to activate this feature
//		if ( DoSelfCorrelation )
//		{
//			double jPID = (*ev).tracks[jTrkA].pid;
//			int ptBin_AssociaID = ptbin( jPID, jpt );
//			bool IsAssociaPIDparticle = ( jPID != 99 );
//			int ptBin_AssociaCh = ptbin(   0 , jpt );
//
//			// self correlation - charged particle
//			if ( IsTriggerInsideChParticlPtRange && ( ptBin_TriggerCh == ptBin_AssociaCh ) )
//			{ correl2D_self_currev_signal[ 0 ][ ptBin_TriggerCh ]->Fill(dEtaA, dPhiA, w); }
//
//			// self correlation - pid particle
//			if ( IsTriggerPIDparticle && IsAssociaPIDparticle && IsTriggerInsideIDParticlPtRange && ( ptBin_TriggerID == ptBin_AssociaID ) )
//			{ correl2D_self_currev_signal[ (*ev).tracks[iTrkA].pid ][ ptBin_TriggerID ]->Fill(dEtaA, dPhiA, w); }
//		}

	}
	}
}

///////////////////////////////////////////////////
// - CorrelationFramework::MixedCorrelation( ... )
void CorrelationFramework::MixedCorrelation( EventData *ev, std::deque< EventData > **&EventCache)
{
	int nTrkA = (*ev).tracks.size();

	int nMixEvs = EventCache[ ev->GetMultiplicityBin_EvM() ][ ev->GetzVtxBin() ].size();

	int multBin = ev->GetMultiplicityBin_EvM();
	int zvtxBin = ev->GetzVtxBin();

	for (int iEvB = 0; iEvB < nMixEvs; iEvB++)
	{ 

		int EvA_ID = ev->EventID;
		int EvB_ID = EventCache[multBin][zvtxBin][iEvB].EventID;

		if ( EvA_ID == EvB_ID  ) {std::cerr << "Warning! Trying to mix same events in making the background function" << std::endl;} 

		nEvents_Processed_backgr_total->Fill(1.);
		nEvents_Processed_backgr[ ev->GetMultiplicityBin_Ana(nMultiplicityBins_Ana) ]->Fill(1.);

		int nTrkB = EventCache[multBin][zvtxBin][iEvB].tracks.size();

		for (int iTrkA = 0; iTrkA < nTrkA; iTrkA++)
		{

		   double iPID = (*ev).tracks[iTrkA].pid;
		   double ipt  = (*ev).tracks[iTrkA].pt;
		   double ieta = (*ev).tracks[iTrkA].eta;
		   double iphi = (*ev).tracks[iTrkA].phi;

			int ptBin_TriggerCh = ptbin(   0 , ipt );
			int ptBin_TriggerID = ptbin( iPID, ipt );

			bool IsTriggerPIDparticle = ( iPID != 99 );

			bool IsTriggerInsideReferencePtRange =  ( ptref1 < ipt) && ( ipt < ptref2 );
			bool IsTriggerInsideChParticlPtRange =  ( ptBin_TriggerCh != -1    );
			bool IsTriggerInsideIDParticlPtRange =  ( ptBin_TriggerID != -1    );

			bool IsTriggertruePID                =  (IsTriggerPIDparticle && IsTriggerInsideIDParticlPtRange);
			
			double iw0 = CorrelationFramework::trackWeight(   0 , ipt, ieta, iphi);
			double iw  = CorrelationFramework::trackWeight( iPID, ipt, ieta, iphi);

		for (int jTrkB = 0; jTrkB < nTrkB; jTrkB++)

		{

		   double jpt  = EventCache[multBin][zvtxBin][iEvB].tracks[jTrkB].pt;
		   double jeta = EventCache[multBin][zvtxBin][iEvB].tracks[jTrkB].eta;
		   double jphi = EventCache[multBin][zvtxBin][iEvB].tracks[jTrkB].phi;
			
			double ptassoc = EventCache[multBin][zvtxBin][iEvB].tracks[jTrkB].pt;

			bool IsAssociaInsideReferencePtRange =  ( ptref1 < jpt ) && ( jpt < ptref2 );

			double dEtaB = dEta( ieta, jeta);
			double dPhiB = dPhi( iphi, jphi);

			double jw0 = CorrelationFramework::trackWeight(   0 , jpt, jeta, jphi);

			double w0 = iw0 * jw0;
			double w;
			if ( IsTriggertruePID )
			{w  = iw  * jw0;}

			// Associated particle pt is in reference range
			if ( IsAssociaInsideReferencePtRange )
			{		  
				// charged particle reference
				if ( IsTriggerInsideReferencePtRange )
				{ correl2D_currev_cpar_ref_backgr->Fill(dEtaB, dPhiB, w0); }

				// charged particle
				if ( IsTriggerInsideChParticlPtRange )
				{ correl2D_currev_backgr[ 0 ][ ptBin_TriggerCh ]->Fill(dEtaB, dPhiB, w0); }

				// PID particle
				if ( IsTriggertruePID )
				{  correl2D_currev_backgr[ (*ev).tracks[iTrkA].pid ][ ptBin_TriggerID ]->Fill(dEtaB, dPhiB, w);};
			}

// Commented out, need to be reviewed if you want to activate this feature
//			if ( DoSelfCorrelation )
//			{
//		   double jPID = EventCache[multBin][zvtxBin][iEvB].tracks[jTrkB].pid;
//			bool IsAssociaPIDparticle = ( jPID != 99 );
//			int ptBin_AssociaID = ptbin( jPID, jpt );
//			int ptBin_AssociaCh = ptbin(    0, jpt );
//
//			// self correlation - charged particle
//			if ( IsTriggerInsideChParticlPtRange && ( ptBin_TriggerCh == ptBin_AssociaCh ) )
//			{ correl2D_self_currev_backgr[ 0 ][ ptBin_TriggerCh ]->Fill(dEtaB, dPhiB, w); }
//
//			// self correlation - pid particle
//			if ( IsTriggerPIDparticle && IsAssociaPIDparticle && IsTriggerInsideIDParticlPtRange && ( ptBin_TriggerID == ptBin_AssociaID ) )
//			{ correl2D_self_currev_backgr[ (*ev).tracks[iTrkA].pid ][ ptBin_TriggerID ]->Fill(dEtaB, dPhiB, w); }
//			}



		}

		}
	}

	EventCache[ ev->GetMultiplicityBin_EvM() ][ ev->GetzVtxBin() ].pop_front();
	EventCache[ ev->GetMultiplicityBin_EvM() ][ ev->GetzVtxBin() ].push_back( (*ev) );

}


//////////////////////////////////////////////////
// - AddCurentEventCorrelation (EventData *ev )
void CorrelationFramework::AddCurrentEventCorrelation( EventData* ev )
{

	int currev_multBin = ev->GetMultiplicityBin_Ana(nMultiplicityBins_Ana);

 	for(int TypBin=0; TypBin < nCorrTyp; TypBin++)
	for(int ptBin=0; ptBin < nPtBins[TypBin]; ptBin++)
	{

//		std::cerr << Form("TypBin: %d ptBin: %d nTrig: %d", TypBin, ptBin, (*ev).nTriggerParticles[TypBin][ptBin]) << std::endl;
//		std::cerr << Form("Entries of correl2D: %f", correl2D_currev_signal[TypBin][ptBin]->GetEntries()) << std::endl;
//		std::cerr << Form("Entries of correl2D/ntrig: %f", double(correl2D_currev_signal[TypBin][ptBin]->GetEntries())/(*ev).nTriggerParticles[TypBin][ptBin]) << std::endl;

		if( (*ev).nTriggerParticles[TypBin][ptBin] == 0 ) continue;
	 	correl2D_signal[TypBin][ptBin][currev_multBin]->Add( correl2D_currev_signal[TypBin][ptBin], 1./double((*ev).nTriggerParticles[TypBin][ptBin]) );
	 	correl2D_backgr[TypBin][ptBin][currev_multBin]->Add( correl2D_currev_backgr[TypBin][ptBin], 1./double((*ev).nTriggerParticles[TypBin][ptBin]) );

		if ( DoSelfCorrelation )
		{
	 	correl2D_self_signal[TypBin][ptBin][currev_multBin]->Add( correl2D_self_currev_signal[TypBin][ptBin], 1./double((*ev).nTriggerParticles[TypBin][ptBin]) );
	 	correl2D_self_backgr[TypBin][ptBin][currev_multBin]->Add( correl2D_self_currev_backgr[TypBin][ptBin], 1./double((*ev).nTriggerParticles[TypBin][ptBin]) );
		}

	}

	if( (*ev).nTriggerParticles_cpar_ref != 0 )
	{
 	correl2D_cpar_ref_signal[currev_multBin]->Add( correl2D_currev_cpar_ref_signal, 1./double((*ev).nTriggerParticles_cpar_ref) );
	correl2D_cpar_ref_backgr[currev_multBin]->Add( correl2D_currev_cpar_ref_backgr, 1./double((*ev).nTriggerParticles_cpar_ref) );
	}

}


/////////////////////////////////////
// - Calcvns()
void CorrelationFramework::Calcvns()
{
	for( int TypBin=0; TypBin < nCorrTyp; TypBin++)
	for( int ptBin=0; ptBin < nPtBins[TypBin]; ptBin++)
	for( int multBin=0; multBin < nMultiplicityBins_Ana; multBin++)
	{

		double V2        = correl1D_FitResults[TypBin][ptBin][multBin].V2;
		double V2_cp     = correl1D_FitResults_cpar_ref[multBin].V2;
		double V2_Err    = correl1D_FitResults[TypBin][ptBin][multBin].V2_Error;
		double V2_cp_Err = correl1D_FitResults_cpar_ref[multBin].V2_Error;

		double V3        = correl1D_FitResults[TypBin][ptBin][multBin].V3;
		double V3_cp     = correl1D_FitResults_cpar_ref[multBin].V3;
		double V3_Err    = correl1D_FitResults[TypBin][ptBin][multBin].V3_Error;
		double V3_cp_Err = correl1D_FitResults_cpar_ref[multBin].V3_Error;

		double v2 = V2 / sqrt( V2_cp);
		double v3 = V3 / sqrt( V3_cp);

		correl_Results[TypBin][ptBin][multBin].v2           = v2;
		correl_Results[TypBin][ptBin][multBin].v2_StatError = sqrt( (V2_Err*V2_Err/ V2_cp) + (0.25 * V2 * V2 * V2_cp_Err * V2_cp_Err / pow( V2_cp, 3)) );
		correl_Results[TypBin][ptBin][multBin].v2_SystError = v2 * 0.055;

		correl_Results[TypBin][ptBin][multBin].v3           = V3 / sqrt( V3_cp);
		correl_Results[TypBin][ptBin][multBin].v3_StatError = sqrt( (V3_Err*V3_Err/ V3_cp) + (0.25 * V3 * V3 * V3_cp_Err * V3_cp_Err / pow( V3_cp, 3)) );
		correl_Results[TypBin][ptBin][multBin].v3_SystError = v3 * 0.055;



		if ( DoSelfCorrelation )
		{
		double V2_self     = correl1D_FitResults_self[TypBin][ptBin][multBin].V2;
		double V2_self_Err = correl1D_FitResults[TypBin][ptBin][multBin].V2_Error;

		correl_Results_self[TypBin][ptBin][multBin].v2           = sqrt(V2_self);
		correl_Results_self[TypBin][ptBin][multBin].v2_StatError = 0.5 * V2_self_Err / sqrt(V2_self);
		}

	}


	for( int multBin=0; multBin < nMultiplicityBins_Ana; multBin++)
	{
		correl_Results_cpar_ref[multBin].v2           = sqrt( correl1D_FitResults_cpar_ref[multBin].V2 );
		correl_Results_cpar_ref[multBin].v2_StatError = 0.5 * correl1D_FitResults_cpar_ref[multBin].V2_Error / sqrt( correl1D_FitResults_cpar_ref[multBin].V2);
		correl_Results_cpar_ref[multBin].v2_SystError = 0;
	}
}


//////////////////////////
// - ResetCurrentEvent()
void CorrelationFramework::ResetCurrentEventCorrelation()
{
 	for(int TypBin=0; TypBin < nCorrTyp; TypBin++)
 	for(int ptBin=0; ptBin < nPtBins[TypBin]; ptBin++)
 	{
		correl2D_currev_signal[TypBin][ptBin]->Reset();
		correl2D_currev_backgr[TypBin][ptBin]->Reset();

		if ( DoSelfCorrelation )
		{
			correl2D_self_currev_signal[TypBin][ptBin]->Reset();
			correl2D_self_currev_backgr[TypBin][ptBin]->Reset();
		}
	}

	correl2D_currev_cpar_ref_signal->Reset();
	correl2D_currev_cpar_ref_backgr->Reset();
}

/////////////////////
// - doAnalysis()
void CorrelationFramework::doAnalysis()
{
	
	for(int TypBin=0; TypBin < nCorrTyp; TypBin++)
	for(int ptBin=0; ptBin < nPtBins[TypBin]; ptBin++)
	for(int multBin=0; multBin < nMultiplicityBins_Ana; multBin++)
	{
	
	  Correl1DfitResultsData resdata;
	
	  resdata = doAnalysisSteps( correl2D_signal[TypBin][ptBin][multBin], correl2D_backgr[TypBin][ptBin][multBin], correl2D_functi[TypBin][ptBin][multBin], correl1D[TypBin][ptBin][multBin], nEvents_Processed_signal[multBin], nEvents_Processed_backgr[multBin], dEtacut);

	  correl1D_FitResults      [TypBin][ptBin][multBin] = resdata;

	  if ( DoSelfCorrelation )
	 {
	  Correl1DfitResultsData resdata_self;
	  resdata_self = doAnalysisSteps( correl2D_self_signal[TypBin][ptBin][multBin], correl2D_self_backgr[TypBin][ptBin][multBin], correl2D_self_functi[TypBin][ptBin][multBin], correl1D_self[TypBin][ptBin][multBin], nEvents_Processed_signal[multBin], nEvents_Processed_backgr[multBin], dEtacut);
	  correl1D_FitResults_self [TypBin][ptBin][multBin] = resdata_self;
	 }
	
	}

	for(int multBin=0; multBin < nMultiplicityBins_Ana; multBin++)
	{
	
	  Correl1DfitResultsData resdata;
	
	  resdata = doAnalysisSteps( correl2D_cpar_ref_signal[multBin], correl2D_cpar_ref_backgr[multBin], correl2D_cpar_ref_functi[multBin], correl1D_cpar_ref[multBin], nEvents_Processed_signal[multBin], nEvents_Processed_backgr[multBin], dEtacut);


	  correl1D_FitResults_cpar_ref[multBin] = resdata;
	

	
	}
	
}


//////////////////////////
// - GetnTrkvec
std::vector< double > CorrelationFramework::GetnTrkvec  ( double offset )
{
	std::vector< double > nTrkvec( nMultiplicityBins_Ana );

	for (int multBin = 0; multBin < nMultiplicityBins_Ana; multBin++)
	{
		nTrkvec[multBin] = offset + (multiplicity_Ana(multBin, 0, nMultiplicityBins_Ana) + multiplicity_Ana(multBin, 1, nMultiplicityBins_Ana)) / 2;
	}
	return nTrkvec;
}

///////////////////////
// - Getptvec
std::vector< double > CorrelationFramework::Getptvec  ( int TypBin, double offset )
{
	std::vector< double > ptvec(nPtBins[TypBin]);

	for (int ptBin = 0; ptBin < nPtBins[TypBin]; ptBin++)
	{
		ptvec[ptBin] = offset + (trigptbins[TypBin][ptBin][0] + trigptbins[TypBin][ptBin][1]) / 2;
	}
	return ptvec;
}

////////////////////////
// - GetV2vec
std::vector< double > CorrelationFramework::GetV2vec ( int TypBin, int multBin)
{

	std::vector< double > V2vec(nPtBins[TypBin]);

	for (int ptBin = 0; ptBin < nPtBins[TypBin]; ptBin++)
	{
		V2vec[ptBin] = correl1D_FitResults[TypBin][ptBin][multBin].V2;
	}

	return V2vec;
}

/////////////////////
// - GetV2_Errorvec
std::vector< double > CorrelationFramework::GetV2_Errorvec( int TypBin, int multBin)
{
	std::vector< double > V2_Errorvec(nPtBins[TypBin]);
	for (int ptBin = 0; ptBin < nPtBins[TypBin]; ptBin++)
	{
		V2_Errorvec[ptBin] = correl1D_FitResults[TypBin][ptBin][multBin].V2_Error;
	}
	return V2_Errorvec;
}

///////////////////////
// - Getv2vec
std::vector< double > CorrelationFramework::Getv2vec ( int TypBin, int multBin)
{

	std::vector< double > v2vec(nPtBins[TypBin]);

	for (int ptBin = 0; ptBin < nPtBins[TypBin]; ptBin++)
	{
		v2vec[ptBin] = correl_Results[TypBin][ptBin][multBin].v2;
	}

	return v2vec;
}

///////////////////////
// - Getv3vec
std::vector< double > CorrelationFramework::Getv3vec ( int TypBin, int multBin)
{

	std::vector< double > v3vec(nPtBins[TypBin]);

	for (int ptBin = 0; ptBin < nPtBins[TypBin]; ptBin++)
	{
		v3vec[ptBin] = correl_Results[TypBin][ptBin][multBin].v3;
	}

	return v3vec;
}

///////////////////////
// - Get_self_v2vec
std::vector< double > CorrelationFramework::Get_self_v2vec ( int TypBin, int multBin)
{

	std::vector< double > v2vec(nPtBins[TypBin]);

	for (int ptBin = 0; ptBin < nPtBins[TypBin]; ptBin++)
	{
		v2vec[ptBin] = correl_Results_self[TypBin][ptBin][multBin].v2;
	}

	return v2vec;
}

///////////////////////
// - Get_self_v2_StatErrorvec
std::vector< double > CorrelationFramework::Get_self_v2_StatErrorvec ( int TypBin, int multBin)
{

	std::vector< double > v2Errorvec(nPtBins[TypBin]);

	for (int ptBin = 0; ptBin < nPtBins[TypBin]; ptBin++)
	{
		v2Errorvec[ptBin] = correl_Results_self[TypBin][ptBin][multBin].v2_StatError;
	}

	return v2Errorvec;
}


/////////////////////////////
// - Get_cpar_ref_v2vec_nTrk
std::vector< double > CorrelationFramework::Get_cpar_ref_v2vec_nTrk ()
{
	std::vector< double > v2vec( nMultiplicityBins_Ana );

	for (int multBin = 0; multBin < nMultiplicityBins_Ana; multBin++)
	{ v2vec[multBin] = correl_Results_cpar_ref[multBin].v2; }
	return v2vec;
}

std::vector< double > CorrelationFramework::Get_cpar_ref_v2_StatError_vec_nTrk ()
{
	std::vector< double > v2StatErrorvec( nMultiplicityBins_Ana );

	for (int multBin = 0; multBin < nMultiplicityBins_Ana; multBin++)
	{ v2StatErrorvec[multBin] = correl_Results_cpar_ref[multBin].v2_StatError; }
	return v2StatErrorvec;
}

//////////////////////////
// Getv2_StatErrorvec
std::vector< double > CorrelationFramework::Getv2_StatErrorvec( int TypBin, int multBin)
{
	std::vector< double > v2_StatErrorvec(nPtBins[TypBin]);
	for (int ptBin = 0; ptBin < nPtBins[TypBin]; ptBin++)
	{
		v2_StatErrorvec[ptBin] = correl_Results[TypBin][ptBin][multBin].v2_StatError;
	}
	return v2_StatErrorvec;
}

//////////////////////////
// Getv2_SystErrorvec
std::vector< double > CorrelationFramework::Getv2_SystErrorvec( int TypBin, int multBin)
{
	std::vector< double > v2_SystErrorvec(nPtBins[TypBin]);
	for (int ptBin = 0; ptBin < nPtBins[TypBin]; ptBin++)
	{
		v2_SystErrorvec[ptBin] = correl_Results[TypBin][ptBin][multBin].v2_SystError;
	}
	return v2_SystErrorvec;
}

//////////////////////////
// Getv3_StatErrorvec
std::vector< double > CorrelationFramework::Getv3_StatErrorvec( int TypBin, int multBin)
{
	std::vector< double > v3_StatErrorvec(nPtBins[TypBin]);
	for (int ptBin = 0; ptBin < nPtBins[TypBin]; ptBin++)
	{
		v3_StatErrorvec[ptBin] = correl_Results[TypBin][ptBin][multBin].v3_StatError;
	}
	return v3_StatErrorvec;
}

//////////////////////////
// Getv3_SystErrorvec
std::vector< double > CorrelationFramework::Getv3_SystErrorvec( int TypBin, int multBin)
{
	std::vector< double > v3_SystErrorvec(nPtBins[TypBin]);
	for (int ptBin = 0; ptBin < nPtBins[TypBin]; ptBin++)
	{
		v3_SystErrorvec[ptBin] = correl_Results[TypBin][ptBin][multBin].v3_SystError;
	}
	return v3_SystErrorvec;
}

void CorrelationFramework::ReBin()
{
 // Displaying
 for(int TypBin=0; TypBin < nCorrTyp; TypBin++)
 for(int ptBin=0; ptBin < nPtBins[TypBin]; ptBin++)
 for(int multiplicityBin=0; multiplicityBin < nMultiplicityBins_Ana; multiplicityBin++)
 {	
	correl2D_signal[TypBin][ptBin][multiplicityBin]->Rebin2D(3,3);
	correl2D_backgr[TypBin][ptBin][multiplicityBin]->Rebin2D(3,3); 
	correl2D_functi[TypBin][ptBin][multiplicityBin]->Rebin2D(3,3);
 }
}


///////////////////////
// display_v2s()
void CorrelationFramework::display_v2s()
{

 std::cerr << std::endl << "# ===== Correlation Analysis results ===== # " << std::endl;
 std::cerr << "(Charged particle/pion/kaon/proton) - (charged particle) correlations:" << std::endl;

 for(int TypBin=0; TypBin < nCorrTyp; TypBin++)
 for(int ptBin=0; ptBin < nPtBins[TypBin]; ptBin++)
 for(int multBin=0; multBin < nMultiplicityBins_Ana; multBin++)
 {


	int mult1 = multiplicity_Ana(multBin, 0, nMultiplicityBins_Ana);
	int mult2 = multiplicity_Ana(multBin, 1, nMultiplicityBins_Ana);

	double pt1 = pt(TypBin, ptBin, 0);
	double pt2 = pt(TypBin, ptBin, 1);

	double V2              = correl1D_FitResults[TypBin][ptBin][multBin].V2;
	double V2_Error        = correl1D_FitResults[TypBin][ptBin][multBin].V2_Error;

	double V2_cp_ref       = correl1D_FitResults_cpar_ref[multBin].V2;
	double V2_cp_ref_Error = correl1D_FitResults_cpar_ref[multBin].V2_Error;

	double v2       	     = correl_Results[TypBin][ptBin][multBin].v2;
	double v2_StatError    = correl_Results[TypBin][ptBin][multBin].v2_StatError;

	std::cout << Form("TypBin: %1d pt: [ %.2f - %.2f ] mult: [ %03d - %03d ]  v2: %.4f +/- %.4f |", TypBin, pt1, pt2, mult1, mult2, v2, v2_StatError  ) << std::endl; 
 }
 

 std::cerr << Form("(Charged particle) - (charged particle) reference pt[ %.2f - %.2f ]", ptref1, ptref2) << std::endl;
 for(int multBin=0; multBin < nMultiplicityBins_Ana; multBin++)
 { 

	int mult1 = multiplicity_Ana(multBin, 0, nMultiplicityBins_Ana);
	int mult2 = multiplicity_Ana(multBin, 1, nMultiplicityBins_Ana);

	double v2       	     = correl_Results_cpar_ref[multBin].v2;
	double v2_StatError    = correl_Results_cpar_ref[multBin].v2_StatError;

	std::cout << Form(" mult: [ %03d - %03d ] v2_cpar: %.4f +/- %.4f", mult1, mult2, v2, v2_StatError ) << std::endl;
 }

}


////////////////////////////////////////////
//                                        //
//  *  Correlation analysis functions  *  //
//                                        //
////////////////////////////////////////////

Correl1DfitResultsData doAnalysisSteps(TH2D *correl_signal, TH2D *correl_backgr, TH2D *correl_functi, TH1D *correl_1D, TH1D *nEvents_Processed_signal, TH1D *nEvents_Processed_backgr, detacut dEtacut)
{

	Correl1DfitResultsData results;
	
	normalizeBynEvents( correl_signal, nEvents_Processed_signal);
	normalizeBynEvents( correl_backgr, nEvents_Processed_backgr);

	makeCorrelationFunction( correl_signal, correl_backgr, correl_functi );
	// project2Dto1D( correl_functi, correl_1D, dEtacut );
	//project2Dto1D_weightedmean( correl_functi, correl_1D, dEtacut );
	sum_and_project2Dto1D(correl_signal, correl_backgr, correl_1D, dEtacut);
	results = fit1DCorrelation_noplot( correl_1D);

	return results;
}


//////////////////////////////
// normalizeBynEvents
void normalizeBynEvents(TH2D* correl, TH1D* nEvents_Processed)
{
 	TH1::SetDefaultSumw2( );
 	TH2::SetDefaultSumw2( );

	double nEvents = nEvents_Processed->GetBinContent( nEvents_Processed->FindBin(1) );

	if (nEvents == 0) { correl->Reset(); }
	else
	{ correl->Scale(1./nEvents); }
};

/////////////////////////////////////////////
// makeCorrelationFunction
// - creates the TH2D correlation function from
//   the signal and background TH2D
//  !!!!!!!!! NEEDS NEVENTS NORMALIZATION
void makeCorrelationFunction(TH2D* correl_signal, TH2D* correl_backgr, TH2D* correl_functi)
{
 	TH1::SetDefaultSumw2( );
 	TH2::SetDefaultSumw2( );

	double Bur = correl_backgr->GetBinContent( correl_backgr->FindBin( 0.01, 0.01) );
	double Bul = correl_backgr->GetBinContent( correl_backgr->FindBin(-0.01, 0.01) );
	double Bdl = correl_backgr->GetBinContent( correl_backgr->FindBin(-0.01,-0.01) );
	double Bdr = correl_backgr->GetBinContent( correl_backgr->FindBin( 0.01,-0.01) );

	double B00_avg = (Bur + Bul + Bdl + Bdr)/4;

	correl_functi->Divide(correl_signal, correl_backgr, B00_avg, 1.00);
	//correl_functi->Divide(1./double(nEvents));
};


////////////////////////////////////
// sum_and_project2Dto1D
void sum_and_project2Dto1D(TH2D *correl_signal, TH2D *correl_backgr, TH1D* correl_1D, detacut dEtacut)
{

 	TH1D correl1D_signal_sum   = TH1D("correl1D_signal_sum",   "1D Correlation", ndPhiBins, dPhiMin, dPhiMax);
 	TH1D correl1D_signal_front = TH1D("correl1D_signal_front", "1D Correlation", ndPhiBins, dPhiMin, dPhiMax);
 	TH1D correl1D_signal_back  = TH1D("correl1D_signal_back" , "1D Correlation", ndPhiBins, dPhiMin, dPhiMax);

 	TH1D correl1D_backgr_sum   = TH1D("correl1D_backgr_sum",   "1D Correlation", ndPhiBins, dPhiMin, dPhiMax);
 	TH1D correl1D_backgr_front = TH1D("correl1D_backgr_front", "1D Correlation", ndPhiBins, dPhiMin, dPhiMax);
 	TH1D correl1D_backgr_back  = TH1D("correl1D_backgr_back",  "1D Correlation", ndPhiBins, dPhiMin, dPhiMax);

	correl_signal->ProjectionY("correl1D_signal_front",  dEtacut.negdEtaCut1Bin, dEtacut.negdEtaCut2Bin, "e");
	correl_signal->ProjectionY("correl1D_signal_back" ,  dEtacut.posdEtaCut1Bin, dEtacut.posdEtaCut2Bin, "e");

	correl_backgr->ProjectionY("correl1D_backgr_front",  dEtacut.negdEtaCut1Bin, dEtacut.negdEtaCut2Bin, "e");
	correl_backgr->ProjectionY("correl1D_backgr_back" ,  dEtacut.posdEtaCut1Bin, dEtacut.posdEtaCut2Bin, "e");

	correl1D_signal_sum.Add(&correl1D_signal_front);
	correl1D_signal_sum.Add(&correl1D_signal_back);

	correl1D_backgr_sum.Add(&correl1D_backgr_front);
	correl1D_backgr_sum.Add(&correl1D_backgr_back);
	
	correl_1D->Divide(&correl1D_signal_sum, &correl1D_backgr_sum, 1.00, 1.00 );
	correl_1D->Rebin(3);
}




////////////////////////////////////
// Project2Dto1D
void project2Dto1D(TH2D *correl_functi, TH1D* correl_1D, detacut dEtacut)
{
 	TH1D correl_1D_front = TH1D("correl_1D_front", "1D Correlation", ndPhiBins, dPhiMin, dPhiMax);
 	TH1D correl_1D_back  = TH1D("correl_1D_back",  "1D Correlation", ndPhiBins, dPhiMin, dPhiMax);

	correl_functi->ProjectionY("correl_1D_front",  dEtacut.negdEtaCut1Bin, dEtacut.negdEtaCut2Bin, "e");
	correl_functi->ProjectionY("correl_1D_back" ,  dEtacut.posdEtaCut1Bin, dEtacut.posdEtaCut2Bin, "e");
	
	correl_1D->Add(&correl_1D_front);
	correl_1D->Add(&correl_1D_back);
}


////////////////////////////////////
// Project2Dto1D
void project2Dto1D_weightedmean(TH2D *correl_functi, TH1D* correl_1D, detacut dEtacut)
{
	for(int dPhiBin = 1; dPhiBin <= ndPhiBins; dPhiBin++)
	{
		double weightedsum = 0.;
		double sumofinversevariances = 0.;
	
		for(int dEtaBin = dEtacut.negdEtaCut1Bin; dEtaBin <= dEtacut.negdEtaCut2Bin; dEtaBin++)
		{
		  double xi = correl_functi->GetBinContent(dEtaBin,dPhiBin);
		  if (xi == 0.) continue;
		  double si = correl_functi->GetBinError(dEtaBin,dPhiBin);
		  weightedsum = 	weightedsum + xi/si/si;
		  sumofinversevariances = sumofinversevariances + 1./si/si;
		}
		
		for(int dEtaBin = dEtacut.posdEtaCut1Bin; dEtaBin <= dEtacut.posdEtaCut2Bin; dEtaBin++)
		{
		  double xi = correl_functi->GetBinContent(dEtaBin,dPhiBin);
		  if (xi == 0.) continue;
		  double si = correl_functi->GetBinError(dEtaBin,dPhiBin);
		  weightedsum = 	weightedsum + xi/si/si;
		  sumofinversevariances = sumofinversevariances + 1./si/si;
		}
	
	
	if ( weightedsum == 0.) continue;
	if ( sumofinversevariances == 0.) continue;
	
	double weightedmean       = weightedsum/sumofinversevariances;
	double weightedmean_sigma = sqrt(1./sumofinversevariances);
	
	correl_1D->SetBinContent(dPhiBin, weightedmean);
	correl_1D->SetBinError(dPhiBin, weightedmean_sigma);
	
	}
}


/////////////////////////
// dEta
// - computes thes diferences between
//  two etas
double dEta (double Eta1, double Eta2)
{
 double deta = Eta1 - Eta2;
 return deta;
};


/////////////////////////////////
// dPhi
// - computes the difference between
//   two azimuth angles
double dPhi (double Phi1, double Phi2)
{
  double dphi = Phi1 - Phi2;
  if ( dphi < -TMath::Pi()/2   ) dphi = dphi + 2*TMath::Pi();
  if ( 3*TMath::Pi()/2 < dphi  ) dphi = dphi - 2*TMath::Pi();
 return dphi;
};


Correl1DfitResultsData fit1DCorrelation(TH1D *correl_1D, std::string figurename, std::string label)
{
   double phimin = -TMath::Pi()/2;
   double phimax = 3*TMath::Pi()/2;
   
	TCanvas canvas_correl_1D ("canvas_correl_1D","",800,600);
	gStyle->SetOptStat(0);

	TF1 *fitFunc = new TF1 ("fitFunc", "[0] * ( 1 + 2*[1]*cos(x) + 2*[2]*cos(2*x) + 2*[3]*cos(3*x) )");
	correl_1D->Fit( fitFunc);

	double a0 = fitFunc->GetParameter(0);
	double V1 = fitFunc->GetParameter(1);
	double V2 = fitFunc->GetParameter(2);
	double V3 = fitFunc->GetParameter(3);
	double a0_error = fitFunc->GetParError(0);
	double V1_error = fitFunc->GetParError(1);
	double V2_error = fitFunc->GetParError(2);
	double V3_error = fitFunc->GetParError(3);
	
	Correl1DfitResultsData results;

	results.V1 		  = V1;
	results.V2 		  = V2;
	results.V3 		  = V3;
	results.V1_Error = V1_error;
	results.V2_Error = V2_error;
	results.V3_Error = V3_error;

	TF1* baseline = new TF1 (  "baseline", "[0]", phimin, phimax);
	baseline->SetLineColor(kBlack);
	baseline->SetLineStyle(3);
	baseline->SetLineWidth(1);
	baseline->SetParameter(0, a0);

	TF1 *Fourier1 = new TF1 ("Fourier1th", "[0]*( 1 + 2*[1]*cos(1*x) )", phimin, phimax);
	Fourier1->SetLineColor(8);
	Fourier1->SetLineWidth(1);
	Fourier1->SetLineStyle(6);
	Fourier1->SetParameter(0, a0);
	Fourier1->SetParameter(1, V1);

	TF1 *Fourier2 = new TF1 ("Fourier2th", "[0]*( 1 + 2*[1]*cos(2*x) )", phimin, phimax);
	Fourier2->SetLineColor(kMagenta);
	Fourier2->SetLineWidth(1);
	Fourier2->SetLineStyle(2);
	Fourier2->SetParameter(0, a0);
	Fourier2->SetParameter(1, V2);

	TF1 *Fourier3 = new TF1 ("Fourier3th", "[0]*( 1 + 2*[1]*cos(3*x) )", phimin, phimax);
	Fourier3->SetLineColor(kBlue);
	Fourier3->SetLineWidth(1);
	Fourier3->SetLineStyle(8);
	Fourier3->SetParameter(0, a0);
	Fourier3->SetParameter(1, V3);


	baseline->Draw("SAME");
	Fourier1->Draw("SAME");
	Fourier2->Draw("SAME");
	Fourier3->Draw("SAME");

	double upperleftposx = 0.50;
	double upperleftposy = 0.25;
	double shift = 0.04;

	// Legend
	Double_t xl1=.73, yl1=0.75, xl2=xl1+.15, yl2=yl1+.125;
	TLegend v2vsptlegend (xl1,yl1,xl2,yl2);
	v2vsptlegend.AddEntry(fitFunc,"Fit function","L");
	v2vsptlegend.AddEntry(baseline,"baseline","L");
	v2vsptlegend.AddEntry(Fourier1,"Fourier 1th comp.","L");
	v2vsptlegend.AddEntry(Fourier2,"Fourier 2nd comp.","L");
	v2vsptlegend.AddEntry(Fourier3,"Fourier 3nd comp.","L");
	v2vsptlegend.Draw("SAME");


	TLatex tlabel( upperleftposx,upperleftposy,label.c_str()); 
	tlabel.SetTextSize(0.032);
	tlabel.SetNDC(kTRUE);
	tlabel.Draw();

	TLatex t1( upperleftposx,upperleftposy-shift,Form("V1 = %f #pm %f ", V1, V1_error) ); 
	t1.SetTextSize(0.032);
	t1.SetNDC(kTRUE);
	t1.Draw();

	TLatex t2( upperleftposx,upperleftposy-2*shift,Form("V2 = %f #pm %f ", V2, V2_error) ); 
	t2.SetTextSize(0.032);
	t2.SetNDC(kTRUE);
	t2.Draw();

	TLatex t3( upperleftposx,upperleftposy-3*shift,Form("V3 = %f #pm %f ", V3, V3_error) ); 
	t3.SetTextSize(0.032);
	t3.SetNDC(kTRUE);
	t3.Draw();

	canvas_correl_1D.SaveAs( figurename.c_str() );

	return results;
};


Correl1DfitResultsData fit1DCorrelation_noplot(TH1D *correl_1D)
{
   double phimin = -TMath::Pi()/2;
   double phimax = 3*TMath::Pi()/2;
   
	TF1 *fitFunc = new TF1 ("fitFunc", "[0] * ( 1 + 2*[1]*cos(x) + 2*[2]*cos(2*x) + 2*[3]*cos(3*x) )");
	correl_1D->Fit( fitFunc);

	double chisquare = fitFunc->GetChisquare();
	double ndf 		  = fitFunc->GetNDF();
	double chisqrdperndf = chisquare/ndf;

	double a0 = fitFunc->GetParameter(0);
	double V1 = fitFunc->GetParameter(1);
	double V2 = fitFunc->GetParameter(2);
	double V3 = fitFunc->GetParameter(3);

	double a0_error = fitFunc->GetParError(0);
	double V1_error = fitFunc->GetParError(1);
	double V2_error = fitFunc->GetParError(2);
	double V3_error = fitFunc->GetParError(3);
	
	Correl1DfitResultsData results;

	results.chisqrdperndf = chisqrdperndf;
	results.a0 		  		 = a0;
	results.V1 		  		 = V1;
	results.V2 		  		 = V2;
	results.V3 		  		 = V3;

	results.a0_Error = a0_error;
	results.V1_Error = V1_error;
	results.V2_Error = V2_error;
	results.V3_Error = V3_error;

	return results;
};


////////////////////////////////
//                            //
//   *  Setup functions  *    //
//                            //
////////////////////////////////

// Setup_EventCache
void Setup_EventCache( std::deque< EventData > **&EventCache, int nMultiplicityBins, int nZvtxBins)
{
 EventCache = new std::deque< EventData >*[nMultiplicityBins];
 for(int multBin=0; multBin < nMultiplicityBins; multBin++)
 { EventCache[multBin] = new std::deque< EventData >[nZvtxBins]; }
}


// Setp_TH2Ds_nCorrnPt
void Setup_TH2Ds_nCorrnPt( TH2D ***&correl2D, int nCorrTyp, int *nPtBins, const char histoname[], const char tag[])
{
	correl2D = new TH2D**[nCorrTyp];
	
	for( int TypBin=0; TypBin < nCorrTyp; TypBin++)
	{
		correl2D[TypBin] = new TH2D*[nPtBins[TypBin]];
		
		for( int ptBin=0 ;  ptBin < nPtBins[TypBin] ; ptBin++)
		{
		  double pt1 = pt(TypBin, ptBin, 0);
		  double pt2 = pt(TypBin, ptBin, 1);

		  correl2D[TypBin][ptBin] = new TH2D( Form("%s_%s_typ_%1d_pt_%.2f-%.2f", histoname, tag, TypBin, pt1, pt2),
		  														"2D Correlation function;#Delta #eta; #Delta #Phi",
		                                            ndEtaBins,dEtaMin,dEtaMax,ndPhiBins,dPhiMin,dPhiMax);}
	}
}


// Setup_TH2Ds_nCorrnPtnMult
void Setup_TH2Ds_nCorrnPtnMult( TH2D ****&correl2D, int nCorrTyp, int *nPtBins, int nMultiplicityBins, const char histoname[], const char tag[])
{
	correl2D = new TH2D***[nCorrTyp];
	
	for( int TypBin=0; TypBin < nCorrTyp; TypBin++)
	{
		correl2D[TypBin] = new TH2D**[nPtBins[TypBin]];

		for( int ptBin=0 ;  ptBin < nPtBins[TypBin] ; ptBin++)
		{
			correl2D[TypBin][ptBin] = new TH2D*[nMultiplicityBins];

			for(int multBin=0; multBin < nMultiplicityBins; multBin++)
			{
			  double pt1 = pt(TypBin, ptBin, 0);
			  double pt2 = pt(TypBin, ptBin, 1);
   		  int mult1 = multiplicity_Ana(multBin, 0, nMultiplicityBins);
			  int mult2 = multiplicity_Ana(multBin, 1, nMultiplicityBins);

				correl2D[TypBin][ptBin][multBin] = new TH2D(
				Form("%s_%s_typ_%1d_pt_%.2f-%.2f_nTrk_%03d-%03d", histoname, tag, TypBin, pt1, pt2, mult1, mult2),
				"2D Correlation function;#Delta #eta; #Delta #Phi",ndEtaBins,dEtaMin,dEtaMax,ndPhiBins,dPhiMin,dPhiMax);

			}
		}
	}
}


// Setup_TH2Ds_nMult
void Setup_TH2Ds_nMult( TH2D **&correl2D, int nMultiplicityBins, const char histoname[], const char tag[], double pt1, double pt2)
{
	correl2D = new TH2D*[nMultiplicityBins];
	
	for(int multBin=0; multBin < nMultiplicityBins; multBin++)
	{

     int mult1 = multiplicity_Ana(multBin, 0, nMultiplicityBins);
	  int mult2 = multiplicity_Ana(multBin, 1, nMultiplicityBins);

		correl2D[multBin] = new TH2D(
		Form("%s_%s_pt_%.2f-%.2f_nTrk_%03d-%03d", histoname, tag, pt1, pt2, mult1, mult2),
		"2D Correlation function;#Delta #eta; #Delta #Phi",ndEtaBins,dEtaMin,dEtaMax,ndPhiBins,dPhiMin,dPhiMax);

	}
}


// Setup_correl2D_currev_cpar_ref
void Setup_correl2D_currev_cpar_ref( TH2D *&correl2D_currev_cpar_ref, const char tag[], double pt1, double pt2)
{
	
	correl2D_currev_cpar_ref = new TH2D( Form("correl2D_currev_cpar_ref_%s_pt_%.2f-%.2f", tag, pt1, pt2),
		  														"2D Correlation function;#Delta #eta; #Delta #Phi",
		                                            ndEtaBins,dEtaMin,dEtaMax,ndPhiBins,dPhiMin,dPhiMax);
}


// Setup_TH1Ds_nCorrnPtnMult
void Setup_TH1Ds_nCorrnPtnMult( TH1D ****&correl1D, int nCorrTyp, int *nPtBins, int nMultiplicityBins, const char histoname[], const char tag[])
{
	
	correl1D = new TH1D***[nCorrTyp];
	
	for( int TypBin=0; TypBin < nCorrTyp; TypBin++)
	{
		correl1D[TypBin] = new TH1D**[nPtBins[TypBin]];

		for( int ptBin=0 ;  ptBin < nPtBins[TypBin] ; ptBin++)
		{
			correl1D[TypBin][ptBin] = new TH1D*[nMultiplicityBins];

			for(int multBin=0; multBin < nMultiplicityBins; multBin++)
			{
			  double pt1 = pt(TypBin, ptBin, 0);
			  double pt2 = pt(TypBin, ptBin, 1);
   		  int mult1 = multiplicity_Ana(multBin, 0, nMultiplicityBins);
			  int mult2 = multiplicity_Ana(multBin, 1, nMultiplicityBins);

				correl1D[TypBin][ptBin][multBin] = new TH1D(
				Form("%s_%s_typ_%1d_pt_%.2f-%.2f_nTrk_%03d-%03d", histoname, tag, TypBin, pt1, pt2, mult1, mult2),
				"1D Correlation function;#Delta #Phi; C(#Delta #Phi) ",ndPhiBins,dPhiMin,dPhiMax);

			}
		}
	}
}


// Setup_TH1Ds_nMult
void Setup_TH1Ds_nMult( TH1D **&correl1D, int nMultiplicityBins, const char histoname[], const char tag[])
{
	
	correl1D = new TH1D*[nMultiplicityBins];
	
			for(int multBin=0; multBin < nMultiplicityBins; multBin++)
			{

   		  int mult1 = multiplicity_Ana(multBin, 0, nMultiplicityBins);
			  int mult2 = multiplicity_Ana(multBin, 1, nMultiplicityBins);

				correl1D[multBin] = new TH1D(
				Form("%s_%s_pt_%.2f-%.2f_nTrk_%03d-%03d", histoname, tag, ptref1, ptref2, mult1, mult2),
				"1D Correlation function;#Delta #Phi; C(#Delta #Phi) ",ndPhiBins,dPhiMin,dPhiMax);
			}
}


// Setup_CorrelResults_nCorrnPtnMult
void Setup_CorrelResults_nCorrnPtnMult( CorrelResults ***&correl_Results, int nCorrTyp, int *nPtBins, int nMultiplicityBins )
{

	correl_Results	= new CorrelResults  **[nCorrTyp];

	for(int TypBin=0; TypBin < nCorrTyp; TypBin++)
	{
		correl_Results     [TypBin] = new CorrelResults         *[nPtBins[TypBin]];

		for(int ptBin=0; ptBin < nPtBins[TypBin]; ptBin++)
		{ correl_Results     [TypBin][ptBin] = new CorrelResults [nMultiplicityBins]; }
	}
}


// Setup_Correl1DfitResultsData_nCorrnPtnMult
void Setup_Correl1DfitResultsData_nCorrnPtnMult( Correl1DfitResultsData ***&correl1D_FitResults, int nCorrTyp, int *nPtBins, int nMultiplicityBins )
{

	correl1D_FitResults = new Correl1DfitResultsData  **[nCorrTyp];

	for(int TypBin=0; TypBin < nCorrTyp; TypBin++)
	{

		correl1D_FitResults[TypBin] = new Correl1DfitResultsData*[nPtBins[TypBin]];

		for(int ptBin=0; ptBin < nPtBins[TypBin]; ptBin++)
		{ correl1D_FitResults[TypBin][ptBin] = new Correl1DfitResultsData[nMultiplicityBins];}
	}

}

///////////////////////////////
//                           //
//  *  Read In functions  *  //
//                           //
///////////////////////////////

// ReadIn_TH2Ds_nCorrnPtnMult
void ReadIn_TH2Ds_nCorrnPtnMult(TFile *f, TH2D ****&correl2D, int nCorrTyp, int *nPtBins, int nMultiplicityBins, const char histoname[], const char tag[])
{
	correl2D = new TH2D***[nCorrTyp];

 	for(int TypBin=0; TypBin < nCorrTyp; TypBin++)
	{
		
		correl2D[TypBin] = new TH2D**[nPtBins[TypBin]];

		for(int ptBin=0; ptBin < nPtBins[TypBin]; ptBin++)
		{

			double pt1 = pt(TypBin, ptBin, 0);
			double pt2 = pt(TypBin, ptBin, 1);

			correl2D[TypBin][ptBin] = new TH2D*[nMultiplicityBins];

			for(int multiplicityBin=0; multiplicityBin < nMultiplicityBins; multiplicityBin++)
			{

			int mult1  = multiplicity_Ana(multiplicityBin, 0, nMultiplicityBins);
			int mult2  = multiplicity_Ana(multiplicityBin, 1, nMultiplicityBins);

			   correl2D[TypBin][ptBin][multiplicityBin] = (TH2D*)f->Get(Form("%s_%s_typ_%d_pt_%.2f-%.2f_nTrk_%03d-%03d", histoname, tag, TypBin, pt1, pt2, mult1, mult2  ) );
				if ( correl2D[TypBin][ptBin][multiplicityBin]->IsZombie() ) {std::cerr << "ReadIn_TH2Ds_nMult failed." << Form("No histogram named '%s_%s_pt_%.2f-%.2f_nTrk_%03d-%03d' is found.", histoname, tag, pt1, pt2, mult1, mult2  )<< std::endl;}
			}
		}

	}

}

// ReadIn_TH2Ds_nMult
void ReadIn_TH2Ds_nMult(TFile *f, TH2D **&correl2D, int nMultiplicityBins, const char histoname[], const char tag[], double pt1, double pt2)
{
	correl2D = new TH2D*[nMultiplicityBins];

		for(int multiplicityBin=0; multiplicityBin < nMultiplicityBins; multiplicityBin++)
		{

		int mult1  = multiplicity_Ana(multiplicityBin, 0, nMultiplicityBins);
		int mult2  = multiplicity_Ana(multiplicityBin, 1, nMultiplicityBins);


		  // Warning! -nTrk to _nTrk needed
		   correl2D[multiplicityBin] = (TH2D*)f->Get(Form("%s_%s_pt_%.2f-%.2f_nTrk_%03d-%03d", histoname, tag, pt1, pt2, mult1, mult2  ) );
			if (correl2D[multiplicityBin]->IsZombie() ) {std::cerr << "ReadIn_TH2Ds_nMult failed." << Form("No histogram named '%s_%s_pt_%.2f-%.2f_nTrk_%03d-%03d' is found.", histoname, tag, pt1, pt2, mult1, mult2  ) << std::endl;}
		}

}
