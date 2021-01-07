#include "player.h"
#include "main.h"
#include "input.h"
#include "sprite.h"
#include "sound.h"
#include "table.h"
#include "bullet.h"
#include "collision.h"
#include "enemybullet.h"
#include "enemylaser.h"
#include "fade.h"


#define PLAYER_WIDTH	(32)
#define PLAYER_HEIGHT	(32)

#define ANIME_PATTERN_MAX		3
#define ANIME_PATTERN_SKIPFRAME 8

#define NOTENEMY (0)

typedef struct
{
	D3DXVECTOR2 pos;			//位置
	int			muki;			//向き
	int			color;			//色

	int			animePattern;	//アニメパターン
	int			animeFrame;		//パターン切り替えウエイト

	CIRCLE		collision;		//円の当たり判定
	int			hitpoint;		//ヒットポイント
	int			bomb;			//弾消しボム

}PLAYER;

PLAYER player;

void Player_Initialize(void)
{
	//プレイヤーの初期化
	player.pos.x = SCREEN_WIDTH / 12;
	player.pos.y = SCREEN_HEIGHT / 1.1;

	player.color = 2;
	player.muki = 0;

	player.collision.cx = player.pos.x;
	player.collision.cy = player.pos.y;
	player.collision.r = PLAYER_WIDTH * 0.1f;

	player.hitpoint = 4000;		//体力調整
	player.bomb = 3;
}

void Player_Finalize(void)
{

}

void Player_Update(void)
{
	D3DXVECTOR2 dir = D3DXVECTOR2(0.0f, 0.0f);
	
	//移動キー
	if (Keyboard_IsPress(DIK_UP) || GamePad_IsPress(0, BUTTON_UP))
	{
		//シフトキーが押されていたとき(低速移動)
		if (Keyboard_IsPress(DIK_LSHIFT))
		{
			dir.y -= 2.0f;
		}
		//押されなかったとき(通常移動)
		else
		{
			dir.y -= 5.0f;
			player.muki = 3;
		}
	}
	if (Keyboard_IsPress(DIK_DOWN) || GamePad_IsPress(0, BUTTON_DOWN))
	{
		//シフトキーが押されていたとき(低速移動)
		if (Keyboard_IsPress(DIK_LSHIFT))
		{
			dir.y += 2.0f;
		}
		//押されなかったとき(通常移動)
		else
		{
			dir.y += 5.0f;
			player.muki = 0;
		}

	}
	if (Keyboard_IsPress(DIK_LEFT) || GamePad_IsPress(0, BUTTON_LEFT))
	{
		//シフトキーが押されていたとき(低速移動)
		if (Keyboard_IsPress(DIK_LSHIFT))
		{
			dir.x -= 2.0f;
		}
		//押されなかったとき(通常移動)
		else
		{
			dir.x -= 5.0f;
			player.muki = 1;
		}

	}
	if (Keyboard_IsPress(DIK_RIGHT) || GamePad_IsPress(0, BUTTON_RIGHT))
	{
		//シフトキーが押されていたとき(低速移動)
		if (Keyboard_IsPress(DIK_LSHIFT))
		{
			dir.x += 2.0f;
		}
		//押されなかったとき(通常移動)
		else
		{
			dir.x += 5.0f;
			player.muki = 2;
		}
	}

	//スペースが押されたら弾を発射
	if (Keyboard_IsTrigger(DIK_SPACE) || GamePad_IsTrigger(0, BUTTON_A)) {
		//カーソルキー入力がされていない場合、向きから発射方向を作成する
		if (D3DXVec2Length(&dir) < 0.01f) {
			switch (player.muki)
			{
			case 0://下向き
				dir.y = 1.0f;
				break;
			case 1://左向き
				dir.x = -1.0f;
				break;
			case 2://右向き
				dir.x = 1.0f;
				break;
			case 3://上向き
				dir.y = -1.0f;
				break;
			}
		}

		//シフトキーが押されていたとき
		if (Keyboard_IsPress(DIK_LSHIFT))
		{
			switch (player.muki)
			{
			case 0://下向き
				dir = D3DXVECTOR2(0.0f, 1.0f);
				break;
			case 1://左向き
				dir = D3DXVECTOR2(-1.0f, 0.0f);
				break;
			case 2://右向き
				dir = D3DXVECTOR2(1.0f, 0.0f);
				break;
			case 3://上向き
				dir = D3DXVECTOR2(0.0f, -1.0f);
				break;
			}
		}
		//弾の作成
		Bullet_Create(player.pos.x, player.pos.y, dir);
		dir = D3DXVECTOR2(0.0f, 0.0f);
	}

	//Zキーでボム
	if (Keyboard_IsTrigger(DIK_Z) || GamePad_IsTrigger(0, BUTTON_B))
	{
		if (player.bomb > 0) {
			//敵弾を全部破壊
			for (int i = 0; i < ENEMYBULLET_MAX; i++) {
				EnemyBullet_Destroy(i);
			}

			//敵のレーザー全消滅
			for (int i = 0; i < ENEMYLASER_MAX; i++) {
				EnemyLaser_Destroy(i);
			}
			PlaySound(SOUND_LABEL_SE_SHUTA);
			Fade_Start(false, 10, D3DCOLOR_RGBA(255, 255, 255, 0));
		}
		player.bomb--;
	}

	//マップとのヒットチェック
	Collision_HitCheck_TileMap(NOTENEMY,player.pos, &dir);

	// 座標の更新処理
	player.pos += dir;

	//当たり判定用座標の更新
	player.collision.cx = player.pos.x;
	player.collision.cy = player.pos.y;

	//スキップするフレーム値を超えたら
	if (++player.animeFrame > ANIME_PATTERN_SKIPFRAME)
	{
		//アニメパターンを進める(最大値を超えたらリセット)
		if (++player.animePattern >= ANIME_PATTERN_MAX)
			player.animePattern = 0;
		//フレームは元に戻す
		player.animeFrame = 0;
	}
}

void Player_Draw(void)
{
	//プレイヤーのテクスチャ表示
	Sprite_Draw(TEXTURE_INDEX_YUKIDARUMA,
		player.pos.x,
		player.pos.y,
		GetAnimTbl(player.color, player.muki, player.animePattern).x * 256,
		GetAnimTbl(player.color, player.muki, player.animePattern).y * 256,
		32,
		32,
		16,
		16,
		1.5f,
		1.5f,
		0.0f);

	for (int i = 0; i < player.bomb; i++)
	{
		//プレイヤーのテクスチャ表示
		Sprite_Draw(TEXTURE_INDEX_BOMB,
			700 + 50 * i,
			550,
			GetAnimTbl(player.color, player.muki, player.animePattern).x * 0,
			GetAnimTbl(player.color, player.muki, player.animePattern).y * 0,
			32,
			32,
			16,
			16,
			1.5f,
			1.5f,
			0.0f);
	}

}

const CIRCLE* Player_GetCollision()
{
	return &player.collision;
}

void Player_AddDamage(int damage)
{
	player.hitpoint -= damage;
	if (player.hitpoint < 0)
		player.hitpoint = 0;
}

int Player_GetHitPoint()
{
	return player.hitpoint;
}
