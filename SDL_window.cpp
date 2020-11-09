#include "SDL_window.h"
#include <stdexcept>

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

void SdlWindow::DrawLine(size_t x0, size_t y0, size_t x1, size_t y1)
{
	SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
}

void SdlWindow::DrawRectangle(size_t x0, size_t y0, size_t x1, size_t y1)
{
	SDL_Rect rect;
	rect.x = x0;
	rect.y = y0;
	rect.h = y1 - y0;
	rect.w = x1 - x0;
}

void SdlWindow::SetDrawColor(unsigned char r, unsigned char g, unsigned char b)
{
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
		if (event.type == SDL_QUIT) {
			return true;
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
