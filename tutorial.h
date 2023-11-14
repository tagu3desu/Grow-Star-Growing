/*=================================================================
�`���[�g���A���̏���[tutorial.h]


===================================================================*/
#pragma once
#include"01_Scene.h"



class TUTORIAL : public Game
{
public:
	virtual HRESULT InitGame();	//������
	virtual void    UninitGame(); //�I������
	virtual void	UpdateGame();	//�X�V����
	virtual void	DrawGame();	//�`�揈��
	int texNo;					//�e�N�X�`��

	bool			Use;		//�g�p
	D3DXVECTOR3		Position;	//�\�����W
	D3DXVECTOR2		Size;		//�T�C�Y
	D3DXCOLOR		Color;		//�F
	float			Rotate;		//�p�x

};

//========================
//�v���g�^�C�v�錾
//========================
void Set_BG(int x);
