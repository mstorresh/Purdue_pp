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

void merge(){

    TH1D *h_cut2  = new TH1D("h_cut2", "h_cut2", 40, -2, 2);
    TH1D *h_cut3  = new TH1D("h_cut3", "h_cut3", 100, -M_PI, M_PI);

/*
    TFile *file1 = TFile::Open("cut1.root");
    TH1D *h11 = (TH1D*)file1->Get("h2_divss_px");
    TH1D *h12 = (TH1D*)file1->Get("h2_divss_py");
  */  
    TFile *file2 = TFile::Open("cut2.root");
    TH1D *h21 = (TH1D*)file2->Get("h2_divss_px");
    TH1D *h22 = (TH1D*)file2->Get("h2_divss_py");
    
    TFile *file3 = TFile::Open("cut3.root");
    TH1D *h31 = (TH1D*)file3->Get("h2_divss_px");
    TH1D *h32 = (TH1D*)file3->Get("h2_divss_py");
   
    float a1;
    //for(int i=1; i<=h11->GetNbinsX(); i++){ a1 = h11->GetBinContent(i); h_cut2->Fill(a1);}
   

    //for(int i=1; i<=h11->GetNbinsX(); i++){ std::cout<<h_cut2->GetBinContent(i)<<'\n';}
   

    TList *list = new TList;
    //list->Add(h11);
    list->Add(h22);
    list->Add(h32);
    h_cut3->Merge(list);


    TCanvas *canvas1 = new TCanvas("canvas1", "canvas1", 800, 700);

    h_cut3->SetStats(0);
    h_cut3->SetLineColor(kBlue);
    h_cut3->GetYaxis()->SetTitle("count");
    h_cut3->GetXaxis()->SetTitle("#Delta#eta");
    h_cut3->Draw("L");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);

    TFile* outFile = new TFile("largeretaT.root", "RECREATE");
    h_cut3->Write();

}
