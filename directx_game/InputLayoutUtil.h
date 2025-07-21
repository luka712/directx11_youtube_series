#pragma once

#include <wrl/client.h>
#include <d3d11.h>
#include <string>

using namespace Microsoft::WRL;

class InputLayoutUtil
{
public:
	static ComPtr<ID3D11InputLayout> CreatePositionColorInputLayout(
		ComPtr<ID3D11Device> device,
		ComPtr<ID3D10Blob> vertexShaderBlob,
		const std::string& debugName = "Position_Color_InputLayout"
	);
};

