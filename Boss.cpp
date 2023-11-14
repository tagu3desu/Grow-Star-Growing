/*==============================================================================

   ボスの処理[Boss.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include"Boss.h"
#include"01_BOSSscene.h"
#include"sprite.h"
#include"texture.h"
#include"boss_parts.h"

#include "enemybullet.h"
#include "bullet.h" //後で変更必須
#include "collision.h"
#include "player.h"
#include "score.h"

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
static BOSS_01 g_Boss01;	//ボス帯ジェクト
int  SceneNo = 0;


//==========================
//初期化
//==========================
HRESULT BOSS_01::InitGame()
{
	{
		//テクスチャのロード
		g_Boss01.TexNo = LoadTexture((char*)"data\\texture\\Boss1.png");
		g_Boss01.BreakTexno = LoadTexture((char*)"data\\texture\\Boss1B.png");

		//構造体の初期化
		g_Boss01.Pos.x = SCREEN_WIDTH;
		g_Boss01.Pos.y = SCREEN_HEIGHT;
		g_Boss01.Use = false;
		g_Boss01.HP = 100;
		g_Boss01.size.x = BOSS_SIZE_W;
		g_Boss01.size.y = BOSS_SIZE_H;
		g_Boss01.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Boss01.BossNo = 0;
		g_Boss01.Count;
		g_Boss01.tacklehit = false;
		g_Boss01.tacklecount = 0;
		for (int i = 0; i < PARTS_MAX; i++)
		{
			g_Boss01.PartsIndex[i] = -1;
		}

		//==============================
	//どのボスなのかを判別
		switch (GetScene())
		{
		case SCENE_BOSS01:

			SceneNo = 1;

			break;

		case SCENE_BOSS02:

			SceneNo = 2;
			break;

		case SCENE_BOSS03:

			SceneNo = 3;
			break;

		case SCENE_BOSS04:

			SceneNo = 4;
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
void BOSS_01::UninitGame()
{

}
//==============================
//更新処理
//==============================
void BOSS_01::UpdateGame()
{

	Boss_damege_reaction();


	g_Boss01.FrameWait++;
	if (g_Boss01.Use == true) {
		if (g_Boss01.FrameWait <= 60)
		{
			g_Boss01.Pos += g_Boss01.move;
		}
		else if (g_Boss01.FrameWait > 60 && g_Boss01.FrameWait < 180)
		{
			g_Boss01.Pos -= g_Boss01.move;
		}
		else if (g_Boss01.FrameWait > 180 && g_Boss01.FrameWait < 240)
		{
			g_Boss01.Pos += g_Boss01.move;
			
		}
		else if (g_Boss01.FrameWait > 240 && g_Boss01.FrameWait < 300)
		{
			g_Boss01.Pos -= g_Boss01.move;
			g_Boss01.FrameWait = 0;
		}
	}

	if (g_Boss01.tacklehit == true)
	{
		g_Boss01.tacklecount++;
	}
	if (g_Boss01.tacklecount >= 60)
	{
		g_Boss01.tacklehit = false;
		g_Boss01.tacklecount = 0;
	}

	if (g_Boss01.Use == true) {

		g_Boss01.Count++;
		if (g_Boss01.Count > 20)
		{
			Set_Enemybullet(4, GetPlayer()->Position, g_Boss01.Pos);
			Set_Enemybullet(5, GetPlayer()->Position, g_Boss01.Pos);
			Set_Enemybullet(6, GetPlayer()->Position, g_Boss01.Pos);
			g_Boss01.Count = 0;
		}
	}
	


	//ボス部位の中心座標を更新
	for (int i = 0; i < PARTS_MAX; i++)
	{
		if (g_Boss01.PartsIndex[i] > -1)
		{
			if (GetBossParts(g_Boss01.PartsIndex[i])->Use == true)
			{
				GetBossParts(g_Boss01.PartsIndex[i])->BossPos = g_Boss01.Pos;
			}
		}
	}
}
//================================
//描画処理
//================================
void BOSS_01::DrawGame()
{
	if (g_Boss01.Use == true)//ボスがtrueの時のみ
	{

		if (Get_BossPartslivis() == true) {
			//テクスチャのセット
			GetDeviceContext()->PSSetShaderResources(0, 1,
				GetTexture(g_Boss01.TexNo));
		}
		else if (Get_BossPartslivis() == false)
		{
			//テクスチャのセット
			GetDeviceContext()->PSSetShaderResources(0, 1,
				GetTexture(g_Boss01.BreakTexno));
		}


		//スプライトの描画
		DrawSpriteColorRotate
		(
			g_Boss01.Pos.x,
			g_Boss01.Pos.y,
			g_Boss01.size.x,
			g_Boss01.size.y,
			g_Boss01.Rot,
			g_Boss01.color,	//とりあえずの色
			0,	//パターン番号
			1.0f,	//パターンの横サイズ
			1.0f,	//パターンの縦サイズ
			1		//パターンの横の数
		);

		//HPゲージの表示
		//テクスチャのセット(赤ゲージ)
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(LoadTexture((char*)"data\\texture\\kk_bossHP.png")));
		//スプライト描画
		DrawSpriteColorRotate
		(
			920.0f,
			250.0f,
			30.0f,
			350.0f,
			0.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			1.0f,
			1.0f,
			1.0f,
			1
		);

		//テクスチャのセット(緑ゲージ)
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(LoadTexture((char*)"data\\texture\\kk_bosshpnokori.png")));
		//スプライト描画
		DrawSpriteColorRotate
		(
			920.0f,
			250.0f + (100.0f - g_Boss01.HP) *1.5f,
			30.0f,
			350.0f * g_Boss01.HP / 100,
			0.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			1.0f,
			1.0f,
			1.0f,
			1
		);

	}


}
//================================
//構造体の先頭のポインタを返す
//================================
BOSS_01  *GetBoss_01()
{
	return  &g_Boss01;
}
//==========================================
//ボス呼び出し＆選択
// ボスの種類,座標X、座標Y
//
//==========================================
void SetBoss_01(int Boss_01Num,float BossX, float BossY)
{
	if (g_Boss01.Use == false) {
		switch (Boss_01Num)
		{
		case 1:	//虫
			g_Boss01.Pos = D3DXVECTOR2(BossX, BossY);
			g_Boss01.move = D3DXVECTOR2(0.0f, BOSS_SPEED);
			//ボス部位0番目をセット		中心から100.0f左・100.0f上の位置、HP50 
			g_Boss01.PartsIndex[0] = SetBossParts(-100.0f, -50.0f, 20, g_Boss01.Pos);
			g_Boss01.PartsIndex[1] = SetBossParts(-75.0f, +100.0f, 20, g_Boss01.Pos);
			g_Boss01.Use = true;

			g_Boss01.TexNo = LoadTexture((char*)"data\\texture\\Boss1.png");
			g_Boss01.BreakTexno = LoadTexture((char*)"data\\texture\\Boss1B.png");

			break;

		case 2:	//クリオネ
			g_Boss01.Pos = D3DXVECTOR2(BossX, BossY);
			g_Boss01.move = D3DXVECTOR2(0.0f, BOSS_SPEED);
			//ボス部位0番目をセット		中心から100.0f左・100.0f上の位置、HP50 
			g_Boss01.PartsIndex[0] = SetBossParts(-95.0f, -95.0f, 50, g_Boss01.Pos);
			g_Boss01.PartsIndex[1] = SetBossParts(+85.0f, -100.0f, 50, g_Boss01.Pos);
			g_Boss01.PartsIndex[2] = SetBossParts(-10.0f, 55.0f, 50, g_Boss01.Pos);
			g_Boss01.Use = true;
			g_Boss01.TexNo = LoadTexture((char*)"data\\texture\\Boss2.png");
			g_Boss01.BreakTexno = LoadTexture((char*)"data\\texture\\Boss2B.png");
			break;

		case 3:	//腕だけ
			g_Boss01.Pos = D3DXVECTOR2(BossX, BossY);
			g_Boss01.move = D3DXVECTOR2(0.0f, BOSS_SPEED);
			//ボス部位0番目をセット		中心から100.0f左・100.0f上の位置、HP50 
			g_Boss01.PartsIndex[0] = SetBossParts(+100.0f, 50.0f, 50, g_Boss01.Pos);
			g_Boss01.PartsIndex[1] = SetBossParts(-100.0f, 0.0f, 50, g_Boss01.Pos);
			g_Boss01.PartsIndex[2] = SetBossParts(-10.0f, -60.0f, 50, g_Boss01.Pos);
			g_Boss01.Use = true;
			g_Boss01.TexNo = LoadTexture((char*)"data\\texture\\Boss3.png");
			g_Boss01.BreakTexno = LoadTexture((char*)"data\\texture\\Boss3B.png");
			break;

		case 4:	//目玉
			g_Boss01.Pos = D3DXVECTOR2(BossX, BossY);
			g_Boss01.move = D3DXVECTOR2(0.0f, BOSS_SPEED);
			//ボス部位0番目をセット		中心から100.0f左・100.0f上の位置、HP50 
			g_Boss01.PartsIndex[0] = SetBossParts(-20.0f, -30.0f, 300, g_Boss01.Pos);
			g_Boss01.Use = true;
			g_Boss01.TexNo = LoadTexture((char*)"data\\texture\\Boss4.png");
			g_Boss01.BreakTexno = LoadTexture((char*)"data\\texture\\Boss4B.png");
			break;

		default:
			break;
		}
		g_Boss01.BossNo = Boss_01Num;
		return;
	}
}

//=============================================================
//ボスのダメージreaction
//============================================================
void Boss_damege_reaction()
{
	
	if (g_Boss01.Use == true) {
		if (Get_BossPartslivis() == false) //ボスのパーツが生きていないなら
		{
			if (GetPlayer()->SizeUp == true && g_Boss01.tacklehit==false)
			{
				if (CollisionBB(GetPlayer()->Position, g_Boss01.Pos,
					GetPlayer()->size, g_Boss01.size) == true)//当たったら
				{
					//ダメージ処理
					g_Boss01.HP -= GetPlayer()->TackleDamege;
					g_Boss01.tacklehit = true;



				}
			}
			else
			{
				for (int i = 0; i < MAX_BULLET; i++)//バレッド全体を見る
				{
					if (GetBullet(i)->use == true)//使用状態で
					{
						if (CollisionBB(GetBullet(i)->pos, g_Boss01.Pos,
							GetBullet(i)->size, g_Boss01.size) == true)//当たったら
						{
							//ダメージ処理
							g_Boss01.HP -= GetBullet(i)->damage;


							GetBullet(i)->use = false;
							break;
						}
					}
				}
			}

			if (g_Boss01.HP <= 0)
			{
				g_Boss01.HP = 0;
				g_Boss01.Use = false;//消す
				// スコアデータの更新(他のクラスの関数を呼び出すときは、ここのコードをコピペ＆改変して使ってください)
				{
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
							score->AddScore(4000);
						}
					}
				}
				SetScene(SCENE_RESULT);
			}
		
		}
	}
	
}


