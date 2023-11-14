#pragma once

#include "main.h"
#include "renderer.h"
#include "01_Scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAUGE_MAX (1)
#define GAUGE2_MAX (1)

class GAUGE: public Game
{
public:

	virtual HRESULT InitGame();	//初期化
	virtual void	UninitGame();//終了処理
	virtual void	UpdateGame();//更新処理
	virtual void    DrawGame();//描画処理

	D3DXVECTOR2		pos;		// 表示座標
	D3DXCOLOR		color;		// 色
	float			rot;		// 角度
	D3DXVECTOR2		move;		// 移動速度
	int				texNo;		// テクスチャ番号
	BOOL			use;		// 使用する/しない

	D3DXVECTOR2     size;       //サイズ
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
GAUGE	*GetGauge();		//構造体の先頭アドレスを返す
GAUGE	*GetGauge2();		//構造体の先頭アドレスを返す
