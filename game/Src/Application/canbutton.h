#pragma once


class C_canbt
{
public:
	C_canbt();
	~C_canbt();
	void Draw();
	void Update();
	const Math::Matrix& GetMat()const { return m_Mat; };
	
private:
	KdModel m_Shell;
	KdModel m_Inside;

	Math::Matrix m_Mat = {};

	float range;
	bool actived;

	
};