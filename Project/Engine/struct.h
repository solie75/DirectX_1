#pragma once

struct Vec3 : public XMFLOAT3
{
	Vec3() noexcept : XMFLOAT3(0.f, 0.f, 0.f) {}
	//XM_CONSTEXPR Vec3(float _x, float _y, float _z) : XMFLOAT3(_x, _y, _z) {}

	// ������
	Vec3(const XMFLOAT3& V) { this->x = V.x; this->y = V.y; this->z = V.z; }
	Vec3(FXMVECTOR V) { XMStoreFloat3(this, V); }
	Vec3(float _x, float _y, float _z) { this->x = _x; this->y = _y; this->z = _z; }

	// XMVECTOR Ÿ�������� ��ȯ ������. 'const'  �� ����� ���� ����ü�� 'XMVECTOR' �� ��ȯ�Ѵ�. ����ü ������ ���� 'XMLoadFloat3' �Լ��� ����Ͽ� 'XMVECTOR' �������� �ε��� ���� �̸� ��ȯ�Ѵ�.
	operator XMVECTOR() const { return XMLoadFloat3(this); }
	// Vec3 ����ü�� XMVECTOR �� ���� �� �� ���� ������.
	Vec3 operator=  (const XMVECTOR& v) { x = v.m128_f32[0]; y = v.m128_f32[1]; z = v.m128_f32[2]; return *this; }

	Vec3 operator += (const Vec3& v)
	{
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&v);
		XMVECTOR x = XMVectorMultiply(v1, v2);
		XMStoreFloat3(this, x);
		return *this;
	}

	Vec3 operator -= (const Vec3& v)
	{
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&v);
		XMVECTOR x = XMVectorSubtract(v1, v2);
		XMStoreFloat3(this, x);
		return *this;
	}

	Vec3 operator += (const Vec3& v)
	{
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&v);
		XMVECTOR x = XMVectorAdd(v1, v2);
		XMStoreFloat3(this, x);
		return *this;
	}
};

struct Matrix : public XMFLOAT4X4
{
	Matrix() noexcept
		: XMFLOAT4X4(
			1.f, 0, 0, 0,
			0, 1.f, 0, 0,
			0, 0, 1.f, 0,
			0, 0, 0, 1.f) {}
	Matrix(XMMATRIX _M) { XMStoreFloat4x4(this, _M); }

	operator XMMATRIX() const { return XMLoadFloat4x4(this); }

	Matrix& operator* (const Matrix& M) {
		XMMATRIX M1 = XMLoadFloat4x4(this);
		XMMATRIX M2 = XMLoadFloat4x4(&M);
		XMMATRIX X = XMMatrixMultiply(M1, M2);
		XMStoreFloat4x4(this, X);
		return *this;
	}

	Matrix& operator*= (const Matrix& M) {
		return operator*(M);
	};

};

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


