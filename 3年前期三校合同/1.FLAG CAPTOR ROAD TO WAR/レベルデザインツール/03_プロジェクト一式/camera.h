#pragma once

#include "gameobject.h"

class CCamera : public CGameObject
{
private:
	D3DXVECTOR3 m_Target;		//カメラの注視点
	D3DXVECTOR3 m_Velocity;
	D3DXMATRIX viewMatrix;		//ビューマトリクス
	D3DXMATRIX projectionMatrix;	//プロジェクションマトリクス

	float			m_speed;	//足の速さ
public:
	CCamera(){}		//コンストラクタ
	~CCamera(){}	//デストラクタ

	void Init();
	void Uninit();
	void Update();
	void Controll_Update();
	void Draw();

	D3DXMATRIX GetViewMatrix() { return viewMatrix; }
	D3DXMATRIX GetProjectionMatrix() { return projectionMatrix; }
};