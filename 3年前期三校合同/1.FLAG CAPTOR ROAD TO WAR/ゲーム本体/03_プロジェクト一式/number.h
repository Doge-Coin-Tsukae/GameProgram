#pragma once

#include"gameobject.h"

class CNUMBER : public CGameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;
	float m_len;		//ˆê•Ó‚Ì’·‚³
	int m_number;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetLength(float SetLen) { m_len = SetLen; }
	void SetNumber(int SetNumber) { m_number = SetNumber; }
};