#include "GameScene.h"
#include"Collision.h"

void GameScene::TitleInit()
{
	audio->PlayLoadedSound(soundData2, 0.05f);
	endFlag = 0;
	backGroundPos = { 640,360 };
	backGround2Pos = { 1920,360 };
	changeSize = { 0,0 };
	sceneChangeFlag = false;

	backGround->SetPosition(backGroundPos);
	backGround2->SetPosition(backGround2Pos);
	sceneChange->SetSize(changeSize);

	title->SetPosition({ 640, 360 });
	title2->SetPosition({ 284,188 });
	title3->SetPosition({ 336.0f + WinApp::window_width / 4,56.0f + WinApp::window_height / 2 });
	rot = -180;
	rotM = XMMatrixIdentity();
	rotM *= XMMatrixRotationY(XMConvertToRadians(0.0f));

	{
		XMFLOAT3 position = stage->GetPosition();
		position = { (float)0,-20,(float)0 };
		stage->SetPosition(position);
	}
	player->SetScale({5, 5, 5});
	player->SetRot({});
	player->SetPosition({ 0,0,stage->GetPosition().z });
	gravity = 0.2f;
	//���̏����l��ݒ�
	sphere.center = XMVectorSet(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z, 1);
	sphere.radius = 5.0f;

	//���ʂ̏����l��ݒ�
	plane.normal = XMVectorSet(0, 1, 0, 0);//�@���x�N�g��
	plane.distance = -15.0f;//���_(0,0,0)����̋���

	stage->SetScale({ 5000, 5, 5 });
	stage->Update();

	player->SetPosition({-80,0,stage->GetPosition().z });
	flag = 0;
	jumpTime = 0;
	jumpChange = 0;
	jumpCount = 0;
	jump = 0.1f;

	V = XMVector3TransformNormal(V0, rotM);
	player->SetTarget({ 0, 50, player->GetPosition().z });//�����_���W
	newTarget = { player->GetTarget().x,player->GetTarget().y,player->GetTarget().z,0 };
	CameraEye = V + newTarget;
	player->SetEye({ CameraEye.m128_f32[0],CameraEye.m128_f32[1] ,CameraEye.m128_f32[2] - 100 });//�n�_���W
	matView = XMMatrixLookAtLH(XMLoadFloat3(&player->GetEye()), XMLoadFloat3(&player->GetTarget()), XMLoadFloat3(&up));
}

