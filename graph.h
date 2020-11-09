#pragma once
#include "SDL_window.h"
class graph { // class for working with graphs
private:
public:
	graph(const std::string& filename); // creates graph with points in circular layout from file with json data
	void draw(SDL_window& window); // draws current graph
	void apply_force(); // applyes forces to verteces
	~graph();
};

