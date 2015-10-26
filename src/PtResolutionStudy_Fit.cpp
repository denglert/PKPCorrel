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
 ptres->tag = tag;
 ptres->OpenFile( inpFilename.c_str() );

 ////////////////////
 ptres->SetupForFit();

 ////////////////////
 
 ptres->Fit();
 ptres->makeFigPtRecPtSim();
 ptres->makeFigSigmaPtDep();


 ptres->SetupOutFile();
 ptres->WriteFitResultsToFile();

 //ptres->testRand();

 printf("Done.\n");

}
