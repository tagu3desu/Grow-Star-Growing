/*==============================================================================

   ����w����� [weapon_shop.cpp]
														 Author :��������
														 Date   :2023_01_16
--------------------------------------------------------------------------------

==============================================================================*/
#include "01_Scene.h"
#include "weapon_shop.h"
#include "score.h"
#include "data.h"
#include "texture.h"

#include "00_soundmain.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//����w����ʂ̔w�i�摜�t�@�C���p�X
static	char* g_WeaponShopBGTextureName = (char*)"data\\texture\\weapon_shop_back.png";

//����w���{�^���摜�̃e�N�X�`���t�@�C���p�X
static	char* g_WeaponShopButtonTextureName[WEAPON_MAX] = {
	(char*)"data\\texture\\weapon_shop_01.png",
	(char*)"data\\texture\\weapon_shop_02.png",
	(char*)"data\\texture\\weapon_shop_03.png",
	(char*)"data\\texture\\weapon_shop_04.png",
};

//�w���ς݉摜�t�@�C���p�X
static	char* g_WeaponShopPurchasedTextureName = (char*)"data\\texture\\weapon_shop_purchased.png";

WEAPON_SHOP* g_WeaponShopBG;

WEAPON_SHOP_BUTTON		g_WeaponShopButton[WEAPON_MAX];

WEAPON_SHOP_BUTTON*		g_WeaponShopButtonPurchased;

Game*					g_WeaponShopScore = new SCORE;

int WeaponShopReplica; //�Z���N�g�ԍ����߂̑j�~�p

