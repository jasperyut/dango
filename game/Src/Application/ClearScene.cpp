#include "main.h"
#include "ClearScene.h"
#include "Game.h"
#include"TitelScene.h"
#include"CompleteScene.h"
#include"SceneManager.h"
#include"System/KeySystem.h"

Clearscene::Clearscene()
{
	Init();

}

Clearscene::~Clearscene()
{
	
	Release();
}

void Clearscene::Init()
{
	m_basept = { ScrW / 2,ScrH / 2 };
	ClientToScreen(APP.m_window.GetWndHandle(), &m_basept);
	SetCursorPos(m_basept.x, m_basept.y);
	

	SHADER.m_cb8_Light.Work().DL_Dir = { 1,-1,0 };
	SHADER.m_cb8_Light.Work().DL_Dir.Normalize();
	SHADER.m_cb8_Light.Work().DL_Color = { 2,2,2 };
	SHADER.m_cb8_Light.Work().AmbientLight = { 0.5f,0.5f,0.5f };
	SHADER.m_cb8_Light.Write();

	//カメラ位置
	camX = 0.0f;
	camY = 1.0f;
	camZ = 4.0f;

	waittime = 10;
	m_animeProgress = 0.0f;
	accountFlg = false;
	soundCheck = false;
	iconAlpha = false;
	stabSoundCheck = false;

	//モデル
	m_Ground = std::make_unique<C_ground>();
	m_Background = std::make_unique<C_Background>();
	m_Backitem = std::make_unique<C_Backitem>();
	m_Number = std::make_unique<C_number>();
	m_Goal.Load("Data/model/warp.gltf");
	m_Dango[0].Load("Data/model/player/dango2.gltf");
	m_Dango[1].Load("Data/model/player/dango1.gltf");
	m_Dango[2].Load("Data/model/player/dango3.gltf");
	m_Clear.Load("Data/Texture/clear.png");
	m_Restart.Load("Data/Texture/restart.png");
	m_Home.Load("Data/Texture/home.png");
	m_Next.Load("Data/Texture/next.png");


	//リザルト画面
	for (int d = 0; d < 3; d++)
	{
		frame_start[d] = DirectX::XMMatrixTranslation(0, 18.0f + d * 10, 0);
		Math::Matrix m_Trans;
		m_Trans = DirectX::XMMatrixTranslation(0, 11.0f + m_GoalMat.Translation().y + d * 1.5f, 0);
		frame_end[d] = m_Trans;
		m_DangoMat[d] = frame_start[d];
	}

	m_GoalMat = DirectX::XMMatrixTranslation(0.0f, 8.0f, 0.0f);
	Math::Matrix cleartrans;
	Math::Matrix clearscale;
	cleartrans = DirectX::XMMatrixTranslation(180.0f, 640.0f, 0.0f);
	clearscale = DirectX::XMMatrixScaling(0.7f, 0.7f, 0.0f);
	m_Clearmat = clearscale * cleartrans;
	m_Restartmat = DirectX::XMMatrixTranslation(-140.0f, -160.0f, 0.0f);
	m_Homemat = DirectX::XMMatrixTranslation(-140.0f, 90.0f, 0.0f);
	m_Nextmat = DirectX::XMMatrixTranslation(450.0f, -160.0f, 0.0f);

	//星
	for (int i = 0; i < 3; i++)
	{
		m_StarEmpty[i].Load("Data/Texture/Estar.png");
		m_StarGlow[i].Load("Data/Texture/Gstar.png");
		m_ESmat[i] = clearscale * DirectX::XMMatrixTranslation(15.0f + i * 140, m_Clearmat._42 + 145 + i % 2 * 35, 0);
		m_GSmat[i] = clearscale * DirectX::XMMatrixTranslation(15.0f + i * 140, m_Clearmat._42 + 145 + i % 2 * 35, 0);
		achflg[i] = 0.0f;
	}

	//BGM
	m_Soundbgm = std::make_shared<KdSoundEffect>();
	m_Soundbgm->Load("Data/music/Clearsound.wav");
	m_BgmInst = m_Soundbgm->CreateInstance(false);
	m_BgmInst->SetVolume(0.05f);
	m_BgmInst->Play(true);
}

