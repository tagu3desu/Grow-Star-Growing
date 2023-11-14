/*==============================================================================

   �X�L���Z�b�g��� [weapon_select.cpp]
														 Author :��������
														 Date   :2023_01_21
--------------------------------------------------------------------------------

==============================================================================*/
#include	"weapon_select.h"
#include	"data.h"
#include	"player.h"
#include	"texture.h"

#include "00_soundmain.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//�X�L���Z�b�g��ʂ̔w�i�摜�t�@�C���p�X
static	char* g_WeaponSelectBGTextureName = (char*)"data\\texture\\weapon_select_back.png";

static	char* g_SelectSkillButtonTextureName[WEAPON_HOLD_MAX] = {
	(char*)"data\\texture\\selected_bullet_back_01.png",
	(char*)"data\\texture\\selected_bullet_back_02.png",
	(char*)"data\\texture\\selected_bullet_back_03.png",
	(char*)"data\\texture\\selected_bullet_back_04.png",
	(char*)"data\\texture\\selected_bullet_back_05.png",
	(char*)"data\\texture\\selected_bullet_back_06.png",
};

static	char* g_SelectWeaponButtonTextureName[WEAPON_HOLD_MAX * 2 + 1] = {
	(char*)"data\\texture\\select_bullet_back_01.png",							//�{�^���w�i�O�ҖC�e
	(char*)"data\\texture\\select_bullet_back_02.png",							//�{�^���w�i�ђʒe
	(char*)"data\\texture\\select_bullet_back_03.png",							//�{�^���w�i��]�e
	(char*)"data\\texture\\select_bullet_back_04.png",							//�{�^���w�i�y���e
	(char*)"data\\texture\\select_bullet_back_05.png",							//�{�^���w�i�����e
	(char*)"data\\texture\\select_bullet_back_06.png",							//�{�^���w�i����e
	(char*)"data\\texture\\kakuta_�O�ҖC�e.png",
	(char*)"data\\texture\\kakuta_�ђʒe.png",
	(char*)"data\\texture\\kakuta_��]�e.png",
	(char*)"data\\texture\\kakuta_�y���e.png",
	(char*)"data\\texture\\kakuta_�����e.png",
	(char*)"data\\texture\\kakuta_����e.png",
	(char*)"data\\texture\\selected_bullet_back_none.png",					//��������Ԃ̃{�^���w�i
};

WEAPON_SELECT*	 g_WeaponSelect;

SELECT_SKILL_BUTTON		g_SelectSkill[2];

SELECT_WEAPON_BUTTON	g_SelectWeapon[WEAPON_HOLD_MAX];


