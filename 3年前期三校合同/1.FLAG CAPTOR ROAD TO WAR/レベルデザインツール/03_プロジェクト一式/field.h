#pragma once

#include "gameobject.h"

class CField : public CGameObject
{
private:

	ID3D11Buffer*				m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView*	m_Texture = nullptr;

public:
	CField(){}
	~CField(){}

	void Init();
	void Uninit();
	void Update();
	void Draw();
};