void Clearscene::Update()
{
	

	for (int d = 0; d < 3; d++)
	{
		

		m_animeProgress += 0.01f;
		if (m_animeProgress > 1)
		{
			m_animeProgress = 1.0f;
			

		}
		if (m_animeProgress > 0.5f&&m_animeProgress<0.51f)
		{
			stabSoundCheck = true;
		}
		else
		{
			stabSoundCheck = false;
		}
		
		AnimeProc(d);
	}

	if(stabSoundCheck==true)
	{
		stabSoundCheck = false;
		SYSTEM.GetSoundManager().SetSound("Data/music/stab.wav");
	}

	if (m_animeProgress == 1)
	{
		camX += -0.05f;
		camY += 0.05f;
		camZ += 0.05f;
		if (camX <= -4.0f)
		{
			camX = -4.0f;
		}
		if (camY >= 5.0f)
		{
			camY = 5.0f;
		}
		if (camZ >= 6.0f)
		{
			camZ = 6.0f;
		}

	}
	if (camX <= -4.0f)
	{
		m_Clearmat._42 -= 20.0f;
		if (m_Clearmat._42 <= 0.0f)
		{
			accountFlg = true;
			iconAlpha = true;
			m_Clearmat._42 = 0.0f;
		}
		for (int i = 0; i < 3; i++)
		{
			m_ESmat[i] = DirectX::XMMatrixTranslation(15.0f + i * 140, m_Clearmat._42 + 145 + i % 2 * 35, 0);
			m_GSmat[i] = DirectX::XMMatrixTranslation(15.0f + i * 140, m_Clearmat._42 + 145 + i % 2 * 35, 0);

		}
	}

	if (APP.m_window.GetWndHandle() == GetActiveWindow()&&iconAlpha==true)
	{

		
		POINT pt;
		GetCursorPos(&pt);

		float MouseX, MouseY;
		MouseX = (float)(pt.x - m_basept.x);
		MouseY = (float)(m_basept.y - pt.y);

		if ((MouseX > m_Restartmat.Translation().x - 45) && (MouseX < m_Restartmat.Translation().x + 45) &&
			(MouseY > m_Restartmat.Translation().y - 45) && (MouseY < m_Restartmat.Translation().y + 45))
		{
			ButtonSet(ButtonName::Restart, m_Restartmat, true);
		}
		else if ((MouseX > m_Homemat.Translation().x - 45) && (MouseX < m_Homemat.Translation().x + 45) &&
			(MouseY > m_Homemat.Translation().y - 45) && (MouseY < m_Homemat.Translation().y + 45))
		{
			ButtonSet(ButtonName::Home, m_Homemat, true);
		}
		else if ((MouseX > m_Nextmat.Translation().x - 85) && (MouseX < m_Nextmat.Translation().x + 85) &&
			(MouseY > m_Nextmat.Translation().y - 35) && (MouseY < m_Nextmat.Translation().y + 35))
		{
			ButtonSet(ButtonName::Next, m_Nextmat, true);
		}
		else
		{
			ButtonSet(ButtonName::Restart, m_Restartmat, false);
			ButtonSet(ButtonName::Home, m_Homemat, false);
			ButtonSet(ButtonName::Next, m_Nextmat, false);
		}
	}

	//時間によって星数を与える
	if (accountFlg != 0)
	{
		if (waittime == 0 && achflg[0] != 1.0f)
		{
			waittime = 20;
			achflg[0] = 1.0f;
			SYSTEM.GetSoundManager().SetSound("Data/music/star.wav");
		}
		if (waittime == 0 && SYSTEM.GetnowTime() <= 60 && achflg[2] != 1.0f)
		{
			waittime = 20;
			achflg[2] = 1.0f;
			SYSTEM.GetSoundManager().SetSound("Data/music/star.wav");
		}
		if (waittime == 0 && SYSTEM.GetnowTime() <= 40 && achflg[1] != 1.0f)
		{
			achflg[1] = 1.0f;
			SYSTEM.GetSoundManager().SetSound("Data/music/star.wav");
		}

		waittime--;
		if (waittime <= 0)
		{
			waittime = 0;
		}


	}


}

