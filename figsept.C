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
    double *k3 = &par[3];

    double re1 = k1 + g1(x,k2,M_PI) + g1(x,k2,-M_PI) + g1(x,k3,0);
    return re1;

}

void figsept(){

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


/*     //------------ restas--------------------------------------------------------- */

/*     TH1D* h4 = (TH1D*) h1y->Clone("h4"); */
/*     h4->Add(h2y,-a); */  

/*     TH1D* h1_resta = (TH1D*) h1_sy->Clone("h1_resta"); */
/*     h1_resta->Add(h1_ly, -b_s); */

/*     TH1D* h5_resta = (TH1D*) h5_sy->Clone("h5_resta"); */
/*     h5_resta->Add(h5_ly, -b_l); */

   //------ new plots ---------------------------------------------------------------------------------------------------------------

    //----------- large ---------------------------------------------------------------------------------------------------

    

    //--------  low -----------------------------------------------------------------
    const int npar = 5;
    double pedes1 = 0.0013;
    double amp1 = 0.00012;
    double param1[npar] = {pedes1, amp1, 1.0, 0.00001, 1.0};

    TF1 *f2 = new TF1("f2", ffu, -M_PI, M_PI, npar); 
    f2->SetParameters(param1);  //center of the G have to be fixed
    f2->SetParNames("Pedestal", "A", "Sigma");

    TCanvas *canvas1 = new TCanvas("canvas1", "canvas1", 800, 700);
    gStyle->SetOptFit(1);
    h1_sy->SetLineColor(kRed);
    h1_sy->Draw("E");
    h1_sy->Fit("f2", "R");
    //gStyle->SetOptFit(1111);
    h1_sy->GetYaxis()->SetTitle("count");
    h1_sy->GetXaxis()->SetTitle("#Delta#phi");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);

    double chi1 = f2->GetChisquare();   //
    double ndf1 = f2->GetNDF();
    std::cout<<"Chisquare low : "<<chi1<<"  Chi/NDF :  "<<chi1/ndf1<<'\n';
         // ----------- medium -------------------------------------------------
    
    double pedes2 = 0.0039;
    double amp2 = 0.0003;
    double param2[npar] = {pedes2, amp2, 1.0, 0.00005, 1.0};

    TF1 *f21 = new TF1("f21", ffu, -M_PI, M_PI, npar); 
    f21->SetParameters(param2);  //center of the G have to be fixed
    f21->SetParNames("Pedestal", "A", "Sigma");

    TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 800, 700);
    gStyle->SetOptFit(1);
    h1y->SetLineColor(kBlack);
    f21->SetLineColor(kBlack);
    h1y->Draw("E");
    h1y->Fit("f21", "R");
    //gStyle->SetOptFit(1111);
    h1y->GetYaxis()->SetTitle("count");
    h1y->GetXaxis()->SetTitle("#Delta#phi");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);

    double chi2 = f21->GetChisquare();   //
    double ndf2 = f21->GetNDF();
    std::cout<<"Chisquare medium: "<<chi2<<"  Chi/NDF :  "<<chi2/ndf2<<'\n';

        //----------- high -------------------------------------------------------
    
    double pedes3 = 0.0183;
    double amp3 = 0.002;
    double param3[npar] = {pedes3, amp3, 1.0, 0.0025, 1.0};

    TF1 *f22 = new TF1("f22", ffu, -M_PI, M_PI, npar); 
    f22->SetParameters(param3);  //center of the G have to be fixed
    f22->SetParNames("Pedestal", "A", "Sigma");

    TCanvas *canvas3 = new TCanvas("canvas3", "canvas3", 800, 700);
    gStyle->SetOptFit(1);
    h5_sy->SetLineColor(kBlue);
    f22->SetLineColor(kBlue);
    h5_sy->Draw("E");
    h5_sy->Fit("f22", "R");
    //gStyle->SetOptFit(1111);
    h5_sy->GetYaxis()->SetTitle("count");
    h5_sy->GetXaxis()->SetTitle("#Delta#phi");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);

    double chi3 = f22->GetChisquare();   //
    double ndf3 = f22->GetNDF();
    std::cout<<"Chisquare medium: "<<chi3<<"  Chi/NDF :  "<<chi3/ndf3<<'\n';
    double sub1; double sub2; double sub3;
    double ped1 = f2->GetParameter(0);
    double ped2 = f21->GetParameter(0);
    double ped3 = f22->GetParameter(0);
    
    //------------ restas---------------------------------------------------------

    TH1D* h1_l2 = new TH1D("h1_larped", "h1_larped", 100, -M_PI, M_PI);
    TH1D* h2_l2 = new TH1D("h2_larped", "h2_larped", 100, -M_PI, M_PI);
    TH1D* h5_l2 = new TH1D("h5_larped", "h5_larped", 100, -M_PI, M_PI);
    int bin1 = h5_sy->GetNbinsX();
    for(int j=1; j<=bin1; j++){
        /* std::cout<<h1_ly->GetBinContent(j)<<'\n'; */
        sub1 = h1_sy->GetBinContent(j);
        sub2 = h1y->GetBinContent(j);
        sub3 = h5_sy->GetBinContent(j);
        h1_l2->SetBinContent(j, sub1);
        h1_l2->SetBinError(j, h1_sy->GetBinError(j));
        h2_l2->SetBinContent(j, sub2);
        h2_l2->SetBinError(j, h1y->GetBinError(j));
        h5_l2->SetBinContent(j, sub3);
        h5_l2->SetBinError(j, h5_sy->GetBinError(j));
    }

    TH1D* h4 = (TH1D*) h2_l2->Clone("h4");
    h4->Add(h2y,-ped2);  

    TH1D* h1_resta = (TH1D*) h1_l2->Clone("h1_resta");
    h1_resta->Add(h1_ly, -ped1);

    TH1D* h5_resta = (TH1D*) h5_l2->Clone("h5_resta");
    h5_resta->Add(h5_ly, -ped3);




    TCanvas *canvas4 = new TCanvas("canvas4", "canvas4", 800, 700);
    h5_resta->SetStats(0);
    h5_resta->SetLineColor(kRed);
    h5_resta->Draw("E");
    h4->SetLineColor(kBlack);
    h4->Draw("E same");
    h1_resta->SetLineColor(kBlue);
    h1_resta->Draw("E same");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);
    h5_resta->GetYaxis()->SetTitle("#frac{dN_{SS}}{d #Delta #Phi_{|#Delta #eta<0.5}}/#frac{dN_{SS}}{d #Delta #Phi_{|#Delta #eta>1.5}}");
    h5_resta->GetXaxis()->SetTitle("#Delta#phi");
    TLegend *leg3 = new TLegend(0.7, 0.7, 0.9, 0.9);
    leg3->AddEntry(h1_resta, "low multiplicity", "l");
    leg3->AddEntry(h4, "medium multiplicity", "l");
    leg3->AddEntry(h5_resta, "high multiplicity", "l");
    leg3->Draw();

   
   
    
    // ratio ---------------------------------------------------------------------
        //---------- low ---------------------------------------------------------
    /* const int npar = 3; */

    /* double param1[npar] = {6.3, 0.5, 0.5}; */

    /* TF1 *f2 = new TF1("f2", ffu, -M_PI, M_PI, npar); */ 
    /* f2->SetParameters(param1);  //center of the G have to be fixed */

    /* TCanvas *canvas1 = new TCanvas("canvas1", "canvas1", 800, 700); */

    /* h3_sho->Draw(""); */
    /* h3_sho->Fit("f2", "R"); */
    /* //gStyle->SetOptFit(1111); */
    /* h3_sho->GetYaxis()->SetTitle("count"); */
    /* h3_sho->GetXaxis()->SetTitle("#Delta#phi"); */
    /* gPad->SetTicks(); */
    /* gStyle->SetOptTitle(0); */

    /* double chi1 = f2->GetChisquare();   // */
    /* double ndf1 = f2->GetNDF(); */
    /* std::cout<<"Chisquare low : "<<chi1<<"  Chi/NDF :  "<<chi1/ndf1<<'\n'; */
    
    /*     // ----------- medium ------------------------------------------------- */
    /* double param2[npar] = {6.55, 0.5, 0.5}; */

    /* TF1 *f21 = new TF1("f21", ffu, -M_PI, M_PI, npar); */ 
    /* f21->SetParameters(param2);  //center of the G have to be fixed */

    /* TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 800, 700); */

    /* h3->Draw(""); */
    /* h3->Fit("f21", "R"); */
    /* //gStyle->SetOptFit(1111); */
    /* h3->GetYaxis()->SetTitle("count"); */
    /* h3->GetXaxis()->SetTitle("#Delta#phi"); */
    /* gPad->SetTicks(); */
    /* gStyle->SetOptTitle(0); */

    /* double chi2 = f21->GetChisquare();   // */
    /* double ndf2 = f21->GetNDF(); */
    /* std::cout<<"Chisquare medium: "<<chi2<<"  Chi/NDF :  "<<chi2/ndf2<<'\n'; */

    /*     //----------- high ------------------------------------------------------- */
    /* double param3[npar] = {7.2, 0.5, 0.5}; */

    /* TF1 *f22 = new TF1("f22", ffu, -M_PI, M_PI, npar); */ 
    /* f22->SetParameters(param3);  //center of the G have to be fixed */

    /* TCanvas *canvas3 = new TCanvas("canvas3", "canvas3", 800, 700); */

    /* h3_lar->Draw(""); */
    /* h3_lar->Fit("f22", "R"); */
    /* //gStyle->SetOptFit(1111); */
    /* h3_lar->GetYaxis()->SetTitle("count"); */
    /* h3_lar->GetXaxis()->SetTitle("#Delta#phi"); */
    /* gPad->SetTicks(); */
    /* gStyle->SetOptTitle(0); */

    /* double chi3 = f22->GetChisquare();   // */
    /* double ndf3 = f22->GetNDF(); */
    /* std::cout<<"Chisquare medium: "<<chi3<<"  Chi/NDF :  "<<chi3/ndf3<<'\n'; */




    //------ old plots ------------------------------------------------------------------------------------------------------------



    // c2-------------------------------------------------------------
    
    /* TCanvas *canvas7 = new TCanvas("canvas7", "canvas7", 800, 700); */
    /* h3->SetStats(0); */
    /* h3->SetLineColor(kRed); */
    /* h3->Draw(""); */
    /* gPad->SetTicks(); */
    /* gStyle->SetOptTitle(0); */
    /* h3->GetYaxis()->SetTitle("#frac{dN_{SS}}{d#Delta#phi_{|#Delta#eta|<0.5}} / #frac{dN_{SS}}{d#Delta#phi_{|#Delta#eta|>1.5}}"); */
    /* h3->GetXaxis()->SetTitle("#Delta#phi"); */
   
   /* // c3------------------------------------------------------------- */
    
    /* TCanvas *canvas8 = new TCanvas("canvas8", "canvas8", 800, 700); */
    /* h4->SetStats(0); */
    /* h4->SetLineColor(kRed); */
    /* h4->Draw(""); */
    /* gPad->SetTicks(); */
    /* gStyle->SetOptTitle(0); */
    /* h4->GetYaxis()->SetTitle("#frac{dN_{SS}}{d#Delta#phi_{|#Delta#eta|<0.5}} - b #frac{dN_{SS}}{d#Delta#phi_{|#Delta#eta|>1.5}}"); */
    /* h4->GetXaxis()->SetTitle("#Delta#phi"); */

    /* TCanvas *canvas9 = new TCanvas("canvas9", "canvas9", 800, 700); */
    /* h2y->SetStats(0); */
    /* h2y->SetLineColor(kRed); */
    /* h2y->Draw(""); */
    /* gPad->SetTicks(); */
    /* gStyle->SetOptTitle(0); */
    /* h2y->GetYaxis()->SetTitle("#frac{dN_{SS}}{d#Delta#phi_{|#Delta#eta|>1.5}}"); */
    /* h2y->GetXaxis()->SetTitle("#Delta#phi"); */


