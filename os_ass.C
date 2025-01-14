#include <string>
#include "TH1D.h"
#include "TFile.h"
#include "TF2.h"
#include "TMath.h"

void os_ass(){

    //--------------------------------
    TFile *file1 = TFile::Open("totnon.root");
    TH2D *h2_sin = (TH2D*)file1->Get("h2_etaphiOS2");
    

    //------- Mixed events file -----------------------------------
    TH2D *h2_mix = (TH2D*)file1->Get("h2_etaphiSS2");
   
    //------- Normalize ----------------------------------------------
    /*
    int n1 = 5000000;
    int MaxBin = h2_mix-> GetMaximumBin();
    int x,y,z;
    h2_mix->GetBinXYZ(MaxBin,x,y,z);
    std::cout<<x<<" "<<y<<'\n';
    h2_sin->Scale(1./(n1*(h2_sin->GetXaxis()->GetBinWidth(1))*(h2_mix->GetYaxis()->GetBinWidth(1))));
    int max1 = h2_mix->GetBinContent(x,y);
    
    h2_mix->Scale(1./max1);
    */
    //

    //----- ratios -------------------------------------------- 
   

    TH2D* h2_divss = (TH2D*)h2_sin->Clone("h2_divss");

    float a = 102.885;
    h2_divss->Add(h2_mix, -a);

    TCanvas *canvas1 = new TCanvas("canvas1", "canvas1", 800, 700);
    h2_divss->SetStats(0);
    gStyle->SetPalette(kInvertedDarkBodyRadiator);
    h2_divss->Draw("colz");
    //gStyle->SetOptFit(1111);
    h2_divss->GetYaxis()->SetTitle("#Delta#phi");
    h2_divss->GetXaxis()->SetTitle("#Delta#eta");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);
    TLatex *lat3 = new TLatex();
	//lat3->DrawLatexNDC(.4,.95,"OS-a*SS");

        //}


}
