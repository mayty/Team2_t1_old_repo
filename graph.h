#pragma once
#include <vector>
#include <list>
#include "SDL_window.h"

class Graph { // class for working with graphs
private:
    struct Vertex {
        struct Edge {
            size_t to;
            double length;
        };
        struct Point {
            double x;
            double y;
        };
        size_t originalIdx;
        std::list<Edge> edges;
        Point point;
    };
    std::vector<Vertex> adjacencyList;
public:
    explicit Graph(const std::string& filename); // creates graph with points in circular layout from file with json data
    void Draw(SDL_Window& window) const; // draws current graph
    void ApplyForce(); // applyes forces to verteces
    ~Graph();
};

