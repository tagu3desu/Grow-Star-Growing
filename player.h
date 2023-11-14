/*==============================================================================

   プレイヤー処理[player.h]
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

//*****************************************************************************
// 構造体定義
//*****************************************************************************
class PLAYER:public Game
{
private:

public:
	virtual HRESULT InitGame();	//初期化
	virtual void	UninitGame();//終了処理
	virtual void	UpdateGame();//更新処理
	virtual void    DrawGame();//描画処理

	BOOL			use;		// 使用する/しない
	D3DXVECTOR2		Position;	// 表示座標
	float			Rotate;		// 角度
	int				texNo;		// テクスチャ番号
    D3DXVECTOR2     size;//プレイヤーのサイズ
	D3DXCOLOR		Color;		// 色
	

	int				Bulletrate;	//弾発射間隔
	bool			ShotFlag;	//弾発射時

	int				Hp;			//体力
	int				HptexNo;	//HPテクスチャ
	D3DXVECTOR2		HpSize;		//HPサイズ
	D3DXVECTOR2		HpPos;		//HP座標
					


	int				HugetexNo;	//巨大化UI
	D3DXVECTOR2		HugePos;	//巨大化UI座標
	D3DXVECTOR2		HugeSize;	//巨大化UI大きさ
	int				HugeCount;	//巨大化用フレームカウント
	float			HugeRotate; //巨大化用UI角度
	bool			ChangeHuge;
	bool			ResetHuge;

	int				energy;		//キラキラの残量
	int				gain;		//キラキラ取得時の増加量


	bool			SizeUp;	//巨大化処理
	bool			tackle;	//タックル
	int				FrameCaount; //フレームカウント
	int				AtacckDelay;	//攻撃硬直
	int				TackleDamege;//タックルのダメージ
	

	int				SkillType[3];			//攻撃種別(左、上、右の3種類)
	int				SkillUsageMax[3];		//スキル使用回数上限(左、上、右の3種類)
	int				SkillUsageCount[3];		//残りのスキル使用回数(左、上、右の3種類)
	int				SkillCoolTime[3];		//スキルのクールタイムカウント(左、上、右の3種類)
	int				SkillCoolTimeMax[3];	//スキルのクールタイムの最大数(左、上、右の3種類)

};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


PLAYER	*GetPlayer();		//構造体の先頭アドレスを返す

void Player_dameg_reaction();