#include "player.h"
#include"statelist.h"





C_playermove0::C_playermove0()
{
	m_Dango.Load("Data/model/player/dango1.gltf");

	m_camAngY = 0;
	m_camAngX = 0;
	soundwait = 0;
	scaleang = 0;
	bounceXZ = 1.0f;
	bounceY = 1.0f;
}

C_playermove0::~C_playermove0()
{
	m_Dango.Release();
}

void C_playermove0::Draw(Math::Matrix& _mat)
{
	SHADER.m_standardShader.SetWorldMatrix(_mat);
	SHADER.m_standardShader.DrawModel(&m_Dango);
}

void C_playermove0::Update(std::unique_ptr<BlockManager>& _blockManager, Math::Matrix& _mat, float& _ang)
{
	GameScene* game;
	game = dynamic_cast<GameScene*>(SYSTEM.GetSceneManager().GetnowScene());
	float ang;
	ang = game->GetAng();

	//�ϊ����[�h��
	if (SYSTEM.Getplayframe() == true)
	{
		//�O�̃p�^�[���̈ʒu�Ɗp�x��������
		m_Pos = game->GetPos();
		m_ang = game->GetplayerAng();
	}
	moveFlg = false;
	//��ʃ��[�h
	if (SYSTEM.Getplayframe() == false && SYSTEM.GetoverFlg() == false)
	{
		if (SYSTEM.Getcolormode() == 1)
		{
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
	}

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
	//�u���b�N�̏�ɂ�������̏���
	if (_blockManager->CheckHit(m_Pos, DownRayVec, m_hitDis, returnDownVec, range))
	{
		m_Pos.y += returnDownVec.y;
		gravity = 0;
	}

	//���ʂɓ�������Q�[���I�[�o�[
	if (game->Getwater()->CheckHit(m_Pos, DownRayVec, m_hitDis, range))
	{
	}

	//�Q�[���I�[�o�[�̎��A����ł���
	if (SYSTEM.GetoverFlg() == true)
	{
		m_Pos.y += -0.05f;
		gravity = 0;
	}

	//�c�q��BOINGBOING�ݒ�
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
		//�������Ă������
		Math::Vector3 nowVec;
		tmpMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_ang));
		nowVec = DirectX::XMVector3TransformNormal(Math::Vector3(0, 0, 1), tmpMat);
		nowVec.Normalize();

		//������������
		Math::Vector3 toVec;
		toVec = moveVec;
		toVec.Normalize();
		//����
		Math::Vector3 dot;
		dot = DirectX::XMVector3Dot(nowVec, toVec);
		if (dot.x >= 1.0f)dot.x = 1.0f;
		if (dot.x <= -1.0f)dot.x = -1.0f;

		float ang;
		ang = DirectX::XMConvertToDegrees(acos(dot.x));

		//�p�x���������Ƃ�������]
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
		//�ړ��ʂ𐳋K��
		moveVec.Normalize();
		moveVec *= 0.2f;
		m_Pos += moveVec;

		//�X�e�[�W�̃A�C�e���Ɣ͈͊O�ɓ���������
		if (_blockManager->CheckHit(m_Pos, nowVec, m_hitDis, returnVec, range) || game->GetShell()->CheckHit(m_Pos, nowVec, m_hitDis, returnVec, range))
		{
			m_Pos += returnVec;
		}
	}

	

	m_Trans = DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
	m_Rot = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_ang));
	m_Scale = DirectX::XMMatrixScaling(bounceXZ, bounceY, bounceXZ);
	//����
	_mat = m_Scale * m_Rot * m_Trans;
	_ang = m_ang;

	soundwait--;
	if (soundwait <= 0)
	{
		soundwait = 0;
	}
}

