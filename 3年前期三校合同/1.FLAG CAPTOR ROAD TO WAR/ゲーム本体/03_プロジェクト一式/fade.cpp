//=====================================
//
// フェード
//  written by Y.Okubo
//
//=====================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"

ID3D11Buffer*				CFADE::m_VertexBuffer;
ID3D11ShaderResourceView*	CFADE::m_Texture;

D3DXCOLOR CFADE::m_FadeColor;
float CFADE::m_Alpha;
float CFADE::m_AddAlpha;
bool CFADE::m_bOut;
bool CFADE::m_bIsFade;

void CFADE::Init()
{
	m_FadeColor = (1.0f, 0.0f, 0.0f, 0.0f);
	m_Alpha = 0.0f;
	m_AddAlpha = 0.0f;
	m_bOut = false;
	m_bIsFade = false;
	m_VertexBuffer = NULL;
	m_Texture = NULL;

	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
}
void CFADE::Uninit()
{
	m_VertexBuffer->Release();
	//m_Texture->Release();
}
void CFADE::Update()
{
	//フェードしてないときはここでおしまい
	if (!m_bIsFade) return;

	//アルファ値の加算
	m_Alpha += m_AddAlpha;

	//
	if (m_bOut) {
		if (m_Alpha >= 1.0f) {
			m_Alpha = 1.0f;
			m_bIsFade = false;
		}
	}
	//
	else {
		if (m_Alpha <= 0.0f) {
			m_Alpha = 0.0f;
			m_bIsFade = false;
		}
	}
}
void CFADE::Draw()
{
	if (!m_bIsFade) return;
	LIGHT light;
	light.Enable = false;
	CRenderer::SetLight(light);

	//マトリクス設定
	CRenderer::SetWorldViewProjection2D();

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Alpha);
	CRenderer::SetMaterial(material);

	//テクスチャ設定
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);
}
void CFADE::Fade_Start(bool bOut, int frame, D3DCOLOR color)
{
	if (m_bIsFade == true)return;	//既にフェードしてたらやらない
	m_bOut = bOut;
	m_AddAlpha = 1.0f / frame;
	m_FadeColor = color;
	m_bIsFade = true;

	if (m_bOut) {
		m_Alpha = 0.0f;
	}
	else {
		m_Alpha = 1.0f;
		m_AddAlpha = -m_AddAlpha;
	}
}
bool CFADE::Fade_IsFade(void)
{
	return m_bIsFade;
}
