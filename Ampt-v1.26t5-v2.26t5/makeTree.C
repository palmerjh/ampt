#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "stdlib.h"
#include "TFile.h"
#include "TTree.h"
using namespace std;

const Int_t maxnh = 2000;
Int_t b_npg;
Int_t b_pid[maxnh];
Int_t b_mass[maxnh];
Float_t b_b; // impact parameter
Float_t b_ptg[maxnh], b_etag[maxnh], b_phig[maxnh];

void makeTree(Int_t job)
{
	//TFile * in = new TFile(Form("/store/user/palmerjh/Results/job-%d/particle_list.dat"))
	TFile out(Form("jb%d/amptTree.root", job), "RECREATE", "ROOT file with tree"); // output file 
	TTree *tree = new TTree("tree","Event tree with a few branches");
	tree->Branch("npg", &b_npg, "npg/I");   // # of particles in event
	tree->Branch("b", &b_b, "b/F");   // impact parameter
  	tree->Branch("ptg", &b_ptg, "ptg[npg]/F");  // transverse momentum of each particle;
  	tree->Branch("etag", &b_etag, "etag[npg]/F"); // eta for each particle
  	tree->Branch("phig", &b_phig, "phig[npg]/F"); // phi for each particle
  	tree->Branch("pid", &b_pid, "pid[npg]/I"); // pid for each particle; pid_lookup.dat in same directory as particle_list.dat
	tree->Branch("mass", &b_mass, "mass[npg]/F"); // mass for each particle;

	//ifstream infile(Form("/store/user/palmerjh/ampt/pAu/bMax_3/prod00/jb%d/ana/ampt.dat", job));
	ifstream infile(Form("jb%d/ana/ampt.dat", job));
	//ifstream infile(Form("job-%d/particle_list.dat", job));
	
	string line;

	Int_t trashEvent, trashTestNumber, pid, trashNucProj, trashNucTarget, trashNucElastic, trashNucInelastic, trash8, trash9;
	Float_t trash10, pX, pY, pZ, mass, trashX, trashY, trashZ, trashTime, mom; 

	while (getline(infile, line))
	{
		istringstream iss(line);
		if (!(iss >> trashEvent >> trashTestNumber >> b_npg >> b_b >> trashNucProj >> trashNucTarget >> trashNucElastic >> trashNucInelastic >> trash8 >> trash9 >> trash10)) { exit(1); } // error
	
		for (Int_t i = 0; i < b_npg; i++) {
			getline(infile, line);
			istringstream issParticle(line);

			if (!(issParticle >> pid >> pX >> pY >> pZ >> mass >> trashX >> trashY >> trashZ >> trashTime)) { exit(1); } // error

			mom = pX*pX + pY*pY;
			b_ptg[i] = pow(mom,0.5);
			mom += pZ*pZ;
			mom = pow(mom,0.5);
			b_etag[i] = atanh(pZ/mom);
			b_phig[i] = atan2(pY,pX);
			b_pid[i] = pid;
			b_mass[i] = mass;
		}

		tree->Fill();
	}

	tree->Write();
	out.Write();
	out.Close();

	//delete tree;
	//tree = 0;

}
