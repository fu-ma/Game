cbuffer cbuff0 : register(b0)
{
	matrix mat; // �R�c�ϊ��s��
};

struct VSOutput
{
	float4 pos : SV_POSITION; // �V�X�e���p���_���W
};

struct GSOutput
{
	float4 svpos : SV_POSITION; // �V�X�e���p���_���W
	float2 uv  :TEXCOORD; // uv�l
};