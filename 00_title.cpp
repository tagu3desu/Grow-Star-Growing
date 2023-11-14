#include "00_title.h"
#include "texture.h"
#include "keyboard.h"
#include "mouse.h"
#include "00_soundmain.h"


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//static	ID3D11ShaderResourceView* g_TitleTexture = NULL;

static	char* g_TitleTextureName = (char*)"data\\texture\\�Q�[�����^�C�g�����.png";//�e�N�X�`���t�@�C���p�X

TITLE* TI;

int TextureNoTI = 0;

bool key = false;


HRESULT Inittitle()
{
	
	initSound();

	PlayBGM(Title, 1.0f);

	TI = new TITLE;		//BG�\���̂̃C���X�^���X�쐬

	TI->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	TI->Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	TI->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	TI->Rotate = 0;

	//	BG�e�N�X�`���̃��[�h
	TextureNoTI = LoadTexture(g_TitleTextureName);
	if (TextureNoTI == -1) {
		//�ǂݍ��݃G���[
		exit(999);//�����I��
	}

	return S_OK;
}

void Uninittitle()
{
	if (TI)
	{
		delete	TI;
		TI = NULL;
	}
}

void Updatetitle()
{
	if (Keyboard_TriggerKeyDown(KK_SPACE) == true || IsButtonPressed(0,XINPUT_GAMEPAD_B))
	{
		SetScene(SCENE_SELECT);
	}

}

void Drawtitle()
{
	//�e�N�X�`���̃Z�b�g
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextureNoTI));



	DrawSpriteColorRotate
	(
		TI->Position.x,
		TI->Position.y,
		TI->Size.x,
		TI->Size.y,
		TI->Rotate,
		TI->Color,
		0,
		1.0f,
		1.0f,
		1
	);
}
