#include "bbqgrill.h"
#include"Application/ModelIntersects.h"
#include"Application/Game.h"

C_BBQgrill::C_BBQgrill(std::shared_ptr<ModelManager>& _om, const Math::Vector3& _pos)
{
	m_Model = _om->GetModel("Data/model/bbqgrill.gltf");
	m_Gravity = _om->GetModel("Data/model/bbqgravity.gltf");
	alpha = 1.0f;



	m_Mat = DirectX::XMMatrixTranslation(_pos.x, _pos.y, _pos.z);
	g_Mat = DirectX::XMMatrixTranslation(_pos.x, _pos.y, _pos.z);

}

void C_BBQgrill::Draw()
{
	if (SYSTEM.GetnowStage() <= 3)
	{
		AlphaSet(alpha);
	}
	SHADER.m_standardShader.SetWorldMatrix(m_Mat);
	SHADER.m_standardShader.DrawModel(m_Model,alpha);
	SHADER.m_standardShader.SetWorldMatrix(g_Mat);
	D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, true), 0);



}

void C_BBQgrill::Update()
{
}

bool C_BBQgrill::CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _returnVec, float& _range) const
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
	if (ModelIntersects(*m_Gravity, g_Mat, _rayPos, _rayVec, _dis, blocknormal))
	{
		if (SYSTEM.GetHotState() == true)
		{
			Math::Vector3 dot;
			dot = DirectX::XMVector3Dot(-_rayVec, blocknormal);

			float limit;
			limit = rand() % 20 / dot.x;
			if (limit < 0)
			{
				limit *= -1;
			}
			//•Ç‚Ü‚ÅlimitˆÈ‰º‚Å“–‚½‚Á‚Ä‚¢‚½‚ç
			if (_dis <= limit)
			{
				_returnVec = blocknormal * ((limit - _dis) * dot.x) * 0.05f;
				return true;
			}
		}
	}
	return false;
}

void C_BBQgrill::AlphaSet(float& _alpha)
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
	

	if (angX<70)
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



