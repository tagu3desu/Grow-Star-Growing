/*==============================================================================

   敵の処理[boss_parts.cpp]
														 Author :髙橋建次
														 Date   :2022/12/22
--------------------------------------------------------------------------------

==============================================================================*/

#include "boss_parts.h"
#include "sprite.h"
#include "texture.h"
#include "enemybullet.h"
#include "player.h"
#include "bullet.h"

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
 
static BOSS_PARTS g_BossParts[BOSS_PARTS_MAX]; //ボス部位オブジェクト


//==========================
//初期化
//==========================
HRESULT BOSS_PARTS::InitGame()
{
	for (int i = 0; i < BOSS_PARTS_MAX; i++)
	{
		//テクスチャロード
		g_BossParts[i].Texno = LoadTexture((char*)"data\\texture\\target_circle.png");

		//構造体の初期化
		g_BossParts[i].Pos.x = 0.0f;
		g_BossParts[i].Pos.y = 0.0f;
		g_BossParts[i].Use = false;
		g_BossParts[i].countE = 0;
		g_BossParts[i].FrameWait = 0;
		g_BossParts[i].bulletrate = 0;
		g_BossParts[i].BulletType = 0;
		g_BossParts[i].size.x = BOSS_PARTS_SIZE_W;
		g_BossParts[i].size.y = BOSS_PARTS_SIZE_H;
		g_BossParts[i].BossPartsNo = 1;
		g_BossParts[i].move = D3DXVECTOR2(0.0f, 0.0f);
		g_BossParts[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_BossParts[i].Rot = 0;
		g_BossParts[i].HP = 0;
		g_BossParts[i].BossPos = D3DXVECTOR2(0.0f, 0.0f);
		g_BossParts[i].tacklehit = false;
		g_BossParts[i].tacklecount = 0;
		
		

	}
	return S_OK;	//正常終了
}
//=============================
//終了処理
//=============================
void BOSS_PARTS::UninitGame()
{

}
//==============================
//更新処理
//==============================
void BOSS_PARTS::UpdateGame()
{
	for (int i = 0; i < BOSS_PARTS_MAX; i++)
	{
		
		if (g_BossParts[i].Use == true)	//ボス部位がtrueの時
		{
			BossParts_damege_reaction(i);//ボス部位がバレッドに当たってないか見てから
			
			if (g_BossParts[i].tacklehit == true)
			{
				g_BossParts[i].tacklecount++;
			}
			if (g_BossParts[i].tacklecount >= 60)
			{
				g_BossParts[i].tacklehit = false;
				g_BossParts[i].tacklecount=0;
			}

			g_BossParts[i].Rot += 2;

			//ボス部位の種類ごとに発射する弾を変更
			switch (g_BossParts[i].BossPartsNo)
			{
			case 1:
				g_BossParts[i].bulletrate += 1.0f;
				if (((int)g_BossParts[i].bulletrate % 100) == 99)
				{
					Set_Enemybullet(g_BossParts[i].BulletType, GetPlayer()->Position, (g_BossParts[i].Pos + g_BossParts[i].BossPos));
				}
				break;
			default:
				g_BossParts[i].bulletrate += 1.0f;
				if (((int)g_BossParts[i].bulletrate % 100) == 99)
				{
					Set_Enemybullet(g_BossParts[i].BulletType, GetPlayer()->Position, (g_BossParts[i].Pos + g_BossParts[i].BossPos));
				}
				break;
			}
		}
	}
}
//================================
//描画処理
//================================
void BOSS_PARTS::DrawGame()
{
	for (int i = 0; i < BOSS_PARTS_MAX; i++)
	{


		if (g_BossParts[i].Use == true)	//ボス部位がtrueの時のみ
		{
				//テクスチャのセット
				GetDeviceContext()->PSSetShaderResources(0, 1,
					GetTexture(g_BossParts[i].Texno));

				//スプライトの描画
				DrawSpriteColorRotate
				(
					g_BossParts[i].Pos.x + g_BossParts[i].BossPos.x,
					g_BossParts[i].Pos.y + g_BossParts[i].BossPos.y,
					g_BossParts[i].size.x,
					g_BossParts[i].size.y,
					g_BossParts[i].Rot,
					g_BossParts[i].color,	//とりあえずの色
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
BOSS_PARTS* GetBossParts(int num)
{
	return &g_BossParts[num];
}

//==========================================
//ボス部位の呼び出し＆選択
// 座標X,座標Y,HP,ボスの中心座標
//
//==========================================
int SetBossParts(float posx, float posy, int HP, D3DXVECTOR2 BOSSposs)
{
	for (int i = 0; i < BOSS_PARTS_MAX; i++)
	{
		if (g_BossParts[i].Use == false) {

			g_BossParts[i].Pos = D3DXVECTOR2(posx, posy);
			g_BossParts[i].HP = HP;
			g_BossParts[i].BossPos = BOSSposs;
			g_BossParts[i].BulletType = 1;
			g_BossParts[i].Use = true;
			return i;
		}
	}
}


//==============================================
//ボスのパーツの残存確認
//==============================================
bool Get_BossPartslivis()
{
	for (int i = 0; i < BOSS_PARTS_MAX; i++)
	{
		if (g_BossParts[i].Use == true) {//生きているパーツが一つでもあれば

			return true;//いると返す
		}
	}

	return false;
}


//==================================================
//ボス部位のダメージreaction
//==================================================

void BossParts_damege_reaction(int num)
{
	
	if (GetPlayer()->SizeUp == true && g_BossParts[num].tacklehit==false)
	{
		if (CollisionBB(GetPlayer()->Position, (g_BossParts[num].Pos + g_BossParts[num].BossPos),
			GetPlayer()->size, g_BossParts[num].size) == true)//当たったら
		{
			//ダメージ処理
			g_BossParts[num].HP -= GetPlayer()->TackleDamege;
			g_BossParts[num].tacklehit = true;
			if (g_BossParts[num].HP <= 0)
			{
				g_BossParts[num].HP = 0;
				g_BossParts[num].Use = false;//消す
			}

		}
	}
	else
	{
		for (int i = 0; i < MAX_BULLET; i++)//バレッド全体を見る
		{
			if (GetBullet(i)->use == true)//使用状態で
			{
				if (CollisionBB(GetBullet(i)->pos, (g_BossParts[num].Pos + g_BossParts[num].BossPos),
					GetBullet(i)->size, g_BossParts[num].size) == true)//当たったら
				{
					//ダメージ処理
					g_BossParts[num].HP -= GetBullet(i)->damage;
					if (g_BossParts[num].HP <= 0)
					{
						g_BossParts[num].HP = 0;
						g_BossParts[num].Use = false;//消す
					}
					GetBullet(i)->use = false;
					break;
				}
			}
		}
	}
	
	
}


