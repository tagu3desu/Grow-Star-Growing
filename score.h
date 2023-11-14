/*==============================================================================

   �X�R�A�i�����\���֌W�j����[score.h]
														 Author :	AT12G_25_��������
														 Date   :	2022_09_29
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
// �N���X��`
//*****************************************************************************
class	SCORE: public Game
{
public:
	SCORE();		//�R���X�g���N�^
	~SCORE();		//�f�X�g���N�^
	HRESULT InitGame(void);
	void UninitGame(void);
	void UpdateGame(void);
	void DrawGame(void);
	void AddScore(int input_score);
	int GetScore(void) const;		//���݂̃X�R�A��Ԃ�
	void SettingScore(D3DXVECTOR2(pos), float size, int diz, BOOL animation);	// �ݒ��ύX����
private:
	/*	�萔	*/
	static const int SCORE_MAX = 10;			//�X�R�A�̍ő包��
	//�e�N�X�`��
	static const int MAX_SCORE_TEXTURE = 1;		//�t�B�[���h�w�i�e�N�X�`���̍ő吔

	/*	�ϐ�	*/
	D3DXVECTOR2		Position;		// �\�����W
	float			w, h;			// �T�C�Y
	D3DXCOLOR		Color;			// �F
	float			Rotate;			// �p�x
	int				number;			// �i�[���鐔
	int				display_number;	// �\�����鐔
	int				dizit;			// ����
	int				type;			// �\���^�C�v(0 : �S����\�� 1: �\��������ϓ�������)
	BOOL			anime;			// �A�j���[�V��������/���Ȃ�
	BOOL			use;			// �g�p����/���Ȃ�
	//�e�N�X�`��
	char* g_ScoreTextureName[MAX_SCORE_TEXTURE];	//�e�N�X�`���t�@�C���p�X
	int				TextureNoScore[MAX_SCORE_TEXTURE];		//�e�N�X�`���C���f�b�N�X
	int				CurrentTexture;							//�g�p����e�N�X�`���ԍ�
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


