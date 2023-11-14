/*==============================================================================

   �e�̏��� [bullet.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include	<stdlib.h>
#include	"bullet.h"

#include	"sprite.h"
#include	"texture.h"
#include	"00_soundmain.h"
#include	"01_Scene.h"
#include	"player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define	BULLET_SIZE_W	(50.0f)	//�l�p�`�̉��̃T�C�Y
//#define	BULLET_SIZE_H	(50.0f)	//�l�p�`�̏c�̃T�C�Y
//#define BULLET_SPEED	(4.0f)	//�e�̑���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

BULLET	g_Bullet[MAX_BULLET];	// �e�I�u�W�F�N�g


/*�e�̎�ނ��Ƃ̐ݒ�l*/
//�e�̎�ނ̍ő�l
static const int	BULET_TYPE_MAX = 8;
                                                                //0,     1,     2,     3,     4,     5,     6,		7
//�l�p�`�̉��̃T�C�Y
static const float	BULLET_SIZE_W[BULET_TYPE_MAX]	=		{ 50.0f, 50.0f, 50.0f, 50.0f, 20.0f, 50.0f, 150.0f, 50.0f};
//�l�p�`�̏c�̃T�C�Y
static const float	BULLET_SIZE_H[BULET_TYPE_MAX]	=		{ 50.0f, 50.0f, 50.0f, 50.0f, 20.0f, 50.0f, 150.0f, 50.0f};
//�e��X�������̑���
static const float	BULLET_SPEED_X[BULET_TYPE_MAX]	=		{  5.0f,  5.0f,  5.0f,  5.0f,  2.0f,  8.0f,  10.0f,  6.0f};
//�e��Y�������̑���
static const float	BULLET_SPEED_Y[BULET_TYPE_MAX]	=		{  0.0f,  0.7f,  0.0f,  0.0f,  0.0f,  0.0f ,  0.0f,  0.0f};
//�e�̃_���[�W��
static const int	BULLET_DAMAGE[BULET_TYPE_MAX]	=		{     2,     2,     1,     1,     2,     2,		10,		1};
//�e���ˎ��̃L���L�������
static const int	BULLET_DEMAND_KIRAKIRA[BULET_TYPE_MAX] = {    2,     5,     5,     5,     2,     2,		 1,		1};
//�e���˃X�L���g�p�񐔂̍ő吔(-1�̏ꍇ�͖���)
static const int	BULLET_USAGE_MAX[BULET_TYPE_MAX]	=	{    -1,    10,     8,     5,    3,     10 ,	 1,   -1};
//�e���˃X�L���g�p�񐔂̍ő吔(-1�̏ꍇ�͖���)
static const int	BULLET_COOL_TIME_MAX[BULET_TYPE_MAX] =	{   -1, 5 * 60, 5 * 60, 10 * 60,10 * 60,5 * 60,10 * 60,-1};

//��]�e�̔��a
static const float	BULLET_TURN_RADIUS = 150.0f;

