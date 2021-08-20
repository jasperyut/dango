#pragma once
#include"System/KeySystem.h"

class ModelManager
{
public:
	KdModel* GetModel(std::string _fileName);
	~ModelManager();

	const std::map<std::string,KdModel*>& GetMod()const
	{
		return m_ModelList;
	}

private:
	std::map<std::string, KdModel*>m_ModelList;
};