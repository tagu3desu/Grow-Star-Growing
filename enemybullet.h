/*==============================================================================

   敵の弾の処理[enemybullet.h]
														 Author :田口功将
														 Date   :2022/10/27
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "main.h"
#include "renderer.h"
#include "01_Scene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_MAX_BULLET		(100)	//弾の数
#define ENEMY_MAX_BIG_BULLET	(1)	//弾の数
#define ENEMY_MAX_ROT_BULLET	(100)	//弾の数
#define ENEMY_MAX_SIDE_BULLET	(100)	//弾の数
#define ENEMY_MAX_WAYUP_BULLET	(100)	//弾の数
#define ENEMY_MAX_WAYDOWN_BULLET (100)	//弾の数

class ENEMY_BULLET:public Game
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
	float			texAnime;			// テクスチャアニメ
	BOOL			use;		// 使用する/しない

	int				bighp = 10; //でかい弾体力
	int				rothp = 3;  //回転弾体力

	D3DXVECTOR2     size;       //サイズ

	int	enemybulletNo;	//バレットパターン

};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


ENEMY_BULLET* GetEnemyBullet(int num);				//構造体の先頭アドレスを返す


void    Set_Enemybullet(int EnemyBulletNum, D3DXVECTOR2 playerpos, D3DXVECTOR2 enemypos); //バレッド選択＆呼び出し



void EnemyBullet_dameg_reaction(int num);
