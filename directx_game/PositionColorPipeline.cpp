#include "PositionColorPipeline.h"
#include <string>
#include <iostream>
#include "BlobUtil.h"
#include "ShaderUtil.h"
#include "InputLayoutUtil.h"

PositionColorPipeline::PositionColorPipeline(Renderer& renderer)
	: renderer(renderer)
{
	device = renderer.GetDevice();
	context = renderer.GetContext();
	CreateShaders();
}

void PositionColorPipeline::Render(VertexBuffer<PositionColorVertex>& vertexBuffer)
{
	context->IASetInputLayout(inputLayout.Get());
	UINT32 stride = sizeof(PositionColorVertex);
	UINT32 offset = 0;
	context->IASetVertexBuffers(0, 1, vertexBuffer.GetBuffer().GetAddressOf(), &stride, &offset);
	context->VSSetShader(vertexShader.Get(), nullptr, 0);
	context->PSSetShader(pixelShader.Get(), nullptr, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->Draw(vertexBuffer.GetVertexCount(), 0);
}

void PositionColorPipeline::CreateShaders()
{
	ComPtr<ID3D10Blob> vertexShaderBlob = BlobUtil::Create("position_color_vs.hlsl", "vs_5_0");
	ComPtr<ID3D10Blob> pixelShaderBlob = BlobUtil::Create("position_color_ps.hlsl", "ps_5_0");

	inputLayout = InputLayoutUtil::CreatePositionColorInputLayout(device, vertexShaderBlob);

	vertexShader = ShaderUtil::CreateVertexShader(device, vertexShaderBlob);
	pixelShader = ShaderUtil::CreatePixelShader(device, pixelShaderBlob);
}
