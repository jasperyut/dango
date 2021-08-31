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
	KdModel m_Shadow;
	
	Math::Matrix m_Mat;
	Math::Matrix camMat;
	Math::Matrix m_Rot;
	Math::Matrix m_Trans;
	Math::Matrix m_Scale;

	Math::Matrix m_SMat;
	Math::Matrix m_STrans;

	Math::Vector3 moveVec = {};
	Math::Vector3 m_Pos;
	Math::Vector3 m_SPos;

	int soundwait;
	int stateFlg;
	float m_camAngY = {};
	float m_camAngX = {};
	float scaleang;
	float bounceXZ;
	float bounceY;
	float m_ang = 0;
	float range = 1.0f;
	float Salpha;
	float m_hitDis = {};
	float gravity = {};//èdóÕ
	bool moveFlg;//à⁄ìÆíÜ
	
};