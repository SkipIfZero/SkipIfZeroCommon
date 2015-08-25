#include "sfz/screens/GameLoop.hpp"

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "sfz/sdl/GameController.hpp"
#include "sfz/math/Vector.hpp"

namespace sfz {

// Typedefs
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

using std::int32_t;
using time_point = std::chrono::high_resolution_clock::time_point;
using std::unordered_map;
using std::vector;

// Static helper functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

static float calculateDelta(time_point& previousTime) noexcept
{
	time_point currentTime = std::chrono::high_resolution_clock::now();

	using FloatSecond = std::chrono::duration<float>;
	float delta = std::chrono::duration_cast<FloatSecond>(currentTime - previousTime).count();

	previousTime = currentTime;
	return delta;
}

static void initControllers(unordered_map<int32_t, sdl::GameController>& controllers) noexcept
{
	controllers.clear();

	int numJoysticks = SDL_NumJoysticks();
	for (int i = 0; i < numJoysticks; ++i) {
		if (!SDL_IsGameController(i)) continue;
		
		sdl::GameController c{i};
		if (c.id() == -1) continue;
		if (controllers.find(c.id()) != controllers.end()) continue;

		controllers[c.id()] = std::move(c);
	}
}

// GameLoop function
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

void runGameLoop(sdl::Window& window, shared_ptr<BaseScreen> currentScreen)
{
	UpdateState state;

	// Initialize controllers
	initControllers(state.controllers);

	// Initialize time delta
	time_point previousTime;
	state.delta = calculateDelta(previousTime);

	// Initialize SDL events
	SDL_GameControllerEventState(SDL_ENABLE);
	SDL_Event event;

	while (true) {
		// Calculate delta
		state.delta = std::min(calculateDelta(previousTime), 0.2f);

		// Process events
		state.events.clear();
		state.handledEvents.clear();
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {

			// Quitting and resizing window
			case SDL_QUIT:
				currentScreen->onQuit();
				return;
			case SDL_WINDOWEVENT:
				switch (event.window.event) {
				case SDL_WINDOWEVENT_RESIZED:
					currentScreen->onResize(window.dimensions(), window.drawableDimensions());
					break;
				default:
					state.events.push_back(event);
					break;
				}
				break;

			// SDL_GameController events
			case SDL_CONTROLLERDEVICEADDED:
			case SDL_CONTROLLERDEVICEREMOVED:
			case SDL_CONTROLLERDEVICEREMAPPED:
			case SDL_CONTROLLERBUTTONDOWN:
			case SDL_CONTROLLERBUTTONUP:
			case SDL_CONTROLLERAXISMOTION:
				state.handledEvents.push_back(event);
				break;

			default:
				state.events.push_back(event);
				break;
			}
		}

		// Updates controllers
		update(state.controllers, state.handledEvents);

		// Update current screen
		UpdateOp op = currentScreen->update(state);

		// Perform eventual operations requested by screen update
		switch (op.type) {
		case UpdateOpType::SWITCH_SCREEN:
			currentScreen = op.newScreen;
			continue;
		case UpdateOpType::QUIT:
			currentScreen->onQuit();
			return;
		case UpdateOpType::REINIT_CONTROLLERS:
			initControllers(state.controllers);
			continue;

		case UpdateOpType::NO_OP:
		default:
			// Do nothing
			break;
		}

		// Render current screen
		currentScreen->render(state);

		SDL_GL_SwapWindow(window.mPtr);
	}
}

} // namespace sfz