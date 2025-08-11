#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const Renderer& renderer, const std::vector<unsigned int> data, const std::string& debugName) 
	: renderer(renderer), buffer(nullptr), indexCount(data.size())
{
	buffer = BufferUtil::CreateIndexBuffer(
		renderer.GetDevice(),
		data,
		debugName
	);
}

ComPtr<ID3D11Buffer> IndexBuffer::GetBuffer() const
{
	return buffer;
}

unsigned int IndexBuffer::GetIndexCount() const
{
	return indexCount;
}