void GameScene::TitleUpdate()
{
#pragma region �X�V����
	/*�d�͉��Z*/
	{
		XMFLOAT3 position = player->GetPosition();
		position.y = position.y - gravity + jump;
		player->SetPosition(position);
	}
	sphere.center = XMVectorSet(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z, 1);

	/*�w�i�ړ�*/
	{
		backGroundPos.x--;
		backGround2Pos.x--;

		if (backGroundPos.x <= -640)
		{
			backGroundPos.x = 1920;
		}
		if (backGround2Pos.x <= -640)
		{
			backGround2Pos.x = 1920;
		}

		backGround->SetPosition(backGroundPos);
		backGround2->SetPosition(backGround2Pos);
	}
	bool hit = Collision::CheckSphere2Plane(sphere, plane);
	if (hit)
	{
		// ���݂̍��W���擾
		XMFLOAT3 position = player->GetPosition();
		position.y = stage->GetPosition().y + 10;
		// ���W�̕ύX�𔽉f
		player->SetPosition(position);
		jump = 0.1f;
		if (jumpCount > 0)
		{
			jumpCount = 0;
		}
		else
		{
			jumpCount--;
		}
		jumpFlag = false;
		player->SetRot({});
		particle->AddDirectionParticle({ -2.8,-2.05,player->GetPosition().z }, static_cast<int>(direction::LEFT));

		if (jumpChange >= 2)
		{
			sceneChangeFlag = true;
		}
	}
	else
	{
		gravity += 0.05f;
		jumpCount=0.01f;
		jumpFlag = true;
		if (jumpChange >= 2)
		{
			/*player�̉�]*/
			XMFLOAT3 rotation = player->GetRot();

			rotation.z -= 10;

			//�Z�b�g
			player->SetRot(rotation);
		}
	}

	if (jumpCount <= 0 && jumpCount > -60)
	{
		jumpTime++;
	}
	else if (jumpCount >= 0)
	{
		jumpTime = -1;
	}
	else
	{
		jumpTime = 0;
	}

	if (keyInput->isKeyTrigger(DIK_SPACE) && jumpFlag == false)
	{
		audio->PlayLoadedSound(soundData3, 0.05f);

		if (jumpCount <= 0 && jumpCount > -30)
		{
			jumpChange++;
		}
		else if (jumpCount >= 0)
		{
			jumpChange = -1;
		}
		else
		{
			jumpChange = 0;
		}

		if (jumpChange == 0)
		{
			jump = 2;
			gravity = 0.2f;
		}
		if (jumpChange == 1)
		{
			jump = 3;
			gravity = 0.2f;
		}
		if (jumpChange >= 2)
		{
			jump = 4;
			gravity = 0.2f;
		}
	}
	if (jumpTime == 0)
	{
		flag = -1;
	}

	if (sceneChangeFlag == true)
	{
		changeSize.x += 10;
		changeSize.y += 10;
	}
	/*�V�[���`�F���W*/
	sceneChange->SetSize(changeSize);

	if (changeSize.x > 1500)
	{
		SceneTime = 0;
		audio->StopLoadedSound(soundData2);
		SceneNo = static_cast<int>(GameSceneNo::GamePlay);
	}
	/*�v���~�e�B�u�}�`�X�V*/
	player->Update();
	stage->Update();
	/*���f���X�V*/
	particle->Update();
}

void GameScene::TitleDraw()
{
	/*�X�v���C�g�`��*/
	/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());

	backGround->Draw();
	backGround2->Draw();
	title->Draw();
	title2->Draw();
	title3->Draw();
	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();

	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();

	/*�v���~�e�B�u�}�`�`��*/
	/*�v���~�e�B�u�}�`�`��O����*/
	Object3d::PreDraw(common->GetCmdList().Get());

	//stage->Draw();
	//player->Draw();
	//titleObj->Draw();

	/*�v���~�e�B�u�}�`�`��㏈��*/
	Object3d::PostDraw();
	/*���f���`��*/
	/*���f���`��O����*/
	ModelObj::PreDraw(common->GetCmdList().Get());

	stage->Draw();
	/*���f���`��㏈��*/
	ModelObj::PostDraw();

	/*�p�[�e�B�N���`��*/
	/*�p�[�e�B�N���`��O����*/
	ParticleManager::PreDraw(common->GetCmdList().Get());

	particle->Draw();

	/*�p�[�e�B�N���`��㏈��*/
	ParticleManager::PostDraw();
	/*���f���`��*/
	/*���f���`��O����*/
	ModelObj::PreDraw(common->GetCmdList().Get());

	//enemy->Draw();
	player->Draw();
	/*���f���`��㏈��*/
	ModelObj::PostDraw();

	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();

	/*�X�v���C�g�`��*/
	/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());
	sceneChange->Draw();
	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
}

