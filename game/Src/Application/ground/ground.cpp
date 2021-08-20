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


	D3D11_SUBRESOURCE_DATA srd = {}; //中身にすべてゼロを入る
	srd.pSysMem = &m_v[0];	//頂点データが入っている先頭アドレス
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


	//頂点バッファをセット
	UINT stride = sizeof(Vertex);    //頂点ひとつあたりのバイトサイズ(Vector3+Vector2+Vector4(float型×9個))
	UINT offset = 0;    //オフセット
	D3D.GetDevContext()->IASetVertexBuffers(0, 1, m_Vb.GetAddress(), &stride, &offset);

	//プリミティブトポロジー（頂点の利用法）をセット
	D3D.GetDevContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//テクスチャをセット
	D3D.GetDevContext()->PSSetShaderResources(0, 1, m_Tex.GetSRViewAddress());
	//描画
	//今後使って欲しい行列をセット

	SHADER.m_effectShader.SetWorldMatrix(m_Mat);
	SHADER.m_effectShader.WriteToCB();//今まで設定した内容を反映
	D3D.GetDevContext()->Draw(4, 0);
}