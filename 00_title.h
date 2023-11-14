#pragma once

#include "main.h"

HRESULT Inittitle();
void Uninittitle();
void Updatetitle();
void Drawtitle();

typedef	struct
{
	D3DXVECTOR3		Position;	//表示座標
	D3DXVECTOR2		Size;		//サイズ
	D3DXCOLOR		Color;		//色
	float			Rotate;		//角度
}TITLE;
