#include "SetupCustomTrackTree.h"

void setupTrackTree(TTree *t, Tracks &tTracks )
{

   t->SetBranchAddress("nTrk", &tTracks.nTrk, &tTracks.b_nTrk);
   t->SetBranchAddress("dedx", &tTracks.dedx, &tTracks.b_dedx);
   t->SetBranchAddress("trkPt", tTracks.trkPt, &tTracks.b_trkPt);
   t->SetBranchAddress("trkPtError", tTracks.trkPtError, &tTracks.b_trkPtError);
   t->SetBranchAddress("trkEta", tTracks.trkEta, &tTracks.b_trkEta);
   t->SetBranchAddress("trkPhi", tTracks.trkPhi, &tTracks.b_trkPhi);
   t->SetBranchAddress("trkCharge", tTracks.trkCharge, &tTracks.b_trkCharge);
   t->SetBranchAddress("highPurity", tTracks.highPurity, &tTracks.b_highPurity);
   t->SetBranchAddress("trkDxy1", tTracks.trkDxy1, &tTracks.b_trkDxy1);
   t->SetBranchAddress("trkDxyError1", tTracks.trkDxyError1, &tTracks.b_trkDxyError1);
   t->SetBranchAddress("trkDz1", tTracks.trkDz1, &tTracks.b_trkDz1);
   t->SetBranchAddress("trkDzError1", tTracks.trkDzError1, &tTracks.b_trkDzError1);

}

void setupTrackTree_c(TTree *t, Tracks_c &tTracks, bool doMC)
{

// Set branch addresses and branch pointers
//   t->SetBranchAddress("nEv", &tTracks.nEv, &tTracks.b_nEv);
//   t->SetBranchAddress("nLumi", &tTracks.nLumi, &tTracks.b_nLumi);
//   t->SetBranchAddress("nBX", &tTracks.nBX, &tTracks.b_nBX);
//   t->SetBranchAddress("nRun", &tTracks.nRun, &tTracks.b_nRun);
//   t->SetBranchAddress("nv", &tTracks.nv, &tTracks.b_nv);
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
//

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

	if (doMC)
	{
   t->SetBranchAddress("trkStatus", tTracks.trkStatus, &tTracks.b_trkStatus);
   t->SetBranchAddress("nParticle", &tTracks.nParticle, &tTracks.b_nParticle);
   t->SetBranchAddress("trkFake", tTracks.trkFake, &tTracks.b_trkFake);
   t->SetBranchAddress("pStatus", tTracks.pStatus, &tTracks.b_pStatus);
   t->SetBranchAddress("pPId", tTracks.pPId, &tTracks.b_pPId);
   t->SetBranchAddress("pEta", tTracks.pEta, &tTracks.b_pEta);
   t->SetBranchAddress("pPhi", tTracks.pPhi, &tTracks.b_pPhi);
   t->SetBranchAddress("pPt", tTracks.pPt, &tTracks.b_pPt);
   t->SetBranchAddress("pNRec", tTracks.pNRec, &tTracks.b_pNRec);
   t->SetBranchAddress("mtrkdedx", tTracks.mtrkdedx, &tTracks.b_mtrkdedx);
   t->SetBranchAddress("mtrkPt", tTracks.mtrkPt, &tTracks.b_mtrkPt);
   t->SetBranchAddress("mtrkPtError", tTracks.mtrkPtError, &tTracks.b_mtrkPtError);
   t->SetBranchAddress("mtrkNHit", tTracks.mtrkNHit, &tTracks.b_mtrkNHit);
   t->SetBranchAddress("mtrkQual", tTracks.mtrkQual, &tTracks.b_mtrkQual);
   t->SetBranchAddress("mtrkChi2", tTracks.mtrkChi2, &tTracks.b_mtrkChi2);
   t->SetBranchAddress("mtrkNdof", tTracks.mtrkNdof, &tTracks.b_mtrkNdof);
   t->SetBranchAddress("mtrkDz1", tTracks.mtrkDz1, &tTracks.b_mtrkDz1);
   t->SetBranchAddress("mtrkDzError1", tTracks.mtrkDzError1, &tTracks.b_mtrkDzError1);
   t->SetBranchAddress("mtrkDxy1", tTracks.mtrkDxy1, &tTracks.b_mtrkDxy1);
   t->SetBranchAddress("mtrkDxyError1", tTracks.mtrkDxyError1, &tTracks.b_mtrkDxyError1);
   t->SetBranchAddress("mtrkDz2", tTracks.mtrkDz2, &tTracks.b_mtrkDz2);
   t->SetBranchAddress("mtrkDzError2", tTracks.mtrkDzError2, &tTracks.b_mtrkDzError2);
   t->SetBranchAddress("mtrkDxy2", tTracks.mtrkDxy2, &tTracks.b_mtrkDxy2);
   t->SetBranchAddress("mtrkDxyError2", tTracks.mtrkDxyError2, &tTracks.b_mtrkDxyError2);
   t->SetBranchAddress("trkGMPId", tTracks.trkGMPId, &tTracks.b_trkGMPId);
   t->SetBranchAddress("trkMPId", tTracks.trkMPId, &tTracks.b_trkMPId);
   t->SetBranchAddress("trkPId", tTracks.trkPId, &tTracks.b_trkPId);


	}

}


