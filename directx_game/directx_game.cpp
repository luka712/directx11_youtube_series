#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <wrl/client.h>

#include <dxgi.h>
#pragma comment(lib, "dxgi.lib")

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
    }

	SDL_Window* window = SDL_CreateWindow("DirectX Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

	if (!window) {
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;

	D3D_FEATURE_LEVEL featureLevelRequested = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL featureLevelSupported;

	HRESULT hr = D3D11CreateDevice(
		nullptr, // Use default adapter. One could query for adapters if there are multiple GPU's to choose from.
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr, // No software rasterizer
		0, // Default flags
		&featureLevelRequested, // Use default feature levels
		1,
		D3D11_SDK_VERSION,
		&device,
		&featureLevelSupported,
		&deviceContext
	);

	if (FAILED(hr)) {
		std::cerr << "Failed to create DirectX 11 device." << std::hex << hr << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice;
	device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(dxgiDevice.GetAddressOf()));

	Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
	dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf());

	DXGI_ADAPTER_DESC adapterDesc;
	dxgiAdapter->GetDesc(&adapterDesc);

	std::wcout << L"Using adapter: " << adapterDesc.Description << std::endl;
	

	bool running = true;
	SDL_Event event;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}

		// Here you would typically render your DirectX content
		SDL_Delay(16); // Simulate frame delay
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

