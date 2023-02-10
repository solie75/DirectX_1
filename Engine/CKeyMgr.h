#pragma once

int g_arrVK[(UINT)KEY::END]
=
{
	 VK_UP,
	 VK_DOWN,
	 VK_LEFT,
	 VK_RIGHT,

	 VK_SPACE,
	 VK_RETURN,
	 VK_ESCAPE,
	 VK_LMENU,
	 VK_LCONTROL,
	 VK_LSHIFT,
	 VK_TAB,

	 VK_LBUTTON,
	 VK_RBUTTON,

	 'Q',
	 'W',
	 'E',
	 'R',

	 'A',
	 'S',
	 'D',
	 'F',

	 '0',
	 '1',
	 '2',
	 '3',
	 '4',
	 '5',
	 '6',
	 '7',
	 '8',
	 '9',
};

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
private:
	vector<tKeyInfo>	m_vecKey;
	Vec2				m_vMousePos;

public:
	void KeyMgrInit();
	void KeyMgrTick();

public:
	KEY_STATE GetKeyState(KEY _key) { return m_vecKey[(UINT)_key].state; }
	Vec2 GetMousePos() { return m_vMousePos; }
public:
	CKeyMgr();
	~CKeyMgr();
};

