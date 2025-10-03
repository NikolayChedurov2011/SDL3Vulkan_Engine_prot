#include "Game_Base.h"
#include <memory>
#include <string>

bool Game_Base::initialize(int windowWidth, int windowHeight, bool isFullScreen) {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		return false;
	}

	Uint64 windowFlag = isFullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE;
	window = SDL_CreateWindow("SDL3 Vulkan Engine", windowWidth, windowHeight, windowFlag);

	if (!window) {
		SDL_Quit();
		return false;
	}

	renderer = SDL_CreateRenderer(window, nullptr);

	if (!renderer) {
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	if (!postInitialize()) {
		cleanup();
		return false;
	}

	bIsRunning = true;
	return true;
}

void Game_Base::run() {
	SDL_Event event;

	while (bIsRunning) {
		while (SDL_PollEvent(&event)) {
			handleEvents(event);
		}

		tick();
		update();
		render();
	}
}

void Game_Base::cleanup() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game_Base::getWindowSize(int* windowWidth, int* windowHeight) {
	SDL_GetWindowSize(window, windowWidth, windowHeight);
}

void Game_Base::tick() {
	currentTime = SDL_GetTicks();

	dT = (currentTime - lastTime) / 1000.;

	frameCount++;

	if (dT >= 1.) {
		fps = frameCount / dT;
		frameCount = 0;
		lastTime = currentTime;
	}

	SDL_Log(("FPS: %f, Elapsed: %f"), fps, dT);

	Uint64 frameTime{ SDL_GetTicks() - currentTime };

	if (frameTime < frameDelay) {
		SDL_Delay(frameDelay - frameTime);
	}
}