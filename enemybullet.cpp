/*==============================================================================

   �G�̒e�̏���[enemybullet.cpp]
														 Author :�c������
														 Date   :2022/11/22
--------------------------------------------------------------------------------

==============================================================================*/
#include <stdlib.h>
#include"sprite.h"
#include"texture.h"
#include "enemybullet.h"
#include "bullet.h"
#include "collision.h"
#include "kirakira.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ENEMY_BULLET_SIZE_W	(20.0f)	//�l�p�`�̉��̃T�C�Y
#define	ENEMY_BULLET_SIZE_H	(20.0f)	//�l�p�`�̏c�̃T�C�Y
#define ENEMY_BULLET_SPEED	(3.0f)	//�e�̑���

#define ENEMY_BULLET_BIG_SIZE_W (70.0f) //����ȋ��̎l�p�`�̉��̃T�C�Y
#define ENEMY_BULLET_BIG_SIZE_H (70.0f) //����ȋ��̎l�p�`�̏c�̃T�C�Y
#define ENEMY_BULLET_BIG_SPEED	(1.0f)	//�e�̑���

#define ENEMY_BULLET_ROT_SIZE_W (40.0f) //��]����e�̎l�p�`�̉��̃T�C�Y
#define ENEMY_BULLET_ROT_SIZE_H (20.0f) //��]����e�̎l�p�`�̉��̃T�C�Y
#define ENEMY_BULLET_ROT_SPEED	(3.0f) //�e�̑���

#define	ENEMY_BULLET_SIDE_SIZE_W (20.0f)	//���֐i�ޒe�̉��̃T�C�Y
#define	ENEMY_BULLET_SIDE_SIZE_H (20.0f)	//���֐i�ޒe�̏c�̃T�C�Y
#define ENEMY_BULLET_SIDE_SPEED	 (-3.0f)	//�e�̑���

#define ENEMY_BULLET_WAYUP_SIZE_W (20.0f)    //��Ғe��̉��̃T�C�Y
#define ENEMY_BULLET_WAYUP_SIZE_H (10.0f)	  //��Ғe��̏c�̃T�C�Y
#define ENEMY_BULLET_WAYUP_SPEED  (3.0f)    //�e�̑���

#define ENEMY_BULLET_WAYDOWN_SIZE_W (20.0f)    //��Ғe���̉��̃T�C�Y
#define ENEMY_BULLET_WAYDOWN_SIZE_H (10.0f)    //��Ғe���̏c�̃T�C�Y
#define ENEMY_BULLET_WAYDOWN_SPEED  (3.0f)    //�e�̑���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************



ENEMY_BULLET	g_EnemyBullet[ENEMY_MAX_BULLET];		  // �e�I�u�W�F�N�g