void GameScene::GamePlayInit()
{
	//�����Đ�
	audio->PlayLoadedSound(soundData1, 0.05f);
	rotM = XMMatrixIdentity();
	rotM *= XMMatrixRotationY(XMConvertToRadians(0.0f));

	backGroundPos = { 640,360 };
	backGround2Pos = { 1920,360 };

	backGround->SetPosition(backGroundPos);
	backGround2->SetPosition(backGround2Pos);

	sceneChange->SetSize(changeSize);
	speed = 1;
	{
		XMFLOAT3 position = stage->GetPosition();
		position = { (float)0,-5,(float)0 };
		stage->SetPosition(position);
	}
	player->SetScale({ 5, 5, 5 });
	player->SetRot({});
	player->SetPosition({ 0,stage->GetPosition().y + 20,stage->GetPosition().z - 10020 });

	//���̏����l��ݒ�
	sphere.center = XMVectorSet(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z, 1);
	sphere.radius = 5.0f;

	//���ʂ̏����l��ݒ�
	plane.normal = XMVectorSet(0, 1, 0, 0);//�@���x�N�g��
	plane.distance = -5.0f;//���_(0,0,0)����̋���

	stage->SetScale({ 50, 5, 10 });
	stage->SetPosition({ 0,stage->GetPosition().y,-10000 });
	stage->Update();

	for (int i = 0; i < _countof(stage2); i++)
	{
		stage2[i]->SetScale({ 50,5,100 });
		stage2[i]->SetPosition({ 0,-10,(float)-10000 + (i * 200) });
	}

	enemyX = -40;
	enemy2Pos = { 40,30 };
	for (int i = 0; i < _countof(enemy); i++)
	{
		enemy[i]->SetScale({ 5,5,5 });
		enemy[i]->SetPosition({ enemyX,5,(float)-9500 + (i * 90) });
		enemyX += 10;
		if (enemyX > 45)
		{
			enemyX= -40;
		}
		enemy[i]->Update();

		enemySphere[i].center = XMVectorSet(enemy[i]->GetPosition().x, enemy[i]->GetPosition().y, enemy[i]->GetPosition().z, 1);
		enemySphere[i].radius = 5.0f;
	}
	for (int i = 0; i < _countof(enemy2); i++)
	{
		enemy2[i]->SetScale({ 5,5,5 });
		enemy2[i]->SetPosition({ enemy2Pos.x,enemy2Pos.y,(float)-8000 + (i * 50) });
		enemy2Pos.x -= 20;
		if (enemy2Pos.x < -45)
		{
			enemy2Pos.x = 45;
		}
		enemy2[i]->Update();

		enemy2Sphere[i].center = XMVectorSet(enemy2[i]->GetPosition().x, enemy2[i]->GetPosition().y, enemy2[i]->GetPosition().z, 1);
		enemy2Sphere[i].radius = 5.0f;
		enemy2[i]->SetPosition({ enemy2Pos.x,enemy2Pos.y,(float)-2000 + (i * 50) });
		enemy2[i]->Update();
	}

	for (int i = 0; i < _countof(enemy); i++)
	{
		enemyFlag[i] = false;
		enemyFlag2[i] = false;
		enemyFlag3[i] = false;
	}

	enemy3MoveSpeed = {1,1};

	V = XMVector3TransformNormal(V0, rotM);
	player->SetTarget(player->GetPosition());//�����_���W
	newTarget = { player->GetTarget().x,player->GetTarget().y,player->GetTarget().z,0 };
	CameraEye = V + newTarget;
	player->SetEye({ CameraEye.m128_f32[0],CameraEye.m128_f32[1],CameraEye.m128_f32[2] });//�n�_���W
	matView = XMMatrixLookAtLH(XMLoadFloat3(&player->GetEye()), XMLoadFloat3(&player->GetTarget()), XMLoadFloat3(&up));
}

