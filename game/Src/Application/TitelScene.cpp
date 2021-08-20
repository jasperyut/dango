#include "main.h"
#include"TitelScene.h"
#include"Game.h"
#include"SceneManager.h"
#include"define.h"
#include"SpriteFont.h"
#include"System/KeySystem.h"


TitleScene::TitleScene()
{
	Init();
}
TitleScene::~TitleScene()
{
	Release();
}
void TitleScene::Init()
{

	m_basept = { ScrW / 2,ScrH / 2 };
	ClientToScreen(APP.m_window.GetWndHandle(), &m_basept);
	SetCursorPos(m_basept.x, m_basept.y);

	SHADER.m_cb8_Light.Work().DL_Dir = { 1,-1,0 };
	SHADER.m_cb8_Light.Work().DL_Dir.Normalize();
	SHADER.m_cb8_Light.Work().DL_Color = { 2,2,2 };
	SHADER.m_cb8_Light.Work().AmbientLight = { 0.7f,0.7f,0.7f };
	SHADER.m_cb8_Light.Write();

	SpriteFont = new DirectX::SpriteFont(D3D.GetDev(), L"Data/Font/SpriteFont.dat");

	srand(timeGetTime());
	m_Ground = std::make_unique<C_ground>();
	m_Background = std::make_unique<C_Background>();
	m_Model.Load("Data/model/titelitem.gltf");
	m_Mat = DirectX::XMMatrixTranslation(0.0f, 10.0f, 0.0f);
	m_Title.Load("Data/Texture/DANGOLOGOFINAL.png");
	m_StartButton.Load("Data/Texture/start.png");
	m_StartbtMat = DirectX::XMMatrixTranslation(0.0f, -150.0f, 0.0f);
	fade = 1.0f;
	time = 0;
	m_Soundbgm = std::make_shared<KdSoundEffect>();
	m_Soundbgm->Load("Data/music/Titlebgm.wav");
	m_BgmInst = m_Soundbgm->CreateInstance(false);
	m_BgmInst->SetVolume(0.05f);
	m_BgmInst->Play(true);
	soundCheck = false;
	alphaswitch = false;

}
void TitleScene::Release()
{

	m_Model.Release();
	m_Title.Release();
	m_StartButton.Release();
	m_BgmInst->Stop();
}
void TitleScene::Update()
{
	Math::Matrix m_StartScale;
	m_StartScale = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
	Math::Matrix m_StartTrans;
	m_StartTrans= DirectX::XMMatrixTranslation(0.0f, -150.0f, 0.0f);
	if (APP.m_window.GetWndHandle() == GetActiveWindow())
	{
		POINT pt;
		GetCursorPos(&pt);

		float MouseX, MouseY;
		MouseX = (float)(pt.x - m_basept.x);
		MouseY = (float)(m_basept.y-pt.y);

		if ((MouseX > m_StartbtMat.Translation().x - 100)&&(MouseX < m_StartbtMat.Translation().x + 100)&&
			(MouseY > m_StartbtMat.Translation().y - 50)&&(MouseY < m_StartbtMat.Translation().y + 50))
		{
			fade = 1.0f;
			time = 0;
			if (soundCheck == false)
			{
				SYSTEM.GetSoundManager().SetSound("Data/music/buttontouch.wav");
				soundCheck = true;
			}

			//スタート
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				if (SYSTEM.GetEnterKeyFlg() == false)
				{
					
					SYSTEM.GetSoundManager().SetSound("Data/music/button.wav");
					SYSTEM.SetEnterKeyFlg(true);
					SYSTEM.SetnowStage(1);
					SYSTEM.GetSceneManager().ChangeScene(new GameScene());

				}
			}
			else
			{
				SYSTEM.SetEnterKeyFlg(false);
			}


			m_StartScale = DirectX::XMMatrixScaling(1.2f, 1.2f, 1.2f);
		}
		else
		{

			m_StartScale = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
			soundCheck = false;

			if (alphaswitch == false)
			{
				fade += 0.01f;
				if (fade >= 1.0f)
				{
					alphaswitch = true;
				}
			}
			else
			{
				fade -= 0.01f;
				if (fade <= 0.3f)
				{
					alphaswitch = false;
				}
			}
		}
	}

	m_camAngX += 5.0f;
	camPos += Math::Vector3(0, 1, 1);

	
	m_StartbtMat = m_StartScale*m_StartTrans;
}
void TitleScene::Draw()
{
	SHADER.m_effectShader.SetToDevice();

	m_Ground->Draw();
	
	SHADER.m_standardShader.SetToDevice();
	SHADER.m_standardShader.SetWorldMatrix(m_Mat);
	SHADER.m_standardShader.SetNetallic(1.0f);
	SHADER.m_standardShader.DrawModel(&m_Model);
	
	m_Background->Draw();
	
	SHADER.m_spriteShader.Begin();
	SHADER.m_spriteShader.SetMatrix(m_TitleMat);
	SHADER.m_spriteShader.DrawTex(&m_Title, Math::Rectangle(0, 0, 600, 600), 1.0f);
	SHADER.m_spriteShader.SetMatrix(m_StartbtMat);
	SHADER.m_spriteShader.DrawTex(&m_StartButton, Math::Rectangle(0, 0, 200, 200), fade);
	SHADER.m_spriteShader.End();

	////位置チェック用
	//SHADER.m_spriteShader.Begin();
	//char text[256];
	//sprintf_s(text, sizeof(text), "%d", (pt.y - m_basept.y));
	//SHADER.m_spriteShader.DrawString(SpriteFont, -450, 340, text, Math::Vector4(1, 1, 1, 1));

	//SHADER.m_spriteShader.End();
}

void TitleScene::SetCamera()
{
	Math::Matrix tmpRotX;

	camPos = DirectX::XMVector3TransformNormal(Math::Vector3(5, 60, 15), tmpRotX);


	camLook = Math::Vector3(-10, 2, -13);

	camHead = Math::Vector3(0, 1, 0);

	SHADER.m_cb7_Camera.Work().mV = DirectX::XMMatrixLookAtLH(
		camPos,
		camLook,
		camHead);
	SHADER.m_cb7_Camera.Work().CamPos = SHADER.m_cb7_Camera.Work().mV.Invert().Translation();

	//射影行列(視界の設定)                                                                          //↓見える距離（最小値,最大値）
	SHADER.m_cb7_Camera.Work().mP =
		DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60), (float)ScrW / (float)ScrH, 0.01f, 1500.0f);
	//                                                         ↑視野角          　↑アスペクト比（横幅長さと縦幅の長さの比率）
	//ビュー行列・射影行列をGPUに転送
	SHADER.m_cb7_Camera.Write();
}
