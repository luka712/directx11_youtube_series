#pragma once

#include <DirectXMath.h>

struct PositionColorVertex
{
	DirectX::XMFLOAT3 position; // Position in 3D space
	DirectX::XMFLOAT4 color;    // Color (RGBA)

	PositionColorVertex() = default;

	PositionColorVertex(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT4 col)
		: position(pos), color(col) {}
};

