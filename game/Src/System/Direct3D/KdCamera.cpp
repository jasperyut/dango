#include "KdCamera.h"

// �ˉe�s��̐ݒ�
void KdCamera::SetProjectionMatrix(float fov, float maxRange, float minRange, float aspectRatio)
{
	m_mProj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fov), aspectRatio, minRange, maxRange);

	m_dirtyProj = true;
}

// �J�����s��E�r���[�s��Z�b�g
void KdCamera::SetCameraMatrix(const DirectX::SimpleMath::Matrix& mCam)
{
	// �J�����s��Z�b�g
	m_mCam = mCam;

	// �J�����ύX�t���OON
	m_dirtyCam = true;
}

// �J�������(�r���[�E�ˉe�s��Ȃ�)���V�F�[�_�փZ�b�g
void KdCamera::SetToShader()
{
	// �J�������ύX����Ă���΍X�V
	if (m_dirtyCam)
	{
		// �J�����s�񂩂�r���[�s����Z�o
		m_mView = m_mCam.Invert();
		/*
		// �J�������W���Z�b�g
		SHADER->m_cb7_Camera.Work().CamPos = m_mCam.Translation();
		// �r���[�s����Z�b�g
		SHADER->m_cb7_Camera.Work().mView = m_mView;
		*/
	}
	// �J�������W���Z�b�g
	SHADER.m_cb7_Camera.Work().CamPos = m_mCam.Translation();
	// �r���[�s����Z�b�g
	SHADER.m_cb7_Camera.Work().mV = m_mView;

	/*
	// �ˉe�s�񂪕ύX����Ă���΍X�V
	if (m_dirtyProj)
	{
		// �ˉe�s����Z�b�g
		SHADER->m_cb7_Camera.Work().mProj = m_mProj;
	}
	*/
	// �ˉe�s����Z�b�g
	SHADER.m_cb7_Camera.Work().mP = m_mProj;

	/*
	// �ύX������Ώ�������
	if (m_dirtyCam || m_dirtyProj)
	{
		// �J�������(�r���[�s��A�ˉe�s��)���A�V�F�[�_�̒萔�o�b�t�@�֏�������
		SHADER->m_cb7_Camera.Write();

		m_dirtyCam  = false;
		m_dirtyProj = false;
	}
	*/
	// �J�������(�r���[�s��A�ˉe�s��)���A�V�F�[�_�̒萔�o�b�t�@�֏�������
	SHADER.m_cb7_Camera.Write();
}

DirectX::SimpleMath::Matrix& KdCamera::WorkCamera()
{
	// �J�����ύX�t���OON
	m_dirtyCam = true;

	// �X�V�\�ȃJ�����s���Ԃ�
	return m_mCam;
}

void KdCamera::ConvertWorldToScreen(const Math::Vector3& pos, const Math::Matrix matrix, float& resultX, float& resultY)
{
	// �r���[�|�[�g���擾����
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