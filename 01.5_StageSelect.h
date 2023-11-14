#pragma once
#include "main.h"



HRESULT InitStageSelect();
void UninitStageSelect();
void UpdateStageSelect();
void DrawStageSelect();



typedef struct
{
	D3DXVECTOR3 Position;	//�\�����W
	D3DXVECTOR2 Size;	//�T�C�Y
	D3DXCOLOR	Color;	//�F
	float		Rotate;	//�p�x
	int			SelectCount;
	bool		SelectFlag;

	int		Texno;	//�e�N�X�`���ԍ�

	int Stageselect;
}STAGESELECTBG;


typedef struct
{
	D3DXVECTOR2 Position;	//�\�����W
	D3DXVECTOR2 Size;	//�T�C�Y
	D3DXCOLOR	Color;	//�F
	float		Rotate;	//�p�x

	int TextureNoSB; //�e�N�X�`�����[�h�p

	int		Texno;	//�e�N�X�`���ԍ�


}SELECTBUTTON;

