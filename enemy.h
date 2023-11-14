/*==============================================================================

   �G�̏���[enemy.h]
														 Author :�c������
														 Date   :2022/10/27
--------------------------------------------------------------------------------

==============================================================================*/

#pragma once			//�𗧂���
#include "01_Scene.h"

static const int  ENEMY_MAX = 100;

static const int ENEMY_SIZE_W = 50;		//�G�l�~�[�̉�
static const int ENEMY_SIZE_H = 50;		//�G�l�~�[�̍���
static const int ENEMY_SPEED = 1;	//�G�l�~�[�̈ړ����x

static const int ENEMY_BIG_SIZE_W = 60;
static const int ENEM_BIG_SIZE_H = 60;
static const int ENEMY_BIG_SPEED = 2;

class ENEMY: public Game
{
public:
	bool		Use;	//�G�g�p�t���O
	D3DXVECTOR2 Pos;	//�\�����W
	float		Rot;	//��]�p�x
	int			Texno;	//�e�N�X�`���ԍ�
	D3DXVECTOR2 size;   //�L�����N�^�[�T�C�Y
	int			MoveCount;	//�ړ��p

	//�e�֌W
	float		FrameWait; //�����܂ł̃J�E���^�[
	int			countE;	   //���X�|�[���܂ł̎���
	float		bulletrate;//�ˌ�����^�C�~���O
	int			BulletType;//�G�l�~�[�e�̎��
	D3DXVECTOR2 move;
	D3DXVECTOR2 secondmove;


	int			enemyNo;
	D3DXCOLOR   color;


	virtual HRESULT InitGame();	//������
	virtual void	UninitGame();//�I������
	virtual void	UpdateGame();//�X�V����
	virtual void    DrawGame();//�`�揈��
private:

};


//========================
//�v���g�^�C�v�錾
//========================
ENEMY* GetEnemy(int num);				//�\���̂̐擪�̃|�C���^��Ԃ�


void SetEnemy(int EnemyNo, int EnemyBulletNo, float EnemyX, float EnemyY);	//�G�l�~�[�I���Ăяo��

void Enemy_dameg_reaction(int num);//�G�l�~�[�̂��߁[������
