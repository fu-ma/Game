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
	WNDCLASSEX w{};//ウィンドウクラスの設定
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

	//現在のシーンの番号
	int SceneNo = static_cast<int>(GameSceneNo::Title);
	//初期化のための計測
	int SceneTime = 0;

	//カメラ
	XMMATRIX matView;
	XMVECTOR V0 = { 0,5,-50,0 };
	XMMATRIX rotM;
	XMVECTOR V;
	XMVECTOR newTarget;
	XMVECTOR CameraEye;
	XMFLOAT3 up = { 0, 1, 0 };//上方向ベクトル
	float CameraRot = 0;

	//あたり判定(球と平面)
	Sphere sphere;
	Plane plane;
	Sphere enemySphere[200];
	Sphere enemy2Sphere[200];
	Sphere enemy3Sphere[200];

	bool collision1[200] = { false };
	bool collision2[200] = { false };
	bool collision3[200] = { false };

	//ゲームで使う変数
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
#pragma region タイトルシーン
	void TitleInit();
	void TitleUpdate();
	void TitleDraw();

#pragma region ゲームプレイシーン
	void GamePlayInit();
	void GamePlayUpdate();
	void GamePlayDraw();

#pragma region エンドシーン
	void EndInit();
	void EndUpdate();
	void EndDraw();

public:
	GameScene() {};
	void SceneDelete()
	{
#pragma region 解放処理
		//XAudio2解放
		Audio::xAudio2.Reset();
		//Inputクラス解放
		delete keyInput;
		keyInput = nullptr;
		delete mouseInput;
		mouseInput = nullptr;
		//WindowsAPIの終了処理
		winApp->Finalize();
		//WindowsAPI解放処理
		delete winApp;
		winApp = nullptr;
		//DirectXCommon解放処理
		delete common;
		common = nullptr;
		//スプライトの解放処理
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

		//modelObj解放処理
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
		//model解放処理
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
		//パーティクルの解放処理
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

