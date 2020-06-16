#include "utils.h"

btTransform utils::btTransform_from_XMFLOAT4X4(const DirectX::XMFLOAT4X4 &matrix)
{
	btMatrix3x3	bulletRotation;
	btVector3	bulletTranslation;

	bulletRotation[0][0] = matrix.m[0][0];
	bulletRotation[1][0] = matrix.m[0][1];
	bulletRotation[2][0] = matrix.m[0][2];
	bulletRotation[0][1] = matrix.m[1][0];
	bulletRotation[1][1] = matrix.m[1][1];
	bulletRotation[2][1] = matrix.m[1][2];
	bulletRotation[0][2] = matrix.m[2][0];
	bulletRotation[1][2] = matrix.m[2][1];
	bulletRotation[2][2] = matrix.m[2][2];

	bulletTranslation[0] = matrix.m[3][0];
	bulletTranslation[1] = matrix.m[3][1];
	bulletTranslation[2] = matrix.m[3][2];

	return btTransform(bulletRotation, bulletTranslation);
}

void utils::XMFLOAT4X4_to_btTransform(btTransform *dest, const DirectX::XMFLOAT4X4 &matrix)
{
	btMatrix3x3	bulletRotation;
	btVector3	bulletTranslation;

	bulletRotation[0][0] = matrix.m[0][0];
	bulletRotation[1][0] = matrix.m[0][1];
	bulletRotation[2][0] = matrix.m[0][2];
	bulletRotation[0][1] = matrix.m[1][0];
	bulletRotation[1][1] = matrix.m[1][1];
	bulletRotation[2][1] = matrix.m[1][2];
	bulletRotation[0][2] = matrix.m[2][0];
	bulletRotation[1][2] = matrix.m[2][1];
	bulletRotation[2][2] = matrix.m[2][2];

	bulletTranslation[0] = matrix.m[3][0];
	bulletTranslation[1] = matrix.m[3][1];
	bulletTranslation[2] = matrix.m[3][2];

	*dest = btTransform(bulletRotation, bulletTranslation);
}

DirectX::XMFLOAT4X4 utils::XMFLOAT4X4_from_btTransform(const btTransform &transform)
{
	DirectX::XMFLOAT4X4 result;
	DirectX::XMStoreFloat4x4(&result, DirectX::XMMatrixIdentity());

	const btMatrix3x3	bulletRotation = transform.getBasis();
	const btVector3		bulletTranslation = transform.getOrigin();

	result.m[0][0] = bulletRotation[0][0];
	result.m[0][1] = bulletRotation[1][0];
	result.m[0][2] = bulletRotation[2][0];
	result.m[1][0] = bulletRotation[0][1];
	result.m[1][1] = bulletRotation[1][1];
	result.m[1][2] = bulletRotation[2][1];
	result.m[2][0] = bulletRotation[0][2];
	result.m[2][1] = bulletRotation[1][2];
	result.m[2][2] = bulletRotation[2][2];

	result.m[3][0] = bulletTranslation[0];
	result.m[3][1] = bulletTranslation[1];
	result.m[3][2] = bulletTranslation[2];

	return result;
}

void utils::btTransform_to_XMFLOAT4X4(DirectX::XMFLOAT4X4A *dest, const btTransform &transform)
{
	DirectX::XMStoreFloat4x4(dest, DirectX::XMMatrixIdentity());

	const btMatrix3x3	bulletRotation = transform.getBasis();
	const btVector3		bulletTranslation = transform.getOrigin();

	dest->m[0][0] = bulletRotation[0][0];
	dest->m[0][1] = bulletRotation[1][0];
	dest->m[0][2] = bulletRotation[2][0];
	dest->m[1][0] = bulletRotation[0][1];
	dest->m[1][1] = bulletRotation[1][1];
	dest->m[1][2] = bulletRotation[2][1];
	dest->m[2][0] = bulletRotation[0][2];
	dest->m[2][1] = bulletRotation[1][2];
	dest->m[2][2] = bulletRotation[2][2];

	dest->m[3][0] = bulletTranslation[0];
	dest->m[3][1] = bulletTranslation[1];
	dest->m[3][2] = bulletTranslation[2];
}
