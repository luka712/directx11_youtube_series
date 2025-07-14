#include "PositionColorTestPipeline.h"
#include <string>
#include <iostream>
#include "BlobUtil.h"
#include "ShaderUtil.h"
#include "InputLayoutUtil.h"

PositionColorTestPipeline::PositionColorTestPipeline(Renderer& renderer)
	: renderer(renderer)
{
	device = renderer.GetDevice();
	context = renderer.GetContext();
	CreateShaders();
}

void PositionColorTestPipeline::Render(VertexBuffer<PositionColorVertex> vertexBuffer)
{
	context->VSSetShader(vertexShader.Get(), nullptr, 0);
	context->PSSetShader(pixelShader.Get(), nullptr, 0);
	context->IASetInputLayout(inputLayout.Get());

	UINT stride = sizeof(PositionColorVertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, vertexBuffer.GetBuffer().GetAddressOf(), &stride, &offset);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->Draw(3, 0);
}

void PositionColorTestPipeline::CreateShaders()
{
	ComPtr<ID3D10Blob> vertexShaderBlob = BlobUtil::Create("position_color_vs.hlsl", "vs_5_0");
	ComPtr<ID3D10Blob> pixelShaderBlob = BlobUtil::Create("position_color_ps.hlsl", "ps_5_0");

	vertexShader = ShaderUtil::CreateVertexShader(device, vertexShaderBlob);
	pixelShader = ShaderUtil::CreatePixelShader(device, pixelShaderBlob);

	inputLayout = InputLayoutUtil::CreatePositionColorInputLayout(
		device,
		vertexShaderBlob,
		"PositionColorInputLayout"
	);
}
