#ifndef _SPICE_NETLIST_
#define _SPICE_NETLIST_

#include <string>
#include <vector>
#include "Net.h"
#include "Node.h"
#include "Model.h"
#include <Eigen/Dense>
#include <vector>

namespace SpiceLibrary {
	class NetList
	{
	public:
		std::string title;
		Eigen::MatrixXd coefficient;
		Eigen::VectorXd source;
		Eigen::ColPivHouseholderQR<Eigen::MatrixXd> invCoeffcient;

	private:
		std::vector<Net> netList;
		std::vector<Node> nodeStack;
		std::vector<Model> modelStack;

	public:
		NetList();
		~NetList();
		void init();
		bool parse(std::string netText);
		bool makeMatrix();
		Eigen::VectorXd solve(Eigen::VectorXd input);
	private:
		bool registModel(Model& model);
		bool searchModel(Model& model);
		bool registNode(Node& node);
		bool searchNode(Node& node);
		bool registNet(Net& net);
		bool searchNet(Net& net);
		std::vector<Net> outNodeNets(int index);
		std::vector<Net> inNodeNets(int index);
		bool aNet(Net& net, int inNodeIndex, int outNodeIndex);
	};
}

#endif
