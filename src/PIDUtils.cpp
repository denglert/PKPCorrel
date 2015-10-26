#include "PIDUtils.h"
#include <TLatex.h>

// PID Parameters settings
//const float BB_Pion_low_par[3] = {2.35e-1, 0.61, 1.1e4};
//const float BB_Pion_hig_par[3] = {0.29, 2.2, 0.00};
//const float BB_Pion_mindEdxcut = 0.2;
//const float BB_Pion_minpcut = 0.15;
//const float BB_Pion_maxpcut = 1.0;
//
//const float BB_Kaon_low_par[3] = {0.3, 2.2, 0.00};
//const float BB_Kaon_hig_par[3] = {0.7, 2.5, 0.05};
//const float BB_Kaon_mindEdxcut = 3.2;
//const float BB_Kaon_maxpcut = 0.9;
//
//const float BB_Prot_low_par[3] = {0.9, 2.5, 0.05};
//const float BB_Prot_hig_par[3] = {2.4, 3.0, 0.15};
//const float BB_Prot_mindEdxcut = 3.4;
//const float BB_Prot_maxpcut = 1.6;

//////////////////////////////////////////////////////////////////////////
// PID class
PIDUtil::PIDUtil(  )
{
	unIDcode = 99;
	unIDcode_cm = 3.5;
	etaMax = 0.8;
};

PIDUtil::~PIDUtil(){};

void PIDUtil::ReadInConfig( std::string PIDconfigfile_str )
{
	configfile = PIDconfigfile_str;

	std::cout << "Reading in file: " << configfile.c_str() << std::endl;
   std::fstream config( configfile.c_str(), std::ios_base::in);

	// comment line
	std::string dummyLine;

	std::getline(config, dummyLine);
	std::cout << "dummyLine: " << dummyLine << std::endl;
	config >> BB_Pion_low_par[0] >> BB_Pion_low_par[1] >> BB_Pion_low_par[2];
	config >> BB_Pion_hig_par[0] >> BB_Pion_hig_par[1] >> BB_Pion_hig_par[2];
	config >> BB_Pion_mindEdxcut;
	config >> BB_Pion_minpcut;
	config >> BB_Pion_maxpcut;
	config >> dummyLine;
	std::getline(config, dummyLine);
	config >> BB_Kaon_low_par[0] >> BB_Kaon_low_par[1] >> BB_Kaon_low_par[2];
	config >> BB_Kaon_hig_par[0] >> BB_Kaon_hig_par[1] >> BB_Kaon_hig_par[2];
	config >> BB_Kaon_mindEdxcut;
	config >> BB_Kaon_maxpcut;
	config >> dummyLine;
	std::getline(config, dummyLine);
	config >> BB_Prot_low_par[0] >> BB_Prot_low_par[1] >> BB_Prot_low_par[2];
	config >> BB_Prot_hig_par[0] >> BB_Prot_hig_par[1] >> BB_Prot_hig_par[2];
	config >> BB_Prot_mindEdxcut;
	config >> BB_Prot_maxpcut;
	config >> dummyLine;
	std::getline(config, dummyLine);
	config >> BB_NonProt_mindEdxcut;
	config >> BB_NonProt_maxpcut;
	
	std::cout << "##########" << std::endl;
	std::cout << "Pion"       << std::endl;
	std::cout << "low"        << std::endl;
	std::cout << "a[0]: "     << BB_Pion_low_par[0] << std::endl;
	std::cout << "a[1]: "     << BB_Pion_low_par[1] << std::endl;
	std::cout << "a[2]: "     << BB_Pion_low_par[2] << std::endl;
	std::cout << "hig"        << std::endl;
	std::cout << "a[0]: "     << BB_Pion_hig_par[0] << std::endl;
	std::cout << "a[1]: "     << BB_Pion_hig_par[1] << std::endl;
	std::cout << "a[2]: "     << BB_Pion_hig_par[2] << std::endl;
	std::cout << "dEdx_min: " << BB_Pion_mindEdxcut << std::endl;
	std::cout << "pmin: "     << BB_Pion_minpcut    << std::endl;
	std::cout << "pmax: "     << BB_Pion_maxpcut    << std::endl;
	std::cout << "##########" << std::endl;
	std::cout << "Kaon"       << std::endl;
	std::cout << "low"        << std::endl;
	std::cout << "a[0]: "     << BB_Kaon_low_par[0] << std::endl;
	std::cout << "a[1]: "     << BB_Kaon_low_par[1] << std::endl;
	std::cout << "a[2]: "     << BB_Kaon_low_par[2] << std::endl;
	std::cout << "hig"        << std::endl;
	std::cout << "a[0]: "     << BB_Kaon_hig_par[0] << std::endl;
	std::cout << "a[1]: "     << BB_Kaon_hig_par[1] << std::endl;
	std::cout << "a[2]: "     << BB_Kaon_hig_par[2] << std::endl;
	std::cout << "dEdx_min: " << BB_Kaon_mindEdxcut << std::endl;
	std::cout << "pmax: "     << BB_Kaon_maxpcut    << std::endl;
	std::cout << "##########" << std::endl;
	std::cout << "Prot"       << std::endl;
	std::cout << "low"        << std::endl;
	std::cout << "a[0]: "     << BB_Prot_low_par[0] << std::endl;
	std::cout << "a[1]: "     << BB_Prot_low_par[1] << std::endl;
	std::cout << "a[2]: "     << BB_Prot_low_par[2] << std::endl;
	std::cout << "hig"        << std::endl;
	std::cout << "a[0]: "     << BB_Prot_hig_par[0] << std::endl;
	std::cout << "a[1]: "     << BB_Prot_hig_par[1] << std::endl;
	std::cout << "a[2]: "     << BB_Prot_hig_par[2] << std::endl;
	std::cout << "dEdx_min: " << BB_Prot_mindEdxcut << std::endl;
	std::cout << "pmax: "     << BB_Prot_maxpcut    << std::endl;
	std::cout << "##########" << std::endl;
	std::cout << "NonProt"       << std::endl;
	std::cout << "dEdx_min: " << BB_NonProt_mindEdxcut << std::endl;
	std::cout << "pmax: "     << BB_NonProt_maxpcut    << std::endl;
}

int PIDUtil::GetID(const Tracks_c &tTracks, int iTrk)
{
	float eta  = tTracks.trkEta[iTrk];
  	float p    = tTracks.trkPt[iTrk] * cosh(tTracks.trkEta[iTrk]);
	float pt   = tTracks.trkPt[iTrk];
	float dEdx = tTracks.dedx[iTrk];

	if (  etaMax < fabs(eta) ) 							{return unIDcode;}
	if (  isPion(p, dEdx) == true ) 						{return 1;}
	if (  isKaon(p, dEdx) == true ) 						{return 2;}

	bool izProt = isProt(p, dEdx);

	if (   izProt ) 											{return 3;}
	if (  (izProt == false) && (p < BB_NonProt_maxpcut) && ( BB_NonProt_mindEdxcut < dEdx) ) {return 4;}
	return unIDcode;
}

int PIDUtil::GetID(const Tracks &tTracks, int iTrk)
{

	float eta  = tTracks.trkEta[iTrk];
  	float p    = tTracks.trkPt[iTrk] * cosh(tTracks.trkEta[iTrk]);
	float pt   = tTracks.trkPt[iTrk];
	float dEdx = tTracks.dedx[iTrk];

	if (  etaMax < fabs(eta) ) 							{return unIDcode;}
	if (  isPion(p, dEdx) == true ) 						{return 1;}
	if (  isKaon(p, dEdx) == true ) 						{return 2;}

	bool izProt = isProt(p, dEdx);

	if (   izProt ) 											{return 3;}
	if (  (izProt == false) && (p < BB_NonProt_maxpcut) && ( BB_NonProt_mindEdxcut < dEdx) ) {return 4;}

	return unIDcode;
}

