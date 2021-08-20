#pragma once
#include"Application/define.h"


class C_Smoke
{
public:
	C_Smoke() {};
	C_Smoke(const Math::Vector3& _pos);
	~C_Smoke();
	bool Update();
	void Draw();



private:
	KdBuffer m_Vb;		// ���_�o�b�t�@
	KdTexture m_Tex;	// �e�N�X�`��


	Math::Matrix m_Mat = {};	// �s��
	Vertex v[4] = {};
	Math::Matrix m_Trans = {};
	Math::Matrix m_Rot = {};
	Math::Matrix m_Scale = {};
	Math::Matrix m_Move = {};
	Math::Vector3 m_Pos = {};
	Math::Vector3 m_MoveVec = {};

	float alpha;
};