#include "background.h"

C_Background::C_Background()
{
	m_Model.Load("Data/model/background/background.gltf");
}

C_Background::~C_Background()
{
	m_Model.Release();
}

void C_Background::Draw()
{
	SHADER.m_standardShader.SetWorldMatrix(m_Mat);
	SHADER.m_standardShader.DrawModel(&m_Model);
}
