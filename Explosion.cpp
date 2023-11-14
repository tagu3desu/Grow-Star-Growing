#include "Explosion.h"
#include "main.h"
#include "sprite.h"

#include "00_soundmain.h"
//======================
//�O���[�o���ϐ�
//======================
EXPLOSION	g_Explosion[EXPLOSION_MAX];	//�����\���̔z��

//======================
//������
//======================
HRESULT EXPLOSION::InitGame()
{
	//�e�N�X�`���̃��[�h
	int texno = LoadTexture((char*)"data\\TEXTURE\\fgh_BOOMkansei.png");
	//�����\���̂̏�����
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		g_Explosion[i].use = false;	//�t���O�𖢎g�p�ɂ���
		g_Explosion[i].size.x = EXPLOSION_SIZE_W;	//���T�C�Y
		g_Explosion[i].size.y = EXPLOSION_SIZE_Y;	//�c�T�C�Y
		g_Explosion[i].pos = D3DXVECTOR2(0, 0);	//�\�����W
		g_Explosion[i].rot = 0.0f;
		g_Explosion[i].texNo = texno;	//�e�N�X�`���ԍ�
		g_Explosion[i].move = D3DXVECTOR2(0.0f, 0.0f);	//�ړ��X�s�[�h
		g_Explosion[i].AnimePattern = 0;
		g_Explosion[i].AnimeSpeed = 0;
	}
	return S_OK;
}
//=============================
//�I������
//=============================
void EXPLOSION::UninitGame()
{

}

//=============================
//�X�V����
//=============================
void EXPLOSION::UpdateGame()
{
	//�\���̂�S�ď���
	for (int i = 0; i < EXPLOSION_MAX; i++) {
		if (g_Explosion[i].use == true) {

			//���W�̍X�V
			g_Explosion[i].pos += g_Explosion[i].move;


			//�A�j���[�V�����̍X�V
			g_Explosion[i].AnimePattern += g_Explosion[i].AnimeSpeed;
			if (g_Explosion[i].AnimePattern > EXPLOSION_ANIME_MAX)
			{
				g_Explosion[i].use = false;
			}
		}
	}
}
//======================
//�`�揈��
//======================
void EXPLOSION::DrawGame()
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_Explosion[i].use == true) {
			//�e�N�X�`���̃Z�b�g
			GetDeviceContext()->PSSetShaderResources(0, 1,
				GetTexture(g_Explosion[i].texNo));

			//�X�v���C�g�̕`��
			DrawSpriteColorRotate
			(
				g_Explosion[i].pos.x,
				g_Explosion[i].pos.y,
				g_Explosion[i].size.x,
				g_Explosion[i].size.y,
				g_Explosion[i].rot,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),//�Ƃ肠�����̐F
				(int)g_Explosion[i].AnimePattern,		//�p�^�[���ԍ�
				1.0f / 4,	//�p�^�[���̉��T�C�Y
				1.0f / 5,	//�p�^�[���̏c�T�C�Y
				16		//�p�^�[�����̐�
			);


		}

	}
}
//=========================
//�\���̂̃|�C���^�擾
//=========================
EXPLOSION* GetExplosion()
{
	return &g_Explosion[0]; //return	g_Bullet;
}
//======================
//�e�̔���
//
//in	�������W�A�A�j���[�V�����X�s�[�h
//======================
void	SetExplosion(D3DXVECTOR2	pos, float animspeed)
{
	//�\���̂�S�Ē��ׂ�
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_Explosion[i].use == false)//���g�p�̍\���̂�������
		{
			g_Explosion[i].pos = pos;//�������W
			g_Explosion[i].use = true;//�g�p��
			g_Explosion[i].AnimeSpeed = animspeed;//�A�j���[�V�����X�s�[�h
			g_Explosion[i].AnimePattern = 0;//�p�^�[�������Z�b�g

			return;					//��������I��
		}
	}



}