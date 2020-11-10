#include <SDL.h>
#include "SDL_manager.h"
#include "SDL_window.h"
#include "graph.h"
#include <chrono>
#include <thread>

int main(int argC, char** argV) {
	SdlManager manager{};
	SdlWindow window{"graph demo", 800, 600};
	Graph demo_graph{ "test.json" };
	auto last_update_time = std::chrono::high_resolution_clock::now();

	while (!window.HasCloseRequest()) {
		window.SetDrawColor(0, 0, 0);
		window.Clear();
		demo_graph.Draw(window);

		auto current_time = std::chrono::high_resolution_clock::now();
		if (current_time - last_update_time < std::chrono::milliseconds{ 33 }) {
			std::this_thread::sleep_for(std::chrono::milliseconds{ 33 } - (current_time - last_update_time));
		}
		last_update_time = std::chrono::high_resolution_clock::now();
		window.Update();
		demo_graph.ApplyForce();
	}

	return 0;
}