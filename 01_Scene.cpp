
#include "01_Scene.h"
#include "field.h"//背景

#include "player.h"//プレイヤー
#include "bullet.h"//Pバレッド

#include "enemy.h"//エネミー
#include "enemybullet.h"//Eバレッド

#include "Enemy_PopALL.h"//エネミーの出現タイミング

#include "score.h"//スコア
#include "gauge.h"//キラキラのゲージ

#include "player_vs_enemy.h" //プレイヤーとエネミーの当たり判定
#include "p_bullet_vs_enemy.h"

#include "kirakira.h"//キラキラ
#include "progress.h"

#include "stage_01.h"

#include "tutorial.h"
#include "Boss.h"
#include "boss_parts.h"

#include "Explosion.h"

#include "skill_ui.h"

#include "00_soundmain.h"

//後で消す↓
#include"keyboard.h"
#include"inputx.h"

Game* Game_01[] = { new FIELD,new TUTORIAL, new ENEMY,new BULLET,new ENEMY_BULLET ,new PLAYER,new EXPLOSION, new PlayerVSEnemy, new SCORE,new GAUGE, new KIRAKIRA, new Progress , new Stage_BOX ,new P_BulletVSEnemy, new SKILL_UI };


HRESULT InitScene()
{



	//SetStage(STAGE_01);	//直接ステージを指定
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
	Game_01配列に格納されている任意のオブジェクトのポインタを取得する関数
	引数：int index (オブジェクト番号)
	戻り値：オブジェクトのポインタ
*/
Game* GetSceneObject(int index)
{
	return Game_01[index];
}