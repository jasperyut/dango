#include "button.h"
#include"Application/ModelIntersects.h"
#include"Application/Game.h"

C_button::C_button(std::shared_ptr<ModelManager>& _om, const Math::Vector3& _pos)
{
	m_Model = _om->GetModel("Data/model/buttonbase.gltf");
	m_Button[0] = _om->GetModel("Data/model/buttonwhite.gltf");
	m_Button[1] = _om->GetModel("Data/model/buttonpink.gltf");
	m_Button[2] = _om->GetModel("Data/model/buttongreen.gltf");

	m_Mat = DirectX::XMMatrixTranslation(_pos.x, _pos.y, _pos.z);

	buttontime = 120;
	active = true;
}

void C_button::Draw()
{
	SHADER.m_standardShader.SetWorldMatrix(m_Mat);

	SHADER.m_standardShader.DrawModel(m_Model);
	if (SYSTEM.Getcolormode() == 1)
	{
		SHADER.m_standardShader.DrawModel(m_Button[0]);
	}
	if (SYSTEM.Getcolormode() == 2)
	{
		SHADER.m_standardShader.DrawModel(m_Button[1]);
	}
	if (SYSTEM.Getcolormode() == 3)
	{
		SHADER.m_standardShader.DrawModel(m_Button[2]);
	}
}

void C_button::Update()
{
	GameScene* game;
	game = dynamic_cast<GameScene*>(SYSTEM.GetSceneManager().GetnowScene());


	if (SYSTEM.Getstate() == 1)
	{
		Math::Vector3 vlen;
		float len;
		Math::Vector3 pPos, rPos;
		pPos = m_Mat.Translation();
		pPos.y = 0;
		rPos = game->GetPos();
		rPos.y = 0;
		vlen = rPos - pPos;
		len = vlen.Length();


		if (active == true && buttontime == 0)
		{

			if (len < range)
			{
				//白モード
				if (SYSTEM.Getcolormode() == 1)
				{
					SYSTEM.Setcolormode(2);
					active = false;

				}
				//ピンクモード
				else if (SYSTEM.Getcolormode() == 2)
				{
					SYSTEM.Setcolormode(3);
					active = false;
				}
				//緑モード
				else
				{
					SYSTEM.Setstagecam(true);
					SYSTEM.Sethotstate(true);
					SYSTEM.GetSoundManager().SetSound("Data/music/fire.wav");
					active = false;

				}
				buttontime = 120;
			}
		}
	}

	buttontime--;
	if (buttontime <= 0)
	{
		buttontime = 0;
	}
}

bool C_button::CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _returnVec, float& _range)const
{
	Math::Vector3 blocknormal;


	if (ModelIntersects(*m_Model, m_Mat, _rayPos, _rayVec, _dis, blocknormal))
	{
		Math::Vector3 dot;
		dot = DirectX::XMVector3Dot(-_rayVec, blocknormal);

		float limit;
		limit = _range / dot.x;
		if (limit < 0)
		{
			limit *= -1;
		}

		//壁までlimit以下で当たっていたら
		if (_dis <= limit)
		{
			_returnVec = blocknormal * ((limit - _dis) * dot.x);
			return true;

		}
	}
	return false;
}