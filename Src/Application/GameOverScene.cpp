#include "main.h"
#include "Game.h"
#include"TitelScene.h"
#include"ClearScene.h"
#include "GameOverScene.h"


GameOver::GameOver()
{
	Init();
}

GameOver::~GameOver()
{
	Release();
}

void GameOver::Init()
{
	m_basept = { ScrW / 2,ScrH / 2 };
	ClientToScreen(APP.m_window.GetWndHandle(), &m_basept);
	SetCursorPos(m_basept.x, m_basept.y);

	soundCheck = false;
	overalpha = 0.0f;
	
	m_bg.Load("Data/Texture/overback.png");
	m_Over.Load("Data/Texture/overscene.png");
	m_Restart.Load("Data/Texture/restart.png");
	m_Home.Load("Data/Texture/home.png");

	m_Restartmat = DirectX::XMMatrixTranslation(-540.0f, -280.0f, 0.0f);
	m_Homemat = DirectX::XMMatrixTranslation(540.0f, -280.0f, 0.0f);
	//BGMƒCƒjƒVƒƒƒ‹
	m_Soundbgm = std::make_shared<KdSoundEffect>();
	m_Soundbgm->Load("Data/music/gameover.wav");
	m_BgmInst = m_Soundbgm->CreateInstance(false);
	m_BgmInst->SetVolume(0.05f);
	m_BgmInst->Play(false);
}

void GameOver::Update()
{
	overalpha += 0.005f;
	if (overalpha >= 1.0f)
	{
		overalpha = 1.0f;
	}

	if (APP.m_window.GetWndHandle() == GetActiveWindow() && overalpha>=1.0f)
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
		else
		{
			ButtonSet(ButtonName::Restart, m_Restartmat, false);
			ButtonSet(ButtonName::Home, m_Homemat, false);
		}
	}
}

void GameOver::Draw()
{
	SHADER.m_spriteShader.Begin();
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawTex(&m_bg, Math::Rectangle(0, 0, 1280, 720), 1.0f);
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawTex(&m_Over, Math::Rectangle(0, 0, 1280, 720), overalpha);
	if (overalpha >= 1.0f)
	{
		SHADER.m_spriteShader.SetMatrix(m_Restartmat);
		SHADER.m_spriteShader.DrawTex(&m_Restart, Math::Rectangle(0, 0, 90, 90), 1.0f);
		SHADER.m_spriteShader.SetMatrix(m_Homemat);
		SHADER.m_spriteShader.DrawTex(&m_Home, Math::Rectangle(0, 0, 90, 90), 1.0f);
	}
}

void GameOver::SetCamera()
{
}

void GameOver::ButtonSet(ButtonName _name, Math::Matrix& _mat, bool _touch)
{
	Math::Matrix m_Scale;
	Math::Matrix m_Trans;
	switch (_name)
	{
	case ButtonName::Restart:
		m_Trans = DirectX::XMMatrixTranslation(-540.0f, -280.0f, 0.0f);
		break;
	case ButtonName::Home:
		m_Trans = DirectX::XMMatrixTranslation(540.0f, -280.0f, 0.0f);
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
		}
	}
	else
	{
		SYSTEM.SetEnterKeyFlg(false);
	}
}

void GameOver::Release()
{
	SYSTEM.SetOverFlg(false);
	m_BgmInst->Stop();
	m_bg.Release();
	m_Over.Release();
	m_Restart.Release();
	m_Home.Release();
}
