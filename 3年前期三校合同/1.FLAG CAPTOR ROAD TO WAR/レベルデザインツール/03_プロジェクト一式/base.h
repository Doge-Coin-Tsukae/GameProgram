#pragma once

#include "gameobject.h"

enum TERRITORY
{
	NONE_ZONE,			//�ǂ���̗̒n�ł͂Ȃ�
	FRIENDRY_ZONE,		//�F�R�̗̒n
	ENEMY_ZONE,			//�G�̗̒n
};

class CBASE : public CGameObject	//�p��(�C���w���^���X)
{
private:
	TERRITORY	m_territory;	//�N�̗̒n��
	CModel*		m_Flag;			//�����f��
	CCOLIDER_CIRCLE*	m_Zone;
	D3DXVECTOR2 m_Territory_Invarter;	//�̒n�ɐN�����Ă��鐔	(x=�F�R,y=�G�R)

	int			m_Gauge;				//���_���͒n
	int			m_Id;					//���X�|�[���|�C���g�ƍ��킹��ID
	bool		test;
	//�w���p�[�֐�
	void Update_Colision();		//�����蔻��
public:
	CBASE() {}
	~CBASE() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Save(FILE* fp);
	void Load(FILE*fp, int line);
	TERRITORY GetTerritory() { return m_territory; }
};