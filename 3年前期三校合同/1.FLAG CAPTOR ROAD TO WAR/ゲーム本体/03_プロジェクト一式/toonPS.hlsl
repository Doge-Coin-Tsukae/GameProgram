//�u�����t�H�����ʔ���

#include "common.hlsl"
Texture2D g_Texture : register(t0); //�e�N�X�`���O�� 
SamplerState g_SamplerState : register(s0); //�T���v���[�O��

void main(in PS_IN In, out float4 outDiffuse : SV_Target) 
{
	float4 normal = normalize(In.Normal);

	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);	//�e�N�X�`���̐F�擾
	outDiffuse.a *= In.Diffuse.a;								//���͕ʏ���(���邳�͂���Ȃ�)

	float  light = 0.5f - dot(normal.xyz, Light.Direction.xyz) *0.5f;

	if (light > 0.8f)
	{
		light=0.8f;
	}
	else if (light > 0.5f)
	{
		light = 0.6f;
	}
	else
	{
		light = 0.2f;
	}

	outDiffuse.rgb *= In.Diffuse.rgb * light;					//���_�F�Ɩ��邳����Z

	//�s�N�Z������J�����̃x�N�g���i�����x�N�g���j 
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev); //���K��

	float3 refv = reflect(Light.Direction.xyz, normal.xyz);
	refv = normalize(refv);

	/*float specular = -dot(eyev, refv);
	specular = saturate(specular);
	specular = pow(specular,30);
	outDiffuse.rgb += specular;*/

	float rim = 1.0 + dot(eyev, normal.xyz); //�����Ɩ@���̓��ς𖾂邳�ɕϊ�����
	rim = pow(rim, 3) * 2.0f; //�X�y�L�����Ɠ����悤�ȏ�����K���ɍs���B 
	rim = saturate(rim); //rim���T�`�����[�g����
	outDiffuse.rgb -= rim; //�ʏ�̐F�։��Z����B 
	outDiffuse.a = In.Diffuse.a;
}