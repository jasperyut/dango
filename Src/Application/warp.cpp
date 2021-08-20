#include "warp.h"
#include"System/KeySystem.h"

C_Warp::C_Warp()
{
	m_Model.Load("Data/model/warp.gltf");
	if (SYSTEM.GetnowStage() == 1)
	{
		m_Mat = DirectX::XMMatrixTranslation(7.0f, 33.0f, 110.0f);
	}
	if (SYSTEM.GetnowStage() == 2)
	{
		m_Mat = DirectX::XMMatrixTranslation(-23.0f, 17.0f, 103.0f);
	}
	if (SYSTEM.GetnowStage() == 3)
	{
		m_Mat = DirectX::XMMatrixTranslation(0.0f, 17.0f, 103.0f);
	}
}

C_Warp::~C_Warp()
{
	m_Model.Release();
}

void C_Warp::Draw()
{
	SHADER.m_standardShader.SetWorldMatrix(m_Mat);
	SHADER.m_standardShader.SetNetallic(1.0f);
	SHADER.m_standardShader.DrawModel(&m_Model);
}

void C_Warp::Update()
{
}
