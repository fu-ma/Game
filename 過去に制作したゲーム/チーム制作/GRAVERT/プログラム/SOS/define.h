#pragma once
//�萔
#define MOVE 5//�ړ���
#define SINDOU 300//�U��
#define MOVEBLOCK_MAX 26//�����u���b�N�̍ő吔
#define TIMER 1000//�U�����鎞��
#define BLOCK_SIZE 32//�u���b�N�̃T�C�Y
#define MAP_HEIGHT 30//�}�b�v�̍����i�u���b�N�̐��j
#define MAP_WIDTH 40//�}�b�v�̉����i�u���b�N�̐��j
#define PLAYER_R 16//�v���C���[�̔��a
#define TURNOVER_RATE 0.2//��]��
#define GRAVITY_MAX 4//�d�͂̍ő�l
#define BLOCK_MAX 40//�����u���b�N�̍ő吔
#define MAX_ARRAY 10
#define HAYASA 5//�A�j���[�V�������x
#define MAX_HANABI 200//�ԉ΂̌�
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
