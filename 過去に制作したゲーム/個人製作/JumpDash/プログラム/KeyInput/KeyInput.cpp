#include "KeyInput.h"
#include <cassert>

KeyInput::KeyInput(WinApp *win):win(win),dinput(nullptr), devkeyboard(nullptr)
{
	//�L�[����ۑ��p�ϐ��̏�����
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

	//�L�[�{�[�h�f�o�C�X�̍쐬
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	//���̓f�[�^�`���̃Z�b�g
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard);//�W���`��
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	//�r�����䃌�x���̃Z�b�g
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

	//�L�[�{�[�h���̎擾�J�n
	result = devkeyboard->Acquire();

	//�O��̃L�[���͂�ۑ�
	memcpy(oldkeys, keys, sizeof(keys));

	//�L�[�̓���
	result = devkeyboard->GetDeviceState(sizeof(keys), keys);
}

bool KeyInput::isKey(BYTE keyNum)
{
	//�ُ�Ȉ��������o
	assert(0 <= keyNum && keyNum <= 256);

	//�����Ă�
	if (keys[keyNum])
	{
		return true;
	}

	//�����ĂȂ�
	return false;
}

bool KeyInput::isKeyTrigger(BYTE keyNum)
{
	//�ُ�Ȉ��������o
	assert(0 <= keyNum && keyNum <= 256);

	//�g���K�[
	if (!oldkeys[keyNum] && keys[keyNum])
	{
		return true;
	}

	//�����ĂȂ�
	return false;
}