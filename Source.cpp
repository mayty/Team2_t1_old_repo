#include <SDL.h>
#include "SDL_manager.h"
#include "SDL_window.h"
#include "graph.h"
#include <chrono>
#include <thread>

int main(int argC, char** argV) {
	SDL_manager manager{};
	SDL_window window{"graph demo", 800, 600};
	graph demo_graph{ "test.json" };
	auto last_update_time = std::chrono::high_resolution_clock::now();

	while (!window.has_close_request()) {
		window.clear();
		demo_graph.draw(window);
		auto current_time = std::chrono::high_resolution_clock::now();
		if (current_time - last_update_time < std::chrono::milliseconds{ 33 }) {
			std::this_thread::sleep_for(std::chrono::milliseconds{ 33 } - (current_time - last_update_time));
		}
		last_update_time = std::chrono::high_resolution_clock::now();
		window.update();
		demo_graph.apply_force();
	}

	return 0;
}