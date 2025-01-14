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

void changerange(){

    TH1D *h_cut2  = new TH1D("h_cut2", "h_cut2", 40, -2, 2);

    //----- single events file -----------------------------------

 //------- Manuel's file -----------------------------------
    TFile *fileNon = TFile::Open("Nonsmallar.root");
    /* TH2D *h2_divss = (TH2D*)fileNon->Get("h2_etaphiSS1"); */
    /* TH2D *h2_divss = (TH2D*)fileNon->Get("h2_etaphiSS2"); */
    TH2D *h2_divss = (TH2D*)fileNon->Get("h2_etaphiSS3");
         
   
    double ev1 = 107073000; 
    double ev2 = 94346000;
    double ev5 = 9492190;
    
    double part1 = 229814000;
    double part2 = 458098000;
    double part5 = 161676000;

    h2_divss->Scale(1./part5);
    /* h1x->Scale(1./(part1)); */
    /* h2x->Scale(1./(part2)); */
    /* h1y->Scale(1./(part1)); */
    /* h2y->Scale(1./(part2)); */

    /* h5x->Scale(1./part5); */
    /* h5y->Scale(1./part5); */

   
    //------ ranges ----------------------------------------------
    

    
    /* h2_divss->GetXaxis()->SetRangeUser(1.0,2); */
    
    h2_divss->GetXaxis()->SetRangeUser(-2,-1.0);
    
    //----------------------------------------------------------------
    TH1D *h1_smx = (TH1D*)h2_divss->ProjectionX();
    TH1D *h1_smy = (TH1D*)h2_divss->ProjectionY();
    //h1_smx->Sumw2();  //beggining
    //h1_smy->Sumw2();


    // c1--------------------------------------------------------------
    TCanvas *canvas1 = new TCanvas("canvas1", "canvas1", 800, 700);
    h2_divss->SetStats(0);
    //gStyle->SetPalette(kInvertedDarkBodyRadiator);
    h2_divss->Draw("colz");
    h2_divss->GetYaxis()->SetTitle("#Delta#phi [rad]");
    h2_divss->GetXaxis()->SetTitle("#Delta#eta");
    gStyle->SetOptTitle(0);
    gPad->SetTicks();
    TLatex *lat1 = new TLatex();
	lat1->DrawLatexNDC(.3,.95,"2D Single/Mixed");
    
    //h2_divss->GetYaxis()->SetRangeUser(-M_PI/2,M_PI/2);
    gPad->Modified();

    // c2-------------------------------------------------------------


    TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 800, 700);
    h1_smx->SetStats(0);
    h1_smx->SetLineColor(kBlue);
    h1_smx->GetYaxis()->SetTitle("count");
    h1_smx->GetXaxis()->SetTitle("#Delta#eta");
    h1_smx->Draw("L");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);
    TLatex *lat2 = new TLatex();
	lat2->DrawLatexNDC(.4,.95,"SS single/mixed #Delta#eta");


    // c3--------------------------------------------------------------
    TCanvas *canvas3 = new TCanvas("canvas3", "canvas3", 800, 700);
    h1_smy->SetStats(0);
    h1_smy->SetLineColor(kBlue);
    h1_smy->GetYaxis()->SetTitle("count");
    h1_smy->GetXaxis()->SetTitle("#Delta#phi");
    h1_smy->Draw();
    gPad->SetTicks();
    gStyle->SetOptTitle(0);
    TLatex *lat3 = new TLatex();
	lat3->DrawLatexNDC(.4,.95,"SS single/mixed #Delta#phi");


    TFile* outFile = new TFile("cut3.root", "RECREATE");
    h2_divss->Write();
    h1_smx->Write("h2_divss_px");
    h1_smy->Write("h2_divss_py");
    outFile->Write();
    outFile->Close();

}
