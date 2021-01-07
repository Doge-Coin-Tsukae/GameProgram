#pragma once

#include "gameobject.h"

#define MAXSHADER  4

class CPlayer : public CGameObject	//�p��(�C���w���^���X)
{
private:
	CAnimationModel* m_Animodel;	//3D�A�j���[�V�������f���N���X
	CSIGHT* m_Sight;			//�Ə�
	CWEAPON* m_Weapon;			//��������
	AABB m_Colider;				//�����蔻��(AABB)
	OBB*  m_Obb;
	D3DXVECTOR3		m_ModelRot;		//���f���̊p�x(���f�����^�������ɂȂ�Ȃ�������ꂽ)
	D3DXVECTOR3		m_Velocity;		//�s������W
	TEAM_NUMBER		m_TeamNumber;	//�������G���̎���
	int				m_Hp;			//�̗�
	float			m_speed;		//���̑���
	bool			m_Death;		//���S�t���O
	bool			m_ready;		//�\���Ă��邩
	char*			m_OldAnimationChara;	//�A�j���[�V�����̖��O�̋���
	char*			m_NowAnimationChara;	//���݂̃A�j���[�V�����̖��O
	int m_Frame = 0;				//�A�j���[�V�����̃t���[��
	float rate = 0;					//�A�j���[�V�����u�����h�̃��[�g

	//������	�V�F�[�_�[�֘A�̕ϐ���ǉ�
	//�z��ɂ��ĕ����̃V�F�[�_�[�𓮂���
	ID3D11VertexShader* m_VertexShader[MAXSHADER];		//���_�V�F�[�_
	ID3D11PixelShader* m_pixelShader[MAXSHADER];		//�s�N�Z���V�F�[�_

	ID3D11InputLayout*  m_VertexLayout;

	BYTE shaderNo;		//���s����V�F�[�_�[�̔ԍ���ǉ�

	void Update_Controll();		//�L�[����
public:
	CPlayer(){}
	~CPlayer(){}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Death();		//���S����
	void Damage();		//�_���[�W
	void ChangeAnimation(char* Name);		//�A�j���[�V�����ύX

	CWEAPON* GetWeapon(){return m_Weapon;}
	bool	 isDeath() { return m_Death; }
	int Getm_Hp() { return m_Hp; }

	void Load(FILE* fp);	//�Z�[�u�t�@�C�����烍�[�h����
};