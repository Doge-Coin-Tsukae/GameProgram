#pragma once

class CSIGHT : public CGameObject{
private:
	CGameObject* m_parent;		//�e�̃A�h���X������
public:
	CSIGHT() {}
	~CSIGHT() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Setparent(CGameObject* object) { m_parent = object; }	//�Ə��̐e�̃A�h���X�̃Z�b�g
};