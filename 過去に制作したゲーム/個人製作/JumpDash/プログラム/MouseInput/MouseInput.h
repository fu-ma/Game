#pragma once
#define DIRECTINPUT_VERSION 0x0800//DirectInput�̃o�[�W�����w��
#include<dinput.h>
#include"WindowAPI.h"
#include<wrl.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

class MouseInput
{
private:
	//Microsoft::WRL::�ȗ�
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devMouse;
	DIMOUSESTATE2 mouseState = {};
	DIMOUSESTATE2 oldMouseState = {};
	WinApp *win;

public:
	//�����t���R���X�g���N�^(��ɂ��������g��)
	MouseInput(WinApp *win);

	//�R���X�g���N�^
	MouseInput();

	/// <summary>
	/// ����������
	/// </summary>
	bool Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Updete();

	/// <summary>
	/// �L�[�̍��{�^���������`�F�b�N
	/// </summary>
	/// <returns>������Ă��邩</returns>
	bool isMouseLeft();

	/// <summary>
	/// �L�[�̒��{�^���������`�F�b�N
	/// </summary>
	/// <returns>������Ă��邩</returns>
	bool isMouseMiddle();

	/// <summary>
	/// �L�[�̍��{�^���g���K�[���`�F�b�N
	/// </summary>
	/// <returns>�g���K�[����</returns>
	bool isTriggerMouseLeft();

	/// <summary>
	/// �L�[�̒��{�^���g���K�[���`�F�b�N
	/// </summary>
	/// <returns>�g���K�[����</returns>
	bool isTriggerMouseMiddle();

};

