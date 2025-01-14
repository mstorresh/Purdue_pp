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

    double re1 = k1 + g1(x,k2,0);
    return re1;

}

void newresta(){

    //------- Manuel's file -----------------------------------
    TFile *fileNon = TFile::Open("Nonsmallar.root");
    TH2D *h2_e1 = (TH2D*)fileNon->Get("h2_delsma2");
    TH2D *h2_e2 = (TH2D*)fileNon->Get("h2_dellar2");
    
    TH2D *h1_s = (TH2D*)fileNon->Get("h2_delsma1");
    TH2D *h1_l = (TH2D*)fileNon->Get("h2_dellar1");
    TH2D *h5_s = (TH2D*)fileNon->Get("h2_delsma5");
    TH2D *h5_l = (TH2D*)fileNon->Get("h2_dellar5");
         
    
    //---- projections ----------------------------------------
    /* TH1D *h1x = (TH1D*)h2_e1->ProjectionX(); */
    /* TH1D *h1y = (TH1D*)h2_e1->ProjectionY(); */
    /* TH1D *h2x = (TH1D*)h2_e2->ProjectionX(); */
    /* TH1D *h2y = (TH1D*)h2_e2->ProjectionY(); */
    
    double ev1 = 107073000; 
    double ev2 = 94346000;
    double ev5 = 9493190;
    
    double part1 = 229814000;
    double part2 = 458098000;
    double part5 = 161676000;
    
    // ----------- normalization -------------------
    h2_e1->Scale(1./(part2*(h2_e1->GetXaxis()->GetBinWidth(1))*(h2_e1->GetYaxis()->GetBinWidth(1))));
    h2_e2->Scale(1./(part2*(h2_e2->GetXaxis()->GetBinWidth(1))*(h2_e2->GetYaxis()->GetBinWidth(1))));
    h1_s->Scale(1./(part1*(h1_l->GetXaxis()->GetBinWidth(1))*(h1_l->GetYaxis()->GetBinWidth(1))));
    h1_l->Scale(1./(part1*(h1_l->GetXaxis()->GetBinWidth(1))*(h1_l->GetYaxis()->GetBinWidth(1))));
    h5_s->Scale(1./(part5*(h5_s->GetXaxis()->GetBinWidth(1))*(h5_s->GetYaxis()->GetBinWidth(1))));
    h5_l->Scale(1./(part5*(h5_l->GetXaxis()->GetBinWidth(1))*(h5_l->GetYaxis()->GetBinWidth(1))));
    //---- projections ----------------------------------------
    TH1D *h1x = (TH1D*)h2_e1->ProjectionX();
    TH1D *h1y = (TH1D*)h2_e1->ProjectionY();
    TH1D *h2x = (TH1D*)h2_e2->ProjectionX();
    TH1D *h2y = (TH1D*)h2_e2->ProjectionY();

    h1x->Scale(h2_e1->GetYaxis()->GetBinWidth(1));
    h1y->Scale(h2_e1->GetXaxis()->GetBinWidth(1));
    h2x->Scale(h2_e2->GetYaxis()->GetBinWidth(1));
    h2y->Scale(h2_e2->GetXaxis()->GetBinWidth(1));

    
    //-----------------------------------------------

/*     h1x->Scale(1./(part2)); */
/*     h2x->Scale(1./(part2)); */
/*     h1y->Scale(1./(part2)); */
/*     h2y->Scale(1./(part2)); */
  
    TH1D *h1_sx = (TH1D*)h1_s->ProjectionX();
    TH1D *h1_sy = (TH1D*)h1_s->ProjectionY();
    TH1D *h1_lx = (TH1D*)h1_l->ProjectionX();
    TH1D *h1_ly = (TH1D*)h1_l->ProjectionY();
    
    h1_sx->Scale(h1_s->GetYaxis()->GetBinWidth(1));
    h1_sy->Scale(h1_s->GetXaxis()->GetBinWidth(1));
    h1_lx->Scale(h1_l->GetYaxis()->GetBinWidth(1));
    h1_ly->Scale(h1_l->GetXaxis()->GetBinWidth(1));

/*     h1_sx->Scale(1./(part1)); */
/*     h1_lx->Scale(1./(part1)); */
/*     h1_sy->Scale(1./(part1));  //quantity for events */
/*     h1_ly->Scale(1./(part1));  //also b have to be with pedestal */

    TH1D *h5_sx = (TH1D*)h5_s->ProjectionX();
    TH1D *h5_sy = (TH1D*)h5_s->ProjectionY();
    TH1D *h5_lx = (TH1D*)h5_l->ProjectionX();
    TH1D *h5_ly = (TH1D*)h5_l->ProjectionY();

    h5_sx->Scale(h5_s->GetYaxis()->GetBinWidth(1));
    h5_sy->Scale(h5_s->GetXaxis()->GetBinWidth(1));
    h5_lx->Scale(h5_l->GetYaxis()->GetBinWidth(1));
    h5_ly->Scale(h5_l->GetXaxis()->GetBinWidth(1));


/*     h5_sx->Scale(1./(part5)); */
/*     h5_lx->Scale(1./(part5)); */
/*     h5_sy->Scale(1./(part5)); */
/*     h5_ly->Scale(1./(part5)); */
  


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

    int a1 = h3->GetNbinsX();
    for (int i=1; i<a1; i++){
        //std::cout<<h3->GetBinContent(i)<<'\n';
        /* std::cout<<i<<" : "<<h3->GetBinContent(i)<<'\n'; */    
        P_rat->Fill(1, h3->GetBinContent(i));
    }
    
    int a2 = h3_sho->GetNbinsX();
    for (int i=1; i<a2; i++){
        //std::cout<<h3->GetBinContent(i)<<'\n';
        /* std::cout<<i<<" : "<<h3->GetBinContent(i)<<'\n'; */    
        P_sho->Fill(1, h3_sho->GetBinContent(i));
    }
    
    int a3 = h3_lar->GetNbinsX();
    for (int i=1; i<a3; i++){
        //std::cout<<h3->GetBinContent(i)<<'\n';
        /* std::cout<<i<<" : "<<h3->GetBinContent(i)<<'\n'; */    
        P_lar->Fill(1, h3_lar->GetBinContent(i));
    }
    //std::cout<<P_rat->GetBinContent(1)<<'\n';

    //---- OS - a*SS eta --------------------------------------------------
    double a = P_rat->GetBinContent(1);
    double a_err = P_rat->GetBinError(1);
    std::cout<<a<<" : "<<a_err<<'\n';

    double b_s = P_sho->GetBinContent(1);
    double b_serr = P_sho->GetBinError(1);
    std::cout<<"low"<<'\n';
    std::cout<<b_s<<" : "<<b_serr<<'\n';

    double b_l = P_lar->GetBinContent(1);
    double b_lerr = P_lar->GetBinError(1);
    std::cout<<"high"<<'\n';
    std::cout<<b_l<<" : "<<b_lerr<<'\n';





    //------------ restas---------------------------------------------------------

    TH1D* h4 = (TH1D*) h1y->Clone("h4");
    h4->Add(h2y,-a);  

    TH1D* h1_resta = (TH1D*) h1_sy->Clone("h1_resta");
    h1_resta->Add(h1_ly, -b_s);

    TH1D* h5_resta = (TH1D*) h5_sy->Clone("h5_resta");
    h5_resta->Add(h5_ly, -b_l);

   //------ new plots ---------------------------------------------------------------------------------------------------------------

    //----------- large ---------------------------------------------------------------------------------------------------

    

    //--------  low -----------------------------------------------------------------
    const int npar = 3;
    double pedes1 = -0.01*pow(10,-3);
    double amp1 = 0.02*pow(10,-3);
    double param1[npar] = {pedes1, amp1, 1.0};

    TF1 *f2 = new TF1("f2", ffu, -M_PI, M_PI, npar); 
    f2->SetParameters(param1);  //center of the G have to be fixed
    f2->SetParNames("Pedestal", "A", "Sigma");

    TCanvas *canvas1 = new TCanvas("canvas1", "canvas1", 800, 700);
    gStyle->SetOptFit(1);
    h1_resta->SetLineColor(kRed);
    h1_resta->Draw("E");
    h1_resta->Fit("f2", "R");
    //gStyle->SetOptFit(1111);
    h1_resta->GetYaxis()->SetTitle("count");
    h1_resta->GetXaxis()->SetTitle("#Delta#phi");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);

    double chi1 = f2->GetChisquare();   //
    double ndf1 = f2->GetNDF();
    std::cout<<"Chisquare low : "<<chi1<<"  Chi/NDF :  "<<chi1/ndf1<<'\n';
         // ----------- medium -------------------------------------------------
    
    double pedes2 = -0.04*pow(10,-3);
    double amp2 = 0.14*pow(10,-3);
    double param2[npar] = {pedes2, amp2, 1.0};

    TF1 *f21 = new TF1("f21", ffu, -M_PI, M_PI, npar); 
    f21->SetParameters(param2);  //center of the G have to be fixed
    f21->SetParNames("Pedestal", "A", "Sigma");

    TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 800, 700);
    gStyle->SetOptFit(1);
    h4->SetLineColor(kBlack);
    f21->SetLineColor(kBlack);
    h4->Draw("E");
    h4->Fit("f21", "R");
    //gStyle->SetOptFit(1111);
    h4->GetYaxis()->SetTitle("count");
    h4->GetXaxis()->SetTitle("#Delta#phi");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);

    double chi2 = f21->GetChisquare();   //
    double ndf2 = f21->GetNDF();
    std::cout<<"Chisquare medium: "<<chi2<<"  Chi/NDF :  "<<chi2/ndf2<<'\n';

        //----------- high -------------------------------------------------------
    
    double pedes3 = -0.4*pow(10,-0.3);
    double amp3 = 0.5*pow(10, -0.3);
    double param3[npar] = {pedes3, amp3, 1.0};

    TF1 *f22 = new TF1("f22", ffu, -M_PI, M_PI, npar); 
    f22->SetParameters(param3);  //center of the G have to be fixed
    f22->SetParNames("Pedestal", "A", "Sigma");

    TCanvas *canvas3 = new TCanvas("canvas3", "canvas3", 800, 700);
    gStyle->SetOptFit(1);
    h5_resta->SetLineColor(kBlue);
    f22->SetLineColor(kBlue);
    h5_resta->Draw("E");
    h5_resta->Fit("f22", "R");
    //gStyle->SetOptFit(1111);
    h5_resta->GetYaxis()->SetTitle("count");
    h5_resta->GetXaxis()->SetTitle("#Delta#phi");
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
        sub1 = h1_resta->GetBinContent(j) - ped1;
        sub2 = h4->GetBinContent(j) -ped2;
        sub3 = h5_resta->GetBinContent(j) - ped3;
        h1_larped->SetBinContent(j, sub1);
        h1_larped->SetBinError(j, h1_resta->GetBinError(j));
        h2_larped->SetBinContent(j, sub2);
        h2_larped->SetBinError(j, h4->GetBinError(j));
        h5_larped->SetBinContent(j, sub3);
        h5_larped->SetBinError(j, h5_resta->GetBinError(j));
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
    h1_larped->GetYaxis()->SetTitle("#frac{dN_{SS}}{d #Delta #Phi_{|#Delta #eta<0.5}}/#frac{dN_{SS}}{d #Delta #Phi_{|#Delta #eta>1.5}}");
    h1_larped->GetXaxis()->SetTitle("#Delta#phi");
    TLegend *leg3 = new TLegend(0.7, 0.7, 0.9, 0.9);
    leg3->AddEntry(h1_larped, "low multiplicity", "l");
    leg3->AddEntry(h2_larped, "medium multiplicity", "l");
    leg3->AddEntry(h5_larped, "high multiplicity", "l");
    leg3->Draw();

   
    TCanvas *canvas5 = new TCanvas("canvas5", "canvas5", 800, 700);
    h2_e1->SetStats(0);
    /* gStyle->SetPalette(kInvertedDarkBodyRadiator); */
    h2_e1->Draw("colz");
    h2_e1->GetYaxis()->SetTitle("#Delta#phi [rad]");
    h2_e1->GetXaxis()->SetTitle("#Delta#eta");
    /* gStyle->SetOptTitle(0); */
    gPad->SetTicks(); 
    
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
