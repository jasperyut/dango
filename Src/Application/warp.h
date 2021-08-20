#pragma once
class C_Warp
{
public:
	C_Warp();
	~C_Warp();
	void Draw();
	void Update();
	const float& GetRange()const { return range; };
	const Math::Matrix& GetMat()const { return m_Mat; };

private:
	KdModel m_Model;

	Math::Matrix m_Mat = {};

	float range = 3.0f;
};
