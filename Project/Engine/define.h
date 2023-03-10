#pragma once

#define DEVICE CDevice::GetInst()->GetCDevice()
#define CONTEXT CDevice::GetInst()->GetCContext()

#define KEY_TAB(KEY) CKeyMgr::GetInst()->GetKeyState(Key)==KEY_STATE::TAP
#define KEY_RELEASE(KEY) CKeyMgr::GetInst()->GetKeyState(key)==KEY_STATE::RELEASE
#define KEY_PRESSED(KEY) CKeyMgr::GetInst()->GetKeyState(key)==KEY_STATE::PRESSED

#define DT CTimeMgr::GetInst()->GetDeltaTime()