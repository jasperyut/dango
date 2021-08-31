#pragma once
#include"./Application/block/blockmanager.h"

class C_Fellow2
{
public:
	C_Fellow2();
	~C_Fellow2();
	void Draw();
	void Update(Math::Vector3 _pos, std::unique_ptr<BlockManager>& _blockManager);
	void HitCheck(std::unique_ptr<BlockManager>& _blockManager);//地面当たり判定
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
	KdModel m_Shadow;

	Math::Matrix m_Mat;
	Math::Matrix m_Trans;
	Math::Matrix m_Move;
	Math::Matrix m_Scale;
	Math::Matrix m_Rot;
	Math::Matrix camMat;

	Math::Matrix m_SMat;
	Math::Matrix m_STrans;

	Math::Vector3 moveVec = {};
	Math::Vector3 m_Pos;
	Math::Vector3 m_SPos;

	int soundwait;
	float scaleang;
	float bounceXZ;
	float bounceY;
	float m_ang = 0;
	float gravity = {};//重力
	float m_hitDis = {};
	float range = 1.0f;
	float Salpha;
	bool moveFlg;//移動フラグ
	bool bounceflg;
	
};