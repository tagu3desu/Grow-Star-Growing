/*==============================================================================

   ����w����� [weapon_select.h]
														 Author :��������
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
	D3DXVECTOR3 Position;	//�\�����W
	D3DXVECTOR2 Size;	//�T�C�Y
	D3DXCOLOR	Color;	//�F
	float		Rotate;	//�p�x

	int			Texno;	//�e�N�X�`���ԍ�

	int			SelectSkill;	//���ݑI�𒆂̃X�L���X���b�g
	int			SelectWeapon;	//���ݑI�𒆂̕���

}WEAPON_SELECT;

typedef struct
{
	D3DXVECTOR2 Position;	//�\�����W
	D3DXVECTOR2 Size;	//�T�C�Y
	D3DXCOLOR	Color;	//�F
	float		Rotate;	//�p�x

	int			Texno[WEAPON_HOLD_MAX];	//�e�N�X�`���ԍ�

	int			SkillType;	//���݂̍U����ʂ��擾���Z�b�g

}SELECT_SKILL_BUTTON;

typedef struct
{
	D3DXVECTOR2 Position;	//�\�����W
	D3DXVECTOR2 Size;	//�T�C�Y
	D3DXCOLOR	Color;	//�F
	float		Rotate;	//�p�x

	int			Texno;		//�e�N�X�`���ԍ�
	int			NoneTexno;	//���������̃e�N�X�`���ԍ�
	int			IconTexno;	//����A�C�R���̃e�N�X�`���ԍ�
	BOOL		Ownership;	//������

}SELECT_WEAPON_BUTTON;

