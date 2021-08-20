#include "SceneManager.h"

void SceneManager::DoScene()
{
	//���̃V�[�������̂ƈႢ�ꍇ
	if (m_NextScene != m_NowScene)
	{
		//���V�[�����폜
		if (m_NowScene != nullptr)
		{
			delete m_NowScene;
		}

		//���̃V�[���ɐؑ�
		m_NowScene = m_NextScene;
	}
	if (m_NowScene != nullptr)
	{
		//���V�[�������s
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
	//���̃V�[����ǂݍ���
	m_NextScene = _next;
}