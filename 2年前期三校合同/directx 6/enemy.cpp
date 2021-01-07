
#include "enemy.h"
#include "main.h"
#include "sprite.h"
#include "sound.h"
#include "table.h"
#include "player.h"
#include "enemybullet.h"
#include "enemylaser.h"
#include "explosion.h"
#include "game.h"

#define _USE_MATH_DEFINES
#include <math.h>

//マクロ宣言
#define ENEMY_WIDTH				(32)
#define ENEMY_HEIGHT			(32)
#define ANIME_PATTERN_MAX		(3)
#define ANIME_PATTERN_SKIPFRAME (8)

#define ENEMY_SEARCH_RADIUS		(200.0f)
#define ENEMY_SEARCH_ANGLE		(0.85f)
#define ENEMY_CHASE_SPEED		(3.0f)
#define ENEMY_RETURN_SPEED		(1.0f)

#define ENEMY (true)

class ENEMY_DATA
{
public :
	int			enable;	//生存フラグ

	D3DXVECTOR2 pos;	//位置
	float		rot;	//回転
	int			color;	//色
	int			muki;	//向き（移動方向）

	int			animePattern;	//アニメパターン
	int			animeFrame;		//パターン切り替えウエイト

	CIRCLE		collision;

	int			frame;
	int			frame_alpha;
	int			state;
	D3DXVECTOR2 dir_shot;
	D3DXVECTOR2 pos_return;

	bool move;		//移動するのかどうか
	int hp;
	int type;		//0,yuki 1,cho 2,maho

	D3DXVECTOR2 posing[3];		//移動場所
	int late;					//移動するポジション
};

ENEMY_DATA enemy[ENEMY_COUNT];


//敵の状態
typedef enum
{
	ENEMY_STATE_INIT,		//初期化
	ENEMY_STATE_SEARCH,		//周囲をサーチ
	ENEMY_STATE_FIND,		//敵を発見
	ENEMY_STATE_CHASE,		//追跡
	ENEMY_STATE_SHOT,		//ショット発射(円)
	ENEMY_STATE_SHOT2,		//ショット発射(単発)
	ENEMY_STATE_SHOT3,		//ショット発射(連続)
	ENEMY_STATE_LASER,		//レーザー発射(単発)
	ENEMY_STATE_LASER2,		//レーザー発射(連発)
	ENEMY_STATE_COOLDOWN,	//ショット終了
	ENEMY_STATE_RETURN,		//定位置に戻る
	ENEMY_STATE_DEAD,		//死亡状態
	ENEMY_STATE_BOSS,		//ボス特有の動き

	ENEMY_STATE_MAX

}ENEMY_STATE;


int Enemy_CalcMuki(D3DXVECTOR2 dir);

void Enemy_StateInit(int index);
void Enemy_StateSearch(int index);
void Enemy_StateFind(int index);
void Enemy_StateChase(int index);
void Enemy_StateShot(int index);
void Enemy_Stateshot2(int index);
void Enemy_Stateshot3(int index, int repet);
void Enemy_StateLaser(int index);
void Enemy_StateLaser2(int index, int repet);
void Enemy_StateCooldown(int index);
void Enemy_StateReturn(int index);


void Enemy_Initialize(void)
{
	//敵の初期化
	for (int i = 0; i < ENEMY_COUNT; i++) {
		Enemy_StateInit(i);
		enemy[i].state = ENEMY_STATE_SEARCH;
	}
}

void Enemy_Finalize(void)
{

}

void Enemy_Update(void)
{
	for (int i = 0; i<ENEMY_COUNT; i++){

		//当たり判定用座標の更新
		enemy[i].collision.cx = enemy[i].pos.x;
		enemy[i].collision.cy = enemy[i].pos.y;

		//スキップするフレーム値を超えたら
		if (++enemy[i].animeFrame > ANIME_PATTERN_SKIPFRAME)
		{
			//アニメパターンを進める(最大値を超えたらリセット)
			if (++enemy[i].animePattern >= ANIME_PATTERN_MAX)
				enemy[i].animePattern = 0;
			//フレームは元に戻す
			enemy[i].animeFrame = 0;
		}

		switch (enemy[i].state)
		{
		case ENEMY_STATE_INIT:
			Enemy_StateInit(i);
			break;
		case ENEMY_STATE_SEARCH:
			Enemy_StateSearch(i);
			break;
		case ENEMY_STATE_FIND:
			Enemy_StateFind(i);
			break;
		case ENEMY_STATE_CHASE:
			Enemy_StateChase(i);
			break;
		case ENEMY_STATE_SHOT:
			Enemy_StateShot(i);
			break;
		case ENEMY_STATE_SHOT2:
			Enemy_Stateshot2(i);
			break;
		case ENEMY_STATE_SHOT3:
			Enemy_Stateshot3(i,5);
			break;
		case ENEMY_STATE_LASER:
			Enemy_StateLaser(i);
			break;
		case ENEMY_STATE_LASER2:
			Enemy_StateLaser2(i,3);
			break;
		case ENEMY_STATE_COOLDOWN:
			Enemy_StateCooldown(i);
			break;
		case ENEMY_STATE_RETURN:
			Enemy_StateReturn(i);
			break;
		case ENEMY_STATE_BOSS:
			Enemy_StateBoss(i);
			break;
		default:
			break;
		}
	}
}

