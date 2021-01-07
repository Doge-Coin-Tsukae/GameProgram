#include "common.hlsl"

Texture2D g_Texture : register(t0); //テクスチャ０番 
SamplerState g_SamplerState : register(s0); //サンプラー０番

void main(in PS_IN In, out float4 outDiffuse : SV_Target) 
{
	float4 normal = normalize(In.Normal);

	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);	//テクスチャの色取得
	outDiffuse.a *= In.Diffuse.a;								//αは別処理(明るさはいらない)

	float  light = 0.5f - dot(normal.xyz, Light.Direction.xyz) *0.5f;
	outDiffuse.rgb *= In.Diffuse.rgb * light;					//頂点色と明るさを乗算


	//フォン鏡面反射を加える
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz; //視線ベクトル作成
	eyev = normalize(eyev);									 //正規化する

	float3 refv = reflect(Light.Direction.xyz,normal.xyz ); //反射ベクトル計算
	refv = normalize(refv);									//正規化

	float specular = -dot(refv, eyev);						//内積計算
	specular = pow(specular,10);							//30乗する(オブジェクトの表面をてかてかさせたいのならば、個々の数字を大きくする)
	specular = saturate(specular);

	outDiffuse.rgb += specular;

}