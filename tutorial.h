/*=================================================================
チュートリアルの処理[tutorial.h]


===================================================================*/
#pragma once
#include"01_Scene.h"



class TUTORIAL : public Game
{
public:
	virtual HRESULT InitGame();	//初期化
	virtual void    UninitGame(); //終了処理
	virtual void	UpdateGame();	//更新処理
	virtual void	DrawGame();	//描画処理
	int texNo;					//テクスチャ

	bool			Use;		//使用
	D3DXVECTOR3		Position;	//表示座標
	D3DXVECTOR2		Size;		//サイズ
	D3DXCOLOR		Color;		//色
	float			Rotate;		//角度

};

//========================
//プロトタイプ宣言
//========================
void Set_BG(int x);
