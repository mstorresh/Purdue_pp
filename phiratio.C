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

void phiratio(){

    //------- Manuel's file -----------------------------------
    TFile *file1 = TFile::Open("Nonsmallar.root");
    TFile *file2 = TFile::Open("outdiffractive_1.root");

    //TH1D *h_mulfullM = (TH1D*)fileNon->Get("h_mulfull");
    TH2D *h2_e1 = (TH2D*)file1->Get("h2_dellar2");
    TH2D *h2_e2 = (TH2D*)file1->Get("h2_delsma2");
    
    //---- projections ----------------------------------------
    TH1D *h1x = (TH1D*)h2_e1->ProjectionX();
    TH1D *h1y = (TH1D*)h2_e1->ProjectionY();
    TH1D *h2x = (TH1D*)h2_e2->ProjectionX();
    TH1D *h2y = (TH1D*)h2_e2->ProjectionY();
   
    double ev1 = 107073000; 
    double ev2 = 94346000;
    double ev3 = 56452100;
    double ev4 = 21812100;
    double ev5 = 9493190;
    
    double part1 = 229814000;
    double part2 = 458098000;
    double part3 = 463920000;
    double part4 = 265734000;
    double part5 = 161676000;


    h1y->Scale(1./(h2_e1->GetXaxis()->GetBinWidth(1)*part2)); //1./(Nevents*binwidth)
    h2y->Scale(1./(h2_e2->GetXaxis()->GetBinWidth(1)*part2));
   
    //---- TProfile ---------------------------------------------


    TProfile *P_rat = new TProfile("P_rat","P_rat", 1, 0, 2);

    //---- ratio --------------------------------------------------
    
    TH1D* h3 = (TH1D*) h2y->Clone("h3");
    h3->Divide(h2y,h1y);
    std::cout<<h3->GetNbinsX()<<'\n';

    int a1 = h3->GetNbinsX();
    for (int i=1; i<=a1; i++){
        P_rat->Fill(1, h3->GetBinContent(i));
    }
    
    //---- OS - a*SS --------------------------------------------------
    float a = h3->GetBinContent(1);
    float a_err = h3->GetBinError(1);
    std::cout<<a<<" : "<<a_err<<'\n';

    TH1D* h4 = (TH1D*) h2y->Clone("h4");
    h4->Add(h1y,-a);  

    // c2-------------------------------------------------------------
    
    TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 800, 700);
    h3->SetStats(0);
    h3->SetLineColor(kRed);
    h3->Draw("");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);
    h3->GetYaxis()->SetTitle("#frac{dN_{SS}}{d#Delta#phi}_{|#Delta#eta|<0.5} / #frac{dN_{SS}}{d#Delta#phi}_{|#Delta#eta|>1.5}");
    h3->GetXaxis()->SetTitle("#Delta#phi");

  

    // --------- labels size ------
    h3->GetXaxis()->SetTitleSize(0.05);
    h3->GetXaxis()->SetTitleOffset(0.95);
    h3->GetXaxis()->SetLabelSize(0.05);

    h3->GetYaxis()->SetTitleSize(0.05);
    h3->GetYaxis()->SetTitleOffset(1.5);
    h3->GetYaxis()->SetLabelSize(0.05);

   // c3-------------------------------------------------------------
    
    /* TCanvas *canvas3 = new TCanvas("canvas3", "canvas3", 800, 700); */
    /* h4->SetStats(0); */
    /* h4->SetLineColor(kRed); */
    /* h4->Draw(""); */
    /* gPad->SetTicks(); */
    /* gStyle->SetOptTitle(0); */
    /* h4->GetYaxis()->SetTitle("#frac{dN_{SS}}{d#Delta#phi}_{|#Delta#eta|<0.5} - b* #frac{dN_{SS}}{d#Delta#phi}_{|#Delta#eta|>1.5}"); */
    /* h4->GetXaxis()->SetTitle("#Delta#phi"); */

   /* // c4 --------------------------------------------------------------- */

    /* TCanvas *canvas4 = new TCanvas("canvas4", "canvas4", 800, 700); */
    /* h1y->SetStats(0); */
    /* h1y->SetLineColor(kRed); */
    /* h1y->Draw(""); */
    /* gPad->SetTicks(); */
    /* gStyle->SetOptTitle(0); */
    /* h1y->GetYaxis()->SetTitle("#frac{dN_{SS}}{d#Delta#phi}_{|#Delta#eta|>1.5}"); */
    /* h1y->GetXaxis()->SetTitle("#Delta#phi"); */


}




