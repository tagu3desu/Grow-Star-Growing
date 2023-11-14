 #include "01.5_StageSelect.h"
#include "texture.h"

#include "00_soundmain.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//static	ID3D11ShaderResourceView* g_StageSelectTexture = NULL;
//
//static	ID3D11ShaderResourceView* g_SelectButtonTexture1 = NULL;
//static	ID3D11ShaderResourceView* g_SelectButtonTexture2 = NULL;
//static	ID3D11ShaderResourceView* g_SelectButtonTexture3 = NULL;
//static	ID3D11ShaderResourceView* g_SelectButtonTexture4 = NULL;

#define STEGE_MAX (6)




static	char* g_StageSelectTextureName =   (char*)"data\\texture\\haikei01.png";//�e�N�X�`���t�@�C���p�X
static	char* g_SelectButtonTextureName = (char*)"data\\texture\\button1.png";//�e�N�X�`���t�@�C���p�X
static	char* g_SelectButtonTextureName2 = (char*)"data\\texture\\button2.png";//�e�N�X�`���t�@�C���p�X
static	char* g_SelectButtonTextureName3 = (char*)"data\\texture\\button3.png";//�e�N�X�`���t�@�C���p�X
static	char* g_SelectButtonTextureName4 = (char*)"data\\texture\\button4.png";//�e�N�X�`���t�@�C���p�X
static	char* g_SelectButtonTextureName5 = (char*)"data\\texture\\buttonShop.png";//�e�N�X�`���t�@�C���p�X
static	char* g_SelectButtonTextureName6 = (char*)"data\\texture\\buttonSelect.png";//�e�N�X�`���t�@�C���p�X

STAGESELECTBG* SS;

SELECTBUTTON  SB[STEGE_MAX];


int	TextureNoSS = 0;



int stageslect_Replica; //�Z���N�g�ԍ����߂̑j�~�p

HRESULT InitStageSelect()
{
	PlayBGM(Select, 1.0f);

	{
		//�Z���N�g��ʂ̔w�i
		SS = new STAGESELECTBG;
		
		SS->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
		SS->Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
		SS->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		SS->Rotate = 0;
		SS->Stageselect = 1;
		SS->SelectCount = 0;
		SS->SelectFlag = false;

		TextureNoSS= LoadTexture(g_StageSelectTextureName);
		if (TextureNoSS == -1) {
			//�ǂݍ��݃G���[
			exit(999);
		}
	}
	
	
	for (int i = 0; i < STEGE_MAX; i++)
	{
		int yoko = 1 + (i % 3);
		int tate = 1 + (i / 3);

		SB[i].Position = D3DXVECTOR2(240 * yoko, 180 * tate);
		SB[i].Size = D3DXVECTOR2(200, 100);
		SB[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		SB[i].Rotate = 0;

		SB[i].TextureNoSB = LoadTexture(g_SelectButtonTextureName);

	}
	SB[0].TextureNoSB = LoadTexture(g_SelectButtonTextureName);
	SB[1].TextureNoSB = LoadTexture(g_SelectButtonTextureName2);
	SB[2].TextureNoSB = LoadTexture(g_SelectButtonTextureName3);
	SB[3].TextureNoSB = LoadTexture(g_SelectButtonTextureName4);
	SB[4].TextureNoSB = LoadTexture(g_SelectButtonTextureName5);
	SB[5].TextureNoSB = LoadTexture(g_SelectButtonTextureName6);


	
	return S_OK;
}
void UninitStageSelect()
{

	StopS();
	if (SS)
	{
		delete SS;
		SS = NULL;
	}
	
	
	
	
}
void UpdateStageSelect()
{
	
	//==============================================================
	//�X�e�[�W�Z���N�g�̏���
	{
		if ((Keyboard_TriggerKeyDown(KK_RIGHT) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_RIGHT)) && SS->SelectFlag == false)//�E�{�^��
		{
			stageslect_Replica = SS->Stageselect + 1;
			SS->SelectFlag = true;
			PlayEffect(Tap, 1.0f);

		}
		else if ((Keyboard_TriggerKeyDown(KK_DOWN) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_DOWN)) && SS->SelectFlag == false)//���{�^��
		{
			stageslect_Replica = SS->Stageselect + STEGE_MAX / 2;
				SS->SelectFlag = true;
			PlayEffect(Tap, 1.0f);
		}
		else if ((Keyboard_TriggerKeyDown(KK_LEFT) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_LEFT)) && SS->SelectFlag == false)//���{�^��
		{
			stageslect_Replica = SS->Stageselect - 1;
				SS->SelectFlag = true;
			PlayEffect(Tap, 1.0f);
		}
		else if ((Keyboard_TriggerKeyDown(KK_UP) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_UP)) && SS->SelectFlag == false)//��{�^��
		{
			stageslect_Replica = SS->Stageselect - STEGE_MAX / 2;
				SS->SelectFlag = true;
			PlayEffect(Tap, 1.0f);
		}

		if (stageslect_Replica >= 0 && stageslect_Replica < STEGE_MAX)//���������Ȃ��悤��
		{
			SS->Stageselect = stageslect_Replica;
		}

		//===============================
	//�Z���N�g�̎��̑ҋ@����
		if (SS->SelectFlag == true)
		{
			SS->SelectCount++;
		}

		if (SS->SelectCount >= 10)
		{
			SS->SelectCount = 0;
			SS->SelectFlag = false;
		}


		//===========================================================
		//���Z���N�g��ʂ̏����ƃO���[�_�E������
		{
			for (int i = 0; i < STEGE_MAX; i++)
			{
				SB[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//���邭����
			}

			SB[SS->Stageselect].Color = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);//�O���[�_�E��

			
		}
	}


	//=============================================================
	//�X�e�[�W�ڍs����
	{
		if (Keyboard_TriggerKeyDown(KK_SPACE) || IsButtonTriggered(0, XINPUT_GAMEPAD_B))
		{
			switch (SS->Stageselect)
			{
			case 0:
				SetScene(SCENE_GAME);
				break;
			case 1:
				//�X�e�[�W�Q
				SetScene(SCENE_STAGE02);
				break;
			case 2:
				//�X�e�[�W�R
				SetScene(SCENE_STAGE03);
				break;
			case 3:
				//�X�e�[�W4
				SetScene(SCENE_STAGE03);

				break;
			case 4:
				//����V���b�v
				SetScene(SCENE_SHOP);
				break;
			case 5:
				//�X�L���Z�b�g���
				SetScene(SCENE_SKILL_SET);
			default:
				break;
			}
		}
	}




	
}
void DrawStageSelect()
{
	//========================================================================
	//�X�e�[�W�w�i�\��
	{
		//�e�N�X�`���̃Z�b�g
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextureNoSS));

		DrawSpriteColorRotate
		(
			SS->Position.x,
			SS->Position.y,
			SS->Size.x,
			SS->Size.y,
			SS->Rotate,
			SS->Color,
			0,
			1.0f,
			1.0f,
			1
		);
	}

	//==========================================================================
	//�X�e�[�W�Z���N�g�p�{�^��
	{

		for (int i = 0; i < STEGE_MAX; i++)
		{
			//�e�N�X�`���̃Z�b�g
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(SB[i].TextureNoSB));

			DrawSpriteColorRotate
			(
				SB[i].Position.x,
				SB[i].Position.y,
				SB[i].Size.x,
				SB[i].Size.y,
				SB[i].Rotate,
				SB[i].Color,
				0,
				1.0f,
				1.0f,
				1
			);
		}
		
	}

}
