#include "uti.h"

//#include "TMVA_BDT_PbPb_pt_5p0_10p0.class.C"
#include "readxml/weights/TMVAClassification_BDT.class.C"

#define MAX_XB       20000
using namespace std;


void BDT(TString infname, TString ofname, int ptmin, int ptmax)
{
	TFile* inf = new TFile(infname);
	TTree* t = (TTree*)inf->Get("Bfinder/ntphi");
	//TTree* t = (TTree*)inf->Get("ntphi");
	//	t->AddFriend("mvaTree");

	Int_t           Bsize;
	Int_t           RunNo;
	Int_t           EvtNo;
	Int_t           LumiNo;
	Float_t         Bchi2cl[MAX_XB];   //[Bsize]
	Float_t         BsvpvDistance[MAX_XB];   //[Bsize]
	Float_t         BsvpvDisErr[MAX_XB];   //[Bsize]
	Float_t         Balpha[MAX_XB];   //[Bsize]   
	Float_t         Btrk1Pt[MAX_XB];   //[Bsize]   
	Float_t         Btrk2Pt[MAX_XB];   //[Bsize]   
	Float_t         Btrk1Eta[MAX_XB];   //[Bsize]   
	Float_t         Btrk2Eta[MAX_XB];   //[Bsize]   
	Float_t         Btrk1Dxy1[MAX_XB];   //[Bsize]   
	Float_t         Btrk2Dxy1[MAX_XB];   //[Bsize]   
	Float_t         Btrk1DxyError1[MAX_XB];   //[Bsize]   
	Float_t         Btrk2DxyError1[MAX_XB];   //[Bsize]   
	Float_t         Btrk1Dz1[MAX_XB];   //[Bsize]   
	Float_t         Btrk2Dz1[MAX_XB];   //[Bsize]   
	Float_t         Btrk1DzError1[MAX_XB];   //[Bsize]   
	Float_t         Btrk2DzError1[MAX_XB];   //[Bsize]   

	Float_t         Btrk1D0Err[MAX_XB];   //[Bsize]   
	Float_t         Btrk2D0Err[MAX_XB];   //[Bsize]   
	Float_t         Btktkmass[MAX_XB]; 
	Float_t         Bd0[MAX_XB]; 
	Float_t         Bd0Err[MAX_XB]; 
	Float_t         Bdtheta[MAX_XB]; 
	Float_t         Bpt[MAX_XB]; 

	t->SetBranchAddress("RunNo", &RunNo);
	t->SetBranchAddress("EvtNo", &EvtNo);
	t->SetBranchAddress("LumiNo", &LumiNo);


	t->SetBranchAddress("Bsize", &Bsize);
	t->SetBranchAddress("Balpha", Balpha);
	t->SetBranchAddress("Bchi2cl", Bchi2cl);
	t->SetBranchAddress("BsvpvDistance", BsvpvDistance);
	t->SetBranchAddress("BsvpvDisErr", BsvpvDisErr);
	//  t->SetBranchAddress("MVA", MVA);

	t->SetBranchAddress("Bd0Err", Bd0Err);
	t->SetBranchAddress("Btrk1Pt", Btrk1Pt);
	t->SetBranchAddress("Btrk2Pt", Btrk2Pt);
	t->SetBranchAddress("Bd0", Bd0);
	//t->SetBranchAddress("Bd0Err", Bd0Err);
	t->SetBranchAddress("Bdtheta", Bdtheta);
	t->SetBranchAddress("Btktkmass", Btktkmass);
	t->SetBranchAddress("Btrk1Dxy1", Btrk1Dxy1);
	t->SetBranchAddress("Btrk2Dxy1", Btrk2Dxy1);
	t->SetBranchAddress("Btrk1Eta", Btrk1Eta);
	t->SetBranchAddress("Btrk2Eta", Btrk2Eta);
	t->SetBranchAddress("Btrk1DxyError1", Btrk1DxyError1);
	t->SetBranchAddress("Btrk2DxyError1", Btrk2DxyError1);
	t->SetBranchAddress("Bpt", Bpt);
	t->SetBranchAddress("Btrk1Dz1", Btrk1Dz1);
	t->SetBranchAddress("Btrk2Dz1", Btrk2Dz1);
	t->SetBranchAddress("Btrk1DzError1", Btrk1DzError1);
	t->SetBranchAddress("Btrk2DzError1", Btrk2DzError1);



	std::vector<std::string> theInputVars;
	std::string a1 = "Btrk1Pt";
	std::string a2 = "Btrk2Pt";
	std::string a3 = "abs(Btrk1Dz1/Btrk1DzError1)";
	std::string a4 = "abs(Btrk2Dz1/Btrk2DzError1)";
	std::string a5 = "abs(Btrk1Dxy1/Btrk1DxyError1)";
	std::string a6 = "abs(Btrk2Dxy1/Btrk2DxyError1)";
	std::string a7 = "abs(Btktkmass-1.019455)";
	std::string a8 = "BsvpvDistance/BsvpvDisErr";
	std::string a9 = "Balpha";
	std::string a10 = "Bd0";
	std::string a11 = "cos(Bdtheta)";
	std::string a12 = "Bchi2cl";
	std::string a13 = "Btrk1Eta";
	std::string a14 = "Btrk2Eta";

	theInputVars.push_back(a1);
	theInputVars.push_back(a2);
	theInputVars.push_back(a3);
	theInputVars.push_back(a4);
	theInputVars.push_back(a5);
	theInputVars.push_back(a6);
	theInputVars.push_back(a7);
	theInputVars.push_back(a8);
	theInputVars.push_back(a9);
//	theInputVars.push_back(a10);
//	theInputVars.push_back(a11);
	theInputVars.push_back(a12);
//	theInputVars.push_back(a13);
//	theInputVars.push_back(a14);


	std::vector<double> inputValues;
	ReadBDT mva(theInputVars);
	int run;
	int evt;
	int lumi;



	TFile* outf = new TFile(ofname,"recreate");
	outf->cd();
	TTree* mvaTree = new TTree(Form("BDT_pt_%d_%d",ptmin,ptmax),"BDT");	

	double BDT[MAX_XB];
	mvaTree->Branch("Bsize",&Bsize,"Bsize/I");
	mvaTree->Branch(Form("BDT_pt_%d_%d",ptmin,ptmax),BDT,Form("BDT_pt_%d_%d[Bsize]/D",ptmin,ptmax));
	mvaTree->Branch("run",&run,"run/I");
	mvaTree->Branch("evt",&evt,"evt/I");
	mvaTree->Branch("lumi",&lumi,"lumi/I");
	std::cout<<std::endl;
	std::cout<<"  Input file: "<<infname<<std::endl;
	std::cout<<"  Calculating MVA values ..."<<std::endl;
	for(int i=0;i< t->GetEntries();i++)
	{
	
		t->GetEntry(i);
		run = RunNo;
		evt = EvtNo;
		lumi = LumiNo;

		if(i%1000==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<t->GetEntries()<<" ] "<<"\033[1;36m"<<Form("%.0f",100.*i/t->GetEntries())<<"%\033[0m"<<"\r"<<std::flush;

		for(int j=0;j<Bsize;j++)
		{

			/*
			cout << "Btrk1Pt = " << Btrk1Pt[j] << endl;
			cout << "Btrk2Pt = " << Btrk2Pt[j] << endl;
			cout << "abs(Btrk1Dz1/Btrk1DzError1) = " << abs(Btrk1Dz1[j]/Btrk1DzError1[j]) << endl;
			cout << "abs(Btrk2Dz1/Btrk2DzError1) = " << abs(Btrk2Dz1[j]/Btrk2DzError1[j]) << endl;
			cout << "abs(Btrk1Dxy1/Btrk1DxyError1) = " << abs(Btrk1Dxy1[j]/Btrk1DxyError1[j]) << endl;
			cout << "abs(Btrk2Dxy1/Btrk2DxyError1) = " << abs(Btrk2Dxy1[j]/Btrk2DxyError1[j]) << endl;
			cout << "abs(Btktkmass-1.019455) = " << abs(Btktkmass[j]-1.019455) << endl;
			cout << "BsvpvDistance/BsvpvDisErr = " << BsvpvDistance[j]/BsvpvDisErr[j]<< endl;
			cout << "Balpha = " <<Balpha[j]<< endl;
			cout << "Bd0 = " << Bd0[j] << endl;
			cout << "cos(Bdtheta) = " << cos(Bdtheta[j]) << endl;
			cout << "Bchi2cl = " << Bchi2cl[j] << endl;
			cout << "Btrk1Eta = " << Btrk1Eta[j] << endl;
			cout << "Btrk2Eta = " << Btrk2Eta[j] << endl;
			*/

			inputValues.clear();

			inputValues.push_back(Btrk1Pt[j]);
			inputValues.push_back(Btrk2Pt[j]);

			inputValues.push_back(abs(Btrk1Dz1[j]/Btrk1DzError1[j]));
			inputValues.push_back(abs(Btrk2Dz1[j]/Btrk2DzError1[j]));
			inputValues.push_back(abs(Btrk1Dxy1[j]/Btrk1DxyError1[j]));
			inputValues.push_back(abs(Btrk2Dxy1[j]/Btrk2DxyError1[j]));
			inputValues.push_back(abs(Btktkmass[j]-1.019455));
			inputValues.push_back(BsvpvDistance[j]/BsvpvDisErr[j]);
			inputValues.push_back(Balpha[j]);
	//		inputValues.push_back(Bd0[j]);
	//		inputValues.push_back(cos(Bdtheta[j]));
			inputValues.push_back(Bchi2cl[j]);
	//		inputValues.push_back(Btrk1Eta[j]);
	//		inputValues.push_back(Btrk2Eta[j]);

			BDT[j] = mva.GetMvaValue(inputValues);  

		

		}

		mvaTree->Fill();
	}
	std::cout<<std::endl<<"  Processed "<<"\033[1;31m"<<t->GetEntries()<<"\033[0m event(s)."<<std::endl;
	outf->Write();
	outf->Close();
}



int main(int argc, char* argv[])
{
	if(argc==5)
	{
		BDT(argv[1],argv[2],atof(argv[3]), atof(argv[4]));
		return 0;
	}
	else
	{
		std::cout<<"  Error: invalid argument number - BDT()"<<std::endl;
		return 1;
	}
}

