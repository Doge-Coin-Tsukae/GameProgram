//=====================================
//
//  プレイヤー
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Vector.h"
#include "sound.h"
#include "scene.h"
#include "input.h"
#include "camera.h"
#include "polygon.h"
#include "gauge.h"
#include "human.h"
#include "model.h"
#include "animationmodel.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "player.h"
#include "meshfield.h"
#include "bullet.h"
#include "bunker.h"
#include "fade.h"

#define		NORMALSPEED 0.25f
#define		SLOWSPEED	0.05f
#define		ANIMEBLENDSPEED	0.1f

typedef struct
{
	char *pFilename;	// ファイル名
} ANIMENAME;

ANIMENAME g_aParam[5] =
{
	{(char *)"idle"},				// 待機
	{(char *)"ready"},				// 構える
	{(char *)"run"},				// 走る
	{(char *)"fire"},				//発射
	{(char *)"Death"},
};

void CPlayer::Init()
{
	//クラスの初期処理
	m_Animodel = new CAnimationModel();
	m_Animodel->Load("asset\\model\\player\\chara.fbx");					//モデルのロード(ボーン付き)
	m_Animodel->LoadAnimation("asset\\model\\player\\idle.fbx", g_aParam[0].pFilename);		//アニメーション
	m_Animodel->LoadAnimation("asset\\model\\player\\ready.fbx", g_aParam[1].pFilename);		//アニメーション
	m_Animodel->LoadAnimation("asset\\model\\player\\run.fbx", g_aParam[2].pFilename);		//アニメーション
	m_Animodel->LoadAnimation("asset\\model\\player\\fire.fbx", g_aParam[3].pFilename);
	m_Animodel->LoadAnimation("asset\\model\\player\\Death.fbx", g_aParam[4].pFilename);

	m_Sight = new CSIGHT();
	m_Sight->Init();
	m_Sight->Setparent(this);	//照準の親を自分に

	m_Weapon = new CWEAPON();
	m_Weapon->Init();
	m_Weapon->Setparent(this);	//武器の親を自分に

	m_Colider.Init(m_Position + D3DXVECTOR3(-1.0f, 0.0f, -1.0f), m_Position + D3DXVECTOR3(1.0f, 2.0f, 1.0f), m_Position);

	//メンバ変数の初期処理
	m_Position = D3DXVECTOR3(350.0f, 1.0f, -200.0f);
	m_Velocity = m_Position;
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ModelRot = D3DXVECTOR3(1.6f, 0.0f, 0.0f);
	m_NowAnimationChara = g_aParam[0].pFilename;
	m_OldAnimationChara = g_aParam[1].pFilename;
	m_Scale = D3DXVECTOR3(1.3f, 1.3f, 1.3f);
	m_speed = 0.01f;
	m_TeamNumber = TEAM_FRIENDRY;	//チーム編集
	m_Death = false;
	m_Hp = 100;
	m_Frame = 0;
	rate = 0;

	const char* VSfilename[MAXSHADER] = //バーテックスシェーダファイルネーム
	{
		"vertexShader.cso",	//シェーダー
		"pixelLightingVS.cso",	//シェーダー
		"vertexLightingVS.cso",	//シェーダー
		"vertexShader.cso",	//シェーダー
	};
	const char* PSfilename[MAXSHADER] = //ピクセルシェーダファイルネーム
	{
		"pixelShader.cso",	//シェーダー
		"pixelLightingPS.cso",	//シェーダー
		"vertexLightingPS.cso",	//シェーダー
		"pixelShader.cso",	//シェーダー
	};
	//ここにシェーダーファイルのロードを追加
	for (int i = 0; i < MAXSHADER; i++)
	{
		//バーテックスシェーダーファイルのロード＆オブジェクト作成
		CRenderer::CreateVertexShader(&m_VertexShader[i], &m_VertexLayout, VSfilename[i]);

		//ピクセルシェーダーファイルのロード＆オブジェクト作成
		CRenderer::CreatePixelShader(&m_pixelShader[i], PSfilename[i]);
	}

	shaderNo = 0;
}

void CPlayer::Uninit()
{
	m_Weapon->Uninit();
	delete m_Weapon;

	m_Sight->Uninit();
	delete m_Sight;

	m_Animodel->Unload();
	delete m_Animodel;

	for (int i = 0; i < MAXSHADER; i++)
	{
		m_VertexShader[i]->Release();
		m_pixelShader[i]->Release();
	}
}

