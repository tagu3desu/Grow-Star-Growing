#pragma once
#include "main.h"
#include "01_Scene.h"


class Stage_BOX : public Game
{
public:
	Stage_BOX() {};
	~Stage_BOX() {};

	virtual HRESULT InitGame();
	virtual void	UninitGame();
	virtual void	UpdateGame();
	virtual void    DrawGame();

private:


};

class Stage_00
{
public:
	virtual void Pop_EnemyBOX()= 0{}
	virtual void InitEnemyflag() = 0 {}
};


