#pragma once

//====================================================
//
// �L���[�u�}�b�v����
//
//====================================================
class KdCubeMapGenerator
{
public:

	// �������ꂽ�L���[�u�}�b�v�擾
	std::shared_ptr<KdTexture> GetCubeMap() const { return m_cubeMap; }

	// �w��T�C�Y�̃L���[�u�}�b�v�𐶐����A���i��`�悷��B
	// size		�F�L���[�u�}�b�v�e�N�X�`���̃T�C�Y�B
	// position	�F�B�e���郏�[���h���W�B
	// drawProc	�F���s����`��֐��B
	void Generate(int size, const Math::Vector3& position, std::function<void()> drawProc);

	// �t�@�C������ǂݍ���
	void LoadFromFile(const std::string& filename);

	// �t�@�C���֕ۑ�����
	void SaveToFile(const std::string& filename);

private:
	// �L���[�u�}�b�v
	std::shared_ptr<KdTexture> m_cubeMap;
	// �`�掞�Ɏg�p����Z�o�b�t�@
	std::shared_ptr<KdTexture> m_zBuffer;
};
