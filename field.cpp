#include "field.h"
#include "00_title.h"
/*==============================================================================

   �t�B�[���h���� [field.cpp]		�v���g�^�C�v��
														 Author :	��������
														 Date   :	2022_10_27
--------------------------------------------------------------------------------

==============================================================================*/


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


FIELD::FIELD()
{
	//�e�N�X�`���t�@�C���p�X�i�[(���݌v2��)		�V���ɒǉ�����ꍇ�͉��̍s�Ƀt�@�C���p�X������
	g_FieldTextureName[0] = (char*)"data\\texture\\haikei01.png";
	g_FieldTextureName[1] = (char*)"data\\texture\\Result.png";



	CurrentTexture = 0;
}

FIELD::~FIELD()
{

}

HRESULT FIELD::InitGame()
{
	Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Rotate = 0;
	Speed = 0.0f;

	//	BG�e�N�X�`���̃��[�h
	for (int i = 0; i < MAX_FIELD_TEXTURE; i++)
	{
		TextureNoField[i] = LoadTexture(g_FieldTextureName[i]);
		if (TextureNoField[i] == -1) {
			//�ǂݍ��݃G���[
			exit(999);//�����I��
		}
	}

	//�g�p����e�N�X�`���̐ݒ�(���U���gor����ȊO)
	if (GetScene() == SCENE_RESULT)
	{
		CurrentTexture = 1;
	}
	else
	{
		CurrentTexture = 0;
	}

	

	//BGM��炷
	//PlaySound(mainBGM[CurrentBGM], -1);

	return S_OK;
}

void FIELD::UninitGame()
{
	//StopSoundAll();
}

void FIELD::UpdateGame()
{
	// �ݒ肵���X�s�[�h�ɉ����ăX�N���[��(�ЂƂ܂��b���)
	Position.x += Speed;
}

void FIELD::DrawGame()
{	
	//�e�N�X�`���̃Z�b�g
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextureNoField[CurrentTexture]));

	DrawSpriteColorRotate
	(
		Position.x,
		Position.y,
		Size.x,
		Size.y,
		Rotate,
		Color,
		0,
		1.0f,
		1.0f,
		1
	);
}

/*
	�t�B�[���h�̃X�N���[�����x��ݒ肷��֐�
	�����Ffloat speed (�X�N���[�����x)
*/
void FIELD::SetFieldSpeed(float speed)
{
	Speed = speed;
}

