#pragma once

#include"main.h"
#include"renderer.h"
#include"01_Scene.h"
//==============================
//�}�N����`
//==============================
#define	 EXPLOSION_MAX (100)	//�e�ő吔
#define  EXPLOSION_SPEED (10.0f) //�ړ����x

#define  EXPLOSION_SIZE_W (40)	//�����G�t�F�N�g�T�C�Y
#define  EXPLOSION_SIZE_Y (40)	//�����G�t�F�N�g�T�C�Y

#define EXPLOSION_ANIME_MAX (16)	//�A�j���[�V�����ő吔

class EXPLOSION : public Game
{
public:
	bool use;		//�g�p�t���O
	D3DXVECTOR2  size;		//�T�C�Y
	D3DXVECTOR2 pos;	//�\�����W
	D3DXVECTOR2	move;	//�ړ��X�s�[�h
	float	rot;	//��]���W
	int		texNo;	//�e�N�X�`���ԍ�

	float AnimePattern;	//�A�j���[�V�����p�^�[���ԍ�
	float AnimeSpeed;	//�A�j���[�V�����X�s�[�h


	virtual HRESULT InitGame();
	virtual void	UninitGame();
	virtual void	UpdateGame();
	virtual void	DrawGame();
};

//===========================
//�v���g�^�C�v�錾
//============================

EXPLOSION* GetExplosion();	//�\���̂̐擪�|�C���^���擾
void	   SetExplosion(D3DXVECTOR2 pos, float animespeed);	//�e�̔���