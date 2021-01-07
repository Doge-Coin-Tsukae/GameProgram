#include "texture.h"
#include "player.h"
#include "enemy.h"
#include "fade.h"
#include "scene.h"
#include "collision.h"
#include "bullet.h"
#include "enemybullet.h"
#include "enemylaser.h"
#include "explosion.h"
#include "score_draw.h"
#include "tileMap.h"
#include "result.h"
#include "sound.h"

//ゲームの状態を示す
typedef enum PHASE_INDEX
{
	PHASE_INDEX_FADE,
	PHASE_INDEX_PLAYER_NORMAL,
	PHASE_INDEX_STAGE_CLEAR,
	PHASE_INDEX_END,

	PHASE_INDEX_MAX
};

static PHASE_INDEX g_Phase;			//ゲームの状態を示す

static int g_KillCount = 0;			//殺害数の表示

//このcppファイル内で使う関数のプロトタイプ宣言
static bool Game_EndCheck(void);


//ゲーム画面の初期処理
void Game_Initialize(void)
{
	Player_Initialize();
	Enemy_Initialize();
	Bullet_Initialize();
	EnemyBullet_Initialize();
	EnemyLaser_Initialize();
	Explosion_Initialize();
	TileMap_Initialize();

	g_Phase = PHASE_INDEX_FADE;			//フェード中の状態にする
	g_KillCount = 0;					//殺害数のリセット

	//BGM再生
	PlaySound(SOUND_LABEL_BGM001);

	//フェードを開始させる
	Fade_Start(false, 30, D3DCOLOR_RGBA(0,0,0,0));
}

//ゲーム画面の終了処理
void Game_Finalize(void)
{
	Player_Finalize();
	Enemy_Finalize();
}

//ゲーム画面の更新
void Game_Update(void)
{
	//ゲームの状態で処理を変える
	switch(g_Phase)
	{
		//フェード中のとき
	case PHASE_INDEX_FADE:
		if( !Fade_IsFade() ) {
			g_Phase = PHASE_INDEX_PLAYER_NORMAL;
		}
		break;
		//通常のとき
	case PHASE_INDEX_PLAYER_NORMAL:
		Player_Update();
		Enemy_Update();
		Bullet_Update();
		EnemyBullet_Update();
		EnemyLaser_Update();
		Explosion_Update();

		//当たり判定は必ずすべてのアップデート処理が終わった後に行う
		Collision_Update();

		//ゲームの終了チェック
		if (Game_EndCheck())
		{
			Fade_Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
			g_Phase = PHASE_INDEX_STAGE_CLEAR;
		}
		break;

		//ステージクリアしたとき
	case PHASE_INDEX_STAGE_CLEAR:
		if (!Fade_IsFade()) {
			Scene_Change(SCENE_INDEX_RESULT);		//リザルト画面にチェンジ
			g_Phase = PHASE_INDEX_END;				//終了の値を入れる
		}
		break;
		//ゲームを終了するとき
	case PHASE_INDEX_END:
		break;
	}

}

//ゲーム画面の描画処理
void Game_Draw(void)
{
	TileMap_Draw();
	Player_Draw();
	Enemy_Draw();
	Bullet_Draw();
	EnemyBullet_Draw();
	EnemyLaser_Draw();
	Explosion_Draw();

	//ライフ表示
	Score_Draw(0, 0, Player_GetHitPoint(), 7, true);
	//殺害数表示
	Score_Draw(950, 530, g_KillCount, 2, true);
}

//ゲームの終了条件を満たしているか
bool Game_EndCheck(void)
{
	//プレイヤーが死亡したら終了
	if (Player_GetHitPoint() <= 0)
	{
		StopSound();			//全ての音を停止
		Welose();				//負けフラグを建てる
		return true;			//終了フラグを建てる
	}

	//6階に到達したら終了(勝利)
	if (Mapwon())
	{
		StopSound();			//全ての音を停止
		Wewon();				//勝ちフラグを建てる
		return true;			//終了フラグを建てる
	}

	//そうでもなかったとき
	return false;
}


//殺害数を追加
void Game_AddKillCount()
{
	g_KillCount += 1;
}

//ゲーム中にフェードさせかつゲームを止めたいとき
void FadeOn()
{
	g_Phase = PHASE_INDEX_FADE;
}