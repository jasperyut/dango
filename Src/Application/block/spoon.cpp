#include"spoon.h"
#include"Application/ModelIntersects.h"
#include"Application/Game.h"

bool C_spoon::CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _returnVec, float& _range)const
{
	Math::Vector3 blocknormal;

	GameScene* game;
	game = dynamic_cast<GameScene*>(SYSTEM.GetSceneManager().GetnowScene());

	if (ModelIntersects(*m_Shell, m_SpoonMat, _rayPos, _rayVec, _dis, blocknormal))
	{
		Math::Vector3 dot;
		dot = DirectX::XMVector3Dot(-_rayVec, blocknormal);

		float limit;
		limit = 0.8f / dot.x;

		//壁までlimit以下で当たっていたら
		if (_dis <= limit)
		{
			_returnVec = blocknormal * ((limit - _dis) * dot.x);
			if (SYSTEM.Getstate() == 3&&SYSTEM.Getfalling()==true)
			{
				SYSTEM.SetSpoonFlg(true);
			}
			else
			{
				SYSTEM.SetSpoonFlg(false);
			}

			return true;

		}
	}
	return false;
}

void C_spoon::OutLine()
{
	if (OutlineFlg)
	{
		Math::Matrix OutlineMat;
		Math::Matrix Scale;
		Scale = DirectX::XMMatrixScaling(1.15f, 1.28f, 1.03f);
		OutlineMat = Scale * m_RotY * m_RotZ * m_SpoonTrans;
		D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, false), 0);
		SHADER.m_standardShader.SetWorldMatrix(OutlineMat);
		SHADER.m_standardShader.DrawModel(m_Spoon[1] ,1.0f,{ 1.0f,1.0f,0.1f });
		D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, true), 0);
	}
}

C_spoon::C_spoon(std::shared_ptr<ModelManager>& _om, const Math::Vector3& _pos)
{
	
	m_Spoon[0] = _om->GetModel("Data/model/spoon.gltf");
	m_Spoon[1] = _om->GetModel("Data/model/spoon.gltf");
	m_Shell = _om->GetModel("Data/model/spoonshell.gltf");
	m_Dango = _om->GetModel("Data/model/player/dangomixtrans2.gltf");
	ang = 10;
	d_ang = 0;
	Inertia = 0;
	m_camAngY = 0;
	waterwaittime = 30;
	usedFlg = false;
	checkout = false;
	sound = false;
	OutlineFlg = false;
	waittimeover = false;
	m_RotY = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90));
	m_RotZ = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(ang));

	
	m_DangoPos = { _pos.x - 9.0f,1.0f,_pos.z };
	m_SpoonTrans = DirectX::XMMatrixTranslation(_pos.x, _pos.y, _pos.z);
	m_SpoonMat = m_RotY*m_RotZ*m_SpoonTrans;
	m_DangoMat = m_RotY * m_RotZ * DirectX::XMMatrixTranslation(m_DangoPos.x, m_DangoPos.y, m_DangoPos.z);
}



void C_spoon::Draw()
{
	OutLine();
	SHADER.m_standardShader.SetWorldMatrix(m_SpoonMat);
	SHADER.m_standardShader.DrawModel(m_Spoon[0]);
	//SHADER.m_standardShader.DrawModel(m_shell);
	SHADER.m_standardShader.SetWorldMatrix(m_DangoMat);
	SHADER.m_standardShader.DrawModel(m_Dango);


	

	

}

void C_spoon::Update()
{

	GameScene* game;
	game = dynamic_cast<GameScene*>(SYSTEM.GetSceneManager().GetnowScene());

	Math::Matrix dangoRotY;
	dangoRotY = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90));
	Math::Matrix dangoRotZ;
	dangoRotZ = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(d_ang));
	float len = {};

	if (SYSTEM.Getstate() == 3)
	{
		len = game->GetMat()._42 - m_SpoonMat._42;
	}
	else
	{
		Math::Vector3 vlen;
		float len;
		Math::Vector3 pPos, rPos;
		pPos = m_SpoonMat.Translation();
		pPos.y = 0;
		rPos = game->GetMat().Translation();//主人公の位置
		rPos.y = 0;
		vlen = rPos - pPos;
		len = vlen.Length();

		//主人公が近づくとヒントをあげる
		if (len < (20.0f)&& usedFlg == false)
		{
			OutlineFlg = true;
		}
		else
		{
			OutlineFlg = false;
		}
	}
	
	if (SYSTEM.GetSpoonFlg()==true&&usedFlg == false)
	{
		gravity = 1.0f;
		Inertia = 1.0f;
		usedFlg = true;
		SYSTEM.Setstagecam(true);

	}

	if (usedFlg == true)
	{
		if (sound == false)
		{
			sound = true;
			SYSTEM.GetSoundManager().SetSound("Data/music/spoonhit.wav");
		}


		ang -= 5.0f;
		if (ang <= -10.0f)
		{
			ang = -10.0f;
		}
		m_DangoPos.y += gravity;
		gravity -= 0.03f;

		if (m_DangoPos.y <= 1.0f)
		{
			m_DangoPos.y = 1.0f;
			gravity = 0;
			Inertia += 0.01f;
			if (Inertia >= 0)
			{
				Inertia = 0;
			}
		}

		if (m_DangoPos.x >= 25.0f)
		{
			Inertia *= -1;
			SYSTEM.GetSoundManager().SetSound("Data/music/faucetbt.wav");
			
		}
		if (Inertia<=0 && waittimeover == false)
		{
			waterwaittime--;
		}
		if (waterwaittime < 0)
		{
			waittimeover = true;
			waterwaittime = 0;
			SYSTEM.SetwaterFlg(true);
		}

		d_ang -= Inertia * 20;

		m_DangoPos.x += Inertia;


	}

	Math::Vector3 SpoonDango;
	Math::Matrix tmpRotY;
	tmpRotY = m_RotY;
	m_RotZ = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(ang));
	SpoonDango =DirectX::XMVector3TransformNormal(Math::Vector3(0, 0, 0.5f), tmpRotY);
	m_DangoTrans = DirectX::XMMatrixTranslation(m_DangoPos.x-SpoonDango.x, m_DangoPos.y, m_DangoPos.z-SpoonDango.z*15.0f);
	m_DangoMat = dangoRotY * dangoRotZ * m_DangoTrans;

	m_SpoonMat = m_RotY * m_RotZ * m_SpoonTrans;
}
