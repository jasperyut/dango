#include"icon.h"

C_icon::C_icon()
{
	m_State[0].Load("data/texture/state1.png");
	m_State[1].Load("data/texture/state2.png");
	m_State[2].Load("data/texture/state3.png");
	m_MouseClick.Load("Data/Texture/mouseclick.png");
	alpha = 0.5f;
	for (int i = 0; i < 3; i++)
	{
		m_Mat[i] = DirectX::XMMatrixTranslation(350.0f + i * 90.0f, -280.0f, 0.0f);
	}
	click_mat = DirectX::XMMatrixTranslation(440.0f, -200.0f, 0.0f);
}

C_icon::~C_icon()
{
	for (int i = 0; i < 3; i++)
	{
		m_State[i].Release();
	}
	m_MouseClick.Release();
}

void C_icon::Draw(int _flg)
{
	for (int i = 0; i < 3; i++)
	{
		if (_flg-1 == i)
		{
			alpha = 1.0f;
		}
		else
		{
			alpha = 0.5f;
		}
		SHADER.m_spriteShader.SetMatrix(m_Mat[i]);
		SHADER.m_spriteShader.DrawTex(&m_State[i], Math::Rectangle(0, 0, 80, 96), alpha);

		SHADER.m_spriteShader.SetMatrix(click_mat);
		SHADER.m_spriteShader.DrawTex(&m_MouseClick, Math::Rectangle(0, 0, 180, 70), 1.0f);

		Math::Matrix m_Scale[3];
		Math::Matrix m_Trans;
		m_Scale[_flg-1] = DirectX::XMMatrixScaling(1.2f, 1.2f, 1.2f);
		m_Trans= DirectX::XMMatrixTranslation(350.0f + i * 90.0f, -280.0f, 0.0f);
		m_Mat[i] = m_Scale[i] * m_Trans;
	}
}

void C_icon::Update()
{
}
