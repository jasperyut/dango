#include "block.h"
#include"Application/ModelIntersects.h"
#include"Application/Game.h"

bool C_block::CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _returnVec, float& _range)const
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
		//•Ç‚Ü‚ÅlimitˆÈ‰º‚Å“–‚½‚Á‚Ä‚¢‚½‚ç
		if (_dis <= limit)
		{
			_returnVec = blocknormal * ((limit - _dis) * dot.x);
			
			return true;
			
		}
		
	}
	return false;
}

C_block::C_block(std::shared_ptr<ModelManager>& _om, const Math::Vector3& _pos)
{
	m_Model = _om->GetModel("Data/model/block.gltf");
	m_Mat = DirectX::XMMatrixTranslation(_pos.x, _pos.y, _pos.z);
	m_Pos = _pos;
	alpha = 1.0f;
	movespeed = 0.05f;
	movestart = true;
}



void C_block::Draw()
{

	if (SYSTEM.GetnowStage() <= 3)
	{
		AlphaSet(alpha);
	}
	SHADER.m_standardShader.SetWorldMatrix(m_Mat);
	SHADER.m_standardShader.DrawModel(m_Model, alpha);
	D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, true), 0);
}

void C_block::Update()
{
	GameScene* game;
	game = dynamic_cast<GameScene*>(SYSTEM.GetSceneManager().GetnowScene());

	if (SYSTEM.GetwaterFlg() == true && game->Getwater()->GetMat()._42 >= 5.0f)
	{
		m_Mat._42 += 0.065f;

	}

	if (SYSTEM.GetwaterFlg() == false && game->Getwater()->GetMat()._42 >= 1.0f)
	{

		m_Mat._42 = 12.0f + sin(DirectX::XMConvertToRadians(m_SinAng)) * 0.5f;
		m_SinAng += rand() % 5;
	}

	if (SYSTEM.GetnowStage() == 1)
	{
		float moveVec;
		moveVec = m_Mat._41 - m_Pos.x;

		if (moveVec > 10 || moveVec < -10)
		{
			movespeed *= -1;
		}

		m_Mat._41 += movespeed;
	}
}

void C_block::AlphaSet(float& _alpha)
{
	GameScene* game;
	game = dynamic_cast<GameScene*>(SYSTEM.GetSceneManager().GetnowScene());
	Math::Vector3 ShortVec;
	ShortVec = m_Mat.Translation() - game->GetPos();
	ShortVec.Normalize();
	Math::Vector3 Dot;
	Dot = DirectX::XMVector3Dot(ShortVec, game->GetcamVec());
	float angX;
	angX = DirectX::XMConvertToDegrees(acos(Dot.x));


	if (angX < 30)
	{

		_alpha -= 0.05f;
		if (_alpha <= 0.2f)
		{
			_alpha = 0.2f;
		}
		D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, false), 0);
	}
	else
	{
		_alpha += 0.05f;
		if (_alpha >= 1.0f)
		{
			_alpha = 1.0f;
		}
		D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, true), 0);
	}


}


