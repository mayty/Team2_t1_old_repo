#include "graph.h"
#include <cmath>

constexpr double PI = 3.141592653589793238463;

Graph::Graph(const std::string& filename) {
	// creating dummy graph for testing
	// --------------------------------
	adjacencyList.resize(8);
	adjacencyList[0].edges.emplace_front(3, 2);
	adjacencyList[0].edges.emplace_front(4, 2);

	adjacencyList[1].edges.emplace_front(6, 2);

	adjacencyList[2].edges.emplace_front(5, 2);

	adjacencyList[3].edges.emplace_front(0, 2);
	adjacencyList[3].edges.emplace_front(7, 2);

	adjacencyList[4].edges.emplace_front(0, 2);
	adjacencyList[4].edges.emplace_front(6, 2);

	adjacencyList[5].edges.emplace_front(2, 2);

	adjacencyList[6].edges.emplace_front(1, 2);
	adjacencyList[6].edges.emplace_front(4, 2);

	adjacencyList[7].edges.emplace_front(3, 2);
	// --------------------------------

	double step = PI * 2 / adjacencyList.size();
	double x0 = 400;
	double y0 = 300;
	double r = 250;
	for (int i = 0; i < adjacencyList.size(); ++i)
	{
		adjacencyList[i].point.x = x0 + r * std::cos(i * step);
		adjacencyList[i].point.y = y0 + r * std::sin(i * step);
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
}

Graph::~Graph() {
}
