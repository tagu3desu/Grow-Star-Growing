
#include "kirakira.h"
#include "enemy.h"

#include "player.h"
#include "collision.h"
#include "texture.h"



static KIRAKIRA g_Kirakira[KIRAKIRA_MAX];

//=====================================================
//�e�N�X�`���̃��[�h



//======================
//������
//======================
HRESULT KIRAKIRA::InitGame()
{

	//�L���L���̃e�N�X�`��
	

	for (int i = 0; i < KIRAKIRA_MAX; i++)
	{
		g_Kirakira[i].Texno = LoadTexture((char*)"data\\texture\\kirakira.png");


		//�\���̂̏�����
		AgeinInitKirakira(i);

	}


	return	S_OK;	//����I��

}

//======================
//�I������
//======================
void	KIRAKIRA::UninitGame()
{
}

//======================
//�X�V����
//======================
void	KIRAKIRA::UpdateGame()
{
	//��߂̊m���ŃL���L���͐�������

	if (rand() % 100 == 1) {//1f�@�Ɂ@1���̊m���Ő���

		for (int i = 0; i < KIRAKIRA_MAX; i++) //���ׂĂ̒�����
		{
			if (g_Kirakira[i].Use == false)	//���g�p�̍\���̂�������
			{
				AgeinInitKirakira(i);

				g_Kirakira[i].Use = true;

				break;
			
			}
			
		}

	
	}


	//==========================================
	//��ʊO����

	for (int i = 0; i < KIRAKIRA_MAX; i++) //���ׂĂ̒�����
	{
		player_get_kirakira(i);

		if (g_Kirakira[i].Use == true)//�g�p����
		{
			if (g_Kirakira[i].Pos.x < SCREEN_LIMIT_LEFT)//���[�Ȃ�
			{
				g_Kirakira[i].Use = false;//�Ȃ���
			}

			g_Kirakira[i].Pos.x -= 1;//�Ⴄ�Ȃ獶����

		}
	}



	
}

//======================
//�`�揈��
//======================
void	KIRAKIRA::DrawGame()
{
	for (int i = 0; i < KIRAKIRA_MAX; i++)
	{





		//�L���L���������[�Ȃ�\������
		if (g_Kirakira[i].Use == true)
		{

				//�e�N�X�`���̃Z�b�g
				GetDeviceContext()->PSSetShaderResources(0, 1,
					GetTexture(g_Kirakira[i].Texno));


				DrawSpriteColorRotate
				(
					g_Kirakira[i].Pos.x,
					g_Kirakira[i].Pos.y,
					g_Kirakira[i].Size.x,
					g_Kirakira[i].Size.y,
					g_Kirakira[i].Rot,
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),//�Ƃ肠�����̐F
					0,		//�p�^�[���ԍ�
					1.0f,	//�p�^�[���̉��T�C�Y
					1.0f,	//�p�^�[���̏c�T�C�Y
					1		//�p�^�[�����̐�
				);
				//SetBlendState(BLEND_MODE_ALPHABLEND);

			
		}
		
	}
}

//==============================
//�\���̂̐擪�̃|�C���^��Ԃ�
//==============================
KIRAKIRA* GetKirakira()
{

	return	&g_Kirakira[0];
}



//=================================
//�L���L��������
//=================================
void AgeinInitKirakira(int num)
{
	g_Kirakira[num].Pos.x = SCREEN_LIMIT_RIGHT ;
	g_Kirakira[num].Pos.y = rand() % (SCREEN_LIMIT_DOWN - 1) + 0;//�E�[���烉���_���Ő���
	g_Kirakira[num].Size.x = KIRAKIRA_SIZE_W;
	g_Kirakira[num].Size.y = KIRAKIRA_SIZE_H;
	g_Kirakira[num].Use = false;
	g_Kirakira[num].countK = 0;

	g_Kirakira[num].collision_size.x = KIRAKIRA_SIZE_W  + 200;
	g_Kirakira[num].collision_size.y = KIRAKIRA_SIZE_H  + 200;


}


//================================
//�G�l�~�[�̎��ӂɃL���L���𐶐�����֐�
//================================
void Kirakira_bone(D3DXVECTOR2 Epos , int bone_ster)//�G�l�~�[�̃|�W�V�������擾����, �������鐯�̐�
{
	for (int i = 0; i < bone_ster; i++)
	{
		for (int num = 0; num < KIRAKIRA_MAX; num++) //���ׂĂ̒�����
		{
			if (g_Kirakira[num].Use == false) {	//���g�p�̍\���̂�������

				g_Kirakira[num].Pos.x = (Epos.x - 100) + rand() % 200;//�G�l�~�[�̍��WX����+-100
				g_Kirakira[num].Pos.y = (Epos.y - 100) + rand() % 200;//�G�l�~�[�̍��WY����+-100
				g_Kirakira[num].Size.x = KIRAKIRA_SIZE_W;
				g_Kirakira[num].Size.y = KIRAKIRA_SIZE_H;
				g_Kirakira[num].Use = true;
				g_Kirakira[num].countK = 0;

				g_Kirakira[num].collision_size.x = KIRAKIRA_SIZE_W ;
				g_Kirakira[num].collision_size.y = KIRAKIRA_SIZE_H ;


				break;
			}
			
		}
	}


}

//============================================
//�v���C���[���L���L���ƐڐG�����Ƃ��̏���

void player_get_kirakira(int num)
{
	if (g_Kirakira[num].Use == true)
	{
		if (CollisionBB(GetPlayer()->Position, g_Kirakira[num].Pos,
			GetPlayer()->size, g_Kirakira[num].collision_size) == true)
		{

			GetPlayer()->energy += 1;

			g_Kirakira[num].Use = false;

		}
	}
}