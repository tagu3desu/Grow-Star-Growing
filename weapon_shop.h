#pragma once
#include "main.h"

HRESULT InitWeaponShop();
void UninitWeaponShop();
void UpdateWeaponShop();
void DrawWeaponShop();

typedef struct
{
	D3DXVECTOR3 Position;	//表示座標
	D3DXVECTOR2 Size;	//サイズ
	D3DXCOLOR	Color;	//色
	float		Rotate;	//角度

	int			Texno;	//テクスチャ番号

	int			WeaponSelect;	//武器購入ボタンの選択状況(1番から始まる)
	int			HoldCoin;	//所持金（プレイヤーから取得して一時保存）
}WEAPON_SHOP;

typedef struct
{
	D3DXVECTOR2 Position;	//表示座標
	D3DXVECTOR2 Size;	//サイズ
	D3DXCOLOR	Color;	//色
	float		Rotate;	//角度

	int			Texno;	//テクスチャ番号

	BOOL		Ownership;	//その武器を持っているか（プレイヤーから取得して一時保存）
	int			Price;	//値段


}WEAPON_SHOP_BUTTON;
