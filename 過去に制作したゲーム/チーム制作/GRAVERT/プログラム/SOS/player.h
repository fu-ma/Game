#pragma once
#include <DxLib.h>
#include"particle.h"

class player
{
public:
	float posX = 100;
	float posY = 700;
	float velY = 0;//�v�Z��̑���
	float speed = 0;//�v���C���[�̑��x
	float t = 0;//��t���[��
	float gravity = 9.8;//�d�͉����x
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
