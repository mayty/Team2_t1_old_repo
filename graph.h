#pragma once
#include "SDL_window.h"
class Graph { // class for working with graphs
private:
public:
	Graph(const std::string& filename); // creates graph with points in circular layout from file with json data
	void Draw(SDL_Window& window); // draws current graph
	void ApplyForce(); // applyes forces to verteces
	~Graph();
};

