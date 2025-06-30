#include "TriangleTestPipeline.h"
#include <iostream>
#include <d3dcompiler.h>
#include "BlobUtil.h"
#include "ShaderUtil.h"

TriangleTestPipeline::TriangleTestPipeline(Renderer& renderer)
	: renderer(renderer)
{
	device = renderer.GetDevice();
	deviceContext = renderer.GetDeviceContext();

	createShaders();
}

void TriangleTestPipeline::render()
{	
	deviceContext->VSSetShader(vertexShader.Get(), nullptr, 0);
	deviceContext->PSSetShader(pixelShader.Get(), nullptr, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->Draw(3, 0);
}

void TriangleTestPipeline::createShaders()
{
	ComPtr<ID3D10Blob> vertexShaderBlob = BlobUtil::Create("triangle_vs.hlsl", "vs_5_0");
	ComPtr<ID3D10Blob> pixelShaderBlob = BlobUtil::Create("triangle_ps.hlsl", "ps_5_0");
	
	vertexShader = ShaderUtil::CreateVertexShader(device, vertexShaderBlob);
	pixelShader = ShaderUtil::CreatePixelShader(device, pixelShaderBlob);

}
