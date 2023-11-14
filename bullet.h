/*==============================================================================

   弾の処理[bullet.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"
#include "01_Scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_BULLET		(100)	//弾の数


class BULLET: public Game
{
private:

public:
	virtual HRESULT InitGame();	//初期化
	virtual void	UninitGame();//終了処理
	virtual void	UpdateGame();//更新処理
	virtual void    DrawGame();//描画処理


	D3DXVECTOR2		pos;				// 表示座標
	D3DXCOLOR		color;				// 色
	float			rot;				// 角度
	D3DXVECTOR2		move;				// 移動速度
	int				texNo;				// テクスチャ番号
	float			texAnime;			// テクスチャアニメ
	BOOL			use;				// 使用する/しない


	D3DXVECTOR2     size;				// 弾のサイズ
	int				damage;				// 弾が当たった時のダメージ量
	int				num_attack;			// 残り攻撃回数(0になると弾が消滅する)
	float			revolution_angle;	// 回転弾の公転角度
	D3DXVECTOR2		circle_origin;		// 回転弾の中心座標

	int	bulletNo;	//バレットパターン

	int time_count;	//弾が生成されてから経った時間

	bool buy;
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


BULLET	*GetBullet(int num);				//構造体の先頭アドレスを返す
void	SetBullet(int BulletNo, D3DXVECTOR2 pos);	//弾の発生 in:弾のID番号,発生座標

//==================================
//弾発射時の消費キラキラ数を返す
//==================================
int			GetBulletDemand(int index);

//==================================
//弾発射スキル使用回数の最大数を返す
//==================================
int			GetBulletUsageMax(int index);

//==================================
//弾発射クールタイムの最大数を返す
//==================================
int			GetBulletCoolTimeMax(int index);