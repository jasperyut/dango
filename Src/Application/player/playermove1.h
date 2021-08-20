#pragma once
#include"state.h"
#include"./Application/block/blockmanager.h"
#include"System/KeySystem.h"

class C_playermove1:public State {
public:
	C_playermove1();
	~C_playermove1();
	void Draw(Math::Matrix& _mat)override;
	void Update(std::unique_ptr<BlockManager>& _blockManager, Math::Matrix& _mat, float& _ang)override;

private:
	KdModel m_partW;
	KdModel m_partG;
	KdModel m_partP;

	Math::Matrix m_Mat;
	Math::Matrix G_mat;
	Math::Matrix P_mat;
	Math::Matrix m_Rot;
	Math::Matrix m_Trans;
	Math::Matrix m_Scale;

	Math::Vector3 m_Pos;
	Math::Vector3 cur_pos;
	Math::Vector3 Inertia;//慣性

	//マウスの座標
	POINT pt;

	//マウスカーソルの基準座標
	POINT m_basePt;

	int stateFlg;
	int soundwait;
	float m_hitDis = {};
	float	m_ang = 0;
	float range = 1.0f;
	float a = 1;
	float scaleang;
	float bounceXZ;
	float bounceY;
	float gravity = {};//重力
	float pressure=1;
	float release;
	bool moveFlg;//移動中
	bool InertiaFlg;//慣性フラグ
	bool jumpSound;
	bool storeSound;
	
};