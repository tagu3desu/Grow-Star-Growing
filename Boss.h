/*==============================================================================

   ボスの処理[Boss.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#include"01_Scene.h"

static const int BOSS_SIZE_W = 320;	//ボスの横
static const int BOSS_SIZE_H = 320;	//ボスの高さ
static const int BOSS_SPEED = 2.0f;		//ボスの移動速度
static const int PARTS_MAX = 10;	//ボス部位の最大数

class BOSS_01 :public Game
{
public:
	virtual HRESULT InitGame();	//初期化
	virtual void	UninitGame();//終了処理
	virtual void	UpdateGame();//更新処理
	virtual void    DrawGame();//描画処理

	bool Use;	//ボス仕様フラグ
	D3DXVECTOR2 Pos;	//表示座標
	float		Rot;	//回転角度
	int			TexNo;	//テクスチャ番号
	int			BreakTexno;
	bool		tacklehit;
	int			tacklecount;

	int HP; //ボスのHP

	D3DXVECTOR2	size;	//サイズ
	int FrameWait;	

	D3DXVECTOR2 move;
	D3DXCOLOR	color;
	int		BossNo;

	int		Count; //テスト
	

	int		PartsIndex[PARTS_MAX];		//ボス部位のインデックスを格納する配列
};

//========================
//プロトタイプ宣言
//========================
BOSS_01 *GetBoss_01();	//構造体の先頭アドレスを返す

void SetBoss_01(int Boss_01Num,float BossX, float BossY);	//ボス呼び出し(X,Y)

void Boss_damege_reaction();
