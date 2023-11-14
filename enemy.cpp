/*==============================================================================

   敵の処理[enemy.cpp]
														 Author :田口功将
														 Date   :2022/10/27
--------------------------------------------------------------------------------

==============================================================================*/

#include "enemy.h"
#include "sprite.h"
#include "texture.h"
#include "enemybullet.h"
#include "player.h"
#include "bullet.h"
#include "kirakira.h"

#include "collision.h"

//======================
//マクロ定義
//======================
// 
//======================
//プロトタイプ宣言
//======================
// 
//======================
//グローバル変数
//======================
 
static ENEMY g_Enemy[ENEMY_MAX]; //エネミーオブジェクト
ENEMY_BULLET* enemy_bullet;


//==========================
//初期化
//==========================
HRESULT ENEMY::InitGame()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//テクスチャロード
		g_Enemy[i].Texno = LoadTexture((char*)"data\\texture\\インベーダー.png");

		//構造体の初期化
		g_Enemy[i].Pos.x = 0.0f;
		g_Enemy[i].Pos.y = 0.0f;	//540から0の範囲で出す
		g_Enemy[i].Use = false;
		g_Enemy[i].countE = 0;
		g_Enemy[i].FrameWait = 0;
		g_Enemy[i].bulletrate = 0;
		g_Enemy[i].BulletType = 0;
		g_Enemy[i].size.x = ENEMY_SIZE_W;
		g_Enemy[i].size.y = ENEMY_SIZE_H;
		g_Enemy[i].enemyNo = 1;
		g_Enemy[i].move = D3DXVECTOR2(ENEMY_SPEED, 0.0f);
		g_Enemy[i].secondmove = D3DXVECTOR2(0.0f, ENEMY_SPEED);
		g_Enemy[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Enemy[i].MoveCount = 0;
		
		switch (GetScene())
		{

		case SCENE_GAME:
		
			g_Enemy[i].Texno = LoadTexture((char*)"data\\texture\\虫1.png");
			break;

		case SCENE_STAGE02:
			
			g_Enemy[i].Texno = LoadTexture((char*)"data\\texture\\クリオネ4.png");

			break;

		case SCENE_STAGE03:
			
			g_Enemy[i].Texno = LoadTexture((char*)"data\\texture\\腕2.png");

			break;

		case SCENE_STAGE04:
			
			g_Enemy[i].Texno = LoadTexture((char*)"data\\texture\\四足4.png");

			break;


		default:
			break;
		}
		

	}
	return S_OK;	//正常終了
}
//=============================
//終了処理
//=============================
void ENEMY::UninitGame()
{

}
//==============================
//更新処理
//==============================
void ENEMY::UpdateGame()
{

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		
		if (g_Enemy[i].Use == true)	//エネミーがtrueの時
		{
			switch (g_Enemy[i].enemyNo)
			{
			case 1:	//雑魚敵
				g_Enemy[i].Pos -= g_Enemy[i].move;	//左に移動
				break;

			case 2:
				g_Enemy[i].Pos -= g_Enemy[i].move;	//左に移動
				break;

			case 3:

				g_Enemy[i].Pos -= g_Enemy[i].move;	//下から上
				break;

			case 4 :

				g_Enemy[i].Pos -= g_Enemy[i].move;	//上から下
				break;
			case 5:
				g_Enemy[i].MoveCount++;
				g_Enemy[i].Pos -= g_Enemy[i].move;
				if (g_Enemy[i].MoveCount <= 60)
				{
					g_Enemy[i].Pos += g_Enemy[i].secondmove;
				}
				else if (g_Enemy[i].MoveCount > 60 && g_Enemy[i].MoveCount < 180)
				{
					g_Enemy[i].Pos -= g_Enemy[i].secondmove;
				}
				else if (g_Enemy[i].MoveCount > 180 && g_Enemy[i].MoveCount < 240)
				{
					g_Enemy[i].Pos += g_Enemy[i].secondmove;

				}
				else if (g_Enemy[i].MoveCount > 240 && g_Enemy[i].MoveCount < 300)
				{
					g_Enemy[i].Pos -= g_Enemy[i].secondmove;
					g_Enemy[i].MoveCount = 0;
				}

			default:
				break;
			}
			Enemy_dameg_reaction(i);//エネミーがバレッドに当たってないか見てから









			
			//画面外チェック
			if (g_Enemy[i].Pos.x < -50)	//左画面外-50になると
			{
				//敵を消滅
				g_Enemy[i].Use = false;
			}                               



			
				g_Enemy[i].bulletrate += 1.0f;
				if(g_Enemy[i].Pos.x>200){
					if (((int)g_Enemy[i].bulletrate % 100) == 99)
					{
						Set_Enemybullet(g_Enemy[i].BulletType, GetPlayer()->Position, g_Enemy[i].Pos);
					}
				}
				                                                     
		}

		



	}
}
//================================
//描画処理
//================================
void ENEMY::DrawGame()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].Use == true)	//エネミーがtrueの時のみ
		{
			
				//テクスチャのセット
				GetDeviceContext()->PSSetShaderResources(0, 1,
					GetTexture(g_Enemy[i].Texno));

				//スプライトの描画
				DrawSpriteColorRotate
				(
					g_Enemy[i].Pos.x,
					g_Enemy[i].Pos.y,
					g_Enemy[i].size.x,
					g_Enemy[i].size.y,
					g_Enemy[i].Rot,
					g_Enemy[i].color,	//とりあえずの色
					0,	//パターン番号
					1.0f,	//パターンの横サイズ
					1.0f,	//パターンの縦サイズ
					1		//パターンの横の数
				);
			
		}
	}
}
//================================
//構造体の先頭のポインタを返す
//================================
ENEMY* GetEnemy(int num)
{
	return &g_Enemy[num];
}