/* //--------- scale ------------- */
/*     h3_lar->Scale(0.86); */
/*     h5_resta->Scale(0.05); */    
/*     h5_ly->Scale(0.1185); */
/*     h3->Scale(0.96); */
/*     h2y->Scale(2.8); */

/*     //------- divide small/larger ---------------------------------------------------------------------------------------------- */


/*     TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 800, 700); */
/*     h3_sho->SetStats(0); */
/*     h3_sho->SetLineColor(kRed); */
/*     h3_sho->Draw(""); */
/*     h3_lar->SetLineColor(kBlue); */
/*     h3_lar->Draw("same"); */
/*     h3->SetLineColor(kBlack); */
/*     h3->Draw("same"); */
/*     gPad->SetTicks(); */
/*     gStyle->SetOptTitle(0); */
/*     h3_sho->GetYaxis()->SetTitle("#frac{dN_{SS}}{d#Delta#phi_{|#Delta#eta|<0.5}} / #frac{dN_{SS}}{d#Delta#phi_{|#Delta#eta|>1.5}}"); */
/*     h3_sho->GetXaxis()->SetTitle("#Delta#phi"); */
/*     TLegend *leg1 = new TLegend(0.7, 0.7, 0.9, 0.9); */
/*     leg1->AddEntry(h3_sho, "low multiplicity", "l"); */
/*     leg1->AddEntry(h3, "medium multiplicity", "l"); */
/*     leg1->AddEntry(h3_lar, "high multiplicity", "l"); */
/*     leg1->Draw(); */


