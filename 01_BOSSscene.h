#pragma once

#include "main.h"
#include "01_Scene.h"

#define MAX_BOSS_HEDDER		(13)

HRESULT	InitBossScene();
void	UninitBossScene();
void	UpdateBossScene();
void	DrawBossScene()
;

/*
	Game_01配列に格納されている任意のオブジェクトのポインタを取得する関数
	引数：int index (オブジェクト番号)
	戻り値：オブジェクトのポインタ
*/
Game* GetBossSceneObject(int index);