void Clearscene::Draw()
{
	GetCursorPos(&pt);

	float MouseX, MouseY;
	MouseX = (float)(pt.x - m_basept.x);
	MouseY = (float)(m_basept.y - pt.y);

	SHADER.m_effectShader.SetToDevice();
	m_Ground->Draw();

	SHADER.m_standardShader.SetToDevice();
	for (int d = 0; d < 3; d++)
	{
		SHADER.m_standardShader.SetWorldMatrix(m_DangoMat[d]);
		SHADER.m_standardShader.DrawModel(&m_Dango[d]);
	}
	SHADER.m_standardShader.SetWorldMatrix(m_GoalMat);
	SHADER.m_standardShader.DrawModel(&m_Goal);


	m_Background->Draw();
	m_Backitem->Draw();
	SHADER.m_spriteShader.Begin();

	SHADER.m_spriteShader.SetMatrix(m_Clearmat);
	SHADER.m_spriteShader.DrawTex(&m_Clear, Math::Rectangle(0, 0, 1280, 720), 1.0f);
	SHADER.m_spriteShader.SetMatrix(m_Restartmat);
	SHADER.m_spriteShader.DrawTex(&m_Restart, Math::Rectangle(0, 0, 90, 90), iconAlpha);
	SHADER.m_spriteShader.SetMatrix(m_Homemat);
	SHADER.m_spriteShader.DrawTex(&m_Home, Math::Rectangle(0, 0, 90, 90), iconAlpha);
	SHADER.m_spriteShader.SetMatrix(m_Nextmat);
	SHADER.m_spriteShader.DrawTex(&m_Next, Math::Rectangle(0, 0, 170, 70), iconAlpha);

	if (accountFlg == true&&SYSTEM.GetnowStage()==0)
	{
		m_Number->Draw();
	}

	for (int i = 0; i < 3; i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_ESmat[i]);
		SHADER.m_spriteShader.DrawTex(&m_StarEmpty[i], Math::Rectangle(0, 0, 200, 200), 1.0f);

		SHADER.m_spriteShader.SetMatrix(m_GSmat[i]);
		SHADER.m_spriteShader.DrawTex(&m_StarGlow[i], Math::Rectangle(0, 0, 200, 200), achflg[i]);
	}

	SHADER.m_spriteShader.End();
}

void Clearscene::SetCamera()
{
	SHADER.m_cb7_Camera.Work().mV = DirectX::XMMatrixLookAtLH(
		m_GoalMat.Translation() + Math::Vector3(camX, camY, camZ),
		m_GoalMat.Translation() + Math::Vector3(camX, 5.0f, 0.0f),
		Math::Vector3(0, 1, 0));
	SHADER.m_cb7_Camera.Work().CamPos = SHADER.m_cb7_Camera.Work().mV.Invert().Translation();

	//射影行列(視界の設定)                                                                          //↓見える距離（最小値,最大値）
	SHADER.m_cb7_Camera.Work().mP =
		DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60), (float)ScrW / (float)ScrH, 0.01f, 1500.0f);
	//                                                         ↑視野角          　↑アスペクト比（横幅長さと縦幅の長さの比率）
	//ビュー行列・射影行列をGPUに転送
	SHADER.m_cb7_Camera.Write();
}

