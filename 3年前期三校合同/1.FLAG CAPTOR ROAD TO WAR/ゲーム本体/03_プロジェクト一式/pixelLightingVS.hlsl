#include "common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
	matrix wvp;		//�v�Z�p�s��

	//wvp = ���[���h�s�� * �r���[�s��
	wvp = mul(World, View);

	//wvp = wvp * �v���W�F�N�V�����s��
	wvp = mul(wvp, Projection);

	//���_���W * �ϊ��s�� ���o��
	Out.Position = mul(In.Position, wvp);

	//���_�@�������[���h�s��ŉ�]������(���_�Ɠ�����]��������)
	float4 worldNormal, normal;
	normal = float4(In.Normal.xyz, 0.0f);	//���_�@���̏���w=0�Ƃ���(���s�ړ����Ȃ�)
	worldNormal = mul(normal, World);		//�x�N�g�����s��ŕϊ�
	worldNormal = normalize(worldNormal);	//���K������
	Out.Normal = worldNormal;

	Out.Diffuse = In.Diffuse; //�f�t���[�Y(���_�̖��邳)������
	Out.TexCoord = In.TexCoord;

	Out.WorldPosition = mul(In.Position, World);
}