void CPlayer::Update()
{
	//ヘルパー関数の更新
	Update_Controll();

	//上限加減チェック
	m_Rotation.z = std::min(m_Rotation.z, 0.0f);
	m_Rotation.z = std::max(m_Rotation.z, -0.5f);
	rate = std::min(rate, 1.0f);
	rate = std::max(rate, 0.0f);

	//プレイヤーに入っているクラスの更新処理
	m_Sight->Update();
	m_Weapon->Update();
	m_Colider.update(m_Velocity);
	m_Animodel->Update(m_OldAnimationChara,m_NowAnimationChara, m_Frame, rate);

	//当たり判定処理
	CScene* scene = CManager::GetScene();
	std::vector<CBUNKER*> bunkerList = scene->GetGameObjects<CBUNKER>(1);
	for (CBUNKER* bunker : bunkerList)
	{
		//AABB
		/*if (intersectAABB(m_Colider, bunker->GetColider()))
		{
			m_Velocity = m_Position;
			m_speed = 0.01f;
		}*/

		//OBB(未完)
		D3DXVECTOR3 bukerPos = bunker->GetPosition();
		D3DXVECTOR3 direction = m_Position - bukerPos;

		D3DXVECTOR3 obbx, obby, obbz;
		float obbLenx, obbLeny,obbLenz;

		obbx = bunker->GetObbX();
		obbLenx = D3DXVec3Length(&obbx);
		obbx /= obbLenx;

		obby = bunker->GetObbY();
		obbLeny = D3DXVec3Length(&obby);
		obby /= obbLeny;

		obbz = bunker->GetObbZ();
		obbLenz = D3DXVec3Length(&obbz);
		obbz /= obbLenz;

		float lenX,lenY, lenZ;
		lenX = D3DXVec3Dot(&obbx, &direction);
		lenY = D3DXVec3Dot(&obby, &direction);
		lenZ = D3DXVec3Dot(&obbz, &direction);

		if (fabs(lenX) < obbLenx && fabs(lenY) < obbLeny && fabs(lenZ) < obbLenz)
		{
			m_Velocity = m_Position;
			m_speed = 0.01f;
		}
	}

	//座標を更新
	m_Position = m_Velocity;

	//体力が0以下になったとき
	if (m_Hp <= 0)
	{
		Death();
	}

	//銃を撃っているときは速度を減速させる
	if (m_Weapon->GetNextShoot() ==true)
	{
		if (m_speed >= SLOWSPEED)
			m_speed = SLOWSPEED;
	}
	else
	{
		if (m_speed >= NORMALSPEED)
			m_speed = NORMALSPEED;
	}

	//ちんだ時の処理
	if (m_Death == true)
	{
		m_OldAnimationChara = (char*)"Death";
		m_NowAnimationChara = (char*)"Death";
	}

	//変数
	rate+= ANIMEBLENDSPEED;
	m_Frame++;
	//if(m_Frame >= 240)
	//	m_Frame = 0;
	//メッシュフィールド高さ取得
	CMeshField* meshField = CManager::GetScene()->GetGameObject<CMeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);
}

