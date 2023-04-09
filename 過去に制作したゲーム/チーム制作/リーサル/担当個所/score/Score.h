#pragma once
#include "Player.h"
#include <memory>
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
//�X�R�A�܂Ƃ߂�N���X
class Score {
public:
	void SetPlayer(Player* player) { this->player.reset(player); }
	//�R���X�g���N�^
	Score();
	//�f�X�g���N�^
	~Score();

	//������
	void Initialize();
	//�X�V
	bool Update(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput);
	//�X�V
	bool TutorialUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput);
	//�`��
	void Draw();

	//FormatString�p
	void FormatDraw();
public:
	//getter setter
	const int GetScorePoint() { return ScorePoint; }

	const int GetGameTimer() { return GameTimer; }

	void SetScorePoint(int ScorePoint) { this->ScorePoint = ScorePoint; }
private:
	//�X�R�A
	int ScorePoint;
	//���Ԑ���(�ʃN���X�ł���������)
	int GameTimer;
	//�{��
	int MultPoint;
	//�p���N���X
	unique_ptr<Player> player = nullptr;

	float scorePosX;
	float scorePosY;

	float scorePosX2;
	float scorePosY2;

	int knockCount;
	int alphaCount;

	int scoreTex;
	int timeTex;
};