void Enemy_Draw(void)
{
	for (int i = 0; i < ENEMY_COUNT; i++) {

		//生存フラグがTRUEの敵のみ処理を行う
		if (!enemy[i].enable) {
			continue;
		}

		//種類によってテクスチャが変わる
		switch (enemy[i].type) {
		case 0:
			Sprite_Draw(TEXTURE_INDEX_YUKIDARUMA,
				enemy[i].pos.x,
				enemy[i].pos.y,
				GetAnimTbl(enemy[i].color, enemy[i].muki, enemy[i].animePattern).x * 256,
				GetAnimTbl(enemy[i].color, enemy[i].muki, enemy[i].animePattern).y * 256,
				32,
				32,
				16,
				16,
				2.0f,
				2.0f,
				enemy[i].rot);
			break;

		case 1:
			//敵テクスチャ
			Sprite_Draw(TEXTURE_INDEX_BOSS,
				enemy[i].pos.x,
				enemy[i].pos.y,
				GetAnimTbl(enemy[i].color, enemy[i].muki, enemy[i].animePattern).x * 0,
				GetAnimTbl(enemy[i].color, enemy[i].muki, enemy[i].animePattern).y * 0,
				256,
				256,
				128,
				128,
				0.5f,
				0.5f,
				enemy[i].rot);

			//体力バー(ボスのみ)
			Sprite_Draw(TEXTURE_INDEX_BAR,
				enemy[i].pos.x - 40,
				enemy[i].pos.y + 50,
				GetAnimTbl(enemy[i].color, enemy[i].muki, enemy[i].animePattern).x * 0,
				GetAnimTbl(enemy[i].color, enemy[i].muki, enemy[i].animePattern).y * 0,
				enemy[i].hp * 10,
				32,
				64,
				64,
				0.5f,
				0.5f,
				enemy[i].rot);
			break;

		case 2:
			Sprite_Draw(TEXTURE_INDEX_YUKIDARUMA,
				enemy[i].pos.x,
				enemy[i].pos.y,
				GetAnimTbl(enemy[i].color, enemy[i].muki, enemy[i].animePattern).x * 256,
				GetAnimTbl(enemy[i].color, enemy[i].muki, enemy[i].animePattern).y * 256,
				32,
				32,
				16,
				16,
				2.0f,
				2.0f,
				enemy[i].rot);
			break;

		default:
			break;
		}
	}
}

void Enemy_Destroy(int index, bool kill )
{
	if (kill == true)
	{
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		Game_AddKillCount();
	}
	enemy[index].state = ENEMY_STATE_DEAD;
	enemy[index].enable = false;
}

bool Enemy_IsEnable(int index)
{
	return enemy[index].enable;
}

const CIRCLE* Enemy_GetCollision(int index)
{
	return &enemy[index].collision;
}

//向きを作る
int Enemy_CalcMuki(D3DXVECTOR2 dir)
{
	int muki = 0;

	//移動方向が有効かチェック
	if (D3DXVec2Length(&dir) > 0.01f)
	{
		//X成分とY成分の大きさを比べて、どちらの方が大きいのかを調べる
		//X成分の方が大きい場合
		if (fabs(dir.x) > fabs(dir.y))
		{
			//X成分がプラスの値なのかマイナスの値なのかを調べる
			//マイナス成分の場合は左向き
			if (dir.x < 0.0f)
				muki = 1;
			//そうじゃない（プラス成分）場合は右向き
			else
				muki = 2;
		}
		//Y成分の方が大きい場合
		else
		{
			//Y成分がプラスの値なのかマイナスの値なのかを調べる
			//マイナス成分の場合は上向き
			if (dir.y < 0.0f)
				muki = 3;
			//そうじゃない（プラス成分）場合は上向き
			else
				muki = 0;
		}
	}

	return muki;
}

