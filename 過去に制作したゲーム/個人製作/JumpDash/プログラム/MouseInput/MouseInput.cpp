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

	//DirectXInput�I�u�W�F�N�g�̍쐬
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

	//�}�E�X�f�o�C�X�̐���
	result = dinput->CreateDevice(GUID_SysMouse, &devMouse, NULL);
	if (FAILED(result))
	{
		assert(0);
		return result;
	}

	//���̓f�[�^�`���̃Z�b�g
	result = devMouse->SetDataFormat(&c_dfDIMouse2); // �W���`��
	if (FAILED(result))
	{
		assert(0);
		return result;
	}

	// �r�����䃌�x���̃Z�b�g
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

	result = devMouse->Acquire();//�}�E�X����J�n

	//�O��̓��͂�ۑ�
	oldMouseState = mouseState;

	//�}�E�X�̓���
	result = devMouse->GetDeviceState(sizeof(mouseState), &mouseState);

}

bool MouseInput::isMouseLeft()
{
	// 0�łȂ���Ή����Ă���
	if (mouseState.rgbButtons[0]) {
		return true;
	}

	// �����Ă��Ȃ�
	return false;
}

bool MouseInput::isMouseMiddle()
{
	// 0�łȂ���Ή����Ă���
	if (mouseState.rgbButtons[2]) {
		return true;
	}

	// �����Ă��Ȃ�
	return false;
}

bool MouseInput::isTriggerMouseLeft()
{
	// �O��0�ŁA����0�łȂ���΃g���K�[
	if (!oldMouseState.rgbButtons[0] && mouseState.rgbButtons[0]) {
		return true;
	}

	// �g���K�[�łȂ�
	return false;
}

bool MouseInput::isTriggerMouseMiddle()
{
	// �O��0�ŁA����0�łȂ���΃g���K�[
	if (!oldMouseState.rgbButtons[2] && mouseState.rgbButtons[2]) {
		return true;
	}

	// �g���K�[�łȂ�
	return false;
}
