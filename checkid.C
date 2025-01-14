#include <string>
#include "TH1D.h"
#include "TFile.h"
#include "TF2.h"
#include "TMath.h"

void checkid(){

    //--------------------------------
    TFile *file1 = TFile::Open("totdif.root");
    TH2D *h2_sin = (TH2D*)file1->Get("h_pid_TPC");

    for(int i=1; i<1001; i++){
        int a = h2_sin->GetBinContent(i);

        if(a!=0){
            std::cout<<a<<'\n';
        }
           

    }


}