//初期化処理
void Enemy_StateInit(int index)
{

	D3DXVECTOR2 dir;

	dir.x = 0;
	dir.y = 0;
	//出現ポイントが通行不可だったらやり直し
	while (1)
	{
		//出現座標を決定
		enemy[index].pos.x = frand() * SCREEN_WIDTH;
		enemy[index].pos.y = frand() * SCREEN_HEIGHT;

		//通行不可かどうか
		if (Collision_HitCheck_TileMap(ENEMY, enemy[index].pos, &dir) == false)
		{
			break;
		}
	}

	enemy[index].rot = 0;
	enemy[index].color = 1;

	enemy[index].muki = rand() % 4;
	enemy[index].enable = TRUE;

	enemy[index].collision.cx = enemy[index].pos.x;
	enemy[index].collision.cy = enemy[index].pos.y;
	enemy[index].collision.r = ENEMY_WIDTH * 0.8f;

	enemy[index].frame = 0;
	enemy[index].hp = 1;


	enemy[index].move = true;	//移動許可する
	enemy[index].type = 0;
	//ステートをサーチ状態へ移行
	enemy[index].state = ENEMY_STATE_SEARCH;

}

void Enemy_StateSearch(int index)
{
	//フレームを進める
	enemy[index].frame++;

	D3DXVECTOR2 dir;

	//向いている方向のベクトルを作る
	switch (enemy[index].muki)
	{
	case 0://下向き
		dir = D3DXVECTOR2( 0.0f,  1.0f);		//xが0,yが1
		if (enemy[index].move == true) {
			Collision_HitCheck_TileMap(ENEMY, enemy[index].pos, &dir);
			enemy[index].pos += dir;
		}
		break;
	case 1://左向き
		dir = D3DXVECTOR2(-1.0f,  0.0f);		//xが-1,yが0
		if (enemy[index].move == true) {
			Collision_HitCheck_TileMap(ENEMY, enemy[index].pos, &dir);
			enemy[index].pos += dir;
		}
		break;
	case 2://右向き
		dir = D3DXVECTOR2( 1.0f,  0.0f);		//xが1,yが0
		if (enemy[index].move == true) {
			Collision_HitCheck_TileMap(ENEMY, enemy[index].pos, &dir);
			enemy[index].pos += dir;
		}
		break;
	case 3://上向き
		dir = D3DXVECTOR2( 0.0f, -1.0f);		//xが0,yが-1
		if (enemy[index].move == true) {
			Collision_HitCheck_TileMap(ENEMY, enemy[index].pos, &dir);
			enemy[index].pos += dir;
		}
		break;
	}

	//プレイヤーの座標を取得する
	D3DXVECTOR2 pl_pos = D3DXVECTOR2(Player_GetCollision()->cx, Player_GetCollision()->cy);

	//敵とプレイヤーの距離を計算する
	D3DXVECTOR2 vLen = enemy[index].pos - pl_pos;
	float length = D3DXVec2Length(&vLen);

	//円で判定をとる
	//判定する距離の中に入っているかをチェックする
	if (length < ENEMY_SEARCH_RADIUS)
	{
		//敵から見てプレイヤーの座標への方向ベクトルを作る
		D3DXVECTOR2 pl_dir = pl_pos - enemy[index].pos;
		D3DXVec2Normalize(&pl_dir, &pl_dir);

		//敵の向きとプレイヤ座標への方向ベクトルで内積を取る
		float dot = D3DXVec2Dot(&dir, &pl_dir);		//内積を取る

		////扇で判定を取る
		//判定する角度内に入っているかをチェックする
		if (dot > ENEMY_SEARCH_ANGLE)		//dotの値が大きい(プレイヤーが中いる)
		{
			Explosion_Create(enemy[index].pos.x, enemy[index].pos.y);

			//判定に通ればプレイヤー発見ステートに移行する
			enemy[index].state = ENEMY_STATE_FIND;
			enemy[index].frame = 0;

			//戻って来る座標を保存する
			enemy[index].pos_return = enemy[index].pos;
		}
	}

	//向きを変化させる
	if (enemy[index].frame > 90)
	{
		enemy[index].muki = (enemy[index].muki + 1) % 4;

		enemy[index].frame = 0;
	}

}

