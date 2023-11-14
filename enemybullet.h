/*==============================================================================

   �G�̒e�̏���[enemybullet.h]
														 Author :�c������
														 Date   :2022/10/27
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "main.h"
#include "renderer.h"
#include "01_Scene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMY_MAX_BULLET		(100)	//�e�̐�
#define ENEMY_MAX_BIG_BULLET	(1)	//�e�̐�
#define ENEMY_MAX_ROT_BULLET	(100)	//�e�̐�
#define ENEMY_MAX_SIDE_BULLET	(100)	//�e�̐�
#define ENEMY_MAX_WAYUP_BULLET	(100)	//�e�̐�
#define ENEMY_MAX_WAYDOWN_BULLET (100)	//�e�̐�

class ENEMY_BULLET:public Game
{
private:

public:
	virtual HRESULT InitGame();	//������
	virtual void	UninitGame();//�I������
	virtual void	UpdateGame();//�X�V����
	virtual void    DrawGame();//�`�揈��

	
	D3DXVECTOR2		pos;		// �\�����W
	D3DXCOLOR		color;		// �F
	float			rot;		// �p�x
	D3DXVECTOR2		move;		// �ړ����x
	int				texNo;		// �e�N�X�`���ԍ�
	float			texAnime;			// �e�N�X�`���A�j��
	BOOL			use;		// �g�p����/���Ȃ�

	int				bighp = 10; //�ł����e�̗�
	int				rothp = 3;  //��]�e�̗�

	D3DXVECTOR2     size;       //�T�C�Y

	int	enemybulletNo;	//�o���b�g�p�^�[��

};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


ENEMY_BULLET* GetEnemyBullet(int num);				//�\���̂̐擪�A�h���X��Ԃ�


void    Set_Enemybullet(int EnemyBulletNum, D3DXVECTOR2 playerpos, D3DXVECTOR2 enemypos); //�o���b�h�I�����Ăяo��



void EnemyBullet_dameg_reaction(int num);
