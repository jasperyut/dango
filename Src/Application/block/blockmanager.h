#pragma once


#include"block.h"
#include"can.h"
#include"spoon.h"
#include"cylinder.h"
#include"faucet.h"
#include"bbqgrill.h"
#include"button.h"
#include"elevator.h"
#include"System/ModelManager.h"
#include<vector>

class BlockManager
{
public:
	BlockManager(std::shared_ptr<ModelManager>& _om);
	~BlockManager();
	void Update();
	void Draw();
	bool CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _returnVec, float& _range)const;
	const std::vector<C_can*> Getcan()
	{
		return m_Can;
	}

private:
	//木のブロック
	std::vector<C_block*>m_Block;
	//缶
	std::vector<C_can*>m_Can;
	//スプーン
	std::vector<C_spoon*>m_Spoon;
	//当たり判定用隠しブロック
	std::vector<C_cylinder*>m_Cylinder;
	//水栓
	std::vector<C_faucet*>m_Faucet;
	//網焼きコンロ
	std::vector<C_BBQgrill*>m_Bbqgrill;
	//ボタン
	std::vector<C_button*>m_Button;
	//エレベーター
	std::vector<C_elevator*>m_Elevator;

	
};
#define BLOCKMANAGER BlockManager::GetInstance()