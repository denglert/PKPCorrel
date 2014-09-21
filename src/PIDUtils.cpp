#include "PIDUtils.h"

const int npBins 		= 300;
const double pMin 	= 0;
const double pMax 	= 3;
const int ndEdxBins 	= 300;
const double dEdxMin = 0;
const double dEdxMax = 30;

const double pminlog    = 0.1;
const double pmaxlog    = 2.0;
const double dEdxminlog = 0.1;
const double dEdxmaxlog = 20;
 
const double pminlin    = 0.1;
const double pmaxlin    = 2.0;
const double dEdxminlin = 0.1;
const double dEdxmaxlin = 20;

// PID Parameters settings
const float BB_Pion_low_par[3] = {2.35e-1, 0.61, 1.1e4};
const float BB_Pion_hig_par[3] = {0.29, 2.2, 0.00};
const float BB_Pion_mindEdxcut = 0.2;
const float BB_Pion_minpcut = 0.15;
const float BB_Pion_maxpcut = 1.0;

const float BB_Kaon_low_par[3] = {0.3, 2.2, 0.00};
const float BB_Kaon_hig_par[3] = {0.7, 2.5, 0.05};
const float BB_Kaon_mindEdxcut = 3.2;
const float BB_Kaon_maxpcut = 0.9;

const float BB_Prot_low_par[3] = {0.9, 2.5, 0.05};
const float BB_Prot_hig_par[3] = {2.4, 3.0, 0.15};
const float BB_Prot_mindEdxcut = 3.2;
const float BB_Prot_maxpcut = 1.6;

double BBcurve1(double *x, double *par)
{
	return ((par[0] / (x[0]-par[2])) / (x[0]-par[2])) + par[1];
}

float BBcurve1c(float *x, const float *par)
{
	return ((par[0] / (x[0]-par[2])) / (x[0]-par[2])) + par[1];
}

// isPion
bool isPion(float p, float dEdx)
{
	if (  (dEdx < BBcurve1c(&p , BB_Pion_hig_par)) && ( p < BB_Pion_maxpcut ) && ( BB_Pion_minpcut < p) && (BB_Pion_mindEdxcut < dEdx)  )
	{ return true; }
	else
	{return false; }
}

// isKaon
bool isKaon(float p, float dEdx)
{
	if (  (BBcurve1c(&p , BB_Kaon_low_par) < dEdx ) && (dEdx < BBcurve1c(&p , BB_Kaon_hig_par))  &&  (p < BB_Kaon_maxpcut ) && (BB_Kaon_mindEdxcut < dEdx) )
	{ return true; }
	else
	{return false; }
}

// isProt
bool isProt(float p, float dEdx)
{
	if (  (BBcurve1c(&p , BB_Prot_low_par) < dEdx ) && (dEdx < BBcurve1c(&p , BB_Prot_hig_par))  &&  (p < BB_Prot_maxpcut ) && (BB_Prot_mindEdxcut < dEdx) )
	{ return true; }
	else
	{return false; }
}

// GetPID
// 10 - unknown
//  1 - pion
//  2 - kaon
//  3 - prot
int GetPID(float p, float dEdx)
{
	int PID = 99;
	if ( isPion(p, dEdx) == true) {PID = 1; return PID;}
	if ( isKaon(p, dEdx) == true) {PID = 2; return PID;}
	if ( isProt(p, dEdx) == true) {PID = 3; return PID;}
	return PID;
}


