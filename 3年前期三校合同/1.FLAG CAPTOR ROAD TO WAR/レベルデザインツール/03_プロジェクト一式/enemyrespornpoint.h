#pragma once

#include "gameobject.h"

class CEnemyRespornPoint : public CGameObject	//�p��(�C���w���^���X)
{
private:
	static CModel* m_Model;			//3D���f���N���X
	CBASE*		   m_ParrentBase;	//�e�̋��_(���X�|�[����Ɍ������̒n)

	int			m_Id;					//���X�|�[���|�C���g�ƍ��킹��ID
	//�w���p�[�֐�

public:
	CEnemyRespornPoint() {}
	~CEnemyRespornPoint() {}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};