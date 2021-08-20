#pragma once
#include"state.h"
#include"player.h"
#include"playermove1.h"
#include"playermove2.h"
#include"Application/block/coal.h"

class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();
	void Update(std::unique_ptr<BlockManager>& _blockManager);
	void Draw();

	const Math::Matrix Getmat()const
	{
		return m_Mat;
	}
	const Math::Matrix& Getrot()const
	{
		return m_Rot;
	}
	const float& Getang()
	{
		return m_ang;
	}

private:
	std::unique_ptr<State> m_State;

	Math::Matrix m_Mat;
	Math::Matrix m_Rot;
	
	float m_ang;
	int soundwait;
};

