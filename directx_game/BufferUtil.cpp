#include "BufferUtil.h"

ComPtr<ID3D11Buffer> BufferUtil::CreateIndexBuffer(
	ComPtr<ID3D11Device> device,
	const std::vector<unsigned int> data,
	const std::string& debugName)
{
	ComPtr<ID3D11Buffer> buffer;

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(unsigned int) * data.size());
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = data.data();

	HRESULT hresult = device->CreateBuffer(&bufferDesc, &initData, &buffer);
	if (FAILED(hresult)) {
		std::cerr << "Failed to create index buffer: " << std::dec << std::endl;
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