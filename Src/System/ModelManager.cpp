#include"ModelManager.h"

KdModel* ModelManager::GetModel(std::string _fileName)
{

	KdModel* tmpModel;

	if (m_ModelList.find(_fileName) == m_ModelList.end())
	{
		//map�N���X�̒���T�������A�Y���̃t�@�C�����͌�����Ȃ�����

		//���f�����̃������m��
		tmpModel = new KdModel();
		//�Y���̃t�@�C�������[�h
		tmpModel->Load(_fileName);

		//�t�@�C�������L�[�Ƃ��ăA�h���X��map�ɕۑ�����
		m_ModelList[_fileName] = tmpModel;
	}
	else
	{
		tmpModel = m_ModelList[_fileName];
	}

	return tmpModel;

}

ModelManager::~ModelManager()
{

	//�C�e���[�^�[�i����ł���f�[�^�̊Ǘ��l�݂����Ȃ��́j
	//std::map<std::string, KdTexture*>::iterator itr;
	//itr = m_textureList.begin();5
	//�^�ʖڂɋL�q����Ə�L�̂悤�ɂȂ邪
	//������Ă�����e����^���������ʂ���^���_(auto)���g��

	//�ۑ�����Ă���S���ڂ�����Release����
	for (auto itr = m_ModelList.begin(); itr != m_ModelList.end(); ++itr)
	{
		//�e���ڂ̍���(�t�@�C����) ==itr->first
		//�e���ڂ̉E��(�A�h���X) ==itr->second

		(itr->second)->Release();

		delete (itr->second);
	}

	//���X�g���̂��̂��폜
	m_ModelList.clear();

}