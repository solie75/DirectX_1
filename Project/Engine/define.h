#pragma once

#define DEVICE CDevice::GetInst()->GetCDevice()
#define CONTEXT CDevice::GetInst()->GetCContext()

#define KEY_TAB(key) CKeyMgr::GetInst()->GetKeyState(key)==KEY_STATE::TAP
#define KEY_RELEASE(key) CKeyMgr::GetInst()->GetKeyState(key)==KEY_STATE::RELEASE
#define KEY_PRESSED(key) CKeyMgr::GetInst()->GetKeyState(key)==KEY_STATE::PRESSED

#define DT CTimeMgr::GetInst()->GetDeltaTime()

#define CLONE(type) public : virtual type* Clone(){return new type(*this);}

#define MAX_LAYER 32

#define SINGLE(type) private: type(); ~type(); friend class CSingleton<type>

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
