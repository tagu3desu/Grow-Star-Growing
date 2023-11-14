
#include "tutorial.h"
#include "texture.h"
#include "sprite.h"


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
static TUTORIAL  g_tutorial;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

HRESULT TUTORIAL::InitGame()
{
	//�e�N�X�`�����[�h
	g_tutorial.texNo = LoadTexture((char*)"data\\texture\\tutorial_01.png");


	g_tutorial.Use = false;
	g_tutorial.Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	g_tutorial.Size = D3DXVECTOR2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	g_tutorial.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_tutorial.Rotate = 0;



	return S_OK;
}

void TUTORIAL :: UninitGame()
{
	
}

void TUTORIAL::UpdateGame()
{
	if (g_tutorial.Use == true)//�g�p�t���O
	{
		g_tutorial.Position.x -= 1.0f;
	}

	if (g_tutorial.Position.x <= -SCREEN_WIDTH / 2) //�����Ȃ��Ȃ�^�C�~���O
	{
		g_tutorial.Use = false;
	}

}

void TUTORIAL::DrawGame()
{



	if (g_tutorial.Use == true)//�g�p�t���O
	{


		//�e�N�X�`���̃Z�b�g
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_tutorial.texNo));

		DrawSpriteColorRotate
		(
			g_tutorial.Position.x,
			g_tutorial.Position.y,
			g_tutorial.Size.x,
			g_tutorial.Size.y,
			g_tutorial.Rotate,
			g_tutorial.Color,
			0,
			1.0f,
			1.0f,
			1
		);

	}

}

//=====================================================
//�`���[�g���A���e�N�X�`���Z�b�g
//=====================================================

void Set_BG(int TutorialTexNo)
{

	switch (TutorialTexNo)
	{
	case 1:
		//	BG�e�N�X�`���̃��[�h
		g_tutorial.texNo = LoadTexture((char*)"data\\texture\\tutorial_01.png");
		if (g_tutorial.texNo == -1) {
			//�ǂݍ��݃G���[
			exit(999);//�����I��
		}

		break;
	case 2:
		//	BG�e�N�X�`���̃��[�h
		g_tutorial.texNo = LoadTexture((char*)"data\\texture\\tutorial_02.png");
		if (g_tutorial.texNo == -1) {
			//�ǂݍ��݃G���[
			exit(999);//�����I��
		}
		break;

	case 3:
		//	BG�e�N�X�`���̃��[�h
		g_tutorial.texNo = LoadTexture((char*)"data\\texture\\tutorial_03.png");
		if (g_tutorial.texNo == -1) {
			//�ǂݍ��݃G���[
			exit(999);//�����I��
		}
		break;

	default://��v���鐔�l���Ȃ��Ƃ��̏���
		break;
	}

	//����͏�����
	g_tutorial.Use = true;
	g_tutorial.Position = D3DXVECTOR3(SCREEN_WIDTH , SCREEN_HEIGHT  / 2, 0);
	g_tutorial.Size = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	g_tutorial.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_tutorial.Rotate = 0;



	return;
}