//ブリンフォン鏡面反射

#include "common.hlsl"
Texture2D g_Texture : register(t0); //テクスチャ０番 
SamplerState g_SamplerState : register(s0); //サンプラー０番

void main(in PS_IN In, out float4 outDiffuse : SV_Target) 
{
	float4 normal = normalize(In.Normal);

	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);	//テクスチャの色取得
	outDiffuse.a *= In.Diffuse.a;								//αは別処理(明るさはいらない)

	float  light = 0.5f - dot(normal.xyz, Light.Direction.xyz) *0.5f;

	if (light > 0.8f)
	{
		light=0.8f;
	}
	else if (light > 0.5f)
	{
		light = 0.6f;
	}
	else
	{
		light = 0.2f;
	}

	outDiffuse.rgb *= In.Diffuse.rgb * light;					//頂点色と明るさを乗算

	//ピクセルからカメラのベクトル（視線ベクトル） 
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev); //正規化

	float3 refv = reflect(Light.Direction.xyz, normal.xyz);
	refv = normalize(refv);

	/*float specular = -dot(eyev, refv);
	specular = saturate(specular);
	specular = pow(specular,30);
	outDiffuse.rgb += specular;*/

	float rim = 1.0 + dot(eyev, normal.xyz); //視線と法線の内積を明るさに変換する
	rim = pow(rim, 3) * 2.0f; //スペキュラと同じような処理を適当に行う。 
	rim = saturate(rim); //rimをサチュレートする
	outDiffuse.rgb -= rim; //通常の色へ加算する。 
	outDiffuse.a = In.Diffuse.a;
}