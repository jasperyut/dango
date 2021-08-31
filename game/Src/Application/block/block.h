#pragma once
#include"System/ModelManager.h"

class C_block
{
public:
	C_block(std::shared_ptr<ModelManager>& _om, const Math::Vector3& _pos);
	void Draw();
	void Update();
	//ìßñæâªèàóù
	void AlphaSet(float& _alpha);
	bool CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _returnVec, float& _range)const;

private:
	KdModel* m_Model;

	Math::Matrix m_Mat = {};
	Math::Vector3 m_Pos;
	float range=5.0f;
	float alpha;
	float m_SinAng=0;
	bool a;
	bool movestart;
	float movespeed;
};