/*==============================================================================

   弾の処理 [bullet.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include	<stdlib.h>
#include	"bullet.h"

#include	"sprite.h"
#include	"texture.h"
#include	"00_soundmain.h"
#include	"01_Scene.h"
#include	"player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//#define	BULLET_SIZE_W	(50.0f)	//四角形の横のサイズ
//#define	BULLET_SIZE_H	(50.0f)	//四角形の縦のサイズ
//#define BULLET_SPEED	(4.0f)	//弾の速さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

BULLET	g_Bullet[MAX_BULLET];	// 弾オブジェクト


/*弾の種類ごとの設定値*/
//弾の種類の最大値
static const int	BULET_TYPE_MAX = 8;
                                                                //0,     1,     2,     3,     4,     5,     6,		7
//四角形の横のサイズ
static const float	BULLET_SIZE_W[BULET_TYPE_MAX]	=		{ 50.0f, 50.0f, 50.0f, 50.0f, 20.0f, 50.0f, 150.0f, 50.0f};
//四角形の縦のサイズ
static const float	BULLET_SIZE_H[BULET_TYPE_MAX]	=		{ 50.0f, 50.0f, 50.0f, 50.0f, 20.0f, 50.0f, 150.0f, 50.0f};
//弾のX軸方向の速さ
static const float	BULLET_SPEED_X[BULET_TYPE_MAX]	=		{  5.0f,  5.0f,  5.0f,  5.0f,  2.0f,  8.0f,  10.0f,  6.0f};
//弾のY軸方向の速さ
static const float	BULLET_SPEED_Y[BULET_TYPE_MAX]	=		{  0.0f,  0.7f,  0.0f,  0.0f,  0.0f,  0.0f ,  0.0f,  0.0f};
//弾のダメージ量
static const int	BULLET_DAMAGE[BULET_TYPE_MAX]	=		{     2,     2,     1,     1,     2,     2,		10,		1};
//弾発射時のキラキラ消費量
static const int	BULLET_DEMAND_KIRAKIRA[BULET_TYPE_MAX] = {    2,     5,     5,     5,     2,     2,		 1,		1};
//弾発射スキル使用回数の最大数(-1の場合は無限)
static const int	BULLET_USAGE_MAX[BULET_TYPE_MAX]	=	{    -1,    10,     8,     5,    3,     10 ,	 1,   -1};
//弾発射スキル使用回数の最大数(-1の場合は無限)
static const int	BULLET_COOL_TIME_MAX[BULET_TYPE_MAX] =	{   -1, 5 * 60, 5 * 60, 10 * 60,10 * 60,5 * 60,10 * 60,-1};

