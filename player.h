/*==============================================================================

   �v���C���[����[player.h]
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

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class PLAYER:public Game
{
private:

public:
	virtual HRESULT InitGame();	//������
	virtual void	UninitGame();//�I������
	virtual void	UpdateGame();//�X�V����
	virtual void    DrawGame();//�`�揈��

	BOOL			use;		// �g�p����/���Ȃ�
	D3DXVECTOR2		Position;	// �\�����W
	float			Rotate;		// �p�x
	int				texNo;		// �e�N�X�`���ԍ�
    D3DXVECTOR2     size;//�v���C���[�̃T�C�Y
	D3DXCOLOR		Color;		// �F
	

	int				Bulletrate;	//�e���ˊԊu
	bool			ShotFlag;	//�e���ˎ�

	int				Hp;			//�̗�
	int				HptexNo;	//HP�e�N�X�`��
	D3DXVECTOR2		HpSize;		//HP�T�C�Y
	D3DXVECTOR2		HpPos;		//HP���W
					


	int				HugetexNo;	//���剻UI
	D3DXVECTOR2		HugePos;	//���剻UI���W
	D3DXVECTOR2		HugeSize;	//���剻UI�傫��
	int				HugeCount;	//���剻�p�t���[���J�E���g
	float			HugeRotate; //���剻�pUI�p�x
	bool			ChangeHuge;
	bool			ResetHuge;

	int				energy;		//�L���L���̎c��
	int				gain;		//�L���L���擾���̑�����


	bool			SizeUp;	//���剻����
	bool			tackle;	//�^�b�N��
	int				FrameCaount; //�t���[���J�E���g
	int				AtacckDelay;	//�U���d��
	int				TackleDamege;//�^�b�N���̃_���[�W
	

	int				SkillType[3];			//�U�����(���A��A�E��3���)
	int				SkillUsageMax[3];		//�X�L���g�p�񐔏��(���A��A�E��3���)
	int				SkillUsageCount[3];		//�c��̃X�L���g�p��(���A��A�E��3���)
	int				SkillCoolTime[3];		//�X�L���̃N�[���^�C���J�E���g(���A��A�E��3���)
	int				SkillCoolTimeMax[3];	//�X�L���̃N�[���^�C���̍ő吔(���A��A�E��3���)

};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


PLAYER	*GetPlayer();		//�\���̂̐擪�A�h���X��Ԃ�

void Player_dameg_reaction();