#pragma once

class CSIGHT : public CGameObject{
private:
	CGameObject* m_parent;		//親のアドレスを入れる
public:
	CSIGHT() {}
	~CSIGHT() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Setparent(CGameObject* object) { m_parent = object; }	//照準の親のアドレスのセット
};