//=====================================
//
//  �Q�[���V�[��
//  written by Y.Okubo
//
//=====================================
#include <list>
#include <vector>
#include <typeinfo>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "input.h"
#include "scene.h"
#include "fade.h"
#include "gamemaneger.h"
#include "Game.h"
#include "Result.h"

#include "gameobject.h"
#include "load.h"
#include "camera.h"
#include "field.h"
#include "meshfield.h"
#include "animationmodel.h"
#include "human.h"
#include "model.h"
#include "colider.h"
#include "sight.h"
#include "weapon.h"

#include "player.h"
#include "enemy.h"
#include "friend.h"
#include "enemycommander.h"
#include "bullet.h"
#include "bunker.h"
#include "polygon.h"
#include "skydome.h"
#include "base.h"
#include "deadtree.h"

#include "explosion.h"
#include "smoke.h"
#include "tree.h"
#include "number.h"
#include "gauge.h"
#include "weapon2d.h"
#include "captureui.h"
#include "playerui.h"

void CGame::Init()
{
	//�e�N�X�`�� + ���f�����[�h
	CBullet::Load();	//�e�̃��f�����Ăяo��
	CBUNKER::Load();	//�o���J�[�̃��f�����Ăяo��
	CEnemy::Load();		//�G�̃��f�����Ăяo��
	CFriend::Load();
	CWEAPON::Load();	//�e�̃��f�����Ăяo��
	CDEADTREE::Load();	//�͂�؂̃��f�����Ăяo��
	CSMOKE::Load();		//���̉摜���Ăяo��

	CLOAD *m_Load = new CLOAD;

	m_GameManeger = new CGAME_MANEGER;
	m_GameManeger->Init(GAME_RULE_CONQUEST);

	//�g���Q�[���I�u�W�F�N�g�Ăяo��
	//�J����0�� 3D���f��1�� 3D���f��(�����蔻��̂��)2�� �r���{�[�h(��)��3�� 2D���f��4��
	AddGameObject<CCamera>(0);		//�J����

	AddGameObject<CSKYDOME>(1);		//�X�J�C�h�[��
	AddGameObject<CMeshField>(1);	//�n��

	AddGameObject<CWEAPON2D>(4);
	AddGameObject<CPLAYERUI>(4);
	AddGameObject<CENEMY_COMMANDER>(4);

	m_Load->Data_Load();	//�f�[�^�̃��[�h

	//PlaySound(SOUND_BGM_BGM002);

	CFADE::SetTexture((char*)"asset/texture/fade.png");
	CFADE::Fade_Start(false,60,D3DCOLOR());
}

void CGame::Uninit()
{
	//���X�g�ɓ����Ă���Q�[���I�u�W�F�N�g���폜
	CScene::Uninit();

	//�e�N�X�`���A�����[�h
	CDEADTREE::Unload();
	CSMOKE::Unload();
	CWEAPON::UnLoad();
	CEnemy::Unload();
	CBUNKER::Unload();
	CBullet::Unload();

	m_GameManeger->Uninit();
	delete m_GameManeger;

	StopSound();
}

void CGame::Update()
{
	CScene::Update();	//���X�g�ɓ����Ă���Q�[���I�u�W�F�N�g���Ăяo��

	m_GameManeger->Update();
}