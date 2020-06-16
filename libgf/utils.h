#pragma once

#include "commons.h"

class utils
{
public:
	static btTransform btTransform_from_XMFLOAT4X4(const DirectX::XMFLOAT4X4 &matrix);
	static void XMFLOAT4X4_to_btTransform(btTransform *dest, const DirectX::XMFLOAT4X4 &matrix);
	static DirectX::XMFLOAT4X4 XMFLOAT4X4_from_btTransform(const btTransform &transform);
	static void btTransform_to_XMFLOAT4X4(DirectX::XMFLOAT4X4A *dest, const btTransform &transform);
};
