//
//
//カーソル
//writen by y.okubo
//
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "Vector.h"

#include "camera.h"
#include "meshfield.h"
#include "model.h"
#include "carsor.h"

void CCARSOR::Init()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\yokoari.obj");

	m_Scale = D3DXVECTOR3(2.0f, 2.0f, 2.0f);

	ShowCursor(FALSE);
}

void CCARSOR::Uninit()
{
	m_Model->Unload();
	delete m_Model;
}

void CCARSOR::Update()
{
	//ポインターのスクリーン座標習得
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(GetWindow(),&pos);	//カーソルの座標をアプリケーションの座標にする

	//カメラとメッシュフィールドのデータ入手
	CCamera* camera = CManager::GetScene()->GetGameObject<CCamera>(0);
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);

	//スクリーン座標からワールド座標に変換
	CalcScreenToWorld(&ppos,pos.x, pos.y,1.0f,SCREEN_WIDTH,SCREEN_HEIGHT, &camera->GetViewMatrix(),&camera->GetProjectionMatrix());

	//カーソルの座標とカメラの座標でベクトルをとる
	D3DXVECTOR3 vpos = GetVector(camera->GetPosition(), ppos);	//スクリーンとカメラのベクトル
	m_Position = camera->GetPosition();	

	while (1)
	{
		m_Position += vpos;

		if (meshField->GetHeight(m_Position) >= m_Position.y)
		{
			m_Position.y = meshField->GetHeight(m_Position);
			break;
		}
	}
}

void CCARSOR::Draw()
{
	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	//拡大縮小のマトリクス
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//ヨーピッチロールのマトリクス
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	//位置マトリクス
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);

	m_Model->Draw();
}

// スクリーン座標をワールド座標に変換
D3DXVECTOR3* CCARSOR::CalcScreenToWorld(
	D3DXVECTOR3* pout,
	int Sx,  // スクリーンX座標
	int Sy,  // スクリーンY座標
	float fZ,  // 射影空間でのZ値（0～1）
	int Screen_w,
	int Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
) 
{
	// 各行列の逆行列を算出
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;
	D3DXMatrixInverse(&InvView, NULL, View);
	D3DXMatrixInverse(&InvPrj, NULL, Prj);
	D3DXMatrixIdentity(&VP);
	VP._11 = Screen_w / 2.0f; VP._22 = -Screen_h / 2.0f;
	VP._41 = Screen_w / 2.0f; VP._42 = Screen_h / 2.0f;
	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	// 逆変換
	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord(pout, &D3DXVECTOR3(Sx, Sy, fZ), &tmp);

	return pout;
}