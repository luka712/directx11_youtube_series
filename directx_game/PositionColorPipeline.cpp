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

void PositionColorPipeline::Render(const VertexBuffer<PositionColorVertex>& vertexBuffer)
{
	// BUFFER
	UINT stride = sizeof(PositionColorVertex); // (3 + 4) * sizeof(float)
	UINT offset = 0;
	context->IASetVertexBuffers(
		0,
		1,
		vertexBuffer.GetBuffer().GetAddressOf(),
		&stride, 
		&offset);

	context->IASetInputLayout(inputLayout.Get());
	context->VSSetShader(vertexShader.Get(), nullptr, 0);
	context->PSSetShader(pixelShader.Get(), nullptr, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->Draw(vertexBuffer.GetVertexCount(), 0);
}

void PositionColorPipeline::Render(const VertexBuffer<PositionColorVertex>& vertexBuffer, const IndexBuffer& indexBuffer)
{
	// BUFFER
	UINT stride = sizeof(PositionColorVertex); // (3 + 4) * sizeof(float)
	UINT offset = 0;
	context->IASetVertexBuffers(
		0,
		1,
		vertexBuffer.GetBuffer().GetAddressOf(),
		&stride,
		&offset);

	context->IASetIndexBuffer(
		indexBuffer.GetBuffer().Get(),
		DXGI_FORMAT_R32_UINT, // Assuming 32-bit indices
		0
	);

	context->IASetInputLayout(inputLayout.Get());
	context->VSSetShader(vertexShader.Get(), nullptr, 0);
	context->PSSetShader(pixelShader.Get(), nullptr, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->DrawIndexed(indexBuffer.GetIndexCount(), 0, 0);
}

void PositionColorPipeline::CreateShaders()
{
	ComPtr<ID3D10Blob> vertexShaderBlob = BlobUtil::Create("position_color_vs.hlsl", "vs_5_0");
	ComPtr<ID3D10Blob> pixelShaderBlob = BlobUtil::Create("position_color_ps.hlsl", "ps_5_0");

	vertexShader = ShaderUtil::CreateVertexShader(device, vertexShaderBlob);
	pixelShader = ShaderUtil::CreatePixelShader(device, pixelShaderBlob);

	inputLayout = InputLayoutUtil::CreatePositionColorInputLayout(
		device,
		vertexShaderBlob
	);
}
