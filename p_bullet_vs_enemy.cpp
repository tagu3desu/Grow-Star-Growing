/*==============================================================================

   �v���C���[�o���b�g�ƃG�l�~�[�̓����蔻�菈�� [p_bullet_vs_enemy.cpp]
														 Author :	AT12G_25_��������
														 Date   :	2022_12_1
--------------------------------------------------------------------------------

==============================================================================*/
#include	"p_bullet_vs_enemy.h"
#include	"01_Scene.h"

#include	"collision.h"
#include	"bullet.h"
#include	"enemy.h"
#include	"enemybullet.h"
#include	"kirakira.h"
#include	"score.h"


#include    "00_soundmain.h"
#include    "Explosion.h"

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
P_BulletVSEnemy::P_BulletVSEnemy()
{
	
}

P_BulletVSEnemy::~P_BulletVSEnemy()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT P_BulletVSEnemy::InitGame(void)
{

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void P_BulletVSEnemy::UninitGame(void)
{


}

//=============================================================================
// �X�V����(�����蔻�菈���������ōs��)
//=============================================================================
void P_BulletVSEnemy::UpdateGame(void)
{
	//�v���C���[�e�ƃG�l�~�[�̓����蔻�菈��
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (GetBullet(i)->use == TRUE)	//�e���g�p��
		{
			for (int j = 0; j < ENEMY_MAX; j++)
			{
				if ((GetEnemy(j)->Use == TRUE) && (CollisionBB(GetBullet(i)->pos, GetEnemy(j)->Pos, GetBullet(i)->size, GetEnemy(j)->size) == TRUE))
				{

					PlayEffect(Bom, 0.5f);
					SetExplosion(GetEnemy(j)->Pos,0.4f);
					if (GetBullet(i)->num_attack < 0)
					{

						Kirakira_bone(GetEnemy(j)->Pos, 3);//�R�L���L���𐶐�����
						// �X�R�A�f�[�^�̍X�V(���̃N���X�̊֐����Ăяo���Ƃ��́A�����̃R�[�h���R�s�y�����ς��Ďg���Ă�������)
						{
							for (int i = 0; i < MAX_HEDDER; i++)
							{
								Game* object = GetSceneObject(i);

								//�N���X�̎�ނ���v�����Ƃ��̂ݏ������s��
								if (typeid(*object) == typeid(SCORE))
								{
									//�_�E���L���X�g���s���h���N���X�ŗL�̊֐����Ăяo����悤�ɂ���
									//���z�֐��݂̂̔h���N���X�̏ꍇ���̏����͕K�v����܂���
									SCORE* score = dynamic_cast<SCORE*>(GetSceneObject(i));
									//�X�R�A�̉��Z
									score->AddScore(100);
								}
							}
						}
						
						GetEnemy(j)->Use = false;//����
					}
					else
					{
						GetBullet(i)->num_attack--;
						Kirakira_bone(GetEnemy(j)->Pos, 3);//�R�L���L���𐶐�����
						// �X�R�A�f�[�^�̍X�V(���̃N���X�̊֐����Ăяo���Ƃ��́A�����̃R�[�h���R�s�y�����ς��Ďg���Ă�������)
						{
							for (int i = 0; i < MAX_HEDDER; i++)
							{
								Game* object = GetSceneObject(i);

								//�N���X�̎�ނ���v�����Ƃ��̂ݏ������s��
								if (typeid(*object) == typeid(SCORE))
								{
									//�_�E���L���X�g���s���h���N���X�ŗL�̊֐����Ăяo����悤�ɂ���
									//���z�֐��݂̂̔h���N���X�̏ꍇ���̏����͕K�v����܂���
									SCORE* score = dynamic_cast<SCORE*>(GetSceneObject(i));
									//�X�R�A�̉��Z
									score->AddScore(100);
								}
							}
						}
						GetEnemy(j)->Use = false;//����

						if (GetBullet(i)->num_attack <= 0)
						{
							GetBullet(i)->use = false;
						}
					}
				}
			}
		}
	}

	//�v���C���[�e�ƃG�l�~�[�e�̓����蔻�菈��
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (GetBullet(i)->use == TRUE)	//�e���g�p��
		{
			for (int j = 0; j < ENEMY_MAX_BULLET; j++)
			{
				if ((GetEnemyBullet(j)->use == TRUE) && CollisionBB(GetBullet(i)->pos, GetEnemyBullet(j)->pos, GetBullet(i)->size, GetEnemyBullet(j)->size) == TRUE)
				{
					GetEnemyBullet(j)->use = FALSE;	//�Ƃ肠�����e����������
					if (GetBullet(i)->num_attack == 1)
					{
						GetBullet(i)->use = false;
					}
				}
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void P_BulletVSEnemy::DrawGame(void)
{
	//�g�p���Ȃ�
}
