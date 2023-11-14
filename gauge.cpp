#include	<stdlib.h>
#include	"gauge.h"

#include	"sprite.h"
#include	"texture.h"

#include	"player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	GAUGE_SIZE_W	(40.0f)	//�l�p�`�̉��̃T�C�Y
#define	GAUGE_SIZE_H	(250.0f)	//�l�p�`�̏c�̃T�C�Y

#define	GAUGE2_SIZE_W	(40.0f)	//�l�p�`�̉��̃T�C�Y
#define GAUGE2_SIZE_H   (200.0f)//���˂��[

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
GAUGE	 g_gauge;
GAUGE	 g_gauge2;

//=============================================================================
// ����������
//=============================================================================
HRESULT GAUGE::InitGame(void)
{
	

	//�\���̂��ׂď���
		g_gauge.pos = D3DXVECTOR2(20.0f, 200.0f);
		g_gauge.size.x = GAUGE_SIZE_W;
		g_gauge.size.y = GAUGE_SIZE_H;
		g_gauge.rot = 0.0f;
		g_gauge.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_gauge.texNo = LoadTexture((char*)"data\\texture\\STARUI.png");//�e�N�X�`�����[�h;
		g_gauge.use = TRUE;

		//�\���̂��ׂď���
		g_gauge2.pos = D3DXVECTOR2(20.0f, 270.0f);
		g_gauge2.size.x = GAUGE2_SIZE_W;
		g_gauge2.size.y = GetPlayer()->energy;
		g_gauge2.rot = 0.0f;
		g_gauge2.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_gauge2.texNo = LoadTexture((char*)"data\\texture\\STARINUI.png");//�e�N�X�`�����[�h;
		g_gauge2.use = TRUE;
	

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void GAUGE::UninitGame(void)
{


}


//=============================================================================
// �X�V����
//=============================================================================
void GAUGE::UpdateGame(void)
{
	if (GetPlayer()->energy < 100 && GetPlayer()->energy > -1) //�Q�[�W�ő��
	{
		g_gauge2.size.y = GetPlayer()->energy ; //�G�l���M�[���̃T�C�Y�ɂ���
		g_gauge2.pos.y = -GetPlayer()->energy / 2 + 325.0f;
	}
	//g_gauge2.EnergyCount += 1.0f;	//�J�E���g�𑝂₷
	//if (g_gauge2.EnergyCount >= 60)	//�J�E���g��60�ɂȂ�����
	//{
	//	g_gauge2.pos.y += 1.5f; //�����グ��
	//	g_gauge2.EnergyCount = 0.0f;	//�J�E���g��߂�
	//}
}

//=============================================================================
// �`�揈��
//=============================================================================
void GAUGE::DrawGame(void)
{
	//�\���̂�S�Ē��ׂ�
	for (int i = 0; i < GAUGE_MAX; i++)
	{
		//�\���̂��g�p���Ȃ珈��
		if (g_gauge.use == true)
		{
			//�e�N�X�`���̃Z�b�g
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_gauge.texNo));

			//�`��
			DrawSpriteColorRotate
			(g_gauge.pos.x,
				g_gauge.pos.y,
				g_gauge.size.x,
				g_gauge.size.y,
				g_gauge.rot,
				g_gauge.color,
				1.0f,
				1.0f,
				1.0f,
				1
			);
		}
	}

	//�\���̂�S�Ē��ׂ�
	for (int i = 0; i < GAUGE2_MAX; i++)
	{
		//�\���̂��g�p���Ȃ珈��
		if (g_gauge2.use == true)
		{
			//�e�N�X�`���̃Z�b�g
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_gauge2.texNo));

			//�`��
			DrawSpriteColorRotate
			(g_gauge2.pos.x,
				g_gauge2.pos.y,
				g_gauge2.size.x,
				g_gauge2.size.y,
				g_gauge2.rot,
				g_gauge2.color,
				1.0f,
				1.0f,
				1.0f,
				1
			);
		}
	}
}

//==========================
//�\���̂̐擪�A�h���X��Ԃ�
//==========================
GAUGE* GetGauge()
{
	return	&g_gauge;
}

//==========================
//�\���̂̐擪�A�h���X��Ԃ�
//==========================
GAUGE* GetGauge2()
{
	return	&g_gauge2;
}