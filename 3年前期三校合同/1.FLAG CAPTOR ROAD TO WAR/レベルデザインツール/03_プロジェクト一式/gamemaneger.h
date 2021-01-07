#pragma once

#include "gameobject.h"

enum GAME_RULE
{
	GAME_RULE_CONQUEST,
	GAME_RULE_DEATHMATH,
};

//���[���N���X(�������)
class CConquest :public CGameObject
{
private:
	bool m_Defeat;		//�s�k�����𖞂������Ƃ�
	bool m_Victory;		//���������𖞂������Ƃ�
	int  m_BaseCaptcha[2];

	void 	VictoryOrDefeatConditions();	//���s����
public:
	void Init();
	void Uninit();
	void Update();
};

//�Q�[�����Ɏ�������v���O����
class CGAME_MANEGER : public CGameObject
{
private:
	CGameObject *m_Rule;			//���[���N���X������
	GAME_RULE    m_GameMode;		//�Q�[�����[�h������enum
public:
	void Init();
	void Uninit();
	void Update();
};
