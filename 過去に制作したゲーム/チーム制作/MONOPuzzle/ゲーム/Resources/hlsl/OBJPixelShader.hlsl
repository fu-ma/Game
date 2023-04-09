#include "OBJShaderHeader.hlsli"

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

float4 main(GSOutput input):SV_TARGET
{
	float4 texColor = float4(tex.Sample(smp, input.uv));

	//float3 light = normalize(float3(0, 1, 1)); //�E�����������C�g
	//float diffuse = saturate(dot(-light, input.normal));
	
	float3 shade_color;
	shade_color = m_ambient;
	shade_color += m_diffuse /** diffuse*/;
	
	float4 texcolor = tex.Sample(smp, input.uv);
	
	return float4(texcolor.rgb * shade_color, texcolor.a * m_alpha);
}