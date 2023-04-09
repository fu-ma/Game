static const int POINTLIGHT_NUM = 3;
static const int SPOTLIGHT_NUM = 3;
static const int CIRCLESHADOW_NUM = 1;
struct PointLight
{
	float3 lightpos;
	float3 lightcolor;
	float3 lightatten;
	uint active;
};
struct SpotLight
{
	float3 lightv;
	float3 lightpos;
	float3 lightcolor;
	float3 lightatten;
	float2 lightfactoranglecos;
	uint active;
};
struct CircleShadow
{
	float3 dir;
	float pad1;
	float3 casterPos;
	float distanceCasterLight;
	float3 atten;
	float2 factorAngleCos;
	uint active;
};

cbuffer cbuff0 : register(b0)
{
	//matrix mat;
	matrix viewproj;//�r���[�v���W�F�N�V�����s��
	matrix world;//���[���h�s��
	float3 cameraPos;//�J�������W
	float tranceparence;
	float flash;
};

cbuffer cbuff1 : register(b1)
{
	float3 m_ambient : packoffset(c0);
	float3 m_diffuse : packoffset(c1);
	float3 m_specular : packoffset(c2);
	float m_alpha : packoffset(c2.w);
}

struct VSOutput
{
	float4 svpos : SV_POSITION;
	//float3 normal : NORMAL;
	//float4 color : COLOR;
	float4 worldpos : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
};

struct GSOutput
{
	float4 svpos : SV_POSITION; // �V�X�e���p���_���W
	float4 color :COLOR; // �@���x�N�g��
	float2 uv  :TEXCOORD; // uv�l
};

cbuffer cbuff2 : register(b2)
{
	float3 lightv;
	float3 lightcolor;
	PointLight pointLights[POINTLIGHT_NUM];
	SpotLight spotLights[SPOTLIGHT_NUM];
	CircleShadow circleShadows[CIRCLESHADOW_NUM];
}