void setupParticleTree(TTree *t, Particles &tTracks)
{
   t->SetBranchAddress("nParticle", &tTracks.nParticle, &tTracks.b_nParticle);
   t->SetBranchAddress("pStatus", tTracks.pStatus, &tTracks.b_pStatus);
   t->SetBranchAddress("pPId", tTracks.pPId, &tTracks.b_pPId);
   t->SetBranchAddress("pEta", tTracks.pEta, &tTracks.b_pEta);
   t->SetBranchAddress("pPhi", tTracks.pPhi, &tTracks.b_pPhi);
   t->SetBranchAddress("pPt", tTracks.pPt, &tTracks.b_pPt);
}



void setupGenParticleTree(TTree *t,GenParticles &tGenParticles, bool doCheck = 1)
{
   // Set branch addresses and branch pointers
   if (t->GetBranch("event")) t->SetBranchAddress("event", &tGenParticles.event, &tGenParticles.b_event);
   if (t->GetBranch("b")) t->SetBranchAddress("b", &tGenParticles.b, &tGenParticles.b_b);
   if (t->GetBranch("npart")) t->SetBranchAddress("npart", &tGenParticles.npart, &tGenParticles.b_npart);
   if (t->GetBranch("ncoll")) t->SetBranchAddress("ncoll", &tGenParticles.ncoll, &tGenParticles.b_ncoll);
   if (t->GetBranch("nhard")) t->SetBranchAddress("nhard", &tGenParticles.nhard, &tGenParticles.b_nhard);
   if (t->GetBranch("phi0")) t->SetBranchAddress("phi0", &tGenParticles.phi0, &tGenParticles.b_phi0);
   if (t->GetBranch("scale")) t->SetBranchAddress("scale", &tGenParticles.scale, &tGenParticles.b_scale);
   if (t->GetBranch("n")) t->SetBranchAddress("n", tGenParticles.n, &tGenParticles.b_n);
   if (t->GetBranch("ptav")) t->SetBranchAddress("ptav", tGenParticles.ptav, &tGenParticles.b_ptav);
   if (t->GetBranch("mult")) t->SetBranchAddress("mult", &tGenParticles.mult, &tGenParticles.b_mult);
   if (t->GetBranch("pt")) t->SetBranchAddress("pt", tGenParticles.pt, &tGenParticles.b_pt);
   if (t->GetBranch("eta")) t->SetBranchAddress("eta", tGenParticles.eta, &tGenParticles.b_eta);
   if (t->GetBranch("phi")) t->SetBranchAddress("phi", tGenParticles.phi, &tGenParticles.b_phi);
   if (t->GetBranch("pdg")) t->SetBranchAddress("pdg", tGenParticles.pdg, &tGenParticles.b_pdg);
   if (t->GetBranch("chg")) t->SetBranchAddress("chg", tGenParticles.chg, &tGenParticles.b_chg);
   if (t->GetBranch("sube")) t->SetBranchAddress("sube", tGenParticles.sube, &tGenParticles.b_sube);
   if (t->GetBranch("vx")) t->SetBranchAddress("vx", &tGenParticles.vx, &tGenParticles.b_vx);
   if (t->GetBranch("vy")) t->SetBranchAddress("vy", &tGenParticles.vy, &tGenParticles.b_vy);
   if (t->GetBranch("vz")) t->SetBranchAddress("vz", &tGenParticles.vz, &tGenParticles.b_vz);
   if (t->GetBranch("vr")) t->SetBranchAddress("vr", &tGenParticles.vr, &tGenParticles.b_vr);
   if (doCheck) {
   if (t->GetMaximum("mult")>maxEntrySim) { cout <<"FATAL ERROR: Arrary size of mult too small!!!  "<<t->GetMaximum("mult")<<endl;
 }   }
}



void TracksParticles::setupGenPartTree( TFile *f )
{
	genPartTree = (TTree*)f->Get("HiGenParticle");
	setupGenParticleTree( genPartTree, genParts);
}

void TracksParticles::GetEntry( int iEv )
{
	genPartTree->GetEntry(iEv);
}
