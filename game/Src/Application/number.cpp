#include"number.h"
#include"define.h"
#include"System/KeySystem.h"

C_number::C_number()
{
	m_Tex.Load("Data/Texture/number.png");
}
C_number::~C_number()
{
	m_Tex.Release();
}
void C_number::Draw()
{
	Math::Rectangle rcNum[] = {
	{0,0,  27,34},
	{28,0, 27,34},
	{56,0, 27,34},
	{84,0, 27,34},
	{112,0,27,34},
	{140,0,27,34},
	{168,0,27,34},
	{196,0,27,34},
	{224,0,27,34},
	{252,0,27,34} };
	Math::Matrix trans;
	trans = DirectX::XMMatrixTranslation(-35.0f, 0, 0);
	int i;
	StartTime++;
	int t;
	t = StartTime / 60;

	
	Math::Matrix tmptrans;
	Math::Matrix m_Scale;
	m_Scale = DirectX::XMMatrixScaling(1.5, 1.5, 1.5);

	char cTime[64];
	sprintf_s(cTime, "%d", t);
	char nowTime[64];
	sprintf_s(nowTime, "%d", SYSTEM.GetnowTime());

	for (i = 0; cTime[i] != '\0'; i++);
	if (SYSTEM.GetnowStage() != 0)
	{
		tmptrans = DirectX::XMMatrixTranslation(-480.0f, ScrH / 2 - 50.0f, 0);
		m_timemat = m_Scale * tmptrans;
		for (i -= 1; i >= 0; i--)
		{
			SHADER.m_spriteShader.SetMatrix(m_timemat);
			SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle(rcNum[cTime[i] - '0']), 1.0f, Math::Vector2(1.0f, 1.0f));
			m_timemat *= trans;
			SYSTEM.SetCurrenTime(t);
		}

	}
	else
	{
		tmptrans = DirectX::XMMatrixTranslation(220, -120, 0);
		m_timemat = m_Scale * tmptrans;
		for (i = 1; i >= 0; i--)
		{
			SHADER.m_spriteShader.SetMatrix(m_timemat);
			SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle(rcNum[nowTime[i] - '0']), 1.0f, Math::Vector2(1.0f, 1.0f));
			m_timemat *= trans;
		}
	}
}

void C_number::Update()
{

}
