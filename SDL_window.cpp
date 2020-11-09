#include "SDL_window.h"
#include <stdexcept>

SDL_window::SDL_window(const std::string& name, size_t width, size_t height)
{
	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	if (!window)
	{
		throw std::runtime_error{ SDL_GetError() };
	}
	renderer = SDL_CreateRenderer(window, 0, 0);
	if (!renderer)
	{
		SDL_DestroyWindow(window);
		throw std::runtime_error{ SDL_GetError() };
	}
}

void SDL_window::clear()
{
	SDL_RenderClear(renderer);
}

void SDL_window::update()
{
	SDL_RenderPresent(renderer);
}

bool SDL_window::has_close_request()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			return true;
		}
	}
	return false;
}

SDL_window::~SDL_window()
{
	if (renderer)
	{
		SDL_DestroyRenderer(renderer);
	}
	if (window)
	{
		SDL_DestroyWindow(window);
	}
}
