#pragma once
#include"System/ModelManager.h"

class C_faucet
{
public:
	C_faucet(std::shared_ptr<ModelManager>& _om, const Math::Vector3& _pos);
	void Draw();
	void Update();
	//透明化処理
	void AlphaSet(float& _alpha);
	bool CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _returnVec, float& _range)const;
	const Math::Vector3& GetPos(void) { return m_FaucetMat.Translation(); };


private:
	KdModel* m_Faucet;
	KdModel* m_Sink;
	KdModel* m_Waterfall;

	Math::Matrix m_FaucetMat = {};
	Math::Matrix m_Sinkmat = {};
	Math::Matrix m_Waterfmat = {};
	
	Math::Vector2 m_uvOffset = { 0,0 };//テクスチャのずらし具合
	
	bool open;
	float alpha;
	float scale_value;
};