void GameScene::GamePlayUpdate()
{
	#pragma region �X�V����
	/*�V�[���؂�ւ��߂�*/
	if (changeSize.x > 0)
	{
		changeSize.x -= 10;
		changeSize.y -= 10;
	}
	sceneChange->SetSize(changeSize);
	/*�����X�N���[��*/
	if (changeSize.x <= 0 && player->GetPosition().z < 9850)
	{
		XMFLOAT3 position = player->GetPosition();
		position.z = position.z+=speed;
		player->SetPosition(position);
	}
	if (player->GetPosition().z >= 9850)
	{
		endFlag = 1;
		audio->StopLoadedSound(soundData1);
		SceneTime = 0;
		SceneNo = static_cast<int>(GameSceneNo::End);
	}
	/*�d�͉��Z*/
	{
		XMFLOAT3 position = player->GetPosition();
		position.y = position.y-gravity+jump;
		player->SetPosition(position);
	}
	/*�ړ�*/
	if (keyInput->isKey(DIK_W) || keyInput->isKey(DIK_S) || keyInput->isKey(DIK_D) || keyInput->isKey(DIK_A))
	{
		// ���݂̍��W���擾
		XMFLOAT3 position = player->GetPosition();

		// �ړ���̍��W���v�Z
		if (keyInput->isKey(DIK_A)) { position.x--; }
		else if (keyInput->isKey(DIK_D)) { position.x++; }

		// ���W�̕ύX�𔽉f
		player->SetPosition(position);
	}

	sphere.center = XMVectorSet(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z, 1);

	bool hit = Collision::CheckSphere2Plane(sphere, plane);
	if (hit)
	{
		// ���݂̍��W���擾
		XMFLOAT3 position = player->GetPosition();
		if (position.x < stage->GetPosition().x + 55 && position.x>stage->GetPosition().x - 55)
		{
			position.y = stage2[0]->GetPosition().y + 10;
		}
		// ���W�̕ύX�𔽉f
		player->SetPosition(position);
		jump = 0.1f;
		if (jumpCount > 0)
		{
			jumpCount = 0;
		}
		else
		{
			jumpCount--;
		}
		jumpFlag = false;
		player->SetRot({});
		//speed = 1;
	}
	else
	{
		gravity += 0.05f;
		jumpCount = 0.01f;
		jumpFlag = true;
		if (jumpChange >= 2)
		{
			/*player�̉�]*/
			XMFLOAT3 rotation = player->GetRot();

			rotation.x += 10;

			//�Z�b�g
			player->SetRot(rotation);
		}
	}

	if (player->GetPosition().y < -1000)
	{
		endFlag = 2;
		audio->StopLoadedSound(soundData1);
		SceneTime = 0;
		SceneNo = static_cast<int>(GameSceneNo::End);
	}

	if (keyInput->isKeyTrigger(DIK_SPACE) && jumpFlag == false)
	{
		audio->PlayLoadedSound(soundData3, 0.05f);
		if (jumpCount <= 0 && jumpCount > -30)
		{
			jumpChange++;
		}
		else if (jumpCount > 0)
		{
			jumpChange = -1;
		}
		else
		{
			jumpChange = 0;
		}

		if (jumpChange == 0)
		{
			jump = 2;
			gravity = 0.2f;
			if (speed < 5)
			{
				speed += 0.1f;
			}
		}
		if (jumpChange == 1)
		{
			jump = 3;
			gravity = 0.2f;
			if (speed < 5)
			{
				speed += 0.2f;
			}
		}
		if (jumpChange >= 2)
		{
			jump = 4;
			gravity = 0.2f;
			if (speed < 5)
			{
				speed += 0.5f;
			}
		}
	}
	/*�Ǐ]�J����*/
	rotM = XMMatrixIdentity();
	rotM *= XMMatrixRotationX(XMConvertToRadians(10));
	rotM *= XMMatrixRotationY(XMConvertToRadians(CameraRot));
	V = XMVector3TransformNormal(V0, rotM);
	player->SetTarget(player->GetPosition());//�����_���W
	newTarget = { player->GetTarget().x,player->GetTarget().y,player->GetTarget().z,0 };
	CameraEye = V + newTarget;
	player->SetEye({ CameraEye.m128_f32[0],CameraEye.m128_f32[1],CameraEye.m128_f32[2] });//�n�_���W
	matView = XMMatrixLookAtLH(XMLoadFloat3(&player->GetEye()), XMLoadFloat3(&player->GetTarget()), XMLoadFloat3(&up));

	for (int i = 0; i < _countof(enemy); i++)
	{
		enemySphere[i].center = XMVectorSet(enemy[i]->GetPosition().x, enemy[i]->GetPosition().y, enemy[i]->GetPosition().z, 1);
		enemySphere[i].radius = 5.0f;
		collision1[i] = Collision::CheckSphere2Sphere(sphere, enemySphere[i], 5, 10);
		if (collision1[i] == true)
		{
			endFlag = 2;
			audio->StopLoadedSound(soundData1);
			SceneTime = 0;
			SceneNo = static_cast<int>(GameSceneNo::End);
		}

		enemy2Sphere[i].center = XMVectorSet(enemy2[i]->GetPosition().x, enemy2[i]->GetPosition().y, enemy2[i]->GetPosition().z, 1);
		enemy2Sphere[i].radius = 5.0f;
		collision2[i] = Collision::CheckSphere2Sphere(sphere, enemy2Sphere[i], 5, 10);
		if (collision2[i] == true)
		{
			endFlag = 2;
			audio->StopLoadedSound(soundData1);
			SceneTime = 0;
			SceneNo = static_cast<int>(GameSceneNo::End);
		}

		enemy3Sphere[i].center = XMVectorSet(enemy3[i]->GetPosition().x, enemy3[i]->GetPosition().y, enemy3[i]->GetPosition().z, 1);
		enemy3Sphere[i].radius = 5.0f;
		collision3[i] = Collision::CheckSphere2Sphere(sphere, enemy3Sphere[i], 5, 10);
		if (collision3[i] == true)
		{
			endFlag = 2;
			audio->StopLoadedSound(soundData1);
			SceneTime = 0;
			SceneNo = static_cast<int>(GameSceneNo::End);
		}

	}
	if (jumpChange >= 1)
	{
	}

	/*�v���~�e�B�u�}�`�X�V*/
	player->Update();
	for (int i = 0; i < _countof(enemy); i++)
	{
		if ((enemy[i]->GetPosition().z - player->GetPosition().z) < 1000)
		{
			enemyFlag[i] = true;
		}
		if ((enemy[i]->GetPosition().z - player->GetPosition().z) < -20)
		{
			enemyFlag[i] = false;
		}
		enemy[i]->Update();
	}
	for (int i = 0; i < _countof(enemy2); i++)
	{
		if ((enemy2[i]->GetPosition().z - player->GetPosition().z) < 1000)
		{
			enemyFlag2[i] = true;
		}
		if ((enemy2[i]->GetPosition().z - player->GetPosition().z) < -20)
		{
			enemyFlag2[i] = false;
		}

		enemy2[i]->Update();
	}

	stage->Update();
	for (int i = 0; i < _countof(stage2); i++)
	{
		stage2[i]->Update();
	}
	/*���f���X�V*/

	/*�p�[�e�B�N���X�V*/
	//�p�[�e�B�N����ǉ��������Ƃ�AddParticle����
	//particle->AddParticle({ 1,1,0 }, 60);

	particle->Update();
}

