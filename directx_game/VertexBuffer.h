#pragma once

#include "Renderer.h"
#include <vector>
#include <string>
#include <iostream>
#include "BufferUtil.h"

template <typename T>
class VertexBuffer
{
public:
	VertexBuffer(
		const Renderer& renderer, 
		const std::vector<T> data, 
		const unsigned int vertexCount,
		const std::string& debugName)
		: renderer(renderer), buffer(nullptr), vertexCount(vertexCount)
	{
		buffer = BufferUtil::CreateVertexBuffer<T>(
			renderer.GetDevice(),
			data,
			debugName
		);
	}

	ComPtr<ID3D11Buffer> GetBuffer() const
	{
		return buffer;
	}

	unsigned int GetVertexCount() const
	{
		return vertexCount;
	}

private:
	const Renderer& renderer;

	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11Buffer> buffer;
	unsigned int vertexCount;
};