void Enemy_StateFind(int index)
{
	//フレームを進める
	enemy[index].frame++;

	//一定時間経ったら追跡ステートへ移行(発見時に何かしたければここに入れる)
	if (enemy[index].frame > 20){

		enemy[index].frame = 0;

		//ステートをサーチ状態へ移行
		enemy[index].state = ENEMY_STATE_CHASE;
	}
}

void Enemy_StateChase(int index)
{
	//フレームを進める
	enemy[index].frame++;

	//プレイヤーの座標を取得する
	D3DXVECTOR2 pl_pos = D3DXVECTOR2(Player_GetCollision()->cx, Player_GetCollision()->cy);
	
	//ベクトル取得
	D3DXVECTOR2 dir = pl_pos - enemy[index].pos;
	D3DXVec2Normalize(&dir, &dir);
	dir *= ENEMY_CHASE_SPEED;

	if (enemy[index].move == true)
	{
		enemy[index].pos += dir;
	}

	//移動方向から向きを作る
	enemy[index].muki = Enemy_CalcMuki(dir);

	//一定時間経ったら弾射出ステートへ移行
	if (enemy[index].frame > 120){

		enemy[index].frame = 0;

		//移動方向を保存
		enemy[index].dir_shot = dir;

		//ランダムで「ばら撒き弾」もしくは「レーザー」を射出
		if (rand() % 3)
		{
			//ステートをサーチ状態へ移行
			enemy[index].state = ENEMY_STATE_SHOT2;
		}
		else if (rand() % 3)
		{
			enemy[index].state = ENEMY_STATE_SHOT;
		}
		else{
			//ステートをサーチ状態へ移行
			enemy[index].state = ENEMY_STATE_LASER;
		}

		if (enemy[index].type == 2)
		{
			enemy[index].state = ENEMY_STATE_SHOT2;
		}
	}
}

void Enemy_StateShot(int index)
{
	//フレームを進める
	enemy[index].frame++;

	//ラジアンを作る
	//円(2π)を20分割し弾を放出する
	float shot_rad = atan2(enemy[index].dir_shot.y, enemy[index].dir_shot.x);
	shot_rad = (float)(M_PI * 2 / 10)*enemy[index].frame;	//20/1の割合で放出する

	//射出角ベクトルをフレーム値で回転させる
	D3DXVECTOR2 shot_dir;
	shot_dir.x = enemy[index].dir_shot.x*cosf(shot_rad) - enemy[index].dir_shot.y*sinf(shot_rad);
	shot_dir.y = enemy[index].dir_shot.x*sinf(shot_rad) + enemy[index].dir_shot.y*cosf(shot_rad);

	EnemyBullet_Create(enemy[index].pos.x, enemy[index].pos.y, shot_dir);

	//一定時間経ったらクールダウンステートへ移行
	if (enemy[index].frame > 90){

		enemy[index].frame = 0;

		//ステートを帰還状態へ移行
		enemy[index].state = ENEMY_STATE_COOLDOWN;
	}
}

void Enemy_StateLaser(int index)
{
	//1回のみ放つ
	if (enemy[index].frame == 0){
		EnemyLaser_Create(enemy[index].pos.x, enemy[index].pos.y, enemy[index].dir_shot);
	}

	//フレームを進める
	enemy[index].frame++;


	//一定時間経ったらクールダウンステートへ移行
	if (enemy[index].frame > 90){

		enemy[index].frame = 0;

		//ステートを帰還状態へ移行
		enemy[index].state = ENEMY_STATE_COOLDOWN;
	}
}

//レーザの連続発射2
void Enemy_StateLaser2(int index, int repet)
{
	static int land = 0;
	//プレイヤーの座標を取得する
	D3DXVECTOR2 pl_pos = D3DXVECTOR2(Player_GetCollision()->cx, Player_GetCollision()->cy);

	//1回のみ放つ
	if (enemy[index].frame == 0) {
		EnemyLaser_Create(enemy[index].pos.x, enemy[index].pos.y, enemy[index].dir_shot);
	}

	//フレームを進める
	enemy[index].frame++;


	//一定時間経ったら2発目発射準備
	if (enemy[index].frame > 40) {
		//ベクトル取得
		D3DXVECTOR2 dir = pl_pos - enemy[index].pos;
		D3DXVec2Normalize(&dir, &dir);
		dir *= ENEMY_CHASE_SPEED;

		//移動方向から向きを作る
		enemy[index].muki = Enemy_CalcMuki(dir);

		//移動方向を保存
		enemy[index].dir_shot = dir;

		enemy[index].frame = 0;
		land++;
		if (repet <= land) {
			land = 0;
			//ステートを帰還状態へ移行
			enemy[index].state = ENEMY_STATE_COOLDOWN;
		}
	}

}

