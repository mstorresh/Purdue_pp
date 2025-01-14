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

void trackplots(){


//------- Manuel's file -----------------------------------
    TFile *fileNon = TFile::Open("Nonsmallar.root");
    TH2D *h2_ss1 = (TH2D*)fileNon->Get("h2_etaphiSS1");
    TH2D *h2_ss2 = (TH2D*)fileNon->Get("h2_etaphiSS2");
    TH2D *h2_ss3 = (TH2D*)fileNon->Get("h2_etaphiSS3");
    TH2D *h2_ss4 = (TH2D*)fileNon->Get("h2_etaphiSS4");
    TH2D *h2_ss5 = (TH2D*)fileNon->Get("h2_etaphiSS5");

    double part1 = 107073000; 
    double part2 = 94346000;
    double part3 = 56452100;
    double part4 = 21812100;
    double part5 = 9493190;
    
    // double part1 = 229814000;
    // double part2 = 458098000;
    // double part3 = 463920000;
    // double part4 = 265734000;
    // double part5 = 161676000;
    

//------ Nomarlization ----------------------------------------

    h2_ss1->Scale(1./(part1*(h2_ss1->GetXaxis()->GetBinWidth(1))*(h2_ss2->GetYaxis()->GetBinWidth(1))));
    h2_ss2->Scale(1./(part2*(h2_ss2->GetXaxis()->GetBinWidth(1))*(h2_ss2->GetYaxis()->GetBinWidth(1))));
    h2_ss3->Scale(1./(part3*(h2_ss3->GetXaxis()->GetBinWidth(1))*(h2_ss3->GetYaxis()->GetBinWidth(1))));
    h2_ss4->Scale(1./(part4*(h2_ss4->GetXaxis()->GetBinWidth(1))*(h2_ss4->GetYaxis()->GetBinWidth(1))));
    h2_ss5->Scale(1./(part5*(h2_ss5->GetXaxis()->GetBinWidth(1))*(h2_ss5->GetYaxis()->GetBinWidth(1))));


    TCanvas *canvas5 = new TCanvas("canvas5", "canvas5", 800, 700);
    // h2_ss2->SetStats(0);
    gStyle->SetPalette(kInvertedDarkBodyRadiator);
    h2_ss3->Draw("colz");
    h2_ss3->GetYaxis()->SetTitle("#Delta#phi [rad]");
    h2_ss3->GetXaxis()->SetTitle("#Delta#eta");
    gStyle->SetOptTitle(0);
    gPad->SetTicks();

}

