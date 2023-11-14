/*==============================================================================

   敵の処理[enemy.h]
														 Author :田口功将
														 Date   :2022/10/27
--------------------------------------------------------------------------------

==============================================================================*/

#pragma once			//役立たず
#include "01_Scene.h"

static const int  ENEMY_MAX = 100;

static const int ENEMY_SIZE_W = 50;		//エネミーの横
static const int ENEMY_SIZE_H = 50;		//エネミーの高さ
static const int ENEMY_SPEED = 1;	//エネミーの移動速度

static const int ENEMY_BIG_SIZE_W = 60;
static const int ENEM_BIG_SIZE_H = 60;
static const int ENEMY_BIG_SPEED = 2;

class ENEMY: public Game
{
public:
	bool		Use;	//敵使用フラグ
	D3DXVECTOR2 Pos;	//表示座標
	float		Rot;	//回転角度
	int			Texno;	//テクスチャ番号
	D3DXVECTOR2 size;   //キャラクターサイズ
	int			MoveCount;	//移動用

	//弾関係
	float		FrameWait; //発生までのカウンター
	int			countE;	   //リスポーンまでの時間
	float		bulletrate;//射撃するタイミング
	int			BulletType;//エネミー弾の種類
	D3DXVECTOR2 move;
	D3DXVECTOR2 secondmove;


	int			enemyNo;
	D3DXCOLOR   color;


	virtual HRESULT InitGame();	//初期化
	virtual void	UninitGame();//終了処理
	virtual void	UpdateGame();//更新処理
	virtual void    DrawGame();//描画処理
private:

};


//========================
//プロトタイプ宣言
//========================
ENEMY* GetEnemy(int num);				//構造体の先頭のポインタを返す


void SetEnemy(int EnemyNo, int EnemyBulletNo, float EnemyX, float EnemyY);	//エネミー選択呼び出し

void Enemy_dameg_reaction(int num);//エネミーのだめーじ処理
