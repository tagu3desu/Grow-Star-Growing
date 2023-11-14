/*==============================================================================

   スコア（数字表示関係）処理 [score.cpp]
														 Author :	AT12G_25_髙橋建次
														 Date   :	2022_09_29
--------------------------------------------------------------------------------

==============================================================================*/
#include	"score.h"

#include	"sprite.h"
#include	"texture.h"
#include	"player.h"
#include	"data.h"

#include	"01_Scene.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define	SCORE_SIZE_W	(43.0f * 0.75f)	//四角形の横のサイズ
#define	SCORE_SIZE_H	(42.0f * 0.75f)	//四角形の縦のサイズ

#define UPDATE_SCORE_NUMBER		(50)	// 実際のスコア表示で加算する数の分割数


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
SCORE::SCORE()
{
	//テクスチャファイルパス格納(現在計1枚)		新たに追加する場合は下の行にファイルパスを書く
	g_ScoreTextureName[0] = (char*)"data\\texture\\number.png";
}

//=============================================================================
// デストラクタ
//=============================================================================
SCORE::~SCORE()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT SCORE::InitGame(void)
{

	Position = D3DXVECTOR2(800.0f, 30.0f);
	w = SCORE_SIZE_W;
	h = SCORE_SIZE_H;
	Rotate = 0.0f;
	Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	number = 0;
	display_number = 0;
	dizit = 5;
	type = 0;
	CurrentTexture = 0;
	anime = TRUE;
	use = TRUE;

	//	BGテクスチャのロード
	for (int i = 0; i < MAX_SCORE_TEXTURE; i++)
	{
		TextureNoScore[i] = LoadTexture(g_ScoreTextureName[i]);
		if (TextureNoScore[i] == -1) {
			//読み込みエラー
			exit(999);//強制終了
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void SCORE::UninitGame(void)
{
	//スコアデータを入れてはいけない条件を記述
	if (GetScene() != SCENE_RESULT || GetScene() != SCENE_SHOP)
	{
		//スコアデータを格納する
		SetData(-1, -1, -1, number);
	}
}

//=============================================================================
// 更新処理(表示する数を引数に入れる)
//=============================================================================
void SCORE::UpdateGame(void)
{

	// 実際に表示する数の更新
	if (use == TRUE)
	{
		if (display_number < number)
		{
			if (display_number + 2000 < number)
			{
				display_number += 1000;
			}

			display_number += UPDATE_SCORE_NUMBER;
			if (display_number > number || anime == FALSE)
			{
				display_number = number;
			}
		}
		else if (display_number > number)
		{
			if (display_number > number + 2000)
			{
				display_number -= 1000;
			}
				display_number -= UPDATE_SCORE_NUMBER;
			if (display_number < number || anime == FALSE)
			{
				display_number = number;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void SCORE::DrawGame(void)
{
	{
		//// 表示したいポリゴンの頂点バッファを設定
		//UINT stride = sizeof(VERTEX_3D);
		//UINT offset = 0;
		//GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

		// ２Ｄ表示をするためのマトリクスを設定
		SetWorldViewProjection2D();

		//// プリミティブトポロジ設定
		//GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

		// マテリアル設定
		MATERIAL material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	}

	for (int i = 0; i < SCORE_MAX; i++)
	{
		if (use == TRUE)
		{
			//テクスチャのセット
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextureNoScore[CurrentTexture]));

			for (int j = 0; j < dizit; j++)
			{
				int		div = 1;
				int		diz = 0;

				for (int n = 1; n < (dizit - j); n++)
				{
					div *= 10;
				}

				diz = display_number / div;

				DrawSpriteColorRotate(Position.x + (w * j), Position.y, w, h, Rotate, Color, 0.0f + (1.0f * diz), 0.1f, 1.0f, 10);

			}
		}
	}
}

//=============================================================================
// スコアを格納する関数
// 引数：int input_score (格納するスコア)
//=============================================================================
void SCORE::AddScore(int input_score)
{
	number += input_score;
}

//=============================================================================
// スコアを取得する関数
//=============================================================================
int SCORE::GetScore(void) const
{
	return number;
}

//====================================================================================================
// 設定を変更する関数
// 引数：D3DXVECTOR2 pos (座標), float size (文字の大きさ), int diz (桁数), BOOL animation (アニメーションする/しない)
//====================================================================================================
void SCORE::SettingScore(D3DXVECTOR2(pos), float size, int diz, BOOL animation)
{
	Position = pos;
	h = size;
	w = (float)(SCORE_SIZE_W / SCORE_SIZE_H)* size;
	dizit = diz;
	anime = animation;
}
