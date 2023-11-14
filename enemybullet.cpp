/*==============================================================================

   敵の弾の処理[enemybullet.cpp]
														 Author :田口功将
														 Date   :2022/11/22
--------------------------------------------------------------------------------

==============================================================================*/
#include <stdlib.h>
#include"sprite.h"
#include"texture.h"
#include "enemybullet.h"
#include "bullet.h"
#include "collision.h"
#include "kirakira.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ENEMY_BULLET_SIZE_W	(20.0f)	//四角形の横のサイズ
#define	ENEMY_BULLET_SIZE_H	(20.0f)	//四角形の縦のサイズ
#define ENEMY_BULLET_SPEED	(3.0f)	//弾の速さ

#define ENEMY_BULLET_BIG_SIZE_W (70.0f) //巨大な球の四角形の横のサイズ
#define ENEMY_BULLET_BIG_SIZE_H (70.0f) //巨大な球の四角形の縦のサイズ
#define ENEMY_BULLET_BIG_SPEED	(1.0f)	//弾の速さ

#define ENEMY_BULLET_ROT_SIZE_W (40.0f) //回転する弾の四角形の横のサイズ
#define ENEMY_BULLET_ROT_SIZE_H (20.0f) //回転する弾の四角形の横のサイズ
#define ENEMY_BULLET_ROT_SPEED	(3.0f) //弾の速さ

#define	ENEMY_BULLET_SIDE_SIZE_W (20.0f)	//横へ進む弾の横のサイズ
#define	ENEMY_BULLET_SIDE_SIZE_H (20.0f)	//横へ進む弾の縦のサイズ
#define ENEMY_BULLET_SIDE_SPEED	 (-3.0f)	//弾の速さ

#define ENEMY_BULLET_WAYUP_SIZE_W (20.0f)    //二股弾上の横のサイズ
#define ENEMY_BULLET_WAYUP_SIZE_H (10.0f)	  //二股弾上の縦のサイズ
#define ENEMY_BULLET_WAYUP_SPEED  (3.0f)    //弾の速さ

#define ENEMY_BULLET_WAYDOWN_SIZE_W (20.0f)    //二股弾下の横のサイズ
#define ENEMY_BULLET_WAYDOWN_SIZE_H (10.0f)    //二股弾下の縦のサイズ
#define ENEMY_BULLET_WAYDOWN_SPEED  (3.0f)    //弾の速さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************



