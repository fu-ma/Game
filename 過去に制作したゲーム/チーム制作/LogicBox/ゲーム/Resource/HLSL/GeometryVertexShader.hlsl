#include "GeometryHeader.hlsli"

VSOutput main(float4 pos : POSITION)
{
	VSOutput output; // �s�N�Z���V�F�[�_�[�ɓn���l
	output.pos = pos;
	/*output.normal = normal;
	output.uv = uv;*/
	return output;
}