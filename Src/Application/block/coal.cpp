#include "coal.h"
#include"Application/ModelIntersects.h"
#include"Application/Game.h"


C_coal::C_coal(const Math::Vector3& _pos)
{
	srand(timeGetTime());


	m_Tex.Load("Data/Texture/fire.png");

	for (int z = 0; z < 11; z++)
	{
		for (int x = 0; x < 11; x++)
		{
			height[z][x] = (float)(rand() % 90) / 100.0f;
		}
	}
	flashing = 10.0f;
	alpha = 1.0f;

	m_Mat = DirectX::XMMatrixTranslation(_pos.x, _pos.y, _pos.z);
	m_Lightmat = DirectX::XMMatrixTranslation(_pos.x + 3.5f, _pos.y + 8.0f, _pos.z + 3.5f);

	SHADER.AddPointLight(Math::Vector3(0.0f, 0.0f, 0.0f), m_Lightmat.Translation(), 20);



}

C_coal::~C_coal()
{
	m_Tex.Release();
	m_Vb.Release();
	SHADER.m_cb8_Light.Work().PL_Num = 0;
}


Math::Vector3 C_coal::GetPanelPos(int _noX, int _noZ)const
{
	Math::Vector3 pos;

	pos.x = _noX * 10.0f;
	pos.y = height[_noZ][_noX];
	pos.z = _noZ * 10.0f;

	return pos;
}


void C_coal::Draw()
{
	if (SYSTEM.Getstagecam() == false && Chroma > 0.4)
	{
		for (int i = 0; i < 3; i++)
		{
			SHADER.m_cb8_Light.Work().PL[i].color = { flashing, flashing * 0.2f, 0.0f };

		}
	}




	m_Vb.Create(D3D11_BIND_VERTEX_BUFFER, sizeof(v), D3D11_USAGE_DEFAULT, nullptr);

	if (SYSTEM.GetnowStage() <= 3)
	{
		AlphaSet(alpha);
	}
	for (int z = 0; z < 10; z++)
	{
		for (int x = 0; x < 11; x++) {
			v[z][x][0].pos = { 1.4f * x,height[z + 0][x],1.4f * (z + 0) };
			v[z][x][1].pos = { 1.4f * x,height[z + 1][x],1.4f * (z + 1) };

			v[z][x][0].color = { Chroma,Chroma,Chroma,alpha };//R.G.B.Alpha
			v[z][x][1].color = { Chroma,Chroma,Chroma,alpha };


			v[z][x][0].uv = { (float)(z + 0) / 25.0f ,(float)x / 25.0f };
			v[z][x][1].uv = { (float)(z + 1) / 25.0f ,(float)x / 25.0f };

		}
	}
	m_Vb.WriteData(&v[0], sizeof(v));

	UINT stride = sizeof(Vertex);    //頂点ひとつあたりのバイトサイズ(Vector3+Vector2+Vector4(float型×9個))
	UINT offset = 0;    //オフセット
	D3D.GetDevContext()->IASetVertexBuffers(0, 1, m_Vb.GetAddress(), &stride, &offset);

	//プリミティブトポロジー（頂点の利用法）をセット
	D3D.GetDevContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	D3D.GetDevContext()->PSSetShaderResources(0, 1, m_Tex.GetSRViewAddress());
	//描画
	//今後使って欲しい行列をセット

	SHADER.m_effectShader.SetWorldMatrix(m_Mat);
	SHADER.m_effectShader.WriteToCB();//今まで設定した内容を反映
	for (int z = 0; z < 10; z++)
	{
		D3D.GetDevContext()->Draw(22, z * 22);
	}
	D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, true), 0);
}

void C_coal::Update()
{

	flashing = (rand() % 50000 + 20000) * 0.0001f;

	if (SYSTEM.GetnowStage() == 3)
	{
		if (SYSTEM.Getstagecam() == true)
		{
			Chroma += 0.01f;
		}
		if (SYSTEM.Getstagecam() == false && Chroma > 0.4)
		{
			Chroma = (rand() % 50000 + 50000) * 0.00001f;
		}
	}
	else
	{
		Chroma = (rand() % 50000 + 50000) * 0.00001f;
	}
}

void C_coal::AlphaSet(float& _alpha)
{
	GameScene* game;
	game = dynamic_cast<GameScene*>(SYSTEM.GetSceneManager().GetnowScene());
	Math::Vector3 ShortVec;
	ShortVec = m_Lightmat.Translation() - game->GetPos();
	ShortVec.Normalize();
	Math::Vector3 Dot;
	Dot = DirectX::XMVector3Dot(ShortVec, game->GetcamVec());
	float angX;
	angX = DirectX::XMConvertToDegrees(acos(Dot.x));
	

	if (angX< 60)
	{

		_alpha -= 0.05f;
		if (_alpha <= 0.2f)
		{
			_alpha = 0.2f;
		}
		D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, false), 0);
	}
	else
	{
		_alpha += 0.05f;
		if (_alpha >= 1.0f)
		{
			_alpha = 1.0f;
		}
		D3D.GetDevContext()->OMSetDepthStencilState(D3D.CreateDepthStencilState(true, true), 0);
	}
}
