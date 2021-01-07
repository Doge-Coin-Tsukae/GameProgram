#pragma once

#include "gameobject.h"

class CPlayer : public CGameObject	//�p��(�C���w���^���X)
{
private:
	CModel* m_Model;			//3D���f���N���X
	CSIGHT* m_Sight;			//�Ə�
	CWEAPON* m_Weapon;			//��������
	AABB m_Colider;

	D3DXVECTOR3		m_Velocity;		//�s������W
	TEAM_NUMBER		m_TeamNumber;	//�������G���̎���
	int				m_Hp;			//�̗�
	float			m_speed;		//���̑���
	bool			m_Death;		//���S�t���O

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

	void Save(FILE* fp);
	void Load(FILE* fp);
	CWEAPON* GetWeapon(){return m_Weapon;}
	bool	 isDeath() { return m_Death; }
};