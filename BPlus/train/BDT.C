#include "../../includes/uti.h"
#include "oldresults07-17-2019/dataset/weights/rootfiles_TMVA_X_BDT_BDTG_CutsGA_CutsSA_5p0_10p0_0-1-2-3-4-5-6-7-8-9-10-11-12-13_root/TMVAClassification_BDT.class.C"

#define MAX_XB       20000

void BDT(TString inputname, TString outputname,
		Float_t ptmin, Float_t ptmax, TString mvatype)
{
	void makeoutput(TString infname, TString ofname, TString treename);
	makeoutput(inputname,Form("%s.root",outputname.Data()),Form("%s_pt_%.0f_%.0f",mvatype.Data(),ptmin,ptmax));
}

void makeoutput(TString infname, TString ofname, TString treename)
{
	TFile* inf = new TFile(infname);
	//TTree* t = (TTree*)inf->Get("Bfinder/ntphi");
	//t->AddFriend("mvaTree");
	TTree* t = (TTree*)inf->Get("ntphi");


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
	theInputVars.push_back(a10);
	theInputVars.push_back(a11);
	theInputVars.push_back(a12);
	theInputVars.push_back(a13);
	theInputVars.push_back(a14);

	std::vector<double> inputValues;
	ReadBDT mva(theInputVars);

	TFile* outf = new TFile(ofname,"recreate");
	TTree* mvaTree = new TTree(Form("%s",treename.Data()),"BDT");

	double BDT[MAX_XB];
	mvaTree->Branch("Bsize",&Bsize,"Bsize/I");
	mvaTree->Branch(Form("%s",treename.Data()),BDT,Form("%s[Bsize]/D",treename.Data()));
	std::cout<<std::endl;
	std::cout<<"  Input file: "<<infname<<std::endl;
	std::cout<<"  Calculating MVA values ..."<<std::endl;
	for(int i=0;i< t->GetEntries();i++)
	{
		if(i%100==0) std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10)<<i<<"\033[0m"<<" / "<<std::setw(10)<<t->GetEntries()<<" ] "<<"\033[1;36m"<<Form("%.0f",100.*i/t->GetEntries())<<"%\033[0m"<<"\r"<<std::flush;
		t->GetEntry(i);
		for(int j=0;j<Bsize;j++)
		{
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
			inputValues.push_back(Bd0[j]);
			inputValues.push_back(cos(Bdtheta[j]));
			inputValues.push_back(Bchi2cl[j]);
			inputValues.push_back(Btrk1Eta[j]);
			inputValues.push_back(Btrk2Eta[j]);


			BDT[j] = mva.GetMvaValue(inputValues);      
		}

		mvaTree->Fill();
	}
	std::cout<<std::endl<<"  Processed "<<"\033[1;31m"<<t->GetEntries()<<"\033[0m event(s)."<<std::endl;
	outf->cd();
	outf->Write();
	outf->Close();
}

int main(int argc, char* argv[])
{
	if(argc==6)
	{
		BDT(argv[1],argv[2],atof(argv[3]),atof(argv[4]),argv[5]);
		return 0;
	}
	else
	{
		std::cout<<"  Error: invalid argument number - BDT()"<<std::endl;
		return 1;
	}
}
