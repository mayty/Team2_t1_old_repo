#include "SDL_window.h"
#include <stdexcept>

#include <iostream>

SdlWindow::SdlWindow(const std::string& name, size_t width, size_t height) {
	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	if (!window) {
		throw std::runtime_error{ SDL_GetError() };
	}
	renderer = SDL_CreateRenderer(window, 0, 0);
	if (!renderer) {
		SDL_DestroyWindow(window);
		throw std::runtime_error{ SDL_GetError() };
	}
}

void SdlWindow::DrawLine(int x0, int y0, int x1, int y1) {
	SDL_RenderDrawLine(renderer, offset_x + x0 * scale, offset_y + y0 * scale, offset_x + x1 * scale, offset_y + y1 * scale);
}

void SdlWindow::DrawRectangle(int x0, int y0, int x1, int y1) {
	SDL_Rect rect;
	rect.x = offset_x + x0 * scale;
	rect.y = offset_y + y0 * scale;
	rect.h = (y1 - y0) * scale;
	rect.w = (x1 - x0) * scale;
	SDL_RenderDrawRect(renderer, &rect);
}

void SdlWindow::SetDrawColor(unsigned char r, unsigned char g, unsigned char b) {
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}

void SdlWindow::Clear() {
	SDL_RenderClear(renderer);
}

void SdlWindow::Update() {
	SDL_RenderPresent(renderer);
}

bool SdlWindow::HasCloseRequest() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			return true;
		case SDL_MOUSEWHEEL:
			if (event.wheel.y < 0) {
				zoomIn();
			}
			else {
				zoomOut();
			}
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_ESCAPE:
				return true;
			case SDL_SCANCODE_UP:
				moveUp();
				break;
			case SDL_SCANCODE_DOWN:
				moveDown();
				break;
			case SDL_SCANCODE_LEFT:
				moveLeft();
				break;
			case SDL_SCANCODE_RIGHT:
				moveRight();
				break;
			}
			break;
		}
	}
	return false;
}

SdlWindow::~SdlWindow() {
	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}
	if (window) {
		SDL_DestroyWindow(window);
	}
}

void SdlWindow::moveUp()
{
	offset_y += 5;
}

void SdlWindow::moveDown()
{
	offset_y -= 5;
}

void SdlWindow::moveLeft()
{
	offset_x += 5;
}

void SdlWindow::moveRight()
{
	offset_x -= 5;
}

void SdlWindow::zoomIn()
{
	scale -= 0.1;
	if (scale < 0.1)
	{
		scale = 0.1;
	}
}

void SdlWindow::zoomOut()
{
	scale += 0.1;
}
