/*==============================================================================

   �G�{�X�̕��ʏ���[boss_parts.h]
														 Author :��������
														 Date   :2022/12/22
--------------------------------------------------------------------------------

==============================================================================*/

#pragma once			//�𗧂���
#include "01_Scene.h"

static const int  BOSS_PARTS_MAX = 100;

static const int BOSS_PARTS_SIZE_W = 100;		//�{�X�̕��ʂ̉�
static const int BOSS_PARTS_SIZE_H = 100;		//�{�X�̕��ʂ̍���
//static const int BOSS_PARTS_SPEED = 1;	//�G�l�~�[�̈ړ����x
//
//static const int BOSS_PARTS_BIG_SIZE_W = 60;
//static const int ENEM_BIG_SIZE_H = 60;
//static const int BOSS_PARTS_BIG_SPEED = 2;

class BOSS_PARTS: public Game
{
public:
	bool		Use;		//�{�X���ʎg�p�t���O
	D3DXVECTOR2 Pos;		//�\�����W(�{�X�̒��S���W����̑��΍��W)
	float		Rot;		//��]�p�x
	int			Texno;		//�e�N�X�`���ԍ�
	D3DXVECTOR2 size;		//�L�����N�^�[�T�C�Y

	int			HP;			//�{�X���ʂ�HP
	D3DXVECTOR2	BossPos;	//�{�X�̒��S���W
	bool		tacklehit;
	int			tacklecount;


	//�e�֌W
	float		FrameWait; //�����܂ł̃J�E���^�[
	int			countE;	   //���X�|�[���܂ł̎���
	float		bulletrate;//�ˌ�����^�C�~���O
	int			BulletType;//�G�l�~�[�e�̎��
	D3DXVECTOR2 move;


	int			BossPartsNo;	//�{�X���ʂ̎��(���ݖ��g�p)
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
BOSS_PARTS* GetBossParts(int num);				//�\���̂̐擪�̃|�C���^��Ԃ�


int SetBossParts(float posx, float posy, int HP, D3DXVECTOR2 BOSSposs);	//�G�l�~�[�I���Ăяo��

void BossParts_damege_reaction(int num);//�G�l�~�[�̂��߁[������


bool Get_BossPartslivis(); // �{�X�̃p�[�c�Ő����Ă���̂����邩�ǂ����@�@�i����Ftrue�@���Ȃ��Ffalse
