#define _CRTDBG_MAP_ALLOC
#include "main.h"
#include "define.h"
#include"SceneManager.h"
#include"TitelScene.h"
#include"Game.h"
#include"ClearScene.h"
#include"GameOverScene.h"
#include"System/KeySystem.h"
#include"ModelIntersects.h"

GameScene::GameScene()
{
	Init();
}
GameScene::~GameScene()
{
	Release();
}

//=============================================================================================================================================

//�J�����ݒ�
void GameScene::SetCamera()
{
	//�J�����̈ړ��ݒ�
	//-----------------------------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------�M�~�b�N������J�����̈ړ�����ꍇ
	if (SYSTEM.Getstagecam() == true)
	{
		//���X�e�[�W�̃J����
		if (SYSTEM.GetnowStage() == 1)
		{
			//�J�����ŏ��̈ʒu
			if (cameraProgress == 0)
			{
				camLook = m_StatePos;
			}
			cameraProgress += 0.01f;//�J���������̎��Ԑ�
			if (cameraProgress > 0.0f && cameraProgress <= 1.0f)
			{
				camPos.z -= 0.1f;
				camLook.x -= 0.2f;
				camLook.y += 0.3f;
			}
			if (cameraProgress > 1.0f && cameraProgress <= 2.0f)
			{
				camLook.y -= 0.3f;
			}
			if (cameraProgress > 2.0f&& cameraProgress <= 2.5f)
			{
				//�J�������ڗp����
			}
			if (cameraProgress >= 2.5f)
			{
				cameraProgress = 2.5f;
				SYSTEM.Setstagecam(false);
			}
		}

		//���X�e�[�W�̃J����
		if (SYSTEM.GetnowStage() == 2)
		{
			//�J�����ŏ��̈ʒu
			if (cameraProgress == 0)
			{
				camPos = Math::Vector3(-40, 0, 20);
				camLook = Math::Vector3(-10, 10, 20);
			}
			cameraProgress += 0.01f;//�J���������̎��Ԑ�
			//�ŏ��̈ړ�
			if (cameraProgress > 0.0f && cameraProgress <= 0.5f)
			{
				camPos.y += 0.5f;
				camPos.x += 0.1f;
				camLook.x += 0.5f;
			}
			//���̈ړ�
			if (cameraProgress > 0.5f && cameraProgress <= 1.5f)
			{
				camPos.y += 0.1f;
				camPos.x += 0.4f;
				camLook.x -= 0.1f;
				camLook.z += 0.3f;
			}
			//�Ō�̈ړ�
			if (cameraProgress > 1.5f && cameraProgress <= 3.0f)
			{
				camPos.x -= 0.1f;
				camPos.z += 0.1f;
				camLook.x -= 0.2f;
				camLook.z += 0.2f;
			}

			if (cameraProgress >= 3.0f)
			{
				cameraProgress = 3.0f;
				SYSTEM.Setstagecam(false);
			}

			camHead = Math::Vector3(0, 1, 0);

		}
		//��O�X�e�[�W�̃J����
		if (SYSTEM.GetnowStage() == 3)
		{
			if (cameraProgress == 0)
			{
				camLook = m_BBQcam;
			}

			if (cameraProgress > 0.0f && cameraProgress <= 2.0f)
			{
				camPos.x -= 0.05f;
				camPos.y += 0.05f;
				camPos.z -= 0.08f;
				camLook += {0.1f, 0.05f, -0.05f};
			}
			if (cameraProgress > 2.0f && cameraProgress <= 4.0f)
			{
				Math::Vector3 GreenToWhiteLook,GreenToWhitePos;
				GreenToWhiteLook = m_PlayerManager->Getmat().Translation() - camLook;
				
				Math::Matrix tmpRotY, tmpRotX, tmpRot;
				Math::Vector3 tmpCamPos;

				tmpRotY = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_camAngY));
				tmpRotX = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_camAngX));
				tmpRot = tmpRotX * tmpRotY;

				tmpCamPos = DirectX::XMVector3TransformNormal(Math::Vector3(0, 5, camZ), tmpRot);
				tmpCamPos += m_PlayerManager->Getmat().Translation();
				GreenToWhitePos = tmpCamPos - camPos;

				camPos += GreenToWhitePos * 0.025f;
				camLook += GreenToWhiteLook * 0.025f;

			}

			cameraProgress += 0.01f;//�J���������̎��Ԑ�

			camHead = Math::Vector3(0, 1, 0);

			if (cameraProgress >= 4.0f)
			{
				cameraProgress = 4.0f;
				SYSTEM.Setstagecam(false);
				SYSTEM.Setcolormode(1);//�����c�q�ɖ߂�
			}
		}
	//-------------------------------------------------------------�M�~�b�N������J�����̈ړ�����ꍇ

	}
	else
	{
		if (intro == true)
		{
			camPos = m_Goalpin->GetMat().Translation() + Math::Vector3(0, 10, -10);

			camPos += m_GPcamPos;
			m_GoalPos = m_Goalpin->GetMat().Translation();
			camLook = m_GoalPos;
			camLook += m_GPcamLook;

			camHead = Math::Vector3(0, 1, 0);

			//�X�e�[�W�ŏ��J�����̓����ݒ�
			Math::Vector3 PcamPos;//�v���C���J�����̈ʒu
			PcamPos = Math::Vector3(0, 5, camZ);
			Math::Vector3 GPCamVec;//�S�[���J��������v���C���J�����܂ł̃x�N�g��
			GPCamVec = PcamPos - camPos;
			float GPCamlen;
			GPCamlen = GPCamVec.Length();
			GPCamVec.Normalize();
			float sang = 0.0f;
			sang += 15;
			if (sang >= 90)
			{
				sang = 90;
			}
			GPCamVec.y *= sin(DirectX::XMConvertToRadians(sang));
			float movespeed;
			movespeed = 0.5f;
			if (GPCamlen <= 20.0f)
			{
				movespeed *= 0.5f;
			}
			if (GPCamlen <= 0.025f)
			{
				movespeed = 0.0f;
				startalpha += 0.05f;
				if (startalpha >= 1.0f)
				{
					startalpha = 1.0f;
				}
				startwait--;
				if (startwait <= 0)
				{
					startwait = 0;
					intro = false;
				}
				if (startFlg == false)
				{
					startFlg = true;
					SYSTEM.GetSoundManager().SetSound("Data/music/startgame.wav");
				}
			}

			Math::Vector3 camLookmove;
			float len;
			camLookmove = m_StatePos - camLook;
			len = camLookmove.Length();
			camLookmove.Normalize();
			if (len >= 0.1f)
			{
				m_GPcamLook += camLookmove * movespeed * 0.8f;

			}

			m_GPcamPos += GPCamVec * movespeed;
		}
		else
		{
			Math::Matrix tmpRotY, tmpRotX, tmpRot;

			tmpRotY = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_camAngY));
			tmpRotX = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_camAngX));
			tmpRot = tmpRotX * tmpRotY;

			camPos = DirectX::XMVector3TransformNormal(Math::Vector3(0, 5, camZ), tmpRot);

			camPos += m_StatePos;
			camLook = m_StatePos;
			camHead = Math::Vector3(0, 1, 0);
			if (camPos.y <= 0)
			{
				camPos.y = 0;
			}
			Math::Vector3 cam_Vec;
			float camlen = 0;
			float hitdis;
			Math::Vector3 returnVec;
			float range = 1.0f;

			cam_Vec = camPos - camLook;
			camlen = cam_Vec.Length();
			cam_Vec.Normalize();

			//�J�����̓����蔻��/////////////////////////////////////////////////////////////////////////////

			//���̂ɓ���������J�����̃x�N�g��������i���ߔ���p�j
			m_CameraVec = (m_BlockManager->CheckHit(camLook, cam_Vec, hitdis, returnVec, camlen)) ? cam_Vec : Math::Vector3::Zero;
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------


	SHADER.m_cb7_Camera.Work().mV = DirectX::XMMatrixLookAtLH(
		camPos,	// �J�����̍��W
		camLook, // �J�����̒����_
		camHead);	// �J�����̓��̕���
	SHADER.m_cb7_Camera.Work().CamPos = SHADER.m_cb7_Camera.Work().mV.Invert().Translation();

	//�ˉe�s��
	SHADER.m_cb7_Camera.Work().mP = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60), (float)ScrW / (float)ScrH, 0.01f, 1000.0f);

	//�r���[�s��E�ˉe�s���GPU�ɓ]��
	SHADER.m_cb7_Camera.Write();

}

