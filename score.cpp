/*==============================================================================

   �X�R�A�i�����\���֌W�j���� [score.cpp]
														 Author :	AT12G_25_��������
														 Date   :	2022_09_29
--------------------------------------------------------------------------------

==============================================================================*/
#include	"score.h"

#include	"sprite.h"
#include	"texture.h"
#include	"player.h"
#include	"data.h"

#include	"01_Scene.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define	SCORE_SIZE_W	(43.0f * 0.75f)	//�l�p�`�̉��̃T�C�Y
#define	SCORE_SIZE_H	(42.0f * 0.75f)	//�l�p�`�̏c�̃T�C�Y

#define UPDATE_SCORE_NUMBER		(50)	// ���ۂ̃X�R�A�\���ŉ��Z���鐔�̕�����


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
SCORE::SCORE()
{
	//�e�N�X�`���t�@�C���p�X�i�[(���݌v1��)		�V���ɒǉ�����ꍇ�͉��̍s�Ƀt�@�C���p�X������
	g_ScoreTextureName[0] = (char*)"data\\texture\\number.png";
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
SCORE::~SCORE()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT SCORE::InitGame(void)
{

	Position = D3DXVECTOR2(800.0f, 30.0f);
	w = SCORE_SIZE_W;
	h = SCORE_SIZE_H;
	Rotate = 0.0f;
	Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	number = 0;
	display_number = 0;
	dizit = 5;
	type = 0;
	CurrentTexture = 0;
	anime = TRUE;
	use = TRUE;

	//	BG�e�N�X�`���̃��[�h
	for (int i = 0; i < MAX_SCORE_TEXTURE; i++)
	{
		TextureNoScore[i] = LoadTexture(g_ScoreTextureName[i]);
		if (TextureNoScore[i] == -1) {
			//�ǂݍ��݃G���[
			exit(999);//�����I��
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void SCORE::UninitGame(void)
{
	//�X�R�A�f�[�^�����Ă͂����Ȃ��������L�q
	if (GetScene() != SCENE_RESULT || GetScene() != SCENE_SHOP)
	{
		//�X�R�A�f�[�^���i�[����
		SetData(-1, -1, -1, number);
	}
}

//=============================================================================
// �X�V����(�\�����鐔�������ɓ����)
//=============================================================================
void SCORE::UpdateGame(void)
{

	// ���ۂɕ\�����鐔�̍X�V
	if (use == TRUE)
	{
		if (display_number < number)
		{
			if (display_number + 2000 < number)
			{
				display_number += 1000;
			}

			display_number += UPDATE_SCORE_NUMBER;
			if (display_number > number || anime == FALSE)
			{
				display_number = number;
			}
		}
		else if (display_number > number)
		{
			if (display_number > number + 2000)
			{
				display_number -= 1000;
			}
				display_number -= UPDATE_SCORE_NUMBER;
			if (display_number < number || anime == FALSE)
			{
				display_number = number;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void SCORE::DrawGame(void)
{
	{
		//// �\���������|���S���̒��_�o�b�t�@��ݒ�
		//UINT stride = sizeof(VERTEX_3D);
		//UINT offset = 0;
		//GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

		// �Q�c�\�������邽�߂̃}�g���N�X��ݒ�
		SetWorldViewProjection2D();

		//// �v���~�e�B�u�g�|���W�ݒ�
		//GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

		// �}�e���A���ݒ�
		MATERIAL material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	}

	for (int i = 0; i < SCORE_MAX; i++)
	{
		if (use == TRUE)
		{
			//�e�N�X�`���̃Z�b�g
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextureNoScore[CurrentTexture]));

			for (int j = 0; j < dizit; j++)
			{
				int		div = 1;
				int		diz = 0;

				for (int n = 1; n < (dizit - j); n++)
				{
					div *= 10;
				}

				diz = display_number / div;

				DrawSpriteColorRotate(Position.x + (w * j), Position.y, w, h, Rotate, Color, 0.0f + (1.0f * diz), 0.1f, 1.0f, 10);

			}
		}
	}
}

//=============================================================================
// �X�R�A���i�[����֐�
// �����Fint input_score (�i�[����X�R�A)
//=============================================================================
void SCORE::AddScore(int input_score)
{
	number += input_score;
}

//=============================================================================
// �X�R�A���擾����֐�
//=============================================================================
int SCORE::GetScore(void) const
{
	return number;
}

//====================================================================================================
// �ݒ��ύX����֐�
// �����FD3DXVECTOR2 pos (���W), float size (�����̑傫��), int diz (����), BOOL animation (�A�j���[�V��������/���Ȃ�)
//====================================================================================================
void SCORE::SettingScore(D3DXVECTOR2(pos), float size, int diz, BOOL animation)
{
	Position = pos;
	h = size;
	w = (float)(SCORE_SIZE_W / SCORE_SIZE_H)* size;
	dizit = diz;
	anime = animation;
}
