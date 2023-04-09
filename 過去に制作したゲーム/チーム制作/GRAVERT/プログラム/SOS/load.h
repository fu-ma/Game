#pragma once
#include"DxLib.h"

class load
{
public:
	int gHandle[9];
	int GH = LoadGraph("resource////1.png");
	int GH2 = LoadGraph("resource////2.png");
	int GH3[3];
	int GH4 = LoadGraph("resource////title.png");
	int GH5 = LoadGraph("resource////effect.png");
	int GH6[12];
	int GH7 = LoadGraph("resource////smile.png");
	int GH8= LoadGraph("resource////ui.png");
	int GH9[2];
	int GH10 = LoadGraph("resource////ty.png");
	int GH12[2];
	int SHandle1 = LoadSoundMem("resource////death.mp3");
	int SHandle2 = LoadSoundMem("resource////space.mp3");
	int SHandle3 = LoadSoundMem("resource////game.mp3");
	int SHandle4 = LoadSoundMem("resource////PC.mp3");
	int SHandle5 = LoadSoundMem("resource////fedoin.mp3");
	int SHandle6 = LoadSoundMem("resource////zyuuryoku.mp3");
	int SHandle7 = LoadSoundMem("resource////gravity.mp3");
	int SHandle8 = LoadSoundMem("resource////tyakuti.mp3");
	int SHandle9 = LoadSoundMem("resource////kuria.mp3");
};
