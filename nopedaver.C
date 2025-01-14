#include "TH1D.h"
#include "RooDataSet.h"
#include "TFile.h"
#include <cmath>
#include <math.h>
#include "TMath.h"


double g1(double *x, double *par, double c){
    double r3 = double((x[0] - c)/par[1]);
    return par[0]*TMath::Exp(-0.5*r3*r3);
}

double ffu(double *x, double *par){

    double k1  =  par[0];
    double *k2 = &par[1];

    double re1 = k1 + g1(x,k2,M_PI) + g1(x,k2, -M_PI);
    return re1;

}

void nopedaver(){

    //------- Manuel's file -----------------------------------
    TFile *fileNon = TFile::Open("Nonsmallar.root");
    TH2D *h2_e1 = (TH2D*)fileNon->Get("h2_delsma2");
    TH2D *h2_e2 = (TH2D*)fileNon->Get("h2_dellar2");
    
    TH2D *h1_s = (TH2D*)fileNon->Get("h2_delsma1");
    TH2D *h1_l = (TH2D*)fileNon->Get("h2_dellar1");
    TH2D *h5_s = (TH2D*)fileNon->Get("h2_delsma5");
    TH2D *h5_l = (TH2D*)fileNon->Get("h2_dellar5");
         
    //---- projections ----------------------------------------
    TH1D *h1x = (TH1D*)h2_e1->ProjectionX();
    TH1D *h1y = (TH1D*)h2_e1->ProjectionY();
    TH1D *h2x = (TH1D*)h2_e2->ProjectionX();
    TH1D *h2y = (TH1D*)h2_e2->ProjectionY();
    
    double ev1 = 107073000; 
    double ev2 = 94346000;
    double ev5 = 9492190;
    
    double part1 = 229814000;
    double part2 = 458098000;
    double part5 = 161676000;


    h1x->Scale(1./(part2));
    h2x->Scale(1./(part2));
    h1y->Scale(1./(part2));
    h2y->Scale(1./(part2));
  
    TH1D *h1_sx = (TH1D*)h1_s->ProjectionX();
    TH1D *h1_sy = (TH1D*)h1_s->ProjectionY();
    TH1D *h1_lx = (TH1D*)h1_l->ProjectionX();
    TH1D *h1_ly = (TH1D*)h1_l->ProjectionY();
    h1_sx->Scale(1./(part1));
    h1_lx->Scale(1./(part1));
    h1_sy->Scale(1./(part1));  //quantity for events
    h1_ly->Scale(1./(part1));  //also b have to be with pedestal

    TH1D *h5_sx = (TH1D*)h5_s->ProjectionX();
    TH1D *h5_sy = (TH1D*)h5_s->ProjectionY();
    TH1D *h5_lx = (TH1D*)h5_l->ProjectionX();
    TH1D *h5_ly = (TH1D*)h5_l->ProjectionY();
    h5_sx->Scale(1./(part5));
    h5_lx->Scale(1./(part5));
    h5_sy->Scale(1./(part5));
    h5_ly->Scale(1./(part5));
  


    //---- TProfile ---------------------------------------------

    TProfile *P_rat = new TProfile("P_rat","P_rat", 1, 0, 2);

    TProfile *P_sho = new TProfile("P_sho","P_sho", 1, 0, 2);
    TProfile *P_lar = new TProfile("P_lar","P_lar", 1, 0, 2);

    //---- ratio --------------------------------------------------
    
    TH1D* h3 = (TH1D*) h1y->Clone("h3");
    h3->Divide(h1y,h2y);

    TH1D* h3_sho = (TH1D*) h1_sy->Clone("h3_sho");
    h3_sho->Divide(h1_sy,h1_ly);

    TH1D* h3_lar = (TH1D*) h5_sy->Clone("h3_lar");
    h3_lar->Divide(h5_sy,h5_ly);

    //----- filling the TProfile -------------------------------------
    /* std::cout<<h3->GetNbinsX()<<'\n'; */

    //float a = h3->GetMean(2);
    //std::cout<<h3->GetMean(1)<<" : "<<a<<'\n';

    /* int a1 = h3->GetNbinsX(); */
    /* for (int i=1; i<a1; i++){ */
    /*     //std::cout<<h3->GetBinContent(i)<<'\n'; */
    /*     /1* std::cout<<i<<" : "<<h3->GetBinContent(i)<<'\n'; *1/ */    
    /*     P_rat->Fill(1, h3->GetBinContent(i)); */
    /* } */
    
    /* int a2 = h3_sho->GetNbinsX(); */
    /* for (int i=1; i<a2; i++){ */
    /*     //std::cout<<h3->GetBinContent(i)<<'\n'; */
    /*     /1* std::cout<<i<<" : "<<h3->GetBinContent(i)<<'\n'; *1/ */    
    /*     P_sho->Fill(1, h3_sho->GetBinContent(i)); */
    /* } */
    
    /* int a3 = h3_lar->GetNbinsX(); */
    /* for (int i=1; i<a3; i++){ */
    /*     //std::cout<<h3->GetBinContent(i)<<'\n'; */
    /*     /1* std::cout<<i<<" : "<<h3->GetBinContent(i)<<'\n'; *1/ */    
    /*     P_lar->Fill(1, h3_lar->GetBinContent(i)); */
    /* } */
    /* //std::cout<<P_rat->GetBinContent(1)<<'\n'; */

    /* //---- OS - a*SS eta -------------------------------------------------- */
    /* double a = P_rat->GetBinContent(1); */
    /* double a_err = P_rat->GetBinError(1); */
    /* std::cout<<a<<" : "<<a_err<<'\n'; */

    /* double b_s = P_sho->GetBinContent(1); */
    /* double b_serr = P_sho->GetBinError(1); */
    /* std::cout<<"low"<<'\n'; */
    /* std::cout<<b_s<<" : "<<b_serr<<'\n'; */

    /* double b_l = P_lar->GetBinContent(1); */
    /* double b_lerr = P_lar->GetBinError(1); */
    /* std::cout<<"high"<<'\n'; */
    /* std::cout<<b_l<<" : "<<b_lerr<<'\n'; */

    /* //------------ restas--------------------------------------------------------- */

    /* TH1D* h4 = (TH1D*) h1y->Clone("h4"); */
    /* h4->Add(h2y,-a); */  

    /* TH1D* h1_resta = (TH1D*) h1_sy->Clone("h1_resta"); */
    /* h1_resta->Add(h1_ly, -b_s); */

    /* TH1D* h5_resta = (TH1D*) h5_sy->Clone("h5_resta"); */
    /* h5_resta->Add(h5_ly, -b_l); */

   //------ new plots ---------------------------------------------------------------------------------------------------------------

    //----------- large ---------------------------------------------------------------------------------------------------

        //--------  low -----------------------------------------------------------------
    const int npar = 3;
    double pedes1 = 0.205*pow(10,-3);
    double amp1 = 0.03*pow(10,-3);
    double param1[npar] = {pedes1, amp1, 1.0};

    TF1 *f2 = new TF1("f2", ffu, -M_PI, M_PI, npar); 
    f2->SetParameters(param1);  //center of the G have to be fixed
    f2->SetParNames("Pedestal", "A", "Sigma");

    TCanvas *canvas1 = new TCanvas("canvas1", "canvas1", 800, 700);
    gStyle->SetOptFit(1);
    h1_ly->SetLineColor(kRed);
    h1_ly->Draw("E");
    h1_ly->Fit("f2", "R");
    //gStyle->SetOptFit(1111);
    h1_ly->GetYaxis()->SetTitle("count");
    h1_ly->GetXaxis()->SetTitle("#Delta#phi");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);

    double chi1 = f2->GetChisquare();   //
    double ndf1 = f2->GetNDF();
    std::cout<<"Chisquare low : "<<chi1<<"  Chi/NDF :  "<<chi1/ndf1<<'\n';
         // ----------- medium -------------------------------------------------
    
    double pedes2 = 0.585*pow(10,-3);
    double amp2 = 0.04*pow(10,-3);
    double param2[npar] = {pedes2, amp2, 1.0};

    TF1 *f21 = new TF1("f21", ffu, -M_PI, M_PI, npar); 
    f21->SetParameters(param2);  //center of the G have to be fixed
    f21->SetParNames("Pedestal", "A", "Sigma");

    TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 800, 700);
    gStyle->SetOptFit(1);
    h2y->SetLineColor(kBlack);
    f21->SetLineColor(kBlack);
    h2y->Draw("E");
    h2y->Fit("f21", "R");
    //gStyle->SetOptFit(1111);
    h2y->GetYaxis()->SetTitle("count");
    h2y->GetXaxis()->SetTitle("#Delta#phi");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);

    double chi2 = f21->GetChisquare();   //
    double ndf2 = f21->GetNDF();
    std::cout<<"Chisquare medium: "<<chi2<<"  Chi/NDF :  "<<chi2/ndf2<<'\n';

        //----------- high -------------------------------------------------------
    
    double pedes3 = 0.00245;
    double amp3 = 0.0002;
    double param3[npar] = {pedes3, amp3, 1.0};

    TF1 *f22 = new TF1("f22", ffu, -M_PI, M_PI, npar); 
    f22->SetParameters(param3);  //center of the G have to be fixed
    f22->SetParNames("Pedestal", "A", "Sigma");

    TCanvas *canvas3 = new TCanvas("canvas3", "canvas3", 800, 700);
    gStyle->SetOptFit(1);
    h5_ly->SetLineColor(kBlue);
    f22->SetLineColor(kBlue);
    h5_ly->Draw("E");
    h5_ly->Fit("f22", "R");
    //gStyle->SetOptFit(1111);
    h5_ly->GetYaxis()->SetTitle("count");
    h5_ly->GetXaxis()->SetTitle("#Delta#phi");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);

    double chi3 = f22->GetChisquare();   //
    double ndf3 = f22->GetNDF();
    std::cout<<"Chisquare medium: "<<chi3<<"  Chi/NDF :  "<<chi3/ndf3<<'\n';

   
    // substracting the pedestal ---------------------------------------------------------------------------------------------
    //

    std::cout<<"------------------------------------------- ped --------------"<<'\n';
    
        //creating the new hist----------------------

    TH1D* h1_larped = new TH1D("h1_larped", "h1_larped", 100, -M_PI, M_PI);
    TH1D* h2_larped = new TH1D("h2_larped", "h2_larped", 100, -M_PI, M_PI);
    TH1D* h5_larped = new TH1D("h5_larped", "h5_larped", 100, -M_PI, M_PI);
    
    double ped1 = f2->GetParameter(0);
    double ped2 = f21->GetParameter(0);
    double ped3 = f22->GetParameter(0);

    /* std::cout<<ped1<<'\n'; */
    int bin1 = h5_ly->GetNbinsX();
   
    double sub1 = 0; double sub2 = 0; double sub3 = 0;

    for(int j=1; j<=bin1; j++){
        /* std::cout<<h1_ly->GetBinContent(j)<<'\n'; */
        sub1 = h1_ly->GetBinContent(j) - ped1;
        sub2 = h2y->GetBinContent(j) -ped2;
        sub3 = h5_ly->GetBinContent(j) - ped3;
        h1_larped->SetBinContent(j, sub1);
        h1_larped->SetBinError(j, h1_ly->GetBinError(j));
        h2_larped->SetBinContent(j, sub2);
        h2_larped->SetBinError(j, h2y->GetBinError(j));
        h5_larped->SetBinContent(j, sub3);
        h5_larped->SetBinError(j, h5_ly->GetBinError(j));
    }
    
    
    TCanvas *canvas4 = new TCanvas("canvas4", "canvas4", 800, 700);
    h5_larped->SetStats(0);
    h5_larped->SetLineColor(kBlue);
    h5_larped->Draw("");
    h2_larped->SetLineColor(kBlack);
    h2_larped->Draw("same");
    h1_larped->SetLineColor(kRed);
    h1_larped->Draw("same");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);
    h5_larped->GetYaxis()->SetTitle("#frac{dN_{SS}}{d#Delta#phi_{|#Delta#eta|>1.5}}");
    h5_larped->GetXaxis()->SetTitle("#Delta#phi");
    TLegend *leg3 = new TLegend(0.7, 0.7, 0.9, 0.9);
    leg3->AddEntry(h1_larped, "low multiplicity", "l");
    leg3->AddEntry(h2_larped, "medium multiplicity", "l");
    leg3->AddEntry(h5_larped, "high multiplicity", "l");
    leg3->Draw();


    TProfile *t1p  = new TProfile("t1p", "t1p", 1,0,1);  
   
    int a1 = h2_larped->GetNbinsX();
    double a2, a3;
    double y1 = 0;
    double y2 = 0;
    int co = 1;
    std::cout<<co<<'\n';
    for(int i=1; i<=a1; i++){
        a2 = h2_larped->GetBinCenter(i);
        a3 = h2_larped->GetBinContent(i);
        t1p->Fill(0.5, cos(co*a2), a3);
        //std::cout<<a2<<" "<<a3<<'\n';
        y1 += a3;
    }
   
    TCanvas *canvas5 = new TCanvas("canvas5", "canvas5", 800, 700);
    t1p->Draw();
    double a4 = t1p->GetBinContent(1);
    double a5 = t1p->GetBinError(1);
    std::cout<<"V1 value: "<<'\n';
    std::cout<<a4<<'\n';  


}
