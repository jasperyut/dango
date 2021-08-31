#pragma once

//=========================================
// カメラクラス
//=========================================
class KdCamera
{
public:
	// コンストラクター　オーナーの設定と射影行列の作成
	KdCamera() {}

	~KdCamera() {}

	void SetProjectionMatrix(
		float fov,
		float maxRange = 2000.0f,
		float minRange = 0.01f,
		float aspectRatio = D3D.GetBackBuffer()->GetAspectRatio());

	void SetProjectionMatrix(const Math::Matrix& rProj) { m_mProj = rProj; m_dirtyProj = true; }

	// カメラ行列取得
	inline const Math::Matrix& GetCameraMatrix() const { return m_mCam; }

	// ビュー行列取得
	inline const Math::Matrix& GetViewMatrix() const { return m_mView; }

	// 射影行列取得
	inline const Math::Matrix& GetProjMatrix() const { return m_mProj; }

	// カメラ行列・ビュー行列
	virtual void SetCameraMatrix(const Math::Matrix& mCam);

	// ワールド座標をスクリーン座標に変換
	void ConvertWorldToScreen(const Math::Vector3& pos, const Math::Matrix matrix, float& resultX, float& resultY);

	// カメラ情報(ビュー・射影行列など)をシェーダへセット
	void SetToShader();

	const Math::Matrix&  GetCamera()const { m_mCam; }

	Math::Matrix& WorkCamera();

protected:

	// カメラ行列
	Math::Matrix	m_mCam;
	// ビュー行列
	Math::Matrix	m_mView;
	// 射影行列
	Math::Matrix	m_mProj;

private:
	bool m_dirtyCam = false;
	bool m_dirtyProj = false;
};
