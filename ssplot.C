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

void ssplot(){

    //------- Manuel's file -----------------------------------
    TFile *fileNon = TFile::Open("nocutnondiffractive_1.root");
    TH2D *h2_os1 = (TH2D*)fileNon->Get("h2_ss");

    TFile *file2 = TFile::Open("nocutdiffractive_1.root");
    TH2D *h2_os2 = (TH2D*)file2->Get("h2_ss");    
        
    //------------------  normalization ----------------------------
    
        
    int n1 = 289177000;
    /* int MaxBin = h2_os2-> GetMaximumBin(); */
    /* int x,y,z; */
    /* h2_os2->GetBinXYZ(MaxBin,x,y,z); */
    /* std::cout<<x<<" "<<y<<'\n'; */
    h2_os1->Scale(1./(n1*(h2_os1->GetXaxis()->GetBinWidth(1))*(h2_os2->GetYaxis()->GetBinWidth(1))));
    /* int max1 = h2_os2->GetBinContent(x,y); */
    
    /* h2_os2->Scale(1./max1); */
    int n2 = 117941000;
    /* int MaxBin2 = h2_ss2-> GetMaximumBin(); */
    /* int x1,y1,z1; */
    /* h2_ss2->GetBinXYZ(MaxBin2,x1,y1,z1); */
    /* std::cout<<x<<" "<<y<<'\n'; */
    h2_os2->Scale(1./(n2*(h2_os1->GetXaxis()->GetBinWidth(1))*(h2_os2->GetYaxis()->GetBinWidth(1))));
    /* int max2 = h2_ss2->GetBinContent(x,y); */
    
    /* h2_ss2->Scale(1./max2); */
    //-------  projections ----------------------------------
    /* TH1D *h1x = (TH1D*)h2_os1->ProjectionX(); */
    /* TH1D *h1y = (TH1D*)h2_os1->ProjectionY(); */
    /* TH1D *h2x = (TH1D*)h2_os2->ProjectionX(); */
    /* TH1D *h2y = (TH1D*)h2_os2->ProjectionY(); */

    
   
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
    /* gStyle->SetPalette(kInvertedDarkBodyRadiator); */
    h2_os2->Draw("colz");
    h2_os2->GetYaxis()->SetTitle("#Delta#phi [rad]");
    h2_os2->GetXaxis()->SetTitle("#Delta#eta");
    gStyle->SetOptTitle(0);
    gPad->SetTicks();
    //TLatex *lat1 = new TLatex();
	//lat1->DrawLatexNDC(.3,.95,"2D Hitogram TPC 3Cut");

}
