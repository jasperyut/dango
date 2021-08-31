#include "KdCamera.h"

// 射影行列の設定
void KdCamera::SetProjectionMatrix(float fov, float maxRange, float minRange, float aspectRatio)
{
	m_mProj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fov), aspectRatio, minRange, maxRange);

	m_dirtyProj = true;
}

// カメラ行列・ビュー行列セット
void KdCamera::SetCameraMatrix(const DirectX::SimpleMath::Matrix& mCam)
{
	// カメラ行列セット
	m_mCam = mCam;

	// カメラ変更フラグON
	m_dirtyCam = true;
}

// カメラ情報(ビュー・射影行列など)をシェーダへセット
void KdCamera::SetToShader()
{
	// カメラが変更されていれば更新
	if (m_dirtyCam)
	{
		// カメラ行列からビュー行列を算出
		m_mView = m_mCam.Invert();
		/*
		// カメラ座標をセット
		SHADER->m_cb7_Camera.Work().CamPos = m_mCam.Translation();
		// ビュー行列をセット
		SHADER->m_cb7_Camera.Work().mView = m_mView;
		*/
	}
	// カメラ座標をセット
	SHADER.m_cb7_Camera.Work().CamPos = m_mCam.Translation();
	// ビュー行列をセット
	SHADER.m_cb7_Camera.Work().mV = m_mView;

	/*
	// 射影行列が変更されていれば更新
	if (m_dirtyProj)
	{
		// 射影行列をセット
		SHADER->m_cb7_Camera.Work().mProj = m_mProj;
	}
	*/
	// 射影行列をセット
	SHADER.m_cb7_Camera.Work().mP = m_mProj;

	/*
	// 変更があれば書き込み
	if (m_dirtyCam || m_dirtyProj)
	{
		// カメラ情報(ビュー行列、射影行列)を、シェーダの定数バッファへ書き込む
		SHADER->m_cb7_Camera.Write();

		m_dirtyCam  = false;
		m_dirtyProj = false;
	}
	*/
	// カメラ情報(ビュー行列、射影行列)を、シェーダの定数バッファへ書き込む
	SHADER.m_cb7_Camera.Write();
}

DirectX::SimpleMath::Matrix& KdCamera::WorkCamera()
{
	// カメラ変更フラグON
	m_dirtyCam = true;

	// 更新可能なカメラ行列を返す
	return m_mCam;
}

void KdCamera::ConvertWorldToScreen(const Math::Vector3& pos, const Math::Matrix matrix, float& resultX, float& resultY)
{
	// ビューポートを取得する
	Math::Viewport vp;
	D3D.GetViewport(vp);
	const float HalfViewportWidth = vp.width * 0.5f;
	const float HalfViewportHeight = vp.height * 0.5f;

	Math::Vector3 Scale = DirectX::XMVectorSet(HalfViewportWidth, -HalfViewportHeight, vp.maxDepth - vp.minDepth, 0.0f);
	Math::Vector3 Offset = DirectX::XMVectorSet(vp.x + HalfViewportWidth, vp.y + HalfViewportHeight, vp.minDepth, 0.0f);

	Math::Matrix Transform = DirectX::XMMatrixMultiply(matrix, GetViewMatrix());
	Transform = XMMatrixMultiply(Transform, GetProjMatrix());

	Math::Vector3 Pos = { GetCameraMatrix()._41,GetCameraMatrix()._42 ,GetCameraMatrix()._43 };
	Math::Vector3 Result = XMVector3TransformCoord(pos, Transform);

	Result = XMVectorMultiplyAdd(Result, Scale, Offset);

	resultX = Result.x;
	resultY = Result.y;

	/*
		const float HalfViewportWidth = ViewportWidth * 0.5f;
		const float HalfViewportHeight = ViewportHeight * 0.5f;

		XMVECTOR Scale = XMVectorSet(HalfViewportWidth, -HalfViewportHeight, ViewportMaxZ - ViewportMinZ, 0.0f);
		XMVECTOR Offset = XMVectorSet(ViewportX + HalfViewportWidth, ViewportY + HalfViewportHeight, ViewportMinZ, 0.0f);

		XMMATRIX Transform = XMMatrixMultiply(World, View);
		Transform = XMMatrixMultiply(Transform, Projection);

		XMVECTOR Result = XMVector3TransformCoord(V, Transform);

		Result = XMVectorMultiplyAdd(Result, Scale, Offset);
	*/
}