//=============================================================================
// ����������
//=============================================================================
HRESULT ENEMY_BULLET::InitGame(void)
{ 
	for (int i = 0; i < ENEMY_MAX_BULLET; i++){
		g_EnemyBullet[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_EnemyBullet[i].size.x = ENEMY_BULLET_SIZE_W;
		g_EnemyBullet[i].size.y = ENEMY_BULLET_SIZE_H;
		g_EnemyBullet[i].rot = 0.0f;
		g_EnemyBullet[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_EnemyBullet[i].move = D3DXVECTOR2(ENEMY_BULLET_SPEED, 0.0f);
		g_EnemyBullet[i].texNo = LoadTexture((char*)"data\\texture\\tekitamamurasaki.png");
		g_EnemyBullet[i].texAnime = 0.0f;
		g_EnemyBullet[i].use = false;
		g_EnemyBullet[i].enemybulletNo = 1;
	}

	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void ENEMY_BULLET::UninitGame(void)
{


}


//=============================================================================
// �X�V����
//=============================================================================
void ENEMY_BULLET::UpdateGame(void)
{
	for (int i = 0; i < ENEMY_MAX_BULLET; i++) {
		if (g_EnemyBullet[i].use == true) 
		{
			switch (g_EnemyBullet[i].enemybulletNo)
			{
			case 1://�v���C���[�̏ꏊ��

				g_EnemyBullet[i].pos += g_EnemyBullet[i].move;//���W�̍X�V

				break;

			case 2:	//�傫���e

					//���W�̍X�V
				g_EnemyBullet[i].pos += g_EnemyBullet[i].move;

				break;
			case 3: //��]�e



					//���W�̍X�V
				g_EnemyBullet[i].pos += g_EnemyBullet[i].move;
				g_EnemyBullet[i].rot += 3.0f;

				break;

			case 4:



				//���W�̍X�V
				g_EnemyBullet[i].pos.x -= 2.0f;

				break;

			case 5:


				g_EnemyBullet[i].pos.y += 1.0f;
				//���W�̍X�V
				g_EnemyBullet[i].pos += g_EnemyBullet[i].move;

				break;

			case 6:


				g_EnemyBullet[i].pos.y -= 1.0f;
				//���W�̍X�V
				g_EnemyBullet[i].pos += g_EnemyBullet[i].move;

				break;

			
			default://��v���鐔�l���Ȃ��Ƃ��̏���
				break;
			}

			//EnemyBullet_dameg_reaction(i);	//�����蔻��

			//�A�j���[�V�����p�^�[���X�V
			g_EnemyBullet[i].texAnime += 0.1;
			if (g_EnemyBullet[i].texAnime > 8.0f)
			{
				g_EnemyBullet[i].texAnime = 0.0f;
			}

			//��ʊO����
			if (g_EnemyBullet[i].pos.x < 0 )	//����ʂ̊O�ɏo��܂Œe���c���Ȃ�if (g_Bullet[i].pos.x > SCREEN_LIMIT_RIGHT)
			{
				g_EnemyBullet[i].use = false;	//��ʊO�ɏo���e������
			}
		}		
	}
	
}


//=============================================================================
// �`�揈��
//=============================================================================
void ENEMY_BULLET::DrawGame(void)
{
	for (int i = 0; i < ENEMY_MAX_BULLET; i++) {
		
		
		//�\���̂��g�p���Ȃ珈��
		if (g_EnemyBullet[i].use == true)
		{
			//�e�N�X�`���̃Z�b�g
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_EnemyBullet[i].texNo));

			//�`��
			DrawSpriteColorRotate
			(g_EnemyBullet[i].pos.x,
				g_EnemyBullet[i].pos.y,
				g_EnemyBullet[i].size.x,
				g_EnemyBullet[i].size.y,
				g_EnemyBullet[i].rot,
				g_EnemyBullet[i].color,
				g_EnemyBullet[i].texAnime,
				0.33f,
				0.33f,
				3
			);
		}
		
	}

}

void Set_Enemybullet(int EnemyBulletNo,D3DXVECTOR2 playerpos, D3DXVECTOR2 enemypos)
{
	for (int i = 0; i < ENEMY_MAX_BULLET; i++) {
		if (g_EnemyBullet[i].use == false) {
			switch (EnemyBulletNo)
			{
			case 1:	//�v���C���[�ǔ��e
				
				

				{
					g_EnemyBullet[i].pos = enemypos;		//�������W
					D3DXVECTOR2 temp = playerpos - enemypos;
					D3DXVec2Normalize(&temp, &temp);
					temp *= ENEMY_BULLET_SPEED;
					g_EnemyBullet[i].move = temp;
					g_EnemyBullet[i].use = true;		//�g�p��
					g_EnemyBullet[i].enemybulletNo = 1;
					return;						//1�������I��
				}
				
				

			case 2:	//�ł����e
				
				g_EnemyBullet[i].enemybulletNo = 2;

				{
					g_EnemyBullet[i].size.x = ENEMY_BULLET_BIG_SIZE_W;
					g_EnemyBullet[i].size.y = ENEMY_BULLET_BIG_SIZE_H;

					g_EnemyBullet[i].pos = enemypos;		//�������W
					D3DXVECTOR2 temp = playerpos - enemypos;
					D3DXVec2Normalize(&temp, &temp);
					temp *= ENEMY_BULLET_BIG_SPEED;
					g_EnemyBullet[i].move = temp;
					g_EnemyBullet[i].use = true;		//�g�p��

					return;						//1�������I��
				}
				
				
			case 3:	//��]�e
			
				g_EnemyBullet[i].enemybulletNo = 3;

				{
					g_EnemyBullet[i].pos = enemypos;		//�������W
					D3DXVECTOR2 temp = playerpos - enemypos;
					D3DXVec2Normalize(&temp, &temp);
					temp *= ENEMY_BULLET_ROT_SPEED;
					g_EnemyBullet[i].move = temp;
					g_EnemyBullet[i].use = true;		//�g�p��

					return;						//1�������I��

				}
				
			case 4: //�ʏ�e
			
				g_EnemyBullet[i].enemybulletNo = 4;

				{
					g_EnemyBullet[i].pos = enemypos;		//�������W
					g_EnemyBullet[i].use = true;		//�g�p��

					return;						//1�������I��
				}

			case 5:  //2WAY�e�@��
				
				g_EnemyBullet[i].enemybulletNo = 5;

				{
					g_EnemyBullet[i].pos = enemypos;		//�������W
					D3DXVECTOR2 temp = playerpos - enemypos;
					D3DXVec2Normalize(&temp, &temp);
					temp *= ENEMY_BULLET_WAYUP_SPEED;
					g_EnemyBullet[i].move = temp;
					g_EnemyBullet[i].use = true;		//�g�p��

					return;						//1�������I��
				}
			
			case 6:  //2WAY�e ��
				
				g_EnemyBullet[i].enemybulletNo = 6;

				{
					g_EnemyBullet[i].pos = enemypos;		//�������W
					D3DXVECTOR2 temp = playerpos - enemypos;
					D3DXVec2Normalize(&temp, &temp);
					temp *= ENEMY_BULLET_WAYUP_SPEED;
					g_EnemyBullet[i].move = temp;
					g_EnemyBullet[i].use = true;		//�g�p��

					return;						//1�������I��
				}




			default:
				break;
			}


		}
	}

}

//==========================
//�\���̂̐擪�A�h���X��Ԃ�
//==========================
ENEMY_BULLET* GetEnemyBullet(int num)
{
	return	&g_EnemyBullet[num];
}





//==================================================
//  �G�l�~�[�e�̃_���[�W����
//==================================================
//void EnemyBullet_dameg_reaction(int num)
//{
//	for (int i = 0; i < MAX_BULLET; i++)//�o���b�h�S�̂�����
//	{
//			if (GetBullet(i)->use == true)//�g�p��Ԃ�
//			{
//				if (CollisionBB(g_EnemyBullet[num].pos, GetBullet(i)->pos,
//					g_EnemyBullet[num].size, GetBullet(i)->size) == true)//����������
//				{
//					GetBullet(i)->use = false,
//						g_EnemyBullet[num].use = false;//����
//					break;
//
//
//				}
//			}
//	}
//}

