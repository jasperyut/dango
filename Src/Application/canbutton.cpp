#include "canbutton.h"
#include"Application/Game.h"

C_canbt::C_canbt()
{
	m_Shell.Load("Data/model/CBshell.gltf");
	m_Inside.Load("Data/model/CBinside.gltf");
	m_Mat = DirectX::XMMatrixTranslation(10.0f, -1.0f, 34.0f);
	range = 8.1f;
	actived = false;

}

C_canbt::~C_canbt()
{
	m_Shell.Release();
	m_Inside.Release();
}

void C_canbt::Draw()
{
	SHADER.m_standardShader.SetWorldMatrix(m_Mat);
	SHADER.m_standardShader.DrawModel(&m_Shell,1.0f);
	SHADER.m_standardShader.DrawModel(&m_Inside, 1.0f);
}

void C_canbt::Update()
{
	GameScene* game;
	game = dynamic_cast<GameScene*>(SYSTEM.GetSceneManager().GetnowScene());

	Math::Vector3 CantoBtVec;
	float CantoBtlen;
	CantoBtVec = m_Mat.Translation() - game->Getblockmng()->Getcan().back()->GetMat().Translation();
	CantoBtlen = CantoBtVec.Length();
	if (CantoBtlen <= range&&actived==false)
	{
		actived = true;
		SYSTEM.Setstagecam(true);
		SYSTEM.GetSoundManager().SetSound("Data/music/canbutton.wav");
	}
}

