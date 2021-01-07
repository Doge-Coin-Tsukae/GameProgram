#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"

#include"tree.h"
#include "meshfield.h"
#include "human.h"
#include "model.h"
#include "colider.h"
#include "sight.h"
#include "weapon.h"
#include "animationmodel.h"
#include "player.h"
#include "enemy.h"
#include "deadtree.h"
#include "bunker.h"
#include "base.h"
#include "load.h"

void CLOAD::Uninit()
{

}

void CLOAD::Update()
{
	//Iを押したときにファイルを読み込む処理を入れる
	if (CInput::GetKeyTrigger('I'))
		Data_Load();
}

void CLOAD::Data_Load()
{
	FILE *SaveFile;//ファイルポインタ
	CScene* scene = CManager::GetScene();	

	Data_Destroy();	//ロードする前にそれまでに配置されていたオブジェクトを削除する

	//プレイヤーの情報をファイルから読み込む
	{
		SaveFile = fopen("asset/savedata/playerdata.txt", "r");
		if (SaveFile == NULL)           // オープンに失敗した場合
			return;

		CPlayer* pPlayer = new CPlayer();
		pPlayer->Init();
		pPlayer->Load(SaveFile);
		scene->AddArgumentGameObject(pPlayer,1);

		fclose(SaveFile);
	}

	//敵の情報をファイルから読み込む
	{
		SaveFile = fopen("asset/savedata/enemydata.txt", "r");
		if (SaveFile == NULL)           // オープンに失敗した場合
			return;

		for (int i = 0; i < 3; i++)
		{
			//CEnemy* pEnemy = new CEnemy();
			//pEnemy->Init();
			//pEnemy->Load(SaveFile,i);
			//scene->AddArgumentGameObject(pEnemy, 1);
		}

		fclose(SaveFile);
	}

	//バンカー情報をファイルから読み込む
	{
		SaveFile = fopen("asset/savedata/bunkerdata.txt", "r");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;

		for (int i = 0; i < 3; i++)
		{
			CBUNKER* pBunker = new CBUNKER();
			pBunker->Init();
			pBunker->Load(SaveFile, i);
			scene->AddArgumentGameObject(pBunker, 1);
		}

		fclose(SaveFile);
	}

	//拠点情報をファイルから読み込む
	{
		SaveFile = fopen("asset/savedata/basedata.txt", "r");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;

		for (int i = 0; i < 3; i++)
		{
			CBASE* pBase = new CBASE();
			pBase->Init();
			pBase->Load(SaveFile, i);
			scene->AddArgumentGameObject(pBase, 2);
		}

		fclose(SaveFile);
	}

	//木情報をファイルから読み込む
	{
		SaveFile = fopen("asset/savedata/treedata.txt", "r");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;

		for (int i = 0; i < 10; i++)
		{
			CTREE* pTree = new CTREE();
			pTree->Init();
			pTree->Load(SaveFile, i);
			scene->AddArgumentGameObject(pTree, 3);
		}

		fclose(SaveFile);
	}

	//枯れ木情報をファイルから読み込む
	{
		SaveFile = fopen("asset/savedata/deadtreedata.txt", "r");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;

		for (int i = 0; i < 10; i++)
		{
			CDEADTREE* pDeadTree = new CDEADTREE();
			pDeadTree->Init();
			pDeadTree->Load(SaveFile, i);
			scene->AddArgumentGameObject(pDeadTree, 1);
		}

		fclose(SaveFile);
	}

	//地形情報をファイルから読み込む
	{
		SaveFile = fopen("asset/savedata/field.txt", "r");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;

		CMeshField* pMeshField = scene->GetGameObject<CMeshField>(1);
		
		fclose(SaveFile);
	}
}

void CLOAD::Data_Destroy()
{
	CScene* scene = CManager::GetScene();

	CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);
	if(pPlayer  != nullptr)		//プレイヤー情報があったときだけ消す
		pPlayer->SetDestroy();

	//リストからピックアップしてデータ削除
	std::vector<CEnemy*> enemylist = scene->GetGameObjects<CEnemy>(1);
	for (CEnemy* enemy : enemylist)
	{
		enemy->SetDestroy();
	}

	//リストからピックアップしてデータ削除
	std::vector<CBUNKER*> bunkerlist = scene->GetGameObjects<CBUNKER>(1);
	for (CBUNKER* bunker : bunkerlist)
	{
		bunker->SetDestroy();
	}

	//リストからピックアップしてデータ削除
	std::vector<CBASE*> baselist = scene->GetGameObjects<CBASE>(1);
	for (CBASE* base : baselist)
	{
		base->SetDestroy();
	}

	//リストからピックアップしてデータ削除
	std::vector<CTREE*> treelist = scene->GetGameObjects<CTREE>(3);
	for (CTREE* tree : treelist)
	{
		tree->SetDestroy();
	}

	//リストからピックアップしてデータ削除
	std::vector<CDEADTREE*> deadtreelist = scene->GetGameObjects<CDEADTREE>(1);
	for (CDEADTREE* deadtree : deadtreelist)
	{
		deadtree->SetDestroy();
	}
}