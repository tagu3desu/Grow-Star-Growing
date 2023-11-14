#include	<stdlib.h>
#include	"skill_ui.h"

#include	"sprite.h"
#include	"texture.h"


#include	"player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	SKILL_UI_SIZE_W	(80.0f)	//�l�p�`�̉��̃T�C�Y
#define	SKILL_UI_SIZE_H	(40.0f)	//�l�p�`�̏c�̃T�C�Y

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
SKILL_UI	 g_SkillUI[3];
//�X�L���A�C�R���摜�̃e�N�X�`��
static	char* g_SkillUITextureName[7] = {
	(char*)"data\\texture\\kakuta_�ʏ�e.png",
	(char*)"data\\texture\\kakuta_�O�ҖC�e.png",
	(char*)"data\\texture\\kakuta_�ђʒe.png",
	(char*)"data\\texture\\kakuta_��]�e.png",
	(char*)"data\\texture\\kakuta_�y���e.png",
	(char*)"data\\texture\\kakuta_�����e.png",
	(char*)"data\\texture\\kakuta_����e.png",
};

//=============================================================================
// ����������
//=============================================================================
HRESULT SKILL_UI::InitGame(void)
{
	for (int i = 0; i < SKILL_UI_MAX; i++)
	{
		//�\���̂��ׂď���
		g_SkillUI[i].pos = D3DXVECTOR2(90.0f * i + 60.0f, 480.0f);
		g_SkillUI[i].size.x = SKILL_UI_SIZE_W;
		g_SkillUI[i].size.y = SKILL_UI_SIZE_H;
		g_SkillUI[i].rot = 0.0f;
		g_SkillUI[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_SkillUI[i].texNo = LoadTexture((char*)"data\\texture\\player_skill_back.png");//�e�N�X�`�����[�h;
		g_SkillUI[i].texGrayDownNo = LoadTexture((char*)"data\\texture\\player_skill_graydown.png");//�O���[�_�E���e�N�X�`�����[�h
		g_SkillUI[i].texIconNo = LoadTexture(g_SkillUITextureName[GetPlayer()->SkillType[i]]);
		g_SkillUI[i].use = TRUE;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void SKILL_UI::UninitGame(void)
{


}


//=============================================================================
// �X�V����
//=============================================================================
void SKILL_UI::UpdateGame(void)
{
	//if (GetPlayer()->energy < 100 && GetPlayer()->energy > 0) //�Q�[�W�ő��
	//{
	//	g_SkillUI2.size.y = GetPlayer()->energy * 2; //�G�l���M�[���̃T�C�Y�ɂ���
	//	g_SkillUI2.pos.y = -GetPlayer()->energy / 2 + 315.0f ;
	//}
	//g_SkillUI2.EnergyCount += 1.0f;	//�J�E���g�𑝂₷
	//if (g_SkillUI2.EnergyCount >= 60)	//�J�E���g��60�ɂȂ�����
	//{
	//	g_SkillUI2.pos.y += 1.5f; //�����グ��
	//	g_SkillUI2.EnergyCount = 0.0f;	//�J�E���g��߂�
	//}
}

//=============================================================================
// �`�揈��
//=============================================================================
void SKILL_UI::DrawGame(void)
{
	PLAYER* player = GetPlayer();

	//�\���̂�S�Ē��ׂ�
	for (int i = 0; i < SKILL_UI_MAX; i++)
	{
		//�\���̂��g�p���Ȃ珈��
		if (g_SkillUI[i].use == TRUE)
		{
			//�w�i
			{
				//�e�N�X�`���̃Z�b�g
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SkillUI[i].texNo));

				//�`��
				DrawSpriteColorRotate
				(g_SkillUI[i].pos.x,
					g_SkillUI[i].pos.y,
					(int)g_SkillUI[i].size.x,
					(int)g_SkillUI[i].size.y,
					g_SkillUI[i].rot,
					g_SkillUI[i].color,
					1.0f,
					1.0f,
					1.0f,
					1
				);
			}

			//�O���[�_�E��
			{
				//�e�N�X�`���̃Z�b�g
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SkillUI[i].texGrayDownNo));

				//�`��
				DrawSpriteColorRotate
				(g_SkillUI[i].pos.x,
					(g_SkillUI[i].pos.y - g_SkillUI[i].size.y * 0.75f * ((float)player->SkillUsageCount[i] / (float)player->SkillUsageMax[i]) * 0.5f),
					(int)(g_SkillUI[i].size.x * 0.8125f),
					(int)(g_SkillUI[i].size.y * 0.75f * (1.0f - ((float)player->SkillUsageCount[i] / (float)player->SkillUsageMax[i]))),
					g_SkillUI[i].rot,
					g_SkillUI[i].color,
					1.0f,
					1.0f,
					1.0f,
					1
				);
			}

			//�A�C�R���摜
			{
				//�e�N�X�`���̃Z�b�g
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SkillUI[i].texIconNo));

				//�`��
				DrawSpriteColorRotate
				(g_SkillUI[i].pos.x,
					g_SkillUI[i].pos.y,
					(int)g_SkillUI[i].size.y * 0.75f,
					(int)g_SkillUI[i].size.y * 0.75f,
					g_SkillUI[i].rot,
					g_SkillUI[i].color,
					1.0f,
					1.0f,
					1.0f,
					1
				);
			}
		}
	}
}

//==========================
//�\���̂̐擪�A�h���X��Ԃ�
//==========================
SKILL_UI	*GetSkillUI()
{
	return	&g_SkillUI[0];
}
