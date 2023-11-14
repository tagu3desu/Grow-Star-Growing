
#include "01_Scene.h"
#include "field.h"//�w�i

#include "player.h"//�v���C���[
#include "bullet.h"//P�o���b�h

#include "enemy.h"//�G�l�~�[
#include "enemybullet.h"//E�o���b�h

#include "Enemy_PopALL.h"//�G�l�~�[�̏o���^�C�~���O

#include "score.h"//�X�R�A
#include "gauge.h"//�L���L���̃Q�[�W

#include "player_vs_enemy.h" //�v���C���[�ƃG�l�~�[�̓����蔻��
#include "p_bullet_vs_enemy.h"

#include "kirakira.h"//�L���L��
#include "progress.h"

#include "stage_01.h"

#include "tutorial.h"
#include "Boss.h"
#include "boss_parts.h"

#include "Explosion.h"

#include "skill_ui.h"

#include "00_soundmain.h"

//��ŏ�����
#include"keyboard.h"
#include"inputx.h"

Game* Game_01[] = { new FIELD,new TUTORIAL, new ENEMY,new BULLET,new ENEMY_BULLET ,new PLAYER,new EXPLOSION, new PlayerVSEnemy, new SCORE,new GAUGE, new KIRAKIRA, new Progress , new Stage_BOX ,new P_BulletVSEnemy, new SKILL_UI };


HRESULT InitScene()
{



	//SetStage(STAGE_01);	//���ڃX�e�[�W���w��
	for (int i = 0; i < MAX_HEDDER; i++) {

		Game_01[i]->InitGame();
	}

	return S_OK;
}

void UninitScene()
{
	
	for (int i = 0; i < MAX_HEDDER; i++) {

		Game_01[i]->UninitGame();

	}

}

void UpdateScene()
{
	
	for (int i = 0; i < MAX_HEDDER; i++) {
		Game_01[i]->UpdateGame();
	}
	

}

void DrawBScene()
{
	
	for (int i = 0; i < MAX_HEDDER; i++) {

		Game_01[i]->DrawGame();
	}
	

}


/*
	Game_01�z��Ɋi�[����Ă���C�ӂ̃I�u�W�F�N�g�̃|�C���^���擾����֐�
	�����Fint index (�I�u�W�F�N�g�ԍ�)
	�߂�l�F�I�u�W�F�N�g�̃|�C���^
*/
Game* GetSceneObject(int index)
{
	return Game_01[index];
}