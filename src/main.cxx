#include "treemaker.h"
#include "global.h"

using namespace std;

int main(int argc,char* argv[])
{
	//Register a NN
	Treemaker *tm = new Treemaker();
	string temp=string(argv[1]);
	string name_out = string(temp).substr(string(temp).find_last_of("/")+1);
	TFile *f=TFile::Open(TString(temp),"READ");
	if(!f)return 0;
	TTree *t=(TTree*)f->Get("vbswy");
	TTree *t2=(TTree*)f->Get("DAOD_tree");
	TFile *fout=new TFile(TString(string(argv[2]))+TString(name_out),"RECREATE");
	TTree *tout=(TTree*)t->CloneTree(0);
	TTree *tout2=(TTree*)t2->CloneTree(0);
	Float_t        lep_pt;
	Float_t        met;
	Float_t        lep_eta;
	Float_t        gam_eta;
	Float_t        gam_pt;
	Float_t        gam_xi;
	Float_t        ly_xi;
	Float_t        wy_pt;
	Float_t        w_mt;
	Float_t        j0_pt;
	Float_t        j0_eta;
	Float_t        j0gam_dr;
	Float_t        j1_pt;
	Int_t           n_bjets_85;
	Float_t        jj_drap;
	Float_t        jj_m;
	Float_t        jj_deta;
	ULong64_t       selection_bits;
	ULong64_t       object_bits;
	ULong64_t       region_bits;
	Double_t	nn_mjj500;
	Double_t	nn_mjj1000;
	Double_t	nn_mjj500_nogapjets;
	Double_t	nn_mjj1000_nogapjets;
	ULong64_t	eventnumber;
	Int_t		n_gapjets;
	Double_t	dsid;
	Float_t		dPhi_Wy_jj;
	Float_t		dR_Wy_jj;
	Float_t		dR_Wy;
	t->SetBranchAddress("eventnumber", &eventnumber);
	t->SetBranchAddress("lep_pt", &lep_pt);
	t->SetBranchAddress("met", &met);
	t->SetBranchAddress("lep_eta", &lep_eta);
	t->SetBranchAddress("gam_eta", &gam_eta);
	t->SetBranchAddress("gam_pt", &gam_pt);
	t->SetBranchAddress("gam_xi", &gam_xi);
	t->SetBranchAddress("ly_xi", &ly_xi);
	t->SetBranchAddress("wy_pt", &wy_pt);
	t->SetBranchAddress("w_mt", &w_mt);
	t->SetBranchAddress("j0_pt", &j0_pt);
	t->SetBranchAddress("j0_eta", &j0_eta);
	t->SetBranchAddress("j0gam_dr", &j0gam_dr);
	t->SetBranchAddress("j1_pt", &j1_pt);
	t->SetBranchAddress("n_bjets_85", &n_bjets_85);
	t->SetBranchAddress("jj_drap", &jj_drap);
	t->SetBranchAddress("jj_m", &jj_m);
	t->SetBranchAddress("jj_deta", &jj_deta);
	t->SetBranchAddress("region_bits", &region_bits);
	t->SetBranchAddress("selection_bits", &selection_bits);
	t->SetBranchAddress("object_bits", &object_bits);
	t->SetBranchAddress("dPhi_Wy_jj", &dPhi_Wy_jj);
	t->SetBranchAddress("dR_Wy_jj", &dR_Wy_jj);
	t->SetBranchAddress("dR_Wy", &dR_Wy);
	t->SetBranchAddress("n_gapjets", &n_gapjets);
	t2->SetBranchAddress("dsid",&dsid);
	tout->Branch("nn_mjj500",&nn_mjj500);
	tout->Branch("nn_mjj1000",&nn_mjj1000);
	tout->Branch("nn_mjj500_nogapjets",&nn_mjj500_nogapjets);
	tout->Branch("nn_mjj1000_nogapjets",&nn_mjj1000_nogapjets);
	map<std::string,double> input;
	map<std::string,double> input_nogapjets;
	int Entry = t->GetEntries();
	int Entry2 = t2->GetEntries();
	t2->GetEntry(0);
	for(int i=0;i<Entry;++i)
	{
		t->GetEntry(i);
		bool pass_onegam = (selection_bits & EventSelections::onegam )!= 0;
		bool pass_trigger = (selection_bits & EventSelections::trigger )!= 0;
		bool pass_twojet = (selection_bits & EventSelections::twojet )!= 0;
		bool pass_primary_vertex = (selection_bits & EventSelections::primary_vertex )!= 0;
		bool pass_duplicate = (selection_bits & EventSelections::duplicate )!= 0;
		bool pass_dq = (selection_bits & EventSelections::dq )!= 0;
		bool pass_jetclean = (selection_bits & EventSelections::jetclean )!= 0;
		bool pass_vy_OR = (selection_bits & EventSelections::vy_OR )!= 0;
		bool is_Wenu = (selection_bits & EventSelections::Wenu )!= 0;
		bool pass_onelep = (selection_bits & EventSelections::onelep )!= 0;
		bool pass_second_lepton_veto = (selection_bits & EventSelections::second_lepton_veto )!= 0;
		bool pass_ly_Z_veto = (selection_bits & EventSelections::ly_Z_veto )!= 0;
		bool pass_dphi = (selection_bits & EventSelections::dphi )!= 0;
		bool pass_dr = (selection_bits & EventSelections::dr )!= 0;
		bool e_passIP = (object_bits & ObjectSelections::bm_e_passIP )!= 0;
		bool gam_idTight = (object_bits & ObjectSelections::bm_gam_idTight )!= 0;
		bool gam_isoTight = (object_bits & ObjectSelections::bm_gam_isoTight )!= 0;
		bool baseline = ((pass_onegam) && (pass_trigger) && (pass_twojet) && (pass_primary_vertex) && (pass_duplicate) &&
				(pass_dq) && (pass_jetclean) && (pass_vy_OR) && (is_Wenu) && (pass_onelep) &&
				(pass_second_lepton_veto) && (gam_pt > 22.0) && (gam_idTight && gam_isoTight && fabs(gam_eta)<2.37) &&
				(lep_pt > 30.0) && (met > 30.0) && (lep_eta > -2.5) && (lep_eta < 2.5) &&
				(w_mt > 30.0) && (pass_ly_Z_veto) &&
				(pass_dphi) && (pass_dr) && (j0_pt > 50.0) && (j1_pt > 50.0) && (n_bjets_85 == 0) &&
				(1) && (e_passIP) && jj_m>500.);
		if(baseline)
		{
			input.clear();
			input_nogapjets.clear();
			input = {{"variable_0",gam_pt},
                                {"variable_1",lep_pt},
                                {"variable_2",wy_pt},
                                {"variable_3",w_mt},
                                {"variable_4",dPhi_Wy_jj},
                                {"variable_5",dR_Wy_jj},
                                {"variable_6",gam_xi},
                                {"variable_7",ly_xi},
                                {"variable_8",dR_Wy},
                                {"variable_9",j0_pt},
                                {"variable_10",j0_eta},
                                {"variable_11",j0gam_dr},
                                {"variable_12",jj_deta},
				{"variable_13",n_gapjets}};

			input_nogapjets = {{"variable_0",gam_pt},
                                {"variable_1",lep_pt},
                                {"variable_2",wy_pt},
                                {"variable_3",w_mt},
                                {"variable_4",dPhi_Wy_jj},
                                {"variable_5",dR_Wy_jj},
                                {"variable_6",gam_xi},
                                {"variable_7",ly_xi},
                                {"variable_8",dR_Wy},
                                {"variable_9",j0_pt},
                                {"variable_10",j0_eta},
                                {"variable_11",j0gam_dr},
                                {"variable_12",jj_deta}};
			tm->ReadValue(input_nogapjets,input);
			tm->Estimate();
			nn_mjj500 = tm->Get500(eventnumber,dsid==0);
			nn_mjj1000 = tm->Get1000(eventnumber,dsid==0);
			nn_mjj500_nogapjets = tm->Get500_nogapjets(eventnumber,dsid==0);
			nn_mjj1000_nogapjets = tm->Get1000_nogapjets(eventnumber,dsid==0);
			tout->Fill();
		}
	}
	for(int i=0;i<Entry2;++i)
	{
		t2->GetEntry(i);
		tout2->Fill();
		cout<<i<<endl;
	}
	fout->cd();
	tout->Write();
	tout2->Write();
	fout->Close();
	f->Close();
}
