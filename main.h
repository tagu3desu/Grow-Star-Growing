/*==============================================================================

   共通ヘッダー [main.h]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止
#include <stdio.h>
#include<windows.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"

#include	"texture.h"
#include	"renderer.h"
#include	"polygon.h"	//polygon.hインクルード
#include	"inputx.h"	//入力処理
#include	"mouse.h"
#include	"keyboard.h"
#include    "sound.h"



#pragma warning(pop)



//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(960)				// ウインドウの幅
#define SCREEN_HEIGHT	(540)				// ウインドウの高さ

#define SCREEN_LIMIT_UP     (0)         //上方向最大値
#define SCREEN_LIMIT_RIGHT (960)       //右方向最大値
#define SCREEN_LIMIT_DOWN  (540)       //下方向最大値
#define SCREEN_LIMIT_LEFT   (0)         //左方向最大値


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

enum SCENE
{
	SCENE_NONE,		//0
	SCENE_TITLE,	//1
	SCENE_SELECT,	//2
	SCENE_GAME,		//3
	
	SCENE_STAGE02,	//4
	SCENE_STAGE03,	//5
	SCENE_STAGE04,	//6

	SCENE_BOSS01,	//7
	SCENE_BOSS02,	//8
	SCENE_BOSS03,	//9
	SCENE_BOSS04,	//10

	SCENE_RESULT,	//11
	SCENE_SHOP,		//12
	SCENE_SKILL_SET,//13
};

void SetScene(SCENE Scene);	// 引数に遷移先シーンを指定

SCENE GetScene();			//現在のシーンを返す
