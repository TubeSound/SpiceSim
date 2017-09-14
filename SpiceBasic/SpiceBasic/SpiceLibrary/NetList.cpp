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
		this->nodeStack.clear();
		this->resistorStack.clear();
		this->currentSourceStack.clear();
		Node gnd;
		gnd.parse("0");
		appendNode(gnd);
	}

	bool NetList::makeMatrix() {
		int matrixSize = this->nodeStack.size() - 1;	// without 0 node (Gnd)
		if (matrixSize == 0) {
			return false;
		}

		this->coefficient = Eigen::MatrixXd::Zero(matrixSize, matrixSize);
		this->source = Eigen::MatrixXXd::Zero(matrixSize, 1);

		for (Resisor r : this->resistorStack) {
			int idx0 = r.nodes[0].index;
			int idx1 = r.nodes[1].index;
			if (idx0 > 0) {
				this->coefficient(idx0, idx0) += r.conductance;
			}
			if (idx1 > 0) {
				this->coefficient(idx1, idx1) += r.conductance;
			}
			if (idx0 > 0 && idx1 > 0) {
				this->coefficient(idx0, idx1) -= r.conductance;
				this->coefficient(idx1, idx0) -= r.conductance;
			}
		}

		for(CurrentSource cs : this->currentSourceStack) {
			int idx0 = cs.nodes[0].index;
			int idx1 = cs.nodes[1].index;
			if (idx0 > 0) {
				this->source(idx0, 0) -= cs.current.value;
			}
			if (idx1 > 0) {
				this->source(idx1, 0) -= cs.current.value;
			}
		}

		this->holder = this->coefficient.colPivHouseholderQr();
		this->invCoeffcient = this->holder.inverse();
	}
	
	Eigen::VectorXd NetList::solve(Eigen::VectorXd input) {
		return this->invCoeffcient.solve(input);
	}

	bool NetList::appendResistor(Resistor& resistor) {
		resistor.index = this->resitorStack.size();
		this->resistorStack.push_back(resitor);
		appenNodes(resistor.nodes);
		return true;
	}

	bool NetList::appendCurrentSource(CurrentSource& currentSource) {
		currentSource.index = this->currentSourceStack.size();
		this->currentSourceStack.push_back(currentSource);
		appenNodes(currentSource.nodes);
		return true;
	}

	bool NetList::appendNodes(Node nodes[2]) {
		for (int i = 0; i < 2; i++) {
			appendNode(nodes[i]);
		}
		return true;
	}

	bool NetList::appendNode(Node& node) {
		if (!isNode(node)) {
			node.index = this->nodeStack.size();
			this->nodeStack.push_back(node);
			return true;
		} else {
			return false;
		}
	}

	bool NetList::isNode(Node& node) {
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