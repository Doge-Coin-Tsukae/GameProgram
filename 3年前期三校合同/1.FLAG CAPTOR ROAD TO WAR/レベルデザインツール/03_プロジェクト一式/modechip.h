#pragma once

#include "gameobject.h"

class CMODECHIP :public CGameObject
{
private:
	int id;			//オブジェクトの種類
	bool m_SelectMode;		//現在このモードか
	CMovePolygon *m_polygon;
	D3DXVECTOR2 m_Size;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool Colision(POINT pos);
	void SetMode();
	void SetPolygon(char* name, D3DXVECTOR2 Size);
	void Setid(int ids) { id = ids; }

	int GetId() { return id; }
};