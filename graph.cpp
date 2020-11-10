#include "graph.h"
#include <cmath>

constexpr double PI = 3.141592653589793238463;
constexpr double xMiddle = 400;
constexpr double yMiddle = 300;

Graph::Graph(const std::string& filename) {
	// creating dummy graph for testing
	// --------------------------------
	adjacencyList.resize(8);
	adjacencyList[0].edges.emplace_front(3, 2.0);
	adjacencyList[0].edges.emplace_front(4, 7.0);
	adjacencyList[0].edges.emplace_front(7, 5.0);

	adjacencyList[1].edges.emplace_front(6, 2.0);

	adjacencyList[2].edges.emplace_front(5, 3.0);
	adjacencyList[2].edges.emplace_front(7, 3.0);

	adjacencyList[3].edges.emplace_front(0, 2.0);
	adjacencyList[3].edges.emplace_front(7, 2.0);

	adjacencyList[4].edges.emplace_front(0, 7.0);
	adjacencyList[4].edges.emplace_front(6, 2.0);

	adjacencyList[5].edges.emplace_front(2, 3.0);
	adjacencyList[5].edges.emplace_front(7, 2.0);

	adjacencyList[6].edges.emplace_front(1, 2.0);
	adjacencyList[6].edges.emplace_front(4, 2.0);

	adjacencyList[7].edges.emplace_front(0, 5.0);
	adjacencyList[7].edges.emplace_front(2, 2.0);
	adjacencyList[7].edges.emplace_front(3, 2.0);
	adjacencyList[7].edges.emplace_front(5, 2.0);

	maxLength = 7.0;
	// --------------------------------

	double step = PI * 2 / adjacencyList.size();
	double r = 250;
	for (int i = 0; i < adjacencyList.size(); ++i)
	{
		adjacencyList[i].point.x = xMiddle + r * std::cos(i * step);
		adjacencyList[i].point.y = yMiddle + r * std::sin(i * step);
	}
}

void Graph::Draw(SdlWindow& window) const {

	window.SetDrawColor(255, 255, 255);
	for (int i = 0; i < adjacencyList.size(); ++i) {
		for (const auto& j : adjacencyList[i].edges) {
			if (j.to < i) {
				break;
			}
			window.DrawLine(std::round(adjacencyList[i].point.x), std::round(adjacencyList[i].point.y), std::round(adjacencyList[j.to].point.x), std::round(adjacencyList[j.to].point.y));
		}
	}
	for (const auto& i : adjacencyList) {
		window.DrawRectangle(std::round(i.point.x - 5), std::round(i.point.y - 5), std::round(i.point.x + 5), std::round(i.point.y + 5));
	}
}

void Graph::ApplyForce() {
	std::vector<std::pair<double, double>> forces;
	forces.resize(adjacencyList.size());

	for (int i = 0; i < adjacencyList.size(); ++i) { // Coulomb's law
		for (int j = adjacencyList.size() - 1; j > i; --j) {
			double x = adjacencyList[i].point.x - adjacencyList[j].point.x; // vector j -> i 
			double y = adjacencyList[i].point.y - adjacencyList[j].point.y;
			
			double distance = std::sqrt(x * x + y * y);
			double force = 10000.0 / (distance * distance);

			double xForceNormilized = x / distance;
			double yForceNormilized = y / distance;

			forces[i].first += xForceNormilized * force;
			forces[i].second += yForceNormilized * force;
			forces[j].first -= xForceNormilized * force;
			forces[j].second -= yForceNormilized * force;
		}
	}

	for (int i = 0; i < adjacencyList.size(); ++i) { // push to the middle
		double x = adjacencyList[i].point.x - xMiddle; // vector j -> i 
		double y = adjacencyList[i].point.y - yMiddle;

		double distance = std::sqrt(x * x + y * y);
		double force;
		if (distance > std::min(yMiddle, xMiddle)) {
			force = 5.0;
		}
		else {
			continue;
		}

		double xForceNormilized = x / distance;
		double yForceNormilized = y / distance;

		forces[i].first -= xForceNormilized * force;
		forces[i].second -= yForceNormilized * force;
	}

	for (int i = 0; i < adjacencyList.size(); ++i) { // Hooke's law
		for (const auto& j : adjacencyList[i].edges) {
			if (j.to < i) {
				break;
			}
			double x = adjacencyList[i].point.x - adjacencyList[j.to].point.x; // vector j -> i
			double y = adjacencyList[i].point.y - adjacencyList[j.to].point.y;

			double distance = std::sqrt(x * x + y * y);
			double force = (maxLength + 1 - j.length) * distance / 100.0;

			double xforcenormilized = x / distance;
			double yforcenormilized = y / distance;

			forces[i].first -= xforcenormilized * force;
			forces[i].second -= yforcenormilized * force;
			forces[j.to].first += xforcenormilized * force;
			forces[j.to].second += yforcenormilized * force;
		}
	}

	for (int i = 0; i < adjacencyList.size(); ++i) {
		adjacencyList[i].point.x += forces[i].first * 0.5;
		adjacencyList[i].point.y += forces[i].second * 0.5;
	}
}

Graph::~Graph() {
}