//=============================================================================================================================================

//���쏈��
void GameScene::Update()
{

	//�ڕW�Љ�̃J�������쓮���Ă��鎞�A�}�E�X�̍��W���ς��Ȃ��悤�ɂ���
	if (intro == true)
	{
		SetCursorPos(m_basept.x, m_basept.y);
	}


	//�ڕW�Љ�̃J�������쓮���Ă��Ȃ��ꍇ
	if (intro == false)
	{
		//�}�E�X�ŃJ��������]����ݒ�
		POINT pt;
		GetCursorPos(&pt);
		if (APP.m_window.GetWndHandle() == GetActiveWindow())
		{
			m_camAngY += (pt.x - m_basept.x) / 4.0f;
			m_camAngX += (pt.y - m_basept.y) / 4.0f;
			if (m_camAngX > 30)
			{
				m_camAngX = 30;
			}
			if (m_camAngX < -30)
			{
				m_camAngX = -30;
			}

			//�������̊p�x�ɔ��f���I������}�E�X���W������W�ɖ߂�
			SetCursorPos(m_basept.x, m_basept.y);
		}
		//3D�A�C�e��
		m_BlockManager->Update();
		//�v���C��
		m_PlayerManager->Update(m_BlockManager);
		//�v���C���̉�]���
		m_Rot = m_PlayerManager->Getrot();
		//�v���C���̊p�x���
		playerAng = m_PlayerManager->Getang();
		m_TransWait->Update();

		//���X�e�[�W�̏ꍇ
		if (SYSTEM.GetnowStage() == 1)
		{
			//�ʂ̃{�^��
			m_Canbt->Update();
		}

		//���X�e�[�W�̏ꍇ
		if (SYSTEM.GetnowStage() == 2)
		{
			//���ʂ̏���
			m_Water->Update();
		}


		//��O�X�e�[�W�c�q�̐ؑ�
		//-------------------------------------------------------------------------------------�c�q1�p�^�[���̐؂�ւ�
		Math::Matrix tmpMat;
		//�����c�q�̏o��
		if (SYSTEM.Getcolormode() == 1)
		{
			tmpMat = m_PlayerManager->Getmat();
			m_Mat = tmpMat;
			m_StatePos = tmpMat.Translation();
		}

		//�s���N�c�q�̏o�ԁi��O�X�e�[�W�̂݁j
		if (SYSTEM.Getcolormode() == 2)
		{
			m_Mat = m_Fellow1->Getmat();
			float tmplen;
			Math::Vector3 tmpVec;
			tmpVec = m_Mat.Translation() - m_StatePos;
			tmplen = tmpVec.Length();
			tmpVec.Normalize();

			if (m_StatePos != m_Mat.Translation())
			{
				SYSTEM.SetbuttonCam(false);
			}

			switch (SYSTEM.GetbuttonCam())
			{
			case false:
				m_StatePos += tmpVec * 0.3f;
				if (tmplen <= 0.3)
				{
					SYSTEM.SetbuttonCam(true);
					m_StatePos = m_Mat.Translation();
				}
				break;
			case true:
				m_StatePos = m_Mat.Translation();
				break;
			}

		}

		//�Βc�q�̏o�ԁi��O�X�e�[�W�̂݁j
		if (SYSTEM.Getcolormode() == 3)
		{
			m_Mat = m_Fellow2->Getmat();
			float tmplen;
			Math::Vector3 tmpVec;
			tmpVec = m_Mat.Translation() - m_StatePos;
			tmplen = tmpVec.Length();
			tmpVec.Normalize();
			if (m_StatePos != m_Mat.Translation())
			{
				SYSTEM.SetbuttonCam(false);
			}

			switch (SYSTEM.GetbuttonCam())
			{
			case false:
				m_StatePos += tmpVec * 0.3f;
				if (tmplen <= 0.3)
				{
					SYSTEM.SetbuttonCam(true);
					m_StatePos = m_Mat.Translation();
				}
				break;
			case true:
				m_StatePos = m_Mat.Translation();
				
				break;
			}

			m_BBQcam = m_StatePos;//�Βc�q�̈ʒu������
		}
		//-------------------------------------------------------------------------------------�c�q1�p�^�[���̐؂�ւ�

		//���p�^�[�������Ă���c�q����
		if (SYSTEM.Getstagecam() == false)
		{
			m_Fellow1->Update(m_StatePos, m_BlockManager);
			m_Fellow2->Update(m_Fellow1->GetPos(), m_BlockManager);
		}

		//��O�X�e�[�W�̏ꍇ�̏���
		if (SYSTEM.GetnowStage() == 3)
		{
			for (UINT i = 0; i < m_Coal.size(); i++)
			{
				//�Y
				m_Coal[i]->Update();
			}

			//��O�X�e�[�W�@�ւ��N�������ꍇ
			if (SYSTEM.GetHotState() == true)
			{
				m_Smoke.push_back(new C_Smoke(Math::Vector3(rand() % 11 - 5.0f, 10.0f, rand() % 46 + 25.0f)));

				for (UINT i = 0; i < m_Smoke.size(); i++)
				{
					m_Smoke[i]->Update();
				}
				//��O�X�e�[�W�̉��������ݒ�
				for (UINT i = 0; i < m_Smoke.size(); i++)
				{
					if (m_Smoke[i]->Update() == false)
					{
						delete m_Smoke[i];
						m_Smoke.erase(m_Smoke.begin() + i);
						i--;
					}
				}
			}
		}

		//�ڕW�Љ�J�����쓮����
		if (startwait <= 0)
		{
			//�X�^�[�g2D�����̐ݒ�
			startalpha -= 0.02f;
			if (startalpha <= 0.0f)
			{
				startalpha = 0.0f;
			}
			startgame_mat *= DirectX::XMMatrixScaling(1.02f, 1.02f, 1.02f);
		}

		//�S�[���ɒ�������̏���
		if ((m_Mat.Translation() - m_Goalpin->GetMat().Translation()).Length() < m_Goalpin->GetRange())
		{
			SYSTEM.GetSoundManager().SetSound("Data/music/warp.wav");
			
			SYSTEM.GetSceneManager().ChangeScene(new Clearscene);
			ShowCursor(TRUE);
			SYSTEM.SetnowStage(0);
		}

		//�Q�[���I�[�o�[�ɂȂ�����A�J�E���g�_�E�����āA�I�[�o�[�V�[���ɓ���
		if (SYSTEM.GetoverFlg() == true)
		{
			overCountDown--;
			if (overCountDown <= 0.0f)
			{
				SYSTEM.GetSceneManager().ChangeScene(new GameOver);
				ShowCursor(TRUE);
			}
		}
	}
}

