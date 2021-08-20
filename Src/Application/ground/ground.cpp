#include "ground.h"
#include"./Application/define.h"

C_ground::C_ground()
{
	m_Tex.Load("Data/Texture/ground.png");

	m_v[0].pos = { -200,0,200 };
	m_v[1].pos = { 200,0,200 };
	m_v[2].pos = { -200,0,-200 };
	m_v[3].pos = { 200,0,-200 };

	m_v[0].color = { 1,1,1,1 };//R.G.B.Alpha
	m_v[1].color = { 1,1,1,1 };
	m_v[2].color = { 1,1,1,1 };
	m_v[3].color = { 1,1,1,1 };

	m_v[0].uv = { 0.0f,  0.0f };
	m_v[1].uv = { 16.0f,  0.0f };
	m_v[2].uv = { 0.0f,  16.0f };
	m_v[3].uv = { 16.0f,  16.0f };


	D3D11_SUBRESOURCE_DATA srd = {}; //���g�ɂ��ׂă[�������
	srd.pSysMem = &m_v[0];	//���_�f�[�^�������Ă���擪�A�h���X
	m_Vb.Create(D3D11_BIND_VERTEX_BUFFER, sizeof(m_v), D3D11_USAGE_DEFAULT, &srd);

	m_Mat = DirectX::XMMatrixTranslation(10, -1, 10);

}
C_ground::~C_ground()
{
	m_Tex.Release();
	m_Vb.Release();
}
void C_ground::Draw()
{


	//���_�o�b�t�@���Z�b�g
	UINT stride = sizeof(Vertex);    //���_�ЂƂ�����̃o�C�g�T�C�Y(Vector3+Vector2+Vector4(float�^�~9��))
	UINT offset = 0;    //�I�t�Z�b�g
	D3D.GetDevContext()->IASetVertexBuffers(0, 1, m_Vb.GetAddress(), &stride, &offset);

	//�v���~�e�B�u�g�|���W�[�i���_�̗��p�@�j���Z�b�g
	D3D.GetDevContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�e�N�X�`�����Z�b�g
	D3D.GetDevContext()->PSSetShaderResources(0, 1, m_Tex.GetSRViewAddress());
	//�`��
	//����g���ė~�����s����Z�b�g

	SHADER.m_effectShader.SetWorldMatrix(m_Mat);
	SHADER.m_effectShader.WriteToCB();//���܂Őݒ肵�����e�𔽉f
	D3D.GetDevContext()->Draw(4, 0);
}