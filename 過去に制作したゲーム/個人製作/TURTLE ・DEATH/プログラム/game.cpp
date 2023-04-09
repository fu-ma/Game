#include "DxLib.h"
#include<time.h>
#include<math.h>

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "k020G1170 塩川風舞:TURTLE・DEATH";

// ウィンドウ横幅
const int WIN_WIDTH = 1024;

// ウィンドウ縦幅
const int WIN_HEIGHT = 512;	
const int TAIKI = 6;
const int ARUKU = 4;
const int BAKUHATU = 13;
const int HARI = 20;
const int RISU = 2;
const int MAME = 10;
const float HAIKEI_SPEED =0.1;
const float SCROOL_SPEED = 0.2;
const int DAMAGE_SPEED = 1;
const int FONT_SIZE = 25;
const int NAME_SIZE = 12;

void DrawMOZI(int x, int y, const char t[], int count, int Coordinate) {
	int n = count / 2;
	const int a = x;
	SetFontSize(FONT_SIZE);
	int color = GetColor(255, 255, 255);
	for (int i = 0; i < n + 1 && t[i] != '\0'; i++)
	{
		int Size = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, t + i);
		if (Size == 1)
		{
			DrawFormatString(x, y, color, "%c", t[i]);
			if (!(x + FONT_SIZE / 2 >= (Coordinate / FONT_SIZE) * FONT_SIZE))
			{
				x += FONT_SIZE / 2;
			}
			if (x + FONT_SIZE/2 >= (Coordinate / FONT_SIZE) * FONT_SIZE)
			{
				y += FONT_SIZE/1.5;
			}
		}
		else
		{
			DrawFormatString(x, y, color, "%c%c", t[i], t[i + 1]);
			x += FONT_SIZE; i++; n++;
			if (x + FONT_SIZE >= (Coordinate / FONT_SIZE) * FONT_SIZE)
			{
				x = x - ((x / FONT_SIZE) * FONT_SIZE) + a;
				y += FONT_SIZE;
			}
		}
	}
}

