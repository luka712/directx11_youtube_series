#include "InputLayoutUtil.h"

ComPtr<ID3D11InputLayout> InputLayoutUtil::CreatePositionColorInputLayout(ComPtr<ID3D11Device> device, ComPtr<ID3D10Blob> vertexShaderBlob, const std::string& debugName)
{

	std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(DirectX::XMFLOAT3), D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	ComPtr<ID3D11InputLayout> inputLayout;

	HRESULT hr = device->CreateInputLayout(
		inputElementDesc.data(),
		inputElementDesc.size(),
		vertexShaderBlob->GetBufferPointer(),
		vertexShaderBlob->GetBufferSize(),
		&inputLayout);

	if (FAILED(hr))
	{
		std::cerr << "Failed to create input layout" << std::endl;
		return nullptr;
	}

	if (!debugName.empty())
	{
		inputLayout->SetPrivateData(WKPDID_D3DDebugObjectName, debugName.length(), debugName.c_str());
	}

	return inputLayout;

}
