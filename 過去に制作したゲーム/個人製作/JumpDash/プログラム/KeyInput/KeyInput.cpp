#include "KeyInput.h"
#include <cassert>

KeyInput::KeyInput(WinApp *win):win(win),dinput(nullptr), devkeyboard(nullptr)
{
	//キー判定保存用変数の初期化
	for (int i = 0; i < 256; i++)
	{
		keys[i] = 0;
		oldkeys[i] = 0;
	}
}

KeyInput::KeyInput()
{
}

bool KeyInput::Initialize()
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

	//キーボードデバイスの作成
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	//入力データ形式のセット
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard);//標準形式
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	//排他制御レベルのセット
	result = devkeyboard->SetCooperativeLevel
	(
		win->GetHwnd(),
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY
	);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	return true;
}

void KeyInput::Updete()
{
	HRESULT result;

	//キーボード情報の取得開始
	result = devkeyboard->Acquire();

	//前回のキー入力を保存
	memcpy(oldkeys, keys, sizeof(keys));

	//キーの入力
	result = devkeyboard->GetDeviceState(sizeof(keys), keys);
}

bool KeyInput::isKey(BYTE keyNum)
{
	//異常な引数を検出
	assert(0 <= keyNum && keyNum <= 256);

	//押してる
	if (keys[keyNum])
	{
		return true;
	}

	//押してない
	return false;
}

bool KeyInput::isKeyTrigger(BYTE keyNum)
{
	//異常な引数を検出
	assert(0 <= keyNum && keyNum <= 256);

	//トリガー
	if (!oldkeys[keyNum] && keys[keyNum])
	{
		return true;
	}

	//押してない
	return false;
}