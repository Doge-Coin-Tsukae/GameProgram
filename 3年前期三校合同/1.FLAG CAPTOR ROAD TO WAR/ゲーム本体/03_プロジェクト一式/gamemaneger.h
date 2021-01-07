#pragma once

#include "gameobject.h"

enum GAME_RULE
{
	GAME_RULE_CONQUEST,
	GAME_RULE_DEATHMATH,
	GAME_RULE_TUTORIAL,
};

//ルールクラス(複数作る)
//コンクエスト
class CConquest :public CGameObject
{
private:
	bool m_deleted;		//画面表示が削除されたか
	bool m_Defeat;		//敗北条件を満たしたとき
	bool m_Victory;		//勝利条件を満たしたとき
	int  m_BaseCaptcha[2];

	void 	VictoryOrDefeatConditions();	//勝敗判定
public:
	void Init();
	void Uninit();
	void Update();
};

//チュートリアル
class CRULE_TUTORIAL :public CGameObject
{
private:
	bool m_deleted;		//画面表示が削除されたか
	bool m_Tutorial[6];	//目標達成数
	bool m_Defeat;		//敗北条件を満たしたとき
	bool m_Victory;		//勝利条件を満たしたとき
	int m_NowTurorial;	//現在のチュートリアルの場面

	void 	VictoryOrDefeatConditions();	//勝敗判定
	void	LevelUp();						//チュートリアルの段階を上げる
public:
	void Init();
	void Uninit();
	void Update();
};



//ゲーム側に実装するプログラム(ルールをする格納)
class CGAME_MANEGER : public CGameObject
{
private:
	CGameObject *m_Rule;			//ルールクラスを入れる
	GAME_RULE    m_GameMode;		//ゲームモードを入れるenum
public:
	void Init(GAME_RULE SetRule);
	void Uninit();
	void Update();
};
