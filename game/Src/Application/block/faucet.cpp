#include "faucet.h"
#include"Application/ModelIntersects.h"
#include"Application/Game.h"

bool C_faucet::CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _returnVec, float& _range)const
{
	Math::Vector3 blocknormal;


	if (ModelIntersects(*m_Sink, m_Sinkmat, _rayPos, _rayVec, _dis, blocknormal))
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



C_faucet::C_faucet(std::shared_ptr<ModelManager>& _om, const Math::Vector3& _pos)
{
	m_Faucet = _om->GetModel("Data/model/faucet.gltf");
	m_Sink = _om->GetModel("Data/model/sink.gltf");
	m_Waterfall = _om->GetModel("Data/model/waterfall.gltf");
	m_FaucetMat = DirectX::XMMatrixTranslation(_pos.x, _pos.y, _pos.z);
	m_Sinkmat = DirectX::XMMatrixTranslation(3.0f, 0.0f, 81.0f);
	m_Waterfmat = DirectX::XMMatrixTranslation(17.0f, 0.5f, 37.0f);
	open = false;
	alpha = 1.0f;
}

void C_faucet::Draw()
{
	AlphaSet(alpha);
	SHADER.m_standardShader.SetWorldMatrix(m_FaucetMat);
	SHADER.m_standardShader.DrawModel(m_Faucet, alpha);
	if (SYSTEM.GetwaterFlg() == true)
	{
		SHADER.m_standardShader.SetUVOffset(m_uvOffset);
		SHADER.m_standardShader.SetWorldMatrix(m_Waterfmat);
		SHADER.m_standardShader.DrawModel(m_Waterfall, 0.5f);
		SHADER.m_standardShader.SetUVOffset(Math::Vector2::Zero);
	}
	SHADER.m_standardShader.SetWorldMatrix(m_Sinkmat);
	SHADER.m_standardShader.DrawModel(m_Sink, alpha);
	D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, true), 0);
}

void C_faucet::Update()
{
	Math::Matrix m_scale;
	

	if (SYSTEM.GetwaterFlg() == true)
	{
		m_uvOffset.y -= 0.01f;
		if (open == false)
		{
			open = true;
			SYSTEM.GetSoundManager().SetSound("Data/music/water.wav");
		}
	}
	if (open == true)
	{
		scale_value += 0.1f;
		if (scale_value >= 1.0f)
		{
			scale_value = 1.0f;
		}
	}
	m_scale = DirectX::XMMatrixScaling(scale_value, 1.0f, scale_value);
	m_Waterfmat = m_scale* DirectX::XMMatrixTranslation(17.0f, 0.5f, 37.0f);
}

void C_faucet::AlphaSet(float& _alpha)
{
	GameScene* game;
	game = dynamic_cast<GameScene*>(SYSTEM.GetSceneManager().GetnowScene());
	Math::Vector3 ShortVecS;//真ん中ベクトル
	Math::Vector3 ShortVecR;//右側ベクトル
	Math::Vector3 ShortVecL;//左側ベクトル

	ShortVecS = m_Sinkmat.Translation() - game->GetPos();
	ShortVecR = (m_Sinkmat.Translation() + Math::Vector3(40.0f, 0.0f, -22.0f)) - game->GetPos();
	ShortVecL = (m_Sinkmat.Translation() + Math::Vector3(-40.0f, 0.0f, -15.0f)) - game->GetPos();
	ShortVecS.Normalize();
	ShortVecR.Normalize();
	ShortVecL.Normalize();
	Math::Vector3 DotS, DotR, DotL;
	DotS = DirectX::XMVector3Dot(ShortVecS, game->GetcamVec());
	DotR = DirectX::XMVector3Dot(ShortVecR, game->GetcamVec());
	DotL = DirectX::XMVector3Dot(ShortVecL, game->GetcamVec());

	float angXS, angXR, angXL;
	angXS = DirectX::XMConvertToDegrees(acos(DotS.x));
	angXR = DirectX::XMConvertToDegrees(acos(DotR.x));
	angXL = DirectX::XMConvertToDegrees(acos(DotL.x));


	if (angXS < 90 || angXR < 90 || angXL < 90)
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

