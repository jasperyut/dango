#include "playermove1.h"
#include"statelist.h"
#include "../main.h"

C_playermove1::C_playermove1()
{
	m_partW.Load("Data/model/player/dango1.gltf");
	m_partG.Load("Data/model/player/dango3.gltf");
	m_partP.Load("Data/model/player/dango2.gltf");
	soundwait = 0;
	jumpSound = true;
	storeSound = false;
	release = 0.0f;
	scaleang = 0.0f;
	pressure = 1.0f;
	bounceXZ = 1.0f;
	bounceY = 1.0f;
}
C_playermove1::~C_playermove1()
{
	SYSTEM.Setjumping(false);
	m_partW.Release();
	m_partG.Release();
	m_partP.Release();
}
void C_playermove1::Draw(Math::Matrix& _mat)
{
	SHADER.m_standardShader.SetWorldMatrix(_mat);
	SHADER.m_standardShader.DrawModel(&m_partW);
	SHADER.m_standardShader.SetWorldMatrix(G_mat);
	SHADER.m_standardShader.DrawModel(&m_partG);
	SHADER.m_standardShader.SetWorldMatrix(P_mat);
	SHADER.m_standardShader.DrawModel(&m_partP);
}

void C_playermove1::Update(std::unique_ptr<BlockManager>& _blockManager, Math::Matrix& _mat, float& _ang)
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
	
	Math::Vector3 moveVec = {};
	Math::Matrix camMat;


	moveFlg = false;


	if (SYSTEM.Getplayframe() == false && SYSTEM.GetoverFlg() == false)
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

		
			//�X�y�[�X�L�[������
			if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				
				if (SYSTEM.Getjumping()== false)
				{
					jumpSound = false;
					pressure *= 0.99f;//���͂𗭂߂�

					if (pressure <= 0.5f)
					{
						pressure = 0.5f;
					}
					release = 1 - pressure;

					cur_pos = m_Pos;

					if (storeSound == false)
					{
						storeSound = true;
						SYSTEM.GetSoundManager().SetSound("Data/music/powerstore.wav");
					}
				}
			}
			else
			{
				
				storeSound = false;
				pressure = 1.0f;//���̈��͂ɖ߂�
				
				//�W�����v��Ԃ̔���
				if (release > 0)
				{
					SYSTEM.Setjumping(true);
				}

				if (jumpSound == false)
				{
					jumpSound = true;
					SYSTEM.GetSoundManager().SetSound("Data/music/jump.wav");
				}

			}

		


		Math::Vector3 tmp_pos;
		tmp_pos.y = m_Pos.y - cur_pos.y;
		float jumplen;
		jumplen = tmp_pos.Length();

		

		if (SYSTEM.Getjumping()==true)
		{
			m_Pos.y += release;
		}


	}
	//�����ړ��̐ݒ�----------------------------------
	float InertiaR = 0.3f;
	if (Inertia.x <= -InertiaR)
	{
		Inertia.x = -InertiaR;
	}
	if (Inertia.x >= InertiaR)
	{
		Inertia.x = InertiaR;
	}
	if (Inertia.z >= InertiaR)
	{
		Inertia.z = InertiaR;
	}
	if (Inertia.z <= -InertiaR)
	{
		Inertia.z = -InertiaR;
	}
	if (InertiaFlg == true)
	{
		Inertia -= moveVec * 0.1f;
	}
	else
	{
		Inertia -= Inertia / 10;
	}
	//----------------------------------------------

	gravity -= 0.01f;
	m_Pos.y += gravity;
	//�n�ʂɂ߂荞�܂Ȃ��ݒ�
	if (m_Pos.y <= 0)
	{
		gravity = 0;
		m_Pos.y = 0;
	}

	Math::Vector3 DownRayVec;
	Math::Vector3 returnDownVec;
	DownRayVec = Math::Vector3{ 0.0f,-1.0f,0.0f };
	DownRayVec *= 0.1f;
	//�u���b�N�ɂ�������̏���
	if ((_blockManager->CheckHit(m_Pos, DownRayVec, m_hitDis, returnDownVec, range)))
	{
		m_Pos.y += returnDownVec.y;
		gravity = 0;

	}
	
	//�W�����v���
	if (SYSTEM.Getjumping() == true)
	{
		//�u���b�N�̏�ɂ�������̏���
		if ((_blockManager->CheckHit(m_Pos, DownRayVec, m_hitDis, returnDownVec, range)) || m_Pos.y <= 0)
		{
			//�㔽������
			release -= release * 0.8f;
			if (release <= 0.02)
			{
				SYSTEM.Setjumping(false);
				release = 0;
			}
			SYSTEM.GetSoundManager().SetSound("Data/music/ground.wav");
		}
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
	if (moveFlg && SYSTEM.Getjumping() == false)
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
		InertiaFlg = true;

		if (soundwait == 0 && SYSTEM.Getjumping() == false)
		{
			SYSTEM.GetSoundManager().SetSound("Data/music/walking.wav");
			soundwait = 30;
		}

		//m_pos = GAME.GetMat().Translation();
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
			if (ang >= 40.0f)
			{
				ang = 40.0f;
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
		//�ړ��ʂ𐳋K��
		moveVec.Normalize();
		moveVec *= 0.4f;

		m_Pos += moveVec;
		Math::Vector3 returnVec;

		//�X�e�[�W�̃A�C�e���ɓ���������,�͈͊O�ɓ���������
		if ((_blockManager->CheckHit(m_Pos, moveVec, m_hitDis, returnVec, range)) || game->GetShell()->CheckHit(m_Pos, moveVec, m_hitDis, returnVec, range))
		{
			m_Pos += returnVec;
			InertiaFlg = false;
		}
	}
	else
	{
		InertiaFlg = false;
	}

	soundwait--;
	if (soundwait <= 0)
	{
		soundwait = 0;
	}

	m_Scale = DirectX::XMMatrixScaling(bounceXZ, bounceY + (pressure - 1.0f), bounceXZ);
	m_Trans = DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y-(1.0-pressure), m_Pos.z);
	m_Rot = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_ang));

	//����
	_mat = m_Scale * m_Rot * m_Trans;
	_ang = m_ang;
	G_mat = m_Scale * m_Rot * DirectX::XMMatrixTranslation(m_Pos.x + Inertia.x / 2, m_Pos.y - (1.8f - pressure*2 - bounceY) + Inertia.y / 2, m_Pos.z + Inertia.z / 2);
	P_mat = m_Scale * m_Rot * DirectX::XMMatrixTranslation(m_Pos.x + Inertia.x, m_Pos.y - (1.8f - pressure*1.5 - bounceY*1.5) * 2 + Inertia.y, m_Pos.z + Inertia.z);
}



