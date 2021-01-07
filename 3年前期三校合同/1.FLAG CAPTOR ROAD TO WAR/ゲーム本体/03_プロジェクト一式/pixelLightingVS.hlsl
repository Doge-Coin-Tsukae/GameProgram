#include "common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
	matrix wvp;		//計算用行列

	//wvp = ワールド行列 * ビュー行列
	wvp = mul(World, View);

	//wvp = wvp * プロジェクション行列
	wvp = mul(wvp, Projection);

	//頂点座標 * 変換行列 を出力
	Out.Position = mul(In.Position, wvp);

	//頂点法線をワールド行列で回転させる(頂点と同じ回転をさせる)
	float4 worldNormal, normal;
	normal = float4(In.Normal.xyz, 0.0f);	//頂点法線の準備w=0とする(平行移動しない)
	worldNormal = mul(normal, World);		//ベクトルを行列で変換
	worldNormal = normalize(worldNormal);	//正規化する
	Out.Normal = worldNormal;

	Out.Diffuse = In.Diffuse; //デフューズ(頂点の明るさ)を合成
	Out.TexCoord = In.TexCoord;

	Out.WorldPosition = mul(In.Position, World);
}