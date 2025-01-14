#include <string>
#include "TH1D.h"
#include "RooArgusBG.h"
#include "RooDataSet.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TFile.h"
#include "TBranch.h"
#include <vector>
#include <cmath>
#include <math.h>

void triangle(){

    //------- Manuel's file -----------------------------------
    TFile *fileNon = TFile::Open("outnondiffractive_1.root");
    TH1D *h_mulfullM = (TH1D*)fileNon->Get("h_mulfull");
    TH2D *h2_e1 = (TH2D*)fileNon->Get("h2_etaphiN1");   //N = OS
    TH2D *h2_e2 = (TH2D*)fileNon->Get("h2_etaphiP1");   //P = SS
    
    //---- projections ----------------------------------------
    TH1D *h1x = (TH1D*)h2_e1->ProjectionX();
    TH1D *h1y = (TH1D*)h2_e1->ProjectionY();
    TH1D *h2x = (TH1D*)h2_e2->ProjectionX();
    TH1D *h2y = (TH1D*)h2_e2->ProjectionY();
    h1x->Scale(1./(h1x->GetXaxis()->GetBinWidth(1)*1000000));
    h2x->Scale(1./(h2x->GetXaxis()->GetBinWidth(1)*1000000));
   
    //-- triangle hist ------------------------------------------------
        
    std::cout<<h1x->GetMaximum()<<'\n';
    double a = h1x->GetMaximum();
    TH1D *h_tri = new TH1D("h_tri","h_tri",40, -2.1, 2.1);
    TF1* fun1   = new TF1("fun1", "-([0]/2)*abs(x) + [0]", -2,2);
    fun1->SetParameter(0, 1);
    fun1->SetNpx(200);
    for(int i=0; i<h_tri->GetXaxis()->GetNbins(); i++){
    double x = h_tri->GetBinCenter(i+1);
    double y =fun1->Eval(x);
    h_tri->SetBinContent(i+1,y);
    h_tri->SetBinError(i+1,0);
    }
    //h_tri->FillRandom("fun1", 100000000);
    
    TH1D* h3 = (TH1D*) h2x->Clone("h3");
    h3->Divide(h2x, h_tri);  // do it manual

    TH1D* h4 = (TH1D*) h2x->Clone("h3");

    for(int i= 1; i<=40; i++ ){
       float ra1  =  h2x->GetBinContent(i)/h_tri->GetBinContent(i);
       float err1 =  h2x->GetBinError(i)/h_tri->GetBinContent(i);
       h4->SetBinContent(i, ra1);
       h4->SetBinError(i, err1);
    }

    // c2-------------------------------------------------------------
    
    TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 800, 700);
    h_tri->SetStats(0);
    h_tri->SetLineColor(kBlue);
    h_tri->Draw("HIST");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);
    h_tri->GetYaxis()->SetTitle("#frac{dN_{OS}}{d#Delta#eta}");
    h_tri->GetXaxis()->SetTitle("#Delta#eta");
    h2x->SetLineColor(418);
    //h2x->SetLineColor(kViolet);
    h2x->Draw("HIST same");

    // c3--------------------------------------------------------------

    TCanvas *canvas3 = new TCanvas("canvas3", "canvas3", 800, 700);
    h3->SetStats(0);
    h3->Draw();
    gPad->SetTicks();
    gStyle->SetOptTitle(0);
    h3->GetYaxis()->SetTitle("#frac{dN_{OS}}{d#Delta#eta}/triangle");
    h3->GetXaxis()->SetTitle("#Delta#eta");

}

