#pragma once
#include "SDL.h"
#include <string>
class SdlWindow { // window class containing all methods for drawing
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	int offset_x = 0;
	int offset_y = 0;
	double scale = 1.0;
public:
	SdlWindow(const std::string& name, size_t width = 800, size_t height = 600);
	void DrawLine(int x0, int y0, int x1, int y1);
	void DrawRectangle(int x0, int y0, int x1, int y1);
	void SetDrawColor(unsigned char r, unsigned char g, unsigned char b);
	void Clear();
	void Update();
	bool HasCloseRequest();
	~SdlWindow();
private:
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void zoomIn();
	void zoomOut();
};

