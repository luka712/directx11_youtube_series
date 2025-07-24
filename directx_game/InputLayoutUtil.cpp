#include "InputLayoutUtil.h"

ComPtr<ID3D11InputLayout> InputLayoutUtil::CreatePositionColorInputLayout(
	ComPtr<ID3D11Device> device,
	ComPtr<ID3D10Blob> vertexShaderBlob, 
	const std::string debugName)
{
	ComPtr<ID3D11InputLayout> inputLayout;

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 3 * sizeof(float), D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	HRESULT hresult = device->CreateInputLayout(
		layout,
		2,
		vertexShaderBlob->GetBufferPointer(),
		vertexShaderBlob->GetBufferSize(),
		&inputLayout
	);

	if (FAILED(hresult)) {
		std::cerr << "Failed to create input layout: " << std::endl;
		return nullptr;
	}

	if (debugName != "") {
		inputLayout->SetPrivateData(
			WKPDID_D3DDebugObjectName,
			static_cast<UINT>(debugName.size()),
			debugName.c_str()
		);
	}

	return inputLayout;
}
