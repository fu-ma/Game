#pragma once
#define DIRECTINPUT_VERSION 0x0800//DirectInput�̃o�[�W�����w��
#include<dinput.h>
#include"WindowAPI.h"
#include<wrl.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

class KeyInput
{
private:
	//Microsoft::WRL::�ȗ�
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//

	//�����o�ϐ�
	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devkeyboard;
	BYTE keys[256];
	BYTE oldkeys[256];
	WinApp *win;
	//
public:

	//�����t���R���X�g���N�^(��ɂ��������g��)
	KeyInput(WinApp *win);

	//�R���X�g���N�^
	KeyInput();

	/// <summary>
	/// ����������
	/// </summary>
	bool Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Updete();

	/// <summary>
	/// �L�[����
	/// </summary>
	/// <param name="keyNum"></param>
	/// <returns>������Ă��邩</returns>
	bool KeyInput::isKey(BYTE keyNum);

	/// <summary>
	/// �g���K�[����
	/// </summary>
	/// <param name="keyNum"></param>
	/// <returns>�g���K�[��</returns>
	bool KeyInput::isKeyTrigger(BYTE keyNum);

	//dinput��Getter
	const ComPtr<IDirectInput8> dinputGetter() { return dinput; }
};