HRESULT InitWeaponShop()
{
	//����w����ʂ̔w�i
	{
		g_WeaponShopBG = new WEAPON_SHOP;

		g_WeaponShopBG->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
		g_WeaponShopBG->Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
		g_WeaponShopBG->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_WeaponShopBG->Rotate = 0;
		g_WeaponShopBG->WeaponSelect = 0;
		g_WeaponShopBG->HoldCoin = 0;

		g_WeaponShopBG->Texno = LoadTexture(g_WeaponShopBGTextureName);
		if (g_WeaponShopBG->Texno == -1) {
			//�ǂݍ��݃G���[
			exit(999);
		}
	}

	//����w���{�^��
	for (int i = 0; i < WEAPON_MAX; i++)
	{
		int yoko = (i % 2);
		int tate = (i / 2);

		g_WeaponShopButton[i].Position = D3DXVECTOR2(450.0f * yoko + 250.0f, 140.0f * tate + 200.0f);
		g_WeaponShopButton[i].Size = D3DXVECTOR2(768.0f * 0.5f, 256.0f * 0.5f);
		g_WeaponShopButton[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_WeaponShopButton[i].Rotate = 0;

		g_WeaponShopButton[i].Texno = LoadTexture(g_WeaponShopButtonTextureName[i]);
		if (g_WeaponShopButton[i].Texno == -1) {
			//�ǂݍ��݃G���[
			exit(999);
		}

		g_WeaponShopButton[i].Ownership = FALSE;
		g_WeaponShopButton[i].Price = 0;
	}

	//�w���ς݃}�[�N
	{
		g_WeaponShopButtonPurchased = new WEAPON_SHOP_BUTTON;
		g_WeaponShopButtonPurchased->Position = D3DXVECTOR2(250.0f, 200.0f);
		g_WeaponShopButtonPurchased->Size = D3DXVECTOR2(768.0f * 0.5f, 256.0f * 0.5f);
		g_WeaponShopButtonPurchased->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_WeaponShopButtonPurchased->Rotate = 0;

		g_WeaponShopButtonPurchased->Texno = LoadTexture(g_WeaponShopPurchasedTextureName);
		if (g_WeaponShopButtonPurchased->Texno == -1) {
			//�ǂݍ��݃G���[
			exit(999);
		}

		//�ȉ��͎g��Ȃ����O�̂��ߏ�����
		g_WeaponShopButtonPurchased->Ownership = FALSE;
		g_WeaponShopButtonPurchased->Price = 0;
	}

	//�X�R�A�̏�����
	g_WeaponShopScore->InitGame();

	//�v���C���[�����擾(���͑���Ƀe�X�g�p�f�[�^�����Ă���܂�)
	g_WeaponShopBG->HoldCoin = GetData()->Money;
	for (int i = 0; i < WEAPON_MAX; i++)
	{
		g_WeaponShopButton[i].Ownership = GetData()->Ownership[i];
	}
	//����̉��i�ݒ�
	g_WeaponShopButton[0].Price = 1000;		//�ђʒe
	g_WeaponShopButton[1].Price = 2500;		//�y���e
	g_WeaponShopButton[2].Price = 2000;		//�����e
	g_WeaponShopButton[3].Price = 4000;		//����e
	SCORE* score = dynamic_cast<SCORE*>(g_WeaponShopScore);		//�_�E���L���X�g
	score->AddScore(g_WeaponShopBG->HoldCoin);		//�e�X�g�p�̏������f�[�^������
	score->SettingScore(D3DXVECTOR2(790.0f, 32.0f), 21.0f, 6, TRUE);

	return S_OK;
}
void UninitWeaponShop()
{
	if (g_WeaponShopBG)
	{
		delete g_WeaponShopBG;
		g_WeaponShopBG = NULL;
	}

	//�X�R�A�̏I������
	g_WeaponShopScore->UninitGame();
}
void UpdateWeaponShop()
{

	//==============================================================
	//�X�e�[�W�Z���N�g�̏���
	//==============================================================
	{
		if (Keyboard_TriggerKeyDown(KK_RIGHT) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_RIGHT))//�E�{�^��
		{
			WeaponShopReplica = g_WeaponShopBG->WeaponSelect + 1;
			PlayEffect(Tap, 1.0f);
		}
		else if (Keyboard_TriggerKeyDown(KK_DOWN) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_DOWN))//���{�^��
		{
			WeaponShopReplica = g_WeaponShopBG->WeaponSelect + WEAPON_MAX / 2;
			PlayEffect(Tap, 1.0f);
		}
		else if (Keyboard_TriggerKeyDown(KK_LEFT) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_LEFT))//���{�^��
		{
			WeaponShopReplica = g_WeaponShopBG->WeaponSelect - 1;
			PlayEffect(Tap, 1.0f);
		}
		else if (Keyboard_TriggerKeyDown(KK_UP) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_UP))//��{�^��
		{
			WeaponShopReplica = g_WeaponShopBG->WeaponSelect - WEAPON_MAX / 2;
			PlayEffect(Tap, 1.0f);
		}

		if (WeaponShopReplica >= 0 && WeaponShopReplica < WEAPON_MAX)//���������Ȃ��悤��
		{
			g_WeaponShopBG->WeaponSelect = WeaponShopReplica;
		}

		//===========================================================
		//���Z���N�g��ʂ̏����ƃO���[�_�E������
		{
			for (int i = 0; i < WEAPON_MAX; i++)
			{
				g_WeaponShopButton[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//���邭����
			}

			g_WeaponShopButton[g_WeaponShopBG->WeaponSelect].Color = D3DXCOLOR(0.5f, 0.8f, 0.8f, 1.0f);//�O���[�_�E��
		}
	}


	//==============================================================
	//�w������
	//==============================================================
	{
		if (Keyboard_TriggerKeyDown(KK_SPACE) || IsButtonTriggered(0, XINPUT_GAMEPAD_B))
		{
			//�����������������\������΍w��
			if (g_WeaponShopButton[g_WeaponShopBG->WeaponSelect].Ownership == FALSE && g_WeaponShopBG->HoldCoin >= g_WeaponShopButton[g_WeaponShopBG->WeaponSelect].Price)
			{
				//�����������炷
				g_WeaponShopBG->HoldCoin -= g_WeaponShopButton[g_WeaponShopBG->WeaponSelect].Price;
				g_WeaponShopButton[g_WeaponShopBG->WeaponSelect].Ownership = TRUE;
				SCORE* score = dynamic_cast<SCORE*>(g_WeaponShopScore);		//�_�E���L���X�g
				score->AddScore(-g_WeaponShopButton[g_WeaponShopBG->WeaponSelect].Price);		//�e�X�g�p�̏������f�[�^������
				//�ς����Ƃ��̌��ʉ���炷
				PlayEffect(OKvol, 1.0f);
			}
			else
			{
				PlayEffect(Not, 1.0f);
				//�������Ȃ��i�����Ȃ��Ƃ��̌��ʉ������炷�H�j
			}
		}
	}

	//�X�R�A�̍X�V
	g_WeaponShopScore->UpdateGame();

	//�^�C�g���֖߂�
	if (Keyboard_TriggerKeyDown(KK_BACK) == true || IsButtonPressed(0, XINPUT_GAMEPAD_X))		//X�{�^��(BACK�L�[)
	{
		SetData(g_WeaponShopBG->HoldCoin, -1, -1, -1);

		G_DATA* data = GetData();
		for (int i = 0; i < WEAPON_MAX; i++)
		{
			data->Ownership[i] = g_WeaponShopButton[i].Ownership;
		}

		SetScene(SCENE_TITLE);
	}
}
void DrawWeaponShop()
{
	//========================================================================
	//�X�e�[�W�w�i�\��
	//========================================================================
	{
		//�e�N�X�`���̃Z�b�g
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_WeaponShopBG->Texno));

		DrawSpriteColorRotate
		(
			g_WeaponShopBG->Position.x,
			g_WeaponShopBG->Position.y,
			g_WeaponShopBG->Size.x,
			g_WeaponShopBG->Size.y,
			g_WeaponShopBG->Rotate,
			g_WeaponShopBG->Color,
			0,
			1.0f,
			1.0f,
			1
		);
	}

	//==========================================================================
	//�X�e�[�W�Z���N�g�p�{�^��
	//========================================================================
	{

		for (int i = 0; i < WEAPON_MAX; i++)
		{
			//�e�N�X�`���̃Z�b�g
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_WeaponShopButton[i].Texno));

			DrawSpriteColorRotate
			(
				g_WeaponShopButton[i].Position.x,
				g_WeaponShopButton[i].Position.y,
				g_WeaponShopButton[i].Size.x,
				g_WeaponShopButton[i].Size.y,
				g_WeaponShopButton[i].Rotate,
				g_WeaponShopButton[i].Color,
				0,
				1.0f,
				1.0f,
				1
			);
		}

	}

	//==========================================================================
	//�w���ς݃}�[�N
	//========================================================================
	{
		for (int i = 0; i < WEAPON_MAX; i++)
		{
			if (g_WeaponShopButton[i].Ownership == TRUE)
			{
				//���W���擾����
				g_WeaponShopButtonPurchased->Position = g_WeaponShopButton[i].Position;

				//�e�N�X�`���̃Z�b�g
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_WeaponShopButtonPurchased->Texno));

				DrawSpriteColorRotate
				(
					g_WeaponShopButtonPurchased->Position.x,
					g_WeaponShopButtonPurchased->Position.y,
					g_WeaponShopButtonPurchased->Size.x,
					g_WeaponShopButtonPurchased->Size.y,
					g_WeaponShopButtonPurchased->Rotate,
					g_WeaponShopButtonPurchased->Color,
					0,
					1.0f,
					1.0f,
					1
				);
			}
		}
	}

	g_WeaponShopScore->DrawGame();
}
