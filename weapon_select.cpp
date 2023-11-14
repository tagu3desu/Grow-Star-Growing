/*==============================================================================

   スキルセット画面 [weapon_select.cpp]
														 Author :髙橋建次
														 Date   :2023_01_21
--------------------------------------------------------------------------------

==============================================================================*/
#include	"weapon_select.h"
#include	"data.h"
#include	"player.h"
#include	"texture.h"

#include "00_soundmain.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//スキルセット画面の背景画像ファイルパス
static	char* g_WeaponSelectBGTextureName = (char*)"data\\texture\\weapon_select_back.png";

static	char* g_SelectSkillButtonTextureName[WEAPON_HOLD_MAX] = {
	(char*)"data\\texture\\selected_bullet_back_01.png",
	(char*)"data\\texture\\selected_bullet_back_02.png",
	(char*)"data\\texture\\selected_bullet_back_03.png",
	(char*)"data\\texture\\selected_bullet_back_04.png",
	(char*)"data\\texture\\selected_bullet_back_05.png",
	(char*)"data\\texture\\selected_bullet_back_06.png",
};

static	char* g_SelectWeaponButtonTextureName[WEAPON_HOLD_MAX * 2 + 1] = {
	(char*)"data\\texture\\select_bullet_back_01.png",							//ボタン背景三股砲弾
	(char*)"data\\texture\\select_bullet_back_02.png",							//ボタン背景貫通弾
	(char*)"data\\texture\\select_bullet_back_03.png",							//ボタン背景回転弾
	(char*)"data\\texture\\select_bullet_back_04.png",							//ボタン背景炸裂弾
	(char*)"data\\texture\\select_bullet_back_05.png",							//ボタン背景時限弾
	(char*)"data\\texture\\select_bullet_back_06.png",							//ボタン背景巨大弾
	(char*)"data\\texture\\kakuta_三股砲弾.png",
	(char*)"data\\texture\\kakuta_貫通弾.png",
	(char*)"data\\texture\\kakuta_回転弾.png",
	(char*)"data\\texture\\kakuta_炸裂弾.png",
	(char*)"data\\texture\\kakuta_時限弾.png",
	(char*)"data\\texture\\kakuta_巨大弾.png",
	(char*)"data\\texture\\selected_bullet_back_none.png",					//未所持状態のボタン背景
};

WEAPON_SELECT*	 g_WeaponSelect;

SELECT_SKILL_BUTTON		g_SelectSkill[2];

SELECT_WEAPON_BUTTON	g_SelectWeapon[WEAPON_HOLD_MAX];


