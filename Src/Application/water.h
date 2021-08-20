#pragma once
#include"System/KeySystem.h"
class C_water
{
public:
	C_water();
	~C_water();
	void Draw();
	void Update();
	const Math::Matrix& GetMat()const { return m_Mat; };
	bool CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, float& _range)const;


private:
	KdModel m_Model;

	Math::Matrix m_Mat = {};
	
	float m_SinAng = 0;
	float alpha;
	bool sinkflg;
};