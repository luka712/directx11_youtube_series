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
	VertexBuffer(const Renderer& renderer, const std::vector<T> data, const std::string& debugName)
		: renderer(renderer), buffer(nullptr)
	{
		buffer = BufferUtil::CreateVertexBuffer<T>(
			renderer.GetDevice(),
			data,
			debugName
		);
	}
private:
	const Renderer& renderer;

	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11Buffer> buffer;
};

