#include "treemaker.h"

Treemaker::Treemaker()
{
	std::ifstream input_mjj_500_even("/afs/cern.ch/user/j/jmcgowan/Public/treemakers/models/classifier_classifier_mjj_500_0107_even.json");
	std::ifstream input_mjj_500_odd("/afs/cern.ch/user/j/jmcgowan/Public/treemakers/models/classifier_classifier_mjj_500_0107_odd.json");
	std::ifstream input_mjj_1000_even("/afs/cern.ch/user/j/jmcgowan/Public/treemakers/models/classifier_classifier_mjj_1000_0107_even.json");
	std::ifstream input_mjj_1000_odd("/afs/cern.ch/user/j/jmcgowan/Public/treemakers/models/classifier_classifier_mjj_1000_0107_odd.json");
	std::ifstream input_mjj_500_nogapjets_even("/afs/cern.ch/user/j/jmcgowan/Public/treemakers/models/classifier_classifier_mjj_500_nogapjets_0107_even.json");
	std::ifstream input_mjj_500_nogapjets_odd("/afs/cern.ch/user/j/jmcgowan/Public/treemakers/models/classifier_classifier_mjj_500_nogapjets_0107_odd.json");
	std::ifstream input_mjj_1000_nogapjets_even("/afs/cern.ch/user/j/jmcgowan/Public/treemakers/models/classifier_classifier_mjj_1000_nogapjets_0107_even.json");
	std::ifstream input_mjj_1000_nogapjets_odd("/afs/cern.ch/user/j/jmcgowan/Public/treemakers/models/classifier_classifier_mjj_1000_nogapjets_0107_odd.json");


	nn_mjj_500_even = new lwt::LightweightGraph(lwt::parse_json_graph(input_mjj_500_even),"");
	nn_mjj_500_odd = new lwt::LightweightGraph(lwt::parse_json_graph(input_mjj_500_odd),"");
	nn_mjj_1000_even = new lwt::LightweightGraph(lwt::parse_json_graph(input_mjj_1000_even),"");
	nn_mjj_1000_odd = new lwt::LightweightGraph(lwt::parse_json_graph(input_mjj_1000_odd),"");
	nn_mjj_500_nogapjets_even = new lwt::LightweightGraph(lwt::parse_json_graph(input_mjj_500_nogapjets_even),"");
	nn_mjj_500_nogapjets_odd = new lwt::LightweightGraph(lwt::parse_json_graph(input_mjj_500_nogapjets_odd),"");
	nn_mjj_1000_nogapjets_even = new lwt::LightweightGraph(lwt::parse_json_graph(input_mjj_1000_nogapjets_even),"");
	nn_mjj_1000_nogapjets_odd = new lwt::LightweightGraph(lwt::parse_json_graph(input_mjj_1000_nogapjets_odd),"");
	
}
Treemaker::~Treemaker()
{
}

void Treemaker::ReadValue(const std::map<std::string, double> &_mapnogapjet, const std::map<std::string, double> &_mapinput)
{
	inputs_nogapjets.clear();
	inputs_nogapjets["node_0"] = _mapnogapjet;
	inputs.clear();
	inputs["node_0"] = _mapinput;
}

void Treemaker::Estimate()
{
	nn_score_mjj_500_even= nn_mjj_500_even->compute(inputs)["out_0"];
	nn_score_mjj_500_odd= nn_mjj_500_odd->compute(inputs)["out_0"];
	nn_score_mjj_1000_even= nn_mjj_1000_even->compute(inputs)["out_0"];
	nn_score_mjj_1000_odd= nn_mjj_1000_odd->compute(inputs)["out_0"];
	nn_score_mjj_500_nogapjets_even= nn_mjj_500_nogapjets_even->compute(inputs_nogapjets)["out_0"];
	nn_score_mjj_500_nogapjets_odd= nn_mjj_500_nogapjets_odd->compute(inputs_nogapjets)["out_0"];
	nn_score_mjj_1000_nogapjets_even= nn_mjj_1000_nogapjets_even->compute(inputs_nogapjets)["out_0"];
	nn_score_mjj_1000_nogapjets_odd= nn_mjj_1000_nogapjets_odd->compute(inputs_nogapjets)["out_0"];
}

double Treemaker::Get500(const int &en,const bool &isdata)
{
	if(isdata)
	{
		return (nn_score_mjj_500_even+nn_score_mjj_500_odd)/2;
	}
	else
	{
		if(en%2 ==1)return nn_score_mjj_500_even;
		else return nn_score_mjj_500_odd;
	}
}

double Treemaker::Get1000(const int &en,const bool &isdata)
{
	if(isdata)
	{
		return (nn_score_mjj_1000_even+nn_score_mjj_1000_odd)/2;
	}
	else
	{
		if(en%2 ==1)return nn_score_mjj_1000_even;
		else return nn_score_mjj_1000_odd;
	}
}

double Treemaker::Get500_nogapjets(const int &en,const bool &isdata)
{
	if(isdata)
	{
		return (nn_score_mjj_500_nogapjets_even+nn_score_mjj_500_nogapjets_odd)/2;
	}
	else
	{
		if(en%2 ==1)return nn_score_mjj_500_nogapjets_even;
		else return nn_score_mjj_500_nogapjets_odd;
	}
}

double Treemaker::Get1000_nogapjets(const int &en,const bool &isdata)
{
	if(isdata)
	{
		return (nn_score_mjj_1000_nogapjets_even+nn_score_mjj_1000_nogapjets_odd)/2;
	}
	else
	{
		if(en%2 ==1)return nn_score_mjj_1000_nogapjets_even;
		else return nn_score_mjj_1000_nogapjets_odd;
	}
}

