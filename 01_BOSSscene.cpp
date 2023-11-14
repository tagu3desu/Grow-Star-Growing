
#include "01_BOSSscene.h"
#include "field.h"

#include "player.h"//�v���C���[
#include "bullet.h"//P�o���b�h

#include "enemy.h"//�G�l�~�[
#include "enemybullet.h"//E�o���b�h

#include "score.h"//�X�R�A
#include "gauge.h"//�L���L���̃Q�[�W

#include "player_vs_enemy.h" //�v���C���[�ƃG�l�~�[�̓����蔻��
#include "p_bullet_vs_enemy.h"
#include "kirakira.h"//�L���L��

#include "Boss.h"//�{�X�{��
#include "boss_parts.h"//�{�X�̕���

#include "skill_ui.h"

#include"00_soundmain.h"

#include "data.h"



Game* Game_01_BOSS[] = { new FIELD, new ENEMY,new BULLET,new ENEMY_BULLET ,new PLAYER, new PlayerVSEnemy, new SCORE,new GAUGE, new KIRAKIRA ,new BOSS_01,new BOSS_PARTS ,new P_BulletVSEnemy , new SKILL_UI };


HRESULT	InitBossScene()
{
	for (int i = 0; i < MAX_BOSS_HEDDER; i++) {

		Game_01_BOSS[i]->InitGame();
	}

	//==============================
	//�ǂ̃{�X�Ȃ̂��𔻕�
	switch (GetScene())
	{
	case SCENE_BOSS01:

		SetBoss_01(1, 700, 270);
		PlayBGM(BOSS_001, 1.0f);

		break;

	case SCENE_BOSS02:

		SetBoss_01(2, 700, 270);
		PlayBGM(BOSS_002, 1.0f);
		break;

	case SCENE_BOSS03:

		SetBoss_01(3, 700, 270);
		PlayBGM(BOSS_003, 1.0f);
		break;

	case SCENE_BOSS04:

		SetBoss_01(4, 700, 270);
		PlayBGM(BOSS_004, 1.0f);
		break;

	default:
		break;
	}

	//���݂̃X�R�A��ǂݍ���ŃZ�b�g����
	int Score = GetData()->PlayerScore;
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
			score->AddScore(Score);
		}
	}

	return S_OK;
}

void	UninitBossScene()
{
	for (int i = 0; i < MAX_BOSS_HEDDER; i++) {

		Game_01_BOSS[i]->UninitGame();

	}
	StopS();
}

void	UpdateBossScene()
{
	for (int i = 0; i < MAX_BOSS_HEDDER; i++) {
		Game_01_BOSS[i]->UpdateGame();
	}

}

void	DrawBossScene()
{
	for (int i = 0; i < MAX_BOSS_HEDDER; i++) {

		Game_01_BOSS[i]->DrawGame();
	}
}

/*
	Game_01�z��Ɋi�[����Ă���C�ӂ̃I�u�W�F�N�g�̃|�C���^���擾����֐�
	�����Fint index (�I�u�W�F�N�g�ԍ�)
	�߂�l�F�I�u�W�F�N�g�̃|�C���^
*/
Game* GetBossSceneObject(int index)
{
	return Game_01_BOSS[index];
}