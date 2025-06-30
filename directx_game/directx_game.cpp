// directx_game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "Renderer.h"
#include "TriangleTestPipeline.h"


int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_Window* window = SDL_CreateWindow("DirectX Game",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800, 600,
		SDL_WINDOW_SHOWN);

	if (!window) {
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return -1;
	}

	Renderer renderer(window, 800, 600);
	TriangleTestPipeline trianglePipeline(renderer);

	bool running = true;
	SDL_Event event;
	while (running)
	{
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}

		renderer.BeginRenderPass();

		trianglePipeline.render();

		renderer.EndRenderPass();

		SDL_Delay(16); // Simulate a frame delay (about 60 FPS)	
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}