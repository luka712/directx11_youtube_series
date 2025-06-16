#pragma once
#include <SDL2/SDL_video.h>

#include <wrl/client.h>
#include <dxgi.h>
#include <dxgi1_3.h>
#include <d3d11.h>

using namespace Microsoft::WRL;

class Renderer
{
public:
	Renderer(SDL_Window* window, int frameBufferWidth, int frameBufferHeight);

	void BeginRenderPass();
	void EndRenderPass();

private:
	SDL_Window* window;
	int frameBufferWidth, frameBufferHeight;
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;
	ComPtr<IDXGISwapChain1> swapChain;
	ComPtr<ID3D11Texture2D> backBuffer;
	ComPtr<ID3D11RenderTargetView> backBufferRenderTargetView;

	void CreateDevice();

	void CreateSwapChain();

	void RetrieveBackBuffer();
};

