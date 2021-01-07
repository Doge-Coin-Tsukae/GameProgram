#pragma once

#include "gameobject.h"

class CCamera : public CGameObject
{
private:
	D3DXVECTOR3 m_Target;		//カメラの注視点
	D3DXMATRIX viewMatrix;		//ビューマトリクス
	D3DXMATRIX projectionMatrix;	//プロジェクションマトリクス

	bool m_zoom;

	void BackFront_Player();	//プレイヤーを後ろから見る
	void Target_Player();	//注視点をプレイヤーの座標にする
	void Zoom_Player();			//プレイヤーにズームする
public:
	CCamera(){}		//コンストラクタ
	~CCamera(){}	//デストラクタ

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void ZoomCamera() { m_zoom = 1 - m_zoom; }

	bool GetZoom() { return m_zoom; }
	D3DXMATRIX GetViewMatrix() { return viewMatrix; }
};