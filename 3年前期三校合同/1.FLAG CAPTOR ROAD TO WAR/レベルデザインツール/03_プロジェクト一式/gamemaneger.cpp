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

//ルール
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
	//リセット
	for (int i = 0; i < 2; i++)
	{
		m_BaseCaptcha[i] = 0;
	}

	VictoryOrDefeatConditions();	//勝敗条件をチェックする

	//勝利条件を満たしたとき
	if (m_Victory == true)
	{
		//CManager::SetScene<CResult>();
		return;
	}
	//敗北条件を満たしたとき
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

	//プレイヤーが死んだら負けにする
	if (pPlayer->isDeath() == true)
	{
		m_Defeat = true;
	}

	//以下勝利条件
	for (CBASE* base : baseList)
	{
		if (base->GetTerritory() == TEAM_FRIENDRY) { m_BaseCaptcha[0]++; }
		if (base->GetTerritory() == TEAM_ENEMY) { m_BaseCaptcha[1]++; }
	}
	//拠点全部取ったら勝ちにする
	if (m_BaseCaptcha[0] == 2)
	{
		m_Victory = true;
	}
}

//ルールを束ねるマネージャー
void CGAME_MANEGER::Init()
{
	//m_GameMode = GAME_RULE_CONQUEST;	//取り合えずルールを入れる
	////選ばれたルールによって代入するクラスを変更する
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