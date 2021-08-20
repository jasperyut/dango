#include "transwait.h"
#include"statelist.h"

C_Transwait::C_Transwait()
{
	m_partW.Load("Data/model/player/dango1.gltf");
	m_partG.Load("Data/model/player/dango3.gltf");
	m_partP.Load("Data/model/player/dango2.gltf");
	m_animeProgress = 0;
	valueflg = false;
	StateStore = 1;

}

C_Transwait::~C_Transwait()
{
	m_partW.Release();
	m_partG.Release();
	m_partP.Release();
}

void C_Transwait::Draw()
{
	SHADER.m_standardShader.SetWorldMatrix(W_mat);
	SHADER.m_standardShader.DrawModel(&m_partW);
	SHADER.m_standardShader.SetWorldMatrix(G_mat);
	SHADER.m_standardShader.DrawModel(&m_partG);
	SHADER.m_standardShader.SetWorldMatrix(P_mat);
	SHADER.m_standardShader.DrawModel(&m_partP);
}

void C_Transwait::Update()
{
	

	if (SYSTEM.Getplayframe() == true)
	{
		GameScene* game;
		game = dynamic_cast<GameScene*>(SYSTEM.GetSceneManager().GetnowScene());
		Math::Matrix RotMat, camMat;
		float ang;
		ang = game->GetplayerAng();
		RotMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(ang));
		camMat = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(game->GetAng()));
		Math::Vector3 Pp;
		Math::Vector3 Gp;
		

		

		//�ϊ��p�^�[���̑���
		//�p�^�[���`�F�b�N
		if (SYSTEM.GettransStep() == 0)
		{
			m_Pos = game->GetPos();
			Pp = game->GetFellow1()->GetPos();//�Z��P�̈ʒu
			Gp = game->GetFellow2()->GetPos();//�Z��Q�̈ʒu

			
			switch (StateStore)
			{
			case 1://���p�^�[���̏ꍇ
				Wstart_mat = DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
				Pstart_mat = DirectX::XMMatrixTranslation(Pp.x, Pp.y, Pp.z);
				Gstart_mat = DirectX::XMMatrixTranslation(Gp.x, Gp.y, Gp.z);
				break;
			case 2://���p�^�[���̏ꍇ
				Wstart_mat = DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
				Pstart_mat = DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
				Gstart_mat = DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
				break;
			case 3://��O�p�^�[���̏ꍇ
				Wstart_mat = DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
				Pstart_mat = DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
				Gstart_mat = DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
				break;
			default:
				break;
			}

			W_mat = RotMat * Wstart_mat;
			P_mat = RotMat * Pstart_mat;
			G_mat = RotMat * Gstart_mat;
			//���̃X�e�b�v�ɍs��
			SYSTEM.SettransStep(1);
		}

		//�ϊ��p�^�[���̑���
		//���ʃp�^�[����ϊ�����
		if (SYSTEM.GettransStep() == 1)
		{
			Math::Vector3 WVec, PVec, GVec;

			if (valueflg == false)
			{
				gravity = 0.5;
				WPos = Wstart_mat.Translation();
				PPos = Pstart_mat.Translation();
				GPos = Gstart_mat.Translation();

				switch (StateStore)
				{
				case 1://���p�^�[���̏ꍇ
					Wtmppos = Math::Vector3(WPos.x, WPos.y, WPos.z + 1.0f);
					Ptmppos = Math::Vector3(PPos.x, PPos.y, PPos.z);
					Gtmppos = Math::Vector3(GPos.x, GPos.y, GPos.z);
					break;
				case 2://���p�^�[���̏ꍇ
					Wtmppos = Math::Vector3(WPos.x, WPos.y, WPos.z + 2.0f);
					Ptmppos = Math::Vector3(PPos.x - 1.732f, PPos.y , PPos.z - 2.0f);
					Gtmppos = Math::Vector3(GPos.x + 1.732f, GPos.y, GPos.z - 2.0f);
					break;
				case 3://��O�p�^�[���̏ꍇ
					Wtmppos = Math::Vector3(WPos.x, WPos.y, WPos.z + 2.0f);
					Ptmppos = Math::Vector3(PPos.x - 1.732f, PPos.y, PPos.z - 2.0f);
					Gtmppos = Math::Vector3(GPos.x + 1.732f, GPos.y, GPos.z - 2.0f);
					break;
				default:
					break;
				}

				valueflg = true;
			}
			//�ϊ��r���ʒu�ƌ��ʒu�̃x�N�g��
			WVec = Wtmppos - WPos;
			PVec = Ptmppos - PPos;
			GVec = Gtmppos - GPos;

			float Wlen = WVec.Length();

			WVec.Normalize();
			PVec.Normalize();
			GVec.Normalize();
			WVec *= 0.2f;
			PVec *= 0.2f;
			GVec *= 0.2f;

			WPos += WVec;
			PPos += PVec;
			GPos += GVec;

			WPos.y += gravity;
			PPos.y += gravity;
			GPos.y += gravity;
			gravity -= 0.04f;

			if (Wlen <= 0.2f)
			{
				WPos = Wtmppos;
				PPos = Ptmppos;
				GPos = Gtmppos;
			}

			//�ϊ�����
			m_animeProgress += 0.04f;
			
			//�ϊ����悪����������
			if (m_animeProgress >= 1)
			{
				m_animeProgress = 0;
				valueflg = false;
				//���̃X�e�b�v�ɍs��
				SYSTEM.SettransStep(2);
			}
		}


		//�ϊ��p�^�[���̑�O��
		//�ŏI�̃p�^�[���ɕϊ�����
		if (SYSTEM.GettransStep() == 2)
		{
			Math::Vector3 WVec, PVec, GVec;

			if (valueflg == false)
			{
				gravity = 0.5;
				
				switch (SYSTEM.Getstate())
				{
				case 1://���͑��p�^�[���̏ꍇ
					Wtmppos = Math::Vector3(m_Pos.x, m_Pos.y, m_Pos.z);
					Ptmppos = Math::Vector3(m_Pos.x, m_Pos.y, m_Pos.z - 2.0f);
					Gtmppos = Math::Vector3(m_Pos.x, m_Pos.y, m_Pos.z - 4.0f);
					StateStore = 1;
					break;
				case 2://���͑��p�^�[���̏ꍇ
					Wtmppos = Math::Vector3(m_Pos.x, m_Pos.y, m_Pos.z);
					Ptmppos = Math::Vector3(m_Pos.x, m_Pos.y + 2.6f, m_Pos.z);
					Gtmppos = Math::Vector3(m_Pos.x, m_Pos.y + 1.3f, m_Pos.z);
					StateStore = 2;
					break;
				case 3://���͑�O�p�^�[���̏ꍇ
					Wtmppos = Math::Vector3(m_Pos.x, m_Pos.y, m_Pos.z);
					Ptmppos = Math::Vector3(m_Pos.x, m_Pos.y, m_Pos.z);
					Gtmppos = Math::Vector3(m_Pos.x, m_Pos.y, m_Pos.z);
					StateStore = 3;
					break;
				default:
					break;
				}

				valueflg = true;
			}

			//�ϊ������ʒu�ƕϊ��r���ʒu�̃x�N�g��
			WVec = Wtmppos - WPos;
			PVec = Ptmppos - PPos;
			GVec = Gtmppos - GPos;

			float Wlen = WVec.Length();
			float Plen = PVec.Length();
			float Glen = GVec.Length();

			WVec.Normalize();
			PVec.Normalize();
			GVec.Normalize();
			WVec *= 0.2f;
			PVec *= 0.2f;
			GVec *= 0.2f;
			//�ŏI�ʒu�Ɉړ�����
			WPos += WVec;
			PPos += PVec;
			GPos += GVec;

			PPos.y += gravity;
			GPos.y += gravity * 0.8f;
			WPos.y += gravity * 0.6f;
			gravity -= 0.03f;

			//��苗���ȓ��ɂȂ�ƍŏI�ʒu�ɕϊ�����
			WPos = (Wlen < 0.2f)? Wtmppos:WPos;
			PPos = (Plen < 0.2f)? Ptmppos:PPos;
			GPos = (Glen < 0.2f) ?Gtmppos:GPos;
			
			m_animeProgress += 0.04f;
			//�ϊ����抮��
			if (m_animeProgress >= 1)
			{
				m_animeProgress = 0;
				SYSTEM.SettransStep(0);
				SYSTEM.Setplayframe(false);
				valueflg = false;
			}
		}

		Math::Matrix W_trans;
		Math::Matrix P_trans;
		Math::Matrix G_trans;

		W_trans = DirectX::XMMatrixTranslation(WPos.x, WPos.y, WPos.z);
		P_trans = DirectX::XMMatrixTranslation(PPos.x, PPos.y, PPos.z);
		G_trans = DirectX::XMMatrixTranslation(GPos.x, GPos.y, GPos.z);
		//����
		W_mat = RotMat * W_trans;
		P_mat = RotMat * P_trans;
		G_mat = RotMat * G_trans;
	}
}

