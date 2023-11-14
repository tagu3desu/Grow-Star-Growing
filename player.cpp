/*==============================================================================

   プレイヤー処理 [player.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include	"player.h"
#include    "enemy.h"
#include    "enemybullet.h"

#include	"sprite.h"
#include	"texture.h"
#include	"bullet.h"
#include	"data.h"

//#include	"mouse.h"
#include	"keyboard.h"
#include    "collision.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	PLAYER_SIZE_W	(30.0f)	//プレイヤーの横のサイズ
#define	PLAYER_SIZE_H	(30.0f)	//プレイヤーの縦のサイズ

#define PLAYER_MAX_SIZE_W	(300.0f)	//巨大化時の横のサイズ
#define PLAYER_MAX_SIZE_H	(300.0f)	//巨大化時の縦のサイズ

#define PLAYER_HP (3)			//プレイヤーHP
#define	PLAYER_HP_SIZE_W	(50.0f)	//プレイヤーHPの横のサイズ
#define PLAYER_HP_SIZE_H	(50.0f) //プレイヤーHPの縦のサイズ 

#define HUGE_SIZE_W (300.0f)
#define HUGE_SIZE_H (250.0f)


#define PLAYER_SPEED	(3.0f)		//プレイヤーの移動速度

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
PLAYER	g_Player;	// プレイヤーオブジェクト


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT PLAYER::InitGame(void)
{
	//テクスチャロード
	g_Player.texNo = LoadTexture((char*)"data\\texture\\hosi.png");//テクスチャファイルパス

	g_Player.Position = D3DXVECTOR2(PLAYER_SIZE_W / 2, SCREEN_HEIGHT / 2);

	g_Player.size.x = PLAYER_SIZE_W;
	g_Player.size.y = PLAYER_SIZE_H;

	g_Player.Rotate = 0.0f;
	g_Player.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Player.energy = 100;
	g_Player.gain = 5;
	g_Player.use = TRUE;

	g_Player.Bulletrate = 0;
	g_Player.ShotFlag = false;

	g_Player.Hp = PLAYER_HP;
	g_Player.HptexNo = LoadTexture((char*)"data\\texture\\playerHP.png");
	g_Player.HpSize.x = PLAYER_HP_SIZE_W;
	g_Player.HpSize.y = PLAYER_HP_SIZE_H;
	g_Player.HpPos = D3DXVECTOR2(50, 50);


	g_Player.HugetexNo=LoadTexture((char*)"data\\texture\\BIGUI.png");
	g_Player.HugePos = D3DXVECTOR2(480, 540);
	g_Player.HugeSize.x = HUGE_SIZE_W;
	g_Player.HugeSize.y = HUGE_SIZE_H;
	g_Player.HugeCount = 0;
	g_Player.HugeRotate = 0;
	g_Player.ResetHuge = false;
	g_Player.ChangeHuge = false;


	g_Player.FrameCaount = 0;
	g_Player.AtacckDelay = 0;
	g_Player.SizeUp = false;
	g_Player.tackle = false;
	g_Player.TackleDamege = 10;

	//攻撃種別をセット
	g_Player.SkillType[0] = GetData()->SkillType[0];		//通常弾(固定)
	g_Player.SkillType[1] = GetData()->SkillType[1];		//スキル1(初期は三股砲弾)
	g_Player.SkillType[2] = GetData()->SkillType[2];		//スキル2(初期は回転弾)

	for (int i = 0; i < 3; i++)
	{
		g_Player.SkillUsageMax[i] = GetBulletUsageMax(g_Player.SkillType[i]);			//使用回数の最大数を取得
		g_Player.SkillUsageCount[i] = g_Player.SkillUsageMax[i];						
		g_Player.SkillCoolTimeMax[i] = GetBulletCoolTimeMax(g_Player.SkillType[i]);		//クールタイムの最大数を取得
		g_Player.SkillCoolTime[i] = g_Player.SkillCoolTimeMax[i];
	}

	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void PLAYER::UninitGame(void)
{


}

//=============================================================================
// 更新処理
//=============================================================================
void PLAYER::UpdateGame(void)
{
	//ダメージ処理
	/*Player_dameg_reaction();*/

	

	if (g_Player.use == TRUE)
	{
		//キー入力チェック
		{
			if (Keyboard_IsKeyDown(KK_W) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_UP) || GetThumbLeftY(0) >= 0.3)			//上
			{
				// 押されたときの処理
				g_Player.Position.y += -PLAYER_SPEED;
			}
			else if (Keyboard_IsKeyDown(KK_S) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_DOWN) || GetThumbLeftY(0) <= -0.3)	//下
			{
				// 押された時の処理
				g_Player.Position.y += PLAYER_SPEED;
			}

			if (Keyboard_IsKeyDown(KK_A) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_LEFT)|| GetThumbLeftX(0) <= -0.3)			//左
			{
				// 押された時の処理
				g_Player.Position.x += -PLAYER_SPEED;
			}
			else if (Keyboard_IsKeyDown(KK_D) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_RIGHT) || GetThumbLeftX(0)  >= 0.3)	//右
			{
				// 押された時の処理
				g_Player.Position.x += PLAYER_SPEED;
			}
		}

	

		//弾の発射

		if (Keyboard_TriggerKeyDown(KK_LEFT) || IsButtonTriggered(0, XINPUT_GAMEPAD_B)/* && ShotFlag == false*/)
		{
			//星の量が一定数ある時＆使用回数が0でない時
			
				D3DXVECTOR2 pos = g_Player.Position;		// プレイヤ―の座標に弾を発射
				SetBullet(g_Player.SkillType[0], pos);		// スキル種別0の弾を発射
				ShotFlag = true;
		}
		/*if (ShotFlag == true)
		{
			Bulletrate++;
		}
		if (Bulletrate > 20)
		{
			Bulletrate = 0;
			ShotFlag = false;
		}*/
		else if (Keyboard_TriggerKeyDown(KK_UP) || IsButtonTriggered(0, XINPUT_GAMEPAD_Y))
		{
			//星の量が一定数ある時＆使用回数が0でない時
			if ( (g_Player.SkillUsageCount[1] != 0))
			{
				D3DXVECTOR2 pos = g_Player.Position;		// プレイヤ―の座標に弾を発射
				SetBullet(g_Player.SkillType[1], pos);		// スキル種別1の弾を発射
				if (g_Player.SkillUsageCount[1] > 0)		// 残り使用回数を減らす
				{
					g_Player.SkillUsageCount[1]--;
				}
			}
		}
		else if (Keyboard_TriggerKeyDown(KK_RIGHT) || IsButtonTriggered(0, XINPUT_GAMEPAD_X))
		{
			//星の量が一定数ある時＆使用回数が0でない時
			if ( (g_Player.SkillUsageCount[2] != 0))
			{
				D3DXVECTOR2 pos = g_Player.Position;		// プレイヤ―の座標に弾を発射
				SetBullet(g_Player.SkillType[2], pos);		// スキル種別2の弾を発射
				if (g_Player.SkillUsageCount[2] > 0)		// 残り使用回数を減らす
				{
					g_Player.SkillUsageCount[2]--;
				}
			}
		}

		// クールタイム処理
		for (int i = 0; i < 3; i++)
		{
			if (g_Player.SkillUsageCount[i] == 0)
			{
				g_Player.SkillCoolTime[i]--;
				if (g_Player.SkillCoolTime[i] <= 0)
				{
					g_Player.SkillCoolTime[i] = g_Player.SkillCoolTimeMax[i];
					g_Player.SkillUsageCount[i] = g_Player.SkillUsageMax[i];
				}
			}
		}



	   //===============================================================
	   // 巨大化系
		{
			

			//巨大化処理
			if (Keyboard_TriggerKeyDown(KK_LEFTSHIFT) || IsButtonTriggered(0, XINPUT_GAMEPAD_LEFT_SHOULDER))
			{
				if (g_Player.SizeUp == false && g_Player.energy >= 11)//小さいとき
				{	
					g_Player.ChangeHuge = true;	//回転開始
					g_Player.SizeUp = true;	//巨大化オン
					g_Player.size = D3DXVECTOR2(PLAYER_MAX_SIZE_W, PLAYER_MAX_SIZE_H);
					g_Player.energy -= 10;
				}


				else if(g_Player.SizeUp == true && g_Player.HugeCount == 0)//巨大化してる時
				{
					g_Player.ChangeHuge = true;	//回転開始
					g_Player.SizeUp = false;
					g_Player.size = D3DXVECTOR2(PLAYER_SIZE_W, PLAYER_SIZE_H);
					

				}
			}

			//===============================================
			//巨大化UIの回転処理
			
			if (g_Player.ChangeHuge==true && g_Player.HugeCount < 60)	//UI回転
			{
				g_Player.HugeCount++;
				g_Player.HugeRotate += 3;
			}
			else if (g_Player.ChangeHuge==true &&  g_Player.HugeCount>=60)
			{
				g_Player.HugeCount = 0;
				g_Player.ChangeHuge = false;
			}

			

			//==============================================
			//タックルの処理

			//巨大化状態の処理
			if (g_Player.SizeUp == true)
			{
				
				g_Player.FrameCaount++;
				if (g_Player.FrameCaount >= 10.0f)
				{
					g_Player.energy -= 1;		//60fごとに-1ずつ
					g_Player.FrameCaount = 0;
				}

				if (Keyboard_TriggerKeyDown(KK_SPACE) || IsButtonTriggered(0, XINPUT_GAMEPAD_RIGHT_SHOULDER))
				{
					g_Player.tackle = true;			//タックル開始
				}

				
				


				if (g_Player.tackle == true)//タックル中なら
				{
					g_Player.AtacckDelay++; //タックル開始からのフレームのカウント
					if (g_Player.AtacckDelay >= 30 && g_Player.AtacckDelay < 60)	//考えてみよう
					{
						g_Player.Rotate += 20.0f;		//回転中
						g_Player.Position.x -= 10.0f;	//タックル終わって戻ってるとこ
					}
					else if (g_Player.AtacckDelay >= 60)	//グランシャリオ
					{
						g_Player.Rotate = 0;		//回転を元に戻す
						g_Player.AtacckDelay = 0;	//タックルからのフレームカウント終了
						g_Player.tackle = false;	//タックル終わり
					}
					else //ライザのふともも最高
					{
						g_Player.Rotate += 20.0f;		//回転中
						g_Player.Position.x += 10.0f;	//敵の方にタックル中
					}

				}

				if (g_Player.energy == 0 && g_Player.tackle == false)
				{
					g_Player.SizeUp = false;
					g_Player.size = D3DXVECTOR2(PLAYER_SIZE_W, PLAYER_SIZE_H);
					g_Player.ChangeHuge = true;
				}
			}
		}

	}

	//================================================
	//画面外チェック

	{
		//上下
		if (g_Player.Position.y < SCREEN_LIMIT_UP + PLAYER_SIZE_H / 2)
		{
			g_Player.Position.y = SCREEN_LIMIT_UP + PLAYER_SIZE_H / 2;
		}
		else if (g_Player.Position.y > SCREEN_LIMIT_DOWN - PLAYER_SIZE_H / 2)
		{
			g_Player.Position.y = SCREEN_LIMIT_DOWN - PLAYER_SIZE_H / 2;
		}

		//左右
		if (g_Player.Position.x < SCREEN_LIMIT_LEFT + PLAYER_SIZE_W / 2)
		{
			g_Player.Position.x = SCREEN_LIMIT_LEFT + PLAYER_SIZE_W / 2;
		}
		else if (g_Player.Position.x > SCREEN_LIMIT_RIGHT - PLAYER_SIZE_W / 2)
		{
			g_Player.Position.x = SCREEN_LIMIT_RIGHT - PLAYER_SIZE_W / 2;
		}
	}

	//===========================================================
	//キラキラの上限と下限処理

	{
		//エナジー100以上なら切り捨て
		if (g_Player.energy > 100)
		{
			g_Player.energy = 100;
		}

		if (g_Player.energy < 0)
		{
			g_Player.energy = 0;
		}

	}
	
	//HPが0になった時
	if (g_Player.Hp <= 0)
	{
		SetScene(SCENE_RESULT);
	}
	
}

