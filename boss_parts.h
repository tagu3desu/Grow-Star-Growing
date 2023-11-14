/*==============================================================================

   敵ボスの部位処理[boss_parts.h]
														 Author :髙橋建次
														 Date   :2022/12/22
--------------------------------------------------------------------------------

==============================================================================*/

#pragma once			//役立たず
#include "01_Scene.h"

static const int  BOSS_PARTS_MAX = 100;

static const int BOSS_PARTS_SIZE_W = 100;		//ボスの部位の横
static const int BOSS_PARTS_SIZE_H = 100;		//ボスの部位の高さ
//static const int BOSS_PARTS_SPEED = 1;	//エネミーの移動速度
//
//static const int BOSS_PARTS_BIG_SIZE_W = 60;
//static const int ENEM_BIG_SIZE_H = 60;
//static const int BOSS_PARTS_BIG_SPEED = 2;

class BOSS_PARTS: public Game
{
public:
	bool		Use;		//ボス部位使用フラグ
	D3DXVECTOR2 Pos;		//表示座標(ボスの中心座標からの相対座標)
	float		Rot;		//回転角度
	int			Texno;		//テクスチャ番号
	D3DXVECTOR2 size;		//キャラクターサイズ

	int			HP;			//ボス部位のHP
	D3DXVECTOR2	BossPos;	//ボスの中心座標
	bool		tacklehit;
	int			tacklecount;


	//弾関係
	float		FrameWait; //発生までのカウンター
	int			countE;	   //リスポーンまでの時間
	float		bulletrate;//射撃するタイミング
	int			BulletType;//エネミー弾の種類
	D3DXVECTOR2 move;


	int			BossPartsNo;	//ボス部位の種類(現在未使用)
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
BOSS_PARTS* GetBossParts(int num);				//構造体の先頭のポインタを返す


int SetBossParts(float posx, float posy, int HP, D3DXVECTOR2 BOSSposs);	//エネミー選択呼び出し

void BossParts_damege_reaction(int num);//エネミーのだめーじ処理


bool Get_BossPartslivis(); // ボスのパーツで生きているのがいるかどうか　　（いる：true　いない：false
