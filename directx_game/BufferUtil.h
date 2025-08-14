#pragma once

#include <wrl/client.h>
#include <d3dcompiler.h>
#include <d3d11.h>
#include <string>
#include <vector>
#include <iostream>

using namespace Microsoft::WRL;

class BufferUtil
{
public:
	template <typename T>
	static ComPtr<ID3D11Buffer> CreateVertexBuffer(
		ComPtr<ID3D11Device> device,
		const std::vector<T> data,
		const std::string& debugName)
	{
		ComPtr<ID3D11Buffer> buffer;

		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		bufferDesc.ByteWidth = static_cast<UINT>(sizeof(T) * data.size());
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = data.data();

		HRESULT hresult = device->CreateBuffer(&bufferDesc, &initData, &buffer);
		if (FAILED(hresult)) {
			std::cerr << "Failed to create vertex buffer: " << std::dec << std::endl;
			return nullptr;
		}

		if (debugName != "") {
			buffer->SetPrivateData(
				WKPDID_D3DDebugObjectName,
				static_cast<UINT>(debugName.size()),
				debugName.c_str()
			);
		}

		return buffer;
	}

	static ComPtr<ID3D11Buffer> CreateIndexBuffer(
		ComPtr<ID3D11Device> device,
		const std::vector<unsigned int> data,
		const std::string& debugName);
};

