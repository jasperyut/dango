#pragma once
//�p�^�[���ϊ����鎞��2D�\��
class C_icon
{
public:
	C_icon();
	~C_icon();
	void Draw(int _flg);
	void Update();

private:
	KdTexture m_State[3];
	KdTexture m_MouseClick;

	Math::Matrix m_Mat[3] = {};
	Math::Matrix click_mat;
	float alpha;
};