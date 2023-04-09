#include "Particle.h"
using namespace DirectX;

Particle::Particle()
{
}

Particle::Particle(const wchar_t *filename)
{
	particleMan = new ParticleManager();
	particleMan = ParticleManager::Create();
	particleMan->Init(filename);
}

Particle::~Particle()
{
	delete particleMan;
	particleMan = nullptr;
}

void Particle::Init(float rnd_vel, float rnd_acc)
{
	this->rnd_vel = rnd_vel;
	this->rnd_acc = rnd_acc;
}

void Particle::AddParticle(XMFLOAT3 position,int life)
{
	for (int i = 0; i < 100; i++)
	{
		//X,Y,Z全て[-0.05f,+0.05f]でランダムに分布
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		//重力に見立ててYのみ[-0.0001f,0]でランダムに分布
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		//追加
		particleMan->Add(life, position, vel, acc, 1.0f, 0.0f);
		break;
	}
}

void Particle::CiycleParticle(const XMFLOAT3 emitterPosition, float startSize, float endSize, int life)
{
	rnd_vel = 0.01f;
	for (int i = 0; i < 11; i++)
	{
		XMFLOAT3 pos{};//初期値
		pos = emitterPosition;
		XMFLOAT3 vel{};//初速
		XMVECTOR a;
		a.m128_f32[0] = cosf((float)i * 0.36f * 3.1415f);
		a.m128_f32[1] = sinf((float)i * 0.36f * 3.1415f);
		a.m128_f32[2] = 0;
		XMVector3Normalize(a);
		vel.x = a.m128_f32[0] / 50;
		vel.y = a.m128_f32[1] / 50;
		XMFLOAT3 acc = {};
		particleMan->Add(life, pos, vel, acc, startSize, endSize);
	}

}

void Particle::AddMiniParticle(XMFLOAT3 position)
{
	rnd_acc = 0.001f;
	rnd_vel = 0.1f;
	for (int i = 0; i < 10; i++)
	{
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		//追加
		particleMan->Add(30, position, vel, acc, 0.2f, 0.0f);
	}
}

void Particle::AddDirectionParticle(XMFLOAT3 position, int direction)
{
	for (int i = 0; i < 10; i++)
	{
		float rnd_vel = 0.01f;
		if (direction == static_cast<int>(direction::UP))
		{
			vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.y = 0.05f;
			vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		}
		if (direction == static_cast<int>(direction::LEFT))
		{
			vel.x = -0.05f;
			vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		}
		if (direction == static_cast<int>(direction::RIGHT))
		{
			vel.x = 0.05f;
			vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		}
		if (direction == static_cast<int>(direction::DOWN))
		{
			vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.y = -0.05f;
			vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		}

		//追加
		particleMan->Add(60, position, vel, acc, 0.2f, 0.0f);
		break;
	}
}

void Particle::AddDirectionParticle2(XMFLOAT3 position, int direction)
{
	for (int i = 0; i < 10; i++)
	{
		float rnd_vel = 0.05f;
		if (direction == static_cast<int>(direction::UP))
		{
			vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.y = 0;
			vel.z = 0;
		}
		if (direction == static_cast<int>(direction::LEFT))
		{
			vel.x = 0;
			vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.z = 0;
		}
		if (direction == static_cast<int>(direction::RIGHT))
		{
			vel.x = 0;
			vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.z = 0;
		}
		if (direction == static_cast<int>(direction::DOWN))
		{
			vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.y = 0;
			vel.z = 0;
		}

		//追加
		particleMan->Add(60, position, vel, acc, 0.5f, 0.0f);
		break;
	}
}

void Particle::Update()
{
	particleMan->Update();
	//particleMan2->Update();
}


void Particle::Draw()
{
	// 3Dオブクジェクトの描画
	particleMan->Draw();
}