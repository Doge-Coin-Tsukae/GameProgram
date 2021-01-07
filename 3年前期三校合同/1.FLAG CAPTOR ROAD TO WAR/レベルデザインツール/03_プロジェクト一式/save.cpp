//
//データのセーブ
//

#include "main.h"
#include <tchar.h>
#include "filewinapi.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"

#include"tree.h"
#include "meshfield.h"
#include "human.h"
#include "model.h"
#include "carsor.h"
#include "colider.h"
#include "sight.h"
#include "weapon.h"
#include "player.h"
#include "enemy.h"
#include "deadtree.h"
#include "bunker.h"
#include "base.h"
#include "save.h"

void CSAVE::Uninit()
{

}

void CSAVE::Update()
{
	if (CInput::GetKeyTrigger('U'))
		Data_Save();
}


TCHAR* CSAVE::PassAsset(TCHAR path[300])
{
	for (int i = 0; i < 300; i++)
	{
		if (path[i] == 'a')
		{
			if (path[i + 1] == 's')
			{
				if (path[i + 2] == 's')
				{
					if (path[i + 3] == 'e')
					{
						if (path[i + 4] == 't')
						{
							TCHAR temp[300];
							for (int j = 0; j < 300; j++)
							{
								temp[j] = path[j + i];
							}
							return temp;
						}
					}
				}
			}
		}
	}
}


void CSAVE::Data_Save()
{
	ShowCursor(TRUE);

	FILE *SaveFile;
	CScene* scene = CManager::GetScene();


	TCHAR def_dir[100], path[300];

	_tcscpy_s(def_dir, sizeof(def_dir) / sizeof(TCHAR), _TEXT("D:"));
	if (GetDir(GetWindow(), def_dir, path) == false)
		return;

	ShowCursor(FALSE);

	TCHAR *path2 = NULL;
	TCHAR temp[300];
	path2 = PassAsset(path);//ファイルのパスをassetフォルダからにする
	strcpy(temp, path2);

	//プレイヤーの情報をファイルに書き込む
	{
		strcat(path2, "/playerdata.txt");
		SaveFile = fopen(path2, "w");

		if (SaveFile == NULL)           // オープンに失敗した場合
			return;                         // 異常終了
		//プレイヤーの情報を書き出す
		CPlayer* pPlayer = scene->GetGameObject<CPlayer>(1);
		pPlayer->Save(SaveFile);
		fclose(SaveFile);
	}

	//敵の情報をファイルに書き込む
	{
		strcpy(path2, temp);
		strcat(path2, "/enemydata.txt");
		SaveFile = fopen(path2, "w");

		if (SaveFile == NULL)           // オープンに失敗した場合
			return;                         // 異常終了
		//敵の情報を書き出す

		std::vector<CEnemy*> enemylist = scene->GetGameObjects<CEnemy>(1);

		//個数を保存する
		fprintf(SaveFile, "%d\n");

		for (CEnemy* enemy : enemylist)
		{
			enemy->Save(SaveFile);
		}

		fclose(SaveFile);
	}

	//バンカー情報をファイルに書き込む
	{
		strcpy(path2, temp);
		strcat(path2, "/bunkerdata.txt");
		SaveFile = fopen(path2, "w");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;				// 異常終了
		//情報を書き込む
		std::vector<CBUNKER*> bunkerlist = scene->GetGameObjects<CBUNKER>(1);
		for (CBUNKER* bunker : bunkerlist)
		{
			bunker->Save(SaveFile);
		}

		fclose(SaveFile);
	}
	//拠点情報を書き込む
	{
		strcpy(path2, temp);
		strcat(path2, "/basedata.txt");
		SaveFile = fopen(path2, "w");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;             // 異常終了
		//情報を書き込む
		std::vector<CBASE*> baselist = scene->GetGameObjects<CBASE>(1);
		for (CBASE* base : baselist)
		{
			base->Save(SaveFile);
		}

		fclose(SaveFile);
	}
	//木情報を書き込む
	{
		strcpy(path2, temp);
		strcat(path2, "/treedata.txt");
		SaveFile = fopen(path2, "w");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;				// 異常終了
		//情報を書き込む
		std::vector<CTREE*> treelist = scene->GetGameObjects<CTREE>(1);
		for (CTREE* tree : treelist)
		{
			tree->Save(SaveFile);
		}

		fclose(SaveFile);
	}
	//枯れ木情報を書き込む
	{
		strcpy(path2, temp);
		strcat(path2, "/deadtreedata.txt");
		SaveFile = fopen(path2, "w");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;				// 異常終了
		//情報を書き込む
		std::vector<CDEADTREE*> deadtreelist = scene->GetGameObjects<CDEADTREE>(1);
		for (CDEADTREE* deadtree : deadtreelist)
		{
			deadtree->Save(SaveFile);
		}

		fclose(SaveFile);
	}
	//地形情報をファイルに書き込む
	{
		strcpy(path2, temp);
		strcat(path2, "/field.txt");
		SaveFile = fopen(path2, "w");
		if (SaveFile == NULL)	// オープンに失敗した場合
			return;				// 異常終了
		CMeshField* pMeshField = scene->GetGameObject<CMeshField>(1);
		pMeshField->Save(SaveFile);
		fclose(SaveFile);
	}
}