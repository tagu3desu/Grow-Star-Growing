
#include "kirakira.h"
#include "enemy.h"

#include "player.h"
#include "collision.h"
#include "texture.h"



static KIRAKIRA g_Kirakira[KIRAKIRA_MAX];

//=====================================================
//テクスチャのロード



//======================
//初期化
//======================
HRESULT KIRAKIRA::InitGame()
{

	//キラキラのテクスチャ
	

	for (int i = 0; i < KIRAKIRA_MAX; i++)
	{
		g_Kirakira[i].Texno = LoadTexture((char*)"data\\texture\\kirakira.png");


		//構造体の初期化
		AgeinInitKirakira(i);

	}


	return	S_OK;	//正常終了

}

//======================
//終了処理
//======================
void	KIRAKIRA::UninitGame()
{
}

//======================
//更新処理
//======================
void	KIRAKIRA::UpdateGame()
{
	//低めの確率でキラキラは生成する

	if (rand() % 100 == 1) {//1f　に　1％の確率で生成

		for (int i = 0; i < KIRAKIRA_MAX; i++) //すべての中から
		{
			if (g_Kirakira[i].Use == false)	//未使用の構造体を見つける
			{
				AgeinInitKirakira(i);

				g_Kirakira[i].Use = true;

				break;
			
			}
			
		}

	
	}


	//==========================================
	//画面外処理

	for (int i = 0; i < KIRAKIRA_MAX; i++) //すべての中から
	{
		player_get_kirakira(i);

		if (g_Kirakira[i].Use == true)//使用中で
		{
			if (g_Kirakira[i].Pos.x < SCREEN_LIMIT_LEFT)//左端なら
			{
				g_Kirakira[i].Use = false;//なくす
			}

			g_Kirakira[i].Pos.x -= 1;//違うなら左側へ

		}
	}



	
}

//======================
//描画処理
//======================
void	KIRAKIRA::DrawGame()
{
	for (int i = 0; i < KIRAKIRA_MAX; i++)
	{





		//キラキラがちゅるーなら表示する
		if (g_Kirakira[i].Use == true)
		{

				//テクスチャのセット
				GetDeviceContext()->PSSetShaderResources(0, 1,
					GetTexture(g_Kirakira[i].Texno));


				DrawSpriteColorRotate
				(
					g_Kirakira[i].Pos.x,
					g_Kirakira[i].Pos.y,
					g_Kirakira[i].Size.x,
					g_Kirakira[i].Size.y,
					g_Kirakira[i].Rot,
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),//とりあえずの色
					0,		//パターン番号
					1.0f,	//パターンの横サイズ
					1.0f,	//パターンの縦サイズ
					1		//パターン横の数
				);
				//SetBlendState(BLEND_MODE_ALPHABLEND);

			
		}
		
	}
}

//==============================
//構造体の先頭のポインタを返す
//==============================
KIRAKIRA* GetKirakira()
{

	return	&g_Kirakira[0];
}



//=================================
//キラキラ初期化
//=================================
void AgeinInitKirakira(int num)
{
	g_Kirakira[num].Pos.x = SCREEN_LIMIT_RIGHT ;
	g_Kirakira[num].Pos.y = rand() % (SCREEN_LIMIT_DOWN - 1) + 0;//右端からランダムで生成
	g_Kirakira[num].Size.x = KIRAKIRA_SIZE_W;
	g_Kirakira[num].Size.y = KIRAKIRA_SIZE_H;
	g_Kirakira[num].Use = false;
	g_Kirakira[num].countK = 0;

	g_Kirakira[num].collision_size.x = KIRAKIRA_SIZE_W  + 200;
	g_Kirakira[num].collision_size.y = KIRAKIRA_SIZE_H  + 200;


}


//================================
//エネミーの周辺にキラキラを生成する関数
//================================
void Kirakira_bone(D3DXVECTOR2 Epos , int bone_ster)//エネミーのポジションを取得する, 生成する星の数
{
	for (int i = 0; i < bone_ster; i++)
	{
		for (int num = 0; num < KIRAKIRA_MAX; num++) //すべての中から
		{
			if (g_Kirakira[num].Use == false) {	//未使用の構造体を見つける

				g_Kirakira[num].Pos.x = (Epos.x - 100) + rand() % 200;//エネミーの座標Xから+-100
				g_Kirakira[num].Pos.y = (Epos.y - 100) + rand() % 200;//エネミーの座標Yから+-100
				g_Kirakira[num].Size.x = KIRAKIRA_SIZE_W;
				g_Kirakira[num].Size.y = KIRAKIRA_SIZE_H;
				g_Kirakira[num].Use = true;
				g_Kirakira[num].countK = 0;

				g_Kirakira[num].collision_size.x = KIRAKIRA_SIZE_W ;
				g_Kirakira[num].collision_size.y = KIRAKIRA_SIZE_H ;


				break;
			}
			
		}
	}


}

//============================================
//プレイヤーがキラキラと接触したときの処理

void player_get_kirakira(int num)
{
	if (g_Kirakira[num].Use == true)
	{
		if (CollisionBB(GetPlayer()->Position, g_Kirakira[num].Pos,
			GetPlayer()->size, g_Kirakira[num].collision_size) == true)
		{

			GetPlayer()->energy += 1;

			g_Kirakira[num].Use = false;

		}
	}
}