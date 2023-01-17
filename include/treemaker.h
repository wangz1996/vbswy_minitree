#ifndef TREEMAKER_H
#define TREEMAKER_H
#include "lwtnn/LightweightGraph.hh"
#include "lwtnn/parse_json.hh"
#include <memory>

#include <fstream>
#include <iostream>
#include <vector>
#include <TMath.h>
#include <string>
#include <cstring>
#include <map>
#include <TFile.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TH1.h>
#include <TH2.h>
#include <stdio.h>
#include<cmath>
#include<TRandom.h>
#include<TLorentzVector.h>

using namespace std;

class Treemaker
{
public:
	Treemaker();
	~Treemaker();
	double Get500(const int &en,const bool &isdata);
	double Get1000(const int &en,const bool &isdata);
	double Get500_nogapjets(const int &en,const bool &isdata);
	double Get1000_nogapjets(const int &en,const bool &isdata);

	void ReadValue(const std::map<std::string, double> &_mapnogapjet, const std::map<std::string, double> &_mapinput);
	void Estimate();
private:
	lwt::LightweightGraph *nn_mjj_500_even;
	lwt::LightweightGraph *nn_mjj_500_odd;
	lwt::LightweightGraph *nn_mjj_1000_even;
	lwt::LightweightGraph *nn_mjj_1000_odd;
	lwt::LightweightGraph *nn_mjj_500_nogapjets_even;
	lwt::LightweightGraph *nn_mjj_500_nogapjets_odd;
	lwt::LightweightGraph *nn_mjj_1000_nogapjets_even;
	lwt::LightweightGraph *nn_mjj_1000_nogapjets_odd;

	std::map<std::string, std::map<std::string, double> > inputs_nogapjets;
	std::map<std::string, std::map<std::string, double> > inputs;
	
	std::map<std::string, double> nn_mjj_500_even_outputs;
        std::map<std::string, double> nn_mjj_500_odd_outputs;
        std::map<std::string, double> nn_mjj_1000_even_outputs;
        std::map<std::string, double> nn_mjj_1000_odd_outputs;
        std::map<std::string, double> nn_mjj_500_nogapjets_even_outputs;
        std::map<std::string, double> nn_mjj_500_nogapjets_odd_outputs;
        std::map<std::string, double> nn_mjj_1000_nogapjets_even_outputs;
        std::map<std::string, double> nn_mjj_1000_nogapjets_odd_outputs;
	
	double nn_score_mjj_500_even;
	double nn_score_mjj_500_odd;
	double nn_score_mjj_1000_even;
	double nn_score_mjj_1000_odd;
	double nn_score_mjj_500_nogapjets_even;
	double nn_score_mjj_500_nogapjets_odd;
	double nn_score_mjj_1000_nogapjets_even;
	double nn_score_mjj_1000_nogapjets_odd;
};

#endif
