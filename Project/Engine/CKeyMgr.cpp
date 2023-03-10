#include "pch.h"
#include "CKeyMgr.h"
#include "CEngine.h"

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

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}


void CKeyMgr::KeyMgrInit()
{
	for (int i = 0; i < (int)KEY::END; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ (KEY)i, KEY_STATE::NONE, false});
	}
}

void CKeyMgr::KeyMgrTick()
{
	if (GetFocus())
	{
		for (size_t i = 0; i < m_vecKey.size(); ++i)
		{
			//ȣ������� ���� �����̸� true
			if (GetAsyncKeyState(g_arrVK[(UINT)m_vecKey[i].key] & 0x8000)) 
			{
				// ���� �����ӿ� �ȴ��� ���
				if (false == m_vecKey[i].bPrev)
				{
					m_vecKey[i].state = KEY_STATE::TAP;
					m_vecKey[i].bPrev = true;
				}
				// ���� �����ӿ� ���� ���
				else
				{
					m_vecKey[i].state = KEY_STATE::PRESSED;
				}
			}
			// ȣ�� ������ ������ ���� ���
			else
			{
				// ���� �����ӿ� �� ���� ���
				if (false == m_vecKey[i].bPrev)
				{
					m_vecKey[i].state = KEY_STATE::NONE;
				}
				// ���� �����ӿ� ���� ���
				else
				{
					m_vecKey[i].state = KEY_STATE::RELEASE;
					m_vecKey[i].bPrev = false;
				}
			}
		}

		// Mouse ��ġ ����
		POINT ptMousePos = {};
		GetCursorPos(&ptMousePos);
		ScreenToClient(CEngine::GetInst()->GetMainWnd(), &ptMousePos);
		m_vMousePos = Vec2((float)ptMousePos.x, (float)ptMousePos.y);
	}
	// �����찡 ��Ŀ�� ���°� �ƴ� ���
	else
	{ // ���ڱ� �����쿡�� ��Ŀ���� ���� ��쿡�� Pressed -> Release �Ǵ� Release -> NONE �������� �Ͼ�� �ڵ� ������ ���� ������ �����Ѵ�.
		for (size_t i = 0; i < m_vecKey.size(); ++i)
		{
			if (KEY_STATE::TAP == m_vecKey[i].state || KEY_STATE::PRESSED == m_vecKey[i].state)
			{
				m_vecKey[i].state = KEY_STATE::RELEASE;
				m_vecKey[i].bPrev = false;
			}
			else if(KEY_STATE::PRESSED == m_vecKey[i].state)
			{
				m_vecKey[i].state = KEY_STATE::NONE;
			}
		}
	}
}
