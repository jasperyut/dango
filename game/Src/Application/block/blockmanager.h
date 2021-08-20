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
	//�؂̃u���b�N
	std::vector<C_block*>m_Block;
	//��
	std::vector<C_can*>m_Can;
	//�X�v�[��
	std::vector<C_spoon*>m_Spoon;
	//�����蔻��p�B���u���b�N
	std::vector<C_cylinder*>m_Cylinder;
	//����
	std::vector<C_faucet*>m_Faucet;
	//�ԏĂ��R����
	std::vector<C_BBQgrill*>m_Bbqgrill;
	//�{�^��
	std::vector<C_button*>m_Button;
	//�G���x�[�^�[
	std::vector<C_elevator*>m_Elevator;

	
};
#define BLOCKMANAGER BlockManager::GetInstance()