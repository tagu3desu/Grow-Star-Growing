/*==============================================================================

   ���ʃw�b�_�[ [main.h]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~
#include <stdio.h>
#include<windows.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#include "dinput.h"
#include "mmsystem.h"

#include	"texture.h"
#include	"renderer.h"
#include	"polygon.h"	//polygon.h�C���N���[�h
#include	"inputx.h"	//���͏���
#include	"mouse.h"
#include	"keyboard.h"
#include    "sound.h"



#pragma warning(pop)



//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(960)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(540)				// �E�C���h�E�̍���

#define SCREEN_LIMIT_UP     (0)         //������ő�l
#define SCREEN_LIMIT_RIGHT (960)       //�E�����ő�l
#define SCREEN_LIMIT_DOWN  (540)       //�������ő�l
#define SCREEN_LIMIT_LEFT   (0)         //�������ő�l


//*****************************************************************************
// �v���g�^�C�v�錾
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

void SetScene(SCENE Scene);	// �����ɑJ�ڐ�V�[�����w��

SCENE GetScene();			//���݂̃V�[����Ԃ�
