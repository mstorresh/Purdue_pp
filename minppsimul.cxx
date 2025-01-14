#include "Pythia8/Pythia.h"
// c++ library
#include <cmath>
#include <array>
#include <vector>
#include <algorithm> 
// ROOT, for histogramming.
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
// ROOT, for saving file.
#include "TFile.h"
#include "TProfile.h"
#include "TVector3.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TMultiGraph.h"

//int possT(int len1, int bins1, int mul);
//float averX(int arr1[], float arr2[], int l1,int l2, int binsi);

int main(){
  //----- input for the seed -----------
  //char* filename= argv[1];
  int seed = 1;
  int iJob = 0;
  int iSim = 0;

  //------- Histogram --------------------------------------------------------------------
  TH1D *h_mulfull = new TH1D("h_mulfull","h_mulfull", 500,0,500);
  TH1D *h_mulfin  = new TH1D("h_mulfin","h_mulfin", 100, 0, 150);
  TH1D *h_mulppk  = new TH1D("h_mulppk","h_mulppk", 100, 0, 80);
  TH1D *h_multpc  = new TH1D("h_multpc", "h_multpc", 100, 0, 40);
  TH1D *h_mulpoi  = new TH1D("h_mulpoi", "h_mulpoi", 100, 0, 20);

  TH1D *h_mulSS  = new TH1D("h_mulSS", "h_mulSS", 100, 0, 20);
  TH1D *h_mulOS  = new TH1D("h_mulOS", "h_mulOS", 100, 0, 20);
  TH1D *h_eta1    = new TH1D("h_eta1", "h_eta1", 200, -10, 10);
  TH1D *h_eta2    = new TH1D("h_eta2", "h_eta2", 200, -2.2, 2.2);
  TH1D *h_eta3    = new TH1D("h_eta3", "h_eta3", 200, -2.2, 2.2);
  TH1D *h_deleta  = new TH1D("h_deleta", "h_deleta", 200, -2.5, 2.5);
  TH1D *h_pid     = new TH1D("h_pid_POI", "h_pid_POI", 100, -2220, 2220);
  TH1D *h_mot1    = new TH1D("h_mot1", "h_mot1", 200, -22200, 22200);
  TH1D *h_mot2    = new TH1D("h_mot2", "h_mot2", 200, -22200, 22200);
  TH1D *id_mot    = new TH1D("id_mot", "id_mot", 200, -21000, 21000);
  //TH1D *h_dellar  = new TH1D("h_dellar", "h_dellar", 200, -2.1, 2.1);
 // TH1D *h_delsma  = new TH1D("h_delsma", "h_delsma", 200, -2.1, 2.1);
  
  
  TH2D *h2_totetaphi = new TH2D("h2_totetaphi", "h2_totetaphi", 40, -2, 2, 100, -M_PI, M_PI); // 64 is not enough *400*   
  
  TH2D *h2_ss = new TH2D("h2_ss", "h2_ss", 40, -2, 2, 100, -M_PI, M_PI); // 64 is not enough *400*   
  TH2D *h2_os = new TH2D("h2_os", "h2_os", 40, -2, 2, 100, -M_PI, M_PI); // 64 is not enough *400*   
   
  TH2D *h2_poifull = new TH2D("h2_poifull", "h2_poifull", 40, -2, 2, 100, -M_PI, M_PI); // 64 is not enough *400*   
   
  
  //------------ NBin 1 CUT -------------------------------------------------------------------------------------------
  TH2D *h2_etaphiSS1 = new TH2D("h2_etaphiSS1", "h2_etaphiSS1", 40, -2, 2, 100, -M_PI, M_PI); // 64 is not enough *400*   
  TH2D *h2_etaphiOS1 = new TH2D("h2_etaphiOS1", "h2_etaphiOS1", 40, -2, 2, 100, -M_PI, M_PI);

  //----------- NBin 2 CUT --------------------------------------------------------------------------------------------- 
  TH2D *h2_etaphiSS2 = new TH2D("h2_etaphiSS2", "h2_etaphiOS2", 40, -2, 2, 100, -M_PI, M_PI); // 64 is not enough *400*   
  TH2D *h2_etaphiOS2 = new TH2D("h2_etaphiOS2", "h2_etaphiSS2", 40, -2, 2, 100, -M_PI, M_PI);

  //----------- NBin 3 CUT ---------------------------------------------------------------------------------------------
  TH2D *h2_etaphiSS3 = new TH2D("h2_etaphiSS3", "h2_etaphiSS3", 40, -2, 2, 100, -M_PI, M_PI); // 64 is not enough *400*   
  TH2D *h2_etaphiOS3 = new TH2D("h2_etaphiOS3", "h2_etaphiOS3", 40, -2, 2, 100, -M_PI, M_PI);

  //----------- NBin 4 CUT ---------------------------------------------------------------------------------------------
  TH2D *h2_etaphiSS4 = new TH2D("h2_etaphiSS4", "h2_etaphiSS4", 40, -2, 2, 100, -M_PI, M_PI); // 64 is not enough *400*   
  TH2D *h2_etaphiOS4 = new TH2D("h2_etaphiOS4", "h2_etaphiOS4", 40, -2, 2, 100, -M_PI, M_PI);

  //----------- NBin 3 CUT ---------------------------------------------------------------------------------------------
  TH2D *h2_etaphiSS5 = new TH2D("h2_etaphiSS5", "h2_etaphiSS5", 40, -2, 2, 100, -M_PI, M_PI); // 64 is not enough *400*   
  TH2D *h2_etaphiOS5 = new TH2D("h2_etaphiOS5", "h2_etaphiOS5", 40, -2, 2, 100, -M_PI, M_PI);




  //for the large and small delta eta SS ----------------------------------------------------------------------------------
  TH2D *h2_dellar1 = new TH2D("h2_dellar1", "h2_dellar1", 40, -2, 2, 100, -M_PI, M_PI); // 64 is not enough *400*   
  TH2D *h2_delsma1 = new TH2D("h2_delsma1", "h2_delsma1", 40, -2, 2, 100, -M_PI, M_PI);

  TH2D *h2_dellar2 = new TH2D("h2_dellar2", "h2_dellar2", 40, -2, 2, 100, -M_PI, M_PI); // 64 is not enough *400*   
  TH2D *h2_delsma2 = new TH2D("h2_delsma2", "h2_delsma2", 40, -2, 2, 100, -M_PI, M_PI);

  TH2D *h2_dellar3 = new TH2D("h2_dellar3", "h2_dellar3", 40, -2, 2, 100, -M_PI, M_PI); // 64 is not enough *400*   
  TH2D *h2_delsma3 = new TH2D("h2_delsma3", "h2_delsma3", 40, -2, 2, 100, -M_PI, M_PI);

  TH2D *h2_dellar4 = new TH2D("h2_dellar4", "h2_dellar4", 40, -2, 2, 100, -M_PI, M_PI); // 64 is not enough *400*   
  TH2D *h2_delsma4 = new TH2D("h2_delsma4", "h2_delsma4", 40, -2, 2, 100, -M_PI, M_PI);

  TH2D *h2_dellar5 = new TH2D("h2_dellar5", "h2_dellar5", 40, -2, 2, 100, -M_PI, M_PI); // 64 is not enough *400*   
  TH2D *h2_delsma5 = new TH2D("h2_delsma5", "h2_delsma5", 40, -2, 2, 100, -M_PI, M_PI);



  //-- pythia string simulation ------------------------------------------------------------
  Pythia8::Pythia *pythiaG = new Pythia8::Pythia();
  pythiaG->readString("Beams:eCM = 200.");
  //pythiaG->readString("SoftQCD:minBias = on");
  //pythiaG->readString("SoftQCD:all = on");
  /* pythiaG->readString("SoftQCD:nonDiffractive = on"); */
  //pythiaG->readString("SoftQCD:elastic = on");
  pythiaG->readString("SoftQCD:singleDiffractive = on");
  pythiaG->readString("SoftQCD:doubleDiffractive = on");
  pythiaG->readString("SoftQCD:centralDiffractive = on");
  //pythiaG->readString("SoftQCD:inelastic = on");
  //pythiaG->readString("HardQCD:all= off");
  pythiaG->readString("Tune:pp 14");
  pythiaG->readString("Random:setSeed = on");
  /* ParticleDecays:limitTau0 = on; */
  /* pythiaG->readString("ParticleDecays:limitTau0 = on"); */
  /* pythiaG->readString("ParticleDecays:tau0Max = 10.0"); */
  /* pythiaG->readString("3122:mayDecay = off"); */
  

  char seedstr[256];
  sprintf(seedstr, "Random:seed = %d", seed);
  pythiaG->readString(seedstr);

  pythiaG->init();

  //------- variables to fill & constants ----------------

  const int nMaxTracks = 2000;
  float s_pt[nMaxTracks];
  float s_eta[nMaxTracks];
  float s_phi[nMaxTracks];
  float s_e[nMaxTracks];
  float s_m[nMaxTracks];
  float s_x[nMaxTracks];
  float s_y[nMaxTracks];
  float s_z[nMaxTracks];
  float s_t[nMaxTracks];
  float s_px[nMaxTracks];
  float s_py[nMaxTracks];
  float s_pz[nMaxTracks];
  int s_id[nMaxTracks];
  int tpc_id[nMaxTracks];
  int s_status[nMaxTracks];
  float final_phi[nMaxTracks];
  float ppk_phi[nMaxTracks];
  float tpc_phi[nMaxTracks];
  float poi_phi[nMaxTracks];
  float fin_eta[nMaxTracks];
  float ppk_eta[nMaxTracks];
  float tpc_eta[nMaxTracks];
  float poi_eta[nMaxTracks];
  int poi_id[nMaxTracks];
  float acum[nMaxTracks];
  float extra_p[nMaxTracks];
  float multinumbers[nMaxTracks];
  int nevt = 300000000;  //1000000
  int multifinnum[nevt];
  int multippknum[nevt];
  int multitpcnum[nevt];
  int multipoinum[nevt];
  int mot1_id[nMaxTracks];
  int mot2_id[nMaxTracks];
  std::vector<int> mothep;
  int mcou1; int mcou2; int mcou;
  int mothe1; int mothe2;
  int mothe1_id; int mothe2_id;
  double CSS1 = 0; double CSS2 = 0; double CSS3 = 0; double CSS4 = 0; double CSS5 = 0;
  double COS1 = 0; double COS2 = 0; double COS3 = 0; double COS4 = 0; double COS5 = 0;
  //---------- loop  --------------- 
  for(int iEvent=0; iEvent<nevt; iEvent++){ 
    if(!pythiaG->next()) continue; int num = pythiaG->event.size(); int multifull = 0; int multifin  = 0;
    int multippk  = 0;
    int multitpc  = 0;
    int multipoi  = 0;
    
    for(int i=0; i<num; i++){
        //---- Full multiplicity no cuts --------------------
        multifull++;
        s_status [i] = pythiaG->event[i].status();
        //s_phi    [i] = pythiaG->event[i].phi();
        s_id     [i] = pythiaG->event[i].id();
        s_pt     [i] = pythiaG->event[i].pT();
        s_px     [i] = pythiaG->event[i].px();
        s_py     [i] = pythiaG->event[i].py();
        s_pz     [i] = pythiaG->event[i].pz();
        if(s_pt[i] == 0){
            s_phi[i] = 0;
            s_eta[i] = s_pz[i]>0?1e10:-1e10;
        } else{
            s_phi[i] = pythiaG->event[i].phi();
            s_eta[i] = pythiaG->event[i].eta();
        }
        h_eta1->Fill(pythiaG->event[i].eta());
        
                //-----------  the condition of final, ppk, tpc & poi ----------------------------------------------------------
        //if(s_status[i]>0){
        if(pythiaG->event[i].isFinal()){    // final condition
            final_phi[multifin] = pythiaG->event[i].phi();
            fin_eta[multifin]   = pythiaG->event[i].eta();
            multifin++;
            if(abs(s_id[i])==2212 || abs(s_id[i])==211 || abs(s_id[i])==321){ // ppk condition
                ppk_phi[multippk] = pythiaG->event[i].phi();
                ppk_eta[multippk] = pythiaG->event[i].eta();
                multippk++;
            }
            if(abs(pythiaG->event[i].eta())<1.0 && pythiaG->event[i].pT()>0.2 && pythiaG->event[i].pT()<2.0){ //tpc condition
                tpc_phi[multitpc] = pythiaG->event[i].phi();
                tpc_eta[multitpc] = pythiaG->event[i].eta();
                tpc_id[multitpc]  = pythiaG->event[i].id();
                multitpc++;
                h_eta2->Fill(pythiaG->event[i].eta());
                if(abs(s_id[i])==2212 || abs(s_id[i])==211 || abs(s_id[i])==321){ //poi condition
                  mothe1 = pythiaG->event[i].mother1();
                  mothe2 = pythiaG->event[i].mother2();
                  if(abs(s_id[i])==211 || abs(s_id[i])==321){
                    mothe1_id = pythiaG->event[mothe1].id();
                    mothe2_id = pythiaG->event[mothe2].id();
                    if(abs(mothe1_id)==3334 || abs(mothe2_id)==3334 || abs(mothe1_id)==3312 || abs(mothe2_id)==3312 ||
                       abs(mothe1_id)==3222 || abs(mothe2_id)==3222 || abs(mothe1_id)==3122 || abs(mothe2_id)==3122 ||
                       abs(mothe1_id)==3112 || abs(mothe2_id)==3112 || abs(mothe1_id)==310  || abs(mothe2_id)==310){
                       int a = 1;
                      }
                    else{
                      poi_phi[multipoi] = pythiaG->event[i].phi();
                      poi_eta[multipoi] = pythiaG->event[i].eta();
                      multipoi++;
                    }
                        
                  }
                  else{
                      poi_phi[multipoi] = pythiaG->event[i].phi();
                      poi_eta[multipoi] = pythiaG->event[i].eta();
                      multipoi++;	
                  }
                  
                  
                }
            }
        }

    }

      
     for(int ki=0; ki<multipoi; ki++){
        h_eta3->Fill(poi_eta[ki]);
        /* h_pid->Fill(tpc_id[ki]); */
        //std::cout<<tpc_id[ki]<<'\n';
    }

    /* for(int kj=0; kj<multipoi; kj++){ */
    /*     h_pid->Fill(poi_id[kj]); */
    /*     /1* h_mot1->Fill(mot1_id[kj]); *1/ */
    /*     /1* h_mot2->Fill(mot2_id[kj]); *1/ */
    /*     /1* std::cout<<mot1_id[kj]<<'\n'; *1/ */
    /*     /1* std::cout<<mot2_id[kj]<<'\n'; *1/ */
    /*     mcou1 = mot1_id[kj]; */
    /*     mcou2 = mot2_id[kj]; */
    /*     if(mcou1!=0 && mcou1<num){ */
    /*       int mcou1id = pythiaG->event[mcou1].id(); */
    /*       /1* std::cout<<mcou1id<<'\n'; *1/ */
    /*       h_mot1->Fill(mcou1id); */
    /*     } */
    /*     if(mcou2!=0 && mcou2<num){ */
    /*       int mcou2id = pythiaG->event[mcou2].id(); */
    /*       /1* std::cout<<mcou2id<<'\n'; *1/ */
    /*       h_mot2->Fill(mcou2id); */
    /*     } */

    /* } */


/*     int lengv = mothep.size(); */
/*     /1* std::cout<<"---------- "<<lengv<<'\n'; *1/ */
/*     for(int kk=0;kk<lengv; kk++){ */
/*       mcou = mothep[kk]; */
/*       std::cout<<mcou<<" -------- "<<num<<'\n'; */
/*       if(mcou!=0 && mcou<num){ */ 
/*       int mcouid = pythiaG->event[mcou].id(); */  
/*       /1* std::cout<<mcouid<<'\n'; *1/ */
/*       id_mot->Fill(mcouid); */
/*       /1* std::cout<<pythiaG->event[mcou].name(); *1/ */
/*       } */
/*     } */
    
    /* std::cout<<"**************************************************"<<'\n'; */

    //---- filling multiplicity histograms ---------------------------------------------------------------------------
    h_mulfull->Fill(multifull);
    h_mulfin ->Fill(multifin);
    h_mulppk ->Fill(multippk);
    h_multpc ->Fill(multitpc);
    h_mulpoi ->Fill(multipoi);

    //---------- randomize an array ------------------------------------------------------------------------------------
    float del2eta = 0;
    int idx[multipoi];
    for(int i=0; i <multipoi; i++){idx[i] = i;}
    //std::random_shuffle(&idx[0], &idx[multipoi]);
    
    for(int j=0; j<multipoi; j++){
        for(int k=j+1; k<multipoi; k++){
            del2eta = poi_eta[idx[j]] - poi_eta[idx[k]];
            h_deleta->Fill(del2eta);
        }
    }

   //--- filling the TH2 ----------------------------------------------------------------------------------------------
    float del1eta = 0;
    float del1phi = 0;
    double CSS0 = 0;
    double COS0 = 0;
    
    for(int j=0; j<multipoi; j++){
            for(int k=j+1; k<multipoi; k++){
                del1eta = poi_eta[idx[j]] - poi_eta[idx[k]];
                del1phi = poi_phi[idx[j]] - poi_phi[idx[k]];
                if(del1phi<-M_PI){ del1phi = del1phi + 2*M_PI; }
                if(del1phi>M_PI){  del1phi = del1phi - 2*M_PI; }
                h2_poifull->Fill(del1eta, del1phi);
                if((tpc_id[j]>=0 && tpc_id[k]>=0) || (tpc_id[j]<0 && tpc_id[k]<0)){
                    h2_ss->Fill(del1eta, del1phi);
                    CSS0++;
                }
                else{
                    h2_os->Fill(del1eta, del1phi);
                    COS0++;
                }
			}
    }

    /* std::cout<<multipoi<<".... "<<CSS1<<"------- "<<COS1<<'\n'; */
    h_mulSS->Fill(CSS0);
    h_mulOS->Fill(COS0);
    
    if(multipoi<=3){
        for(int j=0; j<multipoi; j++){
            for(int k=j+1; k<multipoi; k++){
                del1eta = poi_eta[idx[j]] - poi_eta[idx[k]];
                del1phi = poi_phi[idx[j]] - poi_phi[idx[k]];
                if(del1phi<-M_PI){ del1phi = del1phi + 2*M_PI; }
                if(del1phi>M_PI){  del1phi = del1phi - 2*M_PI; }
                if((tpc_id[j]>=0 && tpc_id[k]>=0) || (tpc_id[j]<0 && tpc_id[k]<0)){
                    h2_etaphiSS1->Fill(del1eta, del1phi);
                    CSS1++;
                    if(abs(del1eta)>1.5){ h2_dellar1->Fill(del1eta, del1phi);}
                    if(abs(del1eta)<0.5){ h2_delsma1->Fill(del1eta, del1phi);}
                }
                else{
                    h2_etaphiOS1->Fill(del1eta, del1phi);
                    COS1++;
                }
            }
        }
    }

    if(multipoi>=4 && multipoi<=6){
        for(int j=0; j<multipoi; j++){
            for(int k=j+1; k<multipoi; k++){
                del1eta = poi_eta[idx[j]] - poi_eta[idx[k]];
                del1phi = poi_phi[idx[j]] - poi_phi[idx[k]];
                if(del1phi<-M_PI){ del1phi = del1phi + 2*M_PI; }
                if(del1phi>M_PI){  del1phi = del1phi - 2*M_PI; }
                if((tpc_id[j]>=0 && tpc_id[k]>=0) || (tpc_id[j]<0 && tpc_id[k]<0)){
                    h2_etaphiSS2->Fill(del1eta, del1phi);
                    CSS2++;
                    if(abs(del1eta)>1.5){ h2_dellar2->Fill(del1eta, del1phi);}
                    if(abs(del1eta)<0.5){ h2_delsma2->Fill(del1eta, del1phi);}
                }
                else{
                    h2_etaphiOS2->Fill(del1eta, del1phi);
                    COS2++;
                }
            }
        }
    }

    if(multipoi>=7 && multipoi<=10){
        for(int j=0; j<multipoi; j++){
            for(int k=j+1; k<multipoi; k++){
                del1eta = poi_eta[idx[j]] - poi_eta[idx[k]];
                del1phi = poi_phi[idx[j]] - poi_phi[idx[k]];
                if(del1phi<-M_PI){ del1phi = del1phi + 2*M_PI; }
                if(del1phi>M_PI){  del1phi = del1phi - 2*M_PI; }
                if((tpc_id[j]>=0 && tpc_id[k]>=0) || (tpc_id[j]<0 && tpc_id[k]<0)){
                    h2_etaphiSS3->Fill(del1eta, del1phi);
                    CSS3++;
                    if(abs(del1eta)>1.5){ h2_dellar3->Fill(del1eta, del1phi);}
                    if(abs(del1eta)<0.5){ h2_delsma3->Fill(del1eta, del1phi);}
                }
                else{
                    h2_etaphiOS3->Fill(del1eta, del1phi);
                    COS3++;
                }
            }
        }
    }

    if(multipoi>=11 && multipoi<=14){
        for(int j=0; j<multipoi; j++){
            for(int k=j+1; k<multipoi; k++){
                del1eta = poi_eta[idx[j]] - poi_eta[idx[k]];
                del1phi = poi_phi[idx[j]] - poi_phi[idx[k]];
                if(del1phi<-M_PI){ del1phi = del1phi + 2*M_PI; }
                if(del1phi>M_PI){  del1phi = del1phi - 2*M_PI; }
                if((tpc_id[j]>=0 && tpc_id[k]>=0) || (tpc_id[j]<0 && tpc_id[k]<0)){
                    h2_etaphiSS4->Fill(del1eta, del1phi);
                    CSS4++;
                    if(abs(del1eta)>1.5){ h2_dellar4->Fill(del1eta, del1phi);}
                    if(abs(del1eta)<0.5){ h2_delsma4->Fill(del1eta, del1phi);}
                }
                else{
                    h2_etaphiOS4->Fill(del1eta, del1phi);
                    COS4++;
                }
            }
        }
    }

    if(multipoi>14){
        for(int j=0; j<multipoi; j++){
            for(int k=j+1; k<multipoi; k++){
                del1eta = poi_eta[idx[j]] - poi_eta[idx[k]];
                del1phi = poi_phi[idx[j]] - poi_phi[idx[k]];
                if(del1phi<-M_PI){ del1phi = del1phi + 2*M_PI; }
                if(del1phi>M_PI){  del1phi = del1phi - 2*M_PI; }
                if((tpc_id[j]>=0 && tpc_id[k]>=0) || (tpc_id[j]<0 && tpc_id[k]<0)){
                    h2_etaphiSS5->Fill(del1eta, del1phi);
                    CSS5++;
                    if(abs(del1eta)>1.5){ h2_dellar5->Fill(del1eta, del1phi);}
                    if(abs(del1eta)<0.5){ h2_delsma5->Fill(del1eta, del1phi);}
                }
                else{
                    h2_etaphiOS5->Fill(del1eta, del1phi);
                    COS5++;
                }
            }
        }
    }




}

std::cout<<"events: "<<'\n';
std::cout<<"1: "<<CSS1<<" ; "<<COS1<<'\n';
std::cout<<"2: "<<CSS2<<" ; "<<COS2<<'\n';
std::cout<<"3: "<<CSS3<<" ; "<<COS3<<'\n';
std::cout<<"4: "<<CSS4<<" ; "<<COS4<<'\n';
std::cout<<"5: "<<CSS5<<" ; "<<COS5<<'\n';
//---- rootfile ---------------------------------------------------------------------------
  TFile* outFile = new TFile("eventsDif.root", "RECREATE");
  h_mulfull->Write();
  h_mulfin->Write();
  h_mulppk->Write();
  h_multpc->Write();
  h_mulpoi->Write();
  h_mulSS->Write();
  h_mulOS->Write();

  h_eta1->Write();
  h_eta2->Write();
  h_eta3->Write();
  h_deleta->Write();
  h_pid->Write();
  h_mot1->Write();
  h_mot2->Write();

  h2_etaphiSS1->Write();
  h2_etaphiOS1->Write();
  h2_etaphiSS2->Write();
  h2_etaphiOS2->Write();
  h2_etaphiSS3->Write();
  h2_etaphiOS3->Write();
  h2_etaphiSS4->Write();
  h2_etaphiOS4->Write();
  h2_etaphiSS5->Write();
  h2_etaphiOS5->Write();

  h2_dellar1->Write();
  h2_delsma1->Write();
  h2_dellar2->Write();
  h2_delsma2->Write();
  h2_dellar3->Write();
  h2_delsma3->Write();
  h2_dellar4->Write();
  h2_delsma4->Write();
  h2_dellar5->Write();
  h2_delsma5->Write();

  h2_poifull->Write();

  h2_ss->Write();
  h2_os->Write();

  outFile->Write();
  outFile->Close();

}