void GameScene::GamePlayDraw()
{
#pragma region �`�揈��

	/*�X�v���C�g�`��*/
	/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());

	backGround3->Draw();
	//spriteA->Draw();

	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();

	/*�v���~�e�B�u�}�`�`��*/
	/*�v���~�e�B�u�}�`�`��O����*/
	Object3d::PreDraw(common->GetCmdList().Get());

	//stage->Draw();
	//enemy->Draw();
	//player->Draw();

	/*�v���~�e�B�u�}�`�`��㏈��*/
	Object3d::PostDraw();

	/*���f���`��*/
	/*���f���`��O����*/
	ModelObj::PreDraw(common->GetCmdList().Get());

	stage->Draw();
	for (int i = 0; i < _countof(enemy); i++)
	{
		if (enemyFlag[i] == true)
		{
			enemy[i]->Draw();
		}
	}
	for (int i = 0; i < _countof(enemy2); i++)
	{
		if (enemyFlag2[i] == true)
		{
			enemy2[i]->Draw();
		}
	}
	for (int i = 0; i < _countof(enemy3); i++)
	{
		if (enemyFlag3[i] == true)
		{
			enemy3[i]->Draw();
		}
	}

	player->Draw();
	for (int i = 0; i < _countof(stage2); i++)
	{
		stage2[i]->Draw();
	}

	/*���f���`��㏈��*/
	ModelObj::PostDraw();

	/*�p�[�e�B�N���`��*/
	/*�p�[�e�B�N���`��O����*/
	ParticleManager::PreDraw(common->GetCmdList().Get());

	//particle->Draw();

	/*�p�[�e�B�N���`��㏈��*/
	ParticleManager::PostDraw();

	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();

	/*�X�v���C�g�`��*/
	/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());
	sceneChange->Draw();
	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();

}

