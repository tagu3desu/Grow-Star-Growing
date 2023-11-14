#include	<stdlib.h>
#include	"skill_ui.h"

#include	"sprite.h"
#include	"texture.h"


#include	"player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	SKILL_UI_SIZE_W	(80.0f)	//四角形の横のサイズ
#define	SKILL_UI_SIZE_H	(40.0f)	//四角形の縦のサイズ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
SKILL_UI	 g_SkillUI[3];
//スキルアイコン画像のテクスチャ
static	char* g_SkillUITextureName[7] = {
	(char*)"data\\texture\\kakuta_通常弾.png",
	(char*)"data\\texture\\kakuta_三股砲弾.png",
	(char*)"data\\texture\\kakuta_貫通弾.png",
	(char*)"data\\texture\\kakuta_回転弾.png",
	(char*)"data\\texture\\kakuta_炸裂弾.png",
	(char*)"data\\texture\\kakuta_時限弾.png",
	(char*)"data\\texture\\kakuta_巨大弾.png",
};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT SKILL_UI::InitGame(void)
{
	for (int i = 0; i < SKILL_UI_MAX; i++)
	{
		//構造体すべて処理
		g_SkillUI[i].pos = D3DXVECTOR2(90.0f * i + 60.0f, 480.0f);
		g_SkillUI[i].size.x = SKILL_UI_SIZE_W;
		g_SkillUI[i].size.y = SKILL_UI_SIZE_H;
		g_SkillUI[i].rot = 0.0f;
		g_SkillUI[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_SkillUI[i].texNo = LoadTexture((char*)"data\\texture\\player_skill_back.png");//テクスチャロード;
		g_SkillUI[i].texGrayDownNo = LoadTexture((char*)"data\\texture\\player_skill_graydown.png");//グレーダウンテクスチャロード
		g_SkillUI[i].texIconNo = LoadTexture(g_SkillUITextureName[GetPlayer()->SkillType[i]]);
		g_SkillUI[i].use = TRUE;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void SKILL_UI::UninitGame(void)
{


}


//=============================================================================
// 更新処理
//=============================================================================
void SKILL_UI::UpdateGame(void)
{
	//if (GetPlayer()->energy < 100 && GetPlayer()->energy > 0) //ゲージ最大量
	//{
	//	g_SkillUI2.size.y = GetPlayer()->energy * 2; //エネルギー分のサイズにする
	//	g_SkillUI2.pos.y = -GetPlayer()->energy / 2 + 315.0f ;
	//}
	//g_SkillUI2.EnergyCount += 1.0f;	//カウントを増やす
	//if (g_SkillUI2.EnergyCount >= 60)	//カウントが60になったら
	//{
	//	g_SkillUI2.pos.y += 1.5f; //半分上げる
	//	g_SkillUI2.EnergyCount = 0.0f;	//カウントを戻す
	//}
}

//=============================================================================
// 描画処理
//=============================================================================
void SKILL_UI::DrawGame(void)
{
	PLAYER* player = GetPlayer();

	//構造体を全て調べる
	for (int i = 0; i < SKILL_UI_MAX; i++)
	{
		//構造体が使用中なら処理
		if (g_SkillUI[i].use == TRUE)
		{
			//背景
			{
				//テクスチャのセット
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SkillUI[i].texNo));

				//描画
				DrawSpriteColorRotate
				(g_SkillUI[i].pos.x,
					g_SkillUI[i].pos.y,
					(int)g_SkillUI[i].size.x,
					(int)g_SkillUI[i].size.y,
					g_SkillUI[i].rot,
					g_SkillUI[i].color,
					1.0f,
					1.0f,
					1.0f,
					1
				);
			}

			//グレーダウン
			{
				//テクスチャのセット
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SkillUI[i].texGrayDownNo));

				//描画
				DrawSpriteColorRotate
				(g_SkillUI[i].pos.x,
					(g_SkillUI[i].pos.y - g_SkillUI[i].size.y * 0.75f * ((float)player->SkillUsageCount[i] / (float)player->SkillUsageMax[i]) * 0.5f),
					(int)(g_SkillUI[i].size.x * 0.8125f),
					(int)(g_SkillUI[i].size.y * 0.75f * (1.0f - ((float)player->SkillUsageCount[i] / (float)player->SkillUsageMax[i]))),
					g_SkillUI[i].rot,
					g_SkillUI[i].color,
					1.0f,
					1.0f,
					1.0f,
					1
				);
			}

			//アイコン画像
			{
				//テクスチャのセット
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SkillUI[i].texIconNo));

				//描画
				DrawSpriteColorRotate
				(g_SkillUI[i].pos.x,
					g_SkillUI[i].pos.y,
					(int)g_SkillUI[i].size.y * 0.75f,
					(int)g_SkillUI[i].size.y * 0.75f,
					g_SkillUI[i].rot,
					g_SkillUI[i].color,
					1.0f,
					1.0f,
					1.0f,
					1
				);
			}
		}
	}
}

//==========================
//構造体の先頭アドレスを返す
//==========================
SKILL_UI	*GetSkillUI()
{
	return	&g_SkillUI[0];
}
