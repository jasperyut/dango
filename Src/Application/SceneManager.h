#pragma once
#include "Scene.h"

class SceneManager
{
public:
	~SceneManager();

	void DoScene();//���̃V�[�������s
	void ChangeScene(Scene* _next);//���̃V�[���ɕς���
	
	Scene* GetnowScene() {
		return m_NowScene;
	}

private:
	
	Scene* m_NowScene = nullptr;//���̃V�[��
	Scene* m_NextScene = nullptr;//���̃V�[��
	
};

#define SCENEMANAGER SceneManager::GetNowScene()