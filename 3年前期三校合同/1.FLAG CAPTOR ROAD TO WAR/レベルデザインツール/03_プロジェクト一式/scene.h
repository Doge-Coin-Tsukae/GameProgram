#pragma once
#include <list>
#include <vector>
#include <typeinfo>
#include "main.h"
#include "gameobject.h"

#define MAX_LAYER 3

//list�Ǘ��́A�����������͂������A�������x�������̂Ŏg���������K�v�B(��x�ɑ�ʂɃI�u�W�F�N�g���o���̂͂��炩���ߔz��ɓ����Ƃ���)
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
			//remove_if�̓��X�g����O���֐��B�ŏ��Ƀ��X�g�A���ɏ���
			m_GameObject[i].remove_if([](CGameObject* object)
			{return object->Destroy(); });//(�|�C���^�N���X����,��������)
			//�����_��
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

	//�Q�[���I�u�W�F�N�g���p�����ꂽ�I�u�W�F�N�g�����X�g�ɒǉ�����e���v���[�g
	template <typename T>
	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
		gameObject->Init();

		return gameObject;
	}

	//�Q�[���I�u�W�F�N�g���p�����ꂽ�I�u�W�F�N�g�����X�g�ɒǉ�����e���v���[�g
	CGameObject* AddArgumentGameObject(CGameObject* gameobject,int Layer)
	{
		CGameObject* GameObject = gameobject;
		m_GameObject[Layer].push_back(GameObject);
		//gameobject->Init();

		return gameobject;
	}

	//�Q�[���I�u�W�F�N�g��{������e���v���[�g(�P�̂̂�)
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

	//�Q�[���I�u�W�F�N�g��{������e���v���[�g(����)
	template<typename T>
	std::vector<T*> GetGameObjects(int Layer)
	{
		std::vector<T*>objects;//STL�̔z��
		for (CGameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))
			{
				objects.push_back((T*)object);
			}
		}
		return objects;
	}

	//�Q�[���I�u�W�F�N�g��S�������o������(����)
	template<typename T>
	std::vector<T*> GetALLGameObjects(int Layer)
	{
		std::vector<T*>objects;//STL�̔z��
		for (CGameObject* object : m_GameObject[Layer])
		{
			objects.push_back((T*)object);
		}
		return objects;
	}
};