int PIDUtil::GetIDmTrk_trkCorr( const Tracks_c &tTracks, int iTrk )
{
	float eta  = tTracks.pEta[iTrk];
	// WARNING/Warning/warning pt = pPt <-> mtrkPt
	float pt   = tTracks.mtrkPt[iTrk];
  	float p    = pt * cosh(eta);
	float dEdx = tTracks.mtrkdedx[iTrk];

	if (  etaMax < fabs(eta) ) 							{return unIDcode;}
	if (  isPion(p, dEdx) == true ) 						{return 1;}
	if (  isKaon(p, dEdx) == true ) 						{return 2;}

	bool izProt = isProt(p, dEdx);

	if (   izProt ) 											{return 3;}
	if (  (izProt == false) && (p < BB_NonProt_maxpcut) && ( BB_NonProt_mindEdxcut < dEdx) ) {return 4;}

	return unIDcode;
}

int PIDUtil::GetIDgenPart_trkCorr(const Particles &tTracks, int iPart)
{

	float eta  = tTracks.pEta[iPart];
	float pt   = tTracks.pPt [iPart];
  	float p    = pt * cosh(eta);
	int McPID  = tTracks.pPId[iPart];

	if (  etaMax < fabs(eta) ) 						{return unIDcode;}

	if ( p < BB_Kaon_maxpcut )
	{
		if (( McPID == 211)  || (McPID == -211) ) 	{ return 1; }
		if (( McPID == 321)  || (McPID == -321) ) 	{ return 2; }
		if (( McPID == 2212) || (McPID == -2212)) 	{ return 3; }
	}
	else if ( ( BB_Kaon_maxpcut < p) && (p < BB_Pion_maxpcut) )
	{
		if (( McPID == 211)  || (McPID == -211) ) 	{ return 1; }
		if (( McPID == 2212) || (McPID == -2212)) 	{ return 3; }
	}
	else if ( ( BB_Pion_maxpcut < p) && (p < BB_Prot_maxpcut) )
	{
		if (  ( McPID == 2212) || (McPID == -2212)) 	{ return 3; }
		else {return 4;}
		
	}

	return unIDcode;
}

int PIDUtil::GetIDgenPart_trkCorr(const GenParticles &tTracks, int iPart)
{

	float eta  = tTracks.eta[iPart];
	float pt   = tTracks.pt [iPart];
  	float p    = pt * cosh(eta);
	int McPID  = tTracks.pdg[iPart];

	if (  etaMax < fabs(eta) ) 						{return unIDcode;}

	if ( p < BB_Kaon_maxpcut )
	{
		if (( McPID == 211)  || (McPID == -211) ) 	{ return 1; }
		if (( McPID == 321)  || (McPID == -321) ) 	{ return 2; }
		if (( McPID == 2212) || (McPID == -2212)) 	{ return 3; }
	}
	else if ( ( BB_Kaon_maxpcut < p) && (p < BB_Pion_maxpcut) )
	{
		if (( McPID == 211)  || (McPID == -211) ) 	{ return 1; }
		if (( McPID == 2212) || (McPID == -2212)) 	{ return 3; }
	}
	else if ( ( BB_Pion_maxpcut < p) && (p < BB_Prot_maxpcut) )
	{
		if (  ( McPID == 2212) || (McPID == -2212)) 	{ return 3; }
		else {return 4;}
		
	}

	return unIDcode;
}

int PIDUtil::GetIDgenPart_trkCorr(const Tracks_c &tTracks, int iPart)
{

	float eta  = tTracks.pEta[iPart];
	float pt   = tTracks.pPt [iPart];
  	float p    = pt * cosh(eta);
	int McPID  = tTracks.pPId[iPart];

	if (  etaMax < fabs(eta) ) 						{return unIDcode;}

	if ( p < BB_Kaon_maxpcut )
	{
		if (( McPID == 211)  || (McPID == -211) ) 	{ return 1; }
		if (( McPID == 321)  || (McPID == -321) ) 	{ return 2; }
		if (( McPID == 2212) || (McPID == -2212)) 	{ return 3; }
	}
	else if ( ( BB_Kaon_maxpcut < p) && (p < BB_Pion_maxpcut) )
	{
		if (( McPID == 211)  || (McPID == -211) ) 	{ return 1; }
		if (( McPID == 2212) || (McPID == -2212)) 	{ return 3; }
	}
	else if ( ( BB_Pion_maxpcut < p) && (p < BB_Prot_maxpcut) )
	{
		if (  ( McPID == 2212) || (McPID == -2212)) 	{ return 3; }
		else {return 4;}
		
	}

	return unIDcode;
}

//int PIDUtil::GetID(float p, float dEdx, float eta)
//{
//	if ( etaMax < fabs(eta) ) return unIDcode;
//	if ( isPion(p, dEdx) == true) {return 1;}
//	if ( isKaon(p, dEdx) == true) {return 2;}
//	if ( isProt(p, dEdx) == true) {return 3;}
//	return unIDcode;
//}

double PIDUtil::GetID_cm(const Tracks_c &tTracks, int iTrk)
{
	float eta  = tTracks.pEta[iTrk];
	float mpt  = tTracks.mtrkPt[iTrk];
  	float mp   = mpt * cosh(eta);
	float dEdx = tTracks.mtrkdedx[iTrk];

	if (  etaMax < fabs(eta) ) 							  {return unIDcode;}
	if (  isPion(mp, dEdx) == true ) 					  {return 0.5;}
	if (  isKaon(mp, dEdx) == true ) 					  {return 1.5;}

	bool izProt = isProt(mp, dEdx);

	if (   izProt ) 											{return 2.5;}
	if (  (izProt == false) && (mp < BB_NonProt_maxpcut) && ( BB_NonProt_mindEdxcut < dEdx) ) {return 3.5;}

	return unIDcode;
}


float PIDUtil::BBcurve(float *x, const float *par)
{
	return ((par[0] / (x[0]-par[2])) / (x[0]-par[2])) + par[1];
}

// isPion
bool PIDUtil::isPion(float p, float dEdx)
{
	if (  (dEdx < BBcurve(&p , BB_Pion_hig_par)) && ( p < BB_Pion_maxpcut ) && ( BB_Pion_minpcut < p) && (BB_Pion_mindEdxcut < dEdx)  )
	{ return true; }
	else
	{return false; }
}

// isKaon
bool PIDUtil::isKaon(float p, float dEdx)
{
	if (  (BBcurve(&p , BB_Kaon_low_par) < dEdx ) && (dEdx < BBcurve(&p , BB_Kaon_hig_par))  &&  (p < BB_Kaon_maxpcut ) && (BB_Kaon_mindEdxcut < dEdx) )
	{ return true; }
	else
	{return false; }

}

// isProt
bool PIDUtil::isProt( float p, float dEdx )
{
	if (  (BBcurve(&p , BB_Prot_low_par) < dEdx ) && (dEdx < BBcurve(&p , BB_Prot_hig_par))  &&  (p < BB_Prot_maxpcut ) && (BB_Prot_mindEdxcut < dEdx) )
	{ return true;  }
	else
	{ return false; }
}

//////////////////////////////////////////////////////////////////////////

double BBcurve1( double *x, double *par )
{
	return ((par[0] / (x[0]-par[2])) / (x[0]-par[2])) + par[1];
}
//
//float BBcurve1c(float *x, const float *par)
//{
//	return ((par[0] / (x[0]-par[2])) / (x[0]-par[2])) + par[1];
//}
//
//// isPion
//bool isPion(float p, float dEdx)
//{
//	if (  (dEdx < BBcurve1c(&p , BB_Pion_hig_par)) && ( p < BB_Pion_maxpcut ) && ( BB_Pion_minpcut < p) && (BB_Pion_mindEdxcut < dEdx)  )
//	{ return true; }
//	else
//	{return false; }
//}
//
//// isKaon
//bool isKaon(float p, float dEdx)
//{
//	if (  (BBcurve1c(&p , BB_Kaon_low_par) < dEdx ) && (dEdx < BBcurve1c(&p , BB_Kaon_hig_par))  &&  (p < BB_Kaon_maxpcut ) && (BB_Kaon_mindEdxcut < dEdx) )
//	{ return true; }
//	else
//	{return false; }
//}
//
//// isProt
//bool isProt(float p, float dEdx)
//{
//	if (  (BBcurve1c(&p , BB_Prot_low_par) < dEdx ) && (dEdx < BBcurve1c(&p , BB_Prot_hig_par))  &&  (p < BB_Prot_maxpcut ) && (BB_Prot_mindEdxcut < dEdx) )
//	{ return true; }
//	else
//	{return false; }
//}

