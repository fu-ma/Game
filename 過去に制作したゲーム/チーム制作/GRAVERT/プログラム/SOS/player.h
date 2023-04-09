#pragma once
#include <DxLib.h>
#include"particle.h"

class player
{
public:
	float posX = 100;
	float posY = 700;
	float velY = 0;//計算後の速さ
	float speed = 0;//プレイヤーの速度
	float t = 0;//一フレーム
	float gravity = 9.8;//重力加速度
	float size = 1.0f;
	float rotation = 0;
	float rightMove = 5;
	float leftMove = 5;
	int gameoverFlag = 0;
	int move(int direction,float *pos,float *move);
	void update();
	void uraUpdate();
	void gravityUpdate();
};
