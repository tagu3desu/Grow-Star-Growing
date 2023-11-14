#pragma once
#include "main.h"
#include "Enemy_PopALL.h"

class Stage_01 : public Stage_00
{
public:
	Stage_01(){}

	virtual void Pop_EnemyBOX();
	virtual void InitEnemyflag();

};
