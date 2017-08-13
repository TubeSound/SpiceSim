#include "NetList.h"
#include "../Utility/StringUtility.h"
#include "Parse.h"


using namespace std;
using namespace SpiceUtility;

namespace SpiceLibrary {

	NetList::NetList()
	{
		init();
	}


	NetList::~NetList()
	{
	}

	void NetList::init() {
		this->netList.clear();
		this->modelStack.clear();
		this->nodeStack.clear();
		Node gnd;
		gnd.name = "0";
		registNode(gnd);
	}

	bool NetList::parse(std::string netText) {
		Net net;
		if (net.parse(netText)) {
			return registNet(net);
		}
		else {
			return false;
		}
	}

	bool NetList::makeMatrix() {
		int nodeSize = this->nodeStack.size() - 1;	// without 0 node (Gnd)
		if (nodeSize == 0) {
			return false;
		}

		this->coefficient = Eigen::MatrixXd::Zero(nodeSize, nodeSize);
		this->source = Eigen::VectorXd::Zero(nodeSize, 1);
	
		for (int index = 1; index < this->nodeStack.size(); index++) {
			vector<Net> ins = inNodeNets(index);
			vector<Net> outs = outNodeNets(index);
			for (Net net : ins) {
				Model model = net.model;
				double val = net.value.value;
				if (model.type == ModelType::currentSource) {
					this->source(index - 1) = -val;
				} else if (model.type == ModelType::resistance) {
					if (val == 0.0) {
						return false;
					}
					double conductance = 1.0 / net.value.value;
					int outIndex = net.outNode.index;
					if (outIndex > 0) { // outIndex == 0 means GND
						this->coefficient(index - 1, outIndex - 1) -= conductance;
					}
					this->coefficient(index - 1, index - 1) += conductance;
				}
			}

			for (Net net : outs) {
				Model model = net.model;
				double val = net.value.value;
				if (model.type == ModelType::currentSource) {
					this->source(index - 1) = val;
				}
				else if (model.type == ModelType::resistance) {
					if (val == 0.0) {
						return false;
					}
					double conductance = 1.0 / net.value.value;
					int inIndex = net.inNode.index;
					if (inIndex > 0) {	// inIndex == 0 means GND
						this->coefficient(index - 1, inIndex - 1) -= conductance;
					}
					this->coefficient(index - 1, index - 1) += conductance;
				}
			}	
		}
		this->invCoeffcient = this->coefficient.colPivHouseholderQr();
	}
	
	Eigen::VectorXd NetList::solve(Eigen::VectorXd input) {
		return this->invCoeffcient.solve(input);
	}

	bool NetList::registNet(Net& net) {
		registModel(net.model);
		registNode(net.inNode);
		registNode(net.outNode);
		net.index = this->netList.size();
		this->netList.push_back(net);
		return true;
	}

	bool NetList::registModel(Model& model) {
		model.index = this->modelStack.size();
		this->modelStack.push_back(model);
		return true;
	}

	bool NetList::registNode(Node& node) {
		if (!searchNode(node)) {
			node.index = this->nodeStack.size();
			this->nodeStack.push_back(node);
			return true;
		}
		else {
			return false;
		}
	}

	bool NetList::searchNet(Net& net) {
		if (this->netList.size() == 0) {
			return false;
		}
		bool found = false;
		for (Net n : this->netList) {
			if (n.index == net.index) {
				net = n;
				found = true;
				break;
			}
		}
		return found;
	}

	vector<Net> NetList::outNodeNets(int index) {
		vector<Net> nets;
		for (Net net : this->netList) {
			if (net.outNode.index == index) {
				nets.push_back(net);
			}
		}
		return nets;
	}

	vector<Net> NetList::inNodeNets(int index) {
		vector<Net> nets;
		nets.clear();
		for (Net net : this->netList) {
			if (net.inNode.index == index) {
				nets.push_back(net);
			}
		}
		return nets;
	}

	bool NetList::aNet(Net& net, int inNodeIndex, int outNodeIndex) {
		int count = 0;
		for (Net n : this->netList) {
			if (n.inNode.index == inNodeIndex && n.outNode.index == outNodeIndex) {
				net = n;
				count++;
			}
		}
		return (count == 0);
	}

	bool NetList::searchModel(Model& model) {
		if (this->modelStack.size() == 0) {
			return false;
		}
		bool found = false;
		for (Model m : this->modelStack) {
			if (m.index == model.index) {
				model = m;
				found = true;
				break;
			}
		}
		return found;
	}

	bool NetList::searchNode(Node& node) {
		if (this->nodeStack.size() == 0) {
			return false;
		}
		bool found = false;
		for (Node n : this->nodeStack) {
			if (toLower(n.name) == toLower(node.name)) {
				node = n;
				found = true;
				break;
			}
		}
		return found;
	}
}