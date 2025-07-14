#pragma once

#include <wrl/client.h>
#include <d3d11.h>
#include <string>
#include <iostream>
#include <vector>
#include <d3dcommon.h>

using namespace Microsoft::WRL;

class BufferUtil
{
public:

	template<typename T>
	static ComPtr<ID3D11Buffer> CreateVertexBuffer(
		ComPtr<ID3D11Device> device,
		const std::vector<T>& data,
		const std::string& debugName
	)
	{
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.ByteWidth = static_cast<UINT>(data.size() * sizeof(T));
		bufferDesc.StructureByteStride = 0;
		bufferDesc.CPUAccessFlags = 0; // No CPU access needed for vertex buffer
		bufferDesc.MiscFlags = 0; // No special flags

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = data.data();

		ComPtr<ID3D11Buffer> buffer;
		HRESULT hr = device->CreateBuffer(&bufferDesc, &initData, &buffer);

		if (FAILED(hr))
		{
			std::cerr << "Failed to create vertex buffer" << std::endl;
			return nullptr;
		}

		if (debugName != "") {
			buffer->SetPrivateData(WKPDID_D3DDebugObjectName, debugName.length(), debugName.c_str());
		}

		return buffer;
	}
};