ENEMY_BULLET	g_EnemyBullet[ENEMY_MAX_BULLET];		  // 弾オブジェクト


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT ENEMY_BULLET::InitGame(void)
{ 
	for (int i = 0; i < ENEMY_MAX_BULLET; i++){
		g_EnemyBullet[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_EnemyBullet[i].size.x = ENEMY_BULLET_SIZE_W;
		g_EnemyBullet[i].size.y = ENEMY_BULLET_SIZE_H;
		g_EnemyBullet[i].rot = 0.0f;
		g_EnemyBullet[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_EnemyBullet[i].move = D3DXVECTOR2(ENEMY_BULLET_SPEED, 0.0f);
		g_EnemyBullet[i].texNo = LoadTexture((char*)"data\\texture\\tekitamamurasaki.png");
		g_EnemyBullet[i].texAnime = 0.0f;
		g_EnemyBullet[i].use = false;
		g_EnemyBullet[i].enemybulletNo = 1;
	}

	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void ENEMY_BULLET::UninitGame(void)
{


}


//=============================================================================
// 更新処理
//=============================================================================
void ENEMY_BULLET::UpdateGame(void)
{
	for (int i = 0; i < ENEMY_MAX_BULLET; i++) {
		if (g_EnemyBullet[i].use == true) 
		{
			switch (g_EnemyBullet[i].enemybulletNo)
			{
			case 1://プレイヤーの場所へ

				g_EnemyBullet[i].pos += g_EnemyBullet[i].move;//座標の更新

				break;

			case 2:	//大きい弾

					//座標の更新
				g_EnemyBullet[i].pos += g_EnemyBullet[i].move;

				break;
			case 3: //回転弾



					//座標の更新
				g_EnemyBullet[i].pos += g_EnemyBullet[i].move;
				g_EnemyBullet[i].rot += 3.0f;

				break;

			case 4:



				//座標の更新
				g_EnemyBullet[i].pos.x -= 2.0f;

				break;

			case 5:


				g_EnemyBullet[i].pos.y += 1.0f;
				//座標の更新
				g_EnemyBullet[i].pos += g_EnemyBullet[i].move;

				break;

			case 6:


				g_EnemyBullet[i].pos.y -= 1.0f;
				//座標の更新
				g_EnemyBullet[i].pos += g_EnemyBullet[i].move;

				break;

			
			default://一致する数値がないときの処理
				break;
			}

			//EnemyBullet_dameg_reaction(i);	//当たり判定

			//アニメーションパターン更新
			g_EnemyBullet[i].texAnime += 0.1;
			if (g_EnemyBullet[i].texAnime > 8.0f)
			{
				g_EnemyBullet[i].texAnime = 0.0f;
			}

			//画面外判定
			if (g_EnemyBullet[i].pos.x < 0 )	//※画面の外に出るまで弾を残すならif (g_Bullet[i].pos.x > SCREEN_LIMIT_RIGHT)
			{
				g_EnemyBullet[i].use = false;	//画面外に出た弾を消す
			}
		}		
	}
	
}


//=============================================================================
// 描画処理
//=============================================================================
void ENEMY_BULLET::DrawGame(void)
{
	for (int i = 0; i < ENEMY_MAX_BULLET; i++) {
		
		
		//構造体が使用中なら処理
		if (g_EnemyBullet[i].use == true)
		{
			//テクスチャのセット
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_EnemyBullet[i].texNo));

			//描画
			DrawSpriteColorRotate
			(g_EnemyBullet[i].pos.x,
				g_EnemyBullet[i].pos.y,
				g_EnemyBullet[i].size.x,
				g_EnemyBullet[i].size.y,
				g_EnemyBullet[i].rot,
				g_EnemyBullet[i].color,
				g_EnemyBullet[i].texAnime,
				0.33f,
				0.33f,
				3
			);
		}
		
	}

}

void Set_Enemybullet(int EnemyBulletNo,D3DXVECTOR2 playerpos, D3DXVECTOR2 enemypos)
{
	for (int i = 0; i < ENEMY_MAX_BULLET; i++) {
		if (g_EnemyBullet[i].use == false) {
			switch (EnemyBulletNo)
			{
			case 1:	//プレイヤー追尾弾
				
				

				{
					g_EnemyBullet[i].pos = enemypos;		//発生座標
					D3DXVECTOR2 temp = playerpos - enemypos;
					D3DXVec2Normalize(&temp, &temp);
					temp *= ENEMY_BULLET_SPEED;
					g_EnemyBullet[i].move = temp;
					g_EnemyBullet[i].use = true;		//使用中
					g_EnemyBullet[i].enemybulletNo = 1;
					return;						//1つ作ったら終了
				}
				
				

			case 2:	//でかい弾
				
				g_EnemyBullet[i].enemybulletNo = 2;

				{
					g_EnemyBullet[i].size.x = ENEMY_BULLET_BIG_SIZE_W;
					g_EnemyBullet[i].size.y = ENEMY_BULLET_BIG_SIZE_H;

					g_EnemyBullet[i].pos = enemypos;		//発生座標
					D3DXVECTOR2 temp = playerpos - enemypos;
					D3DXVec2Normalize(&temp, &temp);
					temp *= ENEMY_BULLET_BIG_SPEED;
					g_EnemyBullet[i].move = temp;
					g_EnemyBullet[i].use = true;		//使用中

					return;						//1つ作ったら終了
				}
				
				
			case 3:	//回転弾
			
				g_EnemyBullet[i].enemybulletNo = 3;

				{
					g_EnemyBullet[i].pos = enemypos;		//発生座標
					D3DXVECTOR2 temp = playerpos - enemypos;
					D3DXVec2Normalize(&temp, &temp);
					temp *= ENEMY_BULLET_ROT_SPEED;
					g_EnemyBullet[i].move = temp;
					g_EnemyBullet[i].use = true;		//使用中

					return;						//1つ作ったら終了

				}
				
			case 4: //通常弾
			
				g_EnemyBullet[i].enemybulletNo = 4;

				{
					g_EnemyBullet[i].pos = enemypos;		//発生座標
					g_EnemyBullet[i].use = true;		//使用中

					return;						//1つ作ったら終了
				}

			case 5:  //2WAY弾　↑
				
				g_EnemyBullet[i].enemybulletNo = 5;

				{
					g_EnemyBullet[i].pos = enemypos;		//発生座標
					D3DXVECTOR2 temp = playerpos - enemypos;
					D3DXVec2Normalize(&temp, &temp);
					temp *= ENEMY_BULLET_WAYUP_SPEED;
					g_EnemyBullet[i].move = temp;
					g_EnemyBullet[i].use = true;		//使用中

					return;						//1つ作ったら終了
				}
			
			case 6:  //2WAY弾 下
				
				g_EnemyBullet[i].enemybulletNo = 6;

				{
					g_EnemyBullet[i].pos = enemypos;		//発生座標
					D3DXVECTOR2 temp = playerpos - enemypos;
					D3DXVec2Normalize(&temp, &temp);
					temp *= ENEMY_BULLET_WAYUP_SPEED;
					g_EnemyBullet[i].move = temp;
					g_EnemyBullet[i].use = true;		//使用中

					return;						//1つ作ったら終了
				}




			default:
				break;
			}


		}
	}

}

//==========================
//構造体の先頭アドレスを返す
//==========================
ENEMY_BULLET* GetEnemyBullet(int num)
{
	return	&g_EnemyBullet[num];
}





//==================================================
//  エネミー弾のダメージ処理
//==================================================
//void EnemyBullet_dameg_reaction(int num)
//{
//	for (int i = 0; i < MAX_BULLET; i++)//バレッド全体を見る
//	{
//			if (GetBullet(i)->use == true)//使用状態で
//			{
//				if (CollisionBB(g_EnemyBullet[num].pos, GetBullet(i)->pos,
//					g_EnemyBullet[num].size, GetBullet(i)->size) == true)//当たったら
//				{
//					GetBullet(i)->use = false,
//						g_EnemyBullet[num].use = false;//消す
//					break;
//
//
//				}
//			}
//	}
//}

