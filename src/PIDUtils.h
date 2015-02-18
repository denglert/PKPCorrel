#ifndef PIDUTILS_H
#define PIDUTILS_H
#include <cmath>
#include <TH2D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLine.h>
#include <fstream>
#include <string>

class dEdxMaps {
public :
   dEdxMaps(const char tag[]);
   ~dEdxMaps();

	// Variables
	TH2D *dEdxvspPID[4];
	TH2D *dEdxvspAll;

	// Functions
	void Fill(int PID, double p, double dedx);
	void PlotFigs(const char tag[]);
};

class PIDUtil {
public :
	
   PIDUtil( );
   ~PIDUtil();

	// Functions
	
	float BBcurve(float *x, const float *par);
	bool  isPion(float p, float dEdx);
	bool  isKaon(float p, float dEdx);
	bool  isProt(float p, float dEdx);

	// Variables
	float BB_Pion_low_par[3];
	float BB_Pion_hig_par[3];
	float BB_Pion_mindEdxcut;
	float BB_Pion_minpcut; 
	float BB_Pion_maxpcut;
	                        
	float BB_Kaon_low_par[3];
	float BB_Kaon_hig_par[3];
	float BB_Kaon_mindEdxcut;
	float BB_Kaon_maxpcut;
	                        
	float BB_Prot_low_par[3];
	float BB_Prot_hig_par[3];
	float BB_Prot_mindEdxcut;
	float BB_Prot_maxpcut;

	std::string configfile;

	int unIDcode;
	double etaMax;
	
	void ReadInConfig( std::string PIDconfigfile_str );

	int GetID(float p, float dEdx, float eta);
};

// Bethe-Bloch Curve function
double poly2nd(double *x, double *par);

extern const float BB_Pion_low_par[3];
extern const float BB_Pion_maxpcut;
extern const float BB_Pion_hig_par[3];
extern const float BB_Kaon_low_par[3];
extern const float BB_Kaon_hig_par[3];
extern const float BB_Kaon_mindEdxcut;
extern const float BB_Kaon_maxpcut;

extern const float BB_Prot_low_par[3];
extern const float BB_Prot_hig_par[3];
extern const float BB_Prot_mindEdxcut;
extern const float BB_Prot_maxpcut;

extern const double delta;

// PIDUtils parameters
extern const int nPIDBins;
extern const int npBins;
extern const double pMin;
extern const double pMax;
extern const int ndEdxBins;
extern const double dEdxMin;
extern const double dEdxMax;

extern const float asymmetry;
extern const float mindEdx;

/////////////////////////////
// PIDUtils functions

float BBcurve1c(float *x, const float *par);
double BBcurve1 (double *x, double *par);
int GetPID(float p, float dEdx, float eta);
int McPID2AnaPID ( int McPID, double eta);
bool isPion(float p, float dEdx);
bool isKaon(float p, float dEdx);
bool isProt(float p, float dEdx);
void makedEdxvspFiglinlin(TH2D* dEdxvsP, std::string PIDconfig, std::string figurename);
void makedEdxvspFigloglog(TH2D* dEdxvsP, std::string PIDconfig, std::string figurename);


#endif
