#pragma once
#include "gameobject.h"

class VICORDEF :public CGameObject
{
private:
	CPolygon *Serif;		//�\�������錾�t��png

	int DeleteTime;			//�I�u�W�F�N�g���폜�����܂ł̎���
	bool Delete;			//���Ԃ���������
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Set(bool Sets);
	bool GetDelete(){	return Delete;}
};