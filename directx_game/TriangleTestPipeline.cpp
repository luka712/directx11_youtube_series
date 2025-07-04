#include "TriangleTestPipeline.h"
#include <string>
#include <iostream>
#include "BlobUtil.h"
#include "ShaderUtil.h"

TriangleTestPipeline::TriangleTestPipeline(Renderer& renderer)
	: renderer(renderer)
{
	device = renderer.GetDevice();
	context = renderer.GetContext();
	CreateShaders();
}

void TriangleTestPipeline::Render()
{
	context->VSSetShader(vertexShader.Get(), nullptr, 0);
	context->PSSetShader(pixelShader.Get(), nullptr, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->Draw(3, 0);
}

void TriangleTestPipeline::CreateShaders()
{
	ComPtr<ID3D10Blob> vertexShaderBlob = BlobUtil::Create("triangle_vs.hlsl", "vs_5_0");
	ComPtr<ID3D10Blob> pixelShaderBlob = BlobUtil::Create("triangle_ps.hlsl", "ps_5_0");

	vertexShader = ShaderUtil::CreateVertexShader(device, vertexShaderBlob);
	pixelShader = ShaderUtil::CreatePixelShader(device, pixelShaderBlob);
}
