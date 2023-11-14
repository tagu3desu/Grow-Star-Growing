/*==============================================================================

   �v���C���[���� [player.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include	"player.h"
#include    "enemy.h"
#include    "enemybullet.h"

#include	"sprite.h"
#include	"texture.h"
#include	"bullet.h"
#include	"data.h"

//#include	"mouse.h"
#include	"keyboard.h"
#include    "collision.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	PLAYER_SIZE_W	(30.0f)	//�v���C���[�̉��̃T�C�Y
#define	PLAYER_SIZE_H	(30.0f)	//�v���C���[�̏c�̃T�C�Y

#define PLAYER_MAX_SIZE_W	(300.0f)	//���剻���̉��̃T�C�Y
#define PLAYER_MAX_SIZE_H	(300.0f)	//���剻���̏c�̃T�C�Y

#define PLAYER_HP (3)			//�v���C���[HP
#define	PLAYER_HP_SIZE_W	(50.0f)	//�v���C���[HP�̉��̃T�C�Y
#define PLAYER_HP_SIZE_H	(50.0f) //�v���C���[HP�̏c�̃T�C�Y 

#define HUGE_SIZE_W (300.0f)
#define HUGE_SIZE_H (250.0f)


#define PLAYER_SPEED	(3.0f)		//�v���C���[�̈ړ����x

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
PLAYER	g_Player;	// �v���C���[�I�u�W�F�N�g


//=============================================================================
// ����������
//=============================================================================
HRESULT PLAYER::InitGame(void)
{
	//�e�N�X�`�����[�h
	g_Player.texNo = LoadTexture((char*)"data\\texture\\hosi.png");//�e�N�X�`���t�@�C���p�X

	g_Player.Position = D3DXVECTOR2(PLAYER_SIZE_W / 2, SCREEN_HEIGHT / 2);

	g_Player.size.x = PLAYER_SIZE_W;
	g_Player.size.y = PLAYER_SIZE_H;

	g_Player.Rotate = 0.0f;
	g_Player.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Player.energy = 100;
	g_Player.gain = 5;
	g_Player.use = TRUE;

	g_Player.Bulletrate = 0;
	g_Player.ShotFlag = false;

	g_Player.Hp = PLAYER_HP;
	g_Player.HptexNo = LoadTexture((char*)"data\\texture\\playerHP.png");
	g_Player.HpSize.x = PLAYER_HP_SIZE_W;
	g_Player.HpSize.y = PLAYER_HP_SIZE_H;
	g_Player.HpPos = D3DXVECTOR2(50, 50);


	g_Player.HugetexNo=LoadTexture((char*)"data\\texture\\BIGUI.png");
	g_Player.HugePos = D3DXVECTOR2(480, 540);
	g_Player.HugeSize.x = HUGE_SIZE_W;
	g_Player.HugeSize.y = HUGE_SIZE_H;
	g_Player.HugeCount = 0;
	g_Player.HugeRotate = 0;
	g_Player.ResetHuge = false;
	g_Player.ChangeHuge = false;


	g_Player.FrameCaount = 0;
	g_Player.AtacckDelay = 0;
	g_Player.SizeUp = false;
	g_Player.tackle = false;
	g_Player.TackleDamege = 10;

	//�U����ʂ��Z�b�g
	g_Player.SkillType[0] = GetData()->SkillType[0];		//�ʏ�e(�Œ�)
	g_Player.SkillType[1] = GetData()->SkillType[1];		//�X�L��1(�����͎O�ҖC�e)
	g_Player.SkillType[2] = GetData()->SkillType[2];		//�X�L��2(�����͉�]�e)

	for (int i = 0; i < 3; i++)
	{
		g_Player.SkillUsageMax[i] = GetBulletUsageMax(g_Player.SkillType[i]);			//�g�p�񐔂̍ő吔���擾
		g_Player.SkillUsageCount[i] = g_Player.SkillUsageMax[i];						
		g_Player.SkillCoolTimeMax[i] = GetBulletCoolTimeMax(g_Player.SkillType[i]);		//�N�[���^�C���̍ő吔���擾
		g_Player.SkillCoolTime[i] = g_Player.SkillCoolTimeMax[i];
	}

	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void PLAYER::UninitGame(void)
{


}

//=============================================================================
// �X�V����
//=============================================================================
void PLAYER::UpdateGame(void)
{
	//�_���[�W����
	/*Player_dameg_reaction();*/

	

	if (g_Player.use == TRUE)
	{
		//�L�[���̓`�F�b�N
		{
			if (Keyboard_IsKeyDown(KK_W) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_UP) || GetThumbLeftY(0) >= 0.3)			//��
			{
				// �����ꂽ�Ƃ��̏���
				g_Player.Position.y += -PLAYER_SPEED;
			}
			else if (Keyboard_IsKeyDown(KK_S) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_DOWN) || GetThumbLeftY(0) <= -0.3)	//��
			{
				// �����ꂽ���̏���
				g_Player.Position.y += PLAYER_SPEED;
			}

			if (Keyboard_IsKeyDown(KK_A) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_LEFT)|| GetThumbLeftX(0) <= -0.3)			//��
			{
				// �����ꂽ���̏���
				g_Player.Position.x += -PLAYER_SPEED;
			}
			else if (Keyboard_IsKeyDown(KK_D) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_RIGHT) || GetThumbLeftX(0)  >= 0.3)	//�E
			{
				// �����ꂽ���̏���
				g_Player.Position.x += PLAYER_SPEED;
			}
		}

	

		//�e�̔���

		if (Keyboard_TriggerKeyDown(KK_LEFT) || IsButtonTriggered(0, XINPUT_GAMEPAD_B)/* && ShotFlag == false*/)
		{
			//���̗ʂ���萔���鎞���g�p�񐔂�0�łȂ���
			
				D3DXVECTOR2 pos = g_Player.Position;		// �v���C���\�̍��W�ɒe�𔭎�
				SetBullet(g_Player.SkillType[0], pos);		// �X�L�����0�̒e�𔭎�
				ShotFlag = true;
		}
		/*if (ShotFlag == true)
		{
			Bulletrate++;
		}
		if (Bulletrate > 20)
		{
			Bulletrate = 0;
			ShotFlag = false;
		}*/
		else if (Keyboard_TriggerKeyDown(KK_UP) || IsButtonTriggered(0, XINPUT_GAMEPAD_Y))
		{
			//���̗ʂ���萔���鎞���g�p�񐔂�0�łȂ���
			if ( (g_Player.SkillUsageCount[1] != 0))
			{
				D3DXVECTOR2 pos = g_Player.Position;		// �v���C���\�̍��W�ɒe�𔭎�
				SetBullet(g_Player.SkillType[1], pos);		// �X�L�����1�̒e�𔭎�
				if (g_Player.SkillUsageCount[1] > 0)		// �c��g�p�񐔂����炷
				{
					g_Player.SkillUsageCount[1]--;
				}
			}
		}
		else if (Keyboard_TriggerKeyDown(KK_RIGHT) || IsButtonTriggered(0, XINPUT_GAMEPAD_X))
		{
			//���̗ʂ���萔���鎞���g�p�񐔂�0�łȂ���
			if ( (g_Player.SkillUsageCount[2] != 0))
			{
				D3DXVECTOR2 pos = g_Player.Position;		// �v���C���\�̍��W�ɒe�𔭎�
				SetBullet(g_Player.SkillType[2], pos);		// �X�L�����2�̒e�𔭎�
				if (g_Player.SkillUsageCount[2] > 0)		// �c��g�p�񐔂����炷
				{
					g_Player.SkillUsageCount[2]--;
				}
			}
		}

		// �N�[���^�C������
		for (int i = 0; i < 3; i++)
		{
			if (g_Player.SkillUsageCount[i] == 0)
			{
				g_Player.SkillCoolTime[i]--;
				if (g_Player.SkillCoolTime[i] <= 0)
				{
					g_Player.SkillCoolTime[i] = g_Player.SkillCoolTimeMax[i];
					g_Player.SkillUsageCount[i] = g_Player.SkillUsageMax[i];
				}
			}
		}



	   //===============================================================
	   // ���剻�n
		{
			

			//���剻����
			if (Keyboard_TriggerKeyDown(KK_LEFTSHIFT) || IsButtonTriggered(0, XINPUT_GAMEPAD_LEFT_SHOULDER))
			{
				if (g_Player.SizeUp == false && g_Player.energy >= 11)//�������Ƃ�
				{	
					g_Player.ChangeHuge = true;	//��]�J�n
					g_Player.SizeUp = true;	//���剻�I��
					g_Player.size = D3DXVECTOR2(PLAYER_MAX_SIZE_W, PLAYER_MAX_SIZE_H);
					g_Player.energy -= 10;
				}


				else if(g_Player.SizeUp == true && g_Player.HugeCount == 0)//���剻���Ă鎞
				{
					g_Player.ChangeHuge = true;	//��]�J�n
					g_Player.SizeUp = false;
					g_Player.size = D3DXVECTOR2(PLAYER_SIZE_W, PLAYER_SIZE_H);
					

				}
			}

			//===============================================
			//���剻UI�̉�]����
			
			if (g_Player.ChangeHuge==true && g_Player.HugeCount < 60)	//UI��]
			{
				g_Player.HugeCount++;
				g_Player.HugeRotate += 3;
			}
			else if (g_Player.ChangeHuge==true &&  g_Player.HugeCount>=60)
			{
				g_Player.HugeCount = 0;
				g_Player.ChangeHuge = false;
			}

			

			//==============================================
			//�^�b�N���̏���

			//���剻��Ԃ̏���
			if (g_Player.SizeUp == true)
			{
				
				g_Player.FrameCaount++;
				if (g_Player.FrameCaount >= 10.0f)
				{
					g_Player.energy -= 1;		//60f���Ƃ�-1����
					g_Player.FrameCaount = 0;
				}

				if (Keyboard_TriggerKeyDown(KK_SPACE) || IsButtonTriggered(0, XINPUT_GAMEPAD_RIGHT_SHOULDER))
				{
					g_Player.tackle = true;			//�^�b�N���J�n
				}

				
				


				if (g_Player.tackle == true)//�^�b�N�����Ȃ�
				{
					g_Player.AtacckDelay++; //�^�b�N���J�n����̃t���[���̃J�E���g
					if (g_Player.AtacckDelay >= 30 && g_Player.AtacckDelay < 60)	//�l���Ă݂悤
					{
						g_Player.Rotate += 20.0f;		//��]��
						g_Player.Position.x -= 10.0f;	//�^�b�N���I����Ė߂��Ă�Ƃ�
					}
					else if (g_Player.AtacckDelay >= 60)	//�O�����V�����I
					{
						g_Player.Rotate = 0;		//��]�����ɖ߂�
						g_Player.AtacckDelay = 0;	//�^�b�N������̃t���[���J�E���g�I��
						g_Player.tackle = false;	//�^�b�N���I���
					}
					else //���C�U�̂ӂƂ����ō�
					{
						g_Player.Rotate += 20.0f;		//��]��
						g_Player.Position.x += 10.0f;	//�G�̕��Ƀ^�b�N����
					}

				}

				if (g_Player.energy == 0 && g_Player.tackle == false)
				{
					g_Player.SizeUp = false;
					g_Player.size = D3DXVECTOR2(PLAYER_SIZE_W, PLAYER_SIZE_H);
					g_Player.ChangeHuge = true;
				}
			}
		}

	}

	//================================================
	//��ʊO�`�F�b�N

	{
		//�㉺
		if (g_Player.Position.y < SCREEN_LIMIT_UP + PLAYER_SIZE_H / 2)
		{
			g_Player.Position.y = SCREEN_LIMIT_UP + PLAYER_SIZE_H / 2;
		}
		else if (g_Player.Position.y > SCREEN_LIMIT_DOWN - PLAYER_SIZE_H / 2)
		{
			g_Player.Position.y = SCREEN_LIMIT_DOWN - PLAYER_SIZE_H / 2;
		}

		//���E
		if (g_Player.Position.x < SCREEN_LIMIT_LEFT + PLAYER_SIZE_W / 2)
		{
			g_Player.Position.x = SCREEN_LIMIT_LEFT + PLAYER_SIZE_W / 2;
		}
		else if (g_Player.Position.x > SCREEN_LIMIT_RIGHT - PLAYER_SIZE_W / 2)
		{
			g_Player.Position.x = SCREEN_LIMIT_RIGHT - PLAYER_SIZE_W / 2;
		}
	}

	//===========================================================
	//�L���L���̏���Ɖ�������

	{
		//�G�i�W�[100�ȏ�Ȃ�؂�̂�
		if (g_Player.energy > 100)
		{
			g_Player.energy = 100;
		}

		if (g_Player.energy < 0)
		{
			g_Player.energy = 0;
		}

	}
	
	//HP��0�ɂȂ�����
	if (g_Player.Hp <= 0)
	{
		SetScene(SCENE_RESULT);
	}
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void PLAYER::DrawGame(void)
{
	//�\���̃`�F�b�N
	if (g_Player.use == TRUE)
	{
		//�e�N�X�`���̃Z�b�g
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Player.texNo));
		
		//�`��
		DrawSpriteColorRotate(g_Player.Position.x, g_Player.Position.y,
			g_Player.size.x,//���T�C�Y
			g_Player.size.y,//���T�C�Y
			g_Player.Rotate,
			g_Player.Color,
			4, 
			1.0f,
			1.0f, 
			1);
	}


	//=======================================
	//HP�̕\��
	//======================================
	for (int i = 0; i < g_Player.Hp; i++)
	{
		//HP�e�N�X�`���̃Z�b�g
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Player.HptexNo));

		//HP�`��
		DrawSpriteColorRotate(g_Player.HpPos.x + i * 40, g_Player.HpPos.y,
			g_Player.HpSize.x,
			g_Player.HpSize.y,
			0,
			g_Player.Color,
			1,
			1.0f,
			1.0f,
			1);
	}

	//=========================================
	//�^�b�N����UI
	//=========================================
	if (g_Player.use == true)
	{
		//UI�e�N�X�`���̃Z�b�g
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Player.HugetexNo));

		//UI�`��
		DrawSpriteColorRotate(g_Player.HugePos.x, g_Player.HugePos.y,
			g_Player.HugeSize.x,
			g_Player.HugeSize.y,
			g_Player.HugeRotate,
			g_Player.Color,
			1,
			1.0f,
			1.0f,
			1);
	}
}


//==========================
//�\���̂̐擪�A�h���X��Ԃ�
//==========================
PLAYER	*GetPlayer()
{
	return	&g_Player;
}


//============================================
//�_���[�W���󂯂����̏����i�G�̒e����

void Player_dameg_reaction()
{
	for (int i = 0; i < ENEMY_MAX_BULLET; i++)
	{
		if (GetEnemyBullet(i)->use == true) {

			if (CollisionBB(g_Player.Position, GetEnemyBullet(i)->pos,//
				g_Player.size, GetEnemyBullet(i)->size) == true)
			{	
				g_Player.energy -= 2;

				GetEnemyBullet(i)->use = false;

				break;
			}
		}
	}
}

