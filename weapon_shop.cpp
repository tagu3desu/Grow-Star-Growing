/*==============================================================================

   武器購入画面 [weapon_shop.cpp]
														 Author :髙橋建次
														 Date   :2023_01_16
--------------------------------------------------------------------------------

==============================================================================*/
#include "01_Scene.h"
#include "weapon_shop.h"
#include "score.h"
#include "data.h"
#include "texture.h"

#include "00_soundmain.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//武器購入画面の背景画像ファイルパス
static	char* g_WeaponShopBGTextureName = (char*)"data\\texture\\weapon_shop_back.png";

//武器購入ボタン画像のテクスチャファイルパス
static	char* g_WeaponShopButtonTextureName[WEAPON_MAX] = {
	(char*)"data\\texture\\weapon_shop_01.png",
	(char*)"data\\texture\\weapon_shop_02.png",
	(char*)"data\\texture\\weapon_shop_03.png",
	(char*)"data\\texture\\weapon_shop_04.png",
};

//購入済み画像ファイルパス
static	char* g_WeaponShopPurchasedTextureName = (char*)"data\\texture\\weapon_shop_purchased.png";

WEAPON_SHOP* g_WeaponShopBG;

WEAPON_SHOP_BUTTON		g_WeaponShopButton[WEAPON_MAX];

WEAPON_SHOP_BUTTON*		g_WeaponShopButtonPurchased;

Game*					g_WeaponShopScore = new SCORE;

int WeaponShopReplica; //セレクト番号超過の阻止用

