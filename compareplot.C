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

void compareplot(){

    //------- Manuel's file -----------------------------------
    TFile *fileNon = TFile::Open("outdiffractive_1.root");
    TH1D *h_mulfullM = (TH1D*)fileNon->Get("h_mulfull");
    TH2D *h2_e1 = (TH2D*)fileNon->Get("h2_etaphiN3");
    TH2D *h2_e2 = (TH2D*)fileNon->Get("h2_etaphiP3");
  
    //------- Yicheng's file ----------------------------------
    TH1D *h1x = (TH1D*)h2_e1->ProjectionX();
    //TH1D *h1x = (TH1D*)h2_e1->ProjectionY();
    TH1D *h2x = (TH1D*)h2_e2->ProjectionX();
    //TH1D *h2x = (TH1D*)h2_e2->ProjectionY();
    h1x->Scale(1./(h1x->GetXaxis()->GetBinWidth(1)*1000000));
    h2x->Scale(1./(h1x->GetXaxis()->GetBinWidth(1)*1000000));
    
    // c2-------------------------------------------------------------

    float ymax= h2x->GetMaximum();
    float ymin= h2x->GetMinimum();

    TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 800, 700);
    h2x->SetStats(0);
    //h1x->SetLineColor(418);
    h2x->SetLineColor(907);
    h2x->Draw("HIST");
    //h2x->SetLineColor(kViolet);
    h1x->SetLineColor(kOrange);
    h1x->Draw("HIST same");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);
    //TLatex *lat2 = new TLatex();
	//lat2->DrawLatexNDC(.4,.95,"Projection in X");
    h2x->GetYaxis()->SetTitle("#frac{dN}{d#Delta#eta}");
    h2x->GetXaxis()->SetTitle("#Delta#eta");
    TLegend *leg = new TLegend(0.8, 0.8, 0.9, 0.9);
    leg->AddEntry(h1x, "OS", "l");
    leg->AddEntry(h2x, "SS", "l");
    leg->Draw("same");
    
   
}

