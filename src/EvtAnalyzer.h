#ifndef EVENTANALYZER_H
#define EVENTANALYZER_H

#include <TTree.h>
#include <TFile.h>
#include <TBranch.h>

class EvtAnalyzer {
public :
   EvtAnalyzer(){};
   ~EvtAnalyzer(){};

	// TTree
	TTree *EvtAna;

	// Variables
   Int_t    hiNtracks;
   Float_t    vz;

	// Branches
   TBranch *b_hiNtracks;  
   TBranch *b_vz;  

	void setupEvtAnaTree( TFile *f );
	void GetEntry( int iEv );
	int gethiNtracks();
	double getvz();
};

#endif
