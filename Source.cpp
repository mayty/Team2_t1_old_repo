#include <SDL.h>
#include "SDL_manager.h"
#include "SDL_window.h"
#include "graph.h"
#include <chrono>
#include <thread>

#define PLACEHOLDER

int main(int argC, char** argV) {
	SdlManager manager{};
	SdlWindow window{"graph demo", 800, 600};
	Graph demo_graph{ "test.json" };
	auto last_update_time = std::chrono::high_resolution_clock::now();

#ifdef PLACEHOLDER
	int x1 = 0;
	int y1 = 0;
	int x1_incr = 1;
	int y1_incr = 3;
	int x1_dir = 1;
	int y1_dir = 1;
	int x2 = 0;
	int y2 = 0;
	int x2_incr = 2;
	int y2_incr = 5;
	int x2_dir = 1;
	int y2_dir = 1;
#endif

	while (!window.HasCloseRequest()) {
		window.SetDrawColor(0, 0, 0);
		window.Clear();

#ifdef PLACEHOLDER
		window.SetDrawColor(255, 255, 255);
		window.DrawLine(x1, y1, x2, y2);
		demo_graph.Draw(window);
		x1 += x1_incr * x1_dir;
		y1 += y1_incr * y1_dir;
		x2 += x2_incr * x2_dir;
		y2 += y2_incr * y2_dir;
		if (x1 < 0 || x1 >= 800) {
			x1_dir *= -1;
		}
		if (y1 < 0 || y1 >= 600) {
			y1_dir *= -1;
		}
		if (x2 < 0 || x2 >= 800) {
			x2_dir *= -1;
		}
		if (y2 < 0 || y2 >= 600) {
			y2_dir *= -1;
		}
#endif

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