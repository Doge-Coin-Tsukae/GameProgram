#pragma once

#include "gameobject.h"

class CChip:public CGameObject
{
private:
	int id;			//オブジェクトの種類(チップを複数個出すときの識別コード)
	CSplitPolygon *m_polygon;	//画像分割できるポリゴン
	D3DXVECTOR2 m_Size;	//ボタンの大きさ

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool Colision(POINT pos);
	void SetPolygon(char* name, D3DXVECTOR2 Size, D3DXVECTOR2 Split, D3DXVECTOR2 Splitend);
	void Setid(int ids) { id = ids; }

	int GetId() { return id; }
};