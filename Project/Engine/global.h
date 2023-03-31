#pragma once

#include <typeinfo>
#include <vector>
#include <list>
#include <map>
#include <string>

using std::vector;
using std::list;
using std::map;
using std::make_pair;
using std::wstring;
using std::string;

#include <assert.h>

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

typedef XMFLOAT2 Vec2;
typedef XMFLOAT3 Vec3;
typedef XMFLOAT4 Vec4;

#include "define.h"
#include "func.h"
#include "struct.h"
#include "CSingleton.h"