
//�s�N�Z���V�F�[�_�[

#include "common.hlsl"

//�e�N�X�`��
Texture2D	g_texture	:	register(t0);//�e�N�X�`��0�Ԃ��g��
//�T���v���[
SamplerState g_SamplerState	:register(s0);	//�T���v���[0���g��

//
//
//
void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//���͂��ꂽ�F�����̂܂܃s�N�Z���F�Ƃ��ďo��
	outDiffuse = In.Diffuse;

	//���͂��ꂽ�e�N�X�`�����W�����ƂɃe�N�X�`���摜�̃s�N�Z���E��
	//�擾���āA������o�͂���B
	outDiffuse = g_texture.Sample(g_SamplerState, In.TexCoord);

	//���_�̐F�ƃe�N�X�`���̐F���������ďo��
	outDiffuse *= In.Diffuse;

	//------------------------
	//�s�N�Z���V�F�[�_�[�e�X�g
	//------------------------
	//�l�K�|�W���]
	//outDiffuse = 1.0f - g_texture.Sample(g_SamplerState, In.TexCoord);
	//outDiffuse.a = 1.0f;

	//�O���[�X�P�[��
	//outDiffuse = g_texture.Sample(g_SamplerState,In.TexCoord);
	//outDiffuse = 0.299*outDiffuse.r + 0.587 * outDiffuse.g + 0.114*outDiffuse.b;
	//outDiffuse.a = 1.0f;

	//�e�N�X�`����RGB�̐F��BGR�ɓ���ւ��ďo��
	//float4 color = g_texture.Sample(g_SamplerState,In.TexCoord);
	//outDiffuse.r = color.b;
	//outDiffuse.g = color.g;
	//outDiffuse.b = color.r;

	//outDiffuse.a = 1.0f;

	//�e�N�X�`���̐F��16�悵�ďo��
	//outDiffuse = g_texture.Sample(g_SamplerState, In.TexCoord);
	//outDiffuse *= outDiffuse;
	//outDiffuse *= outDiffuse;
	//outDiffuse *= outDiffuse;
	//outDiffuse *= outDiffuse;

	//outDiffuse.a = 1.0f;

	//�Z�s�A�ϊ�
	//outDiffuse = g_texture.Sample(g_SamplerState, In.TexCoord);
	//outDiffuse = 0.299*outDiffuse.r + 0.587 * outDiffuse.g + 0.114 * outDiffuse.b;
	//float4 sepia = float4(1.07, 0.74, 0.43, 1.0f);
	//outDiffuse *= sepia;
	//outDiffuse.a = 1.0;

}