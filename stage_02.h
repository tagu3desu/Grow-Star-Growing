#pragma once

#include "main.h"
#include "Enemy_PopALL.h"

class Stage_02 : public Stage_00
{
public:
	Stage_02() {}

	virtual void Pop_EnemyBOX();
	virtual void InitEnemyflag();
};
