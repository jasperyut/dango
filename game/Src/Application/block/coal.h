#pragma once
#include"./Application/define.h"

class C_coal {
public:
	C_coal(const Math::Vector3& _pos);
	~C_coal();
	Math::Vector3 GetPanelPos(int _noX, int _noZ)const;
	void Draw();
	void Update();
	//“§–¾‰»ˆ—
	void AlphaSet(float& _alpha);

private:
	KdTexture m_Tex;
	KdBuffer m_Vb;

	Math::Matrix m_Mat = {};
	Math::Matrix m_Lightmat = {};
	
	Math::Vector3 m_Pos = {};
	Vertex v[10][11][2] = {};
	
	float height[11][11];
	float Chroma=0.3f;//Ê“x
	float flashing = 0.0f;//‰Š‚ÌŒõ
	float alpha;
};