#include "SDL_manager.h"
#include "SDL.h"
#include <exception>
#include <stdexcept>
SDL_Manager::SDL_Manager() {
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		throw std::runtime_error{ SDL_GetError() };
	}
}

SDL_Manager::~SDL_Manager() {
	SDL_Quit();
}
