#pragma once
#include "Scene.h"

class SceneManager
{
public:
	~SceneManager();

	void DoScene();//今のシーンを実行
	void ChangeScene(Scene* _next);//次のシーンに変える
	
	Scene* GetnowScene() {
		return m_NowScene;
	}

private:
	
	Scene* m_NowScene = nullptr;//今のシーン
	Scene* m_NextScene = nullptr;//次のシーン
	
};

#define SCENEMANAGER SceneManager::GetNowScene()