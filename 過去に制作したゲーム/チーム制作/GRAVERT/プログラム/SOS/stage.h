#pragma once
#include"define.h"

class stage
{
public:
	int block = BLOCK_SIZE;
	int hidariUe = 0;
	int hidariSita = 0;
	int migiUe = 0;
	int migiSita = 0;
	int map[MAP_HEIGHT][MAP_WIDTH] = { 0 };
	int mapCountX = sizeof(map[0]) / sizeof(map[0][0]);
	int mapCountY = sizeof(map) / sizeof(map[0]);
	float moveblockX[BLOCK_MAX] = { 0 };
	float moveblockY[BLOCK_MAX] = { 0 };
	float moveblockX2[5] = { 0 };
	float moveblockY2[5] = { 0 };
	float moveblockX3[10] = { 0 };
	float moveblockY3[10] = { 0 };
	int moveFlag3 = 0;
	float moveblockX4[29] = { 0 };
	float moveblockY4[29] = { 0 };
	int moveFlag4 = 0;
	float aitemuX[7] = { 0 };
	float aitemuY[7] = { 0 };
	float aitemuX2[9] = { 0 };
	float aitemuY2[9] = { 0 };
	int aitemuFlag3[2] = { 0 };
	float aitemuX3[2] = { 0 };
	float aitemuY3[2] = { 0 };
	int aitemuFlag4[6] = { 0 };
	float aitemuX4[6] = { 0 };
	float aitemuY4[6] = { 0 };
	int aitemuFlag5[8] = { 0 };
	float aitemuX5[8] = { 0 };
	float aitemuY5[8] = { 0 };
	int aitemuFlag6[7] = { 0 };
	float aitemuX6[7] = { 0 };
	float aitemuY6[7] = { 0 };
	int aitemuFlag7[19] = { 0 };
	float aitemuX7[19] = { 0 };
	float aitemuY7[19] = { 0 };
	int aitemuFlag2[9] = { 0 };
	int aitemuFlag[7] = { 0 };
	float moveSpeed[BLOCK_MAX] = { 0 };
	float moveT[BLOCK_MAX] = { 0 };
	float moveVelY[BLOCK_MAX] = { 0 };
	float moveSpeed2[29] = { 0 };
	float moveT2[29] = { 0 };
	float moveVelY2[29] = { 0 };
	float kakudo = 0;
	void Stagechange(int mapID);
	int HIT(const int &posX, const int &posY,const int kirikae);
};
