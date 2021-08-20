#pragma once
#include"./Application/block/blockmanager.h"

class C_Fellow1
{
public:
	C_Fellow1();
	~C_Fellow1();
	void Draw();
	void Update(Math::Vector3 _pos, std::unique_ptr<BlockManager>& _blockManager);
	const Math::Vector3 GetPos()const
	{
		return m_Mat.Translation();
	}
	const Math::Matrix Getmat()const
	{
		return m_Mat;
	}
	const float& GetRange() { return range; }

private:
	KdModel m_Dango;

	Math::Matrix m_Mat;
	Math::Matrix m_Trans;
	Math::Matrix m_Move;
	Math::Matrix m_Scale;
	Math::Matrix m_Rot;
	Math::Matrix camMat;

	Math::Vector3 moveVec = {};
	Math::Vector3 m_Pos;

	int soundwait;
	float m_ang = 0;
	float scaleang;
	float bounceXZ;
	float bounceY;
	float gravity = {};//d—Í
	float m_hitDis = {};
	float range = 1.0f;
	bool moveFlg;//ˆÚ“®ƒtƒ‰ƒO
	bool bounceflg;
	
	
};




