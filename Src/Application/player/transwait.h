#pragma once
#include"state.h"

class C_Transwait
{
public:
	C_Transwait();
	~C_Transwait();
	void Update();
	void Draw();
	

private:

	KdModel m_partW;
	KdModel m_partG;
	KdModel m_partP;

	Math::Vector3 m_Pos;

	Math::Matrix W_mat;
	Math::Matrix G_mat;
	Math::Matrix P_mat;
	
	Math::Vector3 WPos, PPos, GPos;

	Math::Matrix Wstart_mat;
	Math::Matrix Pstart_mat;
	Math::Matrix Gstart_mat;

	Math::Vector3 Wtmppos;
	Math::Vector3 Ptmppos;
	Math::Vector3 Gtmppos;
	
	State* m_nowState = nullptr;

	float m_animeProgress;
	float gravity = {};
	bool valueflg;
	int StateStore = {};
};
