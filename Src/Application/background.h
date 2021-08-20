#pragma once
class C_Background
{
public:
	C_Background();
	~C_Background();
	void Draw();

private:

	KdModel m_Model;

	Math::Matrix m_Mat = {};
	Math::Matrix m_Scale = {};
};


