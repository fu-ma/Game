#pragma once
//�����蔻��p�̃N���X
class Collision {
public:
	//��_�Ԃ̋���
	static float GetLength(float posX, float posY, float posX2, float posY2);
	//�~�Ɖ~
	static bool CircleCollision(const float& X1, const float& Y1, const float& R1, const float& X2, const float& Y2, const float& R2);
};