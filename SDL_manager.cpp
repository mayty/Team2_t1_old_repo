#include "SDL_manager.h"
#include "SDL.h"
#include <exception>
#include <stdexcept>
SDL_manager::SDL_manager()
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		throw std::runtime_error{ SDL_GetError() };
	}
}

SDL_manager::~SDL_manager()
{
	SDL_Quit();
}
