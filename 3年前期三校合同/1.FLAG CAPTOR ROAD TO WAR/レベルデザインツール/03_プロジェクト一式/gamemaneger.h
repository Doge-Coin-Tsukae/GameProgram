#pragma once

#include "gameobject.h"

enum GAME_RULE
{
	GAME_RULE_CONQUEST,
	GAME_RULE_DEATHMATH,
};

//ルールクラス(複数作る)
class CConquest :public CGameObject
{
private:
	bool m_Defeat;		//敗北条件を満たしたとき
	bool m_Victory;		//勝利条件を満たしたとき
	int  m_BaseCaptcha[2];

	void 	VictoryOrDefeatConditions();	//勝敗判定
public:
	void Init();
	void Uninit();
	void Update();
};

//ゲーム側に実装するプログラム
class CGAME_MANEGER : public CGameObject
{
private:
	CGameObject *m_Rule;			//ルールクラスを入れる
	GAME_RULE    m_GameMode;		//ゲームモードを入れるenum
public:
	void Init();
	void Uninit();
	void Update();
};
