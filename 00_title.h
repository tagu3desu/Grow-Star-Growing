#pragma once

#include "main.h"

HRESULT Inittitle();
void Uninittitle();
void Updatetitle();
void Drawtitle();

typedef	struct
{
	D3DXVECTOR3		Position;	//�\�����W
	D3DXVECTOR2		Size;		//�T�C�Y
	D3DXCOLOR		Color;		//�F
	float			Rotate;		//�p�x
}TITLE;
