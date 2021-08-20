#pragma once
#include"./Application/define.h"

class C_ground {
public:
	C_ground();
	~C_ground();
	void Draw();

private:
	KdTexture m_Tex;
	KdBuffer m_Vb;

	Math::Matrix m_Mat = {};
	
	Vertex m_v[4] = {};
};