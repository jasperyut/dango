#pragma once
#include"Application/block/blockmanager.h"
#include"Application/block/coal.h"
class State
{
public:
	
	virtual ~State();
	virtual void Draw(Math::Matrix& _mat);
	virtual void Update(std::unique_ptr<BlockManager>& _blockManager, Math::Matrix& _mat, float& _ang);

};