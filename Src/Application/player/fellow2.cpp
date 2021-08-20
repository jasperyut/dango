#include "fellow2.h"
#include"statelist.h"


C_Fellow2::C_Fellow2()
{
	m_Dango.Load("Data/model/player/dango3.gltf");
	m_Trans = DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z - 4.0f);
	m_Mat = m_Trans;
	scaleang = 0;
	bounceXZ = 1.0f;
	bounceY = 1.0f;
	bounceflg = false;
	soundwait = 0;
}

C_Fellow2::~C_Fellow2()
{
	m_Dango.Release();
}

void C_Fellow2::Draw()
{

	SHADER.m_standardShader.SetWorldMatrix(m_Mat);
	SHADER.m_standardShader.DrawModel(&m_Dango);

}

void C_Fellow2::Update(Math::Vector3 _pos, std::unique_ptr<BlockManager>& _blockManager)
{
	GameScene* game;
	game = dynamic_cast<GameScene*>(SYSTEM.GetSceneManager().GetnowScene());

	if (SYSTEM.Getcolormode() == 1)
	{
		m_Pos = game->GetPos();

		Math::Vector3 mainPos;
		mainPos = _pos;
		//↑目標のワールド座標

		Math::Matrix invMat;
		invMat = DirectX::XMMatrixInverse(nullptr, m_Trans);
		//逆行列を作る関数

		//invMat==ミサイルの座標分、マイナス移動する、
		//		　ミサイルの角度分、マイナス回転する

		Math::Vector3 targetPos;
		targetPos = DirectX::XMVector3TransformCoord(mainPos, invMat);
		//目標のワールド座標を
		//自身のローカル軸で見たロカール座標（targetPos）に変換する

		Math::Vector3 frontVec(0, 0, 1);

		Math::Vector3 rotAxis;
		rotAxis = DirectX::XMVector3Cross(frontVec, targetPos);
		rotAxis.x = 0.0f;
		rotAxis.z = 0.0f;
		//自身の前方方向と自身から見た目標方向の2本のベクトルから
		//外積を求める


		if (rotAxis != Math::Vector3::Zero && fabs(targetPos.y) <= 2.0)
		{
			targetPos.Normalize();
			Math::Vector3 Dot;
			Dot = DirectX::XMVector3Dot(frontVec, targetPos);

			float ang;
			ang = DirectX::XMConvertToDegrees(acos(Dot.x));
			if (ang > 20)ang = 20;

			m_Rot = DirectX::XMMatrixRotationAxis(rotAxis, DirectX::XMConvertToRadians(ang));
			//指定した軸で回転する行列を作る
			m_Trans = m_Rot * m_Trans;
		}
		//団子のBOINGBOING設定
		//------------------------------------------------------------------------------
		if (bounceflg)
		{
			scaleang += 10;

			bounceXZ = 1.0f + (sin(DirectX::XMConvertToRadians(scaleang)) * 0.2f);
			bounceY = 1.0f + (cos(DirectX::XMConvertToRadians(scaleang)) * 0.2f);
		}
		else
		{
			bounceXZ = 1.0f;
			bounceY = 1.0f;
		}
		//------------------------------------------------------------------------------

		m_Move = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.5f);

		Math::Vector3 leng;
		_pos.y = m_Trans.Translation().y;
		leng = _pos - m_Trans.Translation();
		if (leng.Length() < 4.0f)
		{
			m_Move = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.2f);
			bounceflg = true;

		}
		if (leng.Length() < 3.0f)
		{
			m_Move = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
			bounceflg = false;

		}

		//重力
		gravity -= 0.05f;
		m_Trans._42 += gravity;
		if (m_Trans._42 <= 0)
		{
			gravity = 0;
			m_Trans._42 = 0;
		}

		Math::Vector3 DownRayVec;
		Math::Vector3 returnDownVec;
		DownRayVec = Math::Vector3{ 0,-1,0 };
		//地面にあったらの処理
		if (_blockManager->CheckHit(m_Trans.Translation(), DownRayVec, m_hitDis, returnDownVec, range))
		{
			m_Trans._42 += returnDownVec.y;
			gravity = 0;
		}
		Math::Vector3 returnVec;
		if (_blockManager->CheckHit(m_Trans.Translation(), frontVec, m_hitDis, returnVec, range) || game->GetShell()->CheckHit(m_Trans.Translation(), frontVec, m_hitDis, returnVec, range))
		{
			m_Trans._41 += returnVec.x;
			m_Trans._43 += returnVec.z;
		}

		//仲間と当たったらバックする
		//------------------------------------------------------------------------
		Math::Vector3 vlen;
		float len;
		Math::Vector3 pPos, rPos, kPos;
		pPos = m_Mat.Translation();
		pPos.y = 0;
		rPos = game->GetFellow1()->GetPos();//仲間の位置
		rPos.y = 0;
		vlen = rPos - pPos;
		len = vlen.Length();

		//一定距離以下になったら
		if (len < (1.0f + range))
		{
			float pushlen;
			pushlen = (1.0f + range) - len;

			vlen.Normalize();
			vlen *= pushlen;
			vlen.y = 0.0f;

			m_Pos = m_Mat.Translation() - vlen;
			m_Trans = DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
		}
		//------------------------------------------------------------------------
		m_Trans = m_Move * m_Trans;

		m_Scale = DirectX::XMMatrixScaling(bounceXZ, bounceY, bounceXZ);

		//合成
		if (SYSTEM.Getplayframe() == true)
		{
			m_Trans = DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z - 4.0f);
		}
		else
		{
			m_Mat = m_Scale * m_Trans;
		}
	}

	//--------------------------------------------------------------------
	//緑の移動モード
	//第三ステージに使うだけ

	float ang;
	ang = game->GetAng();

	if (SYSTEM.Getplayframe() == true)
	{
		m_Pos = game->GetPos();
		m_ang = game->GetplayerAng();
	}
	moveFlg = false;

	if (SYSTEM.Getplayframe() == false)
	{

		if (SYSTEM.Getcolormode() == 3&& SYSTEM.GetbuttonCam() == true)
		{
			m_Pos = game->GetPos();

			if (GetAsyncKeyState('W') & 0x8000)
			{
				camMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(ang));
				moveVec = DirectX::XMVector3TransformNormal(Math::Vector3(0, 0, 1), camMat);

				moveFlg = true;
			}

			if (GetAsyncKeyState('S') & 0x8000)
			{
				camMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(ang));
				moveVec = DirectX::XMVector3TransformNormal(Math::Vector3(0, 0, -1), camMat);

				moveFlg = true;
			}

			if (GetAsyncKeyState('A') & 0x8000)
			{
				camMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(ang));
				moveVec = DirectX::XMVector3TransformNormal(Math::Vector3(-1, 0, 0), camMat);

				moveFlg = true;
			}

			if (GetAsyncKeyState('D') & 0x8000)
			{
				camMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(ang));
				moveVec = DirectX::XMVector3TransformNormal(Math::Vector3(1, 0, 0), camMat);

				moveFlg = true;
			}
		}

		//--------------------------------------------------------------------



		gravity -= 0.01f;
		m_Pos.y += gravity;
		if (m_Pos.y <= 0)
		{
			gravity = 0;
			m_Pos.y = 0;
		}
		Math::Vector3 DownRayVec;
		Math::Vector3 returnDownVec;
		DownRayVec = Math::Vector3{ 0,-1,0 };
		//地面にあったらの処理
		if (_blockManager->CheckHit(m_Pos, DownRayVec, m_hitDis, returnDownVec, range))
		{
			m_Pos.y += returnDownVec.y;
			gravity = 0;
		}

		//団子のBOINGBOING設定
		//------------------------------------------------------------------------------
		if (moveFlg)
		{
			scaleang += 10;

			bounceXZ = 1.0f + (sin(DirectX::XMConvertToRadians(scaleang)) * 0.2f);
			bounceY = 1.0f + (cos(DirectX::XMConvertToRadians(scaleang)) * 0.2f);
		}
		else
		{
			bounceXZ = 1.0f;
			bounceY = 1.0f;
		}
		//------------------------------------------------------------------------------

		if (moveFlg == true)
		{
			if (soundwait == 0)
			{
				SYSTEM.GetSoundManager().SetSound("Data/music/walking.wav");
				soundwait = 30;
			}
			Math::Matrix tmpMat;


			//今向いている方向
			Math::Vector3 nowVec;
			tmpMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_ang));
			nowVec = DirectX::XMVector3TransformNormal(Math::Vector3(0, 0, 1), tmpMat);
			nowVec.Normalize();

			//向きたい方向
			Math::Vector3 toVec;
			toVec = moveVec;
			toVec.Normalize();
			//内積
			Math::Vector3 dot;
			dot = DirectX::XMVector3Dot(nowVec, toVec);
			if (dot.x >= 1.0f)dot.x = 1.0f;
			if (dot.x <= -1.0f)dot.x = -1.0f;

			float ang;
			ang = DirectX::XMConvertToDegrees(acos(dot.x));

			//角度があったときだけ回転
			if (ang > 0.0f)
			{
				if (ang >= 20)
				{
					ang = 20.0f;
				}
				Math::Vector3 cross;
				cross = DirectX::XMVector3Cross(nowVec, toVec);
				cross.Normalize();

				if (cross.y > 0.5f)
				{
					m_ang += ang;
				}
				else
				{
					m_ang -= ang;
				}
			}


			Math::Vector3 returnVec;
			//移動量を正規化
			moveVec.Normalize();
			moveVec *= 0.2f;
			m_Pos += moveVec;
			//ステージのアイテムと範囲外に当たったら
			if (_blockManager->CheckHit(m_Pos, nowVec, m_hitDis, returnVec, range) || game->GetShell()->CheckHit(m_Pos, nowVec, m_hitDis, returnVec, range))
			{
				m_Pos += returnVec;
			}

			m_Trans = DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
			m_Rot = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_ang));
			m_Scale = DirectX::XMMatrixScaling(bounceXZ, bounceY, bounceXZ);
			//合成
			m_Mat = m_Scale * m_Rot * m_Trans;

		}

		soundwait--;
		if (soundwait <= 0)
		{
			soundwait = 0;
		}
	}

}
