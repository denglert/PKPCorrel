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

  if(argc != 2)
  {
    std::cerr << "Usage: quickLook <.root file to be preprocessed>" << std::endl;
	 exit(1);
  }

 LogFile log;

 TString inpFilename     = argv[1];

// Open file
 TFile *f = TFile::Open(inpFilename);
 // TFile *f = new TFile(inpFilename, "READ");
 if ( f->IsZombie() ) {std::cerr << "Error opening file: " << inpFilename << std::endl; exit(-1);}
 else {std::cout << "File successfully opened." << std::endl;}

 //
const int npt = 29;
const double ptMin = 0.1;
const double ptMax = 3;
const double ptbw = (ptMax-ptMin)/npt;

const int neta = 48;
const double etaMin = -2.4;
const double etaMax =  2.4;
const double etabw = (etaMax-etaMin)/neta;

const int nphi = 70;
const double phiMin = -TMath::Pi();
const double phiMax =  TMath::Pi();
const double phibw = (phiMax-phiMin)/nphi;


  TH3D **havgcorr = Read_trkEff( f );

  for(int x = 1; x < npt  +1; x++)
  for(int y = 1; y < neta +1; y++)
  for(int z = 1; z < nphi +1; z++)
  {
	  double pt  = ptMin  + x*ptbw;
	  double eta = etaMin + y*etabw;
	  double phi = phiMin + z*phibw;

	  double value = havgcorr[3]->GetBinContent(x,y,z);
 	  log.Write(Form("%.3f %.2f %.2f : %.4f", pt, eta, phi, value));
  }

  log.Close();


}