HRESULT InitWeaponSelect()
{
	//�X�L���Z�b�g���
	{
		g_WeaponSelect = new WEAPON_SELECT;

		g_WeaponSelect->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
		g_WeaponSelect->Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
		g_WeaponSelect->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_WeaponSelect->Rotate = 0;

		g_WeaponSelect->Texno = LoadTexture(g_WeaponSelectBGTextureName);
		if (g_WeaponSelect->Texno == -1) {
			//�ǂݍ��݃G���[
			exit(999);
		}

		g_WeaponSelect->SelectSkill = 0;
		g_WeaponSelect->SelectWeapon = -1;
	}

	//�X�L���I���{�^��
	for (int i = 0; i < 2; i++)
	{
		g_SelectSkill[i].Position = D3DXVECTOR2(0.0f, 0.0f);
		g_SelectSkill[i].Size = D3DXVECTOR2(384.0f * 0.5f, 320.0f * 0.5f);
		g_SelectSkill[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_SelectSkill[i].Rotate = 0;

		for (int j = 0; j < WEAPON_HOLD_MAX; j++)
		{
			g_SelectSkill[i].Texno[j] = LoadTexture(g_SelectSkillButtonTextureName[j]);
			if (g_SelectSkill[i].Texno[j] == -1) {
				//�ǂݍ��݃G���[
				exit(999);
			}
		}

		g_SelectSkill[i].SkillType = GetData()->SkillType[i + 1] - 1;	//0�Ԗڂ͒ʏ�e�Ȃ̂�1�Ԗڂ���擾
	}

	g_SelectSkill[0].Position = D3DXVECTOR2(SCREEN_WIDTH * 0.5f, 100.0f);
	g_SelectSkill[1].Position = D3DXVECTOR2(770.0f, 270.0f);

	//����I���{�^��
	for (int i = 0; i < WEAPON_HOLD_MAX; i++)
	{
		g_SelectWeapon[i].Position = D3DXVECTOR2(i * 128.0f + ((SCREEN_WIDTH - WEAPON_HOLD_MAX * 128.0f) * 0.5f + 64.0f), 450.0f);
		g_SelectWeapon[i].Size = D3DXVECTOR2(128.0f, 128.0f);
		g_SelectWeapon[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_SelectWeapon[i].Rotate = 0;

		//�������̔w�i
		g_SelectWeapon[i].Texno = LoadTexture(g_SelectWeaponButtonTextureName[i]);
		if (g_SelectWeapon[i].Texno == -1) {
			//�ǂݍ��݃G���[
			exit(999);
		}

		//���������̔w�i
		g_SelectWeapon[i].NoneTexno = LoadTexture(g_SelectWeaponButtonTextureName[WEAPON_HOLD_MAX * 2]);
		if (g_SelectWeapon[i].NoneTexno == -1) {
			//�ǂݍ��݃G���[
			exit(999);
		}

		//����A�C�R��
		g_SelectWeapon[i].IconTexno = LoadTexture(g_SelectWeaponButtonTextureName[i + WEAPON_HOLD_MAX]);
		if (g_SelectWeapon[i].IconTexno == -1) {
			//�ǂݍ��݃G���[
			exit(999);
		}

		if (i == 0 || i == 2)		//�O�ҖC�e�Ɖ�]�e�͏������玝���Ă���
		{
			g_SelectWeapon[i].Ownership = TRUE;
		}
		else if (i == 1)			//�ђʒe
		{
			g_SelectWeapon[i].Ownership = GetData()->Ownership[0];
		}
		else
		{
			g_SelectWeapon[i].Ownership = GetData()->Ownership[i - 2];
		}
	}

	return S_OK;
}

void UninitWeaponSelect()
{
	if (g_WeaponSelect)
	{
		delete g_WeaponSelect;
		g_WeaponSelect = NULL;
	}
}

void UpdateWeaponSelect()
{
	if (Keyboard_TriggerKeyDown(KK_RIGHT) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_RIGHT))//�E�{�^��
	{
		PlayEffect(Tap, 1.0f);

		if (g_WeaponSelect->SelectWeapon < 0)
		{
			//�X�L���X���b�g�̃J�[�\���ړ�
			g_WeaponSelect->SelectSkill++;
			if (g_WeaponSelect->SelectSkill > 1)
			{
				g_WeaponSelect->SelectSkill = 0;
			}
		}
		else
		{
			//����I���̃J�[�\���ړ�
			g_WeaponSelect->SelectWeapon++;
			//�ړ��悪���������̏ꍇ�̓X�L�b�v���Ď���
			while (g_SelectWeapon[g_WeaponSelect->SelectWeapon].Ownership == FALSE)
			{
				g_WeaponSelect->SelectWeapon++;
				if (g_WeaponSelect->SelectWeapon >= WEAPON_HOLD_MAX)
				{
					g_WeaponSelect->SelectWeapon = 0;
				}
			}
			if (g_WeaponSelect->SelectWeapon >= WEAPON_HOLD_MAX)
			{
				g_WeaponSelect->SelectWeapon = 0;
			}
		}

	}
	else if (Keyboard_TriggerKeyDown(KK_LEFT) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_LEFT))//���{�^��
	{
		PlayEffect(Tap, 1.0f);

		if (g_WeaponSelect->SelectWeapon < 0)
		{
			//�X�L���X���b�g�̃J�[�\���ړ�
			g_WeaponSelect->SelectSkill--;
			if (g_WeaponSelect->SelectSkill < 0)
			{
				g_WeaponSelect->SelectSkill = 1;
			}
		}
		else
		{
			//����I���̃J�[�\���ړ�
			g_WeaponSelect->SelectWeapon--;
			//�ړ��悪���������̏ꍇ�̓X�L�b�v���Ď���
			while (g_SelectWeapon[g_WeaponSelect->SelectWeapon].Ownership == FALSE)
			{
				g_WeaponSelect->SelectWeapon--;
				if (g_WeaponSelect->SelectWeapon < 0)
				{
					g_WeaponSelect->SelectWeapon = WEAPON_HOLD_MAX - 1;
				}
			}
			if (g_WeaponSelect->SelectWeapon < 0)
			{
				g_WeaponSelect->SelectWeapon = WEAPON_HOLD_MAX - 1;
			}
		}

	}
	else if (Keyboard_TriggerKeyDown(KK_SPACE) || IsButtonTriggered(0, XINPUT_GAMEPAD_B))	//B�{�^��
	{
		PlayEffect(OKvol, 1.0f);

		if (g_WeaponSelect->SelectWeapon < 0)	//�X�L���Z�b�g�g�̑I����Ԃ̏ꍇ�A����I����ԂɈڍs����
		{
			g_WeaponSelect->SelectWeapon = 0;
		}
		else
		{
			//������X�L���Ƃ��ăZ�b�g
			g_SelectSkill[g_WeaponSelect->SelectSkill].SkillType = g_WeaponSelect->SelectWeapon;		//0�Ԗڂ͒ʏ�e�Ȃ̂Ńv���X1����
			g_WeaponSelect->SelectWeapon = -1;
		}
	}

	//===========================================================
	//���Z���N�g��ʂ̏����ƃO���[�_�E������(�X�L���Z�b�g�{�^��)
	//===========================================================
	{
		for (int i = 0; i < 2; i++)
		{
			g_SelectSkill[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//���邭����
		}
		g_SelectSkill[g_WeaponSelect->SelectSkill].Color = D3DXCOLOR(0.5f, 0.8f, 0.8f, 1.0f);//�O���[�_�E��
	}

	//===========================================================
	//���Z���N�g��ʂ̏����ƃO���[�_�E������(����I���{�^��)
	//===========================================================
	{
		for (int i = 0; i < WEAPON_HOLD_MAX; i++)
		{
			g_SelectWeapon[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//���邭����
		}
		if (g_WeaponSelect->SelectWeapon >= 0)
		{
			g_SelectWeapon[g_WeaponSelect->SelectWeapon].Color = D3DXCOLOR(0.5f, 0.8f, 0.8f, 1.0f);//�O���[�_�E��
		}
	}

	//�^�C�g���֖߂�
	if (Keyboard_TriggerKeyDown(KK_BACK) == true || IsButtonPressed(0, XINPUT_GAMEPAD_X))		//X�{�^��(BACK�L�[)
	{
		//�X�L���̃Z�b�g�󋵂�data.cpp�ɕۑ�(skill[0]�͒ʏ�e0�ŌŒ�)
		int skill[3] = {0, g_SelectSkill[0].SkillType + 1, g_SelectSkill[1].SkillType + 1};
		SetSkillType(skill);

		SetScene(SCENE_TITLE);
	}
}

void DrawWeaponSelect()
{
	//========================================================================
	//�X�e�[�W�w�i�\��
	//========================================================================
	{
		//�e�N�X�`���̃Z�b�g
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_WeaponSelect->Texno));

		DrawSpriteColorRotate
		(
			g_WeaponSelect->Position.x,
			g_WeaponSelect->Position.y,
			g_WeaponSelect->Size.x,
			g_WeaponSelect->Size.y,
			g_WeaponSelect->Rotate,
			g_WeaponSelect->Color,
			0,
			1.0f,
			1.0f,
			1
		);
	}

	//==========================================================================
	//�X�L���Z�b�g�{�^��
	//==========================================================================
	{

		for (int i = 0; i < 2; i++)
		{
			//�e�N�X�`���̃Z�b�g(�{�^���w�i)
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SelectSkill[i].Texno[g_SelectSkill[i].SkillType]));

			DrawSpriteColorRotate
			(
				g_SelectSkill[i].Position.x,
				g_SelectSkill[i].Position.y,
				g_SelectSkill[i].Size.x,
				g_SelectSkill[i].Size.y,
				g_SelectSkill[i].Rotate,
				g_SelectSkill[i].Color,
				0,
				1.0f,
				1.0f,
				1
			);

			//�e�N�X�`���̃Z�b�g(����I���{�^���̃A�C�R���e�N�X�`���𗬗p)
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SelectWeapon[g_SelectSkill[i].SkillType].IconTexno));

			DrawSpriteColorRotate
			(
				g_SelectSkill[i].Position.x,
				g_SelectSkill[i].Position.y + 16.0f,
				g_SelectSkill[i].Size.x * 0.75f,
				g_SelectSkill[i].Size.y * 0.75f,
				g_SelectSkill[i].Rotate,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	//�O���[�_�E�����Ȃ�
				0,
				1.0f,
				1.0f,
				1
			);
		}

	}

	//==========================================================================
	//����I���{�^��
	//==========================================================================
	{
		for (int i = 0; i < WEAPON_HOLD_MAX; i++)
		{
			//�e�N�X�`���̃Z�b�g
			if (g_SelectWeapon[i].Ownership == TRUE)
			{
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SelectWeapon[i].Texno));
			}
			else
			{
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SelectWeapon[i].NoneTexno));
			}

			DrawSpriteColorRotate
			(
				g_SelectWeapon[i].Position.x,
				g_SelectWeapon[i].Position.y,
				g_SelectWeapon[i].Size.x,
				g_SelectWeapon[i].Size.y,
				g_SelectWeapon[i].Rotate,
				g_SelectWeapon[i].Color,
				0,
				1.0f,
				1.0f,
				1
			);

			//�e�N�X�`���̃Z�b�g(����A�C�R��)
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SelectWeapon[i].IconTexno));

			if (g_SelectWeapon[i].Ownership == TRUE)	//�������Ă��镐��̂݃A�C�R����\��
			{
				DrawSpriteColorRotate
				(
					g_SelectWeapon[i].Position.x,
					g_SelectWeapon[i].Position.y + 10.0f,
					g_SelectWeapon[i].Size.x * 0.75f,
					g_SelectWeapon[i].Size.y * 0.75f,
					g_SelectWeapon[i].Rotate,
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	//�O���[�_�E�����Ȃ�
					0,
					1.0f,
					1.0f,
					1
				);
			}
		}
	}
}
