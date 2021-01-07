
//���̃t�@�C���͂ق��̃V�F�[�_�[�t�@�C���փC���N���[�h����

//�e��}�g���N�X�o�b�t�@ �R���X�^���g�o�b�t�@���`
cbuffer WorldBuffer : register(b0)
{
	matrix World;	//�s��ϐ�
}

cbuffer ViewBuffer : register(b1)
{
	matrix View;	//�r���[�s��ϐ� (�J����)
}

cbuffer ProjectionBuffer : register(b2)
{
	matrix Projection; //�v���W�F�N�V�����s��ϐ�
}

//���_�V�F�[�_�[�֓��͂����f�[�^���\���̂̌`�ŕ\��
//����͒��_�o�b�t�@�̓��e���̂���
struct VS_IN
{
	float4 Position		: POSITION0;	//���_���W 0
	float4 Normal		: NORMAL0;		//�@�� 0
	float4 Diffuse		: COLOR0;		//�J���[ 0
	float2 TexCoord		: TEXCOORD0;	//�e�N�X�`�����W 0
};

//�s�N�Z���V�F�[�_�[�֓��͂����f�[�^���\���̂̌`�ŕ\��
struct PS_IN
{
	float4 Position		: SV_POSITION0;	//���_���W 0
	float4 WorldPosition: POSITION0;	//���W 0
	float4 Normal		: NORMAL0;		//�@�� 0
	float4 Diffuse		: COLOR0;		//�J���[ 0
	float2 TexCoord		: TEXCOORD0;	//�e�N�X�`�����W 0
};

//���C�g�I�u�W�F�N�g�\���̂ƃR���X�^���g�o�b�t�@ 
struct LIGHT	//���f�[�^�\����(C���ꂩ��󂯎��)
{
	bool Enable;
	bool3 Dummy; //16Byte���E�p
	float4 Direction;	//���̃x�N�g��
	float4 Diffuse;
	float4 Ambient;
};

//�R���X�^���g�o�b�t�@ C���ꂩ����炤�f�[�^�̓��ꕨ
cbuffer LightBuffer : register(b4)//�R���X�^���g�o�b�t�@�S�ԂƂ��� 
{
	LIGHT Light; //���C�g�\���� 
}

//�J�������W�̎󂯎��p 5�ԂƂ���
cbuffer CameraBuffer:register(b5)
{
	float4 CameraPosition;
}

