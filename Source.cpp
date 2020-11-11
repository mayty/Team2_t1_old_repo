#include <SDL.h>
#include "SDL_manager.h"
#include "SDL_window.h"
#include "graph.h"
#include <chrono>
#include <thread>

constexpr int frameTime = 33;

int main(int argC, char** argV) {
	SdlManager manager{};
	SdlWindow window{"graph demo", 800, 600};
	Graph demo_graph{ "JSON_test_files/big_graph.json" };
	bool to_exit = false;
	auto last_update_time = std::chrono::high_resolution_clock::now();
	std::thread graphCalcThread{ [&demo_graph, &to_exit]() {
		double change = 100.0;
		while (!to_exit && change > 20.0) {
			change = demo_graph.ApplyForce();
		} 
	} 
	};

	while (!(to_exit = window.HasCloseRequest())) {
		window.SetDrawColor(0, 0, 0);
		window.Clear();
		demo_graph.Draw(window);

		auto current_time = std::chrono::high_resolution_clock::now();
		if (current_time - last_update_time < std::chrono::milliseconds{ frameTime }) {
			std::this_thread::sleep_for(std::chrono::milliseconds{ frameTime } - (current_time - last_update_time));
		}
		last_update_time = std::chrono::high_resolution_clock::now();
		window.Update();
	}

	graphCalcThread.join();

	return 0;
}