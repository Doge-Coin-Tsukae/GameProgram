#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "model.h"
#include "scene.h"

#include "meshfield.h"
#include "colider.h"
#include "deadtree.h"

class CModel* CDEADTREE::m_Model;

void CDEADTREE::Load()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\deadtree.obj");
}

void CDEADTREE::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void CDEADTREE::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void CDEADTREE::Uninit()
{
}
void CDEADTREE::Update()
{
	Update_Controll();

	angle += 0.0001f;

	//メッシュフィールド高さ取得
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);
	m_lightpos.x = m_Position.x + length*sin(angle);
	m_lightpos.y = m_Position.y + length*cos(angle);
}
void CDEADTREE::Update_Controll()
{
	if (CInput::GetKeyPress('W'))
		length += 0.1f;
	if (CInput::GetKeyPress('S'))
		length -= 0.1f;

	if (CInput::GetKeyPress('A'))
		angle -= 0.1f;
	if (CInput::GetKeyPress('D'))
		angle += 0.1f;

	if (CInput::GetKeyPress('Q'))
		m_lightpos.z -= 0.1f;
	if (CInput::GetKeyPress('E'))
		m_lightpos.z += 0.1f;
}
void CDEADTREE::Draw()
{
	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans, shadow, modelshadow;
	//拡大縮小のマトリクス
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//ヨーピッチロールのマトリクス
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	//位置マトリクス
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);

	m_Model->Draw();

	D3DXVECTOR3 light = m_Position - m_lightpos;
	D3DXMatrixIdentity(&shadow);
	shadow._21 = -light.x / light.y;
	shadow._22 = 0.0f;
	shadow._23 = -light.z / light.y;
	shadow._42 = 0.5f;	// Zファイティング対策

	modelshadow = world *shadow;

	CRenderer::SetWorldMatrix(&modelshadow);

	m_Model->Draw();
}

void CDEADTREE::Load(FILE*fp, int line)
{
	for (int i = 0; i < line * 3; i++)
	{
		fscanf(fp, "");
	}

	fscanf(fp, "%f%f%f", &m_Position.x, &m_Position.y, &m_Position.z);
	fscanf(fp, "%f%f%f", &m_Rotation.x, &m_Rotation.y, &m_Rotation.z);
	fscanf(fp, "%f%f%f", &m_Scale.x, &m_Scale.y, &m_Scale.z);
}