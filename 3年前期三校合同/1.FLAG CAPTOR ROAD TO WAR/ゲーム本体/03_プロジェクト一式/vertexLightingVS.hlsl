#include "common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
	//���_�@�������[���h�s��ŉ�]������(���_�Ɠ�����]��������)
	float4 worldNormal, normal;
	normal = float4(In.Normal.xyz, 0.0f);	//���_�@���̏���w=0�Ƃ���(���s�ړ����Ȃ�)
	worldNormal = mul( normal,World);		//�x�N�g�����s��ŕϊ�
	worldNormal = normalize(worldNormal);	//���K������

	//���邳�̌v�Z
	float light = -dot(Light.Direction,worldNormal);	//���Ɩ@������ς��v�Z
	//float light = 0.5 - 0.5 * dot(Light.Direction.xyz, worldNormal.xyz);	//(�n�[�t�����o�[�g)
	light = saturate(light);				//���邳���T�`�����[�g����

	//���_�̖��邳���o�͂���
	Out.Diffuse = light;
	Out.Diffuse.a = 1.0f;

	//�ȉ��ʏ��VS�̏���

	matrix wvp;		//�v�Z�p�s��

	//wvp = ���[���h�s�� * �r���[�s��
	wvp = mul(World, View);

	//wvp = wvp * �v���W�F�N�V�����s��
	wvp = mul(wvp, Projection);

	//���_���W * �ϊ��s�� ���o��
	Out.Position = mul(In.Position, wvp);

	Out.Normal = worldNormal;
	//�e�N�X�`�����W
	Out.TexCoord = In.TexCoord;

}