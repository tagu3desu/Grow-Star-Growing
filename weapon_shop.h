#pragma once
#include "main.h"

HRESULT InitWeaponShop();
void UninitWeaponShop();
void UpdateWeaponShop();
void DrawWeaponShop();

typedef struct
{
	D3DXVECTOR3 Position;	//�\�����W
	D3DXVECTOR2 Size;	//�T�C�Y
	D3DXCOLOR	Color;	//�F
	float		Rotate;	//�p�x

	int			Texno;	//�e�N�X�`���ԍ�

	int			WeaponSelect;	//����w���{�^���̑I����(1�Ԃ���n�܂�)
	int			HoldCoin;	//�������i�v���C���[����擾���Ĉꎞ�ۑ��j
}WEAPON_SHOP;

typedef struct
{
	D3DXVECTOR2 Position;	//�\�����W
	D3DXVECTOR2 Size;	//�T�C�Y
	D3DXCOLOR	Color;	//�F
	float		Rotate;	//�p�x

	int			Texno;	//�e�N�X�`���ԍ�

	BOOL		Ownership;	//���̕���������Ă��邩�i�v���C���[����擾���Ĉꎞ�ۑ��j
	int			Price;	//�l�i


}WEAPON_SHOP_BUTTON;
