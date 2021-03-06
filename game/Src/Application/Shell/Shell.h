#pragma once
//移動できる範囲を設定するために使っている外殻
class C_Shell
{
public:
	C_Shell();
	~C_Shell();
	void Draw();
	void Update();
	bool C_Shell::CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _returnVec, float& _range) const;
	const Math::Vector3& GetPos(void) { return m_Mat.Translation(); };
	const float GetRange() { return range; };

private:
	KdModel	m_Model;
	Math::Matrix m_Mat;
	float range = 5.0f;


};
