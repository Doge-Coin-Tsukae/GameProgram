//****************************************
//敵のリスポーンポイント
//****************************************

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "scene.h"

#include "meshfield.h"

#include "model.h"
#include "colider.h"
#include "base.h"

#include "enemyrespornpoint.h"

class CModel* CEnemyRespornPoint::m_Model;

void CEnemyRespornPoint::Load()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\flag.obj");
}

void CEnemyRespornPoint::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void CEnemyRespornPoint::Init()
{

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//メッシュフィールド高さ取得
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);

	//idの設定
	std::vector<CEnemyRespornPoint*> EnemyRespornPoints = CManager::GetScene()->GetGameObjects<CEnemyRespornPoint>(1);

	int setid = 0;

	for (CEnemyRespornPoint* bunker : EnemyRespornPoints)
	{
		setid++;	//1ずつ増やす
	}

	m_Id = setid;	//入れる


}

void CEnemyRespornPoint::Uninit()
{

}

void CEnemyRespornPoint::Update()
{
	//ヘルパー関数
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);

}

void CEnemyRespornPoint::Draw()
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