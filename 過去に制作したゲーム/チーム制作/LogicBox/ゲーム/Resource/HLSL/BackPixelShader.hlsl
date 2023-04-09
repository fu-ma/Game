#include "OBJHeader.hlsli"

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
	//�e�N�X�`���}�b�s���O
	float4 texcolor = tex.Sample(smp, input.uv);
	/*texcolor.g = texcolor.r;
	texcolor.b = texcolor.r;
	texcolor.rgb -= 0.1f;*/
	return texcolor;
}