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
	//ゲーム更新
	Update();

	SHADER.m_cb8_Light.Write();

	// バックバッファクリア
	D3D.GetDevContext()->ClearRenderTargetView(D3D.GetBackBuffer()->GetRTView(), Math::Color(0.0f, 0.0f, 1.0f, 1));//RGBAを0-1の範囲で
	// Zバッファクリア
	D3D.GetDevContext()->ClearDepthStencilView(D3D.GetZBuffer()->GetDSView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);

	//カメラ、視界のセット
	SetCamera();

	// ゲーム描画処理
	Draw();
}

