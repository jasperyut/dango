#pragma once
#include"System/ModelManager.h"

class C_elevator
{
public:
	C_elevator(std::shared_ptr<ModelManager>& _om, const Math::Vector3& _pos);
	void Draw();
	void Update();
	bool CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _returnVec, float& _range)const;

private:
	KdModel* m_Elevator;
	KdModel* m_Aura[3];
	Math::Matrix m_Mat;
	Math::Vector3 m_Pos;
	float range;
	bool Wswitch, Pswitch, Gswitch;
	bool actived;
	int process;
};
