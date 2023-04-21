#pragma once

struct tVertex
{
	Vec3 vPosition;
	Vec4 vColor;
	Vec2 vUV;
};

typedef tVertex Vtx;

struct tMaterialConst
{
	int arrInt[4];
	float arrFloat[4];
	Vec2 arrV2[4];
	Vec4 arrV4[4];
	Matrix arrMatrix[4];
};

struct tTransform
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProjection;
};

extern tTransform g_transform;