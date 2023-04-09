#pragma once
//定数
#define MOVE 5//移動量
#define SINDOU 300//振動
#define MOVEBLOCK_MAX 26//動くブロックの最大数
#define TIMER 1000//振動する時間
#define BLOCK_SIZE 32//ブロックのサイズ
#define MAP_HEIGHT 30//マップの高幅（ブロックの数）
#define MAP_WIDTH 40//マップの横幅（ブロックの数）
#define PLAYER_R 16//プレイヤーの半径
#define TURNOVER_RATE 0.2//回転率
#define GRAVITY_MAX 4//重力の最大値
#define BLOCK_MAX 40//動くブロックの最大数
#define MAX_ARRAY 10
#define HAYASA 5//アニメーション速度
#define MAX_HANABI 200//花火の個数
#define UI 40


const enum direction
{
	LEFT,
	RIGHT,
	NONE
};

const enum block
{
	BACK,
	BLOCK1,
	sitaHari,
	ueHari,
	goru=6,
};

const enum hit
{
	ATARI = 1,
	SIBOU,
	SIBOU2,
	AITEMU
};
