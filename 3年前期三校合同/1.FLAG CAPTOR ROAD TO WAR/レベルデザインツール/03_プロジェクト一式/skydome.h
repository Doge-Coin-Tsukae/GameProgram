#pragma once

class CSKYDOME :public CGameObject
{
private:
	CModel *m_Model;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};