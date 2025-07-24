// directx_game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#include "Renderer.h"
#include "TriangleTestPipeline.h"
#include "VertexBuffer.h"
#include "DirectXMath.h"
#include "PositionColorVertex.h"
#include "PositionColorPipeline.h"


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
	PositionColorPipeline positionColorPipeline(renderer);

	std::vector<PositionColorVertex> vertices = {

		// Triangle 1
		{ { -0.5f, 0.5f, 0.0f },   { 1.0f, 0.0f, 0.0f, 1.0f } },  // Top left vertex
		{ { 0.5f, -0.5f, 0.0f },  { 0.0f, 1.0f, 0.0f, 1.0f } }, // Bottom right vertex
		{ { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }, // Bottom left vertex

		// Triangle 2
		{ { 0.5f, 0.5f, 0.0f },   { 1.0f, 0.0f, 0.0f, 1.0f } },  // Top right vertex
		{ { 0.5f, -0.5f, 0.0f },  { 0.0f, 1.0f, 0.0f, 1.0f } }, // Bottom right vertex
		{ { -0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } } // Top left vertex
	};
	VertexBuffer<PositionColorVertex> vertexBuffer(
		renderer,
		vertices,
		vertices.size(),
		"TriangleVertices");


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

		// trianglePipeline.Render(); // Render the triangle
		positionColorPipeline.Render(vertexBuffer); // Render the colored triangle

		renderer.EndRenderPass();

		SDL_Delay(16); // Simulate a frame delay (about 60 FPS)	
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}