//回転弾の半径
static const float	BULLET_TURN_RADIUS = 150.0f;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT  BULLET::InitGame(void)
{
	//構造体すべて処理
	for (int i = 0; i < MAX_BULLET; i++)
	{
		//テクスチャロード
		g_Bullet[i].texNo = LoadTexture((char*)"data\\texture\\01_kirakirabullet.png");//テクスチャファイルパス

		g_Bullet[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_Bullet[i].size.x = BULLET_SIZE_W[0];
		g_Bullet[i].size.y = BULLET_SIZE_H[0];
		g_Bullet[i].rot = 0.0f;
		g_Bullet[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED_X[0], BULLET_SPEED_Y[0]);
		g_Bullet[i].texAnime = 0.0f;
		g_Bullet[i].use = false;
		g_Bullet[i].bulletNo = 0;
		g_Bullet[i].damage = 0;
		g_Bullet[i].num_attack = 0;
		g_Bullet[i].revolution_angle = 0.0f;
		g_Bullet[i].circle_origin = D3DXVECTOR2(0.0f, 0.0f);
		g_Bullet[i].time_count = 0;
		g_Bullet[i].buy = false;
	}

	

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void BULLET::UninitGame(void)
{


}

//=============================================================================
// 更新処理
//=============================================================================
void BULLET::UpdateGame(void)
{
	//構造体を全て処理
	for (int i = 0; i < MAX_BULLET; i++)
	{
		//構造体が使用中なら処理
		if (g_Bullet[i].use == true)
		{
			switch (g_Bullet[i].bulletNo)
			{
			case 0:		//通常キラキラ弾
				//座標の更新
				g_Bullet[i].pos += g_Bullet[i].move;
				break;

			case 1:		//三又キラキラ弾
				//座標の更新
				g_Bullet[i].pos += g_Bullet[i].move;
				break;

			case 2:		//貫通弾
				//座標の更新
				g_Bullet[i].pos += g_Bullet[i].move;
				break;

			case 3:		//回転弾
				//座標の更新
				g_Bullet[i].revolution_angle += 0.07f;
				g_Bullet[i].pos.x = -cos(g_Bullet[i].revolution_angle) * BULLET_TURN_RADIUS + g_Bullet[i].circle_origin.x;
				g_Bullet[i].pos.y =  sin(g_Bullet[i].revolution_angle) * BULLET_TURN_RADIUS + g_Bullet[i].circle_origin.y;
				if (g_Bullet[i].revolution_angle > 6.28318531)
				{
					g_Bullet[i].revolution_angle = 0.0f;
					g_Bullet[i].use = false;
				}

				break;

			case 4:		//炸裂弾
				//座標の更新
				g_Bullet[i].pos += g_Bullet[i].move;
				if (g_Bullet[i].time_count >= 90)
				{
					for (int a = 0; a < 5; a++)
					{
						SetBullet(7, D3DXVECTOR2(g_Bullet[i].pos.x, (g_Bullet[i].pos.y - 100.0f + a * 50.0f)));
					}
					g_Bullet[i].use = false;
				}
				break;

			case 5:		//次元弾
				//座標の更新
				if (g_Bullet[i].time_count >= 60)
				{
					g_Bullet[i].pos += g_Bullet[i].move;
				}
				break;

			case 6:		//巨大玉
				//座標更新
				g_Bullet[i].pos += g_Bullet[i].move;
				break;

			case 7:		//炸裂した後
				//座標更新
				g_Bullet[i].pos += g_Bullet[i].move;
				break;

			default://一致する数値がないときの処理
				break;
			}

			//アニメーションパターン更新
			g_Bullet[i].texAnime += 0.1;
			if (g_Bullet[i].texAnime > 8.0f)
			{
				g_Bullet[i].texAnime = 0.0f;
			}

			g_Bullet[i].time_count++;		//時間の追加

			//画面外チェック
			if (g_Bullet[i].pos.x > (SCREEN_LIMIT_RIGHT - g_Bullet[i].size.x / 2))	//※画面の外に出るまで弾を残すならif (g_Bullet[i].pos.x > SCREEN_LIMIT_RIGHT)
			{
				g_Bullet[i].use = false;	//画面外に出た弾を消す
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void BULLET::DrawGame(void)
{
	//構造体を全て調べる
	for (int i = 0; i < MAX_BULLET; i++)
	{
		//構造体が使用中なら処理
		if (g_Bullet[i].use == true)
		{
			//テクスチャのセット
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Bullet[i].texNo));

			//描画
			DrawSpriteColorRotate
			(g_Bullet[i].pos.x, g_Bullet[i].pos.y,
				g_Bullet[i].size.x, g_Bullet[i].size.y,
				g_Bullet[i].rot, 
				g_Bullet[i].color,
				g_Bullet[i].texAnime, 
				0.33f, 
				0.33f,
				3);
		}
	}
}


//==========================
//構造体の先頭アドレスを返す
//==========================
BULLET		*GetBullet(int num)
{
	return	&g_Bullet[num];
}

//==================================
//弾発射時の消費キラキラ数を返す
//==================================
int			GetBulletDemand(int index)
{
	return BULLET_DEMAND_KIRAKIRA[index];
}

//==================================
//弾発射スキル使用回数の最大数を返す
//==================================
int			GetBulletUsageMax(int index)
{
	return BULLET_USAGE_MAX[index];
}

//==================================
//弾発射クールタイムの最大数を返す
//==================================
int			GetBulletCoolTimeMax(int index)
{
	return BULLET_COOL_TIME_MAX[index];
}

//==========================
//弾の発生
//in	弾のID番号, 発生座標
//==========================
void	SetBullet(int BulletNo, D3DXVECTOR2 pos)
{
	int count = 0;	//複数発射する場合のカウント変数

	//構造体を全て調べる
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (g_Bullet[i].use == false )	//未使用の構造体を見つける&プレイヤーの所持キラキラ量と比較
		{
			//弾の情報をセット
			g_Bullet[i].pos = pos;																//発生座標
			g_Bullet[i].size = D3DXVECTOR2(BULLET_SIZE_W[BulletNo], BULLET_SIZE_H[BulletNo]);	//弾のサイズ
			g_Bullet[i].move = D3DXVECTOR2(BULLET_SPEED_X[BulletNo], BULLET_SPEED_Y[BulletNo]);	//弾のスピード
			g_Bullet[i].texAnime = 0.0f;
			g_Bullet[i].use = true;																//使用中
			g_Bullet[i].bulletNo = BulletNo;													//弾のID番号
			g_Bullet[i].damage = BULLET_DAMAGE[BulletNo];										//弾のダメージ量
			g_Bullet[i].num_attack = 1;															//通常は1回敵に当たるとすぐ消滅
			g_Bullet[i].time_count = 0;															//生成されてから経った時間のカウント用

			if (g_Bullet[i].bulletNo != 7)	//7で音出そうとしたら止まる
			{
				PlayEffect(Ebullet, 0.5f);
			}

			//弾の種類ごとの特殊処理(諸事情によりキラキラ消費はここで行う)
			switch (BulletNo)
			{
			case 0:
									
				return;						//1つ作ったら終了
				break;
			case 1:
				count++;
				switch (count)
				{
				case 1:
					g_Bullet[i].move.y *= -1.0f;
					break;
				case 2:
					g_Bullet[i].move.y = 0.0f;
					break;
				case 3:
										
					return;					//3つ作ったら終了
					break;
				default:
					break;
				}
				break;
			case 2:
				g_Bullet[i].pos.x += 50.0f;
				g_Bullet[i].num_attack = 5;	//最大5回まで
				
				return;						//1つ作ったら終了
				break;
			case 3:
				g_Bullet[i].circle_origin = pos;
				g_Bullet[i].circle_origin.x += (50.0f + BULLET_TURN_RADIUS);
				g_Bullet[i].num_attack = -1;
				g_Bullet[i].pos.x += 50.0f;
				g_Bullet[i].revolution_angle = 0.0f;
				return;
				break;
			case 4:
				g_Bullet[i].pos.x += 50.0f;
				return;
				break;
			case 5:
				g_Bullet[i].pos.x += 50.0f;
				return;
				break;
			case 6:
				g_Bullet[i].pos.x = pos.x + 100.0f;
				g_Bullet[i].num_attack = -1;	//最大5回まで
				return;
				break;
			case 7:
				return;
				break;

			default:
				return;
				break;
			}
		}
	}
}
