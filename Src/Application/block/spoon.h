#pragma once
#include"System/ModelManager.h"

class C_spoon
{
public:
	C_spoon(std::shared_ptr<ModelManager>& _om, const Math::Vector3& _pos);
	void Draw();
	void Update();
	bool CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _returnVec, float& _range)const;
	//アウトライン設定
	void OutLine();
	

private:
	KdModel* m_Spoon[2];
	KdModel* m_Dango;
	KdModel* m_Shell;
	
	
	Math::Matrix m_SpoonMat = {};
	Math::Matrix m_DangoMat = {};
	Math::Matrix m_DangoTrans = {};
	Math::Matrix m_SpoonTrans = {};
	Math::Matrix m_RotY = {};
	Math::Matrix m_RotZ = {};
	
	Math::Vector3 m_DangoPos = {};
	Math::Vector3 LookVec;

	float gravity = {};
	float ang;
	float d_ang;
	float Inertia;
	float m_hitDis = {};
	float range = 1.8f;
	float m_camAngY;
	int waterwaittime;
	bool waittimeover;
	bool usedFlg;
	bool checkout;
	bool sound;
	bool OutlineFlg;
};