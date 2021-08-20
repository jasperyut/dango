#include "Scene.h"

Scene::~Scene()
{

}

void Scene::Update()
{

}

void Scene::Draw()
{

}

void Scene::SetCamera()
{

}

void Scene::Frame()
{
	//�Q�[���X�V
	Update();

	SHADER.m_cb8_Light.Write();

	// �o�b�N�o�b�t�@�N���A
	D3D.GetDevContext()->ClearRenderTargetView(D3D.GetBackBuffer()->GetRTView(), Math::Color(0.0f, 0.0f, 1.0f, 1));//RGBA��0-1�͈̔͂�
	// Z�o�b�t�@�N���A
	D3D.GetDevContext()->ClearDepthStencilView(D3D.GetZBuffer()->GetDSView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);

	//�J�����A���E�̃Z�b�g
	SetCamera();

	// �Q�[���`�揈��
	Draw();
}

