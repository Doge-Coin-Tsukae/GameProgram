#pragma once

#include "gameobject.h"

enum TERRITORY
{
	NONE_ZONE,			//どちらの領地ではない
	FRIENDRY_ZONE,		//友軍の領地
	ENEMY_ZONE,			//敵の領地
};

class CBASE : public CGameObject	//継承(インヘリタンス)
{
private:
	TERRITORY	m_territory;	//誰の領地か
	CModel*		m_Flag;			//旗モデル
	CCOLIDER_CIRCLE*	m_Zone;
	D3DXVECTOR2 m_Territory_Invarter;	//領地に侵入している数	(x=友軍,y=敵軍)

	int			m_Gauge;				//拠点勢力地
	bool		m_inPlayer;				//中にプレイヤーがいるか
	//ヘルパー関数
	void Update_Colision();		//当たり判定
	void Update_Gauge();		//勢力地の更新処理
	void Update_Territory();	//領地の占領者の更新処理
public:
	CBASE() {}
	~CBASE() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Load(FILE*fp, int line);

	TERRITORY GetTerritory() { return m_territory; }
	bool GetinPlayer() { return m_inPlayer; }
	int GetGauge() { return m_Gauge; }
};