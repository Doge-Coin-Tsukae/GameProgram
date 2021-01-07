#pragma once
#include <list>
#include <vector>
#include <typeinfo>
#include "main.h"
#include "gameobject.h"

#define MAX_LAYER 3

//list管理は、メモリ効率はいいが、処理速度が悪いので使い分けが必要。(一度に大量にオブジェクトが出すのはあらかじめ配列に入れるといい)
class CScene
{
protected:
	std::list<CGameObject*> m_GameObject[MAX_LAYER];

public:
	CScene() {}
	virtual ~CScene() {}

	virtual void Init() = 0;
	virtual void Uninit()
	{
		for (int i = 0; i < MAX_LAYER; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();
		}
	}

	virtual void Update()
	{
		for (int i = 0; i < MAX_LAYER; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Update();
			}
			//remove_ifはリストから外す関数。最初にリスト、次に条件
			m_GameObject[i].remove_if([](CGameObject* object)
			{return object->Destroy(); });//(ポインタクラス引数,条件引数)
			//ラムダ式
		}
	}

	virtual void Draw()
	{
		LIGHT light;

		for (int i = 0; i < MAX_LAYER; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}

	//ゲームオブジェクトが継承されたオブジェクトをリストに追加するテンプレート
	template <typename T>
	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
		gameObject->Init();

		return gameObject;
	}

	//ゲームオブジェクトが継承されたオブジェクトをリストに追加するテンプレート
	CGameObject* AddArgumentGameObject(CGameObject* gameobject,int Layer)
	{
		CGameObject* GameObject = gameobject;
		m_GameObject[Layer].push_back(GameObject);
		//gameobject->Init();

		return gameobject;
	}

	//ゲームオブジェクトを捜索するテンプレート(単体のみ)
	template <typename T>
	T* GetGameObject(int Layer)
	{
		for (CGameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))
			{
				return (T*)object;
			}
		}

		return NULL;
	}

	//ゲームオブジェクトを捜索するテンプレート(複数)
	template<typename T>
	std::vector<T*> GetGameObjects(int Layer)
	{
		std::vector<T*>objects;//STLの配列
		for (CGameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))
			{
				objects.push_back((T*)object);
			}
		}
		return objects;
	}

	//ゲームオブジェクトを全部引き出す大作戦(複数)
	template<typename T>
	std::vector<T*> GetALLGameObjects(int Layer)
	{
		std::vector<T*>objects;//STLの配列
		for (CGameObject* object : m_GameObject[Layer])
		{
			objects.push_back((T*)object);
		}
		return objects;
	}
};