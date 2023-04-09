#include"stage.h"
#include"player.h"
#include"load.h"
#include"math.h"
#include"back.h"
#include"smile.h"
#include"easing.h"
#include<time.h>

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "GRAVERT";

// ウィンドウ横幅
const int WIN_WIDTH = 1280;
// ウィンドウ縦幅
const int WIN_HEIGHT = 960;	
bool HIT(float aX, float aY, float bX, float bY, int r)
{
	if (bX - r < aX + r+MOVE-1 && aX - r - MOVE-1 < bX + r && bY - r < aY + r&& aY - r < bY + r)
	{
		return true;
	}
	else
	{
		return false;
	}
}


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);
	SetWindowIconID(100);
	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);
	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(0.8);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0xFF);
	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);
	//クラス宣言
	jampParticle jampParticle[100];
	deathParticle death[200];
	stage stage1;
	player player;
	load load;
	back back;
	particle particle[MAX_ARRAY];
	Fade fade;
	// 画像などのリソースデータの変数宣言と読み込み
	int saveGraph = LoadGraph("resource////checkpoint.png");
	load.GH3[0] = LoadGraph("resource////Back.png");
	load.GH3[1] = LoadGraph("resource////Back_black.png");
	load.GH3[2] = LoadGraph("resource////Space.png");
	LoadDivGraph("resource////sample.png", 7, 7, 1, 32, 32, load.gHandle);
	LoadDivGraph("resource////item.png", 12, 12, 1, 36, 36, load.GH6);
	LoadDivGraph("resource////savepoint.png", 2, 2, 1, 32, 32, load.GH9);
	LoadDivGraph("resource////ui2.png", 2, 2, 1, 278, 543, load.GH12);
	// ゲームループで使う変数の宣言
	float acceleration = 0.98;
	int change = 0;
	int groundFlag = 0;
	int rotationFlag = 0; int sute = 1;
	int moveY = 0;
	int Flag = 0;
	int Flag3 = 0;
	int Flag4 = 0;
	int moveFlag = 0;
	int moveyFlag = 0;
	int kirikae = 0;
	int titleFlag = 0;
	int pCount = 0;
	int aitemugetFlag = 0;
	int agpFlag = 0;
	int randX = 0;
	int randY = 0;
	int randTimer = 0;
	hanabi hanabi[MAX_HANABI];
	int R = 0;
	int G = 0;
	int B = 0;
	//下からでる玉
	int Scene = 0;
	int ALPHA2 = 0;
	int x2 = 0;
	int y2 = 0;
	float r = 0;
	int Count = 0;
	float aitemuAcceleration = 0.5;
	int aitemCount = 0;
	int tenmetu = 0;
	int save = load.GH9[1];
	int savesitakaFlag = 0;
	int savepointX = 0;
	int savepointY = 0;
	int fadeFlag = 0;
	int aitemTimer = 0;
	int saundo = 80;
	int sousaTimer = 0;
	int sukuY = 0;
	int sousaFlag = 0;
	int uiCount = 0;
	float checkX = WIN_WIDTH / 2;
	float checkY = -56;
	float a = 0;
	int b = 0;
	float c = 0;
	//aitemu ap[MAX_ARRAY];

	// 最新のキーボード情報用
	char keys[256] = { 0 };
	XINPUT_STATE input = { 0 };
	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (1)
	{
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		XINPUT_STATE oldinput = input;
		GetJoypadXInputState(DX_INPUT_PAD1, &input);
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		groundFlag = 0;
		jampParticle[0].countFlag = 1;
		randX = 0;
		randY = 0;
		agpFlag = 0;
		stage1.Stagechange(sute - 1);
		//移動処理
		if (titleFlag == 1)
		{
			if ((keys[KEY_INPUT_A] || keys[KEY_INPUT_LEFT] || ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT)) &&
				(keys[KEY_INPUT_D] || keys[KEY_INPUT_RIGHT]) == FALSE))
			{
				if (moveFlag == 0)
				{
					player.move(LEFT, &player.posX, &player.leftMove);
				}

				if (rotationFlag == 0 && moveFlag == 0)
				{
					player.rotation -= TURNOVER_RATE;
				}

				if (rotationFlag == 1 && moveFlag == 0)
				{
					player.rotation += TURNOVER_RATE;
				}

				//左の当たり判定
				if (stage1.HIT(player.posX - PLAYER_R + 1, player.posY - PLAYER_R + 1, sute) == ATARI ||
					stage1.HIT(player.posX - PLAYER_R + 1, player.posY + PLAYER_R - 1, sute) == ATARI)
				{
					player.posX = (player.posX / BLOCK_SIZE) * BLOCK_SIZE + MOVE;
				}
			}

			if ((keys[KEY_INPUT_D] || keys[KEY_INPUT_RIGHT] || ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT))) == TRUE &&
				(keys[KEY_INPUT_A] || keys[KEY_INPUT_LEFT]) == FALSE)
			{
				if (moveFlag == 0)
				{
					player.move(RIGHT, &player.posX, &player.rightMove);
				}

				if (rotationFlag == 0 && moveFlag == 0)
				{
					player.rotation += TURNOVER_RATE;
				}

				if (rotationFlag == 1 && moveFlag == 0)
				{
					player.rotation -= TURNOVER_RATE;
				}

				//右の当たり判定
				if (stage1.HIT(player.posX + PLAYER_R + 1, player.posY - PLAYER_R + 1, sute) == ATARI ||
					stage1.HIT(player.posX + PLAYER_R + 1, player.posY + PLAYER_R - 1, sute) == ATARI)
				{
					player.posX = (player.posX / BLOCK_SIZE) * BLOCK_SIZE - MOVE;
				}
			}

			//みんな大好き重力
			if (player.t <= GRAVITY_MAX)
			{
				player.speed += 0.1;
				player.t += 0.02 * player.speed;

			}
			player.velY = player.gravity * player.t;
			if (moveyFlag == 0 && moveFlag == 0)
			{
				if (change % 2 == false)//上にいて下に行く時
				{
					player.posY += player.velY;
				}

				if (change % 2 == true)//下にいて上にいる時
				{
					player.posY -= player.velY;
				}
			}
			moveyFlag = 0;


			//上の当たり判定
			if (stage1.HIT(player.posX - PLAYER_R + 3, player.posY - PLAYER_R - player.velY + 1, sute) == ATARI ||
				stage1.HIT(player.posX + PLAYER_R - 3, player.posY - PLAYER_R - player.velY + 1, sute) == ATARI)
			{
				if (pCount == 0)
				{
					PlaySoundMem(load.SHandle8, DX_PLAYTYPE_BACK, TRUE);
				}
				if (CheckSoundMem(load.SHandle7) == 1)
				{
					StopSoundMem(load.SHandle7);
				}
				groundFlag = 1;
				pCount++;
				player.gravityUpdate();
				jampParticle[0].countUpdate();
				rotationFlag = 1;
				for (int i = 0; i < 100; i++)
				{
					jampParticle[i].Flag = 0;
				}
				player.posY = (int)(player.posY / BLOCK_SIZE) * BLOCK_SIZE + PLAYER_R;
				randTimer++;
				if (randTimer < 10)
				{
					randX += rand() % 11 - 5;
					randY += rand() % 11 - 5;
				}
			}


			//下の当たり判定
			if (stage1.HIT(player.posX - PLAYER_R + 3, player.posY + PLAYER_R + player.velY - 1, sute) == ATARI ||
				stage1.HIT(player.posX + PLAYER_R - 3, player.posY + PLAYER_R + player.velY - 1, sute) == ATARI)
			{
				if (pCount == 0)
				{
					PlaySoundMem(load.SHandle8, DX_PLAYTYPE_BACK, TRUE);
				}
				groundFlag = 1;
				pCount++;
				player.gravityUpdate();
				jampParticle[0].countUpdate();
				rotationFlag = 0;
				for (int i = 0; i < 100; i++)
				{
					jampParticle[i].Flag = 0;
				}
				player.posY = (int)(player.posY / BLOCK_SIZE) * BLOCK_SIZE + PLAYER_R;
				if (player.gameoverFlag == 1)
				{
					player.gameoverFlag = 0;
				}
				randTimer++;
				if (randTimer < 10)
				{
					randX += rand() % 11 - 5;
					randY += rand() % 11 - 5;
				}
			}

			//針の当たり判定
			if (stage1.HIT(player.posX - PLAYER_R + 10, player.posY - PLAYER_R + 10, sute) == SIBOU ||
				stage1.HIT(player.posX + PLAYER_R - 10, player.posY - PLAYER_R + 10, sute) == SIBOU ||
				stage1.HIT(player.posX - PLAYER_R + 10, player.posY + PLAYER_R - 10, sute) == SIBOU ||
				stage1.HIT(player.posX + PLAYER_R - 10, player.posY + PLAYER_R - 10, sute) == SIBOU)
			{
				if (CheckSoundMem(load.SHandle7) == 1)
				{
					StopSoundMem(load.SHandle7);
				}
				PlaySoundMem(load.SHandle1, DX_PLAYTYPE_BACK);
				StartJoypadVibration(DX_INPUT_PAD1, SINDOU, TIMER);
				player.size = 0;
				player.gameoverFlag = 1;
			}
			if (stage1.HIT(player.posX - PLAYER_R + 10, player.posY - PLAYER_R + 10, sute) == SIBOU2 ||
				stage1.HIT(player.posX + PLAYER_R - 10, player.posY - PLAYER_R + 10, sute) == SIBOU2 ||
				stage1.HIT(player.posX - PLAYER_R + 10, player.posY + PLAYER_R - 10, sute) == SIBOU2 ||
				stage1.HIT(player.posX + PLAYER_R - 10, player.posY + PLAYER_R - 10, sute) == SIBOU2)
			{
				if (CheckSoundMem(load.SHandle7) == 1)
				{
					StopSoundMem(load.SHandle7);
				}
				PlaySoundMem(load.SHandle1, DX_PLAYTYPE_BACK);
				StartJoypadVibration(DX_INPUT_PAD1, SINDOU, TIMER);
				player.size = 0;
				player.gameoverFlag = 1;
			}


			//save

			if (stage1.HIT(player.posX - PLAYER_R + 1, player.posY - PLAYER_R + 1, sute) == 7 ||
				stage1.HIT(player.posX + PLAYER_R - 1, player.posY - PLAYER_R + 1, sute) == 7 ||
				stage1.HIT(player.posX - PLAYER_R + 1, player.posY + PLAYER_R - 1, sute) == 7 ||
				stage1.HIT(player.posX + PLAYER_R - 1, player.posY + PLAYER_R - 1, sute) == 7)
			{
				if (savesitakaFlag == 0)
				{
					PlaySoundMem(load.SHandle4, DX_PLAYTYPE_BACK);
				}
				save = load.GH9[0];
				savesitakaFlag = 1;
				savepointX = (player.posX / BLOCK_SIZE) * BLOCK_SIZE;
				savepointY = (player.posY / BLOCK_SIZE) * BLOCK_SIZE;
				
			}

			//ゴール当たり判定
			if (stage1.HIT(player.posX - PLAYER_R + 1, player.posY - PLAYER_R + 1, sute) == 6 ||
				stage1.HIT(player.posX + PLAYER_R - 1, player.posY - PLAYER_R + 1, sute) == 6 ||
				stage1.HIT(player.posX - PLAYER_R + 1, player.posY + PLAYER_R - 1, sute) == 6 ||
				stage1.HIT(player.posX + PLAYER_R - 1, player.posY + PLAYER_R - 1, sute) == 6 ||
				stage1.HIT(player.posX - PLAYER_R + 1, player.posY - PLAYER_R + 1, sute) == 5 ||
				stage1.HIT(player.posX + PLAYER_R - 1, player.posY - PLAYER_R + 1, sute) == 5 ||
				stage1.HIT(player.posX - PLAYER_R + 1, player.posY + PLAYER_R - 1, sute) == 5 ||
				stage1.HIT(player.posX + PLAYER_R - 1, player.posY + PLAYER_R - 1, sute) == 5)
			{
				moveFlag = 1;
				save = load.GH9[1];
				savesitakaFlag = 0;
				fadeFlag = 1;
				a = 0;
				b = 0;
				c = 0;
				checkX = WIN_WIDTH / 2;
				checkY = -56;
			}
			if (savesitakaFlag == 1)
			{
				if (b < 80)
				{
					easing::Updete(checkY, WIN_HEIGHT/2, InSine, a);
				}
				else
				{
					easing::Updete(checkY, WIN_HEIGHT+56, OutSine, c);
				}
				b++;
			}
			//fade
			if (fadeFlag == 1)
			{
				//フェードイン・フェードアウト
				if (fade.Flag == 0)
				{
					fade.X = player.posX;
					fade.Y = player.posY;
					if (fade.Extrate < 541)
					{
						if (fade.Extrate == 0)
						{
							PlaySoundMem(load.SHandle5, DX_PLAYTYPE_BACK,TRUE);
						}
						fade.Extrate += 6.0;
						fade.Angle += 0.05;
					}
					else
					{
						player.size = 0;
						sute += 1;
						stage1.Stagechange(sute - 1);
						fade.Flag = 1;
					}
				}

				if (fade.Flag == 1)
				{
					player.gravityUpdate();
					player.update();
					if (sute == 10)
					{
						player.uraUpdate();
					}
					change = 0;
					fade.X = player.posX;
					fade.Y = player.posY;
					fade.Angle = 0;
					fade.X = player.posX;
					fade.Y = player.posY;
					if (fade.Extrate > 12.0)
						fade.Extrate -= 12.0;
					else
					{
						fade.Extrate -= 6.0;
						if (CheckSoundMem(load.SHandle5) == 1)
						{
							StopSoundMem(load.SHandle5);
						}
						fade.Flag = 0;
						moveFlag = 0;
						fadeFlag = 0;
					}
				}
			}
			
			//死んでる間
			if (player.gameoverFlag == 1)
			{
				change = 0;
			}
			//aitemu取ったら
			if (aitemugetFlag == 1)
			{
				groundFlag = 1;
				if ((keys[KEY_INPUT_SPACE] == true && oldkeys[KEY_INPUT_SPACE] == false) ||
					(input.Buttons[XINPUT_BUTTON_A] && !oldinput.Buttons[XINPUT_BUTTON_A]))
				{
					aitemugetFlag = 0;
				}
			}

			//プレイヤーの復活処理
			if (player.gameoverFlag == 0 && player.size < 1.0f)
			{
				player.size += 0.1;
			}
		}
		// 描画処理

		if (change % 2 == 1)
			if (back.move > -5.0)
				back.move -= 0.5;

		if (change % 2 == 0)
			if (back.move < 5.0)
				back.move += 0.5;

		if (back.y >= 960)
			back.y = 0;
		if (back.y <= -960)
			back.y = 0;

		back.y += back.move;

		// 描画処理
		DrawGraph(back.x, back.y, load.GH3[2], TRUE);
		DrawGraph(back.x, back.y - 960, load.GH3[2], TRUE);
		DrawGraph(back.x, back.y + 960, load.GH3[2], TRUE);
		aitemCount++;
		if (aitemCount > 11*HAYASA)
		{
			aitemCount = 0;
		}

		//タイトル画面
		if (titleFlag == 0)
		{
			change = 0;
			saundo = 100;
			StopSoundMem(load.SHandle9);
			ChangeVolumeSoundMem(60, load.SHandle1);//hari
			ChangeVolumeSoundMem(100, load.SHandle2);//space
			ChangeVolumeSoundMem(saundo, load.SHandle3);//ゲーム音
			ChangeVolumeSoundMem(100, load.SHandle4);//PC
			ChangeVolumeSoundMem(100, load.SHandle5);//フェードイン
			ChangeVolumeSoundMem(70, load.SHandle6);//重力
			ChangeVolumeSoundMem(100, load.SHandle7);//hannten
			ChangeVolumeSoundMem(100, load.SHandle8);//着地
			ChangeVolumeSoundMem(100, load.SHandle9);//kuria
			if (CheckSoundMem(load.SHandle3) == 0)
			{
				PlaySoundMem(load.SHandle3, DX_PLAYTYPE_LOOP);
			}
			DrawGraph(WIN_WIDTH/2-434.5f, WIN_HEIGHT/2-68.5f, load.GH4, TRUE);
			tenmetu++;
			if (tenmetu % 100 <= 60)
			{
				DrawGraph(WIN_WIDTH / 2 - 304, WIN_HEIGHT / 1.5 - 48, load.GH8, TRUE);
			}
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 || ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A)))
			{
				PlaySoundMem(load.SHandle2, DX_PLAYTYPE_BACK);
				sute = 1;
				pCount = 0;
				titleFlag = 1;
			}
		}

		if (sute == 9)
		{
			saundo-=5;
			if (saundo <= 5)
			{
				StopSoundMem(load.SHandle3);
				if (saundo == 5)
				{
					PlaySoundMem(load.SHandle9, DX_PLAYTYPE_LOOP);
				}
			}
		}

		if (titleFlag == 1)
		{
			if (sute == 3)
			{
				//動くブロックとの当たり判定
				for (int i = 0; i < MOVEBLOCK_MAX; i++)
				{
					if (HIT(player.posX, player.posY, stage1.moveblockX[i], stage1.moveblockY[i], PLAYER_R) == true)
					{
						randTimer++;
						if (randTimer < 10)
						{
							randX += rand() % 11 - 5;
							randY += rand() % 11 - 5;
						}
						groundFlag = 1;

						jampParticle->countUpdate();
						if (kirikae == 0)
						{
							player.posY = stage1.moveblockY[i] - 32;
						}
						if (kirikae == 1)
						{
							player.posY = stage1.moveblockY[i] + 32;
						}
					}
				}
			}
			//if (sute == 3)
			//{
			//	//動くブロックとの当たり判定
			//	for (int i = 0; i < 10; i++)
			//	{
			//		if (HIT(player.posX, player.posY, stage1.moveblockX3[i], stage1.moveblockY3[i], PLAYER_R) == true)
			//		{
			//			randTimer++;
			//			if (randTimer < 10)
			//			{
			//				randX += rand() % 11 - 5;
			//				randY += rand() % 11 - 5;
			//			}
			//			groundFlag = 1;

			//			jampParticle->countUpdate();
			//			if (kirikae == 0)
			//			{
			//				player.posY = stage1.moveblockY3[i] - 32;
			//			}
			//			if (kirikae == 1)
			//			{
			//				player.posY = stage1.moveblockY3[i] + 32;
			//			}
			//		}
			//	}
			//}
			if (sute == 7)
			{
				//動くブロックとの当たり判定
				for (int i = 0; i < 5; i++)
				{
					if (HIT(player.posX, player.posY, stage1.moveblockX2[i], stage1.moveblockY2[i], PLAYER_R) == true)
					{
						randTimer++;
						if (randTimer < 10)
						{
							randX += rand() % 11 - 5;
							randY += rand() % 11 - 5;
						}
						groundFlag = 1;

						jampParticle->countUpdate();
						if (kirikae == 0)
						{
							player.posY = stage1.moveblockY2[i] - 32;
						}
						if (kirikae == 1)
						{
							player.posY = stage1.moveblockY2[i] + 32;
						}
					}
				}
			}
			if (sute == 10)
			{
				//動くブロックとの当たり判定
				for (int i = 0; i < 29; i++)
				{
					if (HIT(player.posX, player.posY, stage1.moveblockX4[i], stage1.moveblockY4[i], PLAYER_R) == true)
					{
						randTimer++;
						if (randTimer < 10)
						{
							randX += rand() % 11 - 5;
							randY += rand() % 11 - 5;
						}
						groundFlag = 1;

						jampParticle->countUpdate();
						if (kirikae == 0)
						{
							player.posY = stage1.moveblockY4[i] - 32;
						}
						if (kirikae == 1)
						{
							player.posY = stage1.moveblockY4[i] + 32;
						}
					}
				}
			}
			DrawGraph(0 + randX, 0 + randY, load.GH3[0], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, back.ALPHA);
			DrawGraph(0 + randX, 0 + randY, load.GH3[1], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			aitemTimer++;
			if (aitemTimer > 120)
			{
				for (int i = 0; i < 7; i++)
				{
					stage1.aitemuFlag[i] = 0;
				}
				for (int i = 0; i < 9; i++)
				{
					stage1.aitemuFlag2[i] = 0;
				}
				for (int i = 0; i < 2; i++)
				{
					stage1.aitemuFlag3[i] = 0;
				}
				for (int i = 0; i < 6; i++)
				{
					stage1.aitemuFlag4[i] = 0;
				}
				for (int i = 0; i < 8; i++)
				{
					stage1.aitemuFlag5[i] = 0;
				}
				for (int i = 0; i < 7; i++)
				{
					stage1.aitemuFlag6[i] = 0;
				}
				for (int i = 0; i < 19; i++)
				{
					stage1.aitemuFlag7[i] = 0;
				}
				aitemTimer = 0;
			}
for (int y = 0; y < stage1.mapCountY; y++)
{
	for (int x = 0; x < stage1.mapCountX; x++)
	{
		if (stage1.map[y][x] == BLOCK1)
		{
			DrawGraph(x * BLOCK_SIZE + randX, y * BLOCK_SIZE + randY, load.gHandle[1], TRUE);
		}

		if (stage1.map[y][x] == sitaHari)
		{
			DrawRotaGraph(x * BLOCK_SIZE + PLAYER_R + randX, y * BLOCK_SIZE + PLAYER_R + randY, 1.0f, DX_PI_F, load.gHandle[2], TRUE);
		}

		if (stage1.map[y][x] == ueHari)
		{
			DrawGraph(x * BLOCK_SIZE + randX, y * BLOCK_SIZE + randY, load.gHandle[2], TRUE);
		}

		if (stage1.map[y][x] == 5)
		{
			DrawRotaGraph(x * BLOCK_SIZE + PLAYER_R + randX, y * BLOCK_SIZE + PLAYER_R + randY, 1.0f, 0, load.gHandle[5], TRUE);
		}
		if (stage1.map[y][x] == 6)
		{
			DrawRotaGraph(x * BLOCK_SIZE + PLAYER_R + randX, y * BLOCK_SIZE + PLAYER_R + randY, 1.0f, 0, load.gHandle[6], TRUE);
		}
		if (stage1.map[y][x] == 7)
		{
			DrawRotaGraph(x * BLOCK_SIZE + PLAYER_R + randX, y * BLOCK_SIZE + PLAYER_R + randY, 4.0f, 0, save, TRUE);
		}
		if (stage1.map[y][x] == 10)
		{
			DrawRotaGraph(x * BLOCK_SIZE + PLAYER_R + randX, y * BLOCK_SIZE + PLAYER_R + randY, 1.0f, 0, load.gHandle[5], TRUE);
		}
		if (stage1.map[y][x] == 11)
		{
			DrawRotaGraph(x * BLOCK_SIZE + PLAYER_R + randX, y * BLOCK_SIZE + PLAYER_R + randY, 1.0f, 0, load.gHandle[6], TRUE);
		}
	}
}
			switch (sute)
			{
			case 1:
				break;
			case 2:
			//	//動くブロック

			//	for (int i = 0; i < MOVEBLOCK_MAX; i++)
			//	{
			//		if (stage1.moveT[i] <= GRAVITY_MAX)
			//		{
			//			stage1.moveSpeed[i] += 0.08;
			//			stage1.moveT[i] += 0.02 * stage1.moveSpeed[i];

			//		}
			//		stage1.moveVelY[i] = player.gravity * stage1.moveT[i];
			//	}

			//	for (int i = 0; i < 10; i++)
			//	{
			//		if (stage1.moveFlag3 == 0)
			//		{
			//			if (i < 5)
			//			{
			//				stage1.moveblockX3[i] = 32 * 6 + PLAYER_R + 32 * i;
			//				stage1.moveblockY3[i] = 32 * 28 + PLAYER_R - 32 * i;
			//			}
			//			else
			//			{
			//				stage1.moveblockX3[i] = 32 * 21 + PLAYER_R + 32 * (i-5);
			//				stage1.moveblockY3[i] = 32 * 19 + PLAYER_R - 32 * (i-5);
			//			}
			//			if (i == 9)
			//			{
			//				stage1.moveFlag3 = 1;
			//			}
			//			
			//		}
			//		if (stage1.moveFlag3 == 1)
			//		{
			//			if (change % 2 == 1)
			//			{
			//				stage1.moveVelY[i] = -stage1.moveVelY[i];
			//				stage1.kakudo = 0;
			//			}

			//			if (change % 2 == 0)
			//			{
			//				stage1.kakudo = DX_PI_F;
			//				stage1.moveVelY[i] = stage1.moveVelY[i];
			//			}
			//			stage1.moveblockY3[i] += stage1.moveVelY[i];
			//			if (stage1.HIT(stage1.moveblockX3[i] - PLAYER_R + 1, stage1.moveblockY3[i] + PLAYER_R + stage1.moveVelY[i] - 1, sute) >= 1 ||
			//				stage1.HIT(stage1.moveblockX3[i] + PLAYER_R - 1, stage1.moveblockY3[i] + PLAYER_R + stage1.moveVelY[i] - 1, sute) >= 1)
			//			{
			//				kirikae = 0;
			//				stage1.moveSpeed[i] = 0;
			//				stage1.moveT[i] = 1;
			//				stage1.moveVelY[i] = 0.1;
			//				stage1.moveblockY3[i] = (int)(stage1.moveblockY3[i] / BLOCK_SIZE) * BLOCK_SIZE + PLAYER_R;
			//			}
			//			if (stage1.HIT(stage1.moveblockX3[i] - PLAYER_R + 1, stage1.moveblockY3[i] - PLAYER_R + stage1.moveVelY[i] + 1, sute) >= 1 ||
			//				stage1.HIT(stage1.moveblockX3[i] + PLAYER_R - 1, stage1.moveblockY3[i] - PLAYER_R + stage1.moveVelY[i] + 1, sute) >= 1)
			//			{
			//				kirikae = 1;
			//				stage1.moveSpeed[i] = 0;
			//				stage1.moveT[i] = 1;
			//				stage1.moveVelY[i] = 0.1;
			//				stage1.moveblockY3[i] = (int)(stage1.moveblockY3[i] / BLOCK_SIZE) * BLOCK_SIZE + PLAYER_R;
			//			}



			//			DrawRotaGraph(stage1.moveblockX3[i] + randX, stage1.moveblockY3[i] + randY, 1.0f, stage1.kakudo, load.gHandle[3], TRUE);
			//		}
			//	}
				//aitemu
				for (int i = 0; i < 7; i++)
				{
					if (stage1.aitemuFlag6[i] == 0)
					{
						if (i < 2)
						{
							stage1.aitemuX6[i] = 32*10 + PLAYER_R + (32* i);
							stage1.aitemuY6[i] = 32 * 14;
						}
						else if (i < 4)
						{
							stage1.aitemuX6[i] = 32 * 20 + PLAYER_R + (32 * i);
							stage1.aitemuY6[i] = 32 * 14;
						}
						else
						{
							stage1.aitemuX6[i] = 32 * 31 + PLAYER_R + (32 * (i-5));
							stage1.aitemuY6[i] = 32 * 9 + PLAYER_R;
						}
							DrawGraph(stage1.aitemuX6[i] - PLAYER_R + randX, stage1.aitemuY6[i] - PLAYER_R + randY, load.GH6[aitemCount / HAYASA], TRUE);
					}
				}

				//aitemuとの当たり判定
				for (int i = 0; i < 7; i++)
				{
					if (stage1.aitemuFlag6[i] == 0)
					{
						if (HIT(player.posX, player.posY, stage1.aitemuX6[i], stage1.aitemuY6[i], PLAYER_R) == true)
						{
							agpFlag = 1;
							aitemugetFlag = 1;
							//change++;
							player.gravityUpdate();
							stage1.aitemuFlag6[i] = 1;
						}
					}
				}
				break;
			case 3:
				//動くブロック

				for (int i = 0; i < MOVEBLOCK_MAX; i++)
				{
					if (stage1.moveT[i] <= GRAVITY_MAX)
					{
						stage1.moveSpeed[i] += 0.08;
						stage1.moveT[i] += 0.02 * stage1.moveSpeed[i];

					}
					stage1.moveVelY[i] = player.gravity * stage1.moveT[i];
				}

				for (int i = 0; i < MOVEBLOCK_MAX; i++)
				{
					if (Flag == 0)
					{
						stage1.moveblockX[i] = 192 + PLAYER_R + 32 * i;
						if (i < 10)
						{
							stage1.moveblockY[i] = 816;
						}
						else if (i < 15)
						{
							stage1.moveblockY[i] = 560;
						}
						else if (i < 20)
						{
							stage1.moveblockY[i] = 720;
						}
						else if (i < 25)
						{
							stage1.moveblockY[i] = 624;
						}
						if (i == 25)
						{
							stage1.moveblockY[i] = 300;
							Flag = 1;
						}
					}
					if (Flag == 1)
					{
						if (change % 2 == 1)
						{
							stage1.moveVelY[i] = -stage1.moveVelY[i];
							stage1.kakudo = 0;
						}

						if (change % 2 == 0)
						{
							stage1.kakudo = DX_PI_F;
							stage1.moveVelY[i] = stage1.moveVelY[i];
						}
						stage1.moveblockY[i] += stage1.moveVelY[i];
						if (stage1.HIT(stage1.moveblockX[i] - PLAYER_R + 1, stage1.moveblockY[i] + PLAYER_R + stage1.moveVelY[i] - 1, sute) >= 1 ||
							stage1.HIT(stage1.moveblockX[i] + PLAYER_R - 1, stage1.moveblockY[i] + PLAYER_R + stage1.moveVelY[i] - 1, sute) >= 1)
						{
							kirikae = 0;
							stage1.moveSpeed[i] = 0;
							stage1.moveT[i] = 1;
							stage1.moveVelY[i] = 0.1;
							stage1.moveblockY[i] = (int)(stage1.moveblockY[i] / BLOCK_SIZE) * BLOCK_SIZE + PLAYER_R;
						}
						if (stage1.HIT(stage1.moveblockX[i] - PLAYER_R + 1, stage1.moveblockY[i] - PLAYER_R + stage1.moveVelY[i] + 1, sute) >= 1 ||
							stage1.HIT(stage1.moveblockX[i] + PLAYER_R - 1, stage1.moveblockY[i] - PLAYER_R + stage1.moveVelY[i] + 1, sute) >= 1)
						{
							kirikae = 1;
							stage1.moveSpeed[i] = 0;
							stage1.moveT[i] = 1;
							stage1.moveVelY[i] = 0.1;
							stage1.moveblockY[i] = (int)(stage1.moveblockY[i] / BLOCK_SIZE) * BLOCK_SIZE + PLAYER_R;
						}



						DrawRotaGraph(stage1.moveblockX[i] + randX, stage1.moveblockY[i] + randY, 1.0f, stage1.kakudo, load.gHandle[3], TRUE);
					}
				}

				break;
			case 4:
		
				//aitemu
				for (int i = 0; i < 2; i++)
				{
					if (stage1.aitemuFlag3[i] == 0)
					{
						stage1.aitemuX3[i] = 320+ PLAYER_R+(32*12*i);
						stage1.aitemuY3[i] = (32*7) + PLAYER_R;
						DrawGraph(stage1.aitemuX3[i]-PLAYER_R + randX, stage1.aitemuY3[i] - PLAYER_R + randY, load.GH6[aitemCount/HAYASA], TRUE);
					}
				}

				//aitemuとの当たり判定
				for (int i = 0; i < 2; i++)
				{
					if (stage1.aitemuFlag3[i] == 0)
					{
						if (HIT(player.posX, player.posY, stage1.aitemuX3[i], stage1.aitemuY3[i], PLAYER_R) == true)
						{
							agpFlag = 1;
							aitemugetFlag = 1;
							//change++;
							player.gravityUpdate();
							stage1.aitemuFlag3[i] = 1;
						}
					}
				}
				break;
			case 5:

				for (int i = 0; i < 6; i++)
				{
					if (stage1.aitemuFlag4[i] == 0)
					{
						if (i <= 1)
						{
							stage1.aitemuX4[i] = 32*13 + PLAYER_R + 32 * i;
							stage1.aitemuY4[i] = 32*5 + PLAYER_R;
						}
						else if (i <= 3)
						{
							stage1.aitemuX4[i] = 32 * 19 + PLAYER_R + 32 * (i-2);
							stage1.aitemuY4[i] = 32*25 + PLAYER_R;
						}
						if (i == 4)
						{
							stage1.aitemuX4[i] = 32 * 23 + PLAYER_R;
							stage1.aitemuY4[i] = 32 * 6 + PLAYER_R;
						}
						if (i == 5)
						{
							stage1.aitemuX4[i] = 32 * 29 + PLAYER_R;
							stage1.aitemuY4[i] = 32 *6 + PLAYER_R;
						}
						DrawGraph(stage1.aitemuX4[i] - PLAYER_R + randX, stage1.aitemuY4[i] - PLAYER_R + randY, load.GH6[aitemCount / HAYASA], TRUE);
					}
					
				}
				//aitemuとの当たり判定
				for (int i = 0; i < 6; i++)
				{
					if (stage1.aitemuFlag4[i] == 0)
					{
						if (HIT(player.posX, player.posY, stage1.aitemuX4[i], stage1.aitemuY4[i], PLAYER_R) == true)
						{
							agpFlag = 1;
							aitemugetFlag = 1;
							//change++;
							player.gravityUpdate();
							stage1.aitemuFlag4[i] = 1;
						}
					}
				}
				
				break;
			case 6:
				for (int i = 0; i < 7; i++)
				{
					if (stage1.aitemuFlag[i] == 0)
					{
						if (i <=3)
						{
							stage1.aitemuX[i] = 288 + PLAYER_R + 224 * i;
							stage1.aitemuY[i] = 288 + PLAYER_R;
						}
						else if (i <=6)
						{
							stage1.aitemuX[i] = 384 + PLAYER_R + 224 * (i-4);
							stage1.aitemuY[i] = 608 + PLAYER_R;
						}
						DrawGraph(stage1.aitemuX[i]-PLAYER_R + randX, stage1.aitemuY[i]-PLAYER_R + randY, load.GH6[aitemCount / HAYASA], TRUE);
					}
				}

				//aitemuとの当たり判定
				for (int i = 0; i < 7; i++)
				{
					if (stage1.aitemuFlag[i] == 0)
					{
						if (HIT(player.posX, player.posY, stage1.aitemuX[i], stage1.aitemuY[i], PLAYER_R) == true)
						{
							agpFlag = 1;
							aitemugetFlag = 1;
							//change++;
							player.gravityUpdate();
							stage1.aitemuFlag[i] = 1;
						}
					}
				}
				break;
			case 7:
				for (int i = 0; i < 9; i++)
				{
					if (stage1.aitemuFlag2[i] == 0)
					{
						if (i == 0)
						{
							stage1.aitemuX2[i] = 32*13 + PLAYER_R;
							stage1.aitemuY2[i] = 32*23 + PLAYER_R;
						}
						if (i == 1)
						{
							stage1.aitemuX2[i] = 32 * 29 + PLAYER_R;
							stage1.aitemuY2[i] = 32 * 25 + PLAYER_R;
						}
						if (i == 2)
						{
							stage1.aitemuX2[i] = 32 * 30 + PLAYER_R;
							stage1.aitemuY2[i] = 32 * 19 + PLAYER_R;
						}
						if (i == 3)
						{
							stage1.aitemuX2[i] = 32 * 6 + PLAYER_R;
							stage1.aitemuY2[i] = 32 * 15 + PLAYER_R;
						}
						if (i == 4)
						{
							stage1.aitemuX2[i] = 32 * 10 + PLAYER_R;
							stage1.aitemuY2[i] = 32 * 15 + PLAYER_R;
						}
						if (i == 5)
						{
							stage1.aitemuX2[i] = 32 * 8 + PLAYER_R;
							stage1.aitemuY2[i] = 32 * 12 + PLAYER_R;
						}
						if (i == 6)
						{
							stage1.aitemuX2[i] = 32 * 26 + PLAYER_R;
							stage1.aitemuY2[i] = 32 * 4 + PLAYER_R;
						}
						if (i == 7)
						{
							stage1.aitemuX2[i] = 32 * 30 + PLAYER_R;
							stage1.aitemuY2[i] = 32 * 6 + PLAYER_R;
						}
						if (i == 8)
						{
							stage1.aitemuX2[i] = 32 * 33 + PLAYER_R;
							stage1.aitemuY2[i] = 32 * 3 + PLAYER_R;
						}
						DrawGraph(stage1.aitemuX2[i]-PLAYER_R + randX, stage1.aitemuY2[i]-PLAYER_R + randY, load.GH6[aitemCount / HAYASA], TRUE);
					}
				}
				//aitemuとの当たり判定
				for (int i = 0; i < 9; i++)
				{
					if (stage1.aitemuFlag2[i] == 0)
					{
						if (HIT(player.posX, player.posY, stage1.aitemuX2[i], stage1.aitemuY2[i], PLAYER_R) == true)
						{
							agpFlag = 1;
							//change++;
							aitemugetFlag = 1;
							player.gravityUpdate();
							stage1.aitemuFlag2[i] = 1;
						}
					}
				}
				//動くブロック

				for (int i = 0; i < 5; i++)
				{
					if (stage1.moveT[i] <= GRAVITY_MAX)
					{
						stage1.moveSpeed[i] += 0.08;
						stage1.moveT[i] += 0.02 * stage1.moveSpeed[i];

					}
					stage1.moveVelY[i] = player.gravity * stage1.moveT[i];
				}

				for (int i = 0; i < 5; i++)
				{
					if (Flag4 == 0)
					{
						stage1.moveblockX2[i] = 352 + PLAYER_R + 32 * i;
						stage1.moveblockY2[i] = 192;
						
						if (i == 4)
						{
							Flag4 = 1;
						}
					}
					if (Flag4 == 1)
					{
						if (change % 2 == 1)
						{
							stage1.moveVelY[i] = -stage1.moveVelY[i];
							stage1.kakudo = 0;
						}

						if (change % 2 == 0)
						{
							stage1.kakudo = DX_PI_F;
							stage1.moveVelY[i] = stage1.moveVelY[i];
						}
						stage1.moveblockY2[i] += stage1.moveVelY[i];
						if (stage1.HIT(stage1.moveblockX2[i] - PLAYER_R + 1, stage1.moveblockY2[i] + PLAYER_R + stage1.moveVelY[i] - 1, sute) >= 1 ||
							stage1.HIT(stage1.moveblockX2[i] + PLAYER_R - 1, stage1.moveblockY2[i] + PLAYER_R + stage1.moveVelY[i] - 1, sute) >= 1)
						{
							kirikae = 0;
							stage1.moveSpeed[i] = 0;
							stage1.moveT[i] = 1;
							stage1.moveVelY[i] = 0.1;
							stage1.moveblockY2[i] = (int)(stage1.moveblockY2[i] / BLOCK_SIZE) * BLOCK_SIZE + PLAYER_R;
						}
						if (stage1.HIT(stage1.moveblockX2[i] - PLAYER_R + 1, stage1.moveblockY2[i] - PLAYER_R + stage1.moveVelY[i] + 1, sute) >= 1 ||
							stage1.HIT(stage1.moveblockX2[i] + PLAYER_R - 1, stage1.moveblockY2[i] - PLAYER_R + stage1.moveVelY[i] + 1, sute) >= 1)
						{
							kirikae = 1;
							stage1.moveSpeed[i] = 0;
							stage1.moveT[i] = 1;
							stage1.moveVelY[i] = 0.1;
							stage1.moveblockY2[i] = (int)(stage1.moveblockY2[i] / BLOCK_SIZE) * BLOCK_SIZE + PLAYER_R;
						}



						DrawRotaGraph(stage1.moveblockX2[i] + randX, stage1.moveblockY2[i] + randY, 1.0f, stage1.kakudo, load.gHandle[3], TRUE);
					}
				}

				
				break;
			case 8:
				//aitemu
				for (int i = 0; i < 8; i++)
				{
					if (stage1.aitemuFlag5[i] == 0)
					{
						if (i == 0)
						{
							stage1.aitemuX5[i] = 32 * 3 + PLAYER_R;
							stage1.aitemuY5[i] = 32 * 16 + PLAYER_R;
						}
						if (i == 1)
						{
							stage1.aitemuX5[i] = 32 * 13 + PLAYER_R;
							stage1.aitemuY5[i] = 32 * 19 + PLAYER_R;
						}
						if (i == 2)
						{
							stage1.aitemuX5[i] = 32 * 24 + PLAYER_R;
							stage1.aitemuY5[i] = 32 * 20 + PLAYER_R;
						}
						if (i == 3)
						{
							stage1.aitemuX5[i] = 32 * 32 + PLAYER_R;
							stage1.aitemuY5[i] = 32 * 19 + PLAYER_R;
						}
						if (i == 4)
						{
							stage1.aitemuX5[i] = 32 * 36 + PLAYER_R;
							stage1.aitemuY5[i] = 32 * 25 + PLAYER_R;
						}
						if (i == 5)
						{
							stage1.aitemuX5[i] = 32 * 37 + PLAYER_R;
							stage1.aitemuY5[i] = 32 * 6 + PLAYER_R;
						}
						if (i == 6)
						{
							stage1.aitemuX5[i] = 32 * 33 + PLAYER_R;
							stage1.aitemuY5[i] = 32 * 11 + PLAYER_R;
						}
						if (i == 7)
						{
							stage1.aitemuX5[i] = 32 * 29 + PLAYER_R;
							stage1.aitemuY5[i] = 32 * 5 + PLAYER_R;
						}
						DrawGraph(stage1.aitemuX5[i] - PLAYER_R + randX, stage1.aitemuY5[i] - PLAYER_R + randY, load.GH6[aitemCount / HAYASA], TRUE);
					}
				}

				//aitemuとの当たり判定
				for (int i = 0; i < 8; i++)
				{
					if (stage1.aitemuFlag5[i] == 0)
					{
						if (HIT(player.posX, player.posY, stage1.aitemuX5[i], stage1.aitemuY5[i], PLAYER_R) == true)
						{
							agpFlag = 1;
							aitemugetFlag = 1;
							//change++;
							player.gravityUpdate();
							stage1.aitemuFlag5[i] = 1;
						}
					}
				}
				break;
			case 9:
				DrawGraph(WIN_WIDTH/2-640+randX, WIN_HEIGHT/2-104+randY,load.GH10, TRUE);
				//花火
				if (Scene == 0)
				{
					for (int i = 0; i < MAX_HANABI; i++)
						if (hanabi[i].hFlag == 1)
							hanabi[i].hFlag = 0;
					if (Count >= GetRand(500))
					{
						ALPHA2 = 255;
						x2 = GetRand(WIN_WIDTH - 500) + 250;
						y2 = WIN_HEIGHT;
						r = 20;
						hanabi[0].hanabiSpeed = GetRand(30) + 10;
						R = GetRand(105) + 150;
						G = GetRand(105) + 150;
						B = GetRand(105) + 150;
						Scene = 1;
					}
					Count += 1;
				}

				else if (Scene == 1)
				{
					y2 -= hanabi[0].hanabiSpeed;
					r -= 0.1;
					ALPHA2 -= 10;

					if (ALPHA2 <= 0)
						Scene = 2;
				}

				else if (Scene == 2)
				{
					for (int i = 0; i < MAX_HANABI; i++)
					{
						if (hanabi[i].hFlag == 0)
						{
							hanabi[i].hspeed = (float)GetRand(50) / 10 + 2;
							hanabi[i].hangle = (float)GetRand(359) / 180.0f * DX_PI_F;
							hanabi[i].hALPHA = 255;
							hanabi[i].hX = x2;
							hanabi[i].hY = y2;
							hanabi[i].hFlag = 1;
							//break;
						}
					}

					for (int i = 0; i < MAX_HANABI; i++)
					{
						if (hanabi[i].hFlag == 1)
						{
							hanabi[i].hX += hanabi[i].hspeed * cos(hanabi[i].hangle);
							hanabi[i].hY += hanabi[i].hspeed * sin(hanabi[i].hangle);
							hanabi[i].hALPHA -= 10;
							if (hanabi[i].hALPHA <= 0)
							{
								Count = 0;
								Scene = 0;
							}

						}
					}
				}
				/*描画処理*/
				if (Scene == 1)
				{
					DrawCircle(x2, y2, r, GetColor(R, G, B), TRUE);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, ALPHA2);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}

				else if (Scene == 2)
				{
					for (int i = 0; i < MAX_HANABI; i++)
					{
						if (hanabi[i].hFlag == 1)
						{
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, hanabi[i].hALPHA);
							DrawCircle(hanabi[i].hX, hanabi[i].hY, 10, GetColor(R, G, B), TRUE);
							SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
						}
					}
				}

				//rasuto
				if (stage1.HIT(player.posX - PLAYER_R + 1, player.posY - PLAYER_R + 1, sute) == 10 ||
					stage1.HIT(player.posX + PLAYER_R - 1, player.posY - PLAYER_R + 1, sute) == 10 ||
					stage1.HIT(player.posX - PLAYER_R + 1, player.posY + PLAYER_R - 1, sute) == 10 ||
					stage1.HIT(player.posX + PLAYER_R - 1, player.posY + PLAYER_R - 1, sute) == 10 ||
					stage1.HIT(player.posX - PLAYER_R + 1, player.posY - PLAYER_R + 1, sute) == 11 ||
					stage1.HIT(player.posX + PLAYER_R - 1, player.posY - PLAYER_R + 1, sute) == 11 ||
					stage1.HIT(player.posX - PLAYER_R + 1, player.posY + PLAYER_R - 1, sute) == 11 ||
					stage1.HIT(player.posX + PLAYER_R - 1, player.posY + PLAYER_R - 1, sute) == 11)
				{
					Flag4 = 0;
					Flag = 0;
					sute = 1;
					change = 0;
					player.update();
					titleFlag = 0;
				}
				break;
			}
			//画面揺れ
			if (groundFlag == 0)
			{
				randTimer = 0;
			}

			//jampパーティクル
			if (jampParticle[0].countFlag == 1)
				jampParticle[0].count++;

			if (jampParticle[0].countFlag == 1)
			{
				SetDrawBright(255, 255, 255);
				if (jampParticle[0].count < 300)
				{
					for (int i = 0; i < 100; i++)
					{
						if (jampParticle[i].Flag == 0)
						{
							jampParticle[i].speedX = (float)(GetRand(RAND_MAX) % 101 - 50) / 10;
							jampParticle[i].speedY = (float)(GetRand(RAND_MAX) % 31 / 10) + 5;
							jampParticle[i].ALPHA = 255;
							jampParticle[i].x = player.posX;
							jampParticle[i].y = player.posY;
							jampParticle[i].Flag = 1;
							jampParticle[i].ExtRate = 0.7;
							break;
						}
					}

					for (int i = 0; i < 100; i++)
					{
						if (jampParticle[i].Flag == 1)
						{
							if (jampParticle[i].ExtRate > 0)
							{
								jampParticle[i].ExtRate -= 0.05;
							}
							jampParticle[i].x += jampParticle[i].speedX;
							if (change % 2 == 0)
							{
								jampParticle[i].y -= jampParticle[i].speedY;
							}
							if (change % 2 == 1)
							{
								jampParticle[i].y += jampParticle[i].speedY;
							}
							if (jampParticle[i].ALPHA <= 0)
								jampParticle[i].Flag = 0;
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, jampParticle[i].ALPHA -= 5);
							//DrawCircle(jampParticle[i].x, jampParticle[i].y, jampParticle[i].ExtRate, GetColor(220, 220, 50), TRUE);
							if (groundFlag == 0)
							{
								DrawRotaGraph(jampParticle[i].x, jampParticle[i].y, jampParticle[i].ExtRate, 0, load.gHandle[4], TRUE);

							}
							if (player.gameoverFlag == 0 && groundFlag == 1 && fade.Flag == 0)
							{
								DrawRotaGraph(jampParticle[i].x, jampParticle[i].y, jampParticle[i].ExtRate, 0, load.gHandle[0], TRUE);
							}
							
						}
					}
				}
			}
			
			////aitemu取った時のパーティクル
			//for (int i = 0; i < MAX_ARRAY; i++)
			//{
			//	if (ap[i].apFlag == 0)
			//		{
			//			if (agpFlag == 1)
			//			{
			//				ap[i].apaliveCount = 1;
			//				ap[i].apspeed = GetRand(100) / 10 + 5;
			//				ap[i].apangle = -(GetRand(60) + 60) / 180.0f * DX_PI_F;
			//				ap[i].apALPHA = 255;
			//				ap[i].apX = player.posX;
			//				ap[i].apY = player.posY;
			//				ap[i].apExtRate = 3;
			//				ap[i].apFlag = 1;
			//				//break;
			//			}
			//		}
			//}

			//for (int i = 0; i < MAX_ARRAY; i++)
			//{
			//	if (ap[i].apFlag == 1)
			//	{
			//		ap[i].apaliveCount++;
			//		ap[i].apExtRate -= 0.01;
			//		ap[i].apgravity = ap[i].apaliveCount * acceleration;
			//		if (ap[i].apspeed > 0)
			//			ap[i].apspeed -= 0.2;
			//		ap[i].apX += ap[i].apspeed * cos(ap[i].apangle);
			//		ap[i].apY += ap[i].apspeed * sin(ap[i].apangle) + ap[i].apgravity;
			//		if (ap[i].apALPHA == 0)
			//			ap[i].apFlag = 0;
			//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, ap[i].apALPHA -= 15);
			//		DrawRotaGraph(ap[i].apX, ap[i].apY, ap[i].apExtRate, 0, load.GH5, TRUE);
			//	}
			//}

			// 処理
			for (int i = 0; i < MAX_ARRAY; i++)
			{
				if (particle[i].Flag == 0)
					if (groundFlag==1&&pCount==1)
					{
						particle[i].aliveCount = 1;
						particle[i].speed = GetRand(100) / 10 + 5;
						particle[i].angle = (GetRand(180) + 180) / 180.0f * DX_PI_F;
						particle[i].ALPHA = 255;
						particle[i].x = player.posX;
						particle[i].y = player.posY;
						particle[i].Flag = 1;
						//break;
					}
			}

			for (int i = 0; i < MAX_ARRAY; i++)
			{
				if (particle[i].Flag == 1)
				{
					particle[i].aliveCount++;
					particle[i].gravity = particle[i].aliveCount * acceleration;
					if (particle[i].speed > 0)
						particle[i].speed -= 0.5;
					if (rotationFlag == 1)
					{
						particle[i].x -= particle[i].speed * cos(particle[i].angle);
						particle[i].y -= particle[i].speed * sin(particle[i].angle) + particle[i].gravity;
					}

					if (rotationFlag == 0)
					{
						particle[i].x += particle[i].speed * cos(particle[i].angle);
						particle[i].y += particle[i].speed * sin(particle[i].angle) + particle[i].gravity;
					}

					if (particle[i].y >= WIN_HEIGHT || particle[i].y <= 0)
						particle[i].Flag = 0;
					SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, particle[i].ALPHA -= 5);
					DrawRotaGraph(particle[i].x, particle[i].y, 0.5, 0, load.gHandle[0], TRUE);
					SetDrawBright(255, 255, 255);
				}
			}

			//死亡パーティクル
			if (player.gameoverFlag == 1)
			{
				for (int i = 0; i < 200; i++)
				{
					if (death[i].Flag == 0)
					{
						death[i].speed = (float)GetRand(50) / 20 + 2;
						death[i].angle = (float)GetRand(359) / 180.0f * DX_PI_F;
						death[i].ALPHA = 255;
						death[i].x = player.posX;
						death[i].y = player.posY;
						death[i].Flag = 1;
						death[i].ExtRate = 1;
						//break;
					}
				}
			}

			for (int i = 0; i < 200; i++)
			{
				if (death[i].Flag == 1)
				{
					death[i].x += death[i].speed * cos(death[i].angle);
					death[i].y += death[i].speed * sin(death[i].angle);
					death[i].ExtRate -= 0.02;
					death[i].x += death[i].speedX;
					death[i].y += death[i].speedY;
					if (savesitakaFlag == 0)
					{
						player.update();
						if (sute == 10)
						{
							player.uraUpdate();
						}
					}
					if (savesitakaFlag == 1)
					{
						player.posX=savepointX;
						player.posY = savepointY;
					}
					if (death[i].ALPHA <= 0)
					{
						death[i].Flag = 0;
						player.gameoverFlag = 0;
					}
					SetDrawBright(255, 255, 255);
					SetDrawBlendMode(DX_BLENDMODE_ADD, death[i].ALPHA -= 10);
					DrawRotaGraph(death[i].x, death[i].y, death[i].ExtRate, 1, load.GH2, TRUE);
				}
			}
			//重力切り替えできるかどうか
			if (groundFlag)
			{
				if ((keys[KEY_INPUT_SPACE] == true && oldkeys[KEY_INPUT_SPACE] == false) ||
					(input.Buttons[XINPUT_BUTTON_A] && !oldinput.Buttons[XINPUT_BUTTON_A]))
				{
					if (change % 2 == 0)
					{
						PlaySoundMem(load.SHandle7, DX_PLAYTYPE_BACK, TRUE);
					}

					if (change % 2 == 1)
					{
						PlaySoundMem(load.SHandle6, DX_PLAYTYPE_BACK);
					}

					player.gravityUpdate();
					change++;
					pCount = 0;
					groundFlag = 0;
				}
			}

			SetDrawBright(255, 255, 255);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			DrawGraph(184, 184, load.GH, TRUE);
			if (groundFlag == 0)
			{
				DrawRotaGraph(player.posX + randX, player.posY + randY, player.size, player.rotation, load.gHandle[4], TRUE);

			}
			if (player.gameoverFlag == 0 && groundFlag == 1&&fade.Flag ==0 )
			{
				DrawRotaGraph(player.posX+randX, player.posY+randY, player.size, player.rotation, load.gHandle[0], TRUE);
			}


			//UI
			if (CheckHitKeyAll() == 0&&
				!(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT)&&
				!(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT)&&
				!input.Buttons[XINPUT_BUTTON_A])
			{
				sousaTimer++;
			}
			else
			{
				sousaTimer = 0;
				sousaFlag = 1;
			}
			if (sousaFlag == 1)
			{
				sukuY-=5;
				if (sukuY <= 0)
				{
					sukuY = 0;
					sousaFlag = 0;
				}
			}
			if (sousaTimer > 240&&sousaFlag == 0)
			{
				sukuY++;
				if (sukuY >= 543)
				{
					sukuY = 543;
				}
			}
			uiCount++;
			if (uiCount >= 2 * UI)
			{
				uiCount = 0;
			}
				DrawGraph(WIN_WIDTH / 2 - 138+randX, 0 - 543+sukuY+randY, load.GH12[uiCount/UI], TRUE);

			DrawRotaGraph(fade.X, fade.Y, fade.Extrate, fade.Angle, load.GH7, TRUE);
		}
		//checkpoint
		DrawGraph(checkX - 336, checkY - 56, saveGraph, TRUE);

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();	

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dxライブラリ終了処理
	InitSoundMem();
	InitGraph();
	DxLib_End();
	// 正常終了
	return 0;
}