#include "SceneManager.h"

void SceneManager::DoScene()
{
	//次のシーンが今のと違い場合
	if (m_NextScene != m_NowScene)
	{
		//今シーンを削除
		if (m_NowScene != nullptr)
		{
			delete m_NowScene;
		}

		//次のシーンに切替
		m_NowScene = m_NextScene;
	}
	if (m_NowScene != nullptr)
	{
		//今シーンを実行
		m_NowScene->Frame();
	}
}

SceneManager::~SceneManager()
{
	if (m_NowScene != nullptr)
	{
		delete m_NowScene;
	}
}

void SceneManager::ChangeScene(Scene* _next)
{
	//次のシーンを読み込む
	m_NextScene = _next;
}