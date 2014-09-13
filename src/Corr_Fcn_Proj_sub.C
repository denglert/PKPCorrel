#include "GetGraphFromFile.C"
#include "makeMultiPanelCanvas.C"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TLine.h"

#include <vector>

#define PI 3.1416

void Corr_Fcn_Proj_sub()
{
    file_1 = TFile::Open("../MultiStudyV2/rootfile/pt13/HighMultCorrelation220_260_pt13_sys.root");
    file_2 = TFile::Open("../MultiStudyV2/rootfile/pt13/MBCorrelation0_35_pt13_sys.root");
    file_3 = TFile::Open("../MultiStudyV2/rootfile/pt13/HighMultCorrelation220_260_ref_pt13.root");
    file_4 = TFile::Open("../MultiStudyV2/rootfile/pt13/MBCorrelation0_35_ref_pt13.root");
    
    TH2D* signal[6];
    TH2D* background[6];
    TH1D* mult[6];
    
    TH2D* signal_bkg[6];
    TH2D* background_bkg[6];
    TH1D* mult_bkg[6];

    signal[0] = (TH2D*)file_1->Get("demo/signalkshort_pt0");
    background[0] = (TH2D*)file_1->Get("demo/backgroundkshort_pt0");
    mult[0] = (TH1D*)file_1->Get("demo/mult_ks_pt0");
    
    signal[1] = (TH2D*)file_1->Get("demo/signallambda_pt0");
    background[1] = (TH2D*)file_1->Get("demo/backgroundlambda_pt0");
    mult[1] = (TH1D*)file_1->Get("demo/mult_la_pt0");
    
    signal[2] = (TH2D*)file_2->Get("demo/signalkshort_pt0");
    background[2] = (TH2D*)file_2->Get("demo/backgroundkshort_pt0");
    mult[2] = (TH1D*)file_2->Get("demo/mult_ks_pt0");
    
    signal[3] = (TH2D*)file_2->Get("demo/signallambda_pt0");
    background[3] = (TH2D*)file_2->Get("demo/backgroundlambda_pt0");
    mult[3] = (TH1D*)file_2->Get("demo/mult_la_pt0");
    
    signal_bkg[0] = (TH2D*)file_1->Get("demo/signalkshort_bkg_pt0");
    background_bkg[0] = (TH2D*)file_1->Get("demo/backgroundkshort_bkg_pt0");
    mult_bkg[0] = (TH1D*)file_1->Get("demo/mult_ks_bkg_pt0");
    
    signal_bkg[1] = (TH2D*)file_1->Get("demo/signallambda_bkg_pt0");
    background_bkg[1] = (TH2D*)file_1->Get("demo/backgroundlambda_bkg_pt0");
    mult_bkg[1] = (TH1D*)file_1->Get("demo/mult_la_bkg_pt0");
    
    signal_bkg[2] = (TH2D*)file_2->Get("demo/signalkshort_bkg_pt0");
    background_bkg[2] = (TH2D*)file_2->Get("demo/backgroundkshort_bkg_pt0");
    mult_bkg[2] = (TH1D*)file_2->Get("demo/mult_ks_bkg_pt0");
    
    signal_bkg[3] = (TH2D*)file_2->Get("demo/signallambda_bkg_pt0");
    background_bkg[3] = (TH2D*)file_2->Get("demo/backgroundlambda_bkg_pt0");
    mult_bkg[3] = (TH1D*)file_2->Get("demo/mult_la_bkg_pt0");
    
    signal[4] = (TH2D*)file_3->Get("demo/signal");
    background[4] = (TH2D*)file_3->Get("demo/background");
    mult[4] = (TH1D*)file_3->Get("demo/mult");
    
    signal[5] = (TH2D*)file_4->Get("demo/signal");
    background[5] = (TH2D*)file_4->Get("demo/background");
    mult[5] = (TH1D*)file_4->Get("demo/mult");

    double BW2D = (9.9/33)*((2-1.0/16)*3.1416/31);
    double fr[4] = {0.935644,0.865217,0.953136,0.896066};
    
    int nEvent[6];
    double Bz[6];
    TH2D* corr[6];
    TH1D* proj_short[6];
    TH1D* proj_long[6];
    int nEvent_bkg[4];
    double Bz_bkg[4];
    TH2D* corr_bkg[4];

    for(int i=0;i<4;i++)
    {
        corr[i] = (TH2D*)signal[i]->Clone();
        nEvent[i] = mult[i]->Integral(2,10000);
        Bz[i] = background[i]->GetBinContent(background[i]->FindBin(0,0));
        
        corr[i]->Divide(background[i]);
        corr[i]->Scale(Bz[i]/nEvent[i]/BW2D);
        
        corr_bkg[i] = (TH2D*)signal_bkg[i]->Clone();
        nEvent_bkg[i] = mult_bkg[i]->Integral(2,10000);
        Bz_bkg[i] = background_bkg[i]->GetBinContent(background_bkg[i]->FindBin(0,0));
        corr_bkg[i]->Divide(background_bkg[i]);
        corr_bkg[i]->Scale(Bz_bkg[i]/nEvent_bkg[i]/BW2D);

        corr_bkg[i]->Scale(1.0-fr[i]);
        corr[i]->Add(corr_bkg[i],-1.0);
        corr[i]->Scale(1.0/fr[i]);
        
        TF1* fit = new TF1("fit","pol4",0.0,2.);
        //fit->SetParameters(1,1,1,1);
        
        //long range proj
        TH1D* lrs = signal[i]->ProjectionY("lrs",1,10);
        TH1D* lrsa = signal[i]->ProjectionY("lrsa",24,33);
        TH1D* lrb = background[i]->ProjectionY("lrb",1,10);
        TH1D* lrba = background[i]->ProjectionY("lrba",24,33);
        lrs->Add(lrsa);
        lrb->Add(lrba);
        lrs->Divide(lrb);
        lrs->Scale(Bz[i]/nEvent[i]/BW2D);

        TH1D* lrs_bkg = signal_bkg[i]->ProjectionY("lrs_bkg",1,10);
        TH1D* lrsa_bkg = signal_bkg[i]->ProjectionY("lrsa_bkg",24,33);
        TH1D* lrb_bkg = background_bkg[i]->ProjectionY("lrb_bkg",1,10);
        TH1D* lrba_bkg = background_bkg[i]->ProjectionY("lrba_bkg",24,33);
        lrs_bkg->Add(lrsa_bkg);
        lrb_bkg->Add(lrba_bkg);
        lrs_bkg->Divide(lrb_bkg);
        lrs_bkg->Scale(Bz_bkg[i]/nEvent_bkg[i]/BW2D);
        
        lrs_bkg->Scale(1.0-fr[i]);
        lrs->Add(lrs_bkg,-1.0);
        lrs->Scale(1.0/fr[i]);
        
        proj_long[i] = (TH1D*)lrs->Clone();

        lrs->Fit("fit","R");
        lrs->Fit("fit","R");
        lrs->Fit("fit","R");
        lrs->Fit("fit","R");
        lrs->Fit("fit","R");

        double lrm = fit->GetMinimum(0.0,2.0);
        TF1* mflr = new TF1("mflr","[0]",-(0.5-1.0/32)*3.1416,(1.5-1.0/32)*3.1416);
        mflr->SetParameter(0,-lrm);
        proj_long[i]->Add(mflr);


        //short range proj
        TH1D* srs = signal[i]->ProjectionY("srs",14,20);
        TH1D* srb = background[i]->ProjectionY("srb",14,20);
        srs->Divide(srb);
        srs->Scale(Bz[i]/nEvent[i]/BW2D);
        
        TH1D* srs_bkg = signal_bkg[i]->ProjectionY("srs_bkg",14,20);
        TH1D* srb_bkg = background_bkg[i]->ProjectionY("srb_bkg",14,20);
        srs_bkg->Divide(srb_bkg);
        srs_bkg->Scale(Bz_bkg[i]/nEvent_bkg[i]/BW2D);

        srs_bkg->Scale(1.0-fr[i]);
        srs->Add(srs_bkg,-1.0);
        srs->Scale(1.0/fr[i]);
        
        srs->Add(lrs,-1);
        proj_short[i] = (TH1D*)srs->Clone();
        
        srs->Fit("fit","R");
        srs->Fit("fit","R");
        srs->Fit("fit","R");
        srs->Fit("fit","R");
        srs->Fit("fit","R");
        
        double srm = fit->GetMinimum(0.0,2.0);
        TF1* mfsr = new TF1("mfsr","[0]",-(0.5-1.0/32)*3.1416,(1.5-1.0/32)*3.1416);
        mfsr->SetParameter(0,-srm);
        proj_short[i]->Add(mfsr);
    }
    
    for(int i=4;i<6;i++)
    {
        corr[i] = (TH2D*)signal[i]->Clone();
        nEvent[i] = mult[i]->Integral(2,10000);
        Bz[i] = background[i]->GetBinContent(background[i]->FindBin(0,0));
        
        corr[i]->Divide(background[i]);
        corr[i]->Scale(Bz[i]/nEvent[i]/BW2D);
        
        TF1* fit = new TF1("fit","pol4",0.0,2.);
        //fit->SetParameters(1,1,1,1);
        
        //long range proj
        TH1D* lrs = signal[i]->ProjectionY("lrs",1,10);
        TH1D* lrsa = signal[i]->ProjectionY("lrsa",24,33);
        TH1D* lrb = background[i]->ProjectionY("lrb",1,10);
        TH1D* lrba = background[i]->ProjectionY("lrba",24,33);
        lrs->Add(lrsa);
        lrb->Add(lrba);
        lrs->Divide(lrb);
        lrs->Scale(Bz[i]/nEvent[i]/BW2D);
        
        proj_long[i] = (TH1D*)lrs->Clone();
        
        lrs->Fit("fit","R");
        lrs->Fit("fit","R");
        lrs->Fit("fit","R");
        lrs->Fit("fit","R");
        lrs->Fit("fit","R");
        
        double lrm = fit->GetMinimum(0.0,2.0);
        TF1* mflr = new TF1("mflr","[0]",-(0.5-1.0/32)*3.1416,(1.5-1.0/32)*3.1416);
        mflr->SetParameter(0,-lrm);
        proj_long[i]->Add(mflr);
        
        
        //short range proj
        TH1D* srs = signal[i]->ProjectionY("srs",14,20);
        TH1D* srb = background[i]->ProjectionY("srb",14,20);
        srs->Divide(srb);
        srs->Scale(Bz[i]/nEvent[i]/BW2D);
        
        srs->Add(lrs,-1);
        proj_short[i] = (TH1D*)srs->Clone();
        
        srs->Fit("fit","R");
        srs->Fit("fit","R");
        srs->Fit("fit","R");
        srs->Fit("fit","R");
        srs->Fit("fit","R");
        
        double srm = fit->GetMinimum(0.0,2.0);
        TF1* mfsr = new TF1("mfsr","[0]",-(0.5-1.0/32)*3.1416,(1.5-1.0/32)*3.1416);
        mfsr->SetParameter(0,-srm);
        proj_short[i]->Add(mfsr);
    }
    
    TCanvas* c1corr = new TCanvas("c1corr","c1corr",1,1,800,700);
    c1corr->Divide(2,2);
    
    corr[0]->SetMaximum(3.58);
    corr[1]->SetMaximum(3.33);
    corr[2]->SetMaximum(0.34);
    corr[3]->SetMaximum(0.34);
    
    corr[0]->SetMinimum(3.15);
    corr[1]->SetMinimum(2.97);
    corr[2]->SetMinimum(0.18);
    corr[3]->SetMinimum(0.18);

    for(int i=0;i<4;i++)
    {
        corr[i]->GetXaxis()->SetRangeUser(-4,4);
        corr[i]->SetZTitle("#frac{1}{N_{trig}} #frac{d^{2}N^{pair}}{d#Delta#eta d#Delta#phi}");
        corr[i]->SetYTitle("#Delta#phi (radians)");
        corr[i]->SetTitleFont(42,"X");
        corr[i]->SetTitleFont(42,"Y");
        corr[i]->SetTitleFont(42,"Z");
        corr[i]->GetXaxis()->CenterTitle(1);
        corr[i]->GetYaxis()->CenterTitle(1);
        corr[i]->GetZaxis()->CenterTitle(1);
        corr[i]->SetTitleOffset(1.1,"X");
        corr[i]->SetTitleOffset(1.1,"Y");
        corr[i]->SetTitleOffset(1.6,"Z");
        corr[i]->GetYaxis()->SetTitleSize(corr[i]->GetYaxis()->GetTitleSize()*1.8);
        corr[i]->GetXaxis()->SetTitleSize(corr[i]->GetXaxis()->GetTitleSize()*1.8);
        corr[i]->GetZaxis()->SetTitleSize(corr[i]->GetZaxis()->GetTitleSize()*1.2);
        corr[i]->GetYaxis()->SetLabelSize(corr[i]->GetYaxis()->GetLabelSize()*1.3);
        corr[i]->GetXaxis()->SetLabelSize(corr[i]->GetXaxis()->GetLabelSize()*1.3);
        corr[i]->GetZaxis()->SetLabelSize(corr[i]->GetZaxis()->GetLabelSize()*1.3);
        c1corr->cd(i+1);
        c1corr->GetPad(i+1)->SetLeftMargin(0.22);
        c1corr->GetPad(i+1)->SetBottomMargin(0.05);
        c1corr->GetPad(i+1)->SetRightMargin(0.01);
        c1corr->GetPad(i+1)->SetTopMargin(0.1);
        c1corr->GetPad(i+1)->SetTheta(60.839);
        c1corr->GetPad(i+1)->SetPhi(38.0172);
        corr[i]->SetLineWidth(1);
//        corr[i]->Draw("SURF1 FB");
    }
    c1corr->cd(1);
    corr[2]->Draw("SURF1 FB");
    c1corr->cd(2);
    corr[3]->Draw("SURF1 FB");
    c1corr->cd(3);
    corr[0]->Draw("SURF1 FB");
    c1corr->cd(4);
    corr[1]->Draw("SURF1 FB");
    
    TCanvas *c2proj = new TCanvas("c2proj","c2proj",1,1,950,590);
    makeMultiPanelCanvas(c2proj,3,2,0.01,0.01,0.25,0.16,0.01);
    
    for(int i=0;i<6;i++)
    {
        fixedFontHist1D(proj_long[i],1.45,2.12);
        fixedFontHist1D(proj_short[i],1.45,2.12);

        proj_long[i]->SetMaximum(0.34);
        proj_long[i]->SetMinimum(-0.02);
        proj_short[i]->SetMaximum(0.34);
        proj_short[i]->SetMinimum(-0.02);
        
        //proj_long[i]->SetTitleFont(42,"X");
        //proj_long[i]->SetTitleFont(42,"Y");
        
        //proj_short[i]->SetTitleFont(42,"X");
        //proj_short[i]->SetTitleFont(42,"Y");
        
        proj_long[i]->SetYTitle("#frac{1}{N_{trig}} #frac{dN^{pair}}{d#Delta#phi} - C_{ZYAM}");
        proj_short[i]->SetYTitle("#frac{1}{N_{trig}} #frac{dN^{pair}}{d#Delta#phi} - C_{ZYAM}");
        proj_short[i]->SetXTitle("#Delta#phi (radians)");
        
        
        proj_long[i]->GetYaxis()->SetTitleSize(proj_long[i]->GetYaxis()->GetTitleSize()*1.3);
        proj_short[i]->GetYaxis()->SetTitleSize(proj_short[i]->GetYaxis()->GetTitleSize()*1.3);
        proj_long[i]->GetXaxis()->SetTitleSize(proj_long[i]->GetXaxis()->GetTitleSize()*1.4);
        proj_short[i]->GetXaxis()->SetTitleSize(proj_short[i]->GetXaxis()->GetTitleSize()*1.4);
        
        proj_long[i]->GetXaxis()->SetLabelSize(proj_long[i]->GetXaxis()->GetLabelSize()*1.3);
        proj_long[i]->GetYaxis()->SetLabelSize(proj_long[i]->GetYaxis()->GetLabelSize()*1.3);
        proj_short[i]->GetXaxis()->SetLabelSize(proj_short[i]->GetXaxis()->GetLabelSize()*1.3);
        proj_short[i]->GetYaxis()->SetLabelSize(proj_short[i]->GetYaxis()->GetLabelSize()*1.3);

        
        proj_long[i]->GetXaxis()->CenterTitle(1);
        proj_short[i]->GetXaxis()->CenterTitle(1);
        proj_long[i]->GetYaxis()->CenterTitle(1);
        proj_short[i]->GetYaxis()->CenterTitle(1);

    }
    
    proj_long[0]->SetMarkerColor(4);
    proj_short[0]->SetMarkerColor(4);
    proj_long[0]->SetMarkerStyle(21);
    proj_short[0]->SetMarkerStyle(21);    

    proj_long[1]->SetMarkerColor(2);
    proj_short[1]->SetMarkerColor(2);
    proj_long[1]->SetMarkerStyle(20);
    proj_short[1]->SetMarkerStyle(20);
    
    proj_long[2]->SetMarkerColor(4);
    proj_short[2]->SetMarkerColor(4);
    proj_long[2]->SetMarkerStyle(25);
    proj_short[2]->SetMarkerStyle(25);    

    proj_long[3]->SetMarkerColor(2);
    proj_short[3]->SetMarkerColor(2);
    proj_long[3]->SetMarkerStyle(24);
    proj_short[3]->SetMarkerStyle(24);    

    proj_long[4]->SetMarkerColor(1);
    proj_short[4]->SetMarkerColor(1);
    proj_long[4]->SetMarkerStyle(34);
    proj_short[4]->SetMarkerStyle(34);    

    proj_long[5]->SetMarkerColor(1);
    proj_short[5]->SetMarkerColor(1);
    proj_long[5]->SetMarkerStyle(28);
    proj_short[5]->SetMarkerStyle(28);
    
    TF1* fitfunc0 = new TF1("fitfunc0","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",-PI/2,3*PI/2);
    fitfunc0->SetParameters(0.3,0.1,0.5,0.1,0.1,0.1);
    TF1* fitfunc1 = new TF1("fitfunc1","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",-PI/2,3*PI/2);
    fitfunc1->SetParameters(0.3,0.1,0.5,0.1,0.1,0.1);
    TF1* fitfunc2 = new TF1("fitfunc2","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",-PI/2,3*PI/2);
    fitfunc2->SetParameters(0.3,0.1,0.5,0.1,0.1,0.1);

    TF1* fitfunc3 = new TF1("fitfunc3","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",-PI/2,3*PI/2);
    fitfunc3->SetParameters(0.3,0.1,0.5,0.1,0.1,0.1);
    TF1* fitfunc4 = new TF1("fitfunc4","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",-PI/2,3*PI/2);
    fitfunc4->SetParameters(0.3,0.1,0.5,0.1,0.1,0.1);
    TF1* fitfunc5 = new TF1("fitfunc5","[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x))",-PI/2,3*PI/2);
    fitfunc5->SetParameters(0.3,0.1,0.5,0.1,0.1,0.1);

    proj_long[4]->Fit("fitfunc0","RNO");
    proj_long[0]->Fit("fitfunc1","RNO");
    proj_long[1]->Fit("fitfunc2","RNO");
    
    proj_long[5]->Fit("fitfunc3","RNO");
    proj_long[2]->Fit("fitfunc4","RNO");
    proj_long[3]->Fit("fitfunc5","RNO");
    
    fitfunc0->SetLineColor(1);
    fitfunc0->SetLineStyle(1);
    fitfunc1->SetLineColor(1);
    fitfunc1->SetLineStyle(1);
    fitfunc2->SetLineColor(1);
    fitfunc2->SetLineStyle(1);

    fitfunc3->SetLineColor(1);
    fitfunc3->SetLineStyle(1);
    fitfunc4->SetLineColor(1);
    fitfunc4->SetLineStyle(1);
    fitfunc5->SetLineColor(1);
    fitfunc5->SetLineStyle(1);

    c2proj->cd(2);
    proj_long[0]->Draw("PE");    // kshort
    proj_long[2]->Draw("PESAME");
    fitfunc1->Draw("LSAME");
    fitfunc4->Draw("LSAME");
    c2proj->cd(3);
    proj_long[1]->Draw("PE");    // lambda
    proj_long[3]->Draw("PESAME");
    fitfunc2->Draw("LSAME");
    fitfunc5->Draw("LSAME");
    c2proj->cd(1);
    proj_long[4]->Draw("PE");    // charged
    proj_long[5]->Draw("PESAME");
    fitfunc0->Draw("LSAME");
    fitfunc3->Draw("LSAME");
    c2proj->cd(5);
    proj_short[0]->Draw("PE");
    proj_short[2]->Draw("PESAME");
    c2proj->cd(6);
    proj_short[1]->Draw("PE");
    proj_short[3]->Draw("PESAME");
    c2proj->cd(4);
    proj_short[4]->Draw("PE");
    proj_short[5]->Draw("PESAME");
    
    char label_cms[200]={"CMS pPb #sqrt{s_{NN}} = 5.02 TeV"};
    char label_energy[2][200]={"CMS PbPb #sqrt{s_{NN}} = 2.76 TeV","L_{int} = 35 nb^{#font[122]{\55}1}"};
    char label_energy_n[4][200]={"(c) CMS pPb #sqrt{s_{NN}} = 5.02 TeV, L_{int} = 35 nb^{#font[122]{\55}1}","(a) CMS pPb #sqrt{s_{NN}} = 5.02 TeV, L_{int} = 35 nb^{#font[122]{\55}1}",
                                 "(d) CMS pPb #sqrt{s_{NN}} = 5.02 TeV, L_{int} = 35 nb^{#font[122]{\55}1}","(b) CMS pPb #sqrt{s_{NN}} = 5.02 TeV, L_{int} = 35 nb^{#font[122]{\55}1}"};
    char label_n[2][200]={"220 #leq N < 260","N < 35"};
    char label_PID[3][200]={"K^{0}_{S}","#Lambda/#bar{#Lambda}","charged hadron"};
    char label_pt[2][200]={"1 < p^{trig}_{T} < 3 GeV","1 < p^{assoc}_{T} < 3 GeV"};
    char label_region[2][200]={"Long range (|#Delta#eta| > 2)","Short range (|#Delta#eta| < 1)"};
    
    TLatex *tex1= new TLatex();
    tex1->SetNDC();
    tex1->SetTextFont(42);
    c1corr->cd(3);
    tex1->SetTextSize(tex1->GetTextSize()*1.1);
    tex1->DrawLatex(0.0,0.94,label_energy_n[0]);
    tex1->SetTextSize(tex1->GetTextSize()/1.1*0.9);
    tex1->DrawLatex(0.0,0.87,label_n[0]);
    tex1->DrawLatex(0.0,0.805,label_pt[0]);
    tex1->DrawLatex(0.0,0.73,label_pt[1]);
    c1corr->cd(4);
    tex1->SetTextSize(tex1->GetTextSize()/0.9*1.1);
    tex1->DrawLatex(0.0,0.94,label_energy_n[2]);
    tex1->SetTextSize(tex1->GetTextSize()/1.1*0.9);
    tex1->DrawLatex(0.0,0.87,label_n[0]);
    tex1->DrawLatex(0.0,0.805,label_pt[0]);
    tex1->DrawLatex(0.0,0.73,label_pt[1]);
    c1corr->cd(1);
    tex1->SetTextSize(tex1->GetTextSize()/0.9*1.1);
    tex1->DrawLatex(0.0,0.94,label_energy_n[1]);
    tex1->SetTextSize(tex1->GetTextSize()/1.1*0.9);
    tex1->DrawLatex(0.0,0.87,label_n[1]);
    tex1->DrawLatex(0.0,0.805,label_pt[0]);
    tex1->DrawLatex(0.0,0.73,label_pt[1]);
    c1corr->cd(2);
    tex1->SetTextSize(tex1->GetTextSize()/0.9*1.1);
    tex1->DrawLatex(0.0,0.94,label_energy_n[3]);
    tex1->SetTextSize(tex1->GetTextSize()/1.1*0.9);
    tex1->DrawLatex(0.0,0.87,label_n[1]);
    tex1->DrawLatex(0.0,0.805,label_pt[0]);
    tex1->DrawLatex(0.0,0.73,label_pt[1]);
    c1corr->cd(1);
    tex1->SetTextSize(tex1->GetTextSize()*1.6);
    tex1->DrawLatex(0.78,0.83,"K^{0}_{S}-h^{#pm}");
    c1corr->cd(2);
    tex1->DrawLatex(0.76,0.83,"#Lambda/#bar{#Lambda}-h^{#pm}");
    c1corr->cd(3);
    tex1->DrawLatex(0.78,0.83,"K^{0}_{S}-h^{#pm}");
    c1corr->cd(4);
    tex1->DrawLatex(0.76,0.83,"#Lambda/#bar{#Lambda}-h^{#pm}");

    TLatex *tex2= new TLatex();
    tex2->SetNDC();
    tex2->SetTextFont(42);
    c2proj->cd(1);
    tex2->SetTextSize(tex2->GetTextSize()*1.5);
    tex2->DrawLatex(0.283,0.9,label_cms);
    //tex2->SetTextSize(tex2->GetTextSize()/1.6*1.6);
    tex2->DrawLatex(0.283,0.80,label_energy[1]);
    tex2->DrawLatex(0.283,0.695,label_pt[0]);
    tex2->DrawLatex(0.283,0.595,label_pt[1]);
    tex2->DrawLatex(0.283,0.51,label_region[0]);
    //tex2->DrawLatex(0.25,0.52,"|#Delta#eta| > 2");
    tex2->SetTextSize(tex2->GetTextSize()/1);
    TLegend* leg1 = new TLegend(0.13,0.6,0.48,0.85);
    leg1->SetFillColor(10);
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0.025);
    leg1->SetTextFont(42);
    leg1->SetTextSize(0.068);
    leg1->AddEntry(proj_long[0],"","p");
    leg1->AddEntry(proj_long[2],"","p");
    //leg1->AddEntry(fitfunc1,"    ","L");
    TLegend* leg2 = new TLegend(0.05,0.6,0.38,0.85);
    leg2->SetFillColor(10);
    leg2->SetFillStyle(0);
    leg2->SetBorderSize(0.025);
    leg2->AddEntry(proj_long[4],"","p");
    leg2->AddEntry(proj_long[5],"","p");
    //leg2->AddEntry(fitfunc0," ","L");
    TLegend* leg3 = new TLegend(0.21,0.6,0.56,0.85);
    leg3->SetFillColor(10);
    leg3->SetFillStyle(0);
    leg3->SetBorderSize(0.025);
    leg3->SetTextFont(42);
    leg3->SetTextSize(0.069);
    leg3->AddEntry(proj_long[1]," 220 #leq N < 260","p");
    leg3->AddEntry(proj_long[3]," 0 < N < 35","p");
    //leg3->AddEntry(fitfunc2," Fourier fits","L");
    c2proj->cd(2);
    leg1->Draw();
    leg2->Draw();
    leg3->Draw();
    
    TLegend* leg4 = new TLegend(0.13,0.715,0.56,0.965);
    leg4->SetFillColor(10);
    leg4->SetFillStyle(0);
    leg4->SetBorderSize(0.025);
    leg4->SetTextFont(42);
    leg4->SetTextSize(0.069);
    leg4->AddEntry(fitfunc0," "," ");
    leg4->AddEntry(fitfunc0," Fourier fits","L");
    
    c2proj->cd(3);
    leg4->Draw();

    c2proj->cd(4);
    tex2->SetTextSize(tex2->GetTextSize()/1.2);
    tex2->DrawLatex(0.51,0.92,label_region[1]);
    tex2->DrawLatex(0.51,0.85,"minus");
    tex2->DrawLatex(0.51,0.78,label_region[0]);
    

    tex2->SetTextSize(tex2->GetTextSize()*1.7);
    c2proj->cd(2);
    tex2->SetTextColor(4);
    tex2->DrawLatex(0.75,0.77,"K^{0}_{S}-h^{#pm}");
    c2proj->cd(3);
    tex2->SetTextColor(2);
    tex2->DrawLatex(0.7,0.77,"#Lambda/#bar{#Lambda}-h^{#pm}");
    tex2->SetTextColor(1);
    c2proj->cd(1);
    tex2->DrawLatex(0.82,0.77,"h^{#pm}-h^{#pm}");

    //return;
    c1corr->Print("./paperplots/Corr_Fcn_Fig1_sub.gif");
    c1corr->Print("./paperplots/Corr_Fcn_Fig1_sub.pdf");
    c2proj->Print("./paperplots/Corr_Proj_Fig2_sub.gif");
    c2proj->Print("./paperplots/Corr_Proj_Fig2_sub.pdf");


}
