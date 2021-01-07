#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "input.h"
#include "gamemaneger.h"
#include "scene.h"
#include "Game.h"
#include "Title.h"

CScene* CManager::m_Scene = NULL;

void CManager::Init()
{
	//ShowCursor(FALSE);	//カーソルを消す

	CRenderer::Init();
	CInput::Init();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplWin32_Init(GetWindow());
	ImGui_ImplDX11_Init(CRenderer::GetDevice(), CRenderer::GetDeviceContext());

	SetScene<CTitle>();
}

void CManager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;

	ImGui_ImplDX11_Shutdown();

	CInput::Uninit();
	CRenderer::Uninit();
}

void CManager::Update()
{
	CInput::Update();
	m_Scene->Update();
}

void CManager::Draw()
{

	CRenderer::Begin();

	LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f,1.0f, 1.0f, 1.0f);
	CRenderer::SetLight(light);

	//カメラ->3Dポリゴン->2Dポリゴンの順番で描画する

	m_Scene->Draw();

	CRenderer::End();
}
