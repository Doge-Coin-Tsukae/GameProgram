//���_�V�F�[�_�[

#include "common.hlsl"

//
//in�͓��͂���Ă���f�[�^
//out�͏o�͂���f�[�^
//

void main(in VS_IN In, out PS_IN Out)
{
	matrix wvp;		//�v�Z�p�s��

	//wvp = ���[���h�s�� * �r���[�s��
	wvp = mul(World, View);

	//wvp = wvp * �v���W�F�N�V�����s��
	wvp = mul(wvp, Projection);

	//���_���W * �ϊ��s�� ���o��
	Out.Position = mul( In.Position, wvp);

	//���_�J���[
	Out.Diffuse = In.Diffuse;

	Out.Diffuse.r = 1.0f;
	Out.Diffuse.g = 1.0f;
	Out.Diffuse.b = 1.0f;
	Out.Diffuse.a = 1.0f;

	//�e�N�X�`�����W
	Out.TexCoord = In.TexCoord;

	//�@�t�H�O�W���Z�o
	//Out���o�͂���̂ŁAOut�ɕK�v�ȏ�����������
	//���[�v���g��Ȃ�
}