HRESULT InitWeaponShop()
{
	//武器購入画面の背景
	{
		g_WeaponShopBG = new WEAPON_SHOP;

		g_WeaponShopBG->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
		g_WeaponShopBG->Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
		g_WeaponShopBG->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_WeaponShopBG->Rotate = 0;
		g_WeaponShopBG->WeaponSelect = 0;
		g_WeaponShopBG->HoldCoin = 0;

		g_WeaponShopBG->Texno = LoadTexture(g_WeaponShopBGTextureName);
		if (g_WeaponShopBG->Texno == -1) {
			//読み込みエラー
			exit(999);
		}
	}

	//武器購入ボタン
	for (int i = 0; i < WEAPON_MAX; i++)
	{
		int yoko = (i % 2);
		int tate = (i / 2);

		g_WeaponShopButton[i].Position = D3DXVECTOR2(450.0f * yoko + 250.0f, 140.0f * tate + 200.0f);
		g_WeaponShopButton[i].Size = D3DXVECTOR2(768.0f * 0.5f, 256.0f * 0.5f);
		g_WeaponShopButton[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_WeaponShopButton[i].Rotate = 0;

		g_WeaponShopButton[i].Texno = LoadTexture(g_WeaponShopButtonTextureName[i]);
		if (g_WeaponShopButton[i].Texno == -1) {
			//読み込みエラー
			exit(999);
		}

		g_WeaponShopButton[i].Ownership = FALSE;
		g_WeaponShopButton[i].Price = 0;
	}

	//購入済みマーク
	{
		g_WeaponShopButtonPurchased = new WEAPON_SHOP_BUTTON;
		g_WeaponShopButtonPurchased->Position = D3DXVECTOR2(250.0f, 200.0f);
		g_WeaponShopButtonPurchased->Size = D3DXVECTOR2(768.0f * 0.5f, 256.0f * 0.5f);
		g_WeaponShopButtonPurchased->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_WeaponShopButtonPurchased->Rotate = 0;

		g_WeaponShopButtonPurchased->Texno = LoadTexture(g_WeaponShopPurchasedTextureName);
		if (g_WeaponShopButtonPurchased->Texno == -1) {
			//読み込みエラー
			exit(999);
		}

		//以下は使わないが念のため初期化
		g_WeaponShopButtonPurchased->Ownership = FALSE;
		g_WeaponShopButtonPurchased->Price = 0;
	}

	//スコアの初期化
	g_WeaponShopScore->InitGame();

	//プレイヤー情報を取得(今は代わりにテスト用データを入れてあります)
	g_WeaponShopBG->HoldCoin = GetData()->Money;
	for (int i = 0; i < WEAPON_MAX; i++)
	{
		g_WeaponShopButton[i].Ownership = GetData()->Ownership[i];
	}
	//武器の価格設定
	g_WeaponShopButton[0].Price = 1000;		//貫通弾
	g_WeaponShopButton[1].Price = 2500;		//炸裂弾
	g_WeaponShopButton[2].Price = 2000;		//時限弾
	g_WeaponShopButton[3].Price = 4000;		//巨大弾
	SCORE* score = dynamic_cast<SCORE*>(g_WeaponShopScore);		//ダウンキャスト
	score->AddScore(g_WeaponShopBG->HoldCoin);		//テスト用の所持金データを入れる
	score->SettingScore(D3DXVECTOR2(790.0f, 32.0f), 21.0f, 6, TRUE);

	return S_OK;
}
void UninitWeaponShop()
{
	if (g_WeaponShopBG)
	{
		delete g_WeaponShopBG;
		g_WeaponShopBG = NULL;
	}

	//スコアの終了処理
	g_WeaponShopScore->UninitGame();
}
void UpdateWeaponShop()
{

	//==============================================================
	//ステージセレクトの処理
	//==============================================================
	{
		if (Keyboard_TriggerKeyDown(KK_RIGHT) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_RIGHT))//右ボタン
		{
			WeaponShopReplica = g_WeaponShopBG->WeaponSelect + 1;
			PlayEffect(Tap, 1.0f);
		}
		else if (Keyboard_TriggerKeyDown(KK_DOWN) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_DOWN))//下ボタン
		{
			WeaponShopReplica = g_WeaponShopBG->WeaponSelect + WEAPON_MAX / 2;
			PlayEffect(Tap, 1.0f);
		}
		else if (Keyboard_TriggerKeyDown(KK_LEFT) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_LEFT))//左ボタン
		{
			WeaponShopReplica = g_WeaponShopBG->WeaponSelect - 1;
			PlayEffect(Tap, 1.0f);
		}
		else if (Keyboard_TriggerKeyDown(KK_UP) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_UP))//上ボタン
		{
			WeaponShopReplica = g_WeaponShopBG->WeaponSelect - WEAPON_MAX / 2;
			PlayEffect(Tap, 1.0f);
		}

		if (WeaponShopReplica >= 0 && WeaponShopReplica < WEAPON_MAX)//上限を上回らないように
		{
			g_WeaponShopBG->WeaponSelect = WeaponShopReplica;
		}

		//===========================================================
		//未セレクト画面の処理とグレーダウン処理
		{
			for (int i = 0; i < WEAPON_MAX; i++)
			{
				g_WeaponShopButton[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//明るくする
			}

			g_WeaponShopButton[g_WeaponShopBG->WeaponSelect].Color = D3DXCOLOR(0.5f, 0.8f, 0.8f, 1.0f);//グレーダウン
		}
	}


	//==============================================================
	//購入処理
	//==============================================================
	{
		if (Keyboard_TriggerKeyDown(KK_SPACE) || IsButtonTriggered(0, XINPUT_GAMEPAD_B))
		{
			//未所持かつ所持金が十分あれば購入
			if (g_WeaponShopButton[g_WeaponShopBG->WeaponSelect].Ownership == FALSE && g_WeaponShopBG->HoldCoin >= g_WeaponShopButton[g_WeaponShopBG->WeaponSelect].Price)
			{
				//所持金を減らす
				g_WeaponShopBG->HoldCoin -= g_WeaponShopButton[g_WeaponShopBG->WeaponSelect].Price;
				g_WeaponShopButton[g_WeaponShopBG->WeaponSelect].Ownership = TRUE;
				SCORE* score = dynamic_cast<SCORE*>(g_WeaponShopScore);		//ダウンキャスト
				score->AddScore(-g_WeaponShopButton[g_WeaponShopBG->WeaponSelect].Price);		//テスト用の所持金データを入れる
				//変えたときの効果音を鳴らす
				PlayEffect(OKvol, 1.0f);
			}
			else
			{
				PlayEffect(Not, 1.0f);
				//何もしない（買えないときの効果音だけ鳴らす？）
			}
		}
	}

	//スコアの更新
	g_WeaponShopScore->UpdateGame();

	//タイトルへ戻る
	if (Keyboard_TriggerKeyDown(KK_BACK) == true || IsButtonPressed(0, XINPUT_GAMEPAD_X))		//Xボタン(BACKキー)
	{
		SetData(g_WeaponShopBG->HoldCoin, -1, -1, -1);

		G_DATA* data = GetData();
		for (int i = 0; i < WEAPON_MAX; i++)
		{
			data->Ownership[i] = g_WeaponShopButton[i].Ownership;
		}

		SetScene(SCENE_TITLE);
	}
}
void DrawWeaponShop()
{
	//========================================================================
	//ステージ背景表示
	//========================================================================
	{
		//テクスチャのセット
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_WeaponShopBG->Texno));

		DrawSpriteColorRotate
		(
			g_WeaponShopBG->Position.x,
			g_WeaponShopBG->Position.y,
			g_WeaponShopBG->Size.x,
			g_WeaponShopBG->Size.y,
			g_WeaponShopBG->Rotate,
			g_WeaponShopBG->Color,
			0,
			1.0f,
			1.0f,
			1
		);
	}

	//==========================================================================
	//ステージセレクト用ボタン
	//========================================================================
	{

		for (int i = 0; i < WEAPON_MAX; i++)
		{
			//テクスチャのセット
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_WeaponShopButton[i].Texno));

			DrawSpriteColorRotate
			(
				g_WeaponShopButton[i].Position.x,
				g_WeaponShopButton[i].Position.y,
				g_WeaponShopButton[i].Size.x,
				g_WeaponShopButton[i].Size.y,
				g_WeaponShopButton[i].Rotate,
				g_WeaponShopButton[i].Color,
				0,
				1.0f,
				1.0f,
				1
			);
		}

	}

	//==========================================================================
	//購入済みマーク
	//========================================================================
	{
		for (int i = 0; i < WEAPON_MAX; i++)
		{
			if (g_WeaponShopButton[i].Ownership == TRUE)
			{
				//座標を取得する
				g_WeaponShopButtonPurchased->Position = g_WeaponShopButton[i].Position;

				//テクスチャのセット
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_WeaponShopButtonPurchased->Texno));

				DrawSpriteColorRotate
				(
					g_WeaponShopButtonPurchased->Position.x,
					g_WeaponShopButtonPurchased->Position.y,
					g_WeaponShopButtonPurchased->Size.x,
					g_WeaponShopButtonPurchased->Size.y,
					g_WeaponShopButtonPurchased->Rotate,
					g_WeaponShopButtonPurchased->Color,
					0,
					1.0f,
					1.0f,
					1
				);
			}
		}
	}

	g_WeaponShopScore->DrawGame();
}
