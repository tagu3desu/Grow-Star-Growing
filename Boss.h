/*==============================================================================

   �{�X�̏���[Boss.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#include"01_Scene.h"

static const int BOSS_SIZE_W = 320;	//�{�X�̉�
static const int BOSS_SIZE_H = 320;	//�{�X�̍���
static const int BOSS_SPEED = 2.0f;		//�{�X�̈ړ����x
static const int PARTS_MAX = 10;	//�{�X���ʂ̍ő吔

class BOSS_01 :public Game
{
public:
	virtual HRESULT InitGame();	//������
	virtual void	UninitGame();//�I������
	virtual void	UpdateGame();//�X�V����
	virtual void    DrawGame();//�`�揈��

	bool Use;	//�{�X�d�l�t���O
	D3DXVECTOR2 Pos;	//�\�����W
	float		Rot;	//��]�p�x
	int			TexNo;	//�e�N�X�`���ԍ�
	int			BreakTexno;
	bool		tacklehit;
	int			tacklecount;

	int HP; //�{�X��HP

	D3DXVECTOR2	size;	//�T�C�Y
	int FrameWait;	

	D3DXVECTOR2 move;
	D3DXCOLOR	color;
	int		BossNo;

	int		Count; //�e�X�g
	

	int		PartsIndex[PARTS_MAX];		//�{�X���ʂ̃C���f�b�N�X���i�[����z��
};

//========================
//�v���g�^�C�v�錾
//========================
BOSS_01 *GetBoss_01();	//�\���̂̐擪�A�h���X��Ԃ�

void SetBoss_01(int Boss_01Num,float BossX, float BossY);	//�{�X�Ăяo��(X,Y)

void Boss_damege_reaction();
