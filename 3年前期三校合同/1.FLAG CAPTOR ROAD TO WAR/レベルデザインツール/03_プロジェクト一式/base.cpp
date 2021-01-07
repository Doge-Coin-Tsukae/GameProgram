//
//拠点オブジェクト(陣取り出来る)
//
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Vector.h"
#include "meshfield.h"
#include "gamemaneger.h"
#include "game.h"
#include "human.h"
#include "model.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "base.h"

void CBASE::Init()
{
	//自身の変数の設定
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_territory = ENEMY_ZONE;
	m_Gauge = 100;

	//旗の設定
	m_Flag = new CModel();
	m_Flag->Load("asset\\model\\flag.obj");

	//当たり判定の設定
	m_Zone = new CCOLIDER_CIRCLE();
	m_Zone->Init();
	m_Zone->SetScale(D3DXVECTOR3(10.0f, 10.0f, 10.0f));
}

void CBASE::Uninit()
{
	//当たり判定の削除
	m_Zone->Uninit();
	delete m_Zone;

	//旗の削除
	m_Flag->Unload();
	delete m_Flag;
}

void CBASE::Update_Colision()
{
	CScene* scene = CManager::GetScene();
	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);

	//円の判定
	//範囲に入ったらゲージを動かす
	if (m_Zone->GetColider(pPlayer->GetPosition()))
	{
		m_Territory_Invarter.x++;	//陣地の勢力数を増やす(友軍)
		m_Rotation.x++;				//分かり易く旗を回転させる
	}
}

void CBASE::Update()
{
	m_Zone->SetPosition(m_Position);		//座標の設定
	m_Zone->Update();						//更新処理

	m_Territory_Invarter = D3DXVECTOR2(0, 0);	//侵入者の値リセット

	//陣地に部隊が入っているとき
	if (m_Territory_Invarter.x != m_Territory_Invarter.y)
	{
		m_Gauge--;		//勢力ゲージを減らす
	}

	//勢力地が0になったら
	if (m_Gauge <= 0)
	{
		switch (m_territory)
		{//所有者によって切り分ける
		case NONE_ZONE:
			if (m_Territory_Invarter.x > m_Territory_Invarter.y)
			{//友軍の方が多かったら
				m_territory = FRIENDRY_ZONE;
			}
			if (m_Territory_Invarter.x < m_Territory_Invarter.y)
			{//敵軍の方が多かったら
				m_territory = ENEMY_ZONE;
			}
			m_Gauge = 100;
			break;

		case FRIENDRY_ZONE:
			m_territory = NONE_ZONE;	//中立にする
			m_Gauge = 100;				//ゲージ回復
			break;

		case ENEMY_ZONE:
			m_territory = NONE_ZONE;	//中立にする
			m_Gauge = 100;				//ゲージ回復
			break;
		}
	}

	//メッシュフィールド高さ取得
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);

}

void CBASE::Draw()
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

	m_Flag->Draw();		//旗の描画
	m_Zone->Draw();		//当たり判定の描画
}

void CBASE::Save(FILE* fp)
{
	//座標
	fprintf(fp, "%f ", m_Position.x);
	fprintf(fp, "%f ", m_Position.y);
	fprintf(fp, "%f\n", m_Position.z);
	//角度
	fprintf(fp, "%f ", m_Rotation.x);
	fprintf(fp, "%f ", m_Rotation.y);
	fprintf(fp, "%f\n", m_Rotation.z);
	//大きさ
	fprintf(fp, "%f ", m_Scale.x);
	fprintf(fp, "%f ", m_Scale.y);
	fprintf(fp, "%f\n", m_Scale.z);
}

void CBASE::Load(FILE*fp, int line)
{
	for (int i = 0; i < line * 3; i++)
	{
		fscanf(fp, "");
	}

	fscanf(fp, "%f%f%f", &m_Position.x, &m_Position.y, &m_Position.z);
	fscanf(fp, "%f%f%f", &m_Rotation.x, &m_Rotation.y, &m_Rotation.z);
	fscanf(fp, "%f%f%f", &m_Scale.x, &m_Scale.y, &m_Scale.z);
}