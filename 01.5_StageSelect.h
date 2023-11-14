#pragma once
#include "main.h"



HRESULT InitStageSelect();
void UninitStageSelect();
void UpdateStageSelect();
void DrawStageSelect();



typedef struct
{
	D3DXVECTOR3 Position;	//表示座標
	D3DXVECTOR2 Size;	//サイズ
	D3DXCOLOR	Color;	//色
	float		Rotate;	//角度
	int			SelectCount;
	bool		SelectFlag;

	int		Texno;	//テクスチャ番号

	int Stageselect;
}STAGESELECTBG;


typedef struct
{
	D3DXVECTOR2 Position;	//表示座標
	D3DXVECTOR2 Size;	//サイズ
	D3DXCOLOR	Color;	//色
	float		Rotate;	//角度

	int TextureNoSB; //テクスチャロード用

	int		Texno;	//テクスチャ番号


}SELECTBUTTON;