//=============================================================================================================================================

//�`�揈��
void GameScene::Draw()
{
	//�����_���Ŋ֐����쐬
	auto drawCharacters = [this]()
	{
		SHADER.m_standardShader.SetToDevice();
		//�w�i
		m_Background->Draw();
		//�w�i�̏���
		m_Backitem->Draw();

		SHADER.m_effectShader.SetToDevice();
		//�n��
		m_Ground->Draw();

		//��O�X�e�[�W�����ʂ��ĂȂ�
		if (SYSTEM.GetnowStage() == 3)
		{
			for (UINT i = 0; i < m_Coal.size(); i++)
			{
				m_Coal[i]->Draw();
			}
		}

		SHADER.m_standardShader.SetToDevice();
		if (m_BlockManager != nullptr)
		{
			//3D�A�C�e��
			m_BlockManager->Draw();
		}
	};

	//=====================================
	// IBL�摜�����`��
	//=====================================
	if (m_cubeMapGen.GetCubeMap() == nullptr)
	{
		//100�ԖڃX���b�g�̃e�N�X�`��������
		ID3D11ShaderResourceView* nullSRV = nullptr;
		D3D.GetDevContext()->PSSetShaderResources(
			100,	//�Z�b�g����X���b�g�ԍ�
			1,		//�Z�b�g���鐔
			&nullSRV
		);
		//�L���[�u�}�b�v�����`��

		m_cubeMapGen.Generate(512, m_StatePos, drawCharacters);

		//�쐬�����L���[�u�}�b�v���A�V�F�[�_�[�ɓn��
		D3D.GetDevContext()->PSSetShaderResources(
			100,	//�Z�b�g����X���b�g�ԍ�
			1,		//�Z�b�g���鐔
			m_cubeMapGen.GetCubeMap()->GetSRViewAddress()
		);
	}

	//�S���̂̕`��
	drawCharacters();

	//�p�^�[���ϊ��r������Ȃ��ꍇ
	if (SYSTEM.Getplayframe() == false)
	{
		if (m_PlayerManager != nullptr)
		{
			m_PlayerManager->Draw();
		}
		//���p�^�[��
		if (SYSTEM.Getstate() == 1)
		{
			m_Fellow1->Draw();
			m_Fellow2->Draw();
		}
	}
	else//�p�^�[���ϊ��r��
	{
		//�r���ϊ����f��
		m_TransWait->Draw();
	}

	//�S�[��
	m_Goalpin->Draw();
	//���X�e�[�W�̏ꍇ
	if (SYSTEM.GetnowStage() == 1)
	{
		//�ʂ̃{�^��
		m_Canbt->Draw();
	}
	//���X�e�[�W�̏ꍇ
	if (SYSTEM.GetnowStage() == 2)
	{
		//����
		m_Water->Draw();
	}

	if (SYSTEM.GetHotState() == true)
	{
		D3D.GetDevContext()->OMSetBlendState(blendAdd, Math::Color(0, 0, 0, 0), 0xFFFFFFFF);
		if (SYSTEM.GetnowStage() == 3)
		{
			SHADER.m_effectShader.SetToDevice();
			for (UINT i = 0; i < m_Smoke.size(); i++)
			{
				//��
				m_Smoke[i]->Draw();
			}
		}
		D3D.GetDevContext()->OMSetBlendState(blendAlpha, Math::Color(0, 0, 0, 1), 0xFFFFFFFF);

	}

	SHADER.m_spriteShader.Begin();

	if (SYSTEM.GetoverFlg() == false)
	{

		SHADER.m_spriteShader.SetMatrix(startgame_mat);
		SHADER.m_spriteShader.DrawTex(&m_Startgame, Math::Rectangle(0, 0, 940, 300), startalpha);


		if (intro == false&&SYSTEM.GetnowStage()!=0)
		{
			SHADER.m_spriteShader.SetMatrix(clock_mat);
			SHADER.m_spriteShader.DrawTex(&m_Clock, Math::Rectangle(0, 0, 108, 108), 1.0f);
			m_Number->Draw();
			m_Icon->Draw(SYSTEM.Getstate());

			if (SYSTEM.Getstate() == 2)
			{
				SHADER.m_spriteShader.SetMatrix(presssp_mat);
				SHADER.m_spriteShader.DrawTex(&m_PressSpace, Math::Rectangle(0, 0, 320, 90), 1.0f);
			}
		}
	}
	SHADER.m_spriteShader.End();


}

