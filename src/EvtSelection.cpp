#include "EvtSelection.h"

void EvtSelection::setupSkimTree_pPb( TFile *f, bool isOLD )
{
	  SkimAna = (TTree*)f->Get("skimanalysis/HltTree");

	  if ( isOLD )
	  { SkimAna->SetBranchAddress("pPAcollisionEventSelection", &pPAcollisionEventSelectionPA, &b_pPAcollisionEventSelectionPA); }
	  else
	  { SkimAna->SetBranchAddress("pPAcollisionEventSelectionPA", &pPAcollisionEventSelectionPA, &b_pPAcollisionEventSelectionPA); 
	  }
     SkimAna->SetBranchAddress("pVertexFilterCutGplus", &pVertexFilterCutGplus, &b_pVertexFilterCutGplus);

}


int EvtSelection::GetEntries()
{
	return SkimAna->GetEntries();
}

bool EvtSelection::isGoodEv_pPb( int iEv )
{
	SkimAna->GetEntry(iEv);

	if ( pPAcollisionEventSelectionPA != 1 ) {return false;}
	if ( pVertexFilterCutGplus != 1 )        {return false;}

	return true;
}
