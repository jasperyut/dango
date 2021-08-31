#include "System/KdSystem.h"

#include "KdCubeMapGenerator.h"

void KdCubeMapGenerator::Generate(int size, const Math::Vector3& position, std::function<void()> drawProc)
{
	//----------------------------------
	// RTとZバッファを作成
	//----------------------------------
	{
		// 作成する2Dテクスチャ設定
		D3D11_TEXTURE2D_DESC desc = {};

		desc.Width = (UINT)size;
		desc.Height = (UINT)size;
		desc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
		desc.ArraySize = 6;
		desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE |	// キューブマップ
			D3D11_RESOURCE_MISC_GENERATE_MIPS;	// Mipmap生成

		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		desc.CPUAccessFlags = 0;
		desc.MipLevels = 0;				// 完全なミップマップチェーン
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;

		m_cubeMap = std::make_shared<KdTexture>();
		m_cubeMap->Create(desc);

		m_zBuffer = std::make_shared<KdTexture>();
		m_zBuffer->Create(size, size);
	}

	//----------------------------------
	// RT、Z、VPの変更
	//----------------------------------
	// 現在のRTとZとVPを取得しておく
	ID3D11RenderTargetView* saveRTV[8] = {};
	ID3D11DepthStencilView* saveDSV = nullptr;
	D3D.GetDevContext()->OMGetRenderTargets(8, saveRTV, &saveDSV);
	D3D11_VIEWPORT saveVP;
	UINT numVPs = 1;
	D3D.GetDevContext()->RSGetViewports(&numVPs, &saveVP);

	// Viewportを変更
	D3D11_VIEWPORT vp = { 0, 0, (float)size, (float)size, 0, 1 };
	D3D.GetDevContext()->RSSetViewports(1, &vp);

	// RTのリソースを取得
	ID3D11Resource* cubeMapResource = nullptr;
	m_cubeMap->GetRTView()->GetResource(&cubeMapResource);

	// カメラ
	KdCamera camera;
	camera.SetProjectionMatrix(90, 2000, 0.01f, 1.0f);

	// キューブマップの各面(6枚)を描画
	for (int i = 0; i < 6; i++)
	{
		// キューブマップの各画像へのビューを作成
		ID3D11RenderTargetView* rtv = nullptr;
		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		rtvDesc.Format = m_cubeMap->GetInfo().Format;	// Format
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
		rtvDesc.Texture2DArray.ArraySize = 1;
		rtvDesc.Texture2DArray.FirstArraySlice = i;
		rtvDesc.Texture2DArray.MipSlice = 0;
		// レンダーターゲットビュー作成
		HRESULT hr = D3D.GetDev()->CreateRenderTargetView(cubeMapResource, &rtvDesc, &rtv);
		if (FAILED(hr))
		{
			assert(0 && "RenderTargetViewの作成に失敗");
		}

		// RT、Zクリア
		D3D.GetDevContext()->ClearRenderTargetView(rtv, Math::Color(0, 0, 0, 1));
		D3D.GetDevContext()->ClearDepthStencilView(m_zBuffer->GetDSView(), D3D11_CLEAR_DEPTH, 1, 0);

		// RTとZを変更する
		D3D.GetDevContext()->OMSetRenderTargets(1, &rtv, m_zBuffer->GetDSView());

		// カメラ設定
		Math::Matrix mView;
		switch (i)
		{
		case D3D11_TEXTURECUBE_FACE_POSITIVE_X:
			mView = DirectX::XMMatrixLookAtLH(position, position + Math::Vector3(1, 0, 0), Math::Vector3(0, 1, 0));
			break;
		case D3D11_TEXTURECUBE_FACE_NEGATIVE_X:
			mView = DirectX::XMMatrixLookAtLH(position, position + Math::Vector3(-1, 0, 0), Math::Vector3(0, 1, 0));
			break;
		case D3D11_TEXTURECUBE_FACE_POSITIVE_Y:
			mView = DirectX::XMMatrixLookAtLH(position, position + Math::Vector3(0, 1, 0), Math::Vector3(0, 0, -1));
			break;
		case D3D11_TEXTURECUBE_FACE_NEGATIVE_Y:
			mView = DirectX::XMMatrixLookAtLH(position, position + Math::Vector3(0, -1, 0), Math::Vector3(0, 0, 1));
			break;
		case D3D11_TEXTURECUBE_FACE_POSITIVE_Z:
			mView = DirectX::XMMatrixLookAtLH(position, position + Math::Vector3(0, 0, 1), Math::Vector3(0, 1, 0));
			break;
		case D3D11_TEXTURECUBE_FACE_NEGATIVE_Z:
			mView = DirectX::XMMatrixLookAtLH(position, position + Math::Vector3(0, 0, -1), Math::Vector3(0, 1, 0));
			break;
		}
		camera.SetCameraMatrix(mView.Invert());
		camera.SetToShader();

		// 描画実行
		drawProc();

		rtv->Release();
	}

	// RTとZを元に戻す
	D3D.GetDevContext()->OMSetRenderTargets(8, saveRTV, saveDSV);
	for (auto&& rtv : saveRTV)
	{
		KdSafeRelease(rtv);
	}
	KdSafeRelease(saveDSV);

	// Viewportを元に戻す
	D3D.GetDevContext()->RSSetViewports(numVPs, &saveVP);

	// 取得したリソースの参照カウンターを減らす
	cubeMapResource->Release();

	// ミップマップの生成
	D3D.GetDevContext()->GenerateMips(m_cubeMap->GetSRView());
}

void KdCubeMapGenerator::LoadFromFile(const std::string& filename)
{
	m_cubeMap = std::make_shared<KdTexture>();
	m_cubeMap->Load(filename);
}

void KdCubeMapGenerator::SaveToFile(const std::string& filename)
{
	if (m_cubeMap == nullptr)return;

	ID3D11Resource* cubeMapResource = nullptr;
	m_cubeMap->GetRTView()->GetResource(&cubeMapResource);
	cubeMapResource->Release();

	HRESULT hr;
	DirectX::ScratchImage image;
	hr = DirectX::CaptureTexture(
		D3D.GetDev(),
		D3D.GetDevContext(),
		cubeMapResource,
		image
	);
	if (FAILED(hr))
	{
		return;
	}


	hr = DirectX::SaveToDDSFile(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::DDS_FLAGS_NONE, sjis_to_wide(filename).c_str());
	if (FAILED(hr))
	{
		return;
	}

}
