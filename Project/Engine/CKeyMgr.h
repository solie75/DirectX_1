#pragma once



enum class KEY
{
	UP,		// VK_UP
	DOWN,
	LEFT,
	RIGHT,

	SPACE,
	ENTER,
	ESC,
	LALT,
	LCTRL,
	LSHIFT,
	TAB,

	LBTN,
	RBTN,

	Q,
	W,
	E,
	R,

	A,
	S,
	D,
	F,

	Z,
	X,
	C,
	V,

	_0,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,

	END,
};

enum class KEY_STATE
{
	TAP,
	PRESSED,
	RELEASE,
	NONE,
};

struct tKeyInfo
{
	KEY			key;
	KEY_STATE	state;
	bool		bPrev; // 지난 프레임이 눌렸는지에 대한 여부
};

class CKeyMgr :
    public CSingleton<CKeyMgr>
{
	SINGLE(CKeyMgr)
private:
	vector<tKeyInfo>	m_vecKey;
	Vec2				m_vMousePos;

public:
	void KeyMgrInit();
	void KeyMgrTick();

public:
	KEY_STATE GetKeyState(KEY _key) { return m_vecKey[(UINT)_key].state; }
	Vec2 GetMousePos() { return m_vMousePos; }
};

