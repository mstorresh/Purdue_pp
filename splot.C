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

void splot(){

    //------- Manuel's file -----------------------------------
    TFile *fileNon = TFile::Open("outnondiffractive_1.root");
    TH1D *h_mulfullM = (TH1D*)fileNon->Get("h_mulfull");
    TH1D *h_d1   = (TH1D*)fileNon->Get("h_deleta");

    /*
    TH2D *h2_e1 = (TH2D*)fileNon->Get("h2_etaphiN3");    
    //------- Yicheng's file ----------------------------------
    TH1D *h1x = (TH1D*)h2_e1->ProjectionX();
    TH1D *h1y = (TH1D*)h2_e1->ProjectionY();
    */

    //--- rebin ------------------------------------------------

    double xbins[210]; int var = 0;
    int maxpo = 100; int count= 0;
    float step = 0.1;  float a = 2*(2.0/step) - 1;
    for(float i=-2.0; i<2.0; i+= step){
        xbins[count] = i;
        count++;
    }

    
   // TH1D *h_d1 = (TH1D*)h_deleta->Rebin(a, "h_d1", xbins);
    float ymax= h_d1->GetMaximum();
    float ymin= h_d1->GetMinimum();


    // c1--------------------------------------------------------------
    TCanvas *canvas1 = new TCanvas("canvas1", "canvas1", 700, 600);
    h_d1->SetStats(0);
    h_d1->SetLineColor(kBlue);
   // gStyle->SetPalette(kInvertedDarkBodyRadiator);
    h_d1->Draw("L");
    h_d1->GetYaxis()->SetTitle("count");
    h_d1->GetXaxis()->SetTitle("#Delta#eta");
    gStyle->SetOptTitle(0);
    gPad->SetTicks();
    TLatex *lat1 = new TLatex();
	lat1->DrawLatexNDC(.4,.95,"Delta eta");
    float chosenEff = 0.0;
    canvas1->Update();
    TLine *line1 = new TLine(chosenEff, ymin,chosenEff, ymax);
    line1->SetLineColor(kBlack);
    line1->SetLineStyle(9);
    line1->Draw("same");
    canvas1->Draw();

}
