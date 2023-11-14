#include	<stdlib.h>
#include	"gauge.h"

#include	"sprite.h"
#include	"texture.h"

#include	"player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	GAUGE_SIZE_W	(40.0f)	//四角形の横のサイズ
#define	GAUGE_SIZE_H	(250.0f)	//四角形の縦のサイズ

#define	GAUGE2_SIZE_W	(40.0f)	//四角形の横のサイズ
#define GAUGE2_SIZE_H   (200.0f)//えねじー

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
GAUGE	 g_gauge;
GAUGE	 g_gauge2;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT GAUGE::InitGame(void)
{
	

	//構造体すべて処理
		g_gauge.pos = D3DXVECTOR2(20.0f, 200.0f);
		g_gauge.size.x = GAUGE_SIZE_W;
		g_gauge.size.y = GAUGE_SIZE_H;
		g_gauge.rot = 0.0f;
		g_gauge.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_gauge.texNo = LoadTexture((char*)"data\\texture\\STARUI.png");//テクスチャロード;
		g_gauge.use = TRUE;

		//構造体すべて処理
		g_gauge2.pos = D3DXVECTOR2(20.0f, 270.0f);
		g_gauge2.size.x = GAUGE2_SIZE_W;
		g_gauge2.size.y = GetPlayer()->energy;
		g_gauge2.rot = 0.0f;
		g_gauge2.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_gauge2.texNo = LoadTexture((char*)"data\\texture\\STARINUI.png");//テクスチャロード;
		g_gauge2.use = TRUE;
	

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void GAUGE::UninitGame(void)
{


}


//=============================================================================
// 更新処理
//=============================================================================
void GAUGE::UpdateGame(void)
{
	if (GetPlayer()->energy < 100 && GetPlayer()->energy > -1) //ゲージ最大量
	{
		g_gauge2.size.y = GetPlayer()->energy ; //エネルギー分のサイズにする
		g_gauge2.pos.y = -GetPlayer()->energy / 2 + 325.0f;
	}
	//g_gauge2.EnergyCount += 1.0f;	//カウントを増やす
	//if (g_gauge2.EnergyCount >= 60)	//カウントが60になったら
	//{
	//	g_gauge2.pos.y += 1.5f; //半分上げる
	//	g_gauge2.EnergyCount = 0.0f;	//カウントを戻す
	//}
}

//=============================================================================
// 描画処理
//=============================================================================
void GAUGE::DrawGame(void)
{
	//構造体を全て調べる
	for (int i = 0; i < GAUGE_MAX; i++)
	{
		//構造体が使用中なら処理
		if (g_gauge.use == true)
		{
			//テクスチャのセット
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_gauge.texNo));

			//描画
			DrawSpriteColorRotate
			(g_gauge.pos.x,
				g_gauge.pos.y,
				g_gauge.size.x,
				g_gauge.size.y,
				g_gauge.rot,
				g_gauge.color,
				1.0f,
				1.0f,
				1.0f,
				1
			);
		}
	}

	//構造体を全て調べる
	for (int i = 0; i < GAUGE2_MAX; i++)
	{
		//構造体が使用中なら処理
		if (g_gauge2.use == true)
		{
			//テクスチャのセット
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_gauge2.texNo));

			//描画
			DrawSpriteColorRotate
			(g_gauge2.pos.x,
				g_gauge2.pos.y,
				g_gauge2.size.x,
				g_gauge2.size.y,
				g_gauge2.rot,
				g_gauge2.color,
				1.0f,
				1.0f,
				1.0f,
				1
			);
		}
	}
}

//==========================
//構造体の先頭アドレスを返す
//==========================
GAUGE* GetGauge()
{
	return	&g_gauge;
}

//==========================
//構造体の先頭アドレスを返す
//==========================
GAUGE* GetGauge2()
{
	return	&g_gauge2;
}