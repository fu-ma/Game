#pragma once
#include"KeyInput.h"
#include"MouseInput.h"
#include"WindowAPI.h"
#include"Object3d.h"
#include"Sprite.h"
#include"Audio.h"
#include"DirectXCommon.h"
#include"ModelObj.h"
#include"Model.h"
#include"ParticleManager.h"
#include"Particle.h"
#include"CollisionPrimitive.h"

class GameScene
{
	enum class GameSceneNo
	{
		Title,
		GamePlay,
		End,
	};
private:
	WNDCLASSEX w{};//�E�B���h�E�N���X�̐ݒ�
	WinApp *winApp = nullptr;
	KeyInput *keyInput = nullptr;
	MouseInput *mouseInput = nullptr;
	DirectXCommon *common = nullptr;

	Audio *audio = nullptr;
	SoundData soundData1;
	SoundData soundData2;
	SoundData soundData3;

	Sprite *spriteA = nullptr;
	Sprite *title = nullptr;
	Sprite *title2 = nullptr;
	Sprite *title3 = nullptr;
	Sprite *backGround = nullptr;
	Sprite *backGround2 = nullptr;
	Sprite *sceneChange = nullptr;
	Sprite *backGround3 = nullptr;
	Sprite *GameOver = nullptr;
	Sprite *GameClear = nullptr;

	Model *model = nullptr;
	Model *model2 = nullptr;
	Model *enemyModel = nullptr;
	ModelObj *player = nullptr;
	ModelObj *enemy[200] = { nullptr };
	ModelObj *enemy2[200] = { nullptr };
	ModelObj *enemy3[200] = { nullptr };

	ModelObj *stage = nullptr;
	ModelObj *stage2[100] = { nullptr };

	Particle *particle = nullptr;

	//���݂̃V�[���̔ԍ�
	int SceneNo = static_cast<int>(GameSceneNo::Title);
	//�������̂��߂̌v��
	int SceneTime = 0;

	//�J����
	XMMATRIX matView;
	XMVECTOR V0 = { 0,5,-50,0 };
	XMMATRIX rotM;
	XMVECTOR V;
	XMVECTOR newTarget;
	XMVECTOR CameraEye;
	XMFLOAT3 up = { 0, 1, 0 };//������x�N�g��
	float CameraRot = 0;

	//�����蔻��(���ƕ���)
	Sphere sphere;
	Plane plane;
	Sphere enemySphere[200];
	Sphere enemy2Sphere[200];
	Sphere enemy3Sphere[200];

	bool collision1[200] = { false };
	bool collision2[200] = { false };
	bool collision3[200] = { false };

	//�Q�[���Ŏg���ϐ�
	float gravity = 0.2;
	float jump = 0.1;
	int jumpCount = 0;
	int jumpChange = 0;
	bool jumpFlag = false;
	float speed = 1;
	int rot = -180;
	int flag = 0;
	int jumpTime = 0;
	XMFLOAT2 backGroundPos = {};
	XMFLOAT2 backGround2Pos = {};
	XMFLOAT2 changeSize = {};
	bool sceneChangeFlag = false;
	bool enemyFlag[200] = { false };
	bool enemyFlag2[200] = { false };
	bool enemyFlag3[200] = { false };
	float enemyX = 0;
	XMFLOAT2 enemy2Pos = { 0,0 };
	XMFLOAT2 enemy3Pos[200] = { };
	XMFLOAT2 enemy3MoveSpeed = {};
	int endFlag = 0;
#pragma region �^�C�g���V�[��
	void TitleInit();
	void TitleUpdate();
	void TitleDraw();

#pragma region �Q�[���v���C�V�[��
	void GamePlayInit();
	void GamePlayUpdate();
	void GamePlayDraw();

#pragma region �G���h�V�[��
	void EndInit();
	void EndUpdate();
	void EndDraw();

public:
	GameScene() {};
	void SceneDelete()
	{
#pragma region �������
		//XAudio2���
		Audio::xAudio2.Reset();
		//Input�N���X���
		delete keyInput;
		keyInput = nullptr;
		delete mouseInput;
		mouseInput = nullptr;
		//WindowsAPI�̏I������
		winApp->Finalize();
		//WindowsAPI�������
		delete winApp;
		winApp = nullptr;
		//DirectXCommon�������
		delete common;
		common = nullptr;
		//�X�v���C�g�̉������
		delete spriteA;
		spriteA = nullptr;
		delete title;
		title = nullptr;
		delete title2;
		title2 = nullptr;
		delete title3;
		title3 = nullptr;
		delete backGround;
		backGround = nullptr;
		delete backGround2;
		backGround2 = nullptr;
		delete sceneChange;
		sceneChange = nullptr;
		delete backGround3;
		backGround3 = nullptr;
		delete GameOver;
		GameOver = nullptr;
		delete GameClear;
		GameClear = nullptr;

		//modelObj�������
		delete player;
		player = nullptr;
		for (int i = 0; i < _countof(enemy); i++)
		{
			delete enemy[i];
			enemy[i] = nullptr;
		}
		for (int i = 0; i < _countof(enemy2); i++)
		{
			delete enemy2[i];
			enemy2[i] = nullptr;
		}
		for (int i = 0; i < _countof(enemy3); i++)
		{
			delete enemy3[i];
			enemy3[i] = nullptr;
		}

		delete stage;
		stage = nullptr;
		//model�������
		delete model;
		model = nullptr;
		delete model2;
		model2 = nullptr;
		delete enemyModel;
		enemyModel = nullptr;
		for (int i = 0; i < _countof(stage2); i++)
		{
			delete stage2[i];
			stage2[i] = nullptr;
		}
		//�p�[�e�B�N���̉������
		delete particle;
		particle = nullptr;
	};

	void staticInit();
	void Init();
	bool Update();
	void Draw();

public://Getter
	const int &SceneTimeGetter() { return SceneTime; }
};