//==========================================
//エネミー呼び出し＆選択
// エネミーの種類,エネミー弾の種類,座標X、座標Y
//
//==========================================
void SetEnemy(int EnemyNo,int EnemyBulletNo,float EnemyX,float EnemyY)
{

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].Use == false) {
			switch (EnemyNo)
			{
			case 1:
			{
				g_Enemy[i].Pos = D3DXVECTOR2(EnemyX, EnemyY);
				g_Enemy[i].move = D3DXVECTOR2(ENEMY_SPEED,0.0f);
				g_Enemy[i].Use = true;
				break;
			}
			case 2:
				
			{
				g_Enemy[i].Pos = D3DXVECTOR2(EnemyX, EnemyY);
				g_Enemy[i].size.x = ENEMY_BIG_SIZE_W;
				g_Enemy[i].size.y = ENEM_BIG_SIZE_H;
				g_Enemy[i].move = D3DXVECTOR2(ENEMY_BIG_SPEED, 0.0f);
				g_Enemy[i].Use = true;
				break;
				
			}		

			case 3:
			{
				g_Enemy[i].Pos = D3DXVECTOR2(EnemyX, EnemyY);
				g_Enemy[i].move = D3DXVECTOR2(ENEMY_SPEED, 1.0f);
				g_Enemy[i].Use = true;
				break;


			}

			case 4:
			{
				g_Enemy[i].Pos = D3DXVECTOR2(EnemyX, EnemyY);
				g_Enemy[i].move = D3DXVECTOR2(ENEMY_SPEED, -1.0f);
				g_Enemy[i].Use = true;
				break;


			}
			case 5:
				g_Enemy[i].Pos = D3DXVECTOR2(EnemyX, EnemyY);
				g_Enemy[i].move = D3DXVECTOR2(ENEMY_SPEED, 0.0f);
				g_Enemy[i].secondmove = D3DXVECTOR2(0.0f,ENEMY_SPEED);
				g_Enemy[i].Use = true;
				break;

			default:
				break;
			}

			g_Enemy[i].enemyNo = EnemyNo;
			g_Enemy[i].BulletType = EnemyBulletNo;
			return;
		}
	}

}


//==================================================
//エネミーのダメージreaction
//==================================================

void Enemy_dameg_reaction(int num)
{
	for (int i = 0; i < MAX_BULLET; i++)//バレッド全体を見る
	{

		if (GetBullet(i)->use == true)//使用状態で
		{
			if (CollisionBB(GetBullet(i)->pos, g_Enemy[num].Pos,
				GetBullet(i)->size, g_Enemy[num].size) == true)//当たったら
			{
				
				//	Kirakira_bone(g_Enemy[num].Pos, 3);//３つキラキラを生成する


				//	GetBullet(i)->use = false,
				//		g_Enemy[num].Use = false;//消す
					break;
				
				
			}
		}

		
	}
}

