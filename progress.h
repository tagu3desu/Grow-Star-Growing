#pragma once
#include "main.h"
#include "01_Scene.h"

//*
//移動可　移動先のヘッダーを読み込むこと
enum STAGE
{
	STAGE_00,	//デフォルト
	STAGE_01,	//1
	STAGE_02,	//2
	STAGE_03,   //3
	STAGE_04,   //3
};
//*/

class Progress :public Game
{
private:

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
	int			time;		//時間

	
};


void	Set_BOSSstage(STAGE stage_num);//ステージと時間を設定するよ！

void	Set_stage(SCENE scene);

int Get_time();
