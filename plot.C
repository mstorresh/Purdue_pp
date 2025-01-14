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

void plot(){

    //------- Manuel's file -----------------------------------
    TFile *fileNon = TFile::Open("totnon.root");
    TH2D *h2_e1 = (TH2D*)fileNon->Get("h2_etaphiSS2");

    TFile *file2 = TFile::Open("totdif.root");
    TH2D *h2_e2 = (TH2D*)file2->Get("h2_etaphiSS2");    
    //------- Yicheng's file ----------------------------------
    TH1D *h1x = (TH1D*)h2_e1->ProjectionX();
    TH1D *h1y = (TH1D*)h2_e1->ProjectionY();
    TH1D *h2x = (TH1D*)h2_e2->ProjectionX();
    TH1D *h2y = (TH1D*)h2_e2->ProjectionY();
    
   /* 
    // c1--------------------------------------------------------------
    TCanvas *canvas1 = new TCanvas("canvas1", "canvas1", 800, 700);
    //h2_e1->SetStats(0);
    //gStyle->SetPalette(kInvertedDarkBodyRadiator);
    h2_e1->Draw("colz");
    h2_e1->GetYaxis()->SetTitle("#Delta#phi [rad]");
    h2_e1->GetXaxis()->SetTitle("#Delta#eta");
    gStyle->SetOptTitle(0);
    gPad->SetTicks();
    //TLatex *lat1 = new TLatex();
	//lat1->DrawLatexNDC(.3,.95,"2D Hitogram TPC 3Cut");
   */
    
    TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 800, 700);
    //h2_e2->SetStats(0);
    gStyle->SetPalette(kInvertedDarkBodyRadiator);
    h2_e1->Draw("colz");
    h2_e1->GetYaxis()->SetTitle("#Delta#phi [rad]");
    h2_e1->GetXaxis()->SetTitle("#Delta#eta");
    gStyle->SetOptTitle(0);
    gPad->SetTicks();
    //TLatex *lat1 = new TLatex();
	//lat1->DrawLatexNDC(.3,.95,"2D Hitogram TPC 3Cut");
  
    // c2-------------------------------------------------------------

    float ymax= h1x->GetMaximum();
    float ymin= h1x->GetMinimum();

    TCanvas *canvas4 = new TCanvas("canvas4", "canvas4", 800, 700);
    h1x->SetStats(0);
    h1x->SetLineColor(kRed);
    h1x->GetYaxis()->SetTitle("count");
    h1x->GetXaxis()->SetTitle("#Delta#eta");
    h1x->Draw("L");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);
    /* TLatex *lat2 = new TLatex(); */
	/* lat2->DrawLatexNDC(.4,.95,"Projection in X"); */
    float chosenEff = 0.0;
    canvas2->Update();
    TLine *line1 = new TLine(chosenEff, ymin,chosenEff, ymax);
    line1->SetLineColor(kBlack);
    line1->SetLineStyle(9);
    line1->Draw("same");


    // c3--------------------------------------------------------------
    TCanvas *canvas3 = new TCanvas("canvas3", "canvas3", 800, 700);
    h1y->SetStats(0);
    h1y->SetLineColor(kRed);
    h1y->GetYaxis()->SetTitle("count");
    h1y->GetXaxis()->SetTitle("#Delta#phi");
    h1y->Draw();
    gPad->SetTicks();
    gStyle->SetOptTitle(0);
    /* TLatex *lat3 = new TLatex(); */
	/* lat3->DrawLatexNDC(.4,.95,"Projection in Y"); */

   
}
