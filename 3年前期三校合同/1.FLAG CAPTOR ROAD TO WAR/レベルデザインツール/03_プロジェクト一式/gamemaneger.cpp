#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "human.h"

#include "model.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "base.h"

#include "gamemaneger.h"

//���[��
void CConquest::Init()
{
	m_Defeat = false;
	m_Victory = false;
}
void CConquest::Uninit()
{

}
void CConquest::Update()
{
	//���Z�b�g
	for (int i = 0; i < 2; i++)
	{
		m_BaseCaptcha[i] = 0;
	}

	VictoryOrDefeatConditions();	//���s�������`�F�b�N����

	//���������𖞂������Ƃ�
	if (m_Victory == true)
	{
		//CManager::SetScene<CResult>();
		return;
	}
	//�s�k�����𖞂������Ƃ�
	if (m_Defeat == true)
	{
		//CManager::SetScene<CResult>();
		return;
	}
}
void CConquest::VictoryOrDefeatConditions()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);
	std::vector<CBASE*> baseList = scene->GetGameObjects<CBASE>(1);

	//�v���C���[�����񂾂畉���ɂ���
	if (pPlayer->isDeath() == true)
	{
		m_Defeat = true;
	}

	//�ȉ���������
	for (CBASE* base : baseList)
	{
		if (base->GetTerritory() == TEAM_FRIENDRY) { m_BaseCaptcha[0]++; }
		if (base->GetTerritory() == TEAM_ENEMY) { m_BaseCaptcha[1]++; }
	}
	//���_�S��������珟���ɂ���
	if (m_BaseCaptcha[0] == 2)
	{
		m_Victory = true;
	}
}

//���[���𑩂˂�}�l�[�W���[
void CGAME_MANEGER::Init()
{
	//m_GameMode = GAME_RULE_CONQUEST;	//��荇�������[��������
	////�I�΂ꂽ���[���ɂ���đ������N���X��ύX����
	//switch (m_GameMode)
	//{
	//case GAME_RULE_CONQUEST:
	//	m_Rule = new CConquest;
	//	break;
	//case GAME_RULE_DEATHMATH:
	//		break;
	//default:
	//	break;
	//}
}
void CGAME_MANEGER::Uninit()
{
	//m_Rule->Uninit();
	//delete m_Rule;
}
void CGAME_MANEGER::Update()
{
	//m_Rule->Update();
}