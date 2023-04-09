#pragma once
#define DIRECTINPUT_VERSION 0x0800//DirectInputのバージョン指定
#include<dinput.h>
#include"WindowAPI.h"
#include<wrl.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

class KeyInput
{
private:
	//Microsoft::WRL::省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//

	//メンバ変数
	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devkeyboard;
	BYTE keys[256];
	BYTE oldkeys[256];
	WinApp *win;
	//
public:

	//引数付きコンストラクタ(主にこっちを使う)
	KeyInput(WinApp *win);

	//コンストラクタ
	KeyInput();

	/// <summary>
	/// 初期化処理
	/// </summary>
	bool Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Updete();

	/// <summary>
	/// キー判定
	/// </summary>
	/// <param name="keyNum"></param>
	/// <returns>押されているか</returns>
	bool KeyInput::isKey(BYTE keyNum);

	/// <summary>
	/// トリガー判定
	/// </summary>
	/// <param name="keyNum"></param>
	/// <returns>トリガーか</returns>
	bool KeyInput::isKeyTrigger(BYTE keyNum);

	//dinputのGetter
	const ComPtr<IDirectInput8> dinputGetter() { return dinput; }
};