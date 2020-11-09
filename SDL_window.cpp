#include "SDL_window.h"
#include <stdexcept>

SDL_Window::SDL_Window(const std::string& name, size_t width, size_t height) {
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

void SDL_Window::Clear() {
	SDL_RenderClear(renderer);
}

void SDL_Window::Update() {
	SDL_RenderPresent(renderer);
}

bool SDL_Window::HasCloseRequest() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return true;
		}
	}
	return false;
}

SDL_Window::~SDL_Window() {
	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}
	if (window) {
		SDL_DestroyWindow(window);
	}
}
