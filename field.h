#pragma once
#include "01_Scene.h"

#include"polygon.h"
#include"renderer.h"
#include "texture.h"
//#include"main.h"
/*==============================================================================

   �t�B�[���h���� [field.h]		�v���g�^�C�v��
														 Author :	��������
														 Date   :	2022_10_27
--------------------------------------------------------------------------------

==============================================================================*/

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class FIELD : public Game
{
public:
	FIELD();					//�R���X�g���N�^
	~FIELD();					//�f�X�g���N�^
	void UninitGame();
	void UpdateGame();
	void DrawGame();
	HRESULT InitGame();
	void SetFieldSpeed(float speed);		//�t�B�[���h�̃X�N���[�����x��ݒ肷��֐�	�����Ffloat speed (�X�N���[�����x)
private:
	/*	�萔	*/
	//�e�N�X�`��
	static const int MAX_FIELD_TEXTURE = 2;		//�t�B�[���h�w�i�e�N�X�`���̍ő吔
	//BGM
	static const int MAX_FIELD_BGM = 1;			//�t�B�[���hBGM�̍ő吔

	/*	�ϐ�	*/
	D3DXVECTOR3		Position;	//�\�����W
	D3DXVECTOR2		Size;		//�T�C�Y
	D3DXCOLOR		Color;		//�F
	float			Rotate;		//�p�x
	float			Speed;		//�X�N���[�����x(��{�I�ɐ��l�̓}�C�i�X�`0)
	//�e�N�X�`��
	char* g_FieldTextureName[MAX_FIELD_TEXTURE];	//�e�N�X�`���t�@�C���p�X
	int				TextureNoField[MAX_FIELD_TEXTURE];		//�e�N�X�`���C���f�b�N�X
	int				CurrentTexture;							//�g�p����e�N�X�`���ԍ�
	//BGM
	char* g_FieldBGMName[MAX_FIELD_BGM];			//BGM�t�@�C���p�X
	int				mainBGM[MAX_FIELD_BGM];					//BGM�C���f�b�N�X
	int				CurrentBGM;								//�g�p����BGM
};
