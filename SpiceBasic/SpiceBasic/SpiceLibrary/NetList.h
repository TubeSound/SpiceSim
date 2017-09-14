#ifndef _SPICE_NETLIST_
#define _SPICE_NETLIST_

#include <string>
#include <vector>
#include "Net.h"
#include "Node.h"
#include "Resitsor.h"
#include "CurrentSource.h"
#include <Eigen/Dense>
#include <vector>

namespace SpiceLibrary {
	class NetList
	{
	public:
		std::string title;
		Eigen::MatrixXd coefficient;
		Eigen::MatrixXd source;
		Eigen::MatrixXd invCoeffcient;
		Eigen::ColPivHouseholderQR<Eigen::MatrixXd> holder;

	private:
		std::vector<Node> nodeStack;
		std::vector<Resistor> resistorStack;
		std::vector<CurrentSource> currentSourceStack

	public:
		NetList();
		~NetList();
		void init();
		bool parse(std::string netText);
		bool makeMatrix();
		Eigen::VectorXd solve(Eigen::VectorXd input);
	private:
		bool appendResistor(Resistor& res);
		bool appendCurrentSoiurce(CurrentSource& cs);
		bool appendNodes(Node nodes[2]);
		bool appenNode(Node& node);
		bool isNode(Node& node);

	};
}

#endif
