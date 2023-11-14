#pragma once

#include "main.h"

#define MAX_HEDDER		(15)

HRESULT InitScene();
void UninitScene();
void UpdateScene();
void DrawBScene();

class Game
{

public:
	virtual HRESULT InitGame()=0{}
	virtual void	UninitGame()=0{}
	virtual void	UpdateGame()=0{}
	virtual void    DrawGame()=0{}

};

/*
	Game_01配列に格納されている任意のオブジェクトのポインタを取得する関数
	引数：int index (オブジェクト番号)
	戻り値：オブジェクトのポインタ
*/
Game* GetSceneObject(int index);