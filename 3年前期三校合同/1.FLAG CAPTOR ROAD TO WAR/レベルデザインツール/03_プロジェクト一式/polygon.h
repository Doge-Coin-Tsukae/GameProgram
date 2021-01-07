#pragma once

#include "gameobject.h"

//ƒ|ƒŠƒSƒ“(‰æ‘œ‚Í“®‚©‚È‚¢)
class CPolygon : public  CGameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;
	float m_len;		//c‚Ì’·‚³
	float m_wid;		//‰¡‚Ì’·‚³

public:
	void Init(D3DXVECTOR3 Pos);
	void Uninit();
	void Update();
	void Draw();

	void SetTexture(char* name);
	void SetSize(float len, float wid) { m_len = len; m_wid=wid; }
};

//ƒ|ƒŠƒSƒ“(‰æ‘œ‚ª“®‚©‚¹‚é)
class CMovePolygon : public  CGameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;
	float m_len;		//c‚Ì’·‚³
	float m_wid;		//‰¡‚Ì’·‚³

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetTexture(char* name);
	void SetSize(float len, float wid) { m_len = len; m_wid = wid; }
};

//ƒ|ƒŠƒSƒ“(‰æ‘œ‚ğ•ªŠ„‚Å‚«‚é)
class CSplitPolygon : public  CGameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;
	float m_len;		//c‚Ì’·‚³
	float m_wid;		//‰¡‚Ì’·‚³

	D3DXVECTOR2 m_StartTexcoord;		//•ªŠ„ˆÊ’u(n‚Ü‚è)
	D3DXVECTOR2 m_EndTexcoord;		//•ªŠ„ˆÊ’u(I‚í‚è)

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetTexture(char* name);
	void SetSize(float len, float wid) { m_len = len; m_wid = wid; }
	void SetSplit(D3DXVECTOR2 SetStartTexcoord, D3DXVECTOR2 SetEndTexcoord) {
		m_StartTexcoord = SetStartTexcoord, m_EndTexcoord = SetEndTexcoord;}
};