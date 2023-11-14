/*==============================================================================

   �S�̃f�[�^�Ǘ�����[data.cpp]
												 Author :	AT12G_25_��������
												 Date   :	2023_01_19
--------------------------------------------------------------------------------

==============================================================================*/
#include	"data.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
G_DATA	g_Data;

HRESULT InitData()
{
	//����N�����̂ݎ��s
	g_Data.Money = 99999;		//������
	g_Data.ClearedStage = 0;	//�N���A�����X�e�[�W
	for (int i = 0; i < WEAPON_MAX; i++)
	{
		g_Data.Ownership[i] = FALSE;	//�V���b�g�̍w����
	}
	
	g_Data.SkillType[0] = 0;			//0�Ԗ�		�ʏ�e
	g_Data.SkillType[1] = 1;			//1�Ԗ�		�O�ҖC�e
	g_Data.SkillType[2] = 3;			//2�Ԗ�		��]�e
	
	//�X�e�[�W���Ƃɋ��L
	g_Data.Energy = 0;
	g_Data.PlayerScore = 0;

	return S_OK;	//����I��
}

void UninitData()
{

}

void UpdateData()
{

}

void DrawData()
{

}

void SetData(int money, int cleared_stage, int energy, int player_score)
{
	if (money >= 0)
	{
		g_Data.Money = money;
	}

	if (cleared_stage >= 0)
	{
		g_Data.ClearedStage = cleared_stage;
	}

	if (energy >= 0)
	{
		g_Data.Energy = energy;
	}

	if (player_score)
	{
		g_Data.PlayerScore = player_score;
	}
}

void SetWeaponData(BOOL ownership[])
{
	for (int i = 0; i < WEAPON_MAX; i++)
	{
		g_Data.Ownership[i] = ownership[i];
	}
}

void SetSkillType(BOOL skill_type[SKILL_TYPE_MAX])
{
	for (int i = 0; i < SKILL_TYPE_MAX; i++)
	{
		g_Data.SkillType[i] = skill_type[i];
	}
}

void ResetStageData()
{
	g_Data.Energy = 0;
	g_Data.PlayerScore = 0;
}

//�f�[�^�\���̂̃|�C���^���擾
G_DATA* GetData()
{
	return &g_Data;
}
