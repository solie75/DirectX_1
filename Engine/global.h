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
// Math 와 PackedVector 는 헤더 안에 구조체와 인라인으로 이미 선언되어 있어 따로 연결할 필요가 없다.

#include <SimpleMath.h>


typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;
