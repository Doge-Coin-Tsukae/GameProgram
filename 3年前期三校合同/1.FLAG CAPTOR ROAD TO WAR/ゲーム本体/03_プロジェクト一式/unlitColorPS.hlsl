
//ピクセルシェーダー

#include "common.hlsl"

//テクスチャ
Texture2D	g_texture	:	register(t0);//テクスチャ0番を使う
//サンプラー
SamplerState g_SamplerState	:register(s0);	//サンプラー0を使う

//
//
//
void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//入力された色をそのままピクセル色として出力
	outDiffuse = In.Diffuse;

	//入力されたテクスチャ座標をもとにテクスチャ画像のピクセル職を
	//取得して、それを出力する。
	outDiffuse = g_texture.Sample(g_SamplerState, In.TexCoord);

	//頂点の色とテクスチャの色を合成して出力
	outDiffuse *= In.Diffuse;

	//------------------------
	//ピクセルシェーダーテスト
	//------------------------
	//ネガポジ反転
	//outDiffuse = 1.0f - g_texture.Sample(g_SamplerState, In.TexCoord);
	//outDiffuse.a = 1.0f;

	//グレースケール
	//outDiffuse = g_texture.Sample(g_SamplerState,In.TexCoord);
	//outDiffuse = 0.299*outDiffuse.r + 0.587 * outDiffuse.g + 0.114*outDiffuse.b;
	//outDiffuse.a = 1.0f;

	//テクスチャのRGBの色をBGRに入れ替えて出力
	//float4 color = g_texture.Sample(g_SamplerState,In.TexCoord);
	//outDiffuse.r = color.b;
	//outDiffuse.g = color.g;
	//outDiffuse.b = color.r;

	//outDiffuse.a = 1.0f;

	//テクスチャの色を16乗して出力
	//outDiffuse = g_texture.Sample(g_SamplerState, In.TexCoord);
	//outDiffuse *= outDiffuse;
	//outDiffuse *= outDiffuse;
	//outDiffuse *= outDiffuse;
	//outDiffuse *= outDiffuse;

	//outDiffuse.a = 1.0f;

	//セピア変換
	//outDiffuse = g_texture.Sample(g_SamplerState, In.TexCoord);
	//outDiffuse = 0.299*outDiffuse.r + 0.587 * outDiffuse.g + 0.114 * outDiffuse.b;
	//float4 sepia = float4(1.07, 0.74, 0.43, 1.0f);
	//outDiffuse *= sepia;
	//outDiffuse.a = 1.0;

}