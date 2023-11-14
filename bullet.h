/*==============================================================================

   �e�̏���[bullet.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"
#include "01_Scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_BULLET		(100)	//�e�̐�


class BULLET: public Game
{
private:

public:
	virtual HRESULT InitGame();	//������
	virtual void	UninitGame();//�I������
	virtual void	UpdateGame();//�X�V����
	virtual void    DrawGame();//�`�揈��


	D3DXVECTOR2		pos;				// �\�����W
	D3DXCOLOR		color;				// �F
	float			rot;				// �p�x
	D3DXVECTOR2		move;				// �ړ����x
	int				texNo;				// �e�N�X�`���ԍ�
	float			texAnime;			// �e�N�X�`���A�j��
	BOOL			use;				// �g�p����/���Ȃ�


	D3DXVECTOR2     size;				// �e�̃T�C�Y
	int				damage;				// �e�������������̃_���[�W��
	int				num_attack;			// �c��U����(0�ɂȂ�ƒe�����ł���)
	float			revolution_angle;	// ��]�e�̌��]�p�x
	D3DXVECTOR2		circle_origin;		// ��]�e�̒��S���W

	int	bulletNo;	//�o���b�g�p�^�[��

	int time_count;	//�e����������Ă���o��������

	bool buy;
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


BULLET	*GetBullet(int num);				//�\���̂̐擪�A�h���X��Ԃ�
void	SetBullet(int BulletNo, D3DXVECTOR2 pos);	//�e�̔��� in:�e��ID�ԍ�,�������W

//==================================
//�e���ˎ��̏���L���L������Ԃ�
//==================================
int			GetBulletDemand(int index);

//==================================
//�e���˃X�L���g�p�񐔂̍ő吔��Ԃ�
//==================================
int			GetBulletUsageMax(int index);

//==================================
//�e���˃N�[���^�C���̍ő吔��Ԃ�
//==================================
int			GetBulletCoolTimeMax(int index);