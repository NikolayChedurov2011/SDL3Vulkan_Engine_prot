#pragma once
#include "SDL3/SDL.h"

class Game_Base {
private:


public:
	Game_Base() : window(nullptr), renderer(nullptr), bIsRunning(false) {}
	bool initialize(int windowWidth = 1200, int windowHeight = 800, bool isFullScreen = false);
	void run(); // Main gameloop
	void tick(); // dTime, target FPS 

	virtual bool postInitialize() { return true; }; // Override function for child classes initialization if needed
	virtual void handleEvents(SDL_Event& event) {};
	virtual void update() {}; // Use to update data
	virtual void render() {}; // Use to render

	void getWindowSize(int* windowWidth, int* windowHeight);

	inline SDL_Window* getWindow() { return window; }
	inline SDL_Renderer* getRenderer() { return renderer; }
	inline void setGameIsRunning(bool newState) { bIsRunning = newState; }
	inline const double getDeltaTime() const { return dT; }

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	bool bIsRunning;

	// Time and FPS
	int targetFPS{ 60 };
	int frameDelay{ 1000 / targetFPS };
	int frameCount{ 0 };
	Uint64 currentTime{ 0 };
	Uint64 lastTime{ 0 };
	double dT{ 0.0 };
	double fps{ 0.0 };

	void cleanup();
};