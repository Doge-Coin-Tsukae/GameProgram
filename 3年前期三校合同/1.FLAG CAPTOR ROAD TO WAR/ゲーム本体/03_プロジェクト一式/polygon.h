#pragma once

#include "gameobject.h"

//�|���S��(�摜�͓����Ȃ�)
class CPolygon : public  CGameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;
	float m_len;		//�c�̒���
	float m_wid;		//���̒���

public:
	void Init(D3DXVECTOR3 Pos);
	void Uninit();
	void Update();
	void Draw();

	void SetTexture(char* name);
	void SetSize(float len, float wid) { m_len = len; m_wid=wid; }
};

class CMovePolygon : public  CGameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;
	float m_len;		//�c�̒���
	float m_wid;		//���̒���

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetTexture(char* name);
	void SetSize(float len, float wid) { m_len = len; m_wid = wid; }
};