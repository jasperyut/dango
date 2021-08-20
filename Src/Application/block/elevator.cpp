#include "elevator.h"
#include"Application/ModelIntersects.h"
#include"Application/Game.h"

C_elevator::C_elevator(std::shared_ptr<ModelManager>& _om, const Math::Vector3& _pos)
{
	m_Elevator = _om->GetModel("Data/model/elevator.gltf");
	m_Aura[0] = _om->GetModel("Data/model/aurawhite.gltf");
	m_Aura[1] = _om->GetModel("Data/model/aurapink.gltf");
	m_Aura[2] = _om->GetModel("Data/model/auragreen.gltf");
	m_Mat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90))*DirectX::XMMatrixTranslation(_pos.x, _pos.y, _pos.z);
	m_Pos = _pos;
	range = 4.0f;
	process = 0;
	Wswitch = false;
	Pswitch = false;
	Gswitch = false;
	actived = false;
}

void C_elevator::Draw()
{
	SHADER.m_standardShader.SetWorldMatrix(m_Mat);
	SHADER.m_standardShader.DrawModel(m_Elevator);
	D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(false, true), 0);
	D3D.GetDevContext()->OMSetBlendState(D3D.CreateBlendState(KdBlendMode::Add), Math::Color(0, 0, 0, 0), 0xFFFFFFFF);
	if (Wswitch == true)
	{
		SHADER.m_standardShader.DrawModel(m_Aura[0]);
	}
	if (Pswitch == true)
	{
		SHADER.m_standardShader.DrawModel(m_Aura[1]);
	}
	if (Gswitch == true)
	{
		SHADER.m_standardShader.DrawModel(m_Aura[2]);
	}
	D3D.GetDevContext()->OMSetBlendState(D3D.CreateBlendState(KdBlendMode::Alpha), Math::Color(0, 0, 0, 0), 0xFFFFFFFF);
	D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, true), 0);
}

void C_elevator::Update()
{
	GameScene* game;
	game = dynamic_cast<GameScene*>(SYSTEM.GetSceneManager().GetnowScene());

	if (SYSTEM.Getstate() == 1)
	{
		Math::Vector3 WhiteVec, PinkVec, GreenVec;
		float Whitelen, Pinklen, Greenlen;
		WhiteVec = m_Mat.Translation() - game->GetPos();
		PinkVec = m_Mat.Translation() - game->GetFellow1()->GetPos();
		GreenVec = m_Mat.Translation() - game->GetFellow2()->GetPos();
		Whitelen = WhiteVec.Length();
		Pinklen = PinkVec.Length();
		Greenlen = GreenVec.Length();
		if (Whitelen < range)
		{
			Wswitch = true;
		}
		else
		{
			Wswitch = false;
		}
		if (Pinklen < range)
		{
			Pswitch = true;
		}
		else
		{
			Pswitch = false;
		}
		if (Greenlen < range)
		{
			Gswitch = true;
		}
		else
		{
			Gswitch = false;
		}
	}
	else
	{
		Wswitch = false;
		Pswitch = false;
		Gswitch = false;
	}

	if (SYSTEM.Getstagecam() == true||(process==2&&game->GetPos().y<=0.0f))
	{
		actived = true;
	}
	if (actived == true)
	{
		m_Pos.y -= 0.3f;
		
		if ((int)m_Pos.y % 15 ==0&&(int)m_Pos.y!=0 )
		{
			SYSTEM.GetSoundManager().SetSound("Data/music/ropesound.wav");
		}

		if (m_Pos.y <= -1.0f)
		{
			m_Pos.y = -1.0f;
			actived = false;
			process = 1;
		}
	}

	if (Wswitch == true && Pswitch == true && Gswitch == true&&process==1)
	{
		m_Pos.y += 0.3f;
		if ((int)m_Pos.y % 15 == 0&&(int)m_Pos.y != 0)
		{
			SYSTEM.GetSoundManager().SetSound("Data/music/ropesound.wav");
		}
		if (m_Pos.y >= 60.0f)
		{
			m_Pos.y = 60.0f;
			process = 2;
		}
	}

	

	m_Mat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90)) * DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
}

bool C_elevator::CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _returnVec, float& _range) const
{
	Math::Vector3 blocknormal;


	if (ModelIntersects(*m_Elevator, m_Mat, _rayPos, _rayVec, _dis, blocknormal))
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
			_returnVec = blocknormal * ((limit - _dis) * dot.x);

			return true;

		}

	}
	return false;
}
