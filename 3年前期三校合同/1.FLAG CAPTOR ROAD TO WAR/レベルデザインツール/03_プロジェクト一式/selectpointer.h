#pragma once

#include "gameobject.h"

class CSelectpointer :public CGameObject
{
private:
	CMovePolygon *m_point;	//�|�C���^�摜

	D3DXVECTOR2 Pointpos;	//���݂̃|�C���^�̈ʒu

	//bool click;

public:
	void move_up() { Pointpos.y -= 1.0f; }
	void move_down() { Pointpos.y += 1.0f; }
	void move_right() { Pointpos.x += 1.0f; }
	void move_left() { Pointpos.x -= 1.0f; }

	void Init();
	void Uninit();
	void Update();
	void Draw();
	
	void SetPos(D3DXVECTOR2 pos) { Pointpos = pos; }
	D3DXVECTOR2  GetPos() { return  Pointpos; }
};