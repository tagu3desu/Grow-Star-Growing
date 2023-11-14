/*==============================================================================

   �G�̏���[enemy.cpp]
														 Author :�c������
														 Date   :2022/10/27
--------------------------------------------------------------------------------

==============================================================================*/

#include "enemy.h"
#include "sprite.h"
#include "texture.h"
#include "enemybullet.h"
#include "player.h"
#include "bullet.h"
#include "kirakira.h"

#include "collision.h"

//======================
//�}�N����`
//======================
// 
//======================
//�v���g�^�C�v�錾
//======================
// 
//======================
//�O���[�o���ϐ�
//======================
 
static ENEMY g_Enemy[ENEMY_MAX]; //�G�l�~�[�I�u�W�F�N�g
ENEMY_BULLET* enemy_bullet;


//==========================
//������
//==========================
HRESULT ENEMY::InitGame()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//�e�N�X�`�����[�h
		g_Enemy[i].Texno = LoadTexture((char*)"data\\texture\\�C���x�[�_�[.png");

		//�\���̂̏�����
		g_Enemy[i].Pos.x = 0.0f;
		g_Enemy[i].Pos.y = 0.0f;	//540����0�͈̔͂ŏo��
		g_Enemy[i].Use = false;
		g_Enemy[i].countE = 0;
		g_Enemy[i].FrameWait = 0;
		g_Enemy[i].bulletrate = 0;
		g_Enemy[i].BulletType = 0;
		g_Enemy[i].size.x = ENEMY_SIZE_W;
		g_Enemy[i].size.y = ENEMY_SIZE_H;
		g_Enemy[i].enemyNo = 1;
		g_Enemy[i].move = D3DXVECTOR2(ENEMY_SPEED, 0.0f);
		g_Enemy[i].secondmove = D3DXVECTOR2(0.0f, ENEMY_SPEED);
		g_Enemy[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Enemy[i].MoveCount = 0;
		
		switch (GetScene())
		{

		case SCENE_GAME:
		
			g_Enemy[i].Texno = LoadTexture((char*)"data\\texture\\��1.png");
			break;

		case SCENE_STAGE02:
			
			g_Enemy[i].Texno = LoadTexture((char*)"data\\texture\\�N���I�l4.png");

			break;

		case SCENE_STAGE03:
			
			g_Enemy[i].Texno = LoadTexture((char*)"data\\texture\\�r2.png");

			break;

		case SCENE_STAGE04:
			
			g_Enemy[i].Texno = LoadTexture((char*)"data\\texture\\�l��4.png");

			break;


		default:
			break;
		}
		

	}
	return S_OK;	//����I��
}
//=============================
//�I������
//=============================
void ENEMY::UninitGame()
{

}
//==============================
//�X�V����
//==============================
void ENEMY::UpdateGame()
{

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		
		if (g_Enemy[i].Use == true)	//�G�l�~�[��true�̎�
		{
			switch (g_Enemy[i].enemyNo)
			{
			case 1:	//�G���G
				g_Enemy[i].Pos -= g_Enemy[i].move;	//���Ɉړ�
				break;

			case 2:
				g_Enemy[i].Pos -= g_Enemy[i].move;	//���Ɉړ�
				break;

			case 3:

				g_Enemy[i].Pos -= g_Enemy[i].move;	//�������
				break;

			case 4 :

				g_Enemy[i].Pos -= g_Enemy[i].move;	//�ォ�牺
				break;
			case 5:
				g_Enemy[i].MoveCount++;
				g_Enemy[i].Pos -= g_Enemy[i].move;
				if (g_Enemy[i].MoveCount <= 60)
				{
					g_Enemy[i].Pos += g_Enemy[i].secondmove;
				}
				else if (g_Enemy[i].MoveCount > 60 && g_Enemy[i].MoveCount < 180)
				{
					g_Enemy[i].Pos -= g_Enemy[i].secondmove;
				}
				else if (g_Enemy[i].MoveCount > 180 && g_Enemy[i].MoveCount < 240)
				{
					g_Enemy[i].Pos += g_Enemy[i].secondmove;

				}
				else if (g_Enemy[i].MoveCount > 240 && g_Enemy[i].MoveCount < 300)
				{
					g_Enemy[i].Pos -= g_Enemy[i].secondmove;
					g_Enemy[i].MoveCount = 0;
				}

			default:
				break;
			}
			Enemy_dameg_reaction(i);//�G�l�~�[���o���b�h�ɓ������ĂȂ������Ă���









			
			//��ʊO�`�F�b�N
			if (g_Enemy[i].Pos.x < -50)	//����ʊO-50�ɂȂ��
			{
				//�G������
				g_Enemy[i].Use = false;
			}                               



			
				g_Enemy[i].bulletrate += 1.0f;
				if(g_Enemy[i].Pos.x>200){
					if (((int)g_Enemy[i].bulletrate % 100) == 99)
					{
						Set_Enemybullet(g_Enemy[i].BulletType, GetPlayer()->Position, g_Enemy[i].Pos);
					}
				}
				                                                     
		}

		



	}
}
//================================
//�`�揈��
//================================
void ENEMY::DrawGame()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].Use == true)	//�G�l�~�[��true�̎��̂�
		{
			
				//�e�N�X�`���̃Z�b�g
				GetDeviceContext()->PSSetShaderResources(0, 1,
					GetTexture(g_Enemy[i].Texno));

				//�X�v���C�g�̕`��
				DrawSpriteColorRotate
				(
					g_Enemy[i].Pos.x,
					g_Enemy[i].Pos.y,
					g_Enemy[i].size.x,
					g_Enemy[i].size.y,
					g_Enemy[i].Rot,
					g_Enemy[i].color,	//�Ƃ肠�����̐F
					0,	//�p�^�[���ԍ�
					1.0f,	//�p�^�[���̉��T�C�Y
					1.0f,	//�p�^�[���̏c�T�C�Y
					1		//�p�^�[���̉��̐�
				);
			
		}
	}
}
//================================
//�\���̂̐擪�̃|�C���^��Ԃ�
//================================
ENEMY* GetEnemy(int num)
{
	return &g_Enemy[num];
}

