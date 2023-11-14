#pragma once
#include "main.h"
#include "01_Scene.h"

//*
//�ړ��@�ړ���̃w�b�_�[��ǂݍ��ނ���
enum STAGE
{
	STAGE_00,	//�f�t�H���g
	STAGE_01,	//1
	STAGE_02,	//2
	STAGE_03,   //3
	STAGE_04,   //3
};
//*/

class Progress :public Game
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
	BOOL			use;		// �g�p����/���Ȃ�

	D3DXVECTOR2     size;       //�T�C�Y
	int			time;		//����

	
};


void	Set_BOSSstage(STAGE stage_num);//�X�e�[�W�Ǝ��Ԃ�ݒ肷���I

void	Set_stage(SCENE scene);

int Get_time();
