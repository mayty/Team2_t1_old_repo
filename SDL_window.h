#pragma once
#include "SDL.h"
#include <string>
class SDL_window { // window class containing all methods for drawing
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
public:
	SDL_window(const std::string& name, size_t width = 800, size_t height = 600);
	void draw_line(size_t x0, size_t y0, size_t x1, size_t y1);
	void draw_rectangle(size_t x0, size_t y0, size_t x1, size_t y1);
	void set_draw_color(unsigned char r, unsigned char g, unsigned char b);
	void clear();
	void update();
	bool has_close_request();
	~SDL_window();
};