void makedEdxvspFiglinlin(TH2D* dEdxvsP, std::string figurename)
{
	TF1 BB_Pion_low ("BB_Pion_low_fcn" , BBcurve1, pminlin, pmaxlin, 3);
	TF1 BB_Pion_hig ("BB_Pion_high_fcn", BBcurve1, pminlin, pmaxlin, 3);
	TF1 BB_Kaon_low ("BB_Kaon_low_fcn" , BBcurve1, pminlin, pmaxlin, 3);
	TF1 BB_Kaon_hig ("BB_Kaon_high_fcn", BBcurve1, pminlin, pmaxlin, 3);
	TF1 BB_Prot_low ("BB_Prot_low_fcn" , BBcurve1, pminlin, pmaxlin, 3);
	TF1 BB_Prot_hig ("BB_Prot_high_fcn", BBcurve1, pminlin, pmaxlin, 3);
	
	BB_Pion_low.SetParameters(BB_Pion_low_par[0], BB_Pion_low_par[1], BB_Pion_low_par[2]);
	BB_Pion_hig.SetParameters(BB_Pion_hig_par[0], BB_Pion_hig_par[1], BB_Pion_hig_par[2]);
	BB_Kaon_low.SetParameters(BB_Kaon_low_par[0], BB_Kaon_low_par[1], BB_Kaon_low_par[2]);
	BB_Kaon_hig.SetParameters(BB_Kaon_hig_par[0], BB_Kaon_hig_par[1], BB_Kaon_hig_par[2]);
	BB_Prot_low.SetParameters(BB_Prot_low_par[0], BB_Prot_low_par[1], BB_Prot_low_par[2]);
	BB_Prot_hig.SetParameters(BB_Prot_hig_par[0], BB_Prot_hig_par[1], BB_Prot_hig_par[2]);
	
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
	
	double pion_maxpcut  = BB_Pion_maxpcut;
	
	double kaon_lowcut  = BB_Kaon_mindEdxcut;
	double kaon_maxpcut = BB_Kaon_maxpcut;
	
	double prot_lowcut  = BB_Prot_mindEdxcut;
	double prot_maxpcut = BB_Prot_maxpcut;
	
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


void makedEdxvspFigloglog(TH2D* dEdxvsP, std::string figurename)
{
	TF1 BB_Pion_low ("BB_Pion_low_fcn" , BBcurve1, pminlin, pmaxlin, 3);
	TF1 BB_Pion_hig ("BB_Pion_high_fcn", BBcurve1, pminlin, pmaxlin, 3);
	TF1 BB_Kaon_low ("BB_Kaon_low_fcn" , BBcurve1, pminlin, pmaxlin, 3);
	TF1 BB_Kaon_hig ("BB_Kaon_high_fcn", BBcurve1, pminlin, pmaxlin, 3);
	TF1 BB_Prot_low ("BB_Prot_low_fcn" , BBcurve1, pminlin, pmaxlin, 3);
	TF1 BB_Prot_hig ("BB_Prot_high_fcn", BBcurve1, pminlin, pmaxlin, 3);
	
	BB_Pion_low.SetParameters(BB_Pion_low_par[0], BB_Pion_low_par[1], BB_Pion_low_par[2]);
	BB_Pion_hig.SetParameters(BB_Pion_hig_par[0], BB_Pion_hig_par[1], BB_Pion_hig_par[2]);
	BB_Kaon_low.SetParameters(BB_Kaon_low_par[0], BB_Kaon_low_par[1], BB_Kaon_low_par[2]);
	BB_Kaon_hig.SetParameters(BB_Kaon_hig_par[0], BB_Kaon_hig_par[1], BB_Kaon_hig_par[2]);
	BB_Prot_low.SetParameters(BB_Prot_low_par[0], BB_Prot_low_par[1], BB_Prot_low_par[2]);
	BB_Prot_hig.SetParameters(BB_Prot_hig_par[0], BB_Prot_hig_par[1], BB_Prot_hig_par[2]);
	
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
	dEdxvsP->GetYaxis()->SetRangeUser(dEdxminlin,dEdxmaxlin);
	dEdxvsP->GetXaxis()->SetTitle("p [GeV/c]");
	
	double pion_maxpcut  = BB_Pion_maxpcut;
	
	double kaon_lowcut  = BB_Kaon_mindEdxcut;
	double kaon_maxpcut = BB_Kaon_maxpcut;
	
	double prot_lowcut  = BB_Prot_mindEdxcut;
	double prot_maxpcut = BB_Prot_maxpcut;
	
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
