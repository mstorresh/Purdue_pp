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

void mulplots(){

    //------- NON diffractive file  -----------------------------------
    TFile *fileNon = TFile::Open("totnon.root");
    TH1D *h_mulfullNon = (TH1D*)fileNon->Get("h_mulfull");
    TH1D *h_mulfinNon  = (TH1D*)fileNon->Get("h_mulfin");
    TH1D *h_mulppkNon  = (TH1D*)fileNon->Get("h_mulppk");
    TH1D *h_multpcNon  = (TH1D*)fileNon->Get("h_multpc");
    TH1D *h_mulpoiNon  = (TH1D*)fileNon->Get("h_mulpoi");
    //h_mulfullNon->SetBins(500,0,500);
    //----- diffractive file ---------------------------------------------

    TFile *fileD = TFile::Open("totdif.root");
    
    TH1D *h_mulfullD = (TH1D*)fileD->Get("h_mulfull");
    TH1D *h_mulfinD  = (TH1D*)fileD->Get("h_mulfin");
    TH1D *h_mulppkD  = (TH1D*)fileD->Get("h_mulppk");
    TH1D *h_multpcD  = (TH1D*)fileD->Get("h_multpc");
    TH1D *h_mulpoiD  = (TH1D*)fileD->Get("h_mulpoi");

    //--- rebin ----------------------------------------------------------------
    
    double xbins[200]; double xbins2[150]; double xbins3[80]; double xbins4[100]; double xbins5[100];
    int var = 0; int var2 = 0; int var3 = 0; int var4 = 0; int var5 = 0;
    int maxpo = 70; int maxpo2 = 50; int maxpo3 = 20; int maxpo4 = 16; int maxpo5 = 21; 
    int othermax = maxpo - 1;  int othermax2 = maxpo2 - 1; int othermax3 = maxpo3 - 1; int othermax4 = maxpo4 - 1; int othermax5 = maxpo5 - 1;  
    for(int i=0; i<maxpo;  i++){  xbins[i]= var; var += 510/maxpo; }
    for(int i=0; i<maxpo2; i++){ xbins2[i]= var2; var2 += 150/maxpo2; }
    for(int i=0; i<maxpo3; i++){ xbins3[i]= var3; var3 += 82/maxpo3; }
    for(int i=0; i<maxpo4; i++){ xbins4[i]= var4; var4 += 35/maxpo4; }
    for(int i=0; i<maxpo5; i++){ xbins5[i]= var5; var5 += 1; }

    TH1D *h_mulfullNonnew = (TH1D*)h_mulfullNon->Rebin(othermax, "h_mulfullNonnew",xbins);
    TH1D *h_mulfinNonnew  = (TH1D*)h_mulfinNon->Rebin(othermax2, "h_mulfinNonnew",xbins2);
    TH1D *h_mulppkNonnew  = (TH1D*)h_mulppkNon->Rebin(othermax3, "h_mulppkNonnew",xbins3);
    TH1D *h_multpcNonnew  = (TH1D*)h_multpcNon->Rebin(othermax4, "h_multpcNonnew",xbins4);
    TH1D *h_mulpoiNonnew  = (TH1D*)h_mulpoiNon->Rebin(othermax5, "h_mulpoiNonnew",xbins5);

    TH1D *h_mulfullDnew = (TH1D*)h_mulfullD->Rebin(othermax, "h_mulfullDnew",xbins);
    TH1D *h_mulfinDnew  = (TH1D*)h_mulfinD->Rebin(othermax2, "h_mulfinDnew",xbins2);
    TH1D *h_mulppkDnew  = (TH1D*)h_mulppkD->Rebin(othermax3, "h_mulppkDnew",xbins3);
    TH1D *h_multpcDnew  = (TH1D*)h_multpcD->Rebin(othermax4, "h_multpcDnew",xbins4);
    TH1D *h_mulpoiDnew  = (TH1D*)h_mulpoiD->Rebin(othermax5, "h_mulpoiDnew",xbins5);

    //---- canvas -----------------------------------------------------------------
/*
    //---- C1 -------------------------------------------------------------------
    TCanvas *canvas1 = new TCanvas("canvas1", "canvas1", 1000, 1000);
    h_mulfullDnew->SetStats(0);
    h_mulfullDnew->SetLineColor(kRed);
    h_mulfullDnew->SetLineStyle(kSolid);
    h_mulfullDnew->SetMarkerStyle(20);
    h_mulfullDnew->SetMarkerColor(kBlack);
    h_mulfullDnew->Draw("pl");
    h_mulfullNonnew->SetLineColor(kBlue);
    h_mulfullNonnew->SetLineStyle(kSolid);
    h_mulfullNonnew->SetMarkerStyle(20);
    h_mulfullNonnew->SetMarkerColor(413);
    h_mulfullNonnew->Draw("pl,same");
    h_mulfullDnew->GetYaxis()->SetTitle("count");
    h_mulfullDnew->GetXaxis()->SetTitle("fullMult");
    gStyle->SetOptTitle(0);
    gStyle->SetOptTitle(0);
    TLatex *lat = new TLatex();
	lat->DrawLatexNDC(.3,.95,"Full Multiplicity");
    TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
    leg->AddEntry(h_mulfullDnew, "Diffractive", "pl");
    leg->AddEntry(h_mulfullNonnew, "NonDiffractive", "pl");
    leg->Draw();
    canvas1->Draw();
    
    //---- C2 -------------------------------------------------------------------
    TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 1000, 1000);
    h_mulfinDnew->SetStats(0);
    h_mulfinDnew->SetLineColor(kRed);
    h_mulfinDnew->SetLineStyle(kSolid);
    h_mulfinDnew->SetMarkerStyle(20);
    h_mulfinDnew->SetMarkerColor(kBlack);
    h_mulfinDnew->Draw("pl");
    h_mulfinNonnew->SetLineColor(kBlue);
    h_mulfinNonnew->SetLineStyle(kSolid);
    h_mulfinNonnew->SetMarkerStyle(20);
    h_mulfinNonnew->SetMarkerColor(413);
    h_mulfinNonnew->Draw("pl,same");
    h_mulfinDnew->GetYaxis()->SetTitle("count");
    h_mulfinDnew->GetXaxis()->SetTitle("finMult");
    gStyle->SetOptTitle(0);
    gStyle->SetOptTitle(0);
    TLatex *lat2 = new TLatex();
	lat2->DrawLatexNDC(.3,.95,"Final state Multiplicity");
    TLegend *leg2 = new TLegend(0.7, 0.7, 0.9, 0.9);
    leg2->AddEntry(h_mulfullDnew, "Diffractive", "pl");
    leg2->AddEntry(h_mulfullNonnew, "NonDiffractive", "pl");
    leg2->Draw();
    canvas2->Draw();
    
    //---- C3 -------------------------------------------------------------------
    TCanvas *canvas3 = new TCanvas("canvas3", "canvas3", 1000, 1000);
    h_mulppkDnew->SetStats(0);
    h_mulppkDnew->SetLineColor(kRed);
    h_mulppkDnew->SetLineStyle(kSolid);
    h_mulppkDnew->SetMarkerStyle(20);
    h_mulppkDnew->SetMarkerColor(kBlack);
    h_mulppkDnew->Draw("pl");
    h_mulppkNonnew->SetLineColor(kBlue);
    h_mulppkNonnew->SetLineStyle(kSolid);
    h_mulppkNonnew->SetMarkerStyle(20);
    h_mulppkNonnew->SetMarkerColor(413);
    h_mulppkNonnew->Draw("pl,same");
    h_mulppkDnew->GetYaxis()->SetTitle("count");
    h_mulppkDnew->GetXaxis()->SetTitle("ppkMult");
    gStyle->SetOptTitle(0);
    gStyle->SetOptTitle(0);
    TLatex *lat3 = new TLatex();
	lat3->DrawLatexNDC(.3,.95,"ppk Multiplicity");
    TLegend *leg3 = new TLegend(0.7, 0.7, 0.9, 0.9);
    leg3->AddEntry(h_mulfullDnew, "Diffractive", "pl");
    leg3->AddEntry(h_mulfullNonnew, "NonDiffractive", "pl");
    leg3->Draw();
    canvas3->Draw();
*/
    //---- C4 -------------------------------------------------------------------
    TCanvas *canvas4 = new TCanvas("canvas4", "canvas4", 1000, 1000);
    /*
    h_multpcDnew->SetStats(0);
    h_multpcDnew->SetLineColor(kRed);
    h_multpcDnew->SetLineStyle(kSolid);
    h_multpcDnew->SetMarkerStyle(20);
    h_multpcDnew->SetMarkerColor(kBlack);
    h_multpcDnew->Draw("pl");
    */
    h_multpcDnew->SetStats(0);
    h_multpcDnew->SetLineColor(kBlue);
    h_multpcDnew->SetLineStyle(kSolid);
    h_multpcDnew->SetMarkerStyle(20);
    h_multpcDnew->SetMarkerColor(413);
    h_multpcDnew->Draw("pl");
    //h_multpcNon->Draw("pl, same");
    h_multpcDnew->GetYaxis()->SetTitle("count");
    h_multpcDnew->GetXaxis()->SetTitle("tpcMult");
    gStyle->SetOptTitle(0);
    gStyle->SetOptTitle(0);
    TLatex *lat4 = new TLatex();
	lat4->DrawLatexNDC(.3,.95,"");
    //TLegend *leg4 = new TLegend(0.7, 0.7, 0.9, 0.9);
    //leg4->AddEntry(h_mulfullDnew, "Diffractive", "pl");
    //leg4->AddEntry(h_mulfullNonnew, "NonDiffractive", "pl");
    //leg4->Draw();
    canvas4->Draw();

    //---- C5 -------------------------------------------------------------------
    TCanvas *canvas5 = new TCanvas("canvas5", "canvas5", 1000, 1000);
    
    /* TGaxis *axis1 = new TGaxis(0,0,20,300000, ); */
    /* axis1->SetName("axis1"); */
    /* axis1->Draw(); */
    h_mulpoiDnew->SetStats(0);
    h_mulpoiDnew->SetLineColor(kRed);
    h_mulpoiDnew->SetLineStyle(kSolid);
    h_mulpoiDnew->SetMarkerStyle(20);
    h_mulpoiDnew->SetMarkerColor(kBlack);
    h_mulpoiDnew->Draw("pl");
    h_mulpoiNonnew->SetLineColor(kBlue);
    h_mulpoiNonnew->SetLineStyle(kSolid);
    h_mulpoiNonnew->SetMarkerStyle(20);
    h_mulpoiNonnew->SetMarkerColor(413);
    h_mulpoiNonnew->Draw("pl,same"); //pl same
    h_mulpoiDnew->GetYaxis()->SetTitle("count");
    h_mulpoiDnew->GetXaxis()->SetTitle("poiMult");
    gStyle->SetOptTitle(0);
    gStyle->SetOptTitle(0);
    TLatex *lat5 = new TLatex();
//	lat5->DrawLatexNDC(.3,.95,"poi Multiplicity");
    TLegend *leg5 = new TLegend(0.7, 0.7, 0.9, 0.9);
    leg5->AddEntry(h_mulpoiDnew, "Diffractive", "pl");
    leg5->AddEntry(h_mulpoiNonnew, "NonDiffractive", "pl");
    leg5->Draw();
    canvas5->Draw();



} 
