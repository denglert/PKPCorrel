#include "EvtAnalyzer.h"

void EvtAnalyzer::setupEvtAnaTree( TFile *f )
{
	  EvtAna = (TTree*)f->Get("hiEvtAnalyzer/HiTree");

     EvtAna->SetBranchAddress("hiNtracks", &hiNtracks, &b_hiNtracks);
     EvtAna->SetBranchAddress("vz", &vz, &b_vz);
}


void EvtAnalyzer::GetEntry( int iEv )
{
	EvtAna->GetEntry(iEv);
}

int EvtAnalyzer::gethiNtracks()
{
	return hiNtracks;
}

double EvtAnalyzer::getvz()
{
	return vz;
}
