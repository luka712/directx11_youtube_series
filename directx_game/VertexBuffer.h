#pragma once

#include "Renderer.h"
#include <vector>
#include "BufferUtil.h"

template<typename T>
class VertexBuffer
{
public:
	VertexBuffer(Renderer& renderer, std::vector<T>& data, std::string debugName = "") {
		buffer = BufferUtil::CreateVertexBuffer<T>(renderer.GetDevice(), data, debugName);
	}

	ComPtr<ID3D11Buffer> GetBuffer() {
		return buffer;
	}


private:
	ComPtr<ID3D11Buffer> buffer;
};