//=============================================================================
// ����������
//=============================================================================
HRESULT  BULLET::InitGame(void)
{
	//�\���̂��ׂď���
	for (int i = 0; i < MAX_BULLET; i++)
	{
		//�e�N�X�`�����[�h
		g_Bullet[i].texNo = LoadTexture((char*)"data\\texture\\01_kirakirabullet.png");//�e�N�X�`���t�@�C���p�X

		g_Bullet[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_Bullet[i].size.x = BULLET_SIZE_W[0];
		g_Bullet[i].size.y = BULLET_SIZE_H[0];
		g_Bullet[i].rot = 0.0f;
		g_Bullet[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED_X[0], BULLET_SPEED_Y[0]);
		g_Bullet[i].texAnime = 0.0f;
		g_Bullet[i].use = false;
		g_Bullet[i].bulletNo = 0;
		g_Bullet[i].damage = 0;
		g_Bullet[i].num_attack = 0;
		g_Bullet[i].revolution_angle = 0.0f;
		g_Bullet[i].circle_origin = D3DXVECTOR2(0.0f, 0.0f);
		g_Bullet[i].time_count = 0;
		g_Bullet[i].buy = false;
	}

	

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void BULLET::UninitGame(void)
{


}

//=============================================================================
// �X�V����
//=============================================================================
void BULLET::UpdateGame(void)
{
	//�\���̂�S�ď���
	for (int i = 0; i < MAX_BULLET; i++)
	{
		//�\���̂��g�p���Ȃ珈��
		if (g_Bullet[i].use == true)
		{
			switch (g_Bullet[i].bulletNo)
			{
			case 0:		//�ʏ�L���L���e
				//���W�̍X�V
				g_Bullet[i].pos += g_Bullet[i].move;
				break;

			case 1:		//�O���L���L���e
				//���W�̍X�V
				g_Bullet[i].pos += g_Bullet[i].move;
				break;

			case 2:		//�ђʒe
				//���W�̍X�V
				g_Bullet[i].pos += g_Bullet[i].move;
				break;

			case 3:		//��]�e
				//���W�̍X�V
				g_Bullet[i].revolution_angle += 0.07f;
				g_Bullet[i].pos.x = -cos(g_Bullet[i].revolution_angle) * BULLET_TURN_RADIUS + g_Bullet[i].circle_origin.x;
				g_Bullet[i].pos.y =  sin(g_Bullet[i].revolution_angle) * BULLET_TURN_RADIUS + g_Bullet[i].circle_origin.y;
				if (g_Bullet[i].revolution_angle > 6.28318531)
				{
					g_Bullet[i].revolution_angle = 0.0f;
					g_Bullet[i].use = false;
				}

				break;

			case 4:		//�y���e
				//���W�̍X�V
				g_Bullet[i].pos += g_Bullet[i].move;
				if (g_Bullet[i].time_count >= 90)
				{
					for (int a = 0; a < 5; a++)
					{
						SetBullet(7, D3DXVECTOR2(g_Bullet[i].pos.x, (g_Bullet[i].pos.y - 100.0f + a * 50.0f)));
					}
					g_Bullet[i].use = false;
				}
				break;

			case 5:		//�����e
				//���W�̍X�V
				if (g_Bullet[i].time_count >= 60)
				{
					g_Bullet[i].pos += g_Bullet[i].move;
				}
				break;

			case 6:		//�����
				//���W�X�V
				g_Bullet[i].pos += g_Bullet[i].move;
				break;

			case 7:		//�y�􂵂���
				//���W�X�V
				g_Bullet[i].pos += g_Bullet[i].move;
				break;

			default://��v���鐔�l���Ȃ��Ƃ��̏���
				break;
			}

			//�A�j���[�V�����p�^�[���X�V
			g_Bullet[i].texAnime += 0.1;
			if (g_Bullet[i].texAnime > 8.0f)
			{
				g_Bullet[i].texAnime = 0.0f;
			}

			g_Bullet[i].time_count++;		//���Ԃ̒ǉ�

			//��ʊO�`�F�b�N
			if (g_Bullet[i].pos.x > (SCREEN_LIMIT_RIGHT - g_Bullet[i].size.x / 2))	//����ʂ̊O�ɏo��܂Œe���c���Ȃ�if (g_Bullet[i].pos.x > SCREEN_LIMIT_RIGHT)
			{
				g_Bullet[i].use = false;	//��ʊO�ɏo���e������
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void BULLET::DrawGame(void)
{
	//�\���̂�S�Ē��ׂ�
	for (int i = 0; i < MAX_BULLET; i++)
	{
		//�\���̂��g�p���Ȃ珈��
		if (g_Bullet[i].use == true)
		{
			//�e�N�X�`���̃Z�b�g
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Bullet[i].texNo));

			//�`��
			DrawSpriteColorRotate
			(g_Bullet[i].pos.x, g_Bullet[i].pos.y,
				g_Bullet[i].size.x, g_Bullet[i].size.y,
				g_Bullet[i].rot, 
				g_Bullet[i].color,
				g_Bullet[i].texAnime, 
				0.33f, 
				0.33f,
				3);
		}
	}
}


//==========================
//�\���̂̐擪�A�h���X��Ԃ�
//==========================
BULLET		*GetBullet(int num)
{
	return	&g_Bullet[num];
}

//==================================
//�e���ˎ��̏���L���L������Ԃ�
//==================================
int			GetBulletDemand(int index)
{
	return BULLET_DEMAND_KIRAKIRA[index];
}

//==================================
//�e���˃X�L���g�p�񐔂̍ő吔��Ԃ�
//==================================
int			GetBulletUsageMax(int index)
{
	return BULLET_USAGE_MAX[index];
}

//==================================
//�e���˃N�[���^�C���̍ő吔��Ԃ�
//==================================
int			GetBulletCoolTimeMax(int index)
{
	return BULLET_COOL_TIME_MAX[index];
}

//==========================
//�e�̔���
//in	�e��ID�ԍ�, �������W
//==========================
void	SetBullet(int BulletNo, D3DXVECTOR2 pos)
{
	int count = 0;	//�������˂���ꍇ�̃J�E���g�ϐ�

	//�\���̂�S�Ē��ׂ�
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (g_Bullet[i].use == false )	//���g�p�̍\���̂�������&�v���C���[�̏����L���L���ʂƔ�r
		{
			//�e�̏����Z�b�g
			g_Bullet[i].pos = pos;																//�������W
			g_Bullet[i].size = D3DXVECTOR2(BULLET_SIZE_W[BulletNo], BULLET_SIZE_H[BulletNo]);	//�e�̃T�C�Y
			g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED_X[BulletNo], BULLET_SPEED_Y[BulletNo]);	//�e�̃X�s�[�h
			g_Bullet[i].texAnime = 0.0f;
			g_Bullet[i].use = true;																//�g�p��
			g_Bullet[i].bulletNo = BulletNo;													//�e��ID�ԍ�
			g_Bullet[i].damage = BULLET_DAMAGE[BulletNo];										//�e�̃_���[�W��
			g_Bullet[i].num_attack = 1;															//�ʏ��1��G�ɓ�����Ƃ�������
			g_Bullet[i].time_count = 0;															//��������Ă���o�������Ԃ̃J�E���g�p

			if (g_Bullet[i].bulletNo != 7)	//7�ŉ��o�����Ƃ�����~�܂�
			{
				PlayEffect(Ebullet, 0.5f);
			}

			//�e�̎�ނ��Ƃ̓��ꏈ��(������ɂ��L���L������͂����ōs��)
			switch (BulletNo)
			{
			case 0:
									
				return;						//1�������I��
				break;
			case 1:
				count++;
				switch (count)
				{
				case 1:
					g_Bullet[i].move.y *= -1.0f;
					break;
				case 2:
					g_Bullet[i].move.y = 0.0f;
					break;
				case 3:
										
					return;					//3�������I��
					break;
				default:
					break;
				}
				break;
			case 2:
				g_Bullet[i].pos.x += 50.0f;
				g_Bullet[i].num_attack = 5;	//�ő�5��܂�
				
				return;						//1�������I��
				break;
			case 3:
				g_Bullet[i].circle_origin = pos;
				g_Bullet[i].circle_origin.x += (50.0f + BULLET_TURN_RADIUS);
				g_Bullet[i].num_attack = -1;
				g_Bullet[i].pos.x += 50.0f;
				g_Bullet[i].revolution_angle = 0.0f;
				return;
				break;
			case 4:
				g_Bullet[i].pos.x += 50.0f;
				return;
				break;
			case 5:
				g_Bullet[i].pos.x += 50.0f;
				return;
				break;
			case 6:
				g_Bullet[i].pos.x = pos.x + 100.0f;
				g_Bullet[i].num_attack = -1;	//�ő�5��܂�
				return;
				break;
			case 7:
				return;
				break;

			default:
				return;
				break;
			}
		}
	}
}
