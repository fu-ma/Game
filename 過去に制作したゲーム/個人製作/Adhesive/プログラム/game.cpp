//初見殺しゲーム、スティックのりとボンドの戦い



//明日やることー＞XBOXコントローラーのボタン対応させる


#include "DxLib.h"
#include "math.h"
#include "time.h"
#define playerAnime 10
#define enemyAnime 10
#define bakuhatuAnime 13
#define taikiAnime 13

const char TITLE[] = "K020G1170塩川風舞：Adhesive";

const int WIN_WIDTH = 800; //ウィンドウ横幅
const int WIN_HEIGHT = 600;//ウィンドウ縦幅

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);						//ウィンドウモードに設定
	//ウィンドウサイズを手動では変更できず、かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);// タイトルを変更
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);	//画面サイズの最大サイズ、カラービット数を設定（モニターの解像度に合わせる）
	SetWindowSizeExtendRate(1.0);				//画面サイズを設定（解像度との比率で設定）
	SetBackgroundColor(0, 255, 0);		// 画面の背景色を設定する

	//Dxライブラリの初期化
	if (DxLib_Init() == -1) { return -1; }

	//（ダブルバッファ）描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	//画像などのリソースデータの変数宣言と読み込み

	int GHandle1[playerAnime];//プレイヤーの連番画像の枚数指定
	int GHandle2[enemyAnime];//エネミーの連番画像の枚数指定
	int GHandle3;//弾の画像変数の初期化
	int GHandle4;
	int GHandle5[bakuhatuAnime];
	int GHandle6;
	int GHandle7;
	int GHandle8;
	int GHandle9;
	int GHandle10;
	int GHandle11;
	int GHandle12;
	int GHandle13;
	int GHandle14;
	int GHandle15;
	int GHandle16;
	int GHandle17[taikiAnime];
	int GHandle18;
	int GHandle19;
	GHandle3 = LoadGraph("bol.png");//画像の読み込み
	GHandle4 = LoadGraph("fukidasi.png");//吹き出しの読み込み
	GHandle6 = LoadGraph("taitoru1.png");
	GHandle7 = LoadGraph("sukoa2.png");
	GHandle8 = LoadGraph("aitemu.png");
	GHandle9 = LoadGraph("taitoru3.png");
	GHandle10 = LoadGraph("enemy2.png");
	GHandle11 = LoadGraph("C.png");
	GHandle12 = LoadGraph("B.png");
	GHandle13 = LoadGraph("A.png");
	GHandle14 = LoadGraph("S.png");
	GHandle15 = LoadGraph("kabe.png");
	GHandle16 = LoadGraph("SS.png");
	GHandle18 = LoadGraph("setumei.png");
	GHandle19 = LoadGraph("hassya.png");

	LoadDivGraph("playersheet.png", 10, 10, 1, 64, 64, GHandle1);//連番画像の読み込み
	LoadDivGraph("enemy-sheet.png", 10, 10, 1, 64, 64, GHandle2);//連番画像の読み込み
	LoadDivGraph("bakuhatu-sheet.png", 13, 13, 1, 128, 128, GHandle5);
	LoadDivGraph("taiki.png", 13, 13, 1, 64, 64, GHandle17);

	//ゲームループで使う変数の宣言
	char keys[256] = { 0 }; //最新のキーボード情報用
	char oldkeys[256] = { 0 };//1ループ（フレーム）前のキーボード情報

	//プレイヤーの中心のx座標

	VECTOR position1 = VGet(400, 500, 0);
	const int mokkouyoubondo = 10;
	int r = 32;//プレイヤーの半径
	int playerVel = 5;
	int bulR = 8;//弾の半径
	int aitemuX = WIN_WIDTH / 2;//敵の中心座標は中心（x座標）;
	int aitemuY = 0;
	int aitemuR = 16;
	int enemyX = WIN_WIDTH / 2;//敵の中心座標は中心（x座標）
	int enemyX2 = 164;
	int enemyY = 50;//エネミーの中心のy座標
	int enemyY2 = 64;
	int enemyR = 32;//エネミーの半径
	int enemyR2 = 64;
	int enemyVelX = 10;//エネミーの速さ
	int enemyVelY = 5;
	int isEnemyAlive1 = 1;//エネミーが生きているか死んでいるか
	int isEnemyAlive2 = 1;
	int isEnemyAlive3 = 1;
	int isPlayerAlive = 1;//プレイヤーが生きているか死んでいるか
	int i = 0;
	int menuFlag = 0;
	int ClearFlag = 0;
	int SHandle2;
	int SHandle3;
	int SHandle4;
	int SHandle5;
	int SHandle6;
	int roopFlag = 0;
	int sukoa = 0;
	int t = 0;//敵の配列の総数
	int p = 0;//プレイヤーの画像の配列数
	int bomFlag = 0;//爆発したか
	int enemyTimer = 120;//敵の復活するタイマー
	int enemyLife1 = mokkouyoubondo;//モブキャラの体力
	int enemyLife2 = 250;//ボスの体力
	int playerLife = 100;//プレイヤーの体力
	int random = 0;//エネミーのランダム変数
	int aitemuFlag = 0;//アイテムが出たか
	int aitemuVel = 5;//アイテムの出てくる速さ
	int atariFlag = 0;//プレイヤーが死んだ以降の当たり判定をなくす
	int shotFlag = 0;//３wayになるか
	int backgroundY1 = 0;//背景
	int backgroundVel1 = 2;//背景の速さ
	int backgroundY2 = backgroundY1 - 600;//２枚目の背景
	int backgroundVel2 = 2;//2枚目の背景の速さ
	int wall = 0;//壁
	int wallVel = 2;//壁の速さ
	int shotTime = 60;//３wayになる秒数
	int waitFlag = 0;//待機アニメーションか移動アニメーションかを切り替える
	int wait = 0;//待機アニメーション
	int houdaiX = 400;
	int houdaiY = 20;
	int houdaiR = 20;
	int tamaFlag = 0;
	int tamaFlag2 = 0;
	int tamaFlag3 = 0;
	int tamaFlag4 = 0;
	int tamaFlag5 = 0;
	int tamaFlag6 = 0;
	int tamaFlag7 = 0;
	int tamaFlag8 = 0;
	int tamaFlag9 = 0;
	int tamaFlag10 = 0;
	int tamaFlag11 = 0;
	int tamaFlag12 = 0;
	int tamaFlag13 = 0;
	int tamaFlag14 = 0;
	int tamaFlag15 = 0;
	int tamaFlag16 = 0;
	int tamaFlag17 = 0;
	int tamaFlag18 = 0;
	int tamaFlag19 = 0;
	int tamaFlag20 = 0;
	int tamaFlag21 = 0;
	int tamaFlag22 = 0;
	int tamaFlag23 = 0;
	int tamaFlag24 = 0;
	int tamaFlag25 = 0;
	int tamaFlag26 = 0;
	int tamaFlag27 = 0;
	int tamaFlag28 = 0;
	int tamaFlag29 = 0;
	int tamaFlag30 = 0;
	int tamaR = 5;
	int istamaletAlive = 1;
	int tamaX1 = 0, tamaY1 = 0;//弾幕
	int tamaX2 = 0, tamaY2 = 0;
	int tamaX3 = 0, tamaY3 = 0;
	int tamaX4 = 0, tamaY4 = 0;
	int tamaX5 = 0, tamaY5 = 0;
	int tamaX6 = 0, tamaY6 = 0;
	int tamaX7 = 0, tamaY7 = 0;
	int tamaX8 = 0, tamaY8 = 0;
	int tamaX9 = 0, tamaY9 = 0;
	int tamaX10 = 0, tamaY10 = 0;
	int tamaX11 = 0, tamaY11 = 0;
	int tamaX12 = 0, tamaY12 = 0;
	int tamaX13 = 0, tamaY13 = 0;
	int tamaX14 = 0, tamaY14 = 0;
	int tamaX15 = 0, tamaY15 = 0;
	int tamaX16 = 0, tamaY16 = 0;
	int tamaX17 = 0, tamaY17 = 0;
	int tamaX18 = 0, tamaY18 = 0;
	int tamaX19 = 0, tamaY19 = 0;
	int tamaX20 = 0, tamaY20 = 0;
	int tamaX21 = 0, tamaY21 = 0;
	int tamaX22 = 0, tamaY22 = 0;
	int tamaX23 = 0, tamaY23 = 0;
	int tamaX24 = 0, tamaY24 = 0;
	int tamaX25 = 0, tamaY25 = 0;
	int tamaX26 = 0, tamaY26 = 0;
	int tamaX27 = 0, tamaY27 = 0;
	int tamaX28 = 0, tamaY28 = 0;
	int tamaX29 = 0, tamaY29 = 0;
	int tamaX30 = 0, tamaY30 = 0;
	int wakaran = 0;//正規化
	int nextFlag = 0;
	const int dansuu = 10;//弾数
	int rensyaX[dansuu] = { 0 };//連射
	int rensyaX2[dansuu] = { 0 };
	int rensyaX3[dansuu] = { 0 };
	int rensyaY[dansuu] = { 0 };
	int rensyaY2[dansuu] = { 0 };
	int rensyaY3[dansuu] = { 0 };
	int bulMax = dansuu;
	int vel = 5;
	int isBullFlag[dansuu] = { 0 };
	int isBullFlag2[dansuu] = { 0 };
	int isBullFlag3[dansuu] = { 0 };
	int kazu = 120;
	int kazu2 = 120;
	int kazu3 = 120;
	int Timer = kazu;
	int Timer2 = kazu;
	int Timer3 = kazu;
	int sibouFlag = 0;
	int GameoverTimer = 0;

	srand(time(NULL));



	SHandle2 = LoadSoundMem("bakuhatu.wav");
	SHandle3 = LoadSoundMem("bul.mp3");
	SHandle4 = LoadSoundMem("sentou.mp3");
	SHandle5 = LoadSoundMem("Gameover.mp3");
	SHandle6 = LoadSoundMem("kuria.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, SHandle2);
	ChangeVolumeSoundMem(255 * 50 / 100, SHandle3);
	ChangeVolumeSoundMem(255 * 50 / 100, SHandle4);
	ChangeVolumeSoundMem(255 * 50 / 100, SHandle5);
	ChangeVolumeSoundMem(255 * 50 / 100, SHandle6);

	// ゲームループ
	while (1)
	{
		//最新のキーボード情報だったものは１フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		//最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		//画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//



		int posX1 = position1.x - r;
		int posY1 = position1.y - r;
		int posX2 = position1.x + r;
		int posY2 = position1.y + r;

		//背景処理
		DrawGraph(0, backgroundY1, GHandle9, TRUE);
		DrawRotaGraph(0 + 400, backgroundY2 + 300, 1.0f, DX_PI_F / 1.0, GHandle9, TRUE);
		DrawGraph(700, wall, GHandle15, TRUE);
		DrawGraph(700, wall - 600, GHandle15, TRUE);
		DrawGraph(0, wall, GHandle15, TRUE);
		DrawGraph(0, wall - 600, GHandle15, TRUE);
		DrawGraph(0, 500, GHandle18, TRUE);
		DrawGraph(0, 400, GHandle19, TRUE);
		backgroundY1 += backgroundVel1;
		backgroundY2 += backgroundVel2;
		wall += wallVel;
		if (backgroundY1 >= 600)
		{
			backgroundY1 = -600;
		}
		if (backgroundY2 >= 600)
		{
			backgroundY2 = -600;
		}
		if (wall >= 600)
		{
			wall = 0;
		}

		if (menuFlag == 0)
		{
			ChangeFont("ＭＳ 明朝");
			clsDx();
			SetFontSize(64);//フォントのサイズを６４に設定
			DrawGraph(250, 300, GHandle6, TRUE);
			SetFontSize(32);
			DrawString(250, 400 - 16, "～のりとボンドの戦い～\n", GetColor(50, 100, 100), FALSE);//文字列を真ん中に表示
			DrawString(250, 500 - 16, "Sでスタート", GetColor(50, 50, 255), FALSE);//文字列を真ん中に表示
			enemyTimer = 120;
			isEnemyAlive1 = 1;
			isEnemyAlive2 = 1;
			isEnemyAlive3 = 1;
			sukoa = 0;
			bomFlag = 0;
			playerLife = 100;
			position1.x = 400;//x座標を元に戻す
			position1.y = 500;//ｙ座標を元に戻す
			enemyX = WIN_WIDTH / 2;//敵の中心座標は中心（x座標）
			enemyY = 50;//エネミーの中心のy座標
			enemyR = 20;//エネミーの半径
			t = 0;
			aitemuFlag = 0;
			shotFlag = 0;
			enemyX2 = 164;
			enemyY2 = 64;
			enemyR2 = 64;
			enemyVelX = 10;
			nextFlag = 0;
			enemyLife1 = mokkouyoubondo;
			enemyLife2 = 250;
			shotTime = 60;
			sibouFlag = 0;
			tamaFlag = 0;
			tamaFlag2 = 0;
			tamaFlag3 = 0;
			tamaFlag4 = 0;
			tamaFlag5 = 0;
			tamaFlag6 = 0;
			tamaFlag7 = 0;
			tamaFlag8 = 0;
			tamaFlag9 = 0;
			tamaFlag10 = 0;
			tamaFlag11 = 0;
			tamaFlag12 = 0;
			tamaFlag13 = 0;
			tamaFlag14 = 0;
			tamaFlag15 = 0;
			tamaFlag16 = 0;
			tamaFlag17 = 0;
			tamaFlag18 = 0;
			tamaFlag19 = 0;
			tamaFlag20 = 0;
			tamaFlag21 = 0;
			tamaFlag22 = 0;
			tamaFlag23 = 0;
			tamaFlag24 = 0;
			tamaFlag25 = 0;
			tamaFlag26 = 0;
			tamaFlag27 = 0;
			tamaFlag28 = 0;
			tamaFlag29 = 0;
			tamaFlag30 = 0;
			GameoverTimer++;
		}
		if (GameoverTimer == 1)
		{
			PlaySoundMem(SHandle4, DX_PLAYTYPE_LOOP);
		}
		if (ClearFlag == 1)
		{
			isEnemyAlive1 = 0;
			isEnemyAlive2 = 0;
			isEnemyAlive3 = 0;
			SetFontSize(64);//フォントのサイズを６４に設定
			DrawString(250, 300 - 32, "のりの勝利", GetColor(0, 0, 255), FALSE);//文字列を真ん中に表示
			DrawGraph(position1.x, position1.y - 128, GHandle4, TRUE);
			SetFontSize(12);
			DrawString(position1.x + 20, position1.y - 64,
				"接着力は劣るけど\n僕はボンドに\n負けないのり！！", GetColor(255, 255, 255), FALSE);

		}
		if (keys[KEY_INPUT_S] == 1 && oldkeys[KEY_INPUT_S] == 0 && menuFlag == 0)//もしSを押したら
		{
			sibouFlag = 1;
			menuFlag = 1;//メニューフラグを立てる
			isPlayerAlive = 1;//プレイヤーを表示
			isEnemyAlive1 = 1;
		}
		if (menuFlag == 1)//メニューフラグがたったら
		{
			DrawGraph(0, 0, GHandle7, TRUE);
			SetFontSize(20);
			DrawFormatString(0, 64, GetColor(255, 0, 255), "%d", sukoa);
			if (sibouFlag == 1)
			{
				for (int i = 0; i <= bulMax; i++)
				{
					Timer--;
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 1)
					{
						if (isBullFlag[i] == 0 && Timer <= 0)
						{
							PlaySoundMem(SHandle3, DX_PLAYTYPE_BACK);
							Timer = kazu;
							isBullFlag[i] = 1;
							rensyaX[i] = position1.x;
							rensyaY[i] = position1.y;
						}
					}
					if (isBullFlag[i] == 1)
					{
						DrawGraph(rensyaX[i] - 8, rensyaY[i] - 8, GHandle3, TRUE);
						rensyaY[i] -= 10;
						if (rensyaY[i] < 0)
						{
							isBullFlag[i] = 0;
						}
					}
				}
				for (int i = 0; i <= bulMax; i++)
				{
					Timer2--;
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 1)
					{
						if (isBullFlag2[i] == 0 && Timer2 <= 0)
						{
							PlaySoundMem(SHandle3, DX_PLAYTYPE_BACK);
							Timer2 = kazu2;
							isBullFlag2[i] = 1;
							rensyaX2[i] = position1.x;
							rensyaY2[i] = position1.y;
						}
					}
					if (isBullFlag2[i] == 1)
					{
						DrawRotaGraph(rensyaX2[i] - 8, rensyaY2[i] - 8, 1.0f, DX_PI_F / 1.5, GHandle3, TRUE);
						rensyaY2[i] -= 8;
						rensyaX2[i] -= 6;
						if (rensyaX2[i] < 100)
						{
							isBullFlag2[i] = 0;
						}
					}
				}

				for (int i = 0; i <= bulMax; i++)
				{
					Timer3--;
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 1)
					{
						if (isBullFlag3[i] == 0 && Timer3 <= 0)
						{
							PlaySoundMem(SHandle3, DX_PLAYTYPE_BACK);
							Timer3 = kazu3;
							isBullFlag3[i] = 1;
							rensyaX3[i] = position1.x;
							rensyaY3[i] = position1.y;
						}
					}
					if (isBullFlag3[i] == 1)
					{
						DrawRotaGraph(rensyaX3[i] - 8, rensyaY3[i] - 8, 1.0f, DX_PI_F / 0.75, GHandle3, TRUE);
						rensyaY3[i] -= 8;
						rensyaX3[i] += 6;
						if (rensyaX3[i] > 700)
						{
							isBullFlag3[i] = 0;
						}
					}
				}
			}

			shotTime = shotTime - 1;
			if (shotFlag == 1)
			{
				playerLife += 1;
			}

			if (shotTime == 0)
			{
				shotTime = 60;
				shotFlag = 0;
			}

			if (isEnemyAlive1 == 1)//敵
			{
				t = 0;
				DrawGraph(enemyX - enemyR, enemyY - enemyR, GHandle2[i], TRUE);
				i++;//連番画像を順次に入れ替え
				if (i == enemyAnime)
				{
					i = 0;//連番画像が最後まで映されたら最初から
				}

				enemyY += enemyVelY;//エネミーを縦に動かす

				if (enemyY + enemyR >= 664)//エネミーが画面外に出たら
				{
					enemyX = position1.x;//エネミーが横に動いていく
					enemyY = 0;//エネミーが上から出てくる
					aitemuFlag = 0;

				}
			}
			if (isEnemyAlive2 == 1)//敵
			{
				DrawGraph(enemyX2 - enemyR2, enemyY2 - enemyR2, GHandle10, TRUE);

				enemyX2 += enemyVelX;//エネミーを縦に動かす

				if (enemyX2 + enemyR2 >= 700)//エネミーが画面外に出たら
				{
					enemyVelX = -enemyVelX;
				}
				if (enemyX2 - enemyR2 <= 100)//エネミーが画面外に出たら
				{
					enemyVelX = -enemyVelX;
				}
			}

			if (isEnemyAlive3 == 1)
			{
				DrawBox(houdaiX - houdaiR, houdaiY - houdaiR, houdaiX + houdaiR, houdaiY + houdaiR, GetColor(255, 255, 255), TRUE);

				if (istamaletAlive == 1)
				{
					if (tamaFlag == 0)
					{
						if (nextFlag == 0)
						{
							tamaFlag = 1;
						}
						else
						{
							if (tamaY30 >= 50)
							{
								tamaFlag = 1;
							}
						}

						tamaX1 = houdaiX;
						tamaY1 = houdaiY;
					}
					if (tamaFlag2 == 0)
					{
						tamaX2 = houdaiX;
						tamaY2 = houdaiY;
					}
					if (tamaFlag3 == 0)
					{
						tamaX3 = houdaiX;
						tamaY3 = houdaiY;
					}
					if (tamaFlag4 == 0)
					{
						tamaX4 = houdaiX;
						tamaY4 = houdaiY;
					}
					if (tamaFlag5 == 0)
					{
						tamaX5 = houdaiX;
						tamaY5 = houdaiY;
					}
					if (tamaFlag6 == 0)
					{
						tamaX6 = houdaiX;
						tamaY6 = houdaiY;
					}
					if (tamaFlag7 == 0)
					{
						tamaX7 = houdaiX;
						tamaY7 = houdaiY;
					}
					if (tamaFlag8 == 0)
					{
						tamaX8 = houdaiX;
						tamaY8 = houdaiY;
					}
					if (tamaFlag9 == 0)
					{
						tamaX9 = houdaiX;
						tamaY9 = houdaiY;
					}
					if (tamaFlag10 == 0)
					{
						tamaX10 = houdaiX;
						tamaY10 = houdaiY;
					}
					if (tamaFlag11 == 0)
					{
						tamaX11 = houdaiX;
						tamaY11 = houdaiY;
					}
					if (tamaFlag12 == 0)
					{
						tamaX12 = houdaiX;
						tamaY12 = houdaiY;
					}
					if (tamaFlag13 == 0)
					{
						tamaX13 = houdaiX;
						tamaY13 = houdaiY;
					}
					if (tamaFlag14 == 0)
					{
						tamaX14 = houdaiX;
						tamaY14 = houdaiY;
					}
					if (tamaFlag15 == 0)
					{
						tamaX15 = houdaiX;
						tamaY15 = houdaiY;
					}
					if (tamaFlag16 == 0)
					{
						tamaX16 = houdaiX;
						tamaY16 = houdaiY;
					}
					if (tamaFlag17 == 0)
					{
						tamaX17 = houdaiX;
						tamaY17 = houdaiY;
					}
					if (tamaFlag18 == 0)
					{
						tamaX18 = houdaiX;
						tamaY18 = houdaiY;
					}
					if (tamaFlag19 == 0)
					{
						tamaX19 = houdaiX;
						tamaY19 = houdaiY;
					}
					if (tamaFlag20 == 0)
					{
						tamaX20 = houdaiX;
						tamaY20 = houdaiY;
					}
					if (tamaFlag21 == 0)
					{
						tamaX21 = houdaiX;
						tamaY21 = houdaiY;
					}
					if (tamaFlag22 == 0)
					{
						tamaX22 = houdaiX;
						tamaY22 = houdaiY;
					}
					if (tamaFlag23 == 0)
					{
						tamaX23 = houdaiX;
						tamaY23 = houdaiY;
					}
					if (tamaFlag24 == 0)
					{
						tamaX24 = houdaiX;
						tamaY24 = houdaiY;
					}
					if (tamaFlag25 == 0)
					{
						tamaX25 = houdaiX;
						tamaY25 = houdaiY;
					}
					if (tamaFlag26 == 0)
					{
						tamaX26 = houdaiX;
						tamaY26 = houdaiY;
					}
					if (tamaFlag27 == 0)
					{
						tamaX27 = houdaiX;
						tamaY27 = houdaiY;
					}
					if (tamaFlag28 == 0)
					{
						tamaX28 = houdaiX;
						tamaY28 = houdaiY;
					}
					if (tamaFlag29 == 0)
					{
						tamaX29 = houdaiX;
						tamaY29 = houdaiY;
					}
					if (tamaFlag30 == 0)
					{
						tamaX30 = houdaiX;
						tamaY30 = houdaiY;
					}

				}
				if (tamaFlag == 1)
				{
					DrawCircle(tamaX1, tamaY1, tamaR, GetColor(0, 0, 255), TRUE);
					tamaY1 += 5;
					if (tamaY1 >= 50)
					{
						tamaFlag2 = 1;
					}
					if (tamaY1 > 620)
					{
						tamaFlag = 0;
					}
				}
				if (tamaFlag2 == 1)
				{
					nextFlag = 1;
					DrawCircle(tamaX2, tamaY2, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(5 * DX_PI_F / 180) * sin(5 * DX_PI_F / 180) + cos(5 * DX_PI_F / 180) * cos(5 * DX_PI_F / 180));
					tamaX2 += wakaran;
					tamaY2 += wakaran * 5;
					if (tamaY2 >= 50)
					{
						tamaFlag3 = 1;
					}
					if (tamaY2 >= 620)
					{
						tamaFlag2 = 0;
					}
				}
				if (tamaFlag3 == 1)
				{
					DrawCircle(tamaX3, tamaY3, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(10 * DX_PI_F / 180) * sin(10 * DX_PI_F / 180) + cos(10 * DX_PI_F / 180) * cos(10 * DX_PI_F / 180));
					tamaX3 += wakaran * 2;
					tamaY3 += wakaran * 5;
					if (tamaY3 >= 50)
					{
						tamaFlag4 = 1;
					}
					if (tamaY3 >= 620)
					{
						tamaFlag3 = 0;
					}
				}
				if (tamaFlag4 == 1)
				{
					DrawCircle(tamaX4, tamaY4, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(15 * DX_PI_F / 180) * sin(15 * DX_PI_F / 180) + cos(15 * DX_PI_F / 180) * cos(15 * DX_PI_F / 180));
					tamaX4 += wakaran * 3;
					tamaY4 += wakaran * 5;
					if (tamaY4 >= 50)
					{
						tamaFlag5 = 1;
					}
					if (tamaY4 >= 620)
					{
						tamaFlag4 = 0;
					}
				}
				if (tamaFlag5 == 1)
				{
					DrawCircle(tamaX5, tamaY5, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(20 * DX_PI_F / 180) * sin(20 * DX_PI_F / 180) + cos(20 * DX_PI_F / 180) * cos(20 * DX_PI_F / 180));
					tamaX5 += wakaran * 4;
					tamaY5 += wakaran * 5;
					if (tamaY5 >= 50)
					{
						tamaFlag6 = 1;
					}
					if (tamaY5 >= 620)
					{
						tamaFlag5 = 0;
					}
				}
				if (tamaFlag6 == 1)
				{
					DrawCircle(tamaX6, tamaY6, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(25 * DX_PI_F / 180) * sin(25 * DX_PI_F / 180) + cos(25 * DX_PI_F / 180) * cos(25 * DX_PI_F / 180));
					tamaX6 += wakaran * 5;
					tamaY6 += wakaran * 5;
					if (tamaY6 >= 50)
					{
						tamaFlag7 = 1;
					}
					if (tamaY6 >= 620)
					{
						tamaFlag6 = 0;
					}
				}
				if (tamaFlag7 == 1)
				{
					DrawCircle(tamaX7, tamaY7, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(30 * DX_PI_F / 180) * sin(30 * DX_PI_F / 180) + cos(30 * DX_PI_F / 180) * cos(30 * DX_PI_F / 180));
					tamaX7 += wakaran * 6;
					tamaY7 += wakaran * 5;
					if (tamaY7 >= 50)
					{
						tamaFlag8 = 1;
					}
					if (tamaY7 >= 620)
					{
						tamaFlag7 = 0;
					}
				}
				if (tamaFlag8 == 1)
				{
					DrawCircle(tamaX8, tamaY8, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(35 * DX_PI_F / 180) * sin(35 * DX_PI_F / 180) + cos(35 * DX_PI_F / 180) * cos(35 * DX_PI_F / 180));
					tamaX8 += wakaran * 7;
					tamaY8 += wakaran * 5;
					if (tamaY8 >= 50)
					{
						tamaFlag9 = 1;
					}
					if (tamaY8 >= 620)
					{
						tamaFlag8 = 0;
					}
				}
				if (tamaFlag9 == 1)
				{
					DrawCircle(tamaX9, tamaY9, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(35 * DX_PI_F / 180) * sin(35 * DX_PI_F / 180) + cos(35 * DX_PI_F / 180) * cos(35 * DX_PI_F / 180));
					tamaX9 += wakaran * 7;
					tamaY9 += wakaran * 5;
					if (tamaY9 >= 50)
					{
						tamaFlag10 = 1;
					}
					if (tamaY9 >= 620)
					{
						tamaFlag9 = 0;
					}
				}
				if (tamaFlag10 == 1)
				{
					DrawCircle(tamaX10, tamaY10, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(30 * DX_PI_F / 180) * sin(30 * DX_PI_F / 180) + cos(30 * DX_PI_F / 180) * cos(30 * DX_PI_F / 180));
					tamaX10 += wakaran * 6;
					tamaY10 += wakaran * 5;
					if (tamaY10 >= 50)
					{
						tamaFlag11 = 1;
					}
					if (tamaY10 >= 620)
					{
						tamaFlag10 = 0;
					}
				}
				if (tamaFlag11 == 1)
				{
					DrawCircle(tamaX11, tamaY11, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(25 * DX_PI_F / 180) * sin(25 * DX_PI_F / 180) + cos(25 * DX_PI_F / 180) * cos(25 * DX_PI_F / 180));
					tamaX11 += wakaran * 5;
					tamaY11 += wakaran * 5;
					if (tamaY11 >= 50)
					{
						tamaFlag12 = 1;
					}
					if (tamaY11 >= 620)
					{
						tamaFlag11 = 0;
					}
				}
				if (tamaFlag12 == 1)
				{
					DrawCircle(tamaX12, tamaY12, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(20 * DX_PI_F / 180) * sin(20 * DX_PI_F / 180) + cos(20 * DX_PI_F / 180) * cos(20 * DX_PI_F / 180));
					tamaX12 += wakaran * 4;
					tamaY12 += wakaran * 5;
					if (tamaY12 >= 50)
					{
						tamaFlag13 = 1;
					}
					if (tamaY12 >= 620)
					{
						tamaFlag12 = 0;
					}
				}
				if (tamaFlag13 == 1)
				{
					DrawCircle(tamaX13, tamaY13, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(15 * DX_PI_F / 180) * sin(15 * DX_PI_F / 180) + cos(15 * DX_PI_F / 180) * cos(15 * DX_PI_F / 180));
					tamaX13 += wakaran * 3;
					tamaY13 += wakaran * 5;
					if (tamaY13 >= 50)
					{
						tamaFlag14 = 1;
					}
					if (tamaY13 >= 620)
					{
						tamaFlag13 = 0;
					}
				}
				if (tamaFlag14 == 1)
				{
					DrawCircle(tamaX14, tamaY14, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(10 * DX_PI_F / 180) * sin(10 * DX_PI_F / 180) + cos(10 * DX_PI_F / 180) * cos(10 * DX_PI_F / 180));
					tamaX14 += wakaran * 2;
					tamaY14 += wakaran * 5;
					if (tamaY14 >= 50)
					{
						tamaFlag15 = 1;
					}
					if (tamaY14 >= 620)
					{
						tamaFlag14 = 0;
					}
				}
				if (tamaFlag15 == 1)
				{
					DrawCircle(tamaX15, tamaY15, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(5 * DX_PI_F / 180) * sin(5 * DX_PI_F / 180) + cos(5 * DX_PI_F / 180) * cos(5 * DX_PI_F / 180));
					tamaX15 += wakaran;
					tamaY15 += wakaran * 5;
					if (tamaY15 >= 50)
					{
						tamaFlag16 = 1;
					}
					if (tamaY15 >= 620)
					{
						tamaFlag15 = 0;
					}
				}
				if (tamaFlag16 == 1)
				{
					DrawCircle(tamaX16, tamaY16, tamaR, GetColor(0, 0, 255), TRUE);
					tamaY16 += 5;
					if (tamaY16 >= 50)
					{
						tamaFlag17 = 1;
					}
					if (tamaY16 > 620)
					{
						tamaFlag16 = 0;
					}
				}
				if (tamaFlag17 == 1)
				{
					DrawCircle(tamaX17, tamaY17, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(5 * DX_PI_F / 180) * sin(5 * DX_PI_F / 180) + cos(5 * DX_PI_F / 180) * cos(5 * DX_PI_F / 180));
					tamaX17 -= wakaran;
					tamaY17 += wakaran * 5;
					if (tamaY17 >= 50)
					{
						tamaFlag18 = 1;
					}
					if (tamaY17 >= 620)
					{
						tamaFlag17 = 0;
					}
				}
				if (tamaFlag18 == 1)
				{
					DrawCircle(tamaX18, tamaY18, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(10 * DX_PI_F / 180) * sin(10 * DX_PI_F / 180) + cos(10 * DX_PI_F / 180) * cos(10 * DX_PI_F / 180));
					tamaX18 -= wakaran * 2;
					tamaY18 += wakaran * 5;
					if (tamaY18 >= 50)
					{
						tamaFlag19 = 1;
					}
					if (tamaY18 >= 620)
					{
						tamaFlag18 = 0;
					}
				}
				if (tamaFlag19 == 1)
				{
					DrawCircle(tamaX19, tamaY19, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(15 * DX_PI_F / 180) * sin(15 * DX_PI_F / 180) + cos(15 * DX_PI_F / 180) * cos(15 * DX_PI_F / 180));
					tamaX19 -= wakaran * 3;
					tamaY19 += wakaran * 5;
					if (tamaY19 >= 50)
					{
						tamaFlag20 = 1;
					}
					if (tamaY19 >= 620)
					{
						tamaFlag19 = 0;
					}
				}
				if (tamaFlag20 == 1)
				{
					DrawCircle(tamaX20, tamaY20, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(20 * DX_PI_F / 180) * sin(20 * DX_PI_F / 180) + cos(20 * DX_PI_F / 180) * cos(20 * DX_PI_F / 180));
					tamaX20 -= wakaran * 4;
					tamaY20 += wakaran * 5;
					if (tamaY20 >= 50)
					{
						tamaFlag21 = 1;
					}
					if (tamaY20 >= 620)
					{
						tamaFlag20 = 0;
					}
				}
				if (tamaFlag21 == 1)
				{
					DrawCircle(tamaX21, tamaY21, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(25 * DX_PI_F / 180) * sin(25 * DX_PI_F / 180) + cos(25 * DX_PI_F / 180) * cos(25 * DX_PI_F / 180));
					tamaX21 -= wakaran * 5;
					tamaY21 += wakaran * 5;
					if (tamaY21 >= 50)
					{
						tamaFlag22 = 1;
					}
					if (tamaY21 >= 620)
					{
						tamaFlag21 = 0;
					}
				}
				if (tamaFlag22 == 1)
				{
					DrawCircle(tamaX22, tamaY22, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(30 * DX_PI_F / 180) * sin(30 * DX_PI_F / 180) + cos(30 * DX_PI_F / 180) * cos(30 * DX_PI_F / 180));
					tamaX22 -= wakaran * 6;
					tamaY22 += wakaran * 5;
					if (tamaY22 >= 50)
					{
						tamaFlag23 = 1;
					}
					if (tamaY22 >= 620)
					{
						tamaFlag22 = 0;
					}
				}
				if (tamaFlag23 == 1)
				{
					DrawCircle(tamaX23, tamaY23, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(35 * DX_PI_F / 180) * sin(35 * DX_PI_F / 180) + cos(35 * DX_PI_F / 180) * cos(35 * DX_PI_F / 180));
					tamaX23 -= wakaran * 7;
					tamaY23 += wakaran * 5;
					if (tamaY23 >= 50)
					{
						tamaFlag24 = 1;
					}
					if (tamaY23 >= 620)
					{
						tamaFlag23 = 0;
					}
				}
				if (tamaFlag24 == 1)
				{
					DrawCircle(tamaX24, tamaY24, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(35 * DX_PI_F / 180) * sin(35 * DX_PI_F / 180) + cos(35 * DX_PI_F / 180) * cos(35 * DX_PI_F / 180));
					tamaX24 -= wakaran * 7;
					tamaY24 += wakaran * 5;
					if (tamaY24 >= 50)
					{
						tamaFlag25 = 1;
					}
					if (tamaY24 >= 620)
					{
						tamaFlag24 = 0;
					}
				}
				if (tamaFlag25 == 1)
				{
					DrawCircle(tamaX25, tamaY25, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(30 * DX_PI_F / 180) * sin(30 * DX_PI_F / 180) + cos(30 * DX_PI_F / 180) * cos(30 * DX_PI_F / 180));
					tamaX25 -= wakaran * 6;
					tamaY25 += wakaran * 5;
					if (tamaY25 >= 50)
					{
						tamaFlag26 = 1;
					}
					if (tamaY25 >= 620)
					{
						tamaFlag25 = 0;
					}
				}
				if (tamaFlag26 == 1)
				{
					DrawCircle(tamaX26, tamaY26, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(25 * DX_PI_F / 180) * sin(25 * DX_PI_F / 180) + cos(25 * DX_PI_F / 180) * cos(25 * DX_PI_F / 180));
					tamaX26 -= wakaran * 5;
					tamaY26 += wakaran * 5;
					if (tamaY26 >= 50)
					{
						tamaFlag27 = 1;
					}
					if (tamaY26 >= 620)
					{
						tamaFlag26 = 0;
					}
				}
				if (tamaFlag27 == 1)
				{
					DrawCircle(tamaX27, tamaY27, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(20 * DX_PI_F / 180) * sin(20 * DX_PI_F / 180) + cos(20 * DX_PI_F / 180) * cos(20 * DX_PI_F / 180));
					tamaX27 -= wakaran * 4;
					tamaY27 += wakaran * 5;
					if (tamaY27 >= 50)
					{
						tamaFlag28 = 1;
					}
					if (tamaY27 >= 620)
					{
						tamaFlag27 = 0;
					}
				}
				if (tamaFlag28 == 1)
				{
					DrawCircle(tamaX28, tamaY28, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(15 * DX_PI_F / 180) * sin(15 * DX_PI_F / 180) + cos(15 * DX_PI_F / 180) * cos(15 * DX_PI_F / 180));
					tamaX28 -= wakaran * 3;
					tamaY28 += wakaran * 5;
					if (tamaY28 >= 50)
					{
						tamaFlag29 = 1;
					}
					if (tamaY28 >= 620)
					{
						tamaFlag28 = 0;
					}
				}
				if (tamaFlag29 == 1)
				{
					DrawCircle(tamaX29, tamaY29, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(10 * DX_PI_F / 180) * sin(10 * DX_PI_F / 180) + cos(10 * DX_PI_F / 180) * cos(10 * DX_PI_F / 180));
					tamaX29 -= wakaran * 2;
					tamaY29 += wakaran * 5;
					if (tamaY29 >= 50)
					{
						tamaFlag30 = 1;
					}
					if (tamaY29 >= 620)
					{
						tamaFlag29 = 0;
					}
				}
				if (tamaFlag30 == 1)
				{
					DrawCircle(tamaX30, tamaY30, tamaR, GetColor(0, 0, 255), TRUE);
					wakaran = sqrt(sin(5 * DX_PI_F / 180) * sin(5 * DX_PI_F / 180) + cos(5 * DX_PI_F / 180) * cos(5 * DX_PI_F / 180));
					tamaX30 -= wakaran * 1;
					tamaY30 += wakaran * 5;
					if (tamaY30 >= 620)
					{
						tamaFlag30 = 0;
					}
				}
			}

			if (isEnemyAlive1 == 1)//エネミーフラグがたったら
			{

				for (int i = 0; i < bulMax; i++)
				{
					float lengh1 = sqrtf((enemyX - rensyaX[i]) * (enemyX - rensyaX[i]) + (enemyY - rensyaY[i]) * (enemyY - rensyaY[i]));//２点間の距離
					if (lengh1 <= bulR + enemyR)//衝突しているかどうか
					{
						enemyLife1 = enemyLife1 - 1;
						isBullFlag[i] = 0;//ノリを打つ前に戻す
						rensyaX[i] = 0;//弾の中心のx座標
						rensyaY[i] = 0;//弾の中心のy座標
						bulR = 8;//弾の半径
					}
				}

				for (int i = 0; i < bulMax; i++)
				{
					float lengh2 = sqrtf((enemyX - rensyaX2[i]) * (enemyX - rensyaX2[i]) + (enemyY - rensyaY2[i]) * (enemyY - rensyaY2[i]));//２点間の距離
					if (lengh2 <= bulR + enemyR)//衝突しているかどうか
					{
						enemyLife1 = enemyLife1 - 1;
						isBullFlag2[i] = 0;//ノリを打つ前に戻す
						rensyaX2[i] = 0;//弾の中心のx座標
						rensyaY2[i] = 0;//弾の中心のy座標
						bulR = 8;//弾の半径
					}
				}
				for (int i = 0; i < bulMax; i++)
				{
					float lengh3 = sqrtf((enemyX - rensyaX3[i]) * (enemyX - rensyaX3[i]) + (enemyY - rensyaY3[i]) * (enemyY - rensyaY3[i]));//２点間の距離
					if (lengh3 <= bulR + enemyR)//衝突しているかどうか
					{
						enemyLife1 = enemyLife1 - 1;
						isBullFlag3[i] = 0;//ノリを打つ前に戻す
						rensyaX3[i] = 0;//弾の中心のx座標
						rensyaY3[i] = 0;//弾の中心のy座標
						bulR = 8;//弾の半径
					}
				}
				if (enemyLife1 <= 0)
				{
					PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
					sukoa += 1000;
					aitemuY = 0;
					aitemuFlag = 1;
					isEnemyAlive1 = 0;//エネミーがやられたか
					enemyLife1 = mokkouyoubondo;
					atariFlag = 1;
				}
			}

			if (isEnemyAlive2 == 1)//エネミーフラグがたったら
			{
				DrawFormatString(700, 0, GetColor(255, 0, 255), "ボスの体力\n%d", enemyLife2, TRUE);

				for (int i = 0; i < bulMax; i++)
				{
					float lengh6 = sqrtf((enemyX2 - rensyaX[i]) * (enemyX2 - rensyaX[i]) + (enemyY2 - rensyaY[i]) * (enemyY2 - rensyaY[i]));//２点間の距離
					if (lengh6 <= bulR + enemyR2)//衝突しているかどうか
					{
						enemyLife2 = enemyLife2 - 1;
						isBullFlag[i] = 0;//ノリを打つ前に戻す
						rensyaX[i] = 0;//弾の中心のx座標
						rensyaY[i] = 0;//弾の中心のy座標
						bulR = 8;//弾の半径
					}
				}
				for (int i = 0; i < bulMax; i++)
				{
					float lengh2 = sqrtf((enemyX2 - rensyaX2[i]) * (enemyX2 - rensyaX2[i]) + (enemyY2 - rensyaY2[i]) * (enemyY2 - rensyaY2[i]));//２点間の距離
					if (lengh2 <= bulR + enemyR2)//衝突しているかどうか
					{
						enemyLife2 = enemyLife2 - 1;
						isBullFlag2[i] = 0;//ノリを打つ前に戻す
						rensyaX2[i] = 0;//弾の中心のx座標
						rensyaY2[i] = 0;//弾の中心のy座標
						bulR = 8;//弾の半径
					}
				}
				for (int i = 0; i < bulMax; i++)
				{
					float lengh3 = sqrtf((enemyX2 - rensyaX3[i]) * (enemyX2 - rensyaX3[i]) + (enemyY2 - rensyaY3[i]) * (enemyY2 - rensyaY3[i]));//２点間の距離
					if (lengh3 <= bulR + enemyR2)//衝突しているかどうか
					{
						enemyLife2 = enemyLife2 - 1;
						isBullFlag3[i] = 0;//ノリを打つ前に戻す
						rensyaX3[i] = 0;//弾の中心のx座標
						rensyaY3[i] = 0;//弾の中心のy座標
						bulR = 8;//弾の半径
					}
				}
				if (enemyLife2 <= 0)
				{
					StopSoundMem(SHandle4);
					PlaySoundMem(SHandle6, DX_PLAYTYPE_BACK);
					sukoa += 100000000;
					isEnemyAlive2 = 0;//エネミーがやられたか
					enemyLife2 = 250;
					ClearFlag = 1;//クリアフラグを立てる
				}
			}

			if (aitemuFlag == 1)
			{
				DrawGraph(aitemuX - aitemuR, aitemuY - aitemuR, GHandle8, TRUE);
				aitemuY += aitemuVel;
				float rengh9 = sqrtf((position1.x - aitemuX) * (position1.x - aitemuX) + (position1.y - aitemuY) * (position1.y - aitemuY));
				if (rengh9 <= r + aitemuR)
				{
					isPlayerAlive = 1;
					aitemuFlag = 0;
					shotFlag = 1;
				}
			}


			if (sukoa >= 2000 && sukoa < 4000)
			{
				DrawGraph(64, 100, GHandle11, TRUE);
			}

			if (sukoa >= 4000 && sukoa < 10000)
			{
				DrawGraph(50, 100, GHandle12, TRUE);
			}

			if (sukoa >= 10000 && sukoa < 20000)
			{
				DrawGraph(50, 100, GHandle13, TRUE);
			}

			if (sukoa >= 20000 && sukoa < 1000000)
			{
				DrawGraph(50, 100, GHandle14, TRUE);
			}

			if (sukoa >= 1000000)
			{
				DrawGraph(20, 100, GHandle16, TRUE);
			}

			if (isEnemyAlive1 == 0)//エネミーがやられたら
			{
				atariFlag = 0;
				enemyTimer -= 1;
				if (enemyTimer == 0)
				{
					isEnemyAlive1 = 1;
					enemyTimer = 120;
					random = rand() % 569 - 300;
					enemyX = WIN_WIDTH / 2 + random;//敵の中心座標は中心（x座標）
					enemyY = 50;//エネミーの中心のy座標
				}
				bomFlag = 1;
				DrawGraph(enemyX - enemyR - 32, enemyY - enemyR - 32, GHandle5[t], TRUE);//配列を用いたgif式画像の読み込み
				if (t == bakuhatuAnime)
				{
					bomFlag = 0;
					enemyX = WIN_WIDTH / 2 + random;//敵の中心座標は中心（x座標）
					enemyY = 0;
				}
				if (bomFlag == 1)
				{
					t++;//連番画像を順次に入れ替え
				}
			}

			if (isEnemyAlive2 == 0)//エネミーがやられたら
			{
				bomFlag = 1;
				DrawGraph(enemyX2 - enemyR2 - 32, enemyY2 - enemyR2 - 32, GHandle5[t], TRUE);//配列を用いたgif式画像の読み込み
				if (t == bakuhatuAnime)
				{
					bomFlag = 0;
				}
				if (bomFlag == 1 && isEnemyAlive2 == 0)
				{
					t++;//連番画像を順次に入れ替え
				}
			}

			if (isPlayerAlive == 0)//エネミーとのりが当たったら
			{
				isEnemyAlive2 = 0;
				isEnemyAlive3 = 0;
				enemyTimer = -1;
				SetFontSize(64);//フォントのサイズを６４に設定
				clsDx();//画面出力履歴をクリアする
				DrawString(250, 300 - 32, "Game over\n", GetColor(255, 0, 0), FALSE);//文字列を真ん中に表示
				SetFontSize(32);
				DrawFormatString(250, 362 - 32, GetColor(0, 255, 255), "あなたのスコアは%dです。", sukoa);
				DrawString(200, 400 - 32, "Aボタンでメニューに戻る", GetColor(255, 255, 255), FALSE);//文字列を表示
				if (keys[KEY_INPUT_A] == 1 && oldkeys[KEY_INPUT_A] == 0)//もしAキーが押されたら
				{
					GameoverTimer = 0;
					menuFlag = 0;//メニューフラグを下す
				}
			}

			if (isPlayerAlive == 1)//プレイヤー
			{
				DrawFormatString(0, 300, GetColor(255, 255, 255), "体力\n%d", playerLife);
				if (waitFlag == 0)
				{
					DrawGraph(posX1, posY1, GHandle17[wait], TRUE);
					wait++;
				}
				if (wait == taikiAnime)
				{
					wait = 0;
				}
				if (waitFlag == 1)
				{
					DrawGraph(posX1, posY1, GHandle1[p], TRUE);//配列を用いたgif式画像の読み込み
					p++;//連番画像を順次に入れ替え
				}
				if (p == playerAnime)
				{
					p = 0;//連番画像が最後まで映されたら最初から
				}

				waitFlag = 0;
				if (keys[KEY_INPUT_LEFT] && posX1 > 100)//左に行くときに画面外に出ないようにする
				{
					waitFlag = 1;
					position1.x -= playerVel;
				}

				if (keys[KEY_INPUT_UP] && posY1 > 0)//上に行くとき画面外に出ないようにする
				{
					waitFlag = 1;
					position1.y -= playerVel;
				}

				if (keys[KEY_INPUT_RIGHT] && posX2 < 700)//右に行くときに画面外に出ないようにする
				{
					waitFlag = 1;
					position1.x += playerVel;
				}

				if (keys[KEY_INPUT_DOWN] && posY2 < 600)//下に行くときに画面外に行かないようにする
				{
					waitFlag = 1;
					position1.y += playerVel;
				}


				if (atariFlag == 0)
				{
					float lengh10 = sqrtf((position1.x - enemyX) * (position1.x - enemyX)
						+ (position1.y - enemyY) * (position1.y - enemyY));
					if (lengh10 <= r + enemyR2 - 30)//衝突判定
					{
						playerLife = playerLife - 1;
						isEnemyAlive1 = 0;//エネミーフラグを下げる
					}
					float lengh11 = sqrtf((position1.x - tamaX1) * (position1.x - tamaX1)
						+ (position1.y - tamaY1) * (position1.y - tamaY1));
					if (lengh11 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag = 0;
						playerLife = playerLife - 10;
					}
					float lengh12 = sqrtf((position1.x - tamaX2) * (position1.x - tamaX2)
						+ (position1.y - tamaY2) * (position1.y - tamaY2));
					if (lengh12 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag2 = 0;
						playerLife = playerLife - 10;
					}
					float lengh13 = sqrtf((position1.x - tamaX3) * (position1.x - tamaX3)
						+ (position1.y - tamaY3) * (position1.y - tamaY3));
					if (lengh13 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag3 = 0;
						playerLife = playerLife - 10;
					}
					float lengh14 = sqrtf((position1.x - tamaX4) * (position1.x - tamaX4)
						+ (position1.y - tamaY4) * (position1.y - tamaY4));
					if (lengh14 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag4 = 0;
						playerLife = playerLife - 10;
					}
					float lengh15 = sqrtf((position1.x - tamaX5) * (position1.x - tamaX5)
						+ (position1.y - tamaY5) * (position1.y - tamaY5));
					if (lengh15 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag5 = 0;
						playerLife = playerLife - 10;
					}
					float lengh16 = sqrtf((position1.x - tamaX6) * (position1.x - tamaX6)
						+ (position1.y - tamaY6) * (position1.y - tamaY6));
					if (lengh16 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag6 = 0;
						playerLife = playerLife - 10;
					}
					float lengh17 = sqrtf((position1.x - tamaX7) * (position1.x - tamaX7)
						+ (position1.y - tamaY7) * (position1.y - tamaY7));
					if (lengh17 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag7 = 0;
						playerLife = playerLife - 10;
					}
					float lengh18 = sqrtf((position1.x - tamaX8) * (position1.x - tamaX8)
						+ (position1.y - tamaY8) * (position1.y - tamaY8));
					if (lengh18 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag8 = 0;
						playerLife = playerLife - 10;
					}
					float lengh19 = sqrtf((position1.x - tamaX9) * (position1.x - tamaX9)
						+ (position1.y - tamaY9) * (position1.y - tamaY9));
					if (lengh19 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag9 = 0;
						playerLife = playerLife - 10;
					}
					float lengh20 = sqrtf((position1.x - tamaX10) * (position1.x - tamaX10)
						+ (position1.y - tamaY10) * (position1.y - tamaY10));
					if (lengh20 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag10 = 0;
						playerLife = playerLife - 10;
					}
					float lengh21 = sqrtf((position1.x - tamaX11) * (position1.x - tamaX11)
						+ (position1.y - tamaY11) * (position1.y - tamaY11));
					if (lengh21 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag11 = 0;
						playerLife = playerLife - 10;
					}
					float lengh22 = sqrtf((position1.x - tamaX12) * (position1.x - tamaX12)
						+ (position1.y - tamaY12) * (position1.y - tamaY12));
					if (lengh22 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag12 = 0;
						playerLife = playerLife - 10;
					}
					float lengh23 = sqrtf((position1.x - tamaX13) * (position1.x - tamaX13)
						+ (position1.y - tamaY13) * (position1.y - tamaY13));
					if (lengh23 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag13 = 0;
						playerLife = playerLife - 10;
					}
					float lengh24 = sqrtf((position1.x - tamaX14) * (position1.x - tamaX14)
						+ (position1.y - tamaY14) * (position1.y - tamaY14));
					if (lengh24 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag14 = 0;
						playerLife = playerLife - 10;
					}
					float lengh25 = sqrtf((position1.x - tamaX15) * (position1.x - tamaX15)
						+ (position1.y - tamaY15) * (position1.y - tamaY15));
					if (lengh15 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag15 = 0;
						playerLife = playerLife - 10;
					}
					float lengh26 = sqrtf((position1.x - tamaX16) * (position1.x - tamaX16)
						+ (position1.y - tamaY16) * (position1.y - tamaY16));
					if (lengh26 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag16 = 0;
						playerLife = playerLife - 10;
					}
					float lengh27 = sqrtf((position1.x - tamaX17) * (position1.x - tamaX17)
						+ (position1.y - tamaY17) * (position1.y - tamaY17));
					if (lengh27 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag17 = 0;
						playerLife = playerLife - 10;
					}
					float lengh28 = sqrtf((position1.x - tamaX18) * (position1.x - tamaX18)
						+ (position1.y - tamaY18) * (position1.y - tamaY18));
					if (lengh28 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag18 = 0;
						playerLife = playerLife - 10;
					}
					float lengh29 = sqrtf((position1.x - tamaX19) * (position1.x - tamaX19)
						+ (position1.y - tamaY19) * (position1.y - tamaY19));
					if (lengh29 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag19 = 0;
						playerLife = playerLife - 10;
					}
					float lengh30 = sqrtf((position1.x - tamaX20) * (position1.x - tamaX20)
						+ (position1.y - tamaY20) * (position1.y - tamaY20));
					if (lengh30 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag20 = 0;
						playerLife = playerLife - 10;
					}
					float lengh31 = sqrtf((position1.x - tamaX21) * (position1.x - tamaX21)
						+ (position1.y - tamaY21) * (position1.y - tamaY21));
					if (lengh31 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag21 = 0;
						playerLife = playerLife - 10;
					}
					float lengh32 = sqrtf((position1.x - tamaX22) * (position1.x - tamaX22)
						+ (position1.y - tamaY22) * (position1.y - tamaY22));
					if (lengh32 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag22 = 0;
						playerLife = playerLife - 10;
					}
					float lengh33 = sqrtf((position1.x - tamaX23) * (position1.x - tamaX23)
						+ (position1.y - tamaY23) * (position1.y - tamaY23));
					if (lengh33 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag23 = 0;
						playerLife = playerLife - 10;
					}
					float lengh34 = sqrtf((position1.x - tamaX24) * (position1.x - tamaX24)
						+ (position1.y - tamaY24) * (position1.y - tamaY24));
					if (lengh34 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag24 = 0;
						playerLife = playerLife - 10;
					}
					float lengh35 = sqrtf((position1.x - tamaX25) * (position1.x - tamaX25)
						+ (position1.y - tamaY25) * (position1.y - tamaY25));
					if (lengh35 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag25 = 0;
						playerLife = playerLife - 10;
					}
					float lengh36 = sqrtf((position1.x - tamaX26) * (position1.x - tamaX26)
						+ (position1.y - tamaY26) * (position1.y - tamaY26));
					if (lengh36 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag26 = 0;
						playerLife = playerLife - 10;
					}
					float lengh37 = sqrtf((position1.x - tamaX27) * (position1.x - tamaX27)
						+ (position1.y - tamaY27) * (position1.y - tamaY27));
					if (lengh37 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag27 = 0;
						playerLife = playerLife - 10;
					}
					float lengh38 = sqrtf((position1.x - tamaX28) * (position1.x - tamaX28)
						+ (position1.y - tamaY28) * (position1.y - tamaY28));
					if (lengh38 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag28 = 0;
						playerLife = playerLife - 10;
					}
					float lengh39 = sqrtf((position1.x - tamaX29) * (position1.x - tamaX29)
						+ (position1.y - tamaY29) * (position1.y - tamaY29));
					if (lengh39 <= r + tamaR)//衝突判定
					{
						tamaFlag29 = 0;
						playerLife = playerLife - 10;
					}
					float lengh40 = sqrtf((position1.x - tamaX30) * (position1.x - tamaX30)
						+ (position1.y - tamaY30) * (position1.y - tamaY30));
					if (lengh40 <= r + tamaR)//衝突判定
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						tamaFlag30 = 0;
						playerLife = playerLife - 10;
					}
				}
				if (playerLife <= 0)
				{
					isPlayerAlive = 0;//プレイヤーフラグを下げる
					isEnemyAlive1 = 0;
					sibouFlag = 0;
					StopSoundMem(SHandle4);
					PlaySoundMem(SHandle5, DX_PLAYTYPE_BACK);
				}
			}
		}


		//---------  ここまでにプログラムを記述  ---------//
		ScreenFlip();//（ダブルバッファ）裏面
		// 20ミリ秒待機（疑似60FPS）
		WaitTimer(20);
		// Windows システムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}
		// ＥＳＣキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// 読み込んだ画像のグラフィックハンドルを削除
	InitGraph();
	DeleteSoundMem(SHandle2);
	DeleteSoundMem(SHandle3);
	DeleteSoundMem(SHandle4);
	DeleteSoundMem(SHandle5);
	DeleteSoundMem(SHandle6);
	//Dxライブラリ終了処理
	DxLib_End();

	return 0;
}