#include "Renderer.h"
#include <iostream>
#include <SDL2/SDL_syswm.h>

Renderer::Renderer(SDL_Window* window, int frameBufferWidth, int frameBufferHeight)
	: window(window), frameBufferWidth(frameBufferWidth), frameBufferHeight(frameBufferHeight) {
	CreateDevice();
	CreateSwapChain();
	RetrieveBackBuffer();
}

void Renderer::BeginRenderPass()
{
	const float clearColor[4] = { 0.682f, 0.847f, 1.0f, 1.0f }; // Clear to light blue
	context->ClearRenderTargetView(backBufferRenderTargetView.Get(), clearColor);

	const CD3D11_VIEWPORT viewport(0.0f, 0.0f, frameBufferWidth, frameBufferHeight);
	context->RSSetViewports(1, &viewport);

	ID3D11RenderTargetView* renderTargets[] = { backBufferRenderTargetView.Get() };
	context->OMSetRenderTargets(1, renderTargets, nullptr); // Set the render target view
}

void Renderer::EndRenderPass()
{
	swapChain->Present(1, 0); // Present the swap chain with vsync (1) and no flags (0)
}

void Renderer::CreateDevice()
{
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
	}
}

void Renderer::CreateSwapChain()
{
	ComPtr<IDXGIFactory2> factory;
	// Same as: HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory2), (void**)&factory);
	HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&factory));

	if (FAILED(hr)) {
		std::cerr << "Failed to create DXGI factory. HRESULT: " << std::hex << hr << std::endl;
		return;
	}

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.BufferCount = 2; // Double buffering
	swapChainDesc.Width = frameBufferWidth; // Width of the window
	swapChainDesc.Height = frameBufferHeight; // Height of the window
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Color format
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Usage
	swapChainDesc.SampleDesc.Count = 1; // No multi-sampling
	swapChainDesc.SampleDesc.Quality = 0; // No multi-sampling quality
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // Swap effect

	// Get information about the window for the swap chain
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version); // Initialize the version field

	if (SDL_GetWindowWMInfo(window, &wmInfo) != SDL_TRUE) {
		std::cerr << "Failed to get window information. SDL_Error: " << SDL_GetError() << std::endl;
		return;
	}

	HWND hwnd = wmInfo.info.win.window; // Get the window handle

	hr = factory->CreateSwapChainForHwnd(
		device.Get(), // Device
		hwnd, // Window handle
		&swapChainDesc, // Swap chain description
		nullptr, // No fullscreen description
		nullptr, // No restrict to output
		&swapChain // Swap chain out
	);

	if (FAILED(hr)) {
		std::cerr << "Failed to create swap chain. HRESULT: " << std::hex << hr << std::endl;
		return;
	}
}

void Renderer::RetrieveBackBuffer()
{
	HRESULT hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
	if (FAILED(hr)) {
		std::cerr << "Failed to retrieve back buffer. HRESULT: " << std::hex << hr << std::endl;
		return;
	}

	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Same format as swap chain
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D; // 2D texture
	hr = device->CreateRenderTargetView(backBuffer.Get(), &rtvDesc, &backBufferRenderTargetView);

	if (FAILED(hr)) {
		std::cerr << "Failed to create render target view. HRESULT: " << std::hex << hr << std::endl;
		return;
	}
}
