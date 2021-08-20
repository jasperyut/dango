#pragma once
#include"System/ModelManager.h"

class C_can
{
public:
	C_can(std::shared_ptr<ModelManager>& _om, const Math::Vector3& _pos);
	bool CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _returnVec, float& _range)const;
	const Math::Matrix& GetMat() { return m_Mat; }
	void Draw();
	void Update();
	//透明化処理
	void AlphaSet(float& _alpha);
	//アウトライン設定
	void OutLine();


private:
	KdModel* m_Model[2];

	Math::Matrix m_Mat = {};
	Math::Vector3 m_Pos = {};
	
	float range = 6.0f;
	float alpha;
	bool OutlineFlg;
	float m_hitDis = {};
	float btrng=0.2f;
};
