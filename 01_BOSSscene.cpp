
#include "01_BOSSscene.h"
#include "field.h"

#include "player.h"//プレイヤー
#include "bullet.h"//Pバレッド

#include "enemy.h"//エネミー
#include "enemybullet.h"//Eバレッド

#include "score.h"//スコア
#include "gauge.h"//キラキラのゲージ

#include "player_vs_enemy.h" //プレイヤーとエネミーの当たり判定
#include "p_bullet_vs_enemy.h"
#include "kirakira.h"//キラキラ

#include "Boss.h"//ボス本体
#include "boss_parts.h"//ボスの部位

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
	//どのボスなのかを判別
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

	//現在のスコアを読み込んでセットする
	int Score = GetData()->PlayerScore;
	for (int is = 0; is < MAX_BOSS_HEDDER; is++)
	{
		Game* object = GetBossSceneObject(is);

		//クラスの種類が一致したときのみ処理を行う
		if (typeid(*object) == typeid(SCORE))
		{
			//ダウンキャストを行い派生クラス固有の関数を呼び出せるようにする
			//仮想関数のみの派生クラスの場合この処理は必要ありません
			SCORE* score = dynamic_cast<SCORE*>(GetBossSceneObject(is));
			//スコアの加算
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
	Game_01配列に格納されている任意のオブジェクトのポインタを取得する関数
	引数：int index (オブジェクト番号)
	戻り値：オブジェクトのポインタ
*/
Game* GetBossSceneObject(int index)
{
	return Game_01_BOSS[index];
}