//bool HIT(float aX, float aY, float bX, float bY,int r)
//{
//	if (bX - r <= aX + r && aX - r <= bX + r && bY - r <= aY + r && aY - r <= bY + r)
//	{
//		return true;
//	}
//else
//{
//return false;
//}
//}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	int GHandle1[TAIKI];
	int GHandle2[ARUKU];
	int GHandle4 = LoadGraph("haikei_kumo.png");
	int GHandle5 = LoadGraph("kyousou.png");
	int GHandle6 = LoadGraph("bakudan.png");
	int GHandle7[BAKUHATU];
	int GHandle8[HARI];
	int GHandle9 = LoadGraph("komento.png");
	int GHandle10[RISU];
	int GHandle11 = LoadGraph("yazirusi.png");
	int GHandle12 = LoadGraph("sousa1.png");
	int GHandle13 = LoadGraph("sousa2.png");
	int GHandle14 = LoadGraph("koment2.png");
	int GHandle15 = LoadGraph("haka.png");
	int GHandle16[MAME];
	int GHandle17 = LoadGraph("ropu.png");
	int GHandle18 = LoadGraph("haka2.png");
	int GHandle19 = LoadGraph("honoo.png");
	int GHandle20 = LoadGraph("end.png");
	int GHandle21 = LoadGraph("kamenamakubi.png");
	int GHandle22 = LoadGraph("kamenamakubi2.png");
	
	int SHandle1 = LoadSoundMem("sentakuon.mp3");
	int SHandle2 = LoadSoundMem("kettei.mp3");
	int SHandle3 = LoadSoundMem("hari.mp3");
	int SHandle4 = LoadSoundMem("gusa.mp3");
	int SHandle5 = LoadSoundMem("bakuhatu.mp3");
	int SHandle6 = LoadSoundMem("tyakuti.mp3");
	int SHandle7 = LoadSoundMem("jump.mp3");
	int SHandle8 = LoadSoundMem("ropu.mp3");
	int SHandle9 = LoadSoundMem("honoo.mp3");
	int SHandle10 = LoadSoundMem("down1.mp3");
	int SHandle11 = LoadSoundMem("syokku.mp3");
	int SHandle12= LoadSoundMem("ikari.mp3");
	int SHandle13= LoadSoundMem("tin1.mp3");
	int SHandle14 = LoadSoundMem("mokugyo.mp3");
	int SHandle15 = LoadSoundMem("end.mp3");
	int SHandle16 = LoadSoundMem("endroll.mp3");
	LoadDivGraph("kametaiki-sheet.png", 6, 6, 1, 128, 128, GHandle1);
	LoadDivGraph("kamearuku-sheet.png", 4, 4, 1, 128, 128, GHandle2);
	LoadDivGraph("bakuhatu-sheet.png", 13, 13, 1, 128, 128, GHandle7);
	LoadDivGraph("hari.png", 20, 20, 1, 128, 256, GHandle8);
	LoadDivGraph("risu.png", 2, 2, 1, 128, 128, GHandle10);
	LoadDivGraph("mamedennkyuukunn.png", 10, 10, 1, 128, 128, GHandle16);

	// ゲームループで使う変数の宣言
	int i = 0; int t = 0; int g = 0; int z = 0; int q = 0; int a = 0; int k = 0; int w = 0; int h = 0; int m = 0;//画像保存用変数
	int r = 64;
	int BESIC_SPEED = 3;
	int titleFlag = 0; float titleX = 410; float titleY = 380;
	int posX = 64; int posY = 386;
	float haikeiX = 0;
	float scrollX = 0; int scrollX2 = 0; int scrollX3 = 0; int scrollX4 = 0;
	int localX = 0; int localBomX = 0; int localHariX = 0;
	int houkouFlag = 0;
	int backGroundX = 0;
	int jampFlag = 1;
	float velY = 0;
	float zyuuryoku = 0.25;
	int isExplosionFlag = 0;
	int bomX = 0; int bomY = 0;
	int hariX = 0; int hariY = 0;
	int speedFlag = 0;
	int damage = 0;
	int Timer = 100;
	int jampCount = 2;
	int startFlag = 0; int count1 = 0; int count2 = 0; int nameFlag = 0;
	int komentoFlag = 0;
	int nameCount = 0; int kakuninFlag = 0;
	int kCount = 0;
	int color1; int color2; int color3; int color4; int color5; int color6; int color7; int color8; int color9;
	int color10=GetColor(255,255,255);
	int menuFlag = 0; int menuCount = 0;
	int talkFlag = 0; int syokikaFlag = 0;
	int kirikaeX = 680; int kirikaeY = 217; int kirikaeX2 = 40;int kirikaeFlag = 0;
	int kirikae3X = 680; int kirikae3Y = 317; int color11; int color12; int color13; int color14;
	int titoFlag = 0;
	int kyoriX = 0;
	int hariFlag = 0;
	int sibouFlag = 0;
	int sibouCount = 0; int sibouCount2 = 0;
	int hakaCount = 0; int sound = 30;
	int musicFlag = 0;
	int hari2X[31] = { 0 };
	int mameX[31] = { 4000,6000,8000,10000,12000,14000,16000,18000,20000,22000,24000,26000,28000,30000,32000,34000,36000,38000,39000,40000,41000,42000,43000,44000,45000,46000,47000,48000,49000,50000,51000 }; int mameY = 320;
	int mameFlag = 0;
	int copy[31] = { 4000,6000,8000,10000,12000,14000,16000,18000,20000,22000,24000,26000,28000,30000,32000,34000,36000,38000,39000,40000,41000,42000,43000,44000,45000,46000,47000,48000,49000,50000,51000 };
	int ropuFlag = 0;
	int ropuX[41] = { 0 };
	int kirikae2Flag = 0;
	int koukaonnFlag = 0;
	int honooFlag = 0;
	int honooX[41] = { 0 };
	int clearFlag = 0;
	int endTimer = 0; int scrollY = 0; int tartle = 2652;
	int endColor;
	int syokkuFlag = 0; int syokkuX[30] = { 0 };
	int reaCount = 0; int funnsiFlag = 0;
	srand(time(NULL));
	char Name[11];

	// 最新のキーボード情報用
	char keys[256] = { 0 };

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
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		localX = posX - scrollX4;
		localBomX = bomX - scrollX3;
		localHariX = hariX - scrollX3;
		backGroundX = scrollX + haikeiX;
		if (sibouFlag == 0)
		{
			DrawGraph(0 - backGroundX, 0, GHandle4, TRUE);
			DrawGraph(WIN_WIDTH - backGroundX, 0, GHandle4, TRUE);
			haikeiX += HAIKEI_SPEED;
		}

		if (titleFlag == 0)
		{
			i = 0;
			t = 0;
			g = 0;
			z = 0;
			q = 0;
			a = 0;
			k = 0;
			w = 0;
			h = 0;//画像保存用変数
			BESIC_SPEED = 3;
			posX = 64;
			posY = 386;
			scrollX2 = 0;
			scrollX3 = 0;
			scrollX4 = 0;
			localX = 0;
			localBomX = 0;
			localHariX = 0;
			houkouFlag = 0;
			jampFlag = 1;
			velY = 0;
			isExplosionFlag = 0;
			bomX = 0;
			bomY = 0;
			hariX = 0;
			hariY = 0;
			speedFlag = 0;
			damage = 0;
			Timer = 100;
			jampCount = 2;
			startFlag = 0;
			count1 = 0;
			count2 = 0;
			nameFlag = 0;
			komentoFlag = 0;
			nameCount = 0;
			kakuninFlag = 0;
			kCount = 0;
			menuFlag = 0;
			menuCount = 0;
			talkFlag = 0;
			syokikaFlag = 0;
			kyoriX = 0;
			hariFlag = 0;
			sibouFlag = 0;
			sibouCount = 0;
			sibouCount2 = 0;
			hakaCount = 0;
			mameFlag = 0;
			ropuFlag = 0;
			for (int i = 0; i < 40; i++)
			{
				honooX[i] = 0;
			}
			for (int i = 0; i < 40; i++)
			{
				ropuX[i] = 0;
			}
			for (int i = 0; i < 30; i++)
			{
				hari2X[i] = 0;
			}
			for (int i = 0; i < 30; i++)
			{
				mameX[i] = copy[i];
			}
			for (int i = 0; i < 30; i++)
			{
				syokkuX[i] = 0;
			}
			mameY = 320;
			mameFlag = 0;
			kirikae2Flag = 0;
			honooFlag = 0;
			clearFlag = 0;
			endTimer = 0;
			scrollY = 0;
			tartle = 2652;
			endColor = GetColor(255, 255, 255);
			syokkuFlag = 0;
			reaCount = 0;
			funnsiFlag = 0;
		}
		if (titleFlag == 0)
		{
			ChangeVolumeSoundMem(255 * sound / 100, SHandle1);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle1);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle2);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle3);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle4);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle5);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle6);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle7);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle8);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle9);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle10);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle11);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle12);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle13);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle14);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle15);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle16);
			ChangeFont("ＭＳ 明朝");
			ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
			SetFontSize(70);
			DrawString(260, 220, "TURTLE・DEATH", GetColor(0, 0, 255));
			SetFontSize(40);
			DrawGraph(titleX - 16, titleY - 16, GHandle11, TRUE);
			color1 = GetColor(255, 255, 255);
			color2 = GetColor(255, 255, 255);
			color3 = GetColor(255, 255, 255);
			if (titleY != 460 && keys[KEY_INPUT_S] == 1 && oldkeys[KEY_INPUT_S] == 0)
			{
				PlaySoundMem(SHandle1, DX_PLAYTYPE_BACK);
				titleY += 40;
			}
			if (titleY != 380 && keys[KEY_INPUT_W] == 1 && oldkeys[KEY_INPUT_W] == 0)
			{
				PlaySoundMem(SHandle1, DX_PLAYTYPE_BACK);
				titleY -= 40;
			}
			if (titleY == 460)
			{
				titleX = 390;
			}
			if (titleY != 460)
			{
				titleX = 410;
			}
			if (titleY == 380)
			{
				color1 = GetColor(0, 0, 0);
			}
			if (titleY == 420)
			{
				color2 = GetColor(0, 0, 0);
			}
			if (titleY == 460)
			{
				color3 = GetColor(0, 0, 0);
			}
			DrawString(WIN_WIDTH / 2 - 80, 360, "スタート", color1);
			DrawString(WIN_WIDTH / 2 - 80, 400, "メニュー", color2);
			DrawString(WIN_WIDTH / 2 - 100, 440, "ゲーム終了", color3);
			if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
			{
				PlaySoundMem(SHandle2 ,DX_PLAYTYPE_BACK);
				if (titleY == 380)
				{
					titleFlag = 1;
				}
				if (titleY == 420)
				{
					menuFlag = 1;
				}
			}
		}

		if (menuFlag == 0)
		{
			menuCount = 0;
		}

		if (menuFlag == 1)
		{
			color4 = GetColor(255, 255, 255);
			color5 = GetColor(255, 255, 255);
			color9 = GetColor(255, 255, 255);
			color14 = GetColor(255, 255, 255);
			if (menuCount == 0)
			{
				titleX = WIN_WIDTH / 4 - 125;
				titleY=120;
			}
			if (menuCount == 0 && kirikaeFlag == 1)
			{
				titleX = 600 - 30;
				titleY = 200+20;
			}
			if (menuCount == 0 && kirikae2Flag == 1)
			{
				titleX = 600 - 30;
				titleY = 300 + 20;
			}
			menuCount++;
			titleFlag = 2;
			if (kirikaeFlag == 0 && kirikae2Flag == 0)
			{
				if (musicFlag == 1 && titleY != 420 && keys[KEY_INPUT_S] == 1 && oldkeys[KEY_INPUT_S] == 0)
				{
					PlaySoundMem(SHandle1, DX_PLAYTYPE_BACK);
					titleY += 100;
				}
				if (musicFlag==1&&titleY != 120 && keys[KEY_INPUT_W] == 1 && oldkeys[KEY_INPUT_W] == 0)
				{
					PlaySoundMem(SHandle1, DX_PLAYTYPE_BACK);
					titleY -= 100;
				}
			}
			if (titleY == 120)
			{
				color4 = GetColor(0, 0, 0);
			}
			if (titleY == 220)
			{
				color5 = GetColor(0, 0, 0);
			}
			if (titleY == 320)
			{
				color9 = GetColor(0, 0, 0);
			}
			if (titleY == 420)
			{
				color14 = GetColor(0, 0, 0);
			}
			color6 = GetColor(255, 255, 255);
			color7 = GetColor(255, 255, 255);
			color8 = GetColor(0, 0, 0);
			color11 = GetColor(0, 0, 0);
			color12 = GetColor(255, 255, 255);
			color13 = GetColor(255, 255, 255);
			if (musicFlag == 1)
			{
				color10 = GetColor(255, 255, 255);
			}
			if (kirikaeX == 680)
			{
				titoFlag = 0;
				if (kirikaeFlag == 0)
				{
					color7 = GetColor(0, 0, 0);
				}
				if (kirikaeFlag == 1)
				{
					color7 = GetColor(255, 0, 0);
					color8 = GetColor(255, 0, 0);
				}
			}
			if (kirikaeX == 580)
			{
				titoFlag = 1;
				if (kirikaeFlag == 0)
				{
					color6 = GetColor(0, 0, 0);
				}
				if (kirikaeFlag == 1)
				{
					color6 = GetColor(255, 0, 0);
					color8 = GetColor(255, 0, 0);
				}
			}
			if (kirikae3X == 680)
			{
				koukaonnFlag = 0;
				if (kirikae2Flag == 0)
				{
					color13 = GetColor(0, 0, 0);
				}
				if (kirikae2Flag == 1)
				{
					color13 = GetColor(255, 0, 0);
					color11 = GetColor(255, 0, 0);
				}
			}
			if (kirikae3X == 580)
			{
				koukaonnFlag = 1;
				if (kirikae2Flag == 0)
				{
					color12 = GetColor(0, 0, 0);
				}
				if (kirikae2Flag == 1)
				{
					color12 = GetColor(255, 0, 0);
					color11 = GetColor(255, 0, 0);
				}
			}
			DrawGraph(titleX - 16, titleY - 16, GHandle11, TRUE);
			DrawString(WIN_WIDTH / 4 - 100, 100, "音量", color4);
			DrawString(WIN_WIDTH / 4 - 100, 200, "チート", color5);
			DrawString(WIN_WIDTH / 4 - 100, 300, "グロ要素", color9);
			DrawString(WIN_WIDTH / 4 - 100, 400, "戻る", color14);
			DrawString(600, 200, "ON", color6);
			DrawString(700, 200, "OFF", color7);
			DrawString(600, 300, "ON", color12);
			DrawString(700, 300, "OFF", color13);
			DrawCircle(580, 217, 10, GetColor(255,255,255));
			DrawCircle(680, 217, 10, GetColor(255,255,255));
			DrawCircle(580, 317, 10, GetColor(255, 255, 255));
			DrawCircle(680, 317, 10, GetColor(255, 255, 255));
			DrawCircle(kirikaeX, kirikaeY, 6, color8);
			DrawCircle(kirikae3X, kirikae3Y, 6, color11);
			if (musicFlag == 2 && keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
			{
				musicFlag = 0;
			}
			if (titleY==120&&musicFlag==1&&keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
			{
				color10 = GetColor(255, 0, 0);
				musicFlag = 2;
			}
			DrawFormatString(630, 100, color10, "%3d％", kirikaeX2);
			if (keys[KEY_INPUT_RETURN] == 1)
			{
				PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
				if (titleY == 120 && musicFlag == 0)
				{
					musicFlag = 1;
				}
				if (titleY == 220&&kirikaeFlag==0)
				{
					kirikaeFlag = 1;
				}
				if (titleY == 320 && kirikaeFlag == 0)
				{
					kirikae2Flag = 1;
				}
				if (titleY == 420 && kirikaeFlag == 0)
				{
					menuFlag = 0;
					titleFlag = 0;
					musicFlag = 0;
					kirikaeFlag = 0;
					kirikae2Flag = 0;
				}
			}
			if (kirikaeFlag == 1 && kirikaeX == 680 && keys[KEY_INPUT_A] == 1 && oldkeys[KEY_INPUT_A] == 0)
			{
				kirikaeFlag = 0;
				if (titleY == 220)
				{
					kirikaeX -= 100;
				}
			}
			if (kirikaeFlag == 1 && kirikaeX == 580 && keys[KEY_INPUT_D] == 1 && oldkeys[KEY_INPUT_D] == 0)
			{
				kirikaeFlag = 0;
				if (titleY == 220)
				{
					kirikaeX += 100;
				}
			}
			if (kirikae2Flag == 1 && kirikae3X == 680 && keys[KEY_INPUT_A] == 1 && oldkeys[KEY_INPUT_A] == 0)
			{
				kirikae2Flag = 0;
				if (titleY == 320)
				{
					kirikae3X -= 100;
				}
			}
			if (kirikae2Flag == 1 && kirikae3X == 580 && keys[KEY_INPUT_D] == 1 && oldkeys[KEY_INPUT_D] == 0)
			{
				kirikae2Flag = 0;
				if (titleY == 320)
				{
					kirikae3X += 100;
				}
			}
			if (musicFlag == 2 && kirikaeX2 !=0 && keys[KEY_INPUT_A] == 1 && oldkeys[KEY_INPUT_A] == 0)
			{
				PlaySoundMem(SHandle1, DX_PLAYTYPE_BACK);
				kirikaeX2 -= 10;
			}
			if (musicFlag == 2 && kirikaeX2 !=100 && keys[KEY_INPUT_D] == 1 && oldkeys[KEY_INPUT_D] == 0)
			{
				PlaySoundMem(SHandle1, DX_PLAYTYPE_BACK);
				kirikaeX2 += 10;
			}
			if (kirikaeX2 == 0)
			{
				sound = 0;
			}
			if (kirikaeX2 == 10)
			{
				sound = 10;
			}
			if (kirikaeX2 == 20)
			{
				sound = 20;
			}
			if (kirikaeX2 == 30)
			{
				sound = 30;
			}
			if (kirikaeX2 == 40)
			{
				sound = 40;
			}
			if (kirikaeX2 == 50)
			{
				sound = 50;
			}
			if (kirikaeX2 == 60)
			{
				sound = 60;
			}
			if (kirikaeX2 == 70)
			{
				sound = 70;
			}
			if (kirikaeX2 == 80)
			{
				sound = 80;
			}
			if (kirikaeX2 == 90)
			{
				sound = 90;
			}
			if (kirikaeX2 == 100)
			{
				sound = 100;
			}
			ChangeVolumeSoundMem(255 * sound / 100, SHandle1);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle2);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle3);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle4);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle5);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle6);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle7);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle8);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle9);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle10);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle11);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle12);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle13);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle14);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle15);
			ChangeVolumeSoundMem(255 * sound / 100, SHandle16);
		}
		if (titleFlag == 1)
		{
			if (startFlag == 0)//名前入力
			{
				if (nameFlag == 0)//最初は名前入力してね
				{
					count2 = 0;
					DrawMOZI(0, 0, "あなたの名前を教えてください", count1, WIN_WIDTH);
					count1++;
				}
				if (count1 >= 30 && nameFlag == 0)
				{
					KeyInputString(0, 30, 10, Name, FALSE);
					if (CheckHitKey(KEY_INPUT_RETURN))
					{
						PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
						nameFlag = 1;
					}
				}
			}
		}
		if (nameFlag == 1)//名前の確認
		{
			count1 = 0;
			DrawString(0, 0, Name, GetColor(255, 255, 255));
			DrawMOZI(0, 32, "でよろしいですか？Yes--->1   No--->2", count2, 250);
			count2++;
			if (count2 >= 60 && CheckHitKey(KEY_INPUT_2))
			{
				PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
				nameFlag = 0;
			}
			if (count2 >= 60 && CheckHitKey(KEY_INPUT_1))
			{
				PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);
				komentoFlag = 1;
				startFlag = 1;
			}
		}
		if (startFlag == 1 && sibouFlag == 0)//ゲームスタート
		{
			if (komentoFlag == 0)
			{
				if (reaCount == 0)
				{
					PlaySoundMem(SHandle15, DX_PLAYTYPE_LOOP, TRUE);
				}
				reaCount++;
				DrawFormatString(700, 0, GetColor(255, 255, 255), "現在の走った距離");
				DrawFormatString(700, 20, GetColor(255, 255, 255), "%5dメートル", kyoriX);
			}
			if (reaCount >= 600&&posX==64)
			{
				funnsiFlag = 1;
				sibouFlag = 1;
			}
			nameFlag = 0;
			if (scrollX2 >= WIN_WIDTH)
			{
				scrollX2 = 0;
			}

			if (backGroundX >= WIN_WIDTH)
			{
				scrollX = 0;
				haikeiX = 0;
			}

			if (titoFlag == 0)
			{
				BESIC_SPEED = 3;
			}

			if (titoFlag == 1)
			{
				BESIC_SPEED = 30;
			}

			// 描画処理
			DrawGraph(0 - scrollX2, 0, GHandle5, TRUE);
			DrawGraph(WIN_WIDTH - scrollX2, 0, GHandle5, TRUE);
			DrawGraph(400-scrollX4, 300, GHandle12, TRUE);
			DrawGraph(200 - scrollX4, 300, GHandle13, TRUE);
			// グラフィックの描画(『DrawGraph』使用)
			if (komentoFlag == 0)
			{
				if (CheckHitKey(KEY_INPUT_D) && !CheckHitKey(KEY_INPUT_A) && clearFlag == 0)
				{
					kyoriX += BESIC_SPEED/3;
					houkouFlag = 0;
					if (speedFlag == 0)
					{
						posX += BESIC_SPEED;
					}
					if (speedFlag == 1)
					{
						posX += DAMAGE_SPEED;
					}
					if (damage % 3 == 0)
					{
						DrawGraph(localX - r, posY - r, GHandle2[t / 5], TRUE);
					}
					t++;
					if (t == ARUKU * 5) t = 0;
					if (localX > WIN_WIDTH / 2)
					{
						scrollX += SCROOL_SPEED;
						if (speedFlag == 0)
						{
							scrollX2 += BESIC_SPEED;
						}
						if (speedFlag == 1)
						{
							scrollX2 += DAMAGE_SPEED;
						}
						scrollX3 += BESIC_SPEED;
						scrollX4 += BESIC_SPEED;
					}
				}

				if (CheckHitKey(KEY_INPUT_A) && !(CheckHitKey(KEY_INPUT_D)) && clearFlag == 0)
				{
					houkouFlag = 1;
					if ((localX - r) > 0)
					{
						kyoriX -= BESIC_SPEED/3;
						if (speedFlag == 0)
						{
							posX -= BESIC_SPEED;
						}
						if (speedFlag == 1)
						{
							posX -= DAMAGE_SPEED;
						}
					}
					if (damage % 3 == 0)
					{
						DrawTurnGraph(localX - r, posY - r, GHandle2[q / 5], TRUE);
					}
					q++;
					if (q == ARUKU * 5) q = 0;

				}
				if ((!(CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_D)) || (CheckHitKey(KEY_INPUT_A) && CheckHitKey(KEY_INPUT_D))) && clearFlag == 0)
				{
					g = 0;
					if (houkouFlag == 0)
					{
						if (damage % 3 == 0)
						{
							DrawGraph(localX - r, posY - r, GHandle1[i / 5], TRUE);
						}
						i++;
						if (i == TAIKI * 5) i = 0;
					}
					if (houkouFlag == 1)
					{
						if (damage % 3 == 0)
						{
							DrawTurnGraph(localX - r, posY - r, GHandle1[z / 5], TRUE);
						}
						z++;
						if (z == TAIKI * 5) z = 0;
					}
				}
			}
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 && jampCount != 0)
			{
				PlaySoundMem(SHandle7, DX_PLAYTYPE_BACK);
				jampFlag = 0;
				velY = 8;
				jampCount--;
			}

			if (jampFlag == 0)
			{
				posY -= velY;
				velY -= zyuuryoku;
			}
			if (posY + r >= 450)
			{
				if ((jampCount == 1 || jampCount == 0))
				{
					PlaySoundMem(SHandle6, DX_PLAYTYPE_BACK);
				}
				posY = 386;
				jampFlag = 1;
				jampCount = 2;
			}
			if (hariFlag == 0)
			{
				hariY = 190;
				hariX = 1000;
				DrawGraph(localHariX,hariY, GHandle8[h / 9], TRUE);
				for (int i = 1; i < 31; i++)
				{
					hari2X[i] = 1000 + 1400 * i;
					DrawGraph(hari2X[i]-scrollX4, hariY, GHandle8[h / 9], TRUE);
					if (h >= 45 && h <= 117 && posX >= hari2X[i] - 10 && posX <= hari2X[i] + 120 && posY <= 400)//針との当たり判定
					{
						hariFlag = 1;
						sibouFlag = 1;
					}
					if (h == 44 && posX >= hari2X[i]-130 && posX <= hari2X[i]+250)
					{
						PlaySoundMem(SHandle3, DX_PLAYTYPE_BACK);
					}
				}

				h++;
				if (h >= 45 && h <= 117 && posX >= hariX - 10 && posX <= hariX + 120 && posY<=400)//針との当たり判定
				{
					hariFlag = 1;
					sibouFlag = 1;
				}
				if (h == 44 && posX >= 800 && posX <= 1300)
				{
					PlaySoundMem(SHandle3, DX_PLAYTYPE_BACK);
				}
				if (h == HARI * 9)
				{
					h = 0;
				}
			}
			if (mameFlag == 0)
			{
				for (int i = 0; i < 30; i++)
				{
					mameX[i] -= 3;
				}
				DrawGraph(mameX[0]-scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[1] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[2] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[3] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[4] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[5] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[6] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[7] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[8] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[9] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[10] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[11] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[12] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[13] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[14] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[15] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[16] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[17] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[18] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[19] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[20] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[21] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[22] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[23] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[24] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[25] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[26] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[27] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[28] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[29] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				DrawGraph(mameX[30] - scrollX4, mameY, GHandle16[m / 5], TRUE);
				m++;
				if (m == MAME*5)
				{
					m = 0;
				}
				for (int i = 0; i < 30; i++)
				{
					if (mameX[i] <= posX + 10 && posX - 30 <= mameX[i] + 100 && mameY +34 <= posY+20 && posY - 40 <= mameY + 120)
					{
						mameFlag = 1;
						sibouFlag = 1;
					}
				}
			}
			if (ropuFlag == 0)
			{
				for (int i = 0; i < 41; i++)
				{
					ropuX[i] = i * 800;
					DrawGraph(ropuX[i]-scrollX4, 0, GHandle17, TRUE);
					if (posX >= ropuX[i]+20&& posX <= ropuX[i] + 100 && posY >= 100 && posY <= 200)
					{
						ropuFlag = 1;
						sibouFlag = 1;
					}
				}
			}
			if (honooFlag == 0)
			{
				for (int i = 1; i < 41; i++)
				{
					honooX[i] = i * 725;
					DrawGraph(honooX[i] - scrollX4, 350, GHandle19, TRUE);
					if (honooX[i]+32 <= posX + 10 && posX - 50 <= honooX[i] + 50 && posY + r >= 400)
					{
						honooFlag = 1;
						sibouFlag = 1;
					}
				}
			}
			if (syokkuFlag == 0)
			{
				for (int i = 0; i < 30; i++)
				{
					syokkuX[i] = 8300 + 800 * i;
					if (koukaonnFlag == 0)
					{
						DrawGraph(syokkuX[i] - scrollX4, 350, GHandle22, TRUE);
					}
					if (koukaonnFlag == 1)
					{
						DrawGraph(syokkuX[i] - scrollX4, 350, GHandle21, TRUE);
					}
					if(syokkuX[i]+22<=posX+10&&posX-50<=syokkuX[i]+50&&posY+r>=400)
					{
						syokkuFlag = 1;
						sibouFlag = 1;
					}
				}
			}
			if (isExplosionFlag == 0)
			{
				bomY = 386;
				bomX = 2000;
				DrawGraph(localBomX - r, bomY, GHandle6, TRUE);
				/*if (localBomX - 21 <= localX + 50 && localX - 10 <= localBomX + 21 && bomY - 22 <= posY + 64 && posY - 10 <= bomY + 22)
				{
					isExplosionFlag = 1;
				}*/
			}
			if (isExplosionFlag == 1)
			{
				DrawGraph(localBomX - r, bomY, GHandle7[a], TRUE);
				a++;
				speedFlag = 1;
				if (a == BAKUHATU)
				{
					a = 12;
					sibouFlag = 1;
				}
			}
			if (speedFlag == 1)
			{
				damage++;
				Timer--;
			}
			if (Timer <= 0)
			{
				damage = 0;
				speedFlag = 0;
			}

			if (kyoriX >= 10000)
			{
				clearFlag = 1;
			}
			if (clearFlag == 1)
			{
				hariFlag = 1;
				mameFlag = 1;
				ropuFlag = 1;
				honooFlag = 1;
				syokkuFlag = 1;
				DrawGraph(localX - r, posY - r, GHandle2[t / 5], TRUE);
				posX += BESIC_SPEED;
				t++;
				if (t == ARUKU * 5) t = 0;
				endTimer++;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, endTimer);
				DrawGraph(0, 0, GHandle20, TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				if (endTimer >= 256)
				{
					StopSoundMem(SHandle15);
					ChangeVolumeSoundMem(255 * sound / 100, SHandle16);
					PlaySoundMem(SHandle16, DX_PLAYTYPE_BACK,FALSE);
					endTimer = 256;
					DrawString(WIN_WIDTH / 2 - 25, 562 - scrollY, "原案", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 32.5, 592 - scrollY, "フーマ", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 50, 690 - scrollY, "企画構成", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 32.5, 720 - scrollY, "フーマ", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 87.5, 820 - scrollY, "ゲームデザイン", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 32.5, 850 - scrollY, "フーマ", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 75, 950 - scrollY, "ステージ制作", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 32.5, 980 - scrollY, "フーマ", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 137.5, 1080 - scrollY, "ゲームキャラクター制作", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 32.5, 1110 - scrollY, "フーマ", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 87.5, 1210 - scrollY, "モーション制作", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 32.5, 1240 - scrollY, "フーマ", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 112.5, 1340 - scrollY, "ステージプログラム", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 32.5, 1370 - scrollY, "フーマ", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 137.5, 1470 - scrollY, "キャラクタープログラム", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 32.5, 1500 - scrollY, "フーマ", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 112.5, 1600 - scrollY, "システムプログラム", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 32.5, 1630 - scrollY, "フーマ", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 137.5, 1730 - scrollY, "グラフィックプログラム", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 32.5, 1760 - scrollY, "フーマ", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 175, 1860 - scrollY, "エグゼクティブプロデューサー", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 32.5, 1890 - scrollY, "フーマ", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 62.5, 1990 - scrollY, "製作総指揮", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 32.5, 2020 - scrollY, "フーマ", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 87.5, 2120 - scrollY, "プロデューサー", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 32.5, 2150 - scrollY, "フーマ", GetColor(255, 255, 255));
					DrawString(WIN_WIDTH / 2 - 110, tartle - scrollY, "TURTLE・DEATH", endColor);
					if (!((tartle - scrollY) <= WIN_HEIGHT / 2))
					{
						scrollY += 1;
					}
					if ((tartle - scrollY) <= WIN_HEIGHT / 2)
					{
						endColor = GetColor(255, 0, 0);
						DrawString(WIN_WIDTH - 300, WIN_HEIGHT - 30, "ENTERでタイトル", GetColor(255, 0, 0));
						if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
						{
							clearFlag = 0;
							titleFlag = 0;
						}
					}
				}
			}
			if (komentoFlag == 1)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
				DrawGraph(0, 0, GHandle9, TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				DrawGraph(localX - r, posY - r, GHandle1[i / 5], TRUE);
				i++;
				if (i == TAIKI * 5) i = 0;
				if (Name != "\0")
				{
					DrawFormatString(32, 17, GetColor(255, 255, 255), "%10s：", Name);
					DrawMOZI(210, 17, "今日もいつも通り", nameCount, WIN_WIDTH);
					nameCount++;
					if (nameCount >= 100)
					{
						DrawMOZI(485, 17, "10000メートル走り切るぞー", nameCount - 100, WIN_WIDTH);
					}
					if (nameCount >= 160 && kakuninFlag == 0)
					{
						DrawString(WIN_WIDTH - 200, 0 + 40, "ENTER", GetColor(255, 0, 0));
						if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
						{
							komentoFlag = 0;
						}
					}
					if (kakuninFlag == 1)
					{
						DrawString(WIN_WIDTH - 200, 0 + 40, "ENTER", GetColor(255, 0, 0));
						if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
						{
							komentoFlag = 0;
						}
					}
					if (CheckHitKey(KEY_INPUT_RETURN))
					{
						nameCount = 150;
						kakuninFlag = 1;
					}
				}
			}
		}

		if (sibouFlag == 1)
		{
			DrawGraph(0, 312, GHandle14, TRUE);
			if (hariFlag == 1)
			{
				if (sibouCount == 1 && koukaonnFlag == 1)
				{
					PlaySoundMem(SHandle4, DX_PLAYTYPE_BACK);
				}
				sibouCount++;
				DrawMOZI(50, 330, "グサッ", sibouCount, WIN_WIDTH);
				if (sibouCount >= 70)
				{
					sibouCount = 70;
					DrawMOZI(150, 330, "何かが体を貫いたような鈍い音がした…", sibouCount2, WIN_WIDTH);
					sibouCount2++;
					if (sibouCount2 >= 38)
					{
						DrawString(WIN_WIDTH - 200, WIN_HEIGHT - 40, "ENTER", GetColor(255, 0, 0));
					}
					if (sibouCount2 >= 38 && keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
					{
						sibouFlag = 2;
					}
				}
			}
			if (isExplosionFlag == 1)
			{
				if (sibouCount == 1 && koukaonnFlag == 1)
				{
					PlaySoundMem(SHandle5, DX_PLAYTYPE_BACK);
				}
				DrawMOZI(50, 330, "ドンッ", sibouCount, WIN_WIDTH);
				sibouCount++;
				if (sibouCount >= 70)
				{
					sibouCount = 70;
					DrawMOZI(150, 330, "不快な音とともにまるで踊るかのように血肉がそこら中に散らばった…", sibouCount2, WIN_WIDTH);
					sibouCount2++;
					if (sibouCount2 >= 65)
					{
						DrawString(WIN_WIDTH - 200, WIN_HEIGHT - 40, "ENTER", GetColor(255, 0, 0));
					}
					if (sibouCount2 >= 65 && keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
					{
						sibouFlag = 2;
					}
				}
			}
			if (mameFlag == 1)
			{
				if (sibouCount == 1 && koukaonnFlag == 1)
				{
					PlaySoundMem(SHandle4, DX_PLAYTYPE_BACK);
				}
				DrawMOZI(50, 330, "グサッ", sibouCount, WIN_WIDTH);
				sibouCount++;
				if (sibouCount >= 70)
				{
					sibouCount = 70;
					DrawMOZI(150, 330, "気が付いたら腹に刀が刺さっていた…", sibouCount2, WIN_WIDTH);
					sibouCount2++;
					if (sibouCount2 == 30 && koukaonnFlag == 1)
					{
						PlaySoundMem(SHandle10, DX_PLAYTYPE_BACK);
					}
					if (sibouCount2 >= 35)
					{
						DrawString(WIN_WIDTH - 200, WIN_HEIGHT - 40, "ENTER", GetColor(255, 0, 0));
					}
					if (sibouCount2 >=35 && keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
					{
						sibouFlag = 2;
					}
				}
			}
			if (ropuFlag == 1)
			{
				if (sibouCount == 40 && koukaonnFlag == 1)
				{
					PlaySoundMem(SHandle8, DX_PLAYTYPE_BACK);
				}
				DrawMOZI(50, 330, "つるしてあったロープがまるで生きてるかのように絡みついてきた", sibouCount, WIN_WIDTH);
				sibouCount++;
				if (sibouCount >= 200)
				{
					sibouCount = 200;
					DrawMOZI(50, 360, "気が付いたら呼吸ができなくなっていた…", sibouCount2, WIN_WIDTH);
					sibouCount2++;
					if (sibouCount2 >= 39)
					{
						DrawString(WIN_WIDTH - 200, WIN_HEIGHT - 40, "ENTER", GetColor(255, 0, 0));
					}
					if (sibouCount2 >= 39 && keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
					{
						sibouFlag = 2;
					}
				}
			}
			if (honooFlag == 1)
			{
				if (sibouCount == 99 && koukaonnFlag == 1)
				{
					PlaySoundMem(SHandle9, DX_PLAYTYPE_BACK);
				}
				DrawMOZI(50, 330, "炎の魔物に触れてしまった", sibouCount, WIN_WIDTH);
				sibouCount++;
				if (sibouCount >= 100)
				{
					sibouCount = 100;
					DrawMOZI(50, 360, "引火した炎は待つことを知らず、無情にも一瞬で全身を包み込んだ…", sibouCount2, WIN_WIDTH);
					sibouCount2++;
					if (sibouCount2 >= 39)
					{
						DrawString(WIN_WIDTH - 200, WIN_HEIGHT - 40, "ENTER", GetColor(255, 0, 0));
					}
					if (sibouCount2 >= 39 && keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
					{
						sibouFlag = 2;
					}
				}
			}
			if (syokkuFlag == 1)
			{
				if (sibouCount == 30 && koukaonnFlag == 1)
				{
					PlaySoundMem(SHandle11, DX_PLAYTYPE_BACK);
				}
				DrawMOZI(50, 330, "不意に足元を見たら生首があった", sibouCount, WIN_WIDTH);
				sibouCount++;
				if (sibouCount >= 200)
				{
					sibouCount = 200;
					DrawMOZI(50, 360, "あまりの生々しさに急激な吐き気と意識が遠のいていくのを感じる", sibouCount2, WIN_WIDTH);
					sibouCount2++;
					if (sibouCount2 >= 93)
					{
						DrawString(WIN_WIDTH - 200, WIN_HEIGHT - 40, "ENTER", GetColor(255, 0, 0));
					}
					if (sibouCount2 >= 93 && keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
					{
						sibouFlag = 2;
					}
				}
			}
			if (funnsiFlag == 1)
			{
				if (sibouCount == 0)
				{
					PlaySoundMem(SHandle12, DX_PLAYTYPE_BACK);
				}
				DrawMOZI(50, 330, "運動すると決意した、それなのに一向に動かない自分に激怒した", sibouCount, WIN_WIDTH);
				sibouCount++;
				if (sibouCount >= 200)
				{
					sibouCount = 200;
					DrawMOZI(50, 360, "怒りは収まることはなく頭に血が上っていきそのまま死に絶えるのであった…", sibouCount2, WIN_WIDTH);
					sibouCount2++;
					if (sibouCount2 >= 72)
					{
						DrawString(WIN_WIDTH - 200, WIN_HEIGHT - 40, "ENTER", GetColor(255, 0, 0));
					}
					if (sibouCount2 >= 72 && keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
					{
						sibouFlag = 2;
					}
				}
			}
		}

		if (sibouFlag == 2)
		{
			StopSoundMem(SHandle15);
			DrawGraph(0 - backGroundX, 0, GHandle4, TRUE);
			DrawGraph(WIN_WIDTH - backGroundX, 0, GHandle4, TRUE);
			haikeiX += HAIKEI_SPEED;
			if (koukaonnFlag == 0)
			{
				DrawGraph(0, 0, GHandle18, TRUE);
			}
			if (koukaonnFlag == 1)
			{
				DrawGraph(0, 0, GHandle15, TRUE);
			}
			DrawMOZI(600, 200, Name, hakaCount, 200);
			hakaCount++;
			if (hakaCount == 40)
			{
				PlaySoundMem(SHandle13, DX_PLAYTYPE_BACK);
			}
			if (hakaCount == 120)
			{
				PlaySoundMem(SHandle14, DX_PLAYTYPE_BACK);
			}
			if (hariFlag == 1)
			{
				if (hakaCount >= 40)
				{
					SetFontSize(20);
					DrawString(550, 160, "死\n因", GetColor(255, 255, 255));
				}
				if (hakaCount >= 80)
				{
					DrawString(550, 210, "刺\n死", GetColor(255, 0, 255));
				}
				if (hakaCount >= 140)
				{
					DrawString(490, 160, "ヒ\nン\nト",GetColor(255,255,255));
				}
				if (hakaCount >= 180)
				{
					DrawString(450, 190, "待\nつ\nこ\nと\nも\n大\n事", GetColor(0, 255, 255));
				}
				if (hakaCount >= 230)
				{
					DrawString(390, 160, "E\nN\nT\nE\nR", GetColor(255, 0, 0));
					DrawString(360, 190, "で\nタ\nイ\nト\nル", GetColor(255, 0, 0));
					if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
					{
						titleFlag = 0;
						sibouFlag = 0;
					}
				}
			}
			if (isExplosionFlag == 1)
			{
				if (hakaCount >= 40)
				{
					SetFontSize(20);
					DrawString(550, 160, "死\n因", GetColor(255, 255, 255));
				}
				if (hakaCount >= 80)
				{
					DrawString(550, 210, "爆\n死", GetColor(255, 0, 255));
				}
				if (hakaCount >= 140)
				{
					DrawString(490, 160, "ヒ\nン\nト", GetColor(255, 255, 255));
				}
				if (hakaCount >= 180)
				{
					DrawString(450, 190, "跳\nぶ\nこ\nと\nも\n大\n切", GetColor(0, 255, 255));
				}
				if (hakaCount >= 230)
				{
					DrawString(390, 160, "E\nN\nT\nE\nR", GetColor(255, 0, 0));
					DrawString(360, 190, "で\nタ\nイ\nト\nル", GetColor(255, 0, 0));
					if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
					{
						titleFlag = 0;
						sibouFlag = 0;
					}
				}
			}
			if (mameFlag == 1)
			{
				if (hakaCount >= 40)
				{
					SetFontSize(20);
					DrawString(550, 160, "死\n因", GetColor(255, 255, 255));
				}
				if (hakaCount >= 80)
				{
					DrawString(550, 210, "通\nり\n魔\n殺\n亀", GetColor(255, 0, 255));
				}
				if (hakaCount >= 140)
				{
					DrawString(490, 160, "ヒ\nン\nト", GetColor(255, 255, 255));
				}
				if (hakaCount >= 180)
				{
					DrawString(450, 190, "ジ\nャ\nン\nプ\nを", GetColor(0, 255, 255));
					DrawString(425, 250, "う\nま\nく\n使\nお\nう", GetColor(0, 255, 255));
				}
				if (hakaCount >= 230)
				{
					DrawString(390, 160, "E\nN\nT\nE\nR", GetColor(255, 0, 0));
					DrawString(360, 190, "で\nタ\nイ\nト\nル", GetColor(255, 0, 0));
					if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
					{
						titleFlag = 0;
						sibouFlag = 0;
					}
				}
			}
			if (ropuFlag == 1)
			{
				if (hakaCount >= 40)
				{
					SetFontSize(20);
					DrawString(550, 160, "死\n因", GetColor(255, 255, 255));
				}
				if (hakaCount >= 80)
				{
					DrawString(550, 210, "縛\n死", GetColor(255, 0, 255));
				}
				if (hakaCount >= 140)
				{
					DrawString(490, 160, "ヒ\nン\nト", GetColor(255, 255, 255));
				}
				if (hakaCount >= 180)
				{
					DrawString(450, 190, "跳\nび\nす\nぎ\n注\n意", GetColor(0, 255, 255));
				}
				if (hakaCount >= 230)
				{
					DrawString(390, 160, "E\nN\nT\nE\nR", GetColor(255, 0, 0));
					DrawString(360, 190, "で\nタ\nイ\nト\nル", GetColor(255, 0, 0));
					if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
					{
						titleFlag = 0;
						sibouFlag = 0;
					}
				}
			}
			if (honooFlag == 1)
			{
				if (hakaCount >= 40)
				{
					SetFontSize(20);
					DrawString(550, 160, "死\n因", GetColor(255, 255, 255));
				}
				if (hakaCount >= 80)
				{
					DrawString(550, 210, "焼\n死", GetColor(255, 0, 255));
				}
				if (hakaCount >= 140)
				{
					DrawString(490, 160, "ヒ\nン\nト", GetColor(255, 255, 255));
				}
				if (hakaCount >= 180)
				{
					DrawString(450, 170, "見\nた\n目\nに\n騙\nさ\nれ\nる\nな", GetColor(0, 255, 255));
				}
				if (hakaCount >= 230)
				{
					DrawString(390, 160, "E\nN\nT\nE\nR", GetColor(255, 0, 0));
					DrawString(360, 190, "で\nタ\nイ\nト\nル", GetColor(255, 0, 0));
					if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
					{
						titleFlag = 0;
						sibouFlag = 0;
					}
				}
			}
			if (syokkuFlag == 1)
			{
				if (hakaCount >= 40)
				{
					SetFontSize(20);
					DrawString(550, 160, "死\n因", GetColor(255, 255, 255));
				}
				if (hakaCount >= 80)
				{
					DrawString(550, 210, "シ\nョ\nッ\nク\n死", GetColor(255, 0, 255));
				}
				if (hakaCount >= 140)
				{
					DrawString(490, 160, "ヒ\nン\nト", GetColor(255, 255, 255));
				}
				if (hakaCount >= 180)
				{
					DrawString(450, 170, "あ\nた\nり\n判\n定\n小\nさ\nめ", GetColor(0, 255, 255));
				}
				if (hakaCount >= 230)
				{
					DrawString(390, 160, "E\nN\nT\nE\nR", GetColor(255, 0, 0));
					DrawString(360, 190, "で\nタ\nイ\nト\nル", GetColor(255, 0, 0));
					if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
					{
						titleFlag = 0;
						sibouFlag = 0;
					}
				}
			}
			if (funnsiFlag == 1)
			{
				if (hakaCount >= 40)
				{
					SetFontSize(20);
					DrawString(550, 160, "レ\nア\n死\n因", GetColor(255, 255, 255));
				}
				if (hakaCount >= 80)
				{
					DrawString(550, 260, "憤\n死", GetColor(255, 0, 255));
				}
				if (hakaCount >= 140)
				{
					DrawString(490, 160, "ヒ\nン\nト", GetColor(255, 255, 255));
				}
				if (hakaCount >= 180)
				{
					DrawString(450, 150, "凄\nい\n死\nに\n方\nし\nま\nし\nた\nね", GetColor(0, 255, 255));
				}
				if (hakaCount >= 230)
				{
					DrawString(390, 160, "E\nN\nT\nE\nR", GetColor(255, 0, 0));
					DrawString(360, 190, "で\nタ\nイ\nト\nル", GetColor(255, 0, 0));
					if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
					{
						titleFlag = 0;
						sibouFlag = 0;
					}
				}
			}
		}
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
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1 || (titleY == 460 && CheckHitKey(KEY_INPUT_RETURN)))
		{
			break;
		}
	}
	// Dxライブラリ終了処理
	InitGraph();
	InitSoundMem();
	DxLib_End();

	// 正常終了
	return 0;
}