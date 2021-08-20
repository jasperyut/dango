#pragma once
class C_Backitem
{
public:
	C_Backitem();
	~C_Backitem();
	void Draw();

private:
	KdModel m_Model;

	Math::Matrix m_Mat = {};
};