//==========================================
//�G�l�~�[�Ăяo�����I��
// �G�l�~�[�̎��,�G�l�~�[�e�̎��,���WX�A���WY
//
//==========================================
void SetEnemy(int EnemyNo,int EnemyBulletNo,float EnemyX,float EnemyY)
{

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].Use == false) {
			switch (EnemyNo)
			{
			case 1:
			{
				g_Enemy[i].Pos = D3DXVECTOR2(EnemyX, EnemyY);
				g_Enemy[i].move = D3DXVECTOR2(ENEMY_SPEED,0.0f);
				g_Enemy[i].Use = true;
				break;
			}
			case 2:
				
			{
				g_Enemy[i].Pos = D3DXVECTOR2(EnemyX, EnemyY);
				g_Enemy[i].size.x = ENEMY_BIG_SIZE_W;
				g_Enemy[i].size.y = ENEM_BIG_SIZE_H;
				g_Enemy[i].move = D3DXVECTOR2(ENEMY_BIG_SPEED, 0.0f);
				g_Enemy[i].Use = true;
				break;
				
			}		

			case 3:
			{
				g_Enemy[i].Pos = D3DXVECTOR2(EnemyX, EnemyY);
				g_Enemy[i].move = D3DXVECTOR2(ENEMY_SPEED, 1.0f);
				g_Enemy[i].Use = true;
				break;


			}

			case 4:
			{
				g_Enemy[i].Pos = D3DXVECTOR2(EnemyX, EnemyY);
				g_Enemy[i].move = D3DXVECTOR2(ENEMY_SPEED, -1.0f);
				g_Enemy[i].Use = true;
				break;


			}
			case 5:
				g_Enemy[i].Pos = D3DXVECTOR2(EnemyX, EnemyY);
				g_Enemy[i].move = D3DXVECTOR2(ENEMY_SPEED, 0.0f);
				g_Enemy[i].secondmove = D3DXVECTOR2(0.0f,ENEMY_SPEED);
				g_Enemy[i].Use = true;
				break;

			default:
				break;
			}

			g_Enemy[i].enemyNo = EnemyNo;
			g_Enemy[i].BulletType = EnemyBulletNo;
			return;
		}
	}

}


//==================================================
//�G�l�~�[�̃_���[�Wreaction
//==================================================

void Enemy_dameg_reaction(int num)
{
	for (int i = 0; i < MAX_BULLET; i++)//�o���b�h�S�̂�����
	{

		if (GetBullet(i)->use == true)//�g�p��Ԃ�
		{
			if (CollisionBB(GetBullet(i)->pos, g_Enemy[num].Pos,
				GetBullet(i)->size, g_Enemy[num].size) == true)//����������
			{
				
				//	Kirakira_bone(g_Enemy[num].Pos, 3);//�R�L���L���𐶐�����


				//	GetBullet(i)->use = false,
				//		g_Enemy[num].Use = false;//����
					break;
				
				
			}
		}

		
	}
}

