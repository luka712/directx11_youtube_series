// directx_game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <wrl/client.h>

#include <dxgi.h>
#pragma comment(lib, "dxgi.lib")

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

using namespace Microsoft::WRL;

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
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

	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;

	D3D_FEATURE_LEVEL featureLevelRequested = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL featureLevelSupported;

	HRESULT hr = D3D11CreateDevice(
		nullptr, // Use default adapter
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr, // No software device
		0, // No flags
		&featureLevelRequested, // Feature level requested
		1, // Number of feature levels
		D3D11_SDK_VERSION, // SDK version
		&device, // Device out
		&featureLevelSupported, // Supported feature level out
		&context // Context out
	);

	if (FAILED(hr)) {
		std::cerr << "Failed to create Direct3D 11 device. HRESULT: " << std::hex << hr << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	ComPtr<IDXGIDevice> dxgiDevice;
	device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(dxgiDevice.GetAddressOf()));

	ComPtr<IDXGIAdapter> dxgiAdapter;
	dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf());

	DXGI_ADAPTER_DESC adapterDesc;
	dxgiAdapter->GetDesc(&adapterDesc);

	std::wcout << L"Using adapter: " << adapterDesc.Description << std::endl;

	bool running = true;
	SDL_Event event;
	while (running)
	{
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}

		SDL_Delay(16); // Simulate a frame delay (about 60 FPS)	
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}