// GetPID
// 99 - pion
//  1 - pion
//  2 - kaon
//  3 - prot
//int GetPID(float p, float dEdx, float eta)
//{
//	if ( 0.8 < fabs(eta) ) return 99;
//	if ( isPion(p, dEdx) == true) {return 1;}
//	if ( isKaon(p, dEdx) == true) {return 2;}
//	if ( isProt(p, dEdx) == true) {return 3;}
//	return 99;
//}

//int McPID2AnaPID ( const Tracks_c &tTracks, int iPart)
//{
//
//	float eta  = tTracks.pEta[iPart];
//	float pt   = tTracks.pPt [iPart];
//	int McPID  = tTracks.pPId[iPart];
//  	float p    = pt * cosh(eta);
//
//	if ( 0.8 < fabs(eta) ) {return 99;}
//
//	if ( p < 1.0 )
//	{
//	if (( McPID == 211)  || (McPID == -211) ) 	{ return 1; }
//	if (( McPID == 321)  || (McPID == -321) ) 	{ return 2; }
//	if (( McPID == 2212) || (McPID == -2212)) 	{ return 3; }
//	}
//	if ( 1.0 < p )
//	{
//		if (  ( McPID == 2212) || (McPID == -2212) ) { return 3; }
//		if (!(( McPID == 2212) || (McPID == -2212))) { return 4; }
//	}
//
//	return 99;
//};

int McPID2AnaPID ( const Particles &tTracks, int iPart)
{

	float eta  = tTracks.pEta[iPart];
	float pt   = tTracks.pPt [iPart];
	int McPID  = tTracks.pPId[iPart];
  	float p    = pt * cosh(eta);

	if ( 0.8 < fabs(eta) ) {return 99;}

	if (( McPID == 211)  || (McPID == -211) ) 	{ return 1; }
	if (( McPID == 321)  || (McPID == -321) ) 	{ return 2; }
	if (( McPID == 2212) || (McPID == -2212)) 	{ return 3; }

	return 99;
};


double McPID2AnaPID_cm(const Tracks_c &tTracks, int iPart)
{
	
	float eta  = tTracks.pEta[iPart];
	float pt   = tTracks.pPt [iPart];
	int McPID  = tTracks.pPId[iPart];
	
	if (  0.8 < fabs(eta) ) 							{return 99;}

	if ( (0.2 < pt) && (pt < 0.9) )
	{
		if (( McPID == 211)  || (McPID == -211) )    { return 0.5; }
		if (( McPID == 321)  || (McPID == -321) )    { return 1.5; }
		if (( McPID == 2212) || (McPID == -2212))    { return 2.5; }
	}

	if ( (0.9 < pt) && (pt < 1.0) )
	{
		if (( McPID == 211)  || (McPID == -211) )    { return 0.5; }
		if (( McPID == 2212) || (McPID == -2212))    { return 2.5; }
	}

	if ( (1.0 < pt) && (pt < 1.6) )
	{
		if (  ( McPID == 2212) || (McPID == -2212) ) { return 2.5; }
		if (!(( McPID == 2212) || (McPID == -2212))) { return 3.5; }
	}

	return 99;
}

void makedEdxvspFiglinlin(TH2D* dEdxvsP, std::string PIDconfig, std::string figurename)
{
	TF1 BB_Pion_low ("BB_Pion_low_fcn" , BBcurve1, pminlin, pmaxlin, 3);
	TF1 BB_Pion_hig ("BB_Pion_high_fcn", BBcurve1, pminlin, pmaxlin, 3);
	TF1 BB_Kaon_low ("BB_Kaon_low_fcn" , BBcurve1, pminlin, pmaxlin, 3);
	TF1 BB_Kaon_hig ("BB_Kaon_high_fcn", BBcurve1, pminlin, pmaxlin, 3);
	TF1 BB_Prot_low ("BB_Prot_low_fcn" , BBcurve1, pminlin, pmaxlin, 3);
	TF1 BB_Prot_hig ("BB_Prot_high_fcn", BBcurve1, pminlin, pmaxlin, 3);

	PIDUtil pid;
	pid.ReadInConfig( PIDconfig);

	BB_Pion_low.SetParameters(pid.BB_Pion_low_par[0], pid.BB_Pion_low_par[1], pid.BB_Pion_low_par[2]);
	BB_Pion_hig.SetParameters(pid.BB_Pion_hig_par[0], pid.BB_Pion_hig_par[1], pid.BB_Pion_hig_par[2]);
	BB_Kaon_low.SetParameters(pid.BB_Kaon_low_par[0], pid.BB_Kaon_low_par[1], pid.BB_Kaon_low_par[2]);
	BB_Kaon_hig.SetParameters(pid.BB_Kaon_hig_par[0], pid.BB_Kaon_hig_par[1], pid.BB_Kaon_hig_par[2]);
	BB_Prot_low.SetParameters(pid.BB_Prot_low_par[0], pid.BB_Prot_low_par[1], pid.BB_Prot_low_par[2]);
	BB_Prot_hig.SetParameters(pid.BB_Prot_hig_par[0], pid.BB_Prot_hig_par[1], pid.BB_Prot_hig_par[2]);
	
	BB_Pion_hig.SetLineColor(kMagenta);
	BB_Kaon_low.SetLineColor(kBlue);
	BB_Kaon_hig.SetLineColor(kBlue);
	BB_Prot_low.SetLineColor(kBlack);
	BB_Prot_hig.SetLineColor(kBlack);
	
	TCanvas c("dEdxvsP","dEdxvsP", 1024, 768);
	c.SetLogz(1);
	
	gStyle->SetOptStat(0);
	dEdxvsP->GetXaxis()->SetRangeUser(pminlin,pmaxlin);
	dEdxvsP->GetYaxis()->SetRangeUser(dEdxminlin,dEdxmaxlin);
	dEdxvsP->GetXaxis()->SetTitle("p [GeV/c]");
	
	double pion_maxpcut  = pid.BB_Pion_maxpcut;
	
	double kaon_lowcut  = pid.BB_Kaon_mindEdxcut;
	double kaon_maxpcut = pid.BB_Kaon_maxpcut;
	
	double prot_lowcut  = pid.BB_Prot_mindEdxcut;
	double prot_maxpcut = pid.BB_Prot_maxpcut;
	
	TLine *BB_Pion_maxpcut  = new TLine(pion_maxpcut,0.1,pion_maxpcut,2); 
	
	TLine *BB_Kaon_lowcut  = new TLine(0.6,kaon_lowcut,kaon_maxpcut,kaon_lowcut); 
	TLine *BB_Kaon_maxpcut = new TLine(kaon_maxpcut,kaon_lowcut,kaon_maxpcut,4); 
	
	TLine *BB_Prot_lowcut  = new TLine(1.1,prot_lowcut,prot_maxpcut,prot_lowcut); 
	TLine *BB_Prot_maxpcut = new TLine(prot_maxpcut,prot_lowcut,prot_maxpcut,4); 
	
	
	BB_Pion_maxpcut->SetLineColor(kMagenta);
	
	BB_Prot_lowcut->SetLineColor(kBlack);
	BB_Prot_maxpcut->SetLineColor(kBlack);
	
	BB_Kaon_lowcut->SetLineColor(kBlue);
	BB_Kaon_maxpcut->SetLineColor(kBlue);
	
	dEdxvsP->Draw("colz");
	
	BB_Pion_hig.Draw("same");
	BB_Kaon_low.Draw("same");
	BB_Kaon_hig.Draw("same");
	BB_Prot_low.Draw("same");
	BB_Prot_hig.Draw("same");
	
	BB_Pion_maxpcut->Draw("same");
	
	BB_Prot_lowcut->Draw("same");
	BB_Prot_maxpcut->Draw("same");
	
	BB_Kaon_lowcut->Draw("same");
	BB_Kaon_maxpcut->Draw("same");
	
	c.SaveAs(figurename.c_str());
};


