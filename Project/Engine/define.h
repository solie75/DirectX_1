#pragma once

#define DEVICE CDevice::GetInst()->GetCDevice()
#define CONTEXT CDevice::GetInst()->GetCContext()

#define KEY_TAB(key) CKeyMgr::GetInst()->GetKeyState(key)==KEY_STATE::TAP
#define KEY_RELEASE(key) CKeyMgr::GetInst()->GetKeyState(key)==KEY_STATE::RELEASE
#define KEY_PRESSED(key) CKeyMgr::GetInst()->GetKeyState(key)==KEY_STATE::PRESSED

#define DT CTimeMgr::GetInst()->GetDeltaTime()

#define CLONE(type) public : virtual type* Clone(){return new type(*this);}

#define MAX_LAYER 32

#define SINGLE(type) private: type(); ~type(); friend class CSingleton<type>;

enum class COMPONENT_TYPE
{
	// update
	TRANSFORM,
	COLLIDER2D,
	COLLIDER3D,
	ANIMATOR2D,
	ANIMATOR3D,
	LIGHT2D,
	LIGHT3D,
	CAMERA,

	// render
	MESHRENDERING,
	PARICLESYSTEM,
	TILEMAP,
	LANDSCAPE,
	DECAL,

	// custom
	SCRIPT,

	END,
};

enum class RESOURCE_TYPE
{
	MESHDATA,
	MATERIAL,
	PREFAB,

	MESH, // 형태
	TEXTURE, // 이미지
	SOUND,

	GRAPHICS_SHADER,
	COMPUTE_SHADER,

	END,
};

enum TEXTURE_PARAM
{
	TEX_0,
	TEX_1,
	TEX_2,
	TEX_3,
	TEX_4,
	TEX_5,
	TEX_6,
	TEX_7,

	TEX_END,
};

enum SCALAR_PARAM
{
	INT_0,
	INT_1,
	INT_2,
	INT_3,

	FLOAT_0,
	FLOAT_1,
	FLOAT_2,
	FLOAT_3,

	VEC2_0,
	VEC2_1,
	VEC2_2,
	VEC2_3,

	VEC4_0,
	VEC4_1,
	VEC4_2,
	VEC4_3,

	MATRIX_0,
	MATRIX_1,
	MATRIX_2,
	MATRIX_3,
};


enum PIPELINE_STAGE
{
	PS_VERTEX = 0x00,
	PS_HULL = 0x01,
	PS_DOMAIN = 0x02,
	PS_GEOMETRY = 0x04,
	PS_PIXEL = 0x08,

	PS_ALL = PS_VERTEX | PS_HULL | PS_DOMAIN | PS_GEOMETRY | PS_PIXEL,
};

enum class CB_TYPE
{
	TRANSFORM, // b0
	MATERIAL, // b1
	
	END,
};

