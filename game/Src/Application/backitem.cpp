#include"backitem.h"

C_Backitem::C_Backitem()
{
	m_Model.Load("Data/model/background/backgrounditem.gltf");
	m_Mat = DirectX::XMMatrixTranslation(0, 3.0f, 0);
}

C_Backitem::~C_Backitem()
{
	m_Model.Release();
}

void C_Backitem::Draw()
{
	SHADER.m_standardShader.SetWorldMatrix(m_Mat);
	SHADER.m_standardShader.DrawModel(&m_Model);
}
