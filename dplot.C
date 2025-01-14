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

void dplot(){

    //------- Manuel's file -----------------------------------
    TFile *fileNon = TFile::Open("nocutnondiffractive_1.root");
    TH2D *h2_os1 = (TH2D*)fileNon->Get("h2_etaphiN2");
    TH2D *h2_ss1 = (TH2D*)fileNon->Get("h2_etaphiP2");

    TFile *file2 = TFile::Open("outnondiffractive_1.root");
    TH2D *h2_os2 = (TH2D*)file2->Get("h2_etaphiN2");    
    TH2D *h2_ss2 = (TH2D*)file2->Get("h2_etaphiP2");    
        
    //------------------  normalization ----------------------------
    
        
    int n1 = 94346000;
    int MaxBin = h2_os2-> GetMaximumBin();
    int x,y,z;
    h2_os2->GetBinXYZ(MaxBin,x,y,z);
    std::cout<<x<<" "<<y<<'\n';
    h2_os1->Scale(1./(n1*(h2_os1->GetXaxis()->GetBinWidth(1))*(h2_os2->GetYaxis()->GetBinWidth(1))));
    int max1 = h2_os2->GetBinContent(x,y);
    
    h2_os2->Scale(1./max1);
    
    int MaxBin2 = h2_ss2-> GetMaximumBin();
    int x1,y1,z1;
    h2_ss2->GetBinXYZ(MaxBin2,x1,y1,z1);
    std::cout<<x<<" "<<y<<'\n';
    h2_ss1->Scale(1./(n1*(h2_ss1->GetXaxis()->GetBinWidth(1))*(h2_ss2->GetYaxis()->GetBinWidth(1))));
    int max2 = h2_ss2->GetBinContent(x,y);
    
    h2_ss2->Scale(1./max2);
    //-------  projections ----------------------------------
    TH1D *h1x = (TH1D*)h2_os1->ProjectionX();
    TH1D *h1y = (TH1D*)h2_os1->ProjectionY();
    TH1D *h2x = (TH1D*)h2_os2->ProjectionX();
    TH1D *h2y = (TH1D*)h2_os2->ProjectionY();

    
   // ----------- ratio --------------------------------------
    
    TH2D *hd_os = (TH2D*)h2_os1->Clone("hd_os");
    hd_os->Divide(h2_os2);

    TH1D *phx_os = (TH1D*)hd_os->ProjectionX();
    TH1D *phy_os = (TH1D*)hd_os->ProjectionY();
    
    TH2D *hd_ss = (TH2D*)h2_ss1->Clone("hd_ss");
    hd_ss->Divide(h2_ss2);

    TH1D *phx_ss = (TH1D*)hd_ss->ProjectionX();
    TH1D *phy_ss = (TH1D*)hd_ss->ProjectionY();


    //------------- resta 2d -----------------------------------

    TH2D *his_os = (TH2D*)hd_os->Clone("his_os");
    his_os->Add(hd_ss, -1);
    
    TH1D *phis_x = (TH1D*)his_os->ProjectionX();
    TH1D *phis_y = (TH1D*)his_os->ProjectionY();
    


    // -------- diference ---------------------------------------

    TH1D *Hx_os = (TH1D*)phx_os->Clone("Hx_os");
    TH1D *Hy_os = (TH1D*)phy_os->Clone("Hy_os");
    Hx_os->Add(phx_ss, -1);
    Hy_os->Add(phy_ss, -1);



    // --- plot projections ----------------------------------------------



    // c1--------------------------------------------------------------
    TCanvas *canvas1 = new TCanvas("canvas1", "canvas1", 800, 700);
    //h2_os1->SetStats(0);
    //gStyle->SetPalette(kInvertedDarkBodyRadiator);
    h2_os1->Draw("colz");
    h2_os1->GetYaxis()->SetTitle("#Delta#phi [rad]");
    h2_os1->GetXaxis()->SetTitle("#Delta#eta");
    gStyle->SetOptTitle(0);
    gPad->SetTicks();
    //TLatex *lat1 = new TLatex();
	//lat1->DrawLatexNDC(.3,.95,"2D Hitogram TPC 3Cut");
    
    TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 800, 700);
    //h2_os2->SetStats(0);
    gStyle->SetPalette(kInvertedDarkBodyRadiator);
    h2_os1->Draw("colz");
    h2_os1->GetYaxis()->SetTitle("#Delta#phi [rad]");
    h2_os1->GetXaxis()->SetTitle("#Delta#eta");
    gStyle->SetOptTitle(0);
    gPad->SetTicks();
    //TLatex *lat1 = new TLatex();
	//lat1->DrawLatexNDC(.3,.95,"2D Hitogram TPC 3Cut");
  
    /* // c2------------------------------------------------------------- */

    float ymax= h1x->GetMaximum();
    float ymin= h1x->GetMinimum();

    /* TCanvas *canvas4 = new TCanvas("canvas4", "canvas4", 800, 700); */
    /* h1x->SetStats(0); */
    /* h1x->SetLineColor(kRed); */
    /* h1x->GetYaxis()->SetTitle("count"); */
    /* h1x->GetXaxis()->SetTitle("#Delta#eta"); */
    /* h1x->Draw("L"); */
    /* gPad->SetTicks(); */
    /* gStyle->SetOptTitle(0); */
    /* /1* TLatex *lat2 = new TLatex(); *1/ */
	/* /1* lat2->DrawLatexNDC(.4,.95,"Projection in X"); *1/ */
    /* float chosenEff = 0.0; */
    /* canvas2->Update(); */
    /* TLine *line1 = new TLine(chosenEff, ymin,chosenEff, ymax); */
    /* line1->SetLineColor(kBlack); */
    /* line1->SetLineStyle(9); */
    /* line1->Draw("same"); */


    /* // c3-------------------------------------------------------------- */
    /* TCanvas *canvas3 = new TCanvas("canvas3", "canvas3", 800, 700); */
    /* h1y->SetStats(0); */
    /* h1y->SetLineColor(kRed); */
    /* h1y->GetYaxis()->SetTitle("count"); */
    /* h1y->GetXaxis()->SetTitle("#Delta#phi"); */
    /* h1y->Draw(); */
    /* gPad->SetTicks(); */
    /* gStyle->SetOptTitle(0); */
    /* /1* TLatex *lat3 = new TLatex(); *1/ */
	/* lat3->DrawLatexNDC(.4,.95,"Projection in Y"); */

  
   //----------------------- real/mixed --------------------------------------------
   //
   
    
    TCanvas *canvas5 = new TCanvas("canvas5", "canvas5", 800, 700);
    hd_os->SetStats(0);
    gStyle->SetPalette(kInvertedDarkBodyRadiator);
    hd_ss->Draw("colz");
    hd_ss->GetYaxis()->SetTitle("#Delta#phi [rad]");
    hd_ss->GetXaxis()->SetTitle("#Delta#eta");
    gStyle->SetOptTitle(0);
    gPad->SetTicks();


    TCanvas *canvas6 = new TCanvas("canvas6", "canvas6", 800, 700);
    phx_ss->SetStats(0);
    phx_ss->SetLineColor(kRed);
    phx_ss->GetYaxis()->SetTitle("count");
    phx_ss->GetXaxis()->SetTitle("#Delta#eta");
    phx_ss->Draw();
    gPad->SetTicks();
    gStyle->SetOptTitle(0);
    
    TCanvas *canvas7 = new TCanvas("canvas7", "canvas7", 800, 700);
    phy_ss->SetStats(0);
    phy_ss->SetLineColor(kRed);
    phy_ss->GetYaxis()->SetTitle("count");
    phy_ss->GetXaxis()->SetTitle("#Delta#phi");
    phy_ss->Draw();
    gPad->SetTicks();
    gStyle->SetOptTitle(0);

//--------- difference proj ------------------------------------------------------------------------------------------------


    /* TCanvas *canvas6 = new TCanvas("canvas6", "canvas6", 800, 700); */
    /* phis_x->SetStats(0); */
    /* phis_x->SetLineColor(kBlue); */
    /* phis_x->GetYaxis()->SetTitle("count"); */
    /* phis_x->GetXaxis()->SetTitle("#Delta#eta"); */
    /* phis_x->Draw(); */
    /* gPad->SetTicks(); */
    /* gStyle->SetOptTitle(0); */
    
    /* TCanvas *canvas7 = new TCanvas("canvas7", "canvas7", 800, 700); */
    /* phis_y->SetStats(0); */
    /* phis_y->SetLineColor(kBlue); */
    /* phis_y->GetYaxis()->SetTitle("count"); */
    /* phis_y->GetXaxis()->SetTitle("#Delta#phi"); */
    /* phis_y->Draw(); */
    /* gPad->SetTicks(); */
    /* gStyle->SetOptTitle(0); */
    




}