void Enemy_Stateshot2(int index)
{

	EnemyBullet_Create(enemy[index].pos.x, enemy[index].pos.y, enemy[index].dir_shot);

	//フレームを進める
	enemy[index].frame++;


	//一定時間経ったらクールダウンステートへ移行
	if (enemy[index].frame > 15) {

		enemy[index].frame = 0;

		//ステートを帰還状態へ移行
		enemy[index].state = ENEMY_STATE_COOLDOWN;

		
	}
}

void Enemy_Stateshot3(int index,int repet)
{
	static int land=0;
	//プレイヤーの座標を取得する
	D3DXVECTOR2 pl_pos = D3DXVECTOR2(Player_GetCollision()->cx, Player_GetCollision()->cy);

	EnemyBullet_Create(enemy[index].pos.x, enemy[index].pos.y, enemy[index].dir_shot);

	//フレームを進める
	enemy[index].frame++;


	//一定時間経ったらクールダウンステートへ移行
	if (enemy[index].frame > 30) {
		//ベクトル取得
		D3DXVECTOR2 dir = pl_pos - enemy[index].pos;
		D3DXVec2Normalize(&dir, &dir);
		dir *= ENEMY_CHASE_SPEED;

		//移動方向から向きを作る
		enemy[index].muki = Enemy_CalcMuki(dir);

		//移動方向を保存
		enemy[index].dir_shot = dir;

		enemy[index].frame = 0;
		land++;
		if (repet <= land) {
			land = 0;
			//ステートを帰還状態へ移行
			enemy[index].state = ENEMY_STATE_COOLDOWN;
		}
	}
}

void Enemy_StateCooldown(int index)
{
	//フレームを進める
	enemy[index].frame++;

	//一定時間経ったら帰還ステートへ移行
	if (enemy[index].frame > 30) {

		enemy[index].frame = 0;

		switch (enemy[index].type)
		{
		case 0:
			//ステートを帰還状態へ移行
			enemy[index].state = ENEMY_STATE_RETURN;
			break;
		case 1:
			enemy[index].state = ENEMY_STATE_BOSS;
			break;
		case 2:
			Enemy_Destroy(index,false);
		default:
			break;

		}
	
	}
}

void Enemy_StateReturn(int index)
{
	//フレームを進める
	enemy[index].frame++;

	//プレイヤーの座標を取得する
	D3DXVECTOR2 pl_pos = D3DXVECTOR2(Player_GetCollision()->cx, Player_GetCollision()->cy);

	//帰還する座標への向きベクトルを計算する
	D3DXVECTOR2 dir = enemy[index].pos_return - enemy[index].pos;

	//ベクトルの長さを計算する
	float length = D3DXVec2Length(&dir);

	D3DXVec2Normalize(&dir, &dir);
	dir *= ENEMY_CHASE_SPEED;

	enemy[index].pos += dir;

	//移動方向から向きを作る
	enemy[index].muki = Enemy_CalcMuki(dir);

	//帰還する座標に到着したら
	if (length <= ENEMY_CHASE_SPEED){

		enemy[index].frame = 0;

		//ステートをサーチ状態へ移行
		enemy[index].state = ENEMY_STATE_SEARCH;
	}
}

//敵の個別出現(X座標,Y座標,敵の種類(0:雪だるま,1:蝶々),方向,移動するかしないか,色選択)
void SetEnemy(int px, int py,int select,int round,bool mov,int col)
{
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		if (enemy[i].enable == false) {
			enemy[i].pos.x = px;
			enemy[i].pos.y = py;

			enemy[i].type = select;

			enemy[i].rot = 0;
			enemy[i].color = col;

			enemy[i].muki = round;		//指定して方向をさす
			enemy[i].enable = TRUE;

			enemy[i].collision.cx = enemy[i].pos.x;
			enemy[i].collision.cy = enemy[i].pos.y;
			enemy[i].collision.r = ENEMY_WIDTH * 0.8f;

			enemy[i].frame = 0;

			enemy[i].move = mov;	//移動をさせるかしないか

			//タイプによって動きを変える
			switch (enemy[i].type) {
			case 0:
				//ステートをサーチ状態へ移行
				enemy[i].state = ENEMY_STATE_CHASE;
				enemy[i].pos_return = D3DXVECTOR2(px, py);
				enemy[i].hp = 1;
				break;
			case 1:
				enemy[i].state = ENEMY_STATE_BOSS;
				enemy[i].posing[0]= D3DXVECTOR2(400, 200);
				enemy[i].posing[1] = D3DXVECTOR2(600, 400);
				enemy[i].posing[2] = D3DXVECTOR2(200, 400);
				enemy[i].late = 0;
				enemy[i].hp = 30;
				break;
			case 2:
				enemy[i].state = ENEMY_STATE_CHASE;
				enemy[i].hp = 5;
				break;
			default:
				break;
			}

			break;
		}
	}
}

