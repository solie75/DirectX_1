#pragma once

#include <wrl.h>
using namespace Microsoft::WRL;

#include <d3d11.h> // Directx 11's header files
#include <d3dcompiler.h> // shader complie
#include <DirectXMath.h> // Dx Math
#include <DirectXPackedVector.h> // vector that used in directx

using namespace DirectX;
using namespace DirectX::PackedVector;

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler")
// Math �� PackedVector �� ��� �ȿ� ����ü�� �ζ������� �̹� ����Ǿ� �־� ���� ������ �ʿ䰡 ����.

#include <SimpleMath.h>


typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;
