
//===============================
//
//スプライト描画処理
//===============================
#pragma once

#include	"main.h"

//========================
//マクロ定義
//=========================

//========================
//プロトタイプ宣言
//=========================

void	DrawSpriteColorRotate(float posx,float posy, 
	int size_w, int size_h, 
	float kakudo,D3DXCOLOR col,
	float PaternNo,
	float uv_w,float uv_h,
	int NumPatarn);
void	InitSprite();
void	UninitSprite();


