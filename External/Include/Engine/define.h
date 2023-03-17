#pragma once

#define DEVICE CDevice::GetInst()->GetCDevice()
#define CONTEXT CDevice::GetInst()->GetCContext()

#define KEY_TAB(key) CKeyMgr::GetInst()->GetKeyState(key)==KEY_STATE::TAP
#define KEY_RELEASE(key) CKeyMgr::GetInst()->GetKeyState(key)==KEY_STATE::RELEASE
#define KEY_PRESSED(key) CKeyMgr::GetInst()->GetKeyState(key)==KEY_STATE::PRESSED

#define DT CTimeMgr::GetInst()->GetDeltaTime()