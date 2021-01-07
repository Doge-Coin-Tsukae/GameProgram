//=====================================
//
//  �Q�[�����[���ƃ��[�������锠
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "scene.h"
#include "title.h"
#include "human.h"

#include "polygon.h"
#include "model.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "base.h"
#include "vicordef.h"
#include "tutorial2D.h"

#include "gamemaneger.h"



//���[��(�R���N�G�X�g)
void CConquest::Init()
{
	m_deleted = false;
	m_Defeat = false;
	m_Victory = false;
}
void CConquest::Uninit()
{

}
void CConquest::Update()
{
	VictoryOrDefeatConditions();	//���s�������`�F�b�N����

	CScene* scene = CManager::GetScene();

	//���U���g��ʂɈڍs����
	VICORDEF* vic = scene->GetGameObject<VICORDEF>(4);
	if (vic != nullptr)
	{
		//�t�F�[�h�I����������
		if (m_deleted == true)
		{
			if (CFADE::Fade_IsFade() == false)
			{
				StopSound();
				CManager::SetScene<CTitle>();
				return;
			}
		}
		if (vic->GetDelete())
		{
			//�t�F�[�h�̎��s
			if (m_deleted == true)return;
			CFADE::SetTexture((char*)"asset/texture/fade.png");
			CFADE::Fade_Start(true, 90, D3DCOLOR());

			m_deleted = true;
		}
	}

	//���������𖞂������Ƃ�
	if (m_Victory == true)
	{
		scene->AddGameObject<VICORDEF>(4)->Set(true);
		return;
	}
	//�s�k�����𖞂������Ƃ�
	if (m_Defeat == true)
	{
		scene->AddGameObject<VICORDEF>(4)->Set(false);
		return;
	}
}
void CConquest::VictoryOrDefeatConditions()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);
	std::vector<CBASE*> baseList = scene->GetGameObjects<CBASE>(2);

	//���Z�b�g
	for (int i = 0; i < 2; i++)
	{
		m_BaseCaptcha[i] = 0;
	}

	//�v���C���[�����񂾂畉���ɂ���
	if (pPlayer->isDeath() == true)
		m_Defeat = true;

	int BaseCount = 0;

	//�ȉ���������
	for (CBASE* base : baseList)
	{
		if (base->GetTerritory() == FRIENDRY_ZONE) { m_BaseCaptcha[0]++; }
		if (base->GetTerritory() == ENEMY_ZONE) { m_BaseCaptcha[1]++; }
		BaseCount++;
	}
	//���_�S��������珟���ɂ���
	if (m_BaseCaptcha[0] >= BaseCount)
		m_Victory = true;
}

//�`���[�g���A���̃��[��
void CRULE_TUTORIAL::Init()
 {
	CScene* scene = CManager::GetScene();
	scene->AddGameObject<CTUTORIAL2D>(4);

	//�ϐ�������
	for (int i = 0; i < 6; i++)
	{
		m_Tutorial[i] = false;
	}
	m_NowTurorial = 0;
	m_deleted = false;
	m_Defeat = false;
	m_Victory = false;
}
void CRULE_TUTORIAL::Uninit()
{
}
void CRULE_TUTORIAL::Update()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);
	CWEAPON* pWeapon = pPlayer->GetWeapon();
	CBASE* pBase = scene->GetGameObject<CBASE>(2);

	VictoryOrDefeatConditions();

	//���݂̐i�s��ɂ���ĕς���
	switch (m_NowTurorial)
	{
	case 0:
		//�N���A��������������
		if (CInput::GetKeyPress('W'))						//�O�i
			LevelUp();	//�i�K���グ��

		break;
	case 1:
		//�N���A��������������
		if (CInput::GetKeyPress(VK_RBUTTON))				//���_�ύX
			LevelUp();	//�i�K���グ��
		break;
	case 2:
		//�N���A��������������
		if (CInput::GetKeyPress(VK_LBUTTON))				//���C
			LevelUp();	//�i�K���グ��
		break;
	case 3:
		//�N���A��������������
		if (pWeapon->GetAmmo() == pWeapon->GetMaxAmmo())	//���݂̒e�ƍő�e���������ɂȂ�����
			LevelUp();	//�i�K���グ��
		break;
	case 4:
		if (pBase->GetTerritory() == FRIENDRY_ZONE)		//���_���
			LevelUp();
		break;
	case 5:
		break;
	default:
		break;
	}
}
void CRULE_TUTORIAL::VictoryOrDefeatConditions()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	//�`���[�g���A���̍Ō���N���A������I���
	if(m_Tutorial[4] == true)
		m_Victory = true;

	//�`���[�g���A���Ŏ��񂾂�I���
	if (pPlayer->isDeath() == true)
		m_Defeat = true;
}
void CRULE_TUTORIAL::LevelUp()
{
	m_Tutorial[m_NowTurorial] = true;		//���݂̃`���[�g���A�����N���A�ɂ���
	m_NowTurorial++;						//�`���[�g���A������i��グ��

	CScene* scene = CManager::GetScene();
	CTUTORIAL2D* ptuto = scene->GetGameObject<CTUTORIAL2D>(4);

	//���݂̐i�s��ɂ���ăe�N�X�`����ς���
	switch (m_NowTurorial)
	{
	case 1:
		ptuto->ChangeTexture((char*)"asset/texture/tutorial/tutorial_viewpoint.png");
		break;
	case 2:
		ptuto->ChangeTexture((char*)"asset/texture/tutorial/tutorial_shoot.png");
		break;
	case 3:
		ptuto->ChangeTexture((char*)"asset/texture/tutorial/tutorial_reload.png");
		break;
	case 4:
		ptuto->ChangeTexture((char*)"asset/texture/tutorial/tutorial_captcha.png");
		break;
	case 5:
		ptuto->ChangeTexture((char*)"asset/texture/tutorial/tutorial_end.png");
		break;
	default:
		break;
	}
}

//���[���𑩂˂�}�l�[�W���[
void CGAME_MANEGER::Init(GAME_RULE SetRule)
{
	m_GameMode = SetRule;

	//�I�΂ꂽ���[���ɂ���đ������N���X��ύX����
	switch (m_GameMode)
	{
	case GAME_RULE_CONQUEST:
		m_Rule = new CConquest;
		break;
	case GAME_RULE_DEATHMATH:
		break;
	case GAME_RULE_TUTORIAL:
		m_Rule = new CRULE_TUTORIAL;
		break;
	default:
		break;
	}

	m_Rule->Init();
}
void CGAME_MANEGER::Uninit()
{
	m_Rule->Uninit();
	delete m_Rule;
}
void CGAME_MANEGER::Update()
{
	m_Rule->Update();
}