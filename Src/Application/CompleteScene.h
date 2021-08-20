#pragma once
#include"Scene.h"
#include"ground/ground.h"
#include"background.h"
#include"block/blockmanager.h"
#include"block/coal.h"
#include"System/ModelManager.h"
#include"backitem.h"
//ゲーム全部クリアした画面
class CompleteScene:public Scene
{
public:
	CompleteScene();
	~CompleteScene();
	void Init();
	void Update()override;
	void Draw()override;
	void SetCamera()override;
	void AnimeProc(int d);
	void Release();

private:

	KdModel m_PinDefault[3];
	KdModel m_PinSmile[3];
	KdModel m_PinContainer[3];
	KdModel m_Bbqnet;
	KdTexture m_Complete;

	std::shared_ptr<BlockManager> m_BlockManager;
	std::shared_ptr<ModelManager> m_ModelManager;
	std::unique_ptr<C_ground> m_Ground;
	std::unique_ptr<C_Background> m_Background;
	std::unique_ptr<C_Backitem> m_Backitem;
	std::unique_ptr<C_coal> m_Coal;

	Math::Matrix m_PinMat[3];
	Math::Matrix m_NetMat;
	Math::Matrix m_ComMat;
	Math::Matrix frame_start[3];
	Math::Matrix frame_end[3];

	Math::Vector3 m_CamPos[2];
	Math::Vector3 m_CamMove;
	Math::Vector3 m_CamLook[2];
	
	float m_animeProgress;
	float txtalpha;
	float scalevalue;
	int waittime;
	int set;//カメラの番号
	bool changeflg;
	bool playonceTurnsound;
	bool playonce2Dtxt;
	bool playoncegrill;
	bool playonceFlysound;
};