//タイトル画面のエフェクトマネージャ

#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "scene.h"
#include "shellexplosion.h"
#include "titleeffectmanager.h"

void Title_Effect_Manager::Init()
{
	ExplosionPos[0] = D3DXVECTOR3(55.0f, 20.0f, -125.0f);
	ExplosionPos[1] = D3DXVECTOR3(95.0f, 20.0f, -130.0f);
	ExplosionPos[2] = D3DXVECTOR3(125.0f, 20.0f, -180.0f);
	ExplosionPos[3] = D3DXVECTOR3(35.0f, 20.0f, -165.0f);
	ExplosionPos[4] = D3DXVECTOR3(65.0f, 20.0f, -200.0f);

	m_randtime = rand() % 100;
}
void Title_Effect_Manager::Uninit()
{
}
void Title_Effect_Manager::Update()
{
	if (m_SpownTime== 100 + m_randtime)
	{
		PlaySound(SOUND_SE_FALL);
	}
	if (m_SpownTime >= 300 + m_randtime)
	{
		StopSound(SOUND_SE_FALL);
		PlaySound(SOUND_SE_SE002);
		SetExplosion();
		m_SpownTime = 0;
		m_randtime = rand() % 100;
		return;
	}

	m_SpownTime++;
}
void Title_Effect_Manager::SetExplosion()
{
	CScene* scene = CManager::GetScene();
	int random = rand() % 5;
	scene->AddGameObject<CShellExplosion>(1)->SetPosition(ExplosionPos[random]);
}