void GameScene::EndInit()
{
}

void GameScene::EndUpdate()
{
	//�V�[���J��
	if (keyInput->isKeyTrigger(DIK_SPACE))
	{
		audio->PlayLoadedSound(soundData3, 0.05f);
		SceneTime = 0;
		SceneNo = static_cast<int>(GameSceneNo::Title);
	}
}

void GameScene::EndDraw()
{
	/*�X�v���C�g�`��*/
	/*�X�v���C�g�`��O����*/
	Sprite::PreDraw(common->GetCmdList().Get());
	if (endFlag == 1)
	{
		GameClear->Draw();
	}
	if (endFlag == 2)
	{
		GameOver->Draw();
	}
	//spriteA->Draw();

	/*�X�v���C�g�`��㏈��*/
	Sprite::PostDraw();
	//�[�x�o�b�t�@�N���A
	common->ClearDepthBuffer();
}

void GameScene::staticInit()
{
	winApp = new WinApp;
	keyInput = new KeyInput(winApp);
	mouseInput = new MouseInput(winApp);
	common = new DirectXCommon(winApp);
	winApp->Innitialize();
	common->Initialize();
	keyInput->Initialize();
	mouseInput->Initialize();
	Audio::Init();

	HRESULT result;

	//�����ǂݍ���
	soundData1 = audio->SoundLoadWave("Resources/GAMEBGM.wav",true);
	soundData2 = audio->SoundLoadWave("Resources/TITLEBGM.wav",true);
	soundData3 = audio->SoundLoadWave("Resources/SPACESE.wav", false);

	/*�X�v���C�g������*/
	Sprite::StaticInitialize(common->GetDev().Get(), WinApp::window_width, WinApp::window_height);
	//�`�揉���������@��������
	Sprite::LoadTexture(0, L"Resources/SCORE.png");
	spriteA = Sprite::Create(0, { 0.0f,0.0f });

	Sprite::LoadTexture(1, L"Resources/title.png");
	title = Sprite::Create(1, { 0.0f,0.0f });

	Sprite::LoadTexture(2, L"Resources/title2.png");
	title2 = Sprite::Create(2, { 220.0f,100.0f });

	Sprite::LoadTexture(3, L"Resources/title3.png");
	title3 = Sprite::Create(3, { 336.0f,56.0f });

	Sprite::LoadTexture(4, L"Resources/backGround.png");
	backGround = Sprite::Create(4, { 640,360 });

	Sprite::LoadTexture(5, L"Resources/backGround2.png");
	backGround2 = Sprite::Create(5, { 640,360 });

	Sprite::LoadTexture(6, L"Resources/SceneChange.png");
	sceneChange = Sprite::Create(6, { 640,360 });

	Sprite::LoadTexture(7, L"Resources/backGround3.png");
	backGround3 = Sprite::Create(7, { 640,360 });

	Sprite::LoadTexture(8, L"Resources/GAMEOVER.png");
	GameOver = Sprite::Create(8, { 640,360 });

	Sprite::LoadTexture(9, L"Resources/GAMECLEAR.png");
	GameClear = Sprite::Create(9, { 640,360 });

	/*�v���~�e�B�u�}�`������*/
	Object3d::StaticInitialize(common->GetDev().Get(), WinApp::window_width, WinApp::window_height);

	//enemy = Object3d::Create();
	//enemy->Init(L"Resources/kuro.png");


	/*���f��������*/
	ModelObj::StaticInitialize(common->GetDev().Get(), WinApp::window_width, WinApp::window_height);

	model = new Model(common);
	model->Initialize();
	model->CreateModel("Resources/stage/", "stage");
	
	model2 = new Model(common);
	model2->Initialize();
	model2->CreateModel("Resources/stage2/", "stage2");

	enemyModel = new Model(common);
	enemyModel->Initialize();
	enemyModel->CreateModel("Resources/enemy/", "enemy");

	//modelObj = ModelObj::Create();
	//modelObj->SetModel(model);
	player = ModelObj::Create();
	player->SetModel(model);
	for (int i = 0; i < _countof(enemy); i++)
	{
		enemy[i] = ModelObj::Create();
		enemy[i]->SetModel(enemyModel);
	}
	for (int i = 0; i < _countof(enemy2); i++)
	{
		enemy2[i] = ModelObj::Create();
		enemy2[i]->SetModel(enemyModel);
	}
	for (int i = 0; i < _countof(enemy3); i++)
	{
		enemy3[i] = ModelObj::Create();
		enemy3[i]->SetModel(enemyModel);
	}

	stage = ModelObj::Create();
	stage->SetModel(model2);
	for (int i = 0; i < _countof(stage2); i++)
	{
		stage2[i] = ModelObj::Create();
		stage2[i]->SetModel(model2);
	}
	/*�p�[�e�B�N��������*/
	ParticleManager::StaticInitialize(common->GetDev().Get());

	particle = new Particle(L"Resources/titleEffect.png");
	particle->Init();

}

