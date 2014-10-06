#ifndef DATATYPE_h
#define DATATYPE_h

#include <iostream>

#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"
//#include "commonSetup.h"

enum collisionType { cPbPb, cPP, cPPb };

enum sampleType{
  kHIDATA, //0
  kHIMC,   //1
  kPPDATA, //2
  kPPMC,   //3
  kPADATA, //4
  kPAMC    //5
};

sampleType str2enumSampleTyp ( std::string str_sampletype )
{
  sampleType sType;		  
  if (str_sampletype == "kHIDATA") {sType = kHIDATA; return sType;}
  if (str_sampletype == "kHIMC"  ) {sType = kHIMC;   return sType;}
  if (str_sampletype == "kPPDATA") {sType = kPPDATA; return sType;}
  if (str_sampletype == "kPPMC"  ) {sType = kPPMC;   return sType;}  
  if (str_sampletype == "kPADATA") {sType = kPADATA; return sType;}
  if (str_sampletype == "kPAMC"  ) {sType = kPAMC;   return sType;}
};

Bool_t isMonteCarlo(sampleType sType = kHIDATA)
{
  if(sType == kHIMC || sType == kPPMC || sType == kPAMC) return true;
  else return false;
}


Bool_t isHI(sampleType sType = kHIDATA)
{
  if(sType == kHIDATA || sType == kHIMC) return true;
  else return false;
}


TString getSampleName ( sampleType colli)
{
  if (colli == kHIDATA) return "pbpbDATA";
  if (colli == kHIMC) return "pbpbMC";
  if (colli == kPPDATA) return "ppDATA";
  if (colli == kPPMC) return "ppMC";
  if (colli == kPADATA) return "ppbDATA";
  if (colli == kPAMC) return "ppbMC";
  return "NULL";
}

TString getSampleName ( int colli)
{
  if (colli == kHIDATA) return "pbpbDATA";
  if (colli == kHIMC) return "pbpbMC";
  if (colli == kPPDATA) return "ppDATA";
  if (colli == kPPMC) return "ppMC";
  if (colli == kPADATA) return "ppbDATA";
  if (colli == kPAMC) return "ppbMC";
  return "NULL";
}

collisionType getCType(sampleType sType)
{
  switch (sType)
    {
    case kPPDATA:
    case kPPMC:
      return cPP;
    case kPADATA:
    case kPAMC:
      return cPPb;
    case kHIDATA:
    case kHIMC:
      return cPbPb;
    }
  return cPbPb; //probably a bad guess
}

#endif
