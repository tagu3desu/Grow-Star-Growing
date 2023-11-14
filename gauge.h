#pragma once

#include "main.h"
#include "renderer.h"
#include "01_Scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GAUGE_MAX (1)
#define GAUGE2_MAX (1)

class GAUGE: public Game
{
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
	BOOL			use;		// �g�p����/���Ȃ�

	D3DXVECTOR2     size;       //�T�C�Y
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
GAUGE	*GetGauge();		//�\���̂̐擪�A�h���X��Ԃ�
GAUGE	*GetGauge2();		//�\���̂̐擪�A�h���X��Ԃ�
