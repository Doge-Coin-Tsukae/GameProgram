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
	outDiffuse.rgb *= In.Diffuse.rgb * light;					//���_�F�Ɩ��邳����Z

	//�u�����t�H�����ʔ��˂�������
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz; //�����x�N�g���쐬
	eyev = normalize(eyev);									 //���K������

	float3 halfv = eyev + Light.Direction.xyz; //���˃x�N�g���v�Z
	halfv = normalize(halfv);									//���K��

	float specular = -dot(halfv, normal.xyz);						//���όv�Z
	specular = pow(specular,30);							//30�悷��(�I�u�W�F�N�g�̕\�ʂ��Ă��Ă����������̂Ȃ�΁A�X�̐�����傫������)
	specular = saturate(specular);

	outDiffuse.rgb += specular;

}