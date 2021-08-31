#pragma once

//=========================================
// �J�����N���X
//=========================================
class KdCamera
{
public:
	// �R���X�g���N�^�[�@�I�[�i�[�̐ݒ�Ǝˉe�s��̍쐬
	KdCamera() {}

	~KdCamera() {}

	void SetProjectionMatrix(
		float fov,
		float maxRange = 2000.0f,
		float minRange = 0.01f,
		float aspectRatio = D3D.GetBackBuffer()->GetAspectRatio());

	void SetProjectionMatrix(const Math::Matrix& rProj) { m_mProj = rProj; m_dirtyProj = true; }

	// �J�����s��擾
	inline const Math::Matrix& GetCameraMatrix() const { return m_mCam; }

	// �r���[�s��擾
	inline const Math::Matrix& GetViewMatrix() const { return m_mView; }

	// �ˉe�s��擾
	inline const Math::Matrix& GetProjMatrix() const { return m_mProj; }

	// �J�����s��E�r���[�s��
	virtual void SetCameraMatrix(const Math::Matrix& mCam);

	// ���[���h���W���X�N���[�����W�ɕϊ�
	void ConvertWorldToScreen(const Math::Vector3& pos, const Math::Matrix matrix, float& resultX, float& resultY);

	// �J�������(�r���[�E�ˉe�s��Ȃ�)���V�F�[�_�փZ�b�g
	void SetToShader();

	const Math::Matrix&  GetCamera()const { m_mCam; }

	Math::Matrix& WorkCamera();

protected:

	// �J�����s��
	Math::Matrix	m_mCam;
	// �r���[�s��
	Math::Matrix	m_mView;
	// �ˉe�s��
	Math::Matrix	m_mProj;

private:
	bool m_dirtyCam = false;
	bool m_dirtyProj = false;
};