HRESULT InitWeaponSelect()
{
	//スキルセット画面
	{
		g_WeaponSelect = new WEAPON_SELECT;

		g_WeaponSelect->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
		g_WeaponSelect->Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
		g_WeaponSelect->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_WeaponSelect->Rotate = 0;

		g_WeaponSelect->Texno = LoadTexture(g_WeaponSelectBGTextureName);
		if (g_WeaponSelect->Texno == -1) {
			//読み込みエラー
			exit(999);
		}

		g_WeaponSelect->SelectSkill = 0;
		g_WeaponSelect->SelectWeapon = -1;
	}

	//スキル選択ボタン
	for (int i = 0; i < 2; i++)
	{
		g_SelectSkill[i].Position = D3DXVECTOR2(0.0f, 0.0f);
		g_SelectSkill[i].Size = D3DXVECTOR2(384.0f * 0.5f, 320.0f * 0.5f);
		g_SelectSkill[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_SelectSkill[i].Rotate = 0;

		for (int j = 0; j < WEAPON_HOLD_MAX; j++)
		{
			g_SelectSkill[i].Texno[j] = LoadTexture(g_SelectSkillButtonTextureName[j]);
			if (g_SelectSkill[i].Texno[j] == -1) {
				//読み込みエラー
				exit(999);
			}
		}

		g_SelectSkill[i].SkillType = GetData()->SkillType[i + 1] - 1;	//0番目は通常弾なので1番目から取得
	}

	g_SelectSkill[0].Position = D3DXVECTOR2(SCREEN_WIDTH * 0.5f, 100.0f);
	g_SelectSkill[1].Position = D3DXVECTOR2(770.0f, 270.0f);

	//武器選択ボタン
	for (int i = 0; i < WEAPON_HOLD_MAX; i++)
	{
		g_SelectWeapon[i].Position = D3DXVECTOR2(i * 128.0f + ((SCREEN_WIDTH - WEAPON_HOLD_MAX * 128.0f) * 0.5f + 64.0f), 450.0f);
		g_SelectWeapon[i].Size = D3DXVECTOR2(128.0f, 128.0f);
		g_SelectWeapon[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_SelectWeapon[i].Rotate = 0;

		//所持時の背景
		g_SelectWeapon[i].Texno = LoadTexture(g_SelectWeaponButtonTextureName[i]);
		if (g_SelectWeapon[i].Texno == -1) {
			//読み込みエラー
			exit(999);
		}

		//未所持時の背景
		g_SelectWeapon[i].NoneTexno = LoadTexture(g_SelectWeaponButtonTextureName[WEAPON_HOLD_MAX * 2]);
		if (g_SelectWeapon[i].NoneTexno == -1) {
			//読み込みエラー
			exit(999);
		}

		//武器アイコン
		g_SelectWeapon[i].IconTexno = LoadTexture(g_SelectWeaponButtonTextureName[i + WEAPON_HOLD_MAX]);
		if (g_SelectWeapon[i].IconTexno == -1) {
			//読み込みエラー
			exit(999);
		}

		if (i == 0 || i == 2)		//三股砲弾と回転弾は初期から持っている
		{
			g_SelectWeapon[i].Ownership = TRUE;
		}
		else if (i == 1)			//貫通弾
		{
			g_SelectWeapon[i].Ownership = GetData()->Ownership[0];
		}
		else
		{
			g_SelectWeapon[i].Ownership = GetData()->Ownership[i - 2];
		}
	}

	return S_OK;
}

void UninitWeaponSelect()
{
	if (g_WeaponSelect)
	{
		delete g_WeaponSelect;
		g_WeaponSelect = NULL;
	}
}

void UpdateWeaponSelect()
{
	if (Keyboard_TriggerKeyDown(KK_RIGHT) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_RIGHT))//右ボタン
	{
		PlayEffect(Tap, 1.0f);

		if (g_WeaponSelect->SelectWeapon < 0)
		{
			//スキルスロットのカーソル移動
			g_WeaponSelect->SelectSkill++;
			if (g_WeaponSelect->SelectSkill > 1)
			{
				g_WeaponSelect->SelectSkill = 0;
			}
		}
		else
		{
			//武器選択のカーソル移動
			g_WeaponSelect->SelectWeapon++;
			//移動先が未所持時の場合はスキップして次へ
			while (g_SelectWeapon[g_WeaponSelect->SelectWeapon].Ownership == FALSE)
			{
				g_WeaponSelect->SelectWeapon++;
				if (g_WeaponSelect->SelectWeapon >= WEAPON_HOLD_MAX)
				{
					g_WeaponSelect->SelectWeapon = 0;
				}
			}
			if (g_WeaponSelect->SelectWeapon >= WEAPON_HOLD_MAX)
			{
				g_WeaponSelect->SelectWeapon = 0;
			}
		}

	}
	else if (Keyboard_TriggerKeyDown(KK_LEFT) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_LEFT))//左ボタン
	{
		PlayEffect(Tap, 1.0f);

		if (g_WeaponSelect->SelectWeapon < 0)
		{
			//スキルスロットのカーソル移動
			g_WeaponSelect->SelectSkill--;
			if (g_WeaponSelect->SelectSkill < 0)
			{
				g_WeaponSelect->SelectSkill = 1;
			}
		}
		else
		{
			//武器選択のカーソル移動
			g_WeaponSelect->SelectWeapon--;
			//移動先が未所持時の場合はスキップして次へ
			while (g_SelectWeapon[g_WeaponSelect->SelectWeapon].Ownership == FALSE)
			{
				g_WeaponSelect->SelectWeapon--;
				if (g_WeaponSelect->SelectWeapon < 0)
				{
					g_WeaponSelect->SelectWeapon = WEAPON_HOLD_MAX - 1;
				}
			}
			if (g_WeaponSelect->SelectWeapon < 0)
			{
				g_WeaponSelect->SelectWeapon = WEAPON_HOLD_MAX - 1;
			}
		}

	}
	else if (Keyboard_TriggerKeyDown(KK_SPACE) || IsButtonTriggered(0, XINPUT_GAMEPAD_B))	//Bボタン
	{
		PlayEffect(OKvol, 1.0f);

		if (g_WeaponSelect->SelectWeapon < 0)	//スキルセット枠の選択状態の場合、武器選択状態に移行する
		{
			g_WeaponSelect->SelectWeapon = 0;
		}
		else
		{
			//武器をスキルとしてセット
			g_SelectSkill[g_WeaponSelect->SelectSkill].SkillType = g_WeaponSelect->SelectWeapon;		//0番目は通常弾なのでプラス1する
			g_WeaponSelect->SelectWeapon = -1;
		}
	}

	//===========================================================
	//未セレクト画面の処理とグレーダウン処理(スキルセットボタン)
	//===========================================================
	{
		for (int i = 0; i < 2; i++)
		{
			g_SelectSkill[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//明るくする
		}
		g_SelectSkill[g_WeaponSelect->SelectSkill].Color = D3DXCOLOR(0.5f, 0.8f, 0.8f, 1.0f);//グレーダウン
	}

	//===========================================================
	//未セレクト画面の処理とグレーダウン処理(武器選択ボタン)
	//===========================================================
	{
		for (int i = 0; i < WEAPON_HOLD_MAX; i++)
		{
			g_SelectWeapon[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//明るくする
		}
		if (g_WeaponSelect->SelectWeapon >= 0)
		{
			g_SelectWeapon[g_WeaponSelect->SelectWeapon].Color = D3DXCOLOR(0.5f, 0.8f, 0.8f, 1.0f);//グレーダウン
		}
	}

	//タイトルへ戻る
	if (Keyboard_TriggerKeyDown(KK_BACK) == true || IsButtonPressed(0, XINPUT_GAMEPAD_X))		//Xボタン(BACKキー)
	{
		//スキルのセット状況をdata.cppに保存(skill[0]は通常弾0で固定)
		int skill[3] = {0, g_SelectSkill[0].SkillType + 1, g_SelectSkill[1].SkillType + 1};
		SetSkillType(skill);

		SetScene(SCENE_TITLE);
	}
}

void DrawWeaponSelect()
{
	//========================================================================
	//ステージ背景表示
	//========================================================================
	{
		//テクスチャのセット
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_WeaponSelect->Texno));

		DrawSpriteColorRotate
		(
			g_WeaponSelect->Position.x,
			g_WeaponSelect->Position.y,
			g_WeaponSelect->Size.x,
			g_WeaponSelect->Size.y,
			g_WeaponSelect->Rotate,
			g_WeaponSelect->Color,
			0,
			1.0f,
			1.0f,
			1
		);
	}

	//==========================================================================
	//スキルセットボタン
	//==========================================================================
	{

		for (int i = 0; i < 2; i++)
		{
			//テクスチャのセット(ボタン背景)
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SelectSkill[i].Texno[g_SelectSkill[i].SkillType]));

			DrawSpriteColorRotate
			(
				g_SelectSkill[i].Position.x,
				g_SelectSkill[i].Position.y,
				g_SelectSkill[i].Size.x,
				g_SelectSkill[i].Size.y,
				g_SelectSkill[i].Rotate,
				g_SelectSkill[i].Color,
				0,
				1.0f,
				1.0f,
				1
			);

			//テクスチャのセット(武器選択ボタンのアイコンテクスチャを流用)
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SelectWeapon[g_SelectSkill[i].SkillType].IconTexno));

			DrawSpriteColorRotate
			(
				g_SelectSkill[i].Position.x,
				g_SelectSkill[i].Position.y + 16.0f,
				g_SelectSkill[i].Size.x * 0.75f,
				g_SelectSkill[i].Size.y * 0.75f,
				g_SelectSkill[i].Rotate,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	//グレーダウンしない
				0,
				1.0f,
				1.0f,
				1
			);
		}

	}

	//==========================================================================
	//武器選択ボタン
	//==========================================================================
	{
		for (int i = 0; i < WEAPON_HOLD_MAX; i++)
		{
			//テクスチャのセット
			if (g_SelectWeapon[i].Ownership == TRUE)
			{
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SelectWeapon[i].Texno));
			}
			else
			{
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SelectWeapon[i].NoneTexno));
			}

			DrawSpriteColorRotate
			(
				g_SelectWeapon[i].Position.x,
				g_SelectWeapon[i].Position.y,
				g_SelectWeapon[i].Size.x,
				g_SelectWeapon[i].Size.y,
				g_SelectWeapon[i].Rotate,
				g_SelectWeapon[i].Color,
				0,
				1.0f,
				1.0f,
				1
			);

			//テクスチャのセット(武器アイコン)
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SelectWeapon[i].IconTexno));

			if (g_SelectWeapon[i].Ownership == TRUE)	//所持している武器のみアイコンを表示
			{
				DrawSpriteColorRotate
				(
					g_SelectWeapon[i].Position.x,
					g_SelectWeapon[i].Position.y + 10.0f,
					g_SelectWeapon[i].Size.x * 0.75f,
					g_SelectWeapon[i].Size.y * 0.75f,
					g_SelectWeapon[i].Rotate,
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	//グレーダウンしない
					0,
					1.0f,
					1.0f,
					1
				);
			}
		}
	}
}
