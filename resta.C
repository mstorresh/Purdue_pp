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

void resta(){

    //------- Manuel's file -----------------------------------
    TFile *fileNon = TFile::Open("totnon.root");
    TH1D *h_mulfullM = (TH1D*)fileNon->Get("h_mulfull");
    TH2D *h2_e1 = (TH2D*)fileNon->Get("h2_etaphiOS3");
    TH2D *h2_e2 = (TH2D*)fileNon->Get("h2_etaphiSS3");
  
    //------- Yicheng's file ----------------------------------
    TH1D *h1x = (TH1D*)h2_e1->ProjectionX();
    TH1D *h1y = (TH1D*)h2_e1->ProjectionY();
    TH1D *h2x = (TH1D*)h2_e2->ProjectionX();
    TH1D *h2y = (TH1D*)h2_e2->ProjectionY();
   
    TH1D* h1xnew = (TH1D*) h1x->Clone("h1xnew");
    TH1D* h2xnew = (TH1D*) h2x->Clone("h2xnew");
    
    h1xnew->Add(h2x, -1);
    // c2-------------------------------------------------------------

    float ymax= h2x->GetMaximum();
    float ymin= h2x->GetMinimum();

    TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 800, 700);
    h1xnew->SetStats(0);
    h1xnew->SetLineColor(kBlue);
    h1xnew->Draw("HIST");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);
    TLatex *lat2 = new TLatex();
	lat2->DrawLatexNDC(.4,.95,"OC - SC");
    h1xnew->GetYaxis()->SetTitle("count");
    h1xnew->GetXaxis()->SetTitle("#Delta#eta");

    // c3 --------------------------------------------------------------
    h2xnew->Add(h1x, -1);
    //float ymax= h2x->GetMaximum();
    //float ymin= h2x->GetMinimum();

    TCanvas *canvas3 = new TCanvas("canvas3", "canvas3", 800, 700);
    h2xnew->SetStats(0);
    h2xnew->SetLineColor(kBlue);
    h2xnew->Draw("HIST");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);
    TLatex *lat3 = new TLatex();
	lat3->DrawLatexNDC(.4,.95,"SC - OC");
    h2xnew->GetYaxis()->SetTitle("count");
    h2xnew->GetXaxis()->SetTitle("#Delta#eta");



}


