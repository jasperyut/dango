#pragma once
#include"Scene.h"
#include"player/state.h"
#include"player/statelist.h"
#include"player/fellow1.h"
#include"player/fellow2.h"
#include"player/transwait.h"
#include"player/playermove2.h"
#include"block/blockmanager.h"
#include"player/playerManager.h"
#include"System/ModelManager.h"
#include"ground/ground.h"
#include"block/coal.h"
#include"icon.h"
#include"block/smoke.h"
#include"Shell/Shell.h"
#include"warp.h"
#include"background.h"
#include"backitem.h"
#include"number.h"
#include"water.h"
#include"canbutton.h"


class GameScene:public Scene
{
public:

	GameScene();
	~GameScene();

	void SetCamera()override;

	// 初期化
	void Init();

	//void Frame();

	// 更新処理
	void Update()override;
	// 描画処理
	void Draw()override;
	// 終了処理
	void Release();

	
	

	static GameScene& GetInstance()
	{
		static GameScene instance;
		return instance;
	}
	const std::unique_ptr <C_Shell>& GetShell()
	{
		return m_Stagelimit;
	}

	const std::unique_ptr<C_water>& Getwater()
	{
		return m_Water;
	}

	const std::unique_ptr<C_Fellow1>& GetFellow1()
	{
		return m_Fellow1;
	}

	const std::unique_ptr <C_Fellow2>& GetFellow2()
	{
		return m_Fellow2;
	}

	const std::unique_ptr<C_Warp>& GetWarp()
	{
		return m_Goalpin;
	}

	const std::unique_ptr<BlockManager>& Getblockmng()
	{
		return m_BlockManager;
	}

	const C_coal* GetCoal()
	{
		return m_Coal[0];
	}

	const Math::Matrix& GetRot()const { return m_Rot; }
	const Math::Matrix& GetMat()const { return m_Mat; }
	const Math::Vector3 GetPos()const { return m_Mat.Translation(); }
	const Math::Vector3& GetcamVec() const { return m_CameraVec; }
	const Math::Vector3& GetCamPos()const { return camPos; }
	const float& GetAng() { return m_camAngY; }
	const float& GetplayerAng() { return playerAng; }
private:
	KdTexture m_Clock;
	KdTexture m_Startgame;
	KdTexture m_PressSpace;

	std::unique_ptr<C_Fellow1> m_Fellow1;
	std::unique_ptr<C_Fellow2> m_Fellow2;
	std::unique_ptr<C_Transwait> m_TransWait;
	std::unique_ptr<C_ground> m_Ground;
	std::unique_ptr<C_Shell> m_Stagelimit;
	std::unique_ptr<C_water> m_Water;
	std::unique_ptr<C_canbt> m_Canbt;
	std::unique_ptr<C_Background> m_Background;
	std::unique_ptr<C_Backitem> m_Backitem;
	std::unique_ptr<C_Warp> m_Goalpin;
	std::unique_ptr<C_number> m_Number;
	std::unique_ptr<C_icon> m_Icon;

	std::unique_ptr<BlockManager> m_BlockManager;
	std::shared_ptr<ModelManager> m_ModelManager;
	std::unique_ptr<PlayerManager> m_PlayerManager;

	std::vector<C_coal*>m_Coal;
	std::vector<C_Smoke*> m_Smoke;

	ID3D11BlendState* blendAdd;
	ID3D11BlendState* blendAlpha;
	
	Math::Vector3 m_Pos = {};
	Math::Vector3 m_StatePos;
	Math::Vector3 m_GoalPos;
	Math::Vector3 m_GPcamPos;//ゴールからプレイヤまでの移動位置
	Math::Vector3 m_GPcamLook;//ゴールからプレイヤまでカメラ見る位置
	Math::Vector3 m_CameraVec;
	Math::Vector3 m_Dango3Pos;
	Math::Vector3 camPos, camLook, camHead;
	Math::Vector3 m_BBQcam;//七輪ギミックのカメラ

	Math::Matrix m_Mat;
	Math::Matrix m_Rot;
	Math::Matrix clock_mat;
	Math::Matrix startgame_mat;
	Math::Matrix presssp_mat;

	int currentState;
	float m_camAngY;
	float m_camAngX;
	float camposZ;
	float fade;
	float playerAng;
	float startalpha;
	float startwait;
	float camZ = -15;
	float overCountDown;
	float cameraProgress;
	bool moveFlg;
	bool transFlg;
	bool hintFlg;
	bool intro;
	bool startFlg;
	
	
	POINT m_basept;
	//bgm
	std::shared_ptr<KdSoundEffect> m_Soundbgm;
	std::shared_ptr<KdSoundInstance> m_BgmInst;

	KdCubeMapGenerator m_cubeMapGen;
	
};

#define GAME GameScene::GetInstance()