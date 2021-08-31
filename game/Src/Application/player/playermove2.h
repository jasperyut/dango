#pragma once
#include"state.h"
#include"./Application/block/blockmanager.h"
class C_playermove2:public State {
public:
	C_playermove2();
	~C_playermove2();
	
	void Draw(Math::Matrix& _mat)override;
	void Update(std::unique_ptr<BlockManager>& _blockManager, Math::Matrix& _mat, float& _ang)override;

private:
	KdModel m_Model;
	KdModel m_Shadow;

	Math::Matrix m_Mat;
	Math::Matrix m_Rot;
	Math::Matrix m_Trans;
	Math::Matrix m_Scale;

	Math::Matrix m_SMat;
	Math::Matrix m_STrans;
	Math::Matrix m_SScale;
	
	Math::Vector3 m_Pos;
	Math::Vector3 m_SPos;

	
	float scaleang;
	float bounceXZ;
	float bounceY;
	float	m_ang = 0;
	float range = 2.1f;
	float a = 1;
	float gravity = {};//d—Í
	float m_hitDis = {};
	float Salpha;
	int soundwait;
	int stateFlg;
	bool moveFlg;//ˆÚ“®’†
	bool isfalling;//—‚¿‚Ä‚éó‘Ô
};

