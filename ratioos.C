#include "TH1D.h"
#include "RooDataSet.h"
#include "TFile.h"
#include <cmath>
#include <math.h>

void ratioos(){

    //------- Manuel's file -----------------------------------
    TFile *fileNon = TFile::Open("totnon.root");
    TH2D *h2_e1 = (TH2D*)fileNon->Get("h2_etaphiOS2");
    TH2D *h2_e2 = (TH2D*)fileNon->Get("h2_etaphiSS2");
    
    //---- projections ----------------------------------------
    TH1D *h1x = (TH1D*)h2_e1->ProjectionX();
    TH1D *h1y = (TH1D*)h2_e1->ProjectionY();
    TH1D *h2x = (TH1D*)h2_e2->ProjectionX();
    TH1D *h2y = (TH1D*)h2_e2->ProjectionY();
    h1x->Scale(1./(h1x->GetXaxis()->GetBinWidth(1)*10000000));
    h2x->Scale(1./(h2x->GetXaxis()->GetBinWidth(1)*10000000));
    h1y->Scale(1./(h1y->GetXaxis()->GetBinWidth(1)*10000000));
    h2y->Scale(1./(h2y->GetXaxis()->GetBinWidth(1)*10000000));
   
    //---- TProfile ---------------------------------------------

    TProfile *P_rat = new TProfile("P_rat","P_rat", 1, 0, 2);

    //---- ratio --------------------------------------------------
    
    TH1D* h3 = (TH1D*) h1x->Clone("h3");
    h3->Divide(h1x,h2x);
 
    std::cout<<h3->GetNbinsX()<<'\n';

    //float a = h3->GetMean(2);
    //std::cout<<h3->GetMean(1)<<" : "<<a<<'\n';

    int a1 = h3->GetNbinsX();
    for (int i=1; i<a1; i++){
        //std::cout<<h3->GetBinContent(i)<<'\n';
        std::cout<<i<<" : "<<h3->GetBinContent(i)<<'\n';    
        P_rat->Fill(1, h3->GetBinContent(i));
    }
    
    //std::cout<<P_rat->GetBinContent(1)<<'\n';

    //---- OS - a*SS eta --------------------------------------------------
    double a = P_rat->GetBinContent(1);
    double a_err = P_rat->GetBinError(1);
    std::cout<<a<<" : "<<a_err<<'\n';

    TH1D* h4 = (TH1D*) h1x->Clone("h4");
    h4->Add(h2x,-a);  

    //---- OS - a*SS phi -------------------------------------------------
    
    TH1D* h5 = (TH1D*) h1y->Clone("h5");
    h5->Add(h2y, -a);

    // c2-------------------------------------------------------------
    
    TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 800, 700);
    h3->SetStats(0);
    h3->SetLineColor(kRed);
    h3->Draw("");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);
    h3->GetYaxis()->SetTitle("#frac{dN_{OS}}{d#Delta#eta} / #frac{dN_{SS}}{d#Delta#eta}");
    h3->GetXaxis()->SetTitle("#Delta#eta");
   
   // c3-------------------------------------------------------------
    
    TCanvas *canvas3 = new TCanvas("canvas3", "canvas3", 800, 700);
    h4->SetStats(0);
    h4->SetLineColor(kRed);
    h4->Draw("");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);
    h4->GetYaxis()->SetTitle("#frac{dN_{OS}}{d#Delta#eta} - a #frac{dN_{SS}}{d#Delta#eta}");
    h4->GetXaxis()->SetTitle("#Delta#eta");

    // c4---------------------------------------------------------------------------------------
    
    TCanvas *canvas4 = new TCanvas("canvas4", "canvas4", 800, 700);
    h5->SetStats(0);
    h5->SetLineColor(kRed);
    h5->Draw("");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);
    h5->GetYaxis()->SetTitle("#frac{dN_{OS}}{d#Delta#phi} - a #frac{dN_{SS}}{d#Delta#phi}");
    h5->GetXaxis()->SetTitle("#Delta#phi");



}



