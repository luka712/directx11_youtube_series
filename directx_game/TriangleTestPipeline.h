#pragma once

#include "Renderer.h"

class TriangleTestPipeline
{
public:
	TriangleTestPipeline(Renderer& renderer);

	void render();

private:
	Renderer& renderer;

	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> deviceContext;

	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3D11PixelShader> pixelShader;

	void createShaders();
};

