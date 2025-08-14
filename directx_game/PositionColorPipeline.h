#pragma once

#include "Renderer.h"
#include "VertexBuffer.h"
#include "PositionColorVertex.h"
#include "IndexBuffer.h"

class PositionColorPipeline
{
public:
	PositionColorPipeline(Renderer& renderer);

	void Render(const VertexBuffer<PositionColorVertex> &vertexBuffer);

	void Render(const VertexBuffer<PositionColorVertex>& vertexBuffer, const IndexBuffer& indexBuffer);


private:
	Renderer& renderer;

	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;

	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3D11PixelShader> pixelShader;
	ComPtr<ID3D11InputLayout> inputLayout;

	void CreateShaders();
};

