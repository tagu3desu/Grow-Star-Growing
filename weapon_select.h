/*==============================================================================

   武器購入画面 [weapon_select.h]
														 Author :髙橋建次
														 Date   :2023_01_21
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#include	"main.h"

HRESULT InitWeaponSelect();
void UninitWeaponSelect();
void UpdateWeaponSelect();
void DrawWeaponSelect();

static const int	WEAPON_HOLD_MAX = 6;

typedef struct
{
	D3DXVECTOR3 Position;	//表示座標
	D3DXVECTOR2 Size;	//サイズ
	D3DXCOLOR	Color;	//色
	float		Rotate;	//角度

	int			Texno;	//テクスチャ番号

	int			SelectSkill;	//現在選択中のスキルスロット
	int			SelectWeapon;	//現在選択中の武器

}WEAPON_SELECT;

typedef struct
{
	D3DXVECTOR2 Position;	//表示座標
	D3DXVECTOR2 Size;	//サイズ
	D3DXCOLOR	Color;	//色
	float		Rotate;	//角度

	int			Texno[WEAPON_HOLD_MAX];	//テクスチャ番号

	int			SkillType;	//現在の攻撃種別を取得しセット

}SELECT_SKILL_BUTTON;

typedef struct
{
	D3DXVECTOR2 Position;	//表示座標
	D3DXVECTOR2 Size;	//サイズ
	D3DXCOLOR	Color;	//色
	float		Rotate;	//角度

	int			Texno;		//テクスチャ番号
	int			NoneTexno;	//未所持時のテクスチャ番号
	int			IconTexno;	//武器アイコンのテクスチャ番号
	BOOL		Ownership;	//所持状況

}SELECT_WEAPON_BUTTON;