//=============================================================================
// 描画処理
//=============================================================================
void PLAYER::DrawGame(void)
{
	//構造体チェック
	if (g_Player.use == TRUE)
	{
		//テクスチャのセット
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Player.texNo));
		
		//描画
		DrawSpriteColorRotate(g_Player.Position.x, g_Player.Position.y,
			g_Player.size.x,//ｘサイズ
			g_Player.size.y,//ｙサイズ
			g_Player.Rotate,
			g_Player.Color,
			4, 
			1.0f,
			1.0f, 
			1);
	}


	//=======================================
	//HPの表示
	//======================================
	for (int i = 0; i < g_Player.Hp; i++)
	{
		//HPテクスチャのセット
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Player.HptexNo));

		//HP描画
		DrawSpriteColorRotate(g_Player.HpPos.x + i * 40, g_Player.HpPos.y,
			g_Player.HpSize.x,
			g_Player.HpSize.y,
			0,
			g_Player.Color,
			1,
			1.0f,
			1.0f,
			1);
	}

	//=========================================
	//タックルのUI
	//=========================================
	if (g_Player.use == true)
	{
		//UIテクスチャのセット
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Player.HugetexNo));

		//UI描画
		DrawSpriteColorRotate(g_Player.HugePos.x, g_Player.HugePos.y,
			g_Player.HugeSize.x,
			g_Player.HugeSize.y,
			g_Player.HugeRotate,
			g_Player.Color,
			1,
			1.0f,
			1.0f,
			1);
	}
}


//==========================
//構造体の先頭アドレスを返す
//==========================
PLAYER	*GetPlayer()
{
	return	&g_Player;
}


//============================================
//ダメージを受けた時の処理（敵の弾から

void Player_dameg_reaction()
{
	for (int i = 0; i < ENEMY_MAX_BULLET; i++)
	{
		if (GetEnemyBullet(i)->use == true) {

			if (CollisionBB(g_Player.Position, GetEnemyBullet(i)->pos,//
				g_Player.size, GetEnemyBullet(i)->size) == true)
			{	
				g_Player.energy -= 2;

				GetEnemyBullet(i)->use = false;

				break;
			}
		}
	}
}

