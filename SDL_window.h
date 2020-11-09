#pragma once
#include "SDL.h"
#include <string>
class SDL_Window { // window class containing all methods for drawing
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
public:
	SDL_Window(const std::string& name, size_t width = 800, size_t height = 600);
	void DrawLine(size_t x0, size_t y0, size_t x1, size_t y1);
	void DrawRectangle(size_t x0, size_t y0, size_t x1, size_t y1);
	void SetDrawColor(unsigned char r, unsigned char g, unsigned char b);
	void Clear();
	void Update();
	bool HasCloseRequest();
	~SDL_Window();
};

