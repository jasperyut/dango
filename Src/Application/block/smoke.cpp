#include"smoke.h"


C_Smoke::C_Smoke(const Math::Vector3& _pos)
{
	m_Tex.Load("Data/Texture/smoke.png");

	alpha = 1.0f;

	v[0].pos = { -2.0f, 2.0f,  0.0f };
	v[1].pos = { 2.0f, 2.0f,  0.0f };
	v[2].pos = { -2.0f, -2.0f, 0.0f };
	v[3].pos = { 2.0f, -2.0f, 0.0f };




	v[0].uv = { 0,0 };
	v[1].uv = { 1,0 };
	v[2].uv = { 0,1 };
	v[3].uv = { 1,1 };



	D3D11_SUBRESOURCE_DATA srd = {};
	srd.pSysMem = &v[0];//書き込むテータの先頭アドレス
	m_Vb.Create(D3D11_BIND_VERTEX_BUFFER, sizeof(v), D3D11_USAGE_DEFAULT, &srd);

	// 行列
	m_Mat = DirectX::XMMatrixIdentity();

	m_Trans = DirectX::XMMatrixTranslation(_pos.x, _pos.y, _pos.z);
}

C_Smoke::~C_Smoke()
{
	m_Vb.Release();
	m_Tex.Release();
}


bool C_Smoke::Update()
{

	v[0].color = { 1,1,1,alpha };
	v[1].color = { 1,1,1,alpha };
	v[2].color = { 1,1,1,alpha };
	v[3].color = { 1,1,1,alpha };


	D3D11_SUBRESOURCE_DATA srd = {};
	srd.pSysMem = &v[0];//書き込むテータの先頭アドレス
	m_Vb.Create(D3D11_BIND_VERTEX_BUFFER, sizeof(v), D3D11_USAGE_DEFAULT, &srd);

	alpha -= 0.005f;
	m_Rot = SHADER.m_cb7_Camera.Work().mV;
	m_Rot._41 = 0.0f;
	m_Rot._42 = 0.0f;
	m_Rot._43 = 0.0f;

	m_Pos += Math::Vector3(0.0f, 0.05f, 0.0f);
	m_Move = DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);

	//逆行列にする
	m_Rot = m_Rot.Invert();
	m_Mat = m_Rot * m_Trans * m_Move;

	//煙は一定アルファ値以下となると
	if (alpha <= 0.01f)
	{
		return false;
	}


	return true;

}

void C_Smoke::Draw()
{
	//板ポリゴン用のシェーダーをセット
	SHADER.m_effectShader.SetToDevice();

	//頂点バッファをセット
	UINT stride = sizeof(Vertex);    //頂点ひとつあたりのバイトサイズ(Vector3+Vector2+Vector4(float型×9個))
	UINT offset = 0;    //オフセット
	D3D.GetDevContext()->IASetVertexBuffers(0, 1, m_Vb.GetAddress(), &stride, &offset);

	//プリミティブトポロジー（頂点の利用法）をセット
	D3D.GetDevContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャをセット
	D3D.GetDevContext()->PSSetShaderResources(0, 1, m_Tex.GetSRViewAddress());


	//描画
	SHADER.m_effectShader.SetWorldMatrix(m_Mat);
	SHADER.m_effectShader.WriteToCB();
	D3D.GetDevContext()->Draw(4, 0);
}