//ダメージを加える
void EnemyDamage(int index,int dama)
{
	enemy[index].hp -= dama;
	if (enemy[index].hp <= 0)
	{
		Enemy_Destroy(index,true);
	}
}

void Enemy_StateBoss(int index)
{

	//プレイヤーの座標を取得する
	D3DXVECTOR2 pl_pos = D3DXVECTOR2(Player_GetCollision()->cx, Player_GetCollision()->cy);

	//ベクトル取得
	D3DXVECTOR2 dir = pl_pos - enemy[index].pos;

	D3DXVec2Normalize(&dir, &dir);
	dir *= ENEMY_CHASE_SPEED;

	//移動方向から向きを作る
	enemy[index].muki = Enemy_CalcMuki(dir);

	//対角に到達したら攻撃
	enemy[index].dir_shot = dir;

	//フレームを進める
	enemy[index].frame++;

	if (enemy[index].frame >= 10) {
		for (int i = 0; i < 10; i++) {
			//ラジアンを作る
			//円(2π)を20分割し弾を放出する
			float shot_rad = atan2(enemy[index].dir_shot.y, enemy[index].dir_shot.x);
			shot_rad = (float)(M_PI * 2 / 10)*i;	//20/1の割合で放出する

			//射出角ベクトルをフレーム値で回転させる
			D3DXVECTOR2 shot_dir;
			shot_dir.x = enemy[index].dir_shot.x*cosf(shot_rad) - enemy[index].dir_shot.y*sinf(shot_rad);
			shot_dir.y = enemy[index].dir_shot.x*sinf(shot_rad) + enemy[index].dir_shot.y*cosf(shot_rad);

			EnemyBullet_Create(enemy[index].pos.x, enemy[index].pos.y, shot_dir);
		}
		enemy[index].frame = 0;
	}

	//移動
	D3DXVECTOR2 dir2 = enemy[index].posing[enemy[index].late] - enemy[index].pos;

	//ベクトルの長さを計算する
	float length = D3DXVec2Length(&dir2);
	D3DXVec2Normalize(&dir2, &dir2);
	dir2 *= (ENEMY_CHASE_SPEED*2.5f);

	enemy[index].pos += dir2;

	//指定した座標とほぼ一致していたら
	if (length <= ENEMY_CHASE_SPEED)
	{
		enemy[index].late++;
		if (enemy[index].late > 2)
		{
			enemy[index].late = 0;
		}

		//移動方向を保存
		enemy[index].frame = 0;			//フレームのリセット

		//ランダムで「ばら撒き弾」もしくは「レーザー」を射出
		if (rand() % 2)
		{
			enemy[index].state = ENEMY_STATE_SHOT2;
		}
		else if (rand() % 2)
		{
			enemy[index].state = ENEMY_STATE_SHOT;
		}
		else if (rand() % 2)
		{
			enemy[index].state = ENEMY_STATE_SHOT3;
		}
		else if (rand() % 2)
		{
			enemy[index].state = ENEMY_STATE_LASER;
		}
		else
		{
			enemy[index].state = ENEMY_STATE_LASER2;
		}

		//一定確率で敵を生む
		if (rand() % 2)
		{
			SetEnemy(400, 300, 0, 0, true, 1);

		}

		//一定の確率で動かない敵を生む
		if (rand() % 5)
		{
			SetEnemy(200, 100, 2, 0, false, 0);
			SetEnemy(400, 100, 2, 0, false, 0);
			SetEnemy(600, 100, 2, 0, false, 0);
			SetEnemy(200, 500, 2, 0, false, 0);
			SetEnemy(400, 500, 2, 0, false, 0);
			SetEnemy(600, 500, 2, 0, false, 0);
		}

	}
}