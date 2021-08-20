#include "can.h"
#include"Application/ModelIntersects.h"
#include"Application/player/statelist.h"

bool C_can::CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _returnVec, float& _range) const
{
	Math::Vector3 blocknormal;


	if (ModelIntersects(*m_Model[0], m_Mat, _rayPos, _rayVec, _dis, blocknormal))
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

C_can::C_can(std::shared_ptr<ModelManager>& _om, const Math::Vector3& _pos)
{

	m_Model[0] = _om->GetModel("Data/model/can.gltf");
	m_Model[1] = _om->GetModel("Data/model/can.gltf");

	m_Mat = DirectX::XMMatrixTranslation(_pos.x, _pos.y, _pos.z);
	alpha = 1.0f;
	OutlineFlg = false;
}


void C_can::Draw()
{
	OutLine();
	AlphaSet(alpha);
	SHADER.m_standardShader.SetWorldMatrix(m_Mat);
	SHADER.m_standardShader.DrawModel(m_Model[0], alpha);
	D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, true), 0);
}

void C_can::Update()
{
	GameScene* game;
	game = dynamic_cast<GameScene*>(SYSTEM.GetSceneManager().GetnowScene());

	Math::Vector3 vlen;
	float len;
	Math::Vector3 pPos, rPos;
	pPos = m_Mat.Translation();
	pPos.y = 0;
	rPos = game->GetMat().Translation();//主人公の位置
	rPos.y = 0;
	vlen = rPos - pPos;
	len = vlen.Length();

	//一定距離以下
	//主人公のモード３しか作動しない
	if (SYSTEM.Getstate() == 3)
	{
		if (len < (1.8f + range))
		{

			float pushlen;
			pushlen = (1.8f + range) - len;

			vlen.Normalize();
			vlen *= pushlen;
			vlen.y = 0.0f;
			vlen.z = 0.0f;

			m_Pos = m_Mat.Translation() - vlen;


			if (SYSTEM.Getstagecam() == false)
			{
				m_Mat = DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
			}
		}
	}
	else
	{
		//主人公が近づくとヒントをあげる
		if (len < (10.0f + range))
		{
			OutlineFlg = true;
		}
		else
		{
			OutlineFlg = false;
		}
	}


}
void C_can::AlphaSet(float& _alpha)
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


	if (angX < 60)
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

void C_can::OutLine()
{
	if (OutlineFlg)
	{
		Math::Matrix OutlineMat;
		Math::Matrix Scale;
		Scale = DirectX::XMMatrixScaling(1.03f, 1.03f, 1.03f);
		OutlineMat = Scale * m_Mat;
		D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, false), 0);
		SHADER.m_standardShader.SetWorldMatrix(OutlineMat);
		SHADER.m_standardShader.DrawModel(m_Model[1], alpha, { 1.0f,1.0f,0.1f });
	}
}



