
//このファイルはほかのシェーダーファイルへインクルードする

//各種マトリクスバッファ コンスタントバッファを定義
cbuffer WorldBuffer : register(b0)
{
	matrix World;	//行列変数
}

cbuffer ViewBuffer : register(b1)
{
	matrix View;	//ビュー行列変数 (カメラ)
}

cbuffer ProjectionBuffer : register(b2)
{
	matrix Projection; //プロジェクション行列変数
}

//頂点シェーダーへ入力されるデータを構造体の形で表現
//これは頂点バッファの内容そのもの
struct VS_IN
{
	float4 Position		: POSITION0;	//頂点座標 0
	float4 Normal		: NORMAL0;		//法線 0
	float4 Diffuse		: COLOR0;		//カラー 0
	float2 TexCoord		: TEXCOORD0;	//テクスチャ座標 0
};

//ピクセルシェーダーへ入力されるデータを構造体の形で表現
struct PS_IN
{
	float4 Position		: SV_POSITION0;	//頂点座標 0
	float4 WorldPosition: POSITION0;	//座標 0
	float4 Normal		: NORMAL0;		//法線 0
	float4 Diffuse		: COLOR0;		//カラー 0
	float2 TexCoord		: TEXCOORD0;	//テクスチャ座標 0
};

//ライトオブジェクト構造体とコンスタントバッファ 
struct LIGHT	//光データ構造体(C言語から受け取る)
{
	bool Enable;
	bool3 Dummy; //16Byte境界用
	float4 Direction;	//光のベクトル
	float4 Diffuse;
	float4 Ambient;
};

//コンスタントバッファ C言語からもらうデータの入れ物
cbuffer LightBuffer : register(b4)//コンスタントバッファ４番とする 
{
	LIGHT Light; //ライト構造体 
}

//カメラ座標の受け取り用 5番とする
cbuffer CameraBuffer:register(b5)
{
	float4 CameraPosition;
}

