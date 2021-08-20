#include"ModelManager.h"

KdModel* ModelManager::GetModel(std::string _fileName)
{

	KdModel* tmpModel;

	if (m_ModelList.find(_fileName) == m_ModelList.end())
	{
		//mapクラスの中を探したが、該当のファイル名は見つからなかった

		//モデル分のメモリ確保
		tmpModel = new KdModel();
		//該当のファイルをロード
		tmpModel->Load(_fileName);

		//ファイル名をキーとしてアドレスをmapに保存する
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

	//イテレーター（並んでいるデータの管理人みたいなもの）
	//std::map<std::string, KdTexture*>::iterator itr;
	//itr = m_textureList.begin();5
	//真面目に記述すると上記のようになるが
	//代入している内容から型を自動判別する型推論(auto)を使う

	//保存されている全項目を順にReleaseする
	for (auto itr = m_ModelList.begin(); itr != m_ModelList.end(); ++itr)
	{
		//各項目の左側(ファイル名) ==itr->first
		//各項目の右側(アドレス) ==itr->second

		(itr->second)->Release();

		delete (itr->second);
	}

	//リストそのものを削除
	m_ModelList.clear();

}