void makedEdxvspFigloglog(TH2D* dEdxvsP, std::string PIDconfig, std::string figurename)
{
	TF1 BB_Pion_low ("BB_Pion_low_fcn" , BBcurve1, pminlin, pmaxlin, 3);
	TF1 BB_Pion_hig ("BB_Pion_high_fcn", BBcurve1, pminlin, pmaxlin, 3);
	TF1 BB_Kaon_low ("BB_Kaon_low_fcn" , BBcurve1, pminlin, pmaxlin, 3);
	TF1 BB_Kaon_hig ("BB_Kaon_high_fcn", BBcurve1, pminlin, pmaxlin, 3);
	TF1 BB_Prot_low ("BB_Prot_low_fcn" , BBcurve1, pminlin, pmaxlin, 3);
	TF1 BB_Prot_hig ("BB_Prot_high_fcn", BBcurve1, pminlin, pmaxlin, 3);

	PIDUtil pid;
	pid.ReadInConfig( PIDconfig);

	// Debuggg 
	std::cerr << "hello " << std::endl;
	
	BB_Pion_low.SetParameters(pid.BB_Pion_low_par[0], pid.BB_Pion_low_par[1], pid.BB_Pion_low_par[2]);
	BB_Pion_hig.SetParameters(pid.BB_Pion_hig_par[0], pid.BB_Pion_hig_par[1], pid.BB_Pion_hig_par[2]);
	BB_Kaon_low.SetParameters(pid.BB_Kaon_low_par[0], pid.BB_Kaon_low_par[1], pid.BB_Kaon_low_par[2]);
	BB_Kaon_hig.SetParameters(pid.BB_Kaon_hig_par[0], pid.BB_Kaon_hig_par[1], pid.BB_Kaon_hig_par[2]);
	BB_Prot_low.SetParameters(pid.BB_Prot_low_par[0], pid.BB_Prot_low_par[1], pid.BB_Prot_low_par[2]);
	BB_Prot_hig.SetParameters(pid.BB_Prot_hig_par[0], pid.BB_Prot_hig_par[1], pid.BB_Prot_hig_par[2]);

	BB_Pion_hig.SetLineColor(kMagenta);
	BB_Kaon_low.SetLineColor(kBlue);
	BB_Kaon_hig.SetLineColor(kBlue);
	BB_Prot_low.SetLineColor(kBlack);
	BB_Prot_hig.SetLineColor(kBlack);

	TCanvas c("dEdxvsP","dEdxvsP", 1024, 768);
	c.SetLogx(1);
	c.SetLogy(1);
	c.SetLogz(1);

	gStyle->SetOptStat(0);
	dEdxvsP->GetXaxis()->SetRangeUser(pminlin,pmaxlin);
	dEdxvsP->GetYaxis()->SetRangeUser(dEdxminlog,dEdxmaxlog);
	dEdxvsP->GetXaxis()->SetTitle("p [GeV/c]");

	double pion_maxpcut  = pid.BB_Pion_maxpcut;
	
	double kaon_lowcut  = pid.BB_Kaon_mindEdxcut;
	double kaon_maxpcut = pid.BB_Kaon_maxpcut;
	
	double prot_lowcut  = pid.BB_Prot_mindEdxcut;
	double prot_maxpcut = pid.BB_Prot_maxpcut;
	
	TLine *BB_Pion_maxpcut  = new TLine(pion_maxpcut,0.1,pion_maxpcut,2); 

	TLine *BB_Kaon_lowcut  = new TLine(0.6,kaon_lowcut,kaon_maxpcut,kaon_lowcut); 
	TLine *BB_Kaon_maxpcut = new TLine(kaon_maxpcut,kaon_lowcut,kaon_maxpcut,4); 
	
	TLine *BB_Prot_lowcut  = new TLine(1.1,prot_lowcut,prot_maxpcut,prot_lowcut); 
	TLine *BB_Prot_maxpcut = new TLine(prot_maxpcut,prot_lowcut,prot_maxpcut,4); 

	BB_Pion_maxpcut->SetLineColor(kMagenta);
	
	BB_Prot_lowcut->SetLineColor(kBlack);
	BB_Prot_maxpcut->SetLineColor(kBlack);
	
	BB_Kaon_lowcut->SetLineColor(kBlue);
	BB_Kaon_maxpcut->SetLineColor(kBlue);
	
	
	dEdxvsP->Draw("colz");
	
	BB_Pion_hig.Draw("same");
	BB_Kaon_low.Draw("same");
	BB_Kaon_hig.Draw("same");
	BB_Prot_low.Draw("same");
	BB_Prot_hig.Draw("same");
	
	
	BB_Pion_maxpcut->Draw("same");
	
	BB_Prot_lowcut->Draw("same");
	BB_Prot_maxpcut->Draw("same");
	
	BB_Kaon_lowcut->Draw("same");
	BB_Kaon_maxpcut->Draw("same");
	
	c.SaveAs(figurename.c_str());
	
}

////////////////////////////
// === class dEdxMaps === //
////////////////////////////

// Constructor
dEdxMaps::dEdxMaps( const char tag[])
{
 // dEdxvsp map
 dEdxvspAll = new TH2D (Form("%s - dEdxVsPAll", tag),";p(GeV/c);dE/dx",npBins,pMin,pMax,ndEdxBins,dEdxMin,dEdxMax);

 for(int iPID = 0; iPID < nPIDBins; iPID++)
 {
 dEdxvspPID[iPID] = new TH2D (Form("%s dEdxVsP PID %d", tag, iPID), Form("dEdxVsP %d ;p(GeV/c);dE/dx", iPID ),npBins,pMin,pMax,ndEdxBins,dEdxMin,dEdxMax);
 }
}

dEdxMaps::~dEdxMaps()
{};

