#include "MouseInput.h"
#include <cassert>

MouseInput::MouseInput(WinApp *win)
{
	this->win = win;
}

MouseInput::MouseInput()
{
}

bool MouseInput::Initialize()
{
	HRESULT result = S_FALSE;

	//DirectXInputオブジェクトの作成
	result = DirectInput8Create
	(
		win->GetHInstance(),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void **)&dinput,
		nullptr
	);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	//マウスデバイスの生成
	result = dinput->CreateDevice(GUID_SysMouse, &devMouse, NULL);
	if (FAILED(result))
	{
		assert(0);
		return result;
	}

	//入力データ形式のセット
	result = devMouse->SetDataFormat(&c_dfDIMouse2); // 標準形式
	if (FAILED(result))
	{
		assert(0);
		return result;
	}

	// 排他制御レベルのセット
	result = devMouse->SetCooperativeLevel(win->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	if (FAILED(result))
	{
		assert(0);
		return result;
	}

	return false;
}

void MouseInput::Updete()
{
	HRESULT result;

	result = devMouse->Acquire();//マウス動作開始

	//前回の入力を保存
	oldMouseState = mouseState;

	//マウスの入力
	result = devMouse->GetDeviceState(sizeof(mouseState), &mouseState);

}

bool MouseInput::isMouseLeft()
{
	// 0でなければ押している
	if (mouseState.rgbButtons[0]) {
		return true;
	}

	// 押していない
	return false;
}

bool MouseInput::isMouseMiddle()
{
	// 0でなければ押している
	if (mouseState.rgbButtons[2]) {
		return true;
	}

	// 押していない
	return false;
}

bool MouseInput::isTriggerMouseLeft()
{
	// 前回が0で、今回が0でなければトリガー
	if (!oldMouseState.rgbButtons[0] && mouseState.rgbButtons[0]) {
		return true;
	}

	// トリガーでない
	return false;
}

bool MouseInput::isTriggerMouseMiddle()
{
	// 前回が0で、今回が0でなければトリガー
	if (!oldMouseState.rgbButtons[2] && mouseState.rgbButtons[2]) {
		return true;
	}

	// トリガーでない
	return false;
}
