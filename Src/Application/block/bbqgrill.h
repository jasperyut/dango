#pragma once
#include"System/ModelManager.h"


class C_BBQgrill
{
public:
	C_BBQgrill(std::shared_ptr<ModelManager>& _om, const Math::Vector3& _pos);
	void Draw();
	void Update();
	//ìßñæâªèàóù
	void AlphaSet(float& _alpha);
	bool CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _returnVec, float& _range)const;
	const Math::Vector3& GetPos(void) { return m_Mat.Translation(); };

private:
	KdModel* m_Model;
	KdModel* m_Gravity;

	Math::Matrix m_Mat = {};
	Math::Matrix g_Mat = {};

	float range = 5.0f;
	float alpha;
};
