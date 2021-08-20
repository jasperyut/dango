#pragma once
#include"System/ModelManager.h"

class C_button
{
public:
	C_button(std::shared_ptr<ModelManager>& _om, const Math::Vector3& _pos);
	void Draw();
	void Update();
	bool CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _returnVec, float& _range)const;
	const Math::Vector3& GetPos(void) { return m_Mat.Translation(); };

private:
	KdModel* m_Model;
	KdModel* m_Button[3] = {};

	Math::Matrix m_Mat = {};

	float range = 0.5f;
	int buttontime;
	bool active;
	bool occupy;
};
