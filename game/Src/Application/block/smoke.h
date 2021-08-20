#pragma once
#include"Application/define.h"


class C_Smoke
{
public:
	C_Smoke() {};
	C_Smoke(const Math::Vector3& _pos);
	~C_Smoke();
	bool Update();
	void Draw();



private:
	KdBuffer m_Vb;		// 頂点バッファ
	KdTexture m_Tex;	// テクスチャ


	Math::Matrix m_Mat = {};	// 行列
	Vertex v[4] = {};
	Math::Matrix m_Trans = {};
	Math::Matrix m_Rot = {};
	Math::Matrix m_Scale = {};
	Math::Matrix m_Move = {};
	Math::Vector3 m_Pos = {};
	Math::Vector3 m_MoveVec = {};

	float alpha;
};