void Clearscene::AnimeProc(int d)
{
	Math::Quaternion startQua;
	Math::Quaternion endQua;
	Math::Quaternion nowQua;
	Math::Vector3 startPos;
	Math::Vector3 endPos;
	Math::Vector3 nowPos;

	//アニメ最初の行列をクオータニオンに変換する
	startQua = DirectX::XMQuaternionRotationMatrix(frame_start[d]);
	//アニメ最後の行列をクオータニオンに変換する
	endQua = DirectX::XMQuaternionRotationMatrix(frame_end[d]);
	//↓最初の状態　　　↓変化の具合
	nowQua = DirectX::XMQuaternionSlerp(startQua, endQua, m_animeProgress);

	m_DangoMat[d] = DirectX::XMMatrixRotationQuaternion(nowQua);


	startPos = frame_start[d].Translation();
	endPos = frame_end[d].Translation();
	//↓最初の位置　　　↓変化の具合
	nowPos = DirectX::XMVectorLerp(startPos, endPos, m_animeProgress);

	//アニメ途中の座標情報を行列に上書きする
	m_DangoMat[d].Translation(nowPos);


}

//ボタンの設定と効果音
void Clearscene::ButtonSet(ButtonName _name, Math::Matrix& _mat, bool _touch)
{
	Math::Matrix m_Scale;
	Math::Matrix m_Trans;
	switch (_name)
	{
	case ButtonName::Restart:
		m_Trans = DirectX::XMMatrixTranslation(-140.0f, -160.0f, 0.0f);
		break;
	case ButtonName::Home:
		m_Trans = DirectX::XMMatrixTranslation(-140.0f, 90.0f, 0.0f);
		break;
	case ButtonName::Next:
		m_Trans = DirectX::XMMatrixTranslation(450.0f, -160.0f, 0.0f);
		break;
	default:
		break;
	}

	if (_touch)
	{
		m_Scale = DirectX::XMMatrixScaling(1.2f, 1.2f, 1.2f);

		if (soundCheck == false)
		{
			SYSTEM.GetSoundManager().SetSound("Data/music/buttontouch.wav");
			soundCheck = true;
		}

	}
	else
	{
		m_Scale = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
		soundCheck = false;

	}

	_mat = m_Scale * m_Trans;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		

			if (SYSTEM.GetEnterKeyFlg() == false)
			{
				SYSTEM.GetSoundManager().SetSound("Data/music/button.wav");
				SYSTEM.SetEnterKeyFlg(true);

				if (_name == ButtonName::Restart)
				{
					SYSTEM.SetnowStage(SYSTEM.GetnextStage() - 1);
					SYSTEM.GetSceneManager().ChangeScene(new GameScene());
					
				}
				if (_name == ButtonName::Home)
				{
					SYSTEM.SetnowStage(0);
					SYSTEM.GetSceneManager().ChangeScene(new TitleScene());
				}
				if (_name == ButtonName::Next)
				{
					//ゲームステージ以外
					if (SYSTEM.GetnextStage() > 3)
					{
						SYSTEM.SetnowStage(SYSTEM.GetnextStage());
						SYSTEM.GetSceneManager().ChangeScene(new CompleteScene());
						
					}
					else 
					{
						SYSTEM.SetnowStage(SYSTEM.GetnextStage());
						SYSTEM.GetSceneManager().ChangeScene(new GameScene());
					}
				}
			}
			
		
	}
	else
	{
		SYSTEM.SetEnterKeyFlg(false);
	}
}

void Clearscene::Release()
{
	
	for (int d = 0; d < 3; d++)
	{
		m_Dango[d].Release();
	}

	for (int i = 0; i < 3; i++)
	{
		m_StarEmpty[i].Release();
		m_StarGlow[i].Release();

	}

	m_Goal.Release();
	m_Clear.Release();
	m_Restart.Release();
	m_Home.Release();
	m_Next.Release();

	m_BgmInst->Stop();
}
