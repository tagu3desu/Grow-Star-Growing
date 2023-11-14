
#include "tutorial.h"
#include "texture.h"
#include "sprite.h"


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
static TUTORIAL  g_tutorial;

//*****************************************************************************
// グローバル変数
//*****************************************************************************

HRESULT TUTORIAL::InitGame()
{
	//テクスチャロード
	g_tutorial.texNo = LoadTexture((char*)"data\\texture\\tutorial_01.png");


	g_tutorial.Use = false;
	g_tutorial.Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	g_tutorial.Size = D3DXVECTOR2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	g_tutorial.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_tutorial.Rotate = 0;



	return S_OK;
}

void TUTORIAL :: UninitGame()
{
	
}

void TUTORIAL::UpdateGame()
{
	if (g_tutorial.Use == true)//使用フラグ
	{
		g_tutorial.Position.x -= 1.0f;
	}

	if (g_tutorial.Position.x <= -SCREEN_WIDTH / 2) //見えなくなるタイミング
	{
		g_tutorial.Use = false;
	}

}

void TUTORIAL::DrawGame()
{



	if (g_tutorial.Use == true)//使用フラグ
	{


		//テクスチャのセット
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_tutorial.texNo));

		DrawSpriteColorRotate
		(
			g_tutorial.Position.x,
			g_tutorial.Position.y,
			g_tutorial.Size.x,
			g_tutorial.Size.y,
			g_tutorial.Rotate,
			g_tutorial.Color,
			0,
			1.0f,
			1.0f,
			1
		);

	}

}

//=====================================================
//チュートリアルテクスチャセット
//=====================================================

void Set_BG(int TutorialTexNo)
{

	switch (TutorialTexNo)
	{
	case 1:
		//	BGテクスチャのロード
		g_tutorial.texNo = LoadTexture((char*)"data\\texture\\tutorial_01.png");
		if (g_tutorial.texNo == -1) {
			//読み込みエラー
			exit(999);//強制終了
		}

		break;
	case 2:
		//	BGテクスチャのロード
		g_tutorial.texNo = LoadTexture((char*)"data\\texture\\tutorial_02.png");
		if (g_tutorial.texNo == -1) {
			//読み込みエラー
			exit(999);//強制終了
		}
		break;

	case 3:
		//	BGテクスチャのロード
		g_tutorial.texNo = LoadTexture((char*)"data\\texture\\tutorial_03.png");
		if (g_tutorial.texNo == -1) {
			//読み込みエラー
			exit(999);//強制終了
		}
		break;

	default://一致する数値がないときの処理
		break;
	}

	//これは初期化
	g_tutorial.Use = true;
	g_tutorial.Position = D3DXVECTOR3(SCREEN_WIDTH , SCREEN_HEIGHT  / 2, 0);
	g_tutorial.Size = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	g_tutorial.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_tutorial.Rotate = 0;



	return;
}