void GameScene::Init()
{

	switch (SceneNo)
	{
	case static_cast<int>(GameScene::GameSceneNo::Title):
		TitleInit();
		break;
	case static_cast<int>(GameScene::GameSceneNo::GamePlay):
		GamePlayInit();
		break;
	case static_cast<int>(GameScene::GameSceneNo::End):
		EndInit();
		break;
	default:
		break;
	}
}

bool GameScene::Update()
{
	if (winApp->ProcessMessage() || keyInput->isKeyTrigger(DIK_ESCAPE))
	{
		return false;
	}
	//�L�[�{�[�h���̎擾�J�n
	keyInput->Updete();
	mouseInput->Updete();
	switch (SceneNo)
	{
	case static_cast<int>(GameScene::GameSceneNo::Title):
		SceneTime = 1;
		TitleUpdate();
		break;
	case static_cast<int>(GameScene::GameSceneNo::GamePlay):
		SceneTime = 1;
		GamePlayUpdate();
		break;
	case static_cast<int>(GameScene::GameSceneNo::End):
		SceneTime = 1;
		EndUpdate();
		break;
	default:
		break;
	}

	return true;
}

void GameScene::Draw()
{
#pragma region �`��O����

	common->PreDraw();

	switch (SceneNo)
	{
	case static_cast<int>(GameScene::GameSceneNo::Title):
		TitleDraw();
		break;
	case static_cast<int>(GameScene::GameSceneNo::GamePlay):
		GamePlayDraw();
		break;
	case static_cast<int>(GameScene::GameSceneNo::End):
		EndDraw();
		break;
	default:
		break;
	}

#pragma region �`��㏈��

	common->PostDraw();
}
