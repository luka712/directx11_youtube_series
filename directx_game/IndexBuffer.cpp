#include "IndexBuffer.h"
#include "BufferUtil.h"

IndexBuffer::IndexBuffer(const Renderer& renderer, const std::vector<unsigned int> data, const std::string& debugName)
	: renderer(renderer), buffer(nullptr), indexCount(data.size())
{
	buffer = BufferUtil::CreateIndexBuffer(
		renderer.GetDevice(),
		data,
		debugName
	);
}