//=============================================================================================================================================

//����������
void GameScene::Init()
{

	srand(timeGetTime());

	m_basept = { ScrW / 2,ScrH / 2 };

	ClientToScreen(APP.m_window.GetWndHandle(), &m_basept);
	SetCursorPos(m_basept.x, m_basept.y);
	ShowCursor(FALSE);


	// ���s���C�g�ݒ�
	SHADER.m_cb8_Light.Work().DL_Dir = { 1,-1,0 };
	SHADER.m_cb8_Light.Work().DL_Dir.Normalize();
	SHADER.m_cb8_Light.Work().DL_Color = { 0.5,0.5,0.5 };
	//SHADER.m_cb8_Light.Work().AmbientLight = { 0.5f,0.5f,0.5f };
	// ���C�g�̃f�[�^����������
	SHADER.m_cb8_Light.Write();

	//�u�����h�ݒ�
	blendAdd = D3D.CreateBlendState(KdBlendMode::Add);
	blendAlpha = D3D.CreateBlendState(KdBlendMode::Alpha);

	//���f��

	m_TransWait = std::make_unique<C_Transwait>();
	m_Ground = std::make_unique<C_ground>();
	m_Background = std::make_unique<C_Background>();
	m_Backitem = std::make_unique<C_Backitem>();
	m_Goalpin = std::make_unique<C_Warp>();
	m_Number = std::make_unique<C_number>();
	m_Icon = std::make_unique<C_icon>();
	m_Stagelimit = std::make_unique<C_Shell>();
	m_Water = std::make_unique<C_water>();
	m_Canbt = std::make_unique<C_canbt>();
	m_Fellow1 = std::make_unique<C_Fellow1>();
	m_Fellow2 = std::make_unique<C_Fellow2>();

	m_ModelManager = std::make_shared<ModelManager>();
	m_BlockManager = std::make_unique<BlockManager>(m_ModelManager);
	m_PlayerManager = std::make_unique<PlayerManager>();

	m_Coal.push_back(new C_coal(Math::Vector3(-7.0f, 10.0f, 23.0f)));
	m_Coal.push_back(new C_coal(Math::Vector3(-7.0f, 10.0f, 39.0f)));
	m_Coal.push_back(new C_coal(Math::Vector3(-7.0f, 10.0f, 55.0f)));

	transFlg = false;
	hintFlg = false;
	startFlg = false;
	intro = true;

	m_StatePos = m_Mat.Translation();
	m_camAngY = 0;
	m_camAngX = 0;
	camposZ = -15;
	startalpha = 0.0f;
	startwait = 60.0f;
	overCountDown = 120.0f;
	cameraProgress = 0.0f;

	clock_mat = DirectX::XMMatrixTranslation(-600, 300, 0);
	startgame_mat = DirectX::XMMatrixScaling(0.5f, 0.5f, 0.5f) * DirectX::XMMatrixTranslation(0, 0, 0);
	presssp_mat = DirectX::XMMatrixTranslation(0, -200, 0);

	m_Clock.Load("Data/Texture/clock.png");
	m_Startgame.Load("Data/Texture/startgame.png");
	m_PressSpace.Load("Data/Texture/pressspace.png");

	SYSTEM.SetnextStage(SYSTEM.GetnowStage() + 1);
	SYSTEM.Setstate(1);
	//BGM�C�j�V����
	m_Soundbgm = std::make_shared<KdSoundEffect>();
	m_Soundbgm->Load("Data/music/Stagesound.wav");
	m_BgmInst = m_Soundbgm->CreateInstance(false);
	m_BgmInst->SetVolume(0.05f);
	m_BgmInst->Play(true);
}

//=============================================================================================================================================

//�����[�X����
void GameScene::Release()
{
	for (UINT i = 0; i < m_Coal.size(); i++)
	{
		delete m_Coal[i];
	}

	for (UINT i = 0; i < m_Smoke.size(); i++)
	{
		delete m_Smoke[i];
	}
	m_Coal.clear();
	m_Smoke.clear();
	m_Clock.Release();
	m_PressSpace.Release();
	m_Startgame.Release();
	m_BgmInst->Stop();

}
