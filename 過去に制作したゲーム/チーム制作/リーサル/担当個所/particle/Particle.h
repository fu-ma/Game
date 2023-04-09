#include "math.h"
#include "DxLib.h"
#include <array>   
#include <memory>
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
//�p�[�e�B�N���̃}�b�N�X��
const int Particle_Max = 60;


class Particle {
protected:
public:
	//void SetPlayer(Player* player) { this->player.reset(player); }
	Particle();

	/// <summary>
	/// 3D�I�u�W�F�N�g����
	/// </summary>
	/// <returns></returns>
	//static Player* Create(Model* model = nullptr);

public:

	/// <summary>
	/// ������
	/// </summary>
	/// <returns>����</returns>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update(float StartPosX,float StartPosY, int Timer, int TargetTimer);

	void NormalParticle(float StartPosX, float StartPosY, int Timer, int TargetTimer);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
public:
	/*void SetParticleType(int ParticleType) { this->ParticleType = ParticleType; }
	void SetParticleBreak(bool ParticleBreak) { this->ParticleBreak = ParticleBreak; }
	void SetStartScale(float StartScale) { this->StartScale = StartScale; }
	void SetAddScale(float  AddScale) { this->AddScale = AddScale; }
	void SetEndCount(int EndCount) { this->EndCount = EndCount; }*/
	void SetTexture(int tex) { this->texture = tex; }
private:
	int texture = 0;
	bool Alive[Particle_Max];
	float particlePosX[Particle_Max];
	float particlePosY[Particle_Max];
	float particleR[Particle_Max];
	float angle[Particle_Max];
	float speed[Particle_Max];
	float alpha[Particle_Max];
	float particleXG[Particle_Max];
	float particleYG[Particle_Max];
	float scale[Particle_Max];
	float x[Particle_Max];
	float y[Particle_Max];
	float radius[Particle_Max];
	
	float StartPosX = 0.0f;
	float StartPosY = 0.0f;
	//unique_ptr<Player> player;
	int NormalParticleCount = 60;
	int WideParticleCount = 10;
	int ParticleType = 0;
	int EndCount = 0;
	bool ParticleBreak = false;
	float StartScale = 0.1f;
	float AddScale = 0.02f;
	enum Type {
		Normal,
		Wide,
	};
};