/*==============================================================================

   プレイヤーバレットとエネミーの当たり判定処理 [p_bullet_vs_enemy.cpp]
														 Author :	AT12G_25_髙橋建次
														 Date   :	2022_12_1
--------------------------------------------------------------------------------

==============================================================================*/
#include	"p_bullet_vs_enemy.h"
#include	"01_Scene.h"

#include	"collision.h"
#include	"bullet.h"
#include	"enemy.h"
#include	"enemybullet.h"
#include	"kirakira.h"
#include	"score.h"


#include    "00_soundmain.h"
#include    "Explosion.h"

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
P_BulletVSEnemy::P_BulletVSEnemy()
{
	
}

P_BulletVSEnemy::~P_BulletVSEnemy()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT P_BulletVSEnemy::InitGame(void)
{

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void P_BulletVSEnemy::UninitGame(void)
{


}

//=============================================================================
// 更新処理(当たり判定処理をここで行う)
//=============================================================================
void P_BulletVSEnemy::UpdateGame(void)
{
	//プレイヤー弾とエネミーの当たり判定処理
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (GetBullet(i)->use == TRUE)	//弾が使用中
		{
			for (int j = 0; j < ENEMY_MAX; j++)
			{
				if ((GetEnemy(j)->Use == TRUE) && (CollisionBB(GetBullet(i)->pos, GetEnemy(j)->Pos, GetBullet(i)->size, GetEnemy(j)->size) == TRUE))
				{

					PlayEffect(Bom, 0.5f);
					SetExplosion(GetEnemy(j)->Pos,0.4f);
					if (GetBullet(i)->num_attack < 0)
					{

						Kirakira_bone(GetEnemy(j)->Pos, 3);//３つキラキラを生成する
						// スコアデータの更新(他のクラスの関数を呼び出すときは、ここのコードをコピペ＆改変して使ってください)
						{
							for (int i = 0; i < MAX_HEDDER; i++)
							{
								Game* object = GetSceneObject(i);

								//クラスの種類が一致したときのみ処理を行う
								if (typeid(*object) == typeid(SCORE))
								{
									//ダウンキャストを行い派生クラス固有の関数を呼び出せるようにする
									//仮想関数のみの派生クラスの場合この処理は必要ありません
									SCORE* score = dynamic_cast<SCORE*>(GetSceneObject(i));
									//スコアの加算
									score->AddScore(100);
								}
							}
						}
						
						GetEnemy(j)->Use = false;//消す
					}
					else
					{
						GetBullet(i)->num_attack--;
						Kirakira_bone(GetEnemy(j)->Pos, 3);//３つキラキラを生成する
						// スコアデータの更新(他のクラスの関数を呼び出すときは、ここのコードをコピペ＆改変して使ってください)
						{
							for (int i = 0; i < MAX_HEDDER; i++)
							{
								Game* object = GetSceneObject(i);

								//クラスの種類が一致したときのみ処理を行う
								if (typeid(*object) == typeid(SCORE))
								{
									//ダウンキャストを行い派生クラス固有の関数を呼び出せるようにする
									//仮想関数のみの派生クラスの場合この処理は必要ありません
									SCORE* score = dynamic_cast<SCORE*>(GetSceneObject(i));
									//スコアの加算
									score->AddScore(100);
								}
							}
						}
						GetEnemy(j)->Use = false;//消す

						if (GetBullet(i)->num_attack <= 0)
						{
							GetBullet(i)->use = false;
						}
					}
				}
			}
		}
	}

	//プレイヤー弾とエネミー弾の当たり判定処理
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (GetBullet(i)->use == TRUE)	//弾が使用中
		{
			for (int j = 0; j < ENEMY_MAX_BULLET; j++)
			{
				if ((GetEnemyBullet(j)->use == TRUE) && CollisionBB(GetBullet(i)->pos, GetEnemyBullet(j)->pos, GetBullet(i)->size, GetEnemyBullet(j)->size) == TRUE)
				{
					GetEnemyBullet(j)->use = FALSE;	//とりあえず弾を消去する
					if (GetBullet(i)->num_attack == 1)
					{
						GetBullet(i)->use = false;
					}
				}
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void P_BulletVSEnemy::DrawGame(void)
{
	//使用しない
}