/*     TCanvas *canvas3 = new TCanvas("canvas3", "canvas3", 800, 700); */
/*     h1_resta->SetStats(0); */
/*     h1_resta->SetLineColor(kRed); */
/*     h1_resta->Draw(""); */
/*     h5_resta->SetLineColor(kBlue); */
/*     h5_resta->Draw("same"); */
/*     h4->SetLineColor(kBlack); */
/*     h4->Draw("same"); */
/*     gPad->SetTicks(); */
/*     gStyle->SetOptTitle(0); */
/*     h1_resta->GetYaxis()->SetTitle("#frac{dN_{SS}}{d#Delta#phi_{|#Delta#eta|<0.5}} - b #frac{dN_{SS}}{d#Delta#phi_{|#Delta#eta|>1.5}}"); */
/*     h1_resta->GetXaxis()->SetTitle("#Delta#phi"); */
/*     TLegend *leg2 = new TLegend(0.7, 0.7, 0.9, 0.9); */
/*     leg2->AddEntry(h1_resta, "low multiplicity", "l"); */
/*     leg2->AddEntry(h4, "medium multiplicity", "l"); */
/*     leg2->AddEntry(h5_resta, "high multiplicity", "l"); */
/*     leg2->Draw(); */


/*     TCanvas *canvas4 = new TCanvas("canvas4", "canvas4", 800, 700); */
/*     h2y->SetStats(0); */
/*     h1_ly->SetLineColor(kRed); */
/*     h1_ly->Draw(""); */
/*     h5_ly->SetLineColor(kBlue); */
/*     h5_ly->Draw("same"); */
/*     h2y->SetLineColor(kBlack); */
/*     h2y->Draw("same"); */
/*     gPad->SetTicks(); */
/*     gStyle->SetOptTitle(0); */
/*     h2y->GetYaxis()->SetTitle("#frac{dN_{SS}}{d#Delta#phi_{|#Delta#eta|>1.5}}"); */
/*     h2y->GetXaxis()->SetTitle("#Delta#phi"); */
/*     TLegend *leg3 = new TLegend(0.7, 0.7, 0.9, 0.9); */
/*     leg3->AddEntry(h1_ly, "low multiplicity", "l"); */
/*     leg3->AddEntry(h2y, "medium multiplicity", "l"); */
/*     leg3->AddEntry(h5_ly, "high multiplicity", "l"); */
/*     leg3->Draw(); */



}
