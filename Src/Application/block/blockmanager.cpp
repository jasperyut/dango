#include "blockManager.h"
#include"System/KeySystem.h"

BlockManager::BlockManager(std::shared_ptr<ModelManager>& _om)
{
	if (SYSTEM.GetnowStage() == 1)
	{
		//インスタンス化
		m_Block.push_back(new C_block(_om, Math::Vector3(0.0f, 50.0f, 42.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(25.0f, 43.0f, 42.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(-14.0f, 43.0f, 56.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(20.0f, 35.0f, 56.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(-20.0f, 30.0f, 64.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(7.0f, 25.0f, 71.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(16.0f, 20.0f, 78.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(-5.0f, 20.0f, 85.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(10.0f, 23.0f, 99.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(7.0f, 30.0f, 110.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(7.0f, 57.0f, 34.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(14.0f, 57.0f, 34.0f)));
		m_Can.push_back(new C_can(_om, Math::Vector3(-10.0f, 7.0f, 34.0f)));
		m_Elevator.push_back(new C_elevator(_om, Math::Vector3(-20.0f, 60.0f, 34.0f)));
	}
	if (SYSTEM.GetnowStage() == 2)
	{
		m_Block.push_back(new C_block(_om, Math::Vector3(-13.0f, 3.0f, 7.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(-13.0f, 10.0f, 15.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(1.0f, 3.0f, 31.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(1.0f, 10.0f, 39.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(1.0f, 10.0f, 47.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(1.0f, 10.0f, 55.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(-6.0f, 10.0f, 55.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(-23.0f, 3.0f, 56.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(-23.0f, 3.0f, 74.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(-23.0f, 13.0f, 95.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(-23.0f, 13.0f, 103.0f)));
		m_Faucet.push_back(new C_faucet(_om, Math::Vector3(30.0f, 0.0f, 26.0f)));
		m_Spoon.push_back(new C_spoon(_om, Math::Vector3(-20.0f, 2.0f, 24.0f)));
		m_Cylinder.push_back(new C_cylinder(_om, Math::Vector3(-20.0f, 0.0f, 24.0f)));
	}

	if (SYSTEM.GetnowStage() == 3)
	{
		m_Block.push_back(new C_block(_om, Math::Vector3(12.0f, 3.0f, 5.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(4.0f, 10.0f, 8.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(4.0f, 10.0f, 16.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(0.0f, 13.0f, 103.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(0.0f, 13.0f, 95.0f)));
		m_Block.push_back(new C_block(_om, Math::Vector3(0.0f, 13.0f, 87.0f)));
		m_Bbqgrill.push_back(new C_BBQgrill(_om, Math::Vector3(0.0f, 0.0f, 30.0f)));
		m_Bbqgrill.push_back(new C_BBQgrill(_om, Math::Vector3(0.0f, 0.0f, 46.0f)));
		m_Bbqgrill.push_back(new C_BBQgrill(_om, Math::Vector3(0.0f, 0.0f, 62.0f)));
		m_Button.push_back(new C_button(_om, Math::Vector3(-10.0f, 0.0f, 30.0f)));
		m_Button.push_back(new C_button(_om, Math::Vector3(-10.0f, 0.0f, 46.0f)));
		m_Button.push_back(new C_button(_om, Math::Vector3(-10.0f, 0.0f, 62.0f)));
	}

	if (SYSTEM.GetnowStage() == 4)
	{
		m_Block.push_back(new C_block(_om, Math::Vector3(2.0f, 3.0f, 87.0f)));
		m_Bbqgrill.push_back(new C_BBQgrill(_om, Math::Vector3(2.0f, 0.0f, 60.0f)));
	}


}

BlockManager::~BlockManager()
{

	//解放
	for (UINT i = 0; i < m_Block.size(); i++)
	{
		delete m_Block[i];

	}
	for (UINT i = 0; i < m_Can.size(); i++)
	{
		delete m_Can[i];

	}

	for (UINT i = 0; i < m_Spoon.size(); i++)
	{
		delete m_Spoon[i];

	}
	
	for (UINT i = 0; i < m_Faucet.size(); i++)
	{
		delete m_Faucet[i];

	}

	for (UINT i = 0; i < m_Bbqgrill.size(); i++)
	{
		delete m_Bbqgrill[i];

	}

	for (UINT i = 0; i < m_Button.size(); i++)
	{
		delete m_Button[i];

	}

	for (UINT i = 0; i < m_Elevator.size(); i++)
	{
		delete m_Elevator[i];
	}

	//配列の削除
	m_Block.clear();
	m_Can.clear();
	m_Spoon.clear();
	m_Cylinder.clear();
	m_Faucet.clear();
	m_Bbqgrill.clear();
	m_Button.clear();
	m_Elevator.clear();
}

void BlockManager::Update()
{
	if (SYSTEM.GetnowStage() == 1)
	{
		m_Block[3]->Update();
		m_Block[5]->Update();
		m_Block[7]->Update();
	}

	//キューブのアップデート
	if (SYSTEM.GetnowStage() == 2)
	{
		m_Block[7]->Update();
		m_Block[8]->Update();
	}

	for (UINT i = 0; i < m_Can.size(); i++)
	{
		m_Can[i]->Update();
	}
	for (UINT i = 0; i < m_Spoon.size(); i++)
	{
		m_Spoon[i]->Update();
	}
	for (UINT i = 0; i < m_Cylinder.size(); i++)
	{
		m_Cylinder[i]->Update();
	}
	for (UINT i = 0; i < m_Faucet.size(); i++)
	{
		m_Faucet[i]->Update();
	}
	for (UINT i = 0; i < m_Bbqgrill.size(); i++)
	{
		m_Bbqgrill[i]->Update();
	}
	for (UINT i = 0; i < m_Button.size(); i++)
	{
		m_Button[i]->Update();
	}
	for (UINT i = 0; i < m_Elevator.size(); i++)
	{
		m_Elevator[i]->Update();
	}
}

void BlockManager::Draw()
{
	//キューブの表示
	for (UINT i = 0; i < m_Block.size(); i++)
	{
		m_Block[i]->Draw();
	}
	
	for (UINT i = 0; i < m_Can.size(); i++)
	{
		m_Can[i]->Draw();
	}

	for (UINT i = 0; i < m_Cylinder.size(); i++)
	{
		m_Cylinder[i]->Draw();
	}

	for (UINT i = 0; i < m_Faucet.size(); i++)
	{
		m_Faucet[i]->Draw();
	}

	for (UINT i = 0; i < m_Spoon.size(); i++)
	{
		m_Spoon[i]->Draw();
	}

	for (UINT i = 0; i < m_Bbqgrill.size(); i++)
	{
		m_Bbqgrill[i]->Draw();
	}

	for (UINT i = 0; i < m_Button.size(); i++)
	{
		m_Button[i]->Draw();
	}
	for (UINT i = 0; i < m_Elevator.size(); i++)
	{
		m_Elevator[i]->Draw();
	}
}



bool BlockManager::CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _returnVec, float& _range) const
{

	//キューブとの当たり判定
	for (UINT i = 0; i < m_Block.size(); i++)
	{
		if (m_Block[i]->CheckHit(_rayPos, _rayVec, _dis, _returnVec, _range))
		{
			return true;
		}
	}
	for (UINT i = 0; i < m_Can.size(); i++)
	{
		if (m_Can[i]->CheckHit(_rayPos, _rayVec, _dis, _returnVec, _range))
		{
			return true;
		}
	}
	for (UINT i = 0; i < m_Spoon.size(); i++)
	{
		if (m_Spoon[i]->CheckHit(_rayPos, _rayVec, _dis, _returnVec, _range))
		{
			return true;
		}
	}
	for (UINT i = 0; i < m_Cylinder.size(); i++)
	{
		if (m_Cylinder[i]->CheckHit(_rayPos, _rayVec, _dis, _returnVec, _range))
		{
			return true;
		}
	}
	for (UINT i = 0; i < m_Faucet.size(); i++)
	{
		if (m_Faucet[i]->CheckHit(_rayPos, _rayVec, _dis, _returnVec, _range))
		{
			return true;
		}

	}

	for (UINT i = 0; i < m_Bbqgrill.size(); i++)
	{
		if (m_Bbqgrill[i]->CheckHit(_rayPos, _rayVec, _dis, _returnVec, _range))
		{
			return true;
		}

	}
	for (UINT i = 0; i < m_Button.size(); i++)
	{
		if (m_Button[i]->CheckHit(_rayPos, _rayVec, _dis, _returnVec, _range))
		{
			return true;
		}

	}

	for (UINT i = 0; i < m_Elevator.size(); i++)
	{
		if (m_Elevator[i]->CheckHit(_rayPos, _rayVec, _dis, _returnVec, _range))
		{
			return true;
		}
	}

	return false;

}
