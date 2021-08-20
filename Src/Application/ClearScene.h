#pragma once
#include"Scene.h"
#include"ground/ground.h"
#include"background.h"
#include"block/blockmanager.h"
#include"backitem.h"
#include"number.h"


//一ステージクリアした画面
class Clearscene:public Scene
{
public:
	Clearscene();
	~Clearscene();
	void Init();
	void Update()override;
	void Draw()override;
	void SetCamera()override;
	void AnimeProc(int d);
	void ButtonSet(ButtonName _name,Math::Matrix& _mat,bool _touch);
	void Release();
private:
	
	KdModel m_Goal;
	KdModel m_Dango[3];
	KdTexture m_StarEmpty[3];
	KdTexture m_StarGlow[3];
	KdTexture m_Clear;
	KdTexture m_Restart;
	KdTexture m_Home;
	KdTexture m_Next;

	std::unique_ptr<C_ground> m_Ground;
	std::unique_ptr<C_Background> m_Background;
	std::unique_ptr<C_Backitem> m_Backitem;
	std::unique_ptr<C_number> m_Number;
	
	Math::Matrix m_DangoMat[3];
	Math::Matrix m_GoalMat;
	Math::Matrix m_ESmat[3];
	Math::Matrix m_GSmat[3];
	Math::Matrix frame_start[3];
	Math::Matrix frame_end[3];
	Math::Matrix m_Clearmat;
	Math::Matrix m_Restartmat;
	Math::Matrix m_Homemat;
	Math::Matrix m_Nextmat;

	Math::Vector3 m_Pos;

	float m_animeProgress;
	float camX;
	float camY;
	float camZ;
	float achflg[3];
	bool accountFlg;
	bool soundCheck;
	bool iconAlpha;
	bool stabSoundCheck;
	int time=15;
	int waittime;

	POINT m_basept;
	POINT pt;

	//bgm
	std::shared_ptr<KdSoundEffect> m_Soundbgm;
	std::shared_ptr<KdSoundInstance> m_BgmInst;
};