void CPlayer::Update_Controll()
{
	if (m_Death == true) return;
	//キー入力で移動
	if (CInput::GetKeyPress('A'))
	{
		m_Velocity.x -= sin(m_Rotation.x)*m_speed;
		m_Velocity.z -= cos(m_Rotation.x)*m_speed;
		m_speed += 0.01f;
		ChangeAnimation((char*)"run");
	}
	if (CInput::GetKeyPress('D'))
	{
		m_Velocity.x += sin(m_Rotation.x)*m_speed;
		m_Velocity.z += cos(m_Rotation.x)*m_speed;
		m_speed += 0.01f;
		ChangeAnimation((char*)"run");
	}
	if (CInput::GetKeyPress('W'))
	{
		m_Velocity.z += sin(m_Rotation.x)*m_speed;
		m_Velocity.x -= cos(m_Rotation.x)*m_speed;
		m_speed += 0.01f;
		ChangeAnimation((char*)"run");
	}
	if (CInput::GetKeyPress('S'))
	{
		m_Velocity.z -= sin(m_Rotation.x)*m_speed;
		m_Velocity.x += cos(m_Rotation.x)*m_speed;
		m_speed += 0.01f;
		ChangeAnimation((char*)"run");
	}
	if (CInput::GetKeyPress('Q'))
		m_Rotation.x -= 0.1f;
	if (CInput::GetKeyPress('E'))
		m_Rotation.x += 0.1f;

	if (CInput::GetKeyPress('Z'))
		m_Rotation.z -= 0.1f;
	if (CInput::GetKeyPress('C'))
		m_Rotation.z += 0.1f;

	if (CInput::GetKeyTrigger('R'))
		m_Weapon->Reload();

	m_Rotation.x += CInput::GetMousedDfference().x / 100;
	m_Rotation.z -= CInput::GetMousedDfference().y / 100;

	if (m_Velocity.x == m_Position.x)
	{
		m_speed = 0.01f;
		if(m_Weapon->GetNextShoot() == false)
		ChangeAnimation((char*)g_aParam[0 + m_ready].pFilename);	//構えかアイドル状態に
	}

	//弾発射
	if (CInput::GetKeyPress(VK_LBUTTON))
	{	//マウスが右クリックされた時
		m_Weapon->Shoot(m_Sight->GetPosition(),m_TeamNumber);	//武器から発射する
		ChangeAnimation((char*)"fire");
	}

	//構え
	if (CInput::GetKeyTrigger(VK_RBUTTON))
	{
		CScene* scene = CManager::GetScene();
		CCamera* pcamera = scene->GetGameObject<CCamera>(0);

		pcamera->ZoomCamera();	//ズームしたり解除したり
		m_ready = 1 - m_ready;	//構えたり解除したり
	}

	//シェーダー切り替え
	if (CInput::GetKeyTrigger('Z'))
	{
		shaderNo++;
		if (shaderNo >= MAXSHADER) shaderNo = 0;
	}

}
void CPlayer::Draw()
{
	//インプットレイアウトのセット(DirectXへ頂点の構造を教える)
	CRenderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	//バーテックスシェーダーオブジェクトのセット
	CRenderer::GetDeviceContext()->VSSetShader(m_VertexShader[shaderNo], NULL, 0);
	//ピクセルシェーダーオブジェクトのセット
	CRenderer::GetDeviceContext()->PSSetShader(m_pixelShader[shaderNo], NULL, 0);

	m_Weapon->Draw();
	m_Sight->Draw();

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;	
	//拡大縮小のマトリクス
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//ヨーピッチロールのマトリクス
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x + m_ModelRot.x, -m_Rotation.z - m_ModelRot.z, m_Rotation.y + m_ModelRot.y);
	//位置マトリクス6
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	CRenderer::SetWorldMatrix(&world);

	m_Animodel->Draw();

	//インプットレイアウトのセット(DirectXへ頂点の構造を教える)
	//CRenderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	//バーテックスシェーダーオブジェクトのセット
	//CRenderer::GetDeviceContext()->VSSetShader(m_VertexShader[MAXSHADER-1], NULL, 0);
	//ピクセルシェーダーオブジェクトのセット
	//CRenderer::GetDeviceContext()->PSSetShader(m_pixelShader[MAXSHADER-1], NULL, 0);
}

void CPlayer::Death()
{
	if (m_Death == true) return;
	PlaySound(SOUND_SE_DEATH);
	m_Death = true;
	m_Hp = 0;
}

void CPlayer::Damage()
{
	if (m_Death == true) return;
	m_Hp -= 10;	//ダメージを入れる
	CFADE::SetTexture((char*)"asset/texture/fade_red.png");
	CFADE::Fade_Start(false, 10.0f, D3DXCOLOR());
}

void CPlayer::ChangeAnimation(char* Name)
{
	if (m_NowAnimationChara == Name)return;	//今のアニメーションと次のアニメーションが一緒なら
	m_OldAnimationChara = m_NowAnimationChara;		//新しいアニメーションデータを古いアニメーションデータにする
	m_NowAnimationChara = Name;						//新しいアニメーションデータを入れる
	rate = 0.0f;									//ブレンド値をリセット
}

void CPlayer::Load(FILE* fp)
{
	fscanf(fp, "%f%f%f", &m_Position.x, &m_Position.y, &m_Position.z);
	m_Velocity = m_Position;
	fscanf(fp, "%f%f%f", &m_Rotation.x, &m_Rotation.y, &m_Rotation.z);
	fscanf(fp, "%f%f%f", &m_Scale.x, &m_Scale.y, &m_Scale.z);
}
