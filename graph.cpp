#include "graph.h"
#include "json.h"
#include <cmath>
#include <fstream>

constexpr double PI = 3.141592653589793238463;
constexpr double xMiddle = 400;
constexpr double yMiddle = 300;
constexpr double r = std::min(xMiddle - 30, yMiddle - 30);

Graph::Graph(const std::string& filename) {
	std::ifstream in(filename);
	Json::Document document = Json::Load(in);
	auto nodeMap = document.GetRoot().AsMap();
	adjacencyList.reserve(nodeMap["points"].AsArray().size());
	std::map<size_t, size_t> idxConverter;
	double phi = 0;
	double phi_step = 2 * PI / nodeMap["points"].AsArray().size();
	for (const auto& vertexNode : nodeMap["points"].AsArray()) {
		auto vertexMap = vertexNode.AsMap();
		idxConverter[vertexMap["idx"].AsInt()] = adjacencyList.size();
		adjacencyList.push_back( {static_cast<size_t>(vertexMap["idx"].AsInt()), static_cast<size_t>(vertexMap["post_idx"].AsInt()), std::list<Vertex::Edge>(), 
			{xMiddle + r * std::cos(phi), yMiddle + r * std::sin(phi)} });
		phi += phi_step;
	}
	for (const auto& edgeNode : nodeMap["lines"].AsArray()) {
		auto edgeMap = edgeNode.AsMap();
		size_t from = idxConverter[edgeMap["points"].AsArray()[0].AsInt()];
		Vertex::Edge edge(edgeMap["idx"].AsInt(), idxConverter[edgeMap["points"].AsArray()[1].AsInt()], edgeMap["length"].AsDouble());
		AddEdge(from, edge);
		std::swap(from, edge.to);
		AddEdge(from, edge);
		maxLength = std::max(maxLength, edge.length);
	}
}

void Graph::AddEdge(size_t from, Vertex::Edge edge) {
	auto pos = std::find_if(begin(adjacencyList[from].edges), end(adjacencyList[from].edges), [edge](const Vertex::Edge& cur) {return cur.to < edge.to; });
	if (pos == end(adjacencyList[from].edges)) {
		adjacencyList[from].edges.push_back(edge);
	} else {
		adjacencyList[from].edges.insert(pos, edge);
	}
}

void Graph::Draw(SdlWindow& window) {
	write_lock.lock();
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
	write_lock.unlock();
}

double Graph::ApplyForce() {
	static std::vector<std::pair<double, double>> forces;
	if (forces.empty())
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

		double xForceNormilized = x / distance;
		double yForceNormilized = y / distance;

		forces[i].first -= xForceNormilized;
		forces[i].second -= yForceNormilized;
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
	double total = 0;
	write_lock.lock();
	for (int i = 0; i < adjacencyList.size(); ++i) {
		adjacencyList[i].point.x += forces[i].first * 0.5;
		adjacencyList[i].point.y += forces[i].second * 0.5;
		total += std::abs(forces[i].first * 0.5) + std::abs(forces[i].second * 0.5);
		forces[i].first *= 0.94;
		forces[i].second *= 0.94;
	}
	write_lock.unlock();
	return total;
}

Graph::~Graph() {
}
