#pragma once
#include"./Application/block/blockmanager.h"

class C_Fellow2
{
public:
	C_Fellow2();
	~C_Fellow2();
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
	float scaleang;
	float bounceXZ;
	float bounceY;
	float m_ang = 0;
	float gravity = {};//重力
	float m_hitDis = {};
	float range = 1.0f;
	bool moveFlg;//移動フラグ
	bool bounceflg;
	
};