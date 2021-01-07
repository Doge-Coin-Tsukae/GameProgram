#pragma once

#include "gameobject.h"

class CChip:public CGameObject
{
private:
	int id;			//�I�u�W�F�N�g�̎��(�`�b�v�𕡐��o���Ƃ��̎��ʃR�[�h)
	CSplitPolygon *m_polygon;	//�摜�����ł���|���S��
	D3DXVECTOR2 m_Size;	//�{�^���̑傫��

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