#pragma once
#include"state.h"
#include"./Application/block/blockmanager.h"
#include"System/ModelManager.h"
class C_playermove0:public State{
public:
	C_playermove0();
	~C_playermove0();
	void Draw(Math::Matrix& _mat)override;
	void Update(std::unique_ptr<BlockManager>& _blockManager, Math::Matrix& _mat, float&	_ang)override;

private:
	KdModel m_Dango;
	
	Math::Matrix m_Mat;
	Math::Matrix camMat;
	Math::Matrix m_Rot;
	Math::Matrix m_Trans;
	Math::Matrix m_Scale;

	Math::Vector3 moveVec = {};
	Math::Vector3 m_Pos;

	int soundwait;
	float m_camAngY = {};
	float m_camAngX = {};
	float scaleang;
	float bounceXZ;
	float bounceY;
	float m_ang = 0;
	float range = 1.0f;
	int stateFlg;
	float m_hitDis = {};
	float gravity = {};//d—Í
	bool moveFlg;//ˆÚ“®’†
	
};