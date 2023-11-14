/*==============================================================================

   �v���C���[�ƃG�l�~�[�̓����蔻�菈�� [player_vs_enemy.cpp]
														 Author :	AT12G_25_��������
														 Date   :	2022_11_24
--------------------------------------------------------------------------------

==============================================================================*/
#include	"player_vs_enemy.h"
#include	"01_Scene.h"

#include	"collision.h"
#include	"player.h"
#include	"enemy.h"
#include	"enemybullet.h"

#include    "kirakira.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
PlayerVSEnemy::PlayerVSEnemy()
{
	
}

PlayerVSEnemy::~PlayerVSEnemy()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT PlayerVSEnemy::InitGame(void)
{
	invincible_time = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void PlayerVSEnemy::UninitGame(void)
{


}

//=============================================================================
// �X�V����(�����蔻�菈���������ōs��)
//=============================================================================
void PlayerVSEnemy::UpdateGame(void)
{
	//========================================================
	//���剻���Ă��Ȃ��Ƃ�

	if (GetPlayer()->SizeUp == false) 
	{
		//�v���C���[�ƃG�l�~�[�̓����蔻�菈��
		if (invincible_time <= 0)	//���G��ԂłȂ��ꍇ�̂ݎ��s
		{
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				if ((GetEnemy(i)->Use == TRUE) && CollisionBB(GetPlayer()->Position, GetEnemy(i)->Pos, GetPlayer()->size, GetEnemy(i)->size) == TRUE)
				{
					//���G��ԂɈڍs
					GetPlayer()->Hp -= 1;
					invincible_time = INVINCIBLE_TIME_MAX;
				}
			}
		}

		//�v���C���[�ƃG�l�~�[�e�̓����蔻�菈��

		for (int i = 0; i < ENEMY_MAX_BULLET; i++)
		{
			if ((GetEnemyBullet(i)->use == TRUE) && CollisionBB(GetPlayer()->Position, GetEnemyBullet(i)->pos, GetPlayer()->size, GetEnemyBullet(i)->size) == TRUE)
			{
				GetEnemyBullet(i)->use = FALSE;	//�Ƃ肠�����e����������
				//���G��ԂłȂ��ꍇ�̂ݎ��s
				if (invincible_time <= 0)
				{
					//���G��ԂɈڍs
					GetPlayer()->Hp -= 1;
					invincible_time = INVINCIBLE_TIME_MAX;
				}
			}
		}
	}





	//=======================================================
	//���傪���Ă鎞�̓����蔻��

	if (GetPlayer()->SizeUp == true)
	{
		//========================================================
		//�΃G�l�~�[�̏���
		for (int i = 0; i < ENEMY_MAX; i++)
			{
			if ((GetEnemy(i)->Use == TRUE) && CollisionBB(GetPlayer()->Position, GetEnemy(i)->Pos, GetPlayer()->size, GetEnemy(i)->size) == TRUE)
			{
				if (GetPlayer()->tackle == true)//�^�b�N����
				{
					GetEnemy(i)->Use = false;
				}

				else//�^�b�N�����łȂ�
				{
					GetEnemy(i)->Use = false;
					GetPlayer()->energy -= DAMAGE;
				}

			}
		}
		
		//========================================================
		//��E�o���b�h
		for (int i = 0; i < ENEMY_MAX_BULLET; i++)
		{
			if ((GetEnemyBullet(i)->use == TRUE) && CollisionBB(GetPlayer()->Position, GetEnemyBullet(i)->pos, GetPlayer()->size, GetEnemyBullet(i)->size) == TRUE)
			{
				if (GetPlayer()->tackle == true)//�^�b�N����
				{
					GetEnemyBullet(i)->use = FALSE;
				}

				if (GetPlayer()->tackle == false)//�^�b�N��������Ȃ�
				{
					GetEnemyBullet(i)->use = FALSE;
					GetPlayer()->energy -= DAMAGE;
				}


			}
		}




	}


	//���G��Ԏ��̏���
	if (invincible_time > 0)
	{
		invincible_time--;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void PlayerVSEnemy::DrawGame(void)
{
	//�g�p���Ȃ�
}