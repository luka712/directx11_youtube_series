#pragma once

#include "Renderer.h"
#include <vector>
#include <string>
#include <iostream>
#include "BufferUtil.h"

class IndexBuffer
{
public:
	IndexBuffer(
		const Renderer& renderer,
		const std::vector<unsigned int> data,
		const std::string& debugName);

	ComPtr<ID3D11Buffer> GetBuffer() const;

	unsigned int GetIndexCount() const;

private:
	const Renderer& renderer;

	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11Buffer> buffer;
	unsigned int indexCount;
};

