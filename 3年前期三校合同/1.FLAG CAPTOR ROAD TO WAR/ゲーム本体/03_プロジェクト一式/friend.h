#pragma once

#include "gameobject.h"

class CFriend : public CGameObject	//�p��(�C���w���^���X)
{
private:
	static CAnimationModel* m_Animodel;	//3D�A�j���[�V�������f���N���X
	//static CModel* m_Model;			//3D���f���N���X
	CSIGHT* m_Sight;			//�Ə�
	CWEAPON* m_Weapon;			//��������

	TEAM_NUMBER		m_TeamNumber;			//�������G���̎���

	char*	m_OldAnimationChara;	//�A�j���[�V�����̖��O�̋���
	char*	m_NowAnimationChara;	//���݂̃A�j���[�V�����̖��O
	int		m_Frame = 0;			//�A�j���[�V�����̃t���[��
	float	rate = 0;				//�A�j���[�V�����u�����h�̃��[�g

	//�w���p�[�֐�
	void Update_AI();

	void ChangeAnimation(char* Name);
public:
	CFriend() {}
	~CFriend() {}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void LookPlayer();		//�v���C���[������
	void Death();
};