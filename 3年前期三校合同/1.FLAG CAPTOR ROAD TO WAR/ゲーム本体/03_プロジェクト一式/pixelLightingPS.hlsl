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


	//�t�H�����ʔ��˂�������
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz; //�����x�N�g���쐬
	eyev = normalize(eyev);									 //���K������

	float3 refv = reflect(Light.Direction.xyz,normal.xyz ); //���˃x�N�g���v�Z
	refv = normalize(refv);									//���K��

	float specular = -dot(refv, eyev);						//���όv�Z
	specular = pow(specular,10);							//30�悷��(�I�u�W�F�N�g�̕\�ʂ��Ă��Ă����������̂Ȃ�΁A�X�̐�����傫������)
	specular = saturate(specular);

	outDiffuse.rgb += specular;

}