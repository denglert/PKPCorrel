#include "SetupCustomTrackTree.h"

void setupTrackTree(TTree *t,Tracks &tTracks,bool doCheck = 1)
{
   // Set branch addresses and branch pointers
//   t->SetBranchAddress("nEv", &tTracks.nEv, &tTracks.b_nEv);
//   t->SetBranchAddress("nLumi", &tTracks.nLumi, &tTracks.b_nLumi);
//   t->SetBranchAddress("nBX", &tTracks.nBX, &tTracks.b_nBX);
//   t->SetBranchAddress("nRun", &tTracks.nRun, &tTracks.b_nRun);
   t->SetBranchAddress("nv", &tTracks.nv, &tTracks.b_nv);
//   t->SetBranchAddress("vx", tTracks.vx, &tTracks.b_vx);
//   t->SetBranchAddress("vy", tTracks.vy, &tTracks.b_vy);
//   t->SetBranchAddress("vz", tTracks.vz, &tTracks.b_vz);
//   t->SetBranchAddress("vxErr", tTracks.vxErr, &tTracks.b_vxErr);
//   t->SetBranchAddress("vyErr", tTracks.vyErr, &tTracks.b_vyErr);
//   t->SetBranchAddress("vzErr", tTracks.vzErr, &tTracks.b_vzErr);
////	t->SetBranchAddress("nDaugher", tTracks.nDaugher, &tTracks.b_nDaugher);
//   t->SetBranchAddress("nVtx", &tTracks.nVtx, &tTracks.b_nVtx);
//   t->SetBranchAddress("maxVtx", &tTracks.maxVtx, &tTracks.b_maxVtx);
//   t->SetBranchAddress("nTrkVtx", tTracks.nTrkVtx, &tTracks.b_nTrkVtx);
//   t->SetBranchAddress("xVtx", tTracks.xVtx, &tTracks.b_xVtx);
//   t->SetBranchAddress("yVtx", tTracks.yVtx, &tTracks.b_yVtx);
//   t->SetBranchAddress("zVtx", tTracks.zVtx, &tTracks.b_zVtx);
//   t->SetBranchAddress("xVtxErr", tTracks.xVtxErr, &tTracks.b_xVtxErr);
//   t->SetBranchAddress("yVtxErr", tTracks.yVtxErr, &tTracks.b_yVtxErr);
//   t->SetBranchAddress("zVtxErr", tTracks.zVtxErr, &tTracks.b_zVtxErr);
   t->SetBranchAddress("nTrk", &tTracks.nTrk, &tTracks.b_nTrk);
   t->SetBranchAddress("dedx", &tTracks.dedx, &tTracks.b_dedx);
   t->SetBranchAddress("trkPt", tTracks.trkPt, &tTracks.b_trkPt);
   t->SetBranchAddress("trkPtError", tTracks.trkPtError, &tTracks.b_trkPtError);
//   t->SetBranchAddress("trkNHit", tTracks.trkNHit, &tTracks.b_trkNHit);
//   t->SetBranchAddress("trkNlayer", tTracks.trkNlayer, &tTracks.b_trkNlayer);
   t->SetBranchAddress("trkEta", tTracks.trkEta, &tTracks.b_trkEta);
   t->SetBranchAddress("trkPhi", tTracks.trkPhi, &tTracks.b_trkPhi);
   t->SetBranchAddress("trkCharge", tTracks.trkCharge, &tTracks.b_trkCharge);
   t->SetBranchAddress("highPurity", tTracks.highPurity, &tTracks.b_highPurity);
// t->SetBranchAddress("trkChi2", tTracks.trkChi2, &tTracks.b_trkChi2);
// t->SetBranchAddress("trkNdof", tTracks.trkNdof, &tTracks.b_trkNdof);
   t->SetBranchAddress("trkDxy1", tTracks.trkDxy1, &tTracks.b_trkDxy1);
   t->SetBranchAddress("trkDxyError1", tTracks.trkDxyError1, &tTracks.b_trkDxyError1);
   t->SetBranchAddress("trkDz1", tTracks.trkDz1, &tTracks.b_trkDz1);
   t->SetBranchAddress("trkDzError1", tTracks.trkDzError1, &tTracks.b_trkDzError1);
//   t->SetBranchAddress("trkFake", tTracks.trkFake, &tTracks.b_trkFake);
//   t->SetBranchAddress("trkAlgo", tTracks.trkAlgo, &tTracks.b_trkAlgo);
   if (doCheck) {
      if (t->GetMaximum("nv")>4) cout <<"FATAL ERROR: Arrary size of nv too small!!!  "<<t->GetMaximum("nv")<<endl;
      if (t->GetMaximum("nVtx") > MAXVTX) cout <<"FATAL ERROR: Arrary size of nVtx too small!!!  "<<t->GetMaximum("nVtx")<<endl;
      if (t->GetMaximum("nTrk")>maxTracks) cout <<"FATAL ERROR: Arrary size of nTrk too small!!!  "<<t->GetMaximum("nTrk")<<endl;
   }
}
