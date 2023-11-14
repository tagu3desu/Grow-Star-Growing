#pragma once

#include "main.h"
#include "renderer.h"
#include "01_Scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SKILL_UI_MAX (3)

class SKILL_UI : public Game
{
public:

	virtual HRESULT InitGame();	//������
	virtual void	UninitGame();//�I������
	virtual void	UpdateGame();//�X�V����
	virtual void    DrawGame();//�`�揈��

	D3DXVECTOR2		pos;			// �\�����W
	D3DXCOLOR		color;			// �F
	float			rot;			// �p�x
	D3DXVECTOR2		move;			// �ړ����x
	int				texNo;			// �e�N�X�`���ԍ�
	int				texGrayDownNo;	// �O���[�_�E���e�N�X�`���ԍ�
	int				texIconNo;		// �X�L���A�C�R���e�N�X�`���ԍ�
	BOOL			use;			// �g�p����/���Ȃ�

	D3DXVECTOR2     size;       //�T�C�Y
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
SKILL_UI	*GetSkillUI();		//�\���̂̐擪�A�h���X��Ԃ�SKILL_UI