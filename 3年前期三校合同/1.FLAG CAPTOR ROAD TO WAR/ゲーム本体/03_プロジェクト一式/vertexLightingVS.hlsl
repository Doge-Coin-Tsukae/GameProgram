#include "common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
	//頂点法線をワールド行列で回転させる(頂点と同じ回転をさせる)
	float4 worldNormal, normal;
	normal = float4(In.Normal.xyz, 0.0f);	//頂点法線の準備w=0とする(平行移動しない)
	worldNormal = mul( normal,World);		//ベクトルを行列で変換
	worldNormal = normalize(worldNormal);	//正規化する

	//明るさの計算
	float light = -dot(Light.Direction,worldNormal);	//光と法線を内積を計算
	//float light = 0.5 - 0.5 * dot(Light.Direction.xyz, worldNormal.xyz);	//(ハーフランバート)
	light = saturate(light);				//明るさをサチュレートする

	//頂点の明るさを出力する
	Out.Diffuse = light;
	Out.Diffuse.a = 1.0f;

	//以下通常のVSの処理

	matrix wvp;		//計算用行列

	//wvp = ワールド行列 * ビュー行列
	wvp = mul(World, View);

	//wvp = wvp * プロジェクション行列
	wvp = mul(wvp, Projection);

	//頂点座標 * 変換行列 を出力
	Out.Position = mul(In.Position, wvp);

	Out.Normal = worldNormal;
	//テクスチャ座標
	Out.TexCoord = In.TexCoord;

}