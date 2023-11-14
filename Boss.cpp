/*==============================================================================

   �{�X�̏���[Boss.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include"Boss.h"
#include"01_BOSSscene.h"
#include"sprite.h"
#include"texture.h"
#include"boss_parts.h"

#include "enemybullet.h"
#include "bullet.h" //��ŕύX�K�{
#include "collision.h"
#include "player.h"
#include "score.h"

//======================
//�}�N����`
//======================
// 
//======================
//�v���g�^�C�v�錾
//======================
// 
//======================
//�O���[�o���ϐ�
//======================
static BOSS_01 g_Boss01;	//�{�X�уW�F�N�g
int  SceneNo = 0;


//==========================
//������
//==========================
HRESULT BOSS_01::InitGame()
{
	{
		//�e�N�X�`���̃��[�h
		g_Boss01.TexNo = LoadTexture((char*)"data\\texture\\Boss1.png");
		g_Boss01.BreakTexno = LoadTexture((char*)"data\\texture\\Boss1B.png");

		//�\���̂̏�����
		g_Boss01.Pos.x = SCREEN_WIDTH;
		g_Boss01.Pos.y = SCREEN_HEIGHT;
		g_Boss01.Use = false;
		g_Boss01.HP = 100;
		g_Boss01.size.x = BOSS_SIZE_W;
		g_Boss01.size.y = BOSS_SIZE_H;
		g_Boss01.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Boss01.BossNo = 0;
		g_Boss01.Count;
		g_Boss01.tacklehit = false;
		g_Boss01.tacklecount = 0;
		for (int i = 0; i < PARTS_MAX; i++)
		{
			g_Boss01.PartsIndex[i] = -1;
		}

		//==============================
	//�ǂ̃{�X�Ȃ̂��𔻕�
		switch (GetScene())
		{
		case SCENE_BOSS01:

			SceneNo = 1;

			break;

		case SCENE_BOSS02:

			SceneNo = 2;
			break;

		case SCENE_BOSS03:

			SceneNo = 3;
			break;

		case SCENE_BOSS04:

			SceneNo = 4;
			break;

		default:
			break;
		}
	}
	return S_OK;	//����I��
}
//=============================
//�I������
//=============================
void BOSS_01::UninitGame()
{

}
//==============================
//�X�V����
//==============================
void BOSS_01::UpdateGame()
{

	Boss_damege_reaction();


	g_Boss01.FrameWait++;
	if (g_Boss01.Use == true) {
		if (g_Boss01.FrameWait <= 60)
		{
			g_Boss01.Pos += g_Boss01.move;
		}
		else if (g_Boss01.FrameWait > 60 && g_Boss01.FrameWait < 180)
		{
			g_Boss01.Pos -= g_Boss01.move;
		}
		else if (g_Boss01.FrameWait > 180 && g_Boss01.FrameWait < 240)
		{
			g_Boss01.Pos += g_Boss01.move;
			
		}
		else if (g_Boss01.FrameWait > 240 && g_Boss01.FrameWait < 300)
		{
			g_Boss01.Pos -= g_Boss01.move;
			g_Boss01.FrameWait = 0;
		}
	}

	if (g_Boss01.tacklehit == true)
	{
		g_Boss01.tacklecount++;
	}
	if (g_Boss01.tacklecount >= 60)
	{
		g_Boss01.tacklehit = false;
		g_Boss01.tacklecount = 0;
	}

	if (g_Boss01.Use == true) {

		g_Boss01.Count++;
		if (g_Boss01.Count > 20)
		{
			Set_Enemybullet(4, GetPlayer()->Position, g_Boss01.Pos);
			Set_Enemybullet(5, GetPlayer()->Position, g_Boss01.Pos);
			Set_Enemybullet(6, GetPlayer()->Position, g_Boss01.Pos);
			g_Boss01.Count = 0;
		}
	}
	


	//�{�X���ʂ̒��S���W���X�V
	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (g_Boss01.PartsIndex[i] > -1)
		{
			if (GetBossParts(g_Boss01.PartsIndex[i])->Use == true)
			{
				GetBossParts(g_Boss01.PartsIndex[i])->BossPos = g_Boss01.Pos;
			}
		}
	}
}
//================================
//�`�揈��
//================================
void BOSS_01::DrawGame()
{
	if (g_Boss01.Use == true)//�{�X��true�̎��̂�
	{

		if (Get_BossPartslivis() == true) {
			//�e�N�X�`���̃Z�b�g
			GetDeviceContext()->PSSetShaderResources(0, 1,
				GetTexture(g_Boss01.TexNo));
		}
		else if (Get_BossPartslivis() == false)
		{
			//�e�N�X�`���̃Z�b�g
			GetDeviceContext()->PSSetShaderResources(0, 1,
				GetTexture(g_Boss01.BreakTexno));
		}


		//�X�v���C�g�̕`��
		DrawSpriteColorRotate
		(
			g_Boss01.Pos.x,
			g_Boss01.Pos.y,
			g_Boss01.size.x,
			g_Boss01.size.y,
			g_Boss01.Rot,
			g_Boss01.color,	//�Ƃ肠�����̐F
			0,	//�p�^�[���ԍ�
			1.0f,	//�p�^�[���̉��T�C�Y
			1.0f,	//�p�^�[���̏c�T�C�Y
			1		//�p�^�[���̉��̐�
		);

		//HP�Q�[�W�̕\��
		//�e�N�X�`���̃Z�b�g(�ԃQ�[�W)
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(LoadTexture((char*)"data\\texture\\kk_bossHP.png")));
		//�X�v���C�g�`��
		DrawSpriteColorRotate
		(
			920.0f,
			250.0f,
			30.0f,
			350.0f,
			0.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			1.0f,
			1.0f,
			1.0f,
			1
		);

		//�e�N�X�`���̃Z�b�g(�΃Q�[�W)
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(LoadTexture((char*)"data\\texture\\kk_bosshpnokori.png")));
		//�X�v���C�g�`��
		DrawSpriteColorRotate
		(
			920.0f,
			250.0f + (100.0f - g_Boss01.HP) *1.5f,
			30.0f,
			350.0f * g_Boss01.HP / 100,
			0.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			1.0f,
			1.0f,
			1.0f,
			1
		);

	}


}
//================================
//�\���̂̐擪�̃|�C���^��Ԃ�
//================================
BOSS_01  *GetBoss_01()
{
	return  &g_Boss01;
}
//==========================================
//�{�X�Ăяo�����I��
// �{�X�̎��,���WX�A���WY
//
//==========================================
void SetBoss_01(int Boss_01Num,float BossX, float BossY)
{
	if (g_Boss01.Use == false) {
		switch (Boss_01Num)
		{
		case 1:	//��
			g_Boss01.Pos = D3DXVECTOR2(BossX, BossY);
			g_Boss01.move = D3DXVECTOR2(0.0f, BOSS_SPEED);
			//�{�X����0�Ԗڂ��Z�b�g		���S����100.0f���E100.0f��̈ʒu�AHP50 
			g_Boss01.PartsIndex[0] = SetBossParts(-100.0f, -50.0f, 20, g_Boss01.Pos);
			g_Boss01.PartsIndex[1] = SetBossParts(-75.0f, +100.0f, 20, g_Boss01.Pos);
			g_Boss01.Use = true;

			g_Boss01.TexNo = LoadTexture((char*)"data\\texture\\Boss1.png");
			g_Boss01.BreakTexno = LoadTexture((char*)"data\\texture\\Boss1B.png");

			break;

		case 2:	//�N���I�l
			g_Boss01.Pos = D3DXVECTOR2(BossX, BossY);
			g_Boss01.move = D3DXVECTOR2(0.0f, BOSS_SPEED);
			//�{�X����0�Ԗڂ��Z�b�g		���S����100.0f���E100.0f��̈ʒu�AHP50 
			g_Boss01.PartsIndex[0] = SetBossParts(-95.0f, -95.0f, 50, g_Boss01.Pos);
			g_Boss01.PartsIndex[1] = SetBossParts(+85.0f, -100.0f, 50, g_Boss01.Pos);
			g_Boss01.PartsIndex[2] = SetBossParts(-10.0f, 55.0f, 50, g_Boss01.Pos);
			g_Boss01.Use = true;
			g_Boss01.TexNo = LoadTexture((char*)"data\\texture\\Boss2.png");
			g_Boss01.BreakTexno = LoadTexture((char*)"data\\texture\\Boss2B.png");
			break;

		case 3:	//�r����
			g_Boss01.Pos = D3DXVECTOR2(BossX, BossY);
			g_Boss01.move = D3DXVECTOR2(0.0f, BOSS_SPEED);
			//�{�X����0�Ԗڂ��Z�b�g		���S����100.0f���E100.0f��̈ʒu�AHP50 
			g_Boss01.PartsIndex[0] = SetBossParts(+100.0f, 50.0f, 50, g_Boss01.Pos);
			g_Boss01.PartsIndex[1] = SetBossParts(-100.0f, 0.0f, 50, g_Boss01.Pos);
			g_Boss01.PartsIndex[2] = SetBossParts(-10.0f, -60.0f, 50, g_Boss01.Pos);
			g_Boss01.Use = true;
			g_Boss01.TexNo = LoadTexture((char*)"data\\texture\\Boss3.png");
			g_Boss01.BreakTexno = LoadTexture((char*)"data\\texture\\Boss3B.png");
			break;

		case 4:	//�ڋ�
			g_Boss01.Pos = D3DXVECTOR2(BossX, BossY);
			g_Boss01.move = D3DXVECTOR2(0.0f, BOSS_SPEED);
			//�{�X����0�Ԗڂ��Z�b�g		���S����100.0f���E100.0f��̈ʒu�AHP50 
			g_Boss01.PartsIndex[0] = SetBossParts(-20.0f, -30.0f, 300, g_Boss01.Pos);
			g_Boss01.Use = true;
			g_Boss01.TexNo = LoadTexture((char*)"data\\texture\\Boss4.png");
			g_Boss01.BreakTexno = LoadTexture((char*)"data\\texture\\Boss4B.png");
			break;

		default:
			break;
		}
		g_Boss01.BossNo = Boss_01Num;
		return;
	}
}

//=============================================================
//�{�X�̃_���[�Wreaction
//============================================================
void Boss_damege_reaction()
{
	
	if (g_Boss01.Use == true) {
		if (Get_BossPartslivis() == false) //�{�X�̃p�[�c�������Ă��Ȃ��Ȃ�
		{
			if (GetPlayer()->SizeUp == true && g_Boss01.tacklehit==false)
			{
				if (CollisionBB(GetPlayer()->Position, g_Boss01.Pos,
					GetPlayer()->size, g_Boss01.size) == true)//����������
				{
					//�_���[�W����
					g_Boss01.HP -= GetPlayer()->TackleDamege;
					g_Boss01.tacklehit = true;



				}
			}
			else
			{
				for (int i = 0; i < MAX_BULLET; i++)//�o���b�h�S�̂�����
				{
					if (GetBullet(i)->use == true)//�g�p��Ԃ�
					{
						if (CollisionBB(GetBullet(i)->pos, g_Boss01.Pos,
							GetBullet(i)->size, g_Boss01.size) == true)//����������
						{
							//�_���[�W����
							g_Boss01.HP -= GetBullet(i)->damage;


							GetBullet(i)->use = false;
							break;
						}
					}
				}
			}

			if (g_Boss01.HP <= 0)
			{
				g_Boss01.HP = 0;
				g_Boss01.Use = false;//����
				// �X�R�A�f�[�^�̍X�V(���̃N���X�̊֐����Ăяo���Ƃ��́A�����̃R�[�h���R�s�y�����ς��Ďg���Ă�������)
				{
					for (int is = 0; is < MAX_BOSS_HEDDER; is++)
					{
						Game* object = GetBossSceneObject(is);

						//�N���X�̎�ނ���v�����Ƃ��̂ݏ������s��
						if (typeid(*object) == typeid(SCORE))
						{
							//�_�E���L���X�g���s���h���N���X�ŗL�̊֐����Ăяo����悤�ɂ���
							//���z�֐��݂̂̔h���N���X�̏ꍇ���̏����͕K�v����܂���
							SCORE* score = dynamic_cast<SCORE*>(GetBossSceneObject(is));
							//�X�R�A�̉��Z
							score->AddScore(4000);
						}
					}
				}
				SetScene(SCENE_RESULT);
			}
		
		}
	}
	
}


