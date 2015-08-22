#include "PtResolutionStudy.h"

int main( int argc, const char *argv[] )
{


  if(argc != 3)
  {
    std::cerr << "Usage: StudyMCinfo <MC sample> <tag> <nEvents> <PIDconfig>" << std::endl;
	 exit(1);
  }

 std::string inpFilename 	  = argv[1];
 std::string tag		        = argv[2];
 
 ///////////////
 // Open file //
 ///////////////
 
 PtRes *ptres = new PtRes();
 ptres->OpenFile( inpFilename.c_str() );
 ptres->SetupForFit();

 ////////////////////
 // Setting output //
 ////////////////////

// TFile *output = new TFile(Form("./PtResolutions_%s.root", tag.c_str() ),"RECREATE");
// output->cd();

 ptres->Fit();
 ptres->makeFigPtRecPtSim();

 //////////////////////
 //                  //
 // **** OUTPUT **** //
 //                  //
 //////////////////////
  
//  output->cd();
//  output->Write();
//  
//  output->Close();
//  delete output;

  printf("Done.\n");

}
