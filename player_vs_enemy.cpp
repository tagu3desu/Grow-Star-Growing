/*==============================================================================

   プレイヤーとエネミーの当たり判定処理 [player_vs_enemy.cpp]
														 Author :	AT12G_25_髙橋建次
														 Date   :	2022_11_24
--------------------------------------------------------------------------------

==============================================================================*/
#include	"player_vs_enemy.h"
#include	"01_Scene.h"

#include	"collision.h"
#include	"player.h"
#include	"enemy.h"
#include	"enemybullet.h"

#include    "kirakira.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
PlayerVSEnemy::PlayerVSEnemy()
{
	
}

PlayerVSEnemy::~PlayerVSEnemy()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT PlayerVSEnemy::InitGame(void)
{
	invincible_time = 0;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void PlayerVSEnemy::UninitGame(void)
{


}

//=============================================================================
// 更新処理(当たり判定処理をここで行う)
//=============================================================================
void PlayerVSEnemy::UpdateGame(void)
{
	//========================================================
	//巨大化していないとき

	if (GetPlayer()->SizeUp == false) 
	{
		//プレイヤーとエネミーの当たり判定処理
		if (invincible_time <= 0)	//無敵状態でない場合のみ実行
		{
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				if ((GetEnemy(i)->Use == TRUE) && CollisionBB(GetPlayer()->Position, GetEnemy(i)->Pos, GetPlayer()->size, GetEnemy(i)->size) == TRUE)
				{
					//無敵状態に移行
					GetPlayer()->Hp -= 1;
					invincible_time = INVINCIBLE_TIME_MAX;
				}
			}
		}

		//プレイヤーとエネミー弾の当たり判定処理

		for (int i = 0; i < ENEMY_MAX_BULLET; i++)
		{
			if ((GetEnemyBullet(i)->use == TRUE) && CollisionBB(GetPlayer()->Position, GetEnemyBullet(i)->pos, GetPlayer()->size, GetEnemyBullet(i)->size) == TRUE)
			{
				GetEnemyBullet(i)->use = FALSE;	//とりあえず弾を消去する
				//無敵状態でない場合のみ実行
				if (invincible_time <= 0)
				{
					//無敵状態に移行
					GetPlayer()->Hp -= 1;
					invincible_time = INVINCIBLE_TIME_MAX;
				}
			}
		}
	}





	//=======================================================
	//巨大がしてる時の当たり判定

	if (GetPlayer()->SizeUp == true)
	{
		//========================================================
		//対エネミーの処理
		for (int i = 0; i < ENEMY_MAX; i++)
			{
			if ((GetEnemy(i)->Use == TRUE) && CollisionBB(GetPlayer()->Position, GetEnemy(i)->Pos, GetPlayer()->size, GetEnemy(i)->size) == TRUE)
			{
				if (GetPlayer()->tackle == true)//タックル中
				{
					GetEnemy(i)->Use = false;
				}

				else//タックル中でない
				{
					GetEnemy(i)->Use = false;
					GetPlayer()->energy -= DAMAGE;
				}

			}
		}
		
		//========================================================
		//対Eバレッド
		for (int i = 0; i < ENEMY_MAX_BULLET; i++)
		{
			if ((GetEnemyBullet(i)->use == TRUE) && CollisionBB(GetPlayer()->Position, GetEnemyBullet(i)->pos, GetPlayer()->size, GetEnemyBullet(i)->size) == TRUE)
			{
				if (GetPlayer()->tackle == true)//タックル中
				{
					GetEnemyBullet(i)->use = FALSE;
				}

				if (GetPlayer()->tackle == false)//タックル中じゃない
				{
					GetEnemyBullet(i)->use = FALSE;
					GetPlayer()->energy -= DAMAGE;
				}


			}
		}




	}


	//無敵状態時の処理
	if (invincible_time > 0)
	{
		invincible_time--;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void PlayerVSEnemy::DrawGame(void)
{
	//使用しない
}