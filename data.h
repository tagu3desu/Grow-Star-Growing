/*==============================================================================

   �S�̃f�[�^�Ǘ�����[data.h]
												 Author :	AT12G_25_��������
												 Date   :	2023_01_19
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#include "main.h"

//�O���[�o���ϐ�
static const int	WEAPON_MAX = 4;		//�w���\�ȕ���̍ő吔
static const int	SKILL_TYPE_MAX = 3;	//�Z�b�g����X�L���̍ő吔

HRESULT InitData();
void UninitData();
void UpdateData();
void DrawData();

typedef struct
{
	//�Q�[���S�̂̋��L�f�[�^
	int		Money;					//�v���C���[�̏�����
	int		ClearedStage;			//�N���A�����X�e�[�W
	BOOL	Ownership[WEAPON_MAX];	//�V���b�g�̍w����
	int		SkillType[3];			//���݃Z�b�g����Ă���V���b�g

	//�X�e�[�W���Ƃ̃f�[�^
	int		Energy;					//�L���L���̎c��
	int		PlayerScore;				//�l���X�R�A
}G_DATA;

void SetData(int money, int cleared_stage, int energy, int player_score);//����,�N���A�����X�e�[�W, �G�i�W�[, �X�R�A
void SetWeaponData(BOOL ownership[]);
void SetSkillType(BOOL skill_type[SKILL_TYPE_MAX]);
void ResetStageData();
G_DATA* GetData();

