#pragma once

#include"main.h"
#include"renderer.h"
#include"01_Scene.h"
//==============================
//マクロ定義
//==============================
#define	 EXPLOSION_MAX (100)	//弾最大数
#define  EXPLOSION_SPEED (10.0f) //移動速度

#define  EXPLOSION_SIZE_W (40)	//爆発エフェクトサイズ
#define  EXPLOSION_SIZE_Y (40)	//爆発エフェクトサイズ

#define EXPLOSION_ANIME_MAX (16)	//アニメーション最大数

class EXPLOSION : public Game
{
public:
	bool use;		//使用フラグ
	D3DXVECTOR2  size;		//サイズ
	D3DXVECTOR2 pos;	//表示座標
	D3DXVECTOR2	move;	//移動スピード
	float	rot;	//回転座標
	int		texNo;	//テクスチャ番号

	float AnimePattern;	//アニメーションパターン番号
	float AnimeSpeed;	//アニメーションスピード


	virtual HRESULT InitGame();
	virtual void	UninitGame();
	virtual void	UpdateGame();
	virtual void	DrawGame();
};

//===========================
//プロトタイプ宣言
//============================

EXPLOSION* GetExplosion();	//構造体の先頭ポインタを取得
void	   SetExplosion(D3DXVECTOR2 pos, float animespeed);	//弾の発生