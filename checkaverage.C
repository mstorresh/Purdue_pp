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

void checkaverage(){

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

    //------------ average ---------------------------------------------------------

    TProfile *t1p  = new TProfile("t1p", "t1p", 1,0,1);

    int a1 = h5_ly->GetNbinsX();
    double a2, a3;
    double y1 = 0;
    double y2 = 0;
    int co = 1;
    std::cout<<co<<'\n';
    for(int i=1; i<=a1; i++){
        a2 = h5_ly->GetBinCenter(i);
        a3 = h5_ly->GetBinContent(i);
        t1p->Fill(0.5, cos(co*a2), a3);
        /* std::cout<<a2<<" "<<a3<<'\n'; */
        y1 += a3;
    }

    double p1, p2;
    t1p->Draw();
    double a4 = t1p->GetBinContent(1);
    double a5 = t1p->GetBinError(1);
    std::cout<<a4<<'\n';


    /* TProfile *t2p  = new TProfile("t2p", "t2p", 1,0,1); */

    /* int a1 = h5_ly->GetNbinsX(); */
    /* double a2, a3; */
    /* double y1 = 0; */
    /* double y2 = 0; */
    /* int co = 3; */
    /* std::cout<<co<<'\n'; */
    /* for(int i=1; i<=a1; i++){ */
    /*     a2 = h5_ly->GetBinCenter(i); */
    /*     a3 = h5_ly->GetBinContent(i); */
    /*     t1p->Fill(0.5, cos(co*a2), a3); */
    /*     //std::cout<<a2<<" "<<a3<<'\n'; */
    /*     y1 += a3; */
    /* } */

    /* double p1, p2; */
    /* t1p->Draw(); */
    /* double a4 = t1p->GetBinContent(1); */
    /* double a5 = t1p->GetBinError(1); */
    /* std::cout<<a4<<'\n'; */




}
