#pragma once
#define DIRECTINPUT_VERSION 0x0800//DirectInputのバージョン指定
#include<dinput.h>
#include"WindowAPI.h"
#include<wrl.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

class MouseInput
{
private:
	//Microsoft::WRL::省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devMouse;
	DIMOUSESTATE2 mouseState = {};
	DIMOUSESTATE2 oldMouseState = {};
	WinApp *win;

public:
	//引数付きコンストラクタ(主にこっちを使う)
	MouseInput(WinApp *win);

	//コンストラクタ
	MouseInput();

	/// <summary>
	/// 初期化処理
	/// </summary>
	bool Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Updete();

	/// <summary>
	/// キーの左ボタン押下をチェック
	/// </summary>
	/// <returns>押されているか</returns>
	bool isMouseLeft();

	/// <summary>
	/// キーの中ボタン押下をチェック
	/// </summary>
	/// <returns>押されているか</returns>
	bool isMouseMiddle();

	/// <summary>
	/// キーの左ボタントリガーをチェック
	/// </summary>
	/// <returns>トリガー判定</returns>
	bool isTriggerMouseLeft();

	/// <summary>
	/// キーの中ボタントリガーをチェック
	/// </summary>
	/// <returns>トリガー判定</returns>
	bool isTriggerMouseMiddle();

};