void dEdxMaps::Fill(int PID, double p, double dedx)
{
	dEdxvspAll->Fill(p,dedx);
	if ( PID != 99)
   { dEdxvspPID[PID]->Fill(p,dedx); }	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////
// -- PIDStudy -- //
////////////////////

PIDStudy::PIDStudy( )
{

	nPBins_lin = 300;	
	ndEdxBins_lin = 300;
	
	PMin_lin = 0.15;
	PMax_lin = 2.0;

	dEdxMin_lin = 0.1;
	dEdxMax_lin = 50;

	   nPBins_log = 300;	
	ndEdxBins_log = 100;

	PMin_log = 0.15;
	PMax_log = 2.0;

	dEdxMin_log =  0.1;
	dEdxMax_log = 50;

   PBinWidth_lin = (PMax_lin-PMin_lin)/nPBins_lin;

	// -- dEdxDistr -- //
	ndEdxDistrBins_lin = 300;
	dEdxDistrMin_lin = 0.1;
	dEdxDistrMax_lin = 20;

	ndEdxDistrBins_log = 300;
	dEdxDistrMin_log = 0.1;
	dEdxDistrMax_log = 20;

	// Debuggg 
	std::cerr << "hallo " << std::endl;
 	l10 = TMath::Log(10);

   pBins_log    = new float [nPBins_log+1];
   dEdxBins_log = new float [ndEdxBins_log+1];
   dEdxDistrBins_log = new float [ndEdxDistrBins_log+1];

	double dplog    = ( TMath::Log(PMax_log)    - TMath::Log(PMin_log)   )/nPBins_log/l10;
	double ddEdxlog = ( TMath::Log(dEdxMax_log) - TMath::Log(dEdxMin_log) )/ndEdxBins_log/l10;
	double ddEdxDistrlog = ( TMath::Log(dEdxDistrMax_log) - TMath::Log(dEdxDistrMin_log) )/ndEdxDistrBins_log/l10;
	
	for (int i=0; i <= nPBins_log; i++)
	{ pBins_log[i] = TMath::Exp(l10*(i*dplog + TMath::Log(PMin_log)/l10)); }
	
	for (int i=0; i <= ndEdxBins_log; i++)
	{ dEdxBins_log[i] = TMath::Exp(l10*(i*ddEdxlog+ TMath::Log(dEdxMin_log)/l10)); }

	for (int i=0; i <= ndEdxDistrBins_log; i++)
	{ dEdxDistrBins_log[i] = TMath::Exp(l10*(i*ddEdxDistrlog+ TMath::Log(dEdxDistrMin_log)/l10)); }
}


void PIDStudy::Setup( )
{

	dEdxvsPMap_lin = new TH2D *[nMultiplicityBins]; 
	dEdxvsPMap_log = new TH2D *[nMultiplicityBins]; 
	dEdxDistr_lin 	= new TH1D**[nMultiplicityBins];
	dEdxDistr_log 	= new TH1D**[nMultiplicityBins];
	dEdxDistr_lin_Fit = new TF1 **[nMultiplicityBins];
	dEdxDistr_log_Fit = new TF1 **[nMultiplicityBins];

	for (int multBin=0; multBin < nMultiplicityBins; multBin++)
	{
   	int mult1 = multiplicity_Ana(multBin, 0, nMultiplicityBins);
		int mult2 = multiplicity_Ana(multBin, 1, nMultiplicityBins);

		dEdxvsPMap_lin[multBin] = NULL;
		dEdxvsPMap_log[multBin] = NULL;

		dEdxvsPMap_lin[multBin] = new TH2D (Form("dEdxVsP_lin-lin_multBin_[%03d-%03d]", mult1, mult2),";p(GeV/c);dE/dx [MeV/cm]", nPBins_lin, PMin_lin, PMax_lin, ndEdxBins_lin, dEdxMin_lin, dEdxMax_lin);
 		dEdxvsPMap_log[multBin] = new TH2D (Form("dEdxVsP_log-log_multBin_[%03d-%03d]", mult1, mult2),";p(GeV/c);dE/dx [MeV/cm]", nPBins_log, pBins_log, ndEdxBins_log, dEdxBins_log);

		dEdxDistr_lin[multBin] = new TH1D*[nPBins_lin];
		dEdxDistr_log[multBin] = new TH1D*[nPBins_lin];
		
			for (int PBin=0; PBin < nPBins_lin; PBin++)
			{	
				float p1 = PMin_lin + PBin*PBinWidth_lin;
				float p2 = PMin_lin + (PBin+1)*PBinWidth_lin;

				dEdxDistr_lin[multBin][PBin] = new TH1D (Form("dEdxDistr_lin_multBin_[%03d-%03d]_pBin_[%.2f-%.2f]", mult1, mult2, p1, p2 ), "Entries;dE/dx [MeV/cm];", ndEdxDistrBins_lin, dEdxDistrMin_lin, dEdxDistrMax_lin);
				dEdxDistr_log[multBin][PBin] = new TH1D (Form("dEdxDistr_log_multBin_[%03d-%03d]_pBin_[%.2f-%.2f]", mult1, mult2, p1, p2 ), "Entries;dE/dx [MeV/cm];", ndEdxDistrBins_log, dEdxDistrBins_log);
			}
			
	}
}

void PIDStudy::SetupInput( )
{

	pid = new PIDUtil();
	pid->ReadInConfig(PIDconfig);

	f_inp = NULL;
	std::cout << "f_inp: " << f_inp << std::endl;
	f_inp = new TFile( Form("%s", fname_inp.c_str()), "READ");
	std::cout << "f_inp: " << f_inp << std::endl;

	f_inp->cd();

	dEdxvsPMap_lin = new TH2D *[nMultiplicityBins]; 
	dEdxvsPMap_log = new TH2D *[nMultiplicityBins]; 
	dEdxDistr_lin 	= new TH1D**[nMultiplicityBins];
	dEdxDistr_log 	= new TH1D**[nMultiplicityBins];
	dEdxDistr_lin_Fit = new TF1 **[nMultiplicityBins];
	dEdxDistr_log_Fit = new TF1 **[nMultiplicityBins];

	for (int multBin=0; multBin < nMultiplicityBins; multBin++)
	{
   	int mult1 = multiplicity_Ana(multBin, 0, nMultiplicityBins);
		int mult2 = multiplicity_Ana(multBin, 1, nMultiplicityBins);

		dEdxvsPMap_lin[multBin] = NULL;
		dEdxvsPMap_log[multBin] = NULL;

		dEdxvsPMap_lin[multBin] = (TH2D*)f_inp->Get(Form("dEdxVsP_lin-lin_multBin_[%03d-%03d]", mult1, mult2));
 		dEdxvsPMap_log[multBin] = (TH2D*)f_inp->Get(Form("dEdxVsP_log-log_multBin_[%03d-%03d]", mult1, mult2));
		dEdxDistr_lin[multBin] = new TH1D*[nPBins_lin];
		dEdxDistr_log[multBin] = new TH1D*[nPBins_log];

		dEdxDistr_lin_Fit[multBin] = new TF1 *[nPBins_lin];
		dEdxDistr_log_Fit[multBin] = new TF1 *[nPBins_log];
		
			for (int PBin=0; PBin < nPBins_lin; PBin++)
			{	
				float p1 = PMin_lin + PBin*PBinWidth_lin;
				float p2 = PMin_lin + (PBin+1)*PBinWidth_lin;

				dEdxDistr_lin[multBin][PBin] = (TH1D*)f_inp->Get(Form("dEdxDistr_lin_multBin_[%03d-%03d]_pBin_[%.2f-%.2f]", mult1, mult2, p1, p2 ));
				dEdxDistr_log[multBin][PBin] = (TH1D*)f_inp->Get(Form("dEdxDistr_log_multBin_[%03d-%03d]_pBin_[%.2f-%.2f]", mult1, mult2, p1, p2 ));

				dEdxDistr_lin_Fit[multBin][PBin] = new TF1(Form("dEdxDistr_lin_Fit[%d][%d]", multBin, PBin), "gaus(0)+gaus(3)+gaus(6)");
				dEdxDistr_log_Fit[multBin][PBin] = new TF1(Form("dEdxDistr_log_Fit[%d][%d]", multBin, PBin), "gaus(0)+gaus(3)+gaus(6)");
			}
			
	}
}


int PIDStudy::GetpBin(float p)
{
	if ( (PMin_lin <= p ) && (p < PMax_lin) )
	{
	int pBin = floor( (p - PMin_lin)/PBinWidth_lin);
	return pBin;
	}
	else
	{
	return -1;
	}
}

void PIDStudy::SetupOut()
{
	f_out = new TFile("PIDStudy.root","RECREATE");
	f_out->cd();
}

void PIDStudy::Write()
{
	f_out->Write();
	f_out->Close();
}


void PIDStudy::makeFigdEdxvsPMap()
{
	for (int multBin = 0; multBin < nMultiplicityBins; multBin++)
	{

   int mult1 = multiplicity_Ana(multBin, 0, nMultiplicityBins);
	int mult2 = multiplicity_Ana(multBin, 1, nMultiplicityBins);

	{
	TF1 BB_Pion_low ("BB_Pion_low_fcn" , BBcurve1, PMin_log, PMax_log, 3);
	TF1 BB_Pion_hig ("BB_Pion_high_fcn", BBcurve1, PMin_log, PMax_log, 3);
	TF1 BB_Kaon_low ("BB_Kaon_low_fcn" , BBcurve1, PMin_log, PMax_log, 3);
	TF1 BB_Kaon_hig ("BB_Kaon_high_fcn", BBcurve1, PMin_log, PMax_log, 3);
	TF1 BB_Prot_low ("BB_Prot_low_fcn" , BBcurve1, PMin_log, PMax_log, 3);
	TF1 BB_Prot_hig ("BB_Prot_high_fcn", BBcurve1, PMin_log, PMax_log, 3);

	BB_Pion_low.SetParameters(pid->BB_Pion_low_par[0], pid->BB_Pion_low_par[1], pid->BB_Pion_low_par[2]);
	BB_Pion_hig.SetParameters(pid->BB_Pion_hig_par[0], pid->BB_Pion_hig_par[1], pid->BB_Pion_hig_par[2]);
	BB_Kaon_low.SetParameters(pid->BB_Kaon_low_par[0], pid->BB_Kaon_low_par[1], pid->BB_Kaon_low_par[2]);
	BB_Kaon_hig.SetParameters(pid->BB_Kaon_hig_par[0], pid->BB_Kaon_hig_par[1], pid->BB_Kaon_hig_par[2]);
	BB_Prot_low.SetParameters(pid->BB_Prot_low_par[0], pid->BB_Prot_low_par[1], pid->BB_Prot_low_par[2]);
	BB_Prot_hig.SetParameters(pid->BB_Prot_hig_par[0], pid->BB_Prot_hig_par[1], pid->BB_Prot_hig_par[2]);

	BB_Pion_hig.SetLineColor(kMagenta);
	BB_Kaon_low.SetLineColor(kBlue);
	BB_Kaon_hig.SetLineColor(kBlue);
	BB_Prot_low.SetLineColor(kBlack);
	BB_Prot_hig.SetLineColor(kBlack);

	TCanvas c("dEdxvsP","dEdxvsP", 1024, 768);
	c.SetLogx(1);
	c.SetLogy(1);
	c.SetLogz(1);

	gStyle->SetOptStat(0);
	dEdxvsPMap_log[multBin]->GetXaxis()->SetRangeUser(PMin_log,PMax_log);
	dEdxvsPMap_log[multBin]->GetYaxis()->SetRangeUser(dEdxMin_log,dEdxMax_log);
	dEdxvsPMap_log[multBin]->GetXaxis()->SetTitle("p [GeV/c]");

	double pion_maxpcut  = pid->BB_Pion_maxpcut;
	
	double kaon_lowcut  = pid->BB_Kaon_mindEdxcut;
	double kaon_maxpcut = pid->BB_Kaon_maxpcut;
	
	double prot_lowcut  = pid->BB_Prot_mindEdxcut;
	double prot_maxpcut = pid->BB_Prot_maxpcut;

	TLine *BB_Pion_maxpcut  = new TLine(pion_maxpcut,0.1,pion_maxpcut,2); 

	TLine *BB_Kaon_lowcut  = new TLine(0.6,kaon_lowcut,kaon_maxpcut,kaon_lowcut); 
	TLine *BB_Kaon_maxpcut = new TLine(kaon_maxpcut,kaon_lowcut,kaon_maxpcut,4); 
	
	TLine *BB_Prot_lowcut  = new TLine(1.1,prot_lowcut,prot_maxpcut,prot_lowcut); 
	TLine *BB_Prot_maxpcut = new TLine(prot_maxpcut,prot_lowcut,prot_maxpcut,4); 

	BB_Pion_maxpcut->SetLineColor(kMagenta);
	
	BB_Prot_lowcut->SetLineColor(kBlack);
	BB_Prot_maxpcut->SetLineColor(kBlack);
	
	BB_Kaon_lowcut->SetLineColor(kBlue);
	BB_Kaon_maxpcut->SetLineColor(kBlue);
	
	dEdxvsPMap_log[multBin]->Draw("colz");
	
	BB_Pion_hig.Draw("same");
	BB_Kaon_low.Draw("same");
	BB_Kaon_hig.Draw("same");
	BB_Prot_low.Draw("same");
	BB_Prot_hig.Draw("same");
	
	BB_Pion_maxpcut->Draw("same");
	
	BB_Prot_lowcut->Draw("same");
	BB_Prot_maxpcut->Draw("same");
	
	BB_Kaon_lowcut->Draw("same");
	BB_Kaon_maxpcut->Draw("same");
	
 	std::string FigBase = Form("dEdxvspLog_mult_%03d-%03d", mult1, mult2);
 	std::string FigPNG = FigBase+".png";
 	std::string FigPDF = FigBase+".pdf";

	c.SaveAs( FigPNG.c_str());
	c.SaveAs( FigPDF.c_str());
	}


	}
}

void PIDStudy::makeFigdEdxDistr()
{

	gStyle->SetOptStat(0);

	for (int multBin = 0; multBin < nMultiplicityBins; multBin++)
	{

   int mult1 = multiplicity_Ana(multBin, 0, nMultiplicityBins);
	int mult2 = multiplicity_Ana(multBin, 1, nMultiplicityBins);


		for (int PBin=0; PBin < nPBins_lin; PBin++)
		{	

			float p1 = PMin_lin + PBin*PBinWidth_lin;
			float p2 = PMin_lin + (PBin+1)*PBinWidth_lin;

			float p_avg = (p1+p2)/2.;

			// Bethe-Bloch cut values in this 'p' bin.
			float BB_Pion_mindEdxcut = pid->BB_Pion_mindEdxcut;
			float BB_Pion_hig = pid->BBcurve(&p_avg, pid->BB_Pion_hig_par);

			float BB_Kaon_low = pid->BBcurve(&p_avg, pid->BB_Kaon_low_par);
			float BB_Kaon_hig = pid->BBcurve(&p_avg, pid->BB_Kaon_hig_par);
			float BB_Kaon_mindEdxcut = pid->BB_Kaon_mindEdxcut;

			float BB_Prot_low = pid->BBcurve(&p_avg, pid->BB_Prot_low_par);
			float BB_Prot_hig = pid->BBcurve(&p_avg, pid->BB_Prot_hig_par);
			float BB_Prot_mindEdxcut = pid->BB_Prot_mindEdxcut;

			int BB_Pion_mindEdxcut_Bin = dEdxDistr_log[multBin][PBin]->GetXaxis()->FindBin( BB_Pion_mindEdxcut );
			int BB_Pion_hig_Bin 			= dEdxDistr_log[multBin][PBin]->GetXaxis()->FindBin( BB_Pion_hig );

			int BB_Kaon_mindEdxcut_Bin = dEdxDistr_log[multBin][PBin]->GetXaxis()->FindBin( BB_Kaon_mindEdxcut );
			int BB_Kaon_low_Bin 			= dEdxDistr_log[multBin][PBin]->GetXaxis()->FindBin( BB_Kaon_low );
			int BB_Kaon_hig_Bin 			= dEdxDistr_log[multBin][PBin]->GetXaxis()->FindBin( BB_Kaon_hig );

			int BB_Prot_mindEdxcut_Bin = dEdxDistr_log[multBin][PBin]->GetXaxis()->FindBin( BB_Prot_mindEdxcut );
			int BB_Prot_low_Bin 			= dEdxDistr_log[multBin][PBin]->GetXaxis()->FindBin( BB_Prot_low );
			int BB_Prot_hig_Bin 			= dEdxDistr_log[multBin][PBin]->GetXaxis()->FindBin( BB_Prot_hig );

			double Pion_Entries = dEdxDistr_log[multBin][PBin]->Integral(BB_Pion_mindEdxcut_Bin, BB_Pion_hig_Bin);
			double Kaon_Entries = dEdxDistr_log[multBin][PBin]->Integral(BB_Kaon_low_Bin, BB_Kaon_hig_Bin);
			double Prot_Entries = dEdxDistr_log[multBin][PBin]->Integral(BB_Prot_low_Bin, BB_Prot_hig_Bin);
			double Kaon_Entries_mindEdxcut = dEdxDistr_log[multBin][PBin]->Integral(BB_Kaon_mindEdxcut_Bin, BB_Kaon_hig_Bin);
			double Prot_Entries_mindEdxcut = dEdxDistr_log[multBin][PBin]->Integral(BB_Prot_mindEdxcut_Bin, BB_Prot_hig_Bin);

			double Prot2PionRatio = Prot_Entries/Pion_Entries;
			double Kaon2PionRatio = Kaon_Entries/Pion_Entries;
			double Prot2PionRatio_mindExcut = Prot_Entries_mindEdxcut/Pion_Entries;
			double Kaon2PionRatio_mindExcut = Kaon_Entries_mindEdxcut/Pion_Entries;

			double Prot2PionRatio_Err = Prot2PionRatio*sqrt(1/Prot_Entries+1/Pion_Entries);
			double Kaon2PionRatio_Err = Kaon2PionRatio*sqrt(1/Kaon_Entries+1/Pion_Entries);
			double Prot2PionRatio_mindExcut_Err = Prot2PionRatio_mindExcut*sqrt(1/Prot_Entries_mindEdxcut+1/Pion_Entries);
			double Kaon2PionRatio_mindExcut_Err = Kaon2PionRatio_mindExcut*sqrt(1/Kaon_Entries_mindEdxcut+1/Pion_Entries);



			/////////////////////////////////////////////////////////////////
			{
			TCanvas canv("dEdxvsDistr",";;", 1024, 768);

			canv.SetLeftMargin(0.15);

			double EntryStat_Pion_TLatex_posx = 0.4;
			double EntryStat_Pion_TLatex_posy = 0.6;
			double EntryStat_Kaon_TLatex_posx = 0.4;
			double EntryStat_Kaon_TLatex_posy = 0.55;
			double EntryStat_Prot_TLatex_posx = 0.4;
			double EntryStat_Prot_TLatex_posy = 0.50;


			double RatioStat_Kaon2Pion_TLatex_posx = 0.6;
			double RatioStat_Kaon2Pion_TLatex_posy = 0.6;
			double RatioStat_Prot2Pion_TLatex_posx = 0.6;
			double RatioStat_Prot2Pion_TLatex_posy = 0.55;

			// Drawing
			dEdxDistr_log[multBin][PBin]->SetLineColor(kBlack);
			dEdxDistr_log[multBin][PBin]->SetMarkerColor(kBlack);
			dEdxDistr_log[multBin][PBin]->SetTitle("");
			// Biwidth scaling
			dEdxDistr_log[multBin][PBin]->Scale(1, "width");
			dEdxDistr_log[multBin][PBin]->GetYaxis()->SetTitle("Entries/bw.");
			dEdxDistr_log[multBin][PBin]->GetYaxis()->SetTitleOffset(1.6);
			dEdxDistr_log[multBin][PBin]->Draw("");
			double maxval = dEdxDistr_log[multBin][PBin]->GetBinContent(dEdxDistr_log[multBin][PBin]->GetMaximumBin());

			TLatex *EntryStat_Pion_TLatex;
			TLatex *EntryStat_Kaon_TLatex;
			TLatex *EntryStat_Prot_TLatex;
			TLatex *RatioStat_Kaon2Pion_TLatex;
			TLatex *RatioStat_Prot2Pion_TLatex;

			double scale = 0.4;
			TLine BB_Pion_mindEdxcut_line (BB_Pion_mindEdxcut,0.0,BB_Pion_mindEdxcut,0.5*maxval);
			TLine BB_Pion_hig_line (BB_Pion_hig,0.0,BB_Pion_hig,scale*maxval);
			TLine BB_Kaon_low_line (BB_Kaon_low,0.0,BB_Kaon_low,scale*maxval);
			TLine BB_Kaon_hig_line (BB_Kaon_hig,0.0,BB_Kaon_hig,scale*maxval);
			TLine BB_Prot_low_line (BB_Prot_low,0.0,BB_Prot_low,scale*maxval);
			TLine BB_Prot_hig_line (BB_Prot_hig,0.0,BB_Prot_hig,scale*maxval);
			TLine BB_Kaon_mindEdxcut_line (BB_Kaon_mindEdxcut,0.0,BB_Kaon_mindEdxcut,scale*maxval);
			TLine BB_Prot_mindEdxcut_line (BB_Prot_mindEdxcut,0.0,BB_Prot_mindEdxcut,scale*maxval);

			TLatex BB_Pion_hig_TLatex (BB_Pion_hig,scale*maxval,"#pi_{high}");
			TLatex BB_Kaon_low_TLatex (BB_Kaon_low,scale*maxval,"K_{low}");
			TLatex BB_Kaon_hig_TLatex (BB_Kaon_hig,scale*maxval,"K_{high}");
			TLatex BB_Prot_low_TLatex (BB_Prot_low,scale*maxval,"p_{low}");
			TLatex BB_Prot_hig_TLatex (BB_Prot_hig,scale*maxval,"p_{high}");

			TLatex BB_Pion_mindEdxcut_TLatex (BB_Pion_mindEdxcut,scale*maxval,"#pi_{min dE/dx}");
			TLatex BB_Kaon_mindEdxcut_TLatex (BB_Kaon_mindEdxcut,scale*maxval,"K_{min dE/dx}");
			TLatex BB_Prot_mindEdxcut_TLatex (BB_Prot_mindEdxcut,scale*maxval,"p_{min dE/dx}");

			// Kaon
			if ( p2 < 0.9 )
			{
				BB_Kaon_hig_line.Draw();
				BB_Kaon_hig_TLatex.Draw();

				std::string EntryStat_Kaon_TLatex_Str;
				std::string RatioStat_Kaon2Pion_TLatex_Str;

				if ( BB_Kaon_low < BB_Kaon_mindEdxcut )
				{
					EntryStat_Kaon_TLatex_Str = Form("N_{K} = %f",   Kaon_Entries_mindEdxcut);
					RatioStat_Kaon2Pion_TLatex_Str = Form("N_{K}/N_{#pi} = %f #pm %f", Kaon2PionRatio_mindExcut, Kaon2PionRatio_mindExcut_Err);
					BB_Kaon_mindEdxcut_line.Draw();
					BB_Kaon_mindEdxcut_TLatex.Draw();
				}
				else
				{
					EntryStat_Kaon_TLatex_Str = Form("N_{K} = %f",   Kaon_Entries);
					RatioStat_Kaon2Pion_TLatex_Str = Form("N_{K}/N_{#pi} = %f #pm %f", Kaon2PionRatio, Kaon2PionRatio_Err);
					BB_Kaon_low_line.Draw();
					BB_Kaon_low_TLatex.Draw();
				}

				EntryStat_Kaon_TLatex = new TLatex(EntryStat_Kaon_TLatex_posx, EntryStat_Kaon_TLatex_posy, EntryStat_Kaon_TLatex_Str.c_str());
				EntryStat_Kaon_TLatex->SetTextSize(0.03);
				EntryStat_Kaon_TLatex->SetNDC(kTRUE);

				RatioStat_Kaon2Pion_TLatex = new TLatex (RatioStat_Kaon2Pion_TLatex_posx, RatioStat_Kaon2Pion_TLatex_posy, RatioStat_Kaon2Pion_TLatex_Str.c_str());
				RatioStat_Kaon2Pion_TLatex->SetTextSize(0.03);
				RatioStat_Kaon2Pion_TLatex->SetNDC(kTRUE);

				EntryStat_Kaon_TLatex->Draw();
				RatioStat_Kaon2Pion_TLatex->Draw();
			}

			// Pion
			if ( p2 < 1.0 )
			{
				std::string EntryStat_Pion_TLatex_Str = Form("N_{#pi} = %f", Pion_Entries);
				BB_Pion_hig_line.Draw();
				BB_Pion_hig_TLatex.Draw();
				BB_Pion_mindEdxcut_line.Draw();
				BB_Pion_mindEdxcut_TLatex.Draw();
				EntryStat_Pion_TLatex = new TLatex(EntryStat_Pion_TLatex_posx, EntryStat_Pion_TLatex_posy, EntryStat_Pion_TLatex_Str.c_str());
				EntryStat_Pion_TLatex->SetTextSize(0.03);
				EntryStat_Pion_TLatex->SetNDC(kTRUE);
				EntryStat_Pion_TLatex->Draw();

			}

			// Prot
			if ( p2 < 1.6 )
			{

				BB_Prot_hig_line.Draw();
				BB_Prot_hig_TLatex.Draw();

				std::string RatioStat_Prot2Pion_TLatex_Str;
				std::string EntryStat_Prot_TLatex_Str;

				if ( BB_Prot_low < BB_Prot_mindEdxcut )
				{
					RatioStat_Prot2Pion_TLatex_Str = Form("N_{p}/N_{#pi} = %f #pm %f", Prot2PionRatio_mindExcut, Prot2PionRatio_mindExcut_Err);
					EntryStat_Prot_TLatex_Str = Form("N_{p} = %f",   Prot_Entries_mindEdxcut);
					BB_Prot_mindEdxcut_line.Draw();
					BB_Prot_mindEdxcut_TLatex.Draw();
				}
				else
				{
					RatioStat_Prot2Pion_TLatex_Str = Form("N_{p}/N_{#pi} = %f #pm %f", Prot2PionRatio, Prot2PionRatio_Err);
					EntryStat_Prot_TLatex_Str = Form("N_{p} = %f",   Prot_Entries);
					BB_Prot_low_line.Draw();
					BB_Prot_low_TLatex.Draw();
				}

			EntryStat_Prot_TLatex = new TLatex (EntryStat_Prot_TLatex_posx, EntryStat_Prot_TLatex_posy, EntryStat_Prot_TLatex_Str.c_str());
			EntryStat_Prot_TLatex->SetTextSize(0.03);
			EntryStat_Prot_TLatex->SetNDC(kTRUE);

			RatioStat_Prot2Pion_TLatex = new TLatex (RatioStat_Prot2Pion_TLatex_posx, RatioStat_Prot2Pion_TLatex_posy, RatioStat_Prot2Pion_TLatex_Str.c_str());
			RatioStat_Prot2Pion_TLatex->SetTextSize(0.03);
			RatioStat_Prot2Pion_TLatex->SetNDC(kTRUE);

			EntryStat_Prot_TLatex->Draw();
			if ( p2 < 1.0)
			{RatioStat_Prot2Pion_TLatex->Draw();	}
	
			}

			BB_Pion_hig_line.SetLineColor(kRed);
			BB_Kaon_low_line.SetLineColor(kGreen);
			BB_Kaon_hig_line.SetLineColor(kGreen);
			BB_Prot_low_line.SetLineColor(kBlue);
			BB_Prot_hig_line.SetLineColor(kBlue);
			BB_Pion_mindEdxcut_line.SetLineColor(kRed);
			BB_Kaon_mindEdxcut_line.SetLineColor(kGreen);
			BB_Prot_mindEdxcut_line.SetLineColor(kBlue);

			BB_Pion_hig_TLatex.SetTextColor(kRed);
			BB_Kaon_low_TLatex.SetTextColor(kGreen);
			BB_Kaon_hig_TLatex.SetTextColor(kGreen);
			BB_Prot_low_TLatex.SetTextColor(kBlue);
			BB_Prot_hig_TLatex.SetTextColor(kBlue);
			BB_Pion_mindEdxcut_TLatex.SetTextColor(kRed);
			BB_Kaon_mindEdxcut_TLatex.SetTextColor(kGreen);
			BB_Prot_mindEdxcut_TLatex.SetTextColor(kBlue);

			BB_Pion_hig_TLatex.SetTextSize(0.02);
			BB_Kaon_low_TLatex.SetTextSize(0.02);
			BB_Kaon_hig_TLatex.SetTextSize(0.02);
			BB_Prot_low_TLatex.SetTextSize(0.02);
			BB_Prot_hig_TLatex.SetTextSize(0.02);
			BB_Pion_mindEdxcut_TLatex.SetTextSize(0.02);
			BB_Kaon_mindEdxcut_TLatex.SetTextSize(0.02);
			BB_Prot_mindEdxcut_TLatex.SetTextSize(0.02);

			BB_Pion_hig_line.SetLineStyle(8);
			BB_Kaon_low_line.SetLineStyle(8);
			BB_Kaon_hig_line.SetLineStyle(8);
			BB_Prot_low_line.SetLineStyle(8);
			BB_Prot_hig_line.SetLineStyle(8);
			BB_Pion_mindEdxcut_line.SetLineStyle(8);
			BB_Kaon_mindEdxcut_line.SetLineStyle(8);
			BB_Prot_mindEdxcut_line.SetLineStyle(8);

			BB_Pion_hig_line.SetLineWidth(3);
			BB_Kaon_low_line.SetLineWidth(3);
			BB_Kaon_hig_line.SetLineWidth(3);
			BB_Prot_low_line.SetLineWidth(3);
			BB_Prot_hig_line.SetLineWidth(3);
			BB_Pion_mindEdxcut_line.SetLineWidth(3);
			BB_Kaon_mindEdxcut_line.SetLineWidth(3);
			BB_Prot_mindEdxcut_line.SetLineWidth(3);

			// Fitting
			//dEdxDistr_log[multBin][PBin]->Fit( dEdxDistr_log_Fit[multBin][PBin]);
			//

			double BinStat_TLatex_posx = 0.5;
			double BinStat_TLatex_posy = 0.8;
			std::string BinStat_TLatex_Str = Form("#splitline{%d #leq N_{trk}^{off} #leq %d}{%.2f < p < %.2f GeV/c}", mult1, mult2 ,p1, p2);
			TLatex BinStat_TLatex (BinStat_TLatex_posx, BinStat_TLatex_posy, BinStat_TLatex_Str.c_str());
			BinStat_TLatex.SetTextSize(0.03);
			BinStat_TLatex.SetNDC(kTRUE);
			BinStat_TLatex.Draw();

			std::string FigBase = Form("dEdxDistr_log_mult_%03d-%03d_p_%.2f-%.2f", mult1, mult2, p1, p2);
 			std::string FigPNG = FigBase+".png";
 			std::string FigPDF = FigBase+".pdf";

			canv.SaveAs( FigPNG.c_str());
			canv.SaveAs( FigPDF.c_str());
			}

//			{
//			TCanvas canv("dEdxvsDistr",";;", 1024, 768);
//
//			dEdxDistr_lin[multBin][PBin]->Draw("");
//
//			std::string FigBase = Form("dEdxDistr_lin_mult_%03d-%03d_p_%.2f-%.2f", mult1, mult2, p1, p2);
// 			std::string FigPNG = FigBase+".png";
// 			std::string FigPDF = FigBase+".pdf";
//
//			canv.SaveAs( FigPNG.c_str());
//			canv.SaveAs( FigPDF.c_str());
//			}

		}

	}
}

void PIDStudy::InitializeFits()
{

	for (int multBin = 0; multBin < nMultiplicityBins; multBin++)
	for (int PBin=0; PBin < nPBins_lin; PBin++)
	{	


		TF1 pion("pion", "gaus(0)", 2.0, 4.0);
		pion.SetParameter(0,10000);
		pion.SetParameter(1,2.8);
		pion.SetParameter(2,0.2);

		TF1 kaon("kaon", "gaus(0)", 3.0, 6.0);
		kaon.SetParameter(0,2000);
		kaon.SetParameter(1,4);
		kaon.SetParameter(2,0.2);

		TF1 prot("prot", "gaus(0)", 5.0, 8.0);
		prot.SetParameter(0,1000);
		prot.SetParameter(1,7);
		prot.SetParameter(2,0.4);

		// "R" means only using fit range.
		//dEdxDistr_log[multBin][PBin]->Fit(&pion, "R");
		//dEdxDistr_log[multBin][PBin]->Fit(&kaon, "R");
		//dEdxDistr_log[multBin][PBin]->Fit(&prot, "R");

		double pion_amp = pion.GetParameter(0);
		double pion_pos = pion.GetParameter(1);
		double pion_sig = pion.GetParameter(2);

		double kaon_amp = kaon.GetParameter(0);
		double kaon_pos = kaon.GetParameter(1);
		double kaon_sig = kaon.GetParameter(2);

		double prot_amp = prot.GetParameter(0);
		double prot_pos = prot.GetParameter(1);
		double prot_sig = prot.GetParameter(2);

 	   // Pion
		dEdxDistr_log_Fit[multBin][PBin]->SetParameter(0,pion_amp);
		dEdxDistr_log_Fit[multBin][PBin]->SetParameter(1,pion_pos);
		dEdxDistr_log_Fit[multBin][PBin]->SetParameter(2,pion_sig);

		dEdxDistr_log_Fit[multBin][PBin]->SetParameter(3,kaon_amp);
		dEdxDistr_log_Fit[multBin][PBin]->SetParameter(4,kaon_pos);
		dEdxDistr_log_Fit[multBin][PBin]->SetParameter(5,kaon_sig);

		dEdxDistr_log_Fit[multBin][PBin]->SetParameter(6,prot_amp);
		dEdxDistr_log_Fit[multBin][PBin]->SetParameter(7,prot_pos);
		dEdxDistr_log_Fit[multBin][PBin]->SetParameter(8,prot_sig);
	}

}
