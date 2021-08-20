#include "water.h"
#include"Application/ModelIntersects.h"
#include"Application/Game.h"

C_water::C_water()
{
	m_Model.Load("Data/model/water.gltf");
	m_Mat = DirectX::XMMatrixTranslation(31.0f, 0.5f, 71.0f);
	alpha = 0.0f;
	sinkflg = false;
}

C_water::~C_water()
{
	m_Model.Release();
}

void C_water::Draw()
{	
	SHADER.m_standardShader.SetWorldMatrix(m_Mat);
	SHADER.m_standardShader.DrawModel(&m_Model,alpha);
}

void C_water::Update()
{
	if (SYSTEM.GetwaterFlg() == true)
	{
		m_Mat._42 += 0.065f;
		alpha = 0.5f;
		if (m_Mat._42 >= 15.0f)
		{
			SYSTEM.SetwaterFlg(false);
		}
	}
	//…‚Ìã‰ºˆÚ“®
	if (SYSTEM.GetwaterFlg() == false && m_Mat._42 >= 1.0f)
	{
		m_Mat._42 = 15.0f + sin(DirectX::XMConvertToRadians(m_SinAng)) * 0.5f;
		m_SinAng += rand() % 5;
	}

	if (SYSTEM.GetoverFlg() == true && sinkflg == false)
	{
		sinkflg = true;
		SYSTEM.GetSoundManager().SetSound("Data/music/sink.wav");
	}


}

bool C_water::CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, float& _range)const
{
	if (SYSTEM.GetnowStage() == 2)
	{
		Math::Vector3 blocknormal;

		GameScene* game;
		game = dynamic_cast<GameScene*>(SYSTEM.GetSceneManager().GetnowScene());

		if (ModelIntersects(m_Model, m_Mat, _rayPos, _rayVec, _dis, blocknormal))
		{
			Math::Vector3 dot;
			dot = DirectX::XMVector3Dot(-_rayVec, blocknormal);

			float limit;
			limit = _range / dot.x;
			if (limit < 0)
			{
				limit *= -1;
			}
			//•Ç‚Ü‚ÅlimitˆÈ‰º‚Å“–‚½‚Á‚Ä‚¢‚½‚ç
			if (_dis <= limit)
			{
				SYSTEM.SetOverFlg(true);
				return true;
			}
		}
	}
	
	return false;

}
