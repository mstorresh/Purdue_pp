#include <string>
#include "TH1D.h"
#include "TFile.h"
#include "TF2.h"
#include "TMath.h"

double g1(double *x, double *par, double c){
    double r3 = double((x[0] - c)/par[1]);
    return par[0]*TMath::Exp(-0.5*r3*r3);
}

double fou(double *x, double *par){
    return 1 + par[0]*TMath::Cos(x[0]) + par[1]*TMath::Cos(2*x[0]) + par[2]*TMath::Cos(3*x[0]);
}


double funf(double *x, double *par){

    double *p1 = &par[0];
    //double *p2 = &par[2];
    //double *p3 = &par[4];
    //double *p4 = &par[8];
    double  p5 = par[2];
    //double *p6 = &par[7];

    double result = p5 + g1(x,p1,0);
    //double result = p4 + g2(x,p1) + g2(x,p2) + TMath::Cos(x[1]);
    return result;

}

double ffu(double *x, double *par){

    double k1  =  par[0];
    double *k2 = &par[1];

    double re1 = k1*fou(x,k2);
    return re1;

}

void onefit(){

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
    TH2D* h2_div = (TH2D*)h2_sin->Clone("h2_divss");
    h2_div->Divide(h2_mix);


    TH1D *h2_divss = (TH1D*)h2_div->ProjectionX();
    

    //for(double i=0.0; i<0.3; i+= 0.01){
    const int npar=3;
    double f2params[npar] = {17.0, 1., 108};
    //double f2params[npar] = {99, 0.01,0.01,0.001};

    TF1 *f2 = new TF1("f2", funf, -M_PI, M_PI, npar); 
    f2->SetParameters(f2params);  //center of the G have to be fixed

    TCanvas *canvas1 = new TCanvas("canvas1", "canvas1", 800, 700);

    h2_divss->Draw("");
    h2_divss->Fit("f2", "R");
    //gStyle->SetOptFit(1111);
    h2_divss->GetYaxis()->SetTitle("count");
    h2_divss->GetXaxis()->SetTitle("#Delta#phi");
    gPad->SetTicks();
    gStyle->SetOptTitle(0);
    TLatex *lat3 = new TLatex();
	lat3->DrawLatexNDC(.4,.95,"Projection in Y real/mixed fit");

    double a1 = f2->GetChisquare();   //
    double a2 = f2->GetProb();
    double ndf = f2->GetNDF();
    std::cout<<"Chisquare : "<<a1<<"  Chi/NDF :  "<<a1/ndf<<'\n';
    std::cout<<"Prob : "<<a2<<'\n';
    
    //}


}
