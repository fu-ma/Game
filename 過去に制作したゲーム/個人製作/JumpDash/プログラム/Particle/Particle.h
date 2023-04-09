#pragma once
#include "ParticleManager.h"
#include <DirectXMath.h>
#include<math.h>

enum class direction
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

class Particle
{
private: // エイリアス
	using XMFLOAT3 = DirectX::XMFLOAT3;

private: //メンバ変数
	XMFLOAT3 vel;
	XMFLOAT3 acc;
	ParticleManager *particleMan;

	float rnd_vel;
	float rnd_acc;
public:
	Particle();
	Particle(const wchar_t *filename);
	~Particle();
	void Init(float rnd_vel = 0.1f, float rnd_acc = 0.001f);
	void AddParticle(XMFLOAT3 position,int life = 0);
	void CiycleParticle(const XMFLOAT3 emitterPosition = { 0, 0, 0 }, float startSize = 1.0f, float endSize = 0.0f, int life = 60);
	void AddMiniParticle(XMFLOAT3 position);
	void AddDirectionParticle(XMFLOAT3 position, int direction);
	void AddDirectionParticle2(XMFLOAT3 position, int direction);

	void Update();
	void Draw();
};