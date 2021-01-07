#pragma once

class CGameObject
{
protected:	//アクセス指定子
	bool			m_Destroy = false;
	D3DXVECTOR3		m_Position;
	D3DXVECTOR3		m_Rotation;
	D3DXVECTOR3		m_Scale;

public:		//アクセス指定子
	CGameObject() {}	//コンストラクタ
	virtual ~CGameObject() {}	//デストラクタ(virtualは必ずつける)

	virtual void Init() {};
	virtual void Uninit() = 0;		//純粋仮想関数
	virtual void Update() = 0;
	virtual void Draw() {};

	//ゲッター
	D3DXVECTOR3 GetPosition() { return m_Position; }
	D3DXVECTOR3 GetRotation() { return m_Rotation; }
	D3DXVECTOR3 GetScale()	  { return m_Scale; }

	//セッター
	void SetPosition(D3DXVECTOR3 Pos) { m_Position = Pos; }
	void SetRotation(D3DXVECTOR3 Rot) { m_Rotation = Rot; }
	void SetScale(D3DXVECTOR3 Scl) { m_Scale = Scl; }

	void SetDestroy() { m_Destroy = true; }

	//オブジェクトの破壊処理
	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}

	//ImGuinに表示させる項目
	virtual void SetImGui()
	{
		ImGui::Text("fugafuga");
		ImGui::SliderFloat("fugafuga",&m_Rotation.x,0,1);
		ImGui::Checkbox("delete",&m_Destroy);
	}

	virtual void Load(){}	//データのロード
	virtual void Save(){}	//データのセーブ
};