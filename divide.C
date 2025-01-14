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

void divide(){

    //------- Manuel's file -----------------------------------
    TFile *fileNon = TFile::Open("totnon.root");
    TH2D *h2_e1 = (TH2D*)fileNon->Get("h2_etaphiSS2");
    TH2D *h2_e2 = (TH2D*)fileNon->Get("h2_etaphiOS2");
  
    //------- Yicheng's file ----------------------------------
    TH1D *h1x = (TH1D*)h2_e1->ProjectionX();
    TH1D *h1y = (TH1D*)h2_e1->ProjectionY();
    TH1D *h2x = (TH1D*)h2_e2->ProjectionX();
    TH1D *h2y = (TH1D*)h2_e2->ProjectionY();
   
    TH1D* h2xnew = (TH1D*) h2x->Clone("h2xnew");
    TH1D* h2ynew = (TH1D*) h2y->Clone("h2ynew");
    
    TH2D* h2_div = (TH2D*) h2_e2->Clone("h2_div");

    h2_div->Divide(h2_e2, h2_e1);
    h2xnew->Divide(h2x, h1x);
    

    TCanvas *canvas3 = new TCanvas("canvas3", "canvas3", 800, 700);
    h2_div->SetStats(0);
    /* h2xnew->SetLineColor(kBlue); */
    h2_div->Draw("colz");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);
    /* TLatex *lat3 = new TLatex(); */
	/* lat3->DrawLatexNDC(.4,.95,"SC - OC"); */
    /* h2xnew->GetYaxis()->SetTitle("count"); */
    /* h2xnew->GetXaxis()->SetTitle("#Delta#eta"); */


    TCanvas *canvas4 = new TCanvas("canvas4", "canvas4", 800, 700);
    h2xnew->SetStats(0);
    h2xnew->SetLineColor(kBlue);
    h2xnew->Draw("colz");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);

}


