#include "field.h"
#include "00_title.h"
/*==============================================================================

   フィールド処理 [field.cpp]		プロトタイプ版
														 Author :	髙橋建次
														 Date   :	2022_10_27
--------------------------------------------------------------------------------

==============================================================================*/


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************


FIELD::FIELD()
{
	//テクスチャファイルパス格納(現在計2枚)		新たに追加する場合は下の行にファイルパスを書く
	g_FieldTextureName[0] = (char*)"data\\texture\\haikei01.png";
	g_FieldTextureName[1] = (char*)"data\\texture\\Result.png";



	CurrentTexture = 0;
}

FIELD::~FIELD()
{

}

HRESULT FIELD::InitGame()
{
	Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Rotate = 0;
	Speed = 0.0f;

	//	BGテクスチャのロード
	for (int i = 0; i < MAX_FIELD_TEXTURE; i++)
	{
		TextureNoField[i] = LoadTexture(g_FieldTextureName[i]);
		if (TextureNoField[i] == -1) {
			//読み込みエラー
			exit(999);//強制終了
		}
	}

	//使用するテクスチャの設定(リザルトorそれ以外)
	if (GetScene() == SCENE_RESULT)
	{
		CurrentTexture = 1;
	}
	else
	{
		CurrentTexture = 0;
	}

	

	//BGMを鳴らす
	//PlaySound(mainBGM[CurrentBGM], -1);

	return S_OK;
}

void FIELD::UninitGame()
{
	//StopSoundAll();
}

void FIELD::UpdateGame()
{
	// 設定したスピードに応じてスクロール(ひとまず暫定版)
	Position.x += Speed;
}

void FIELD::DrawGame()
{	
	//テクスチャのセット
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextureNoField[CurrentTexture]));

	DrawSpriteColorRotate
	(
		Position.x,
		Position.y,
		Size.x,
		Size.y,
		Rotate,
		Color,
		0,
		1.0f,
		1.0f,
		1
	);
}

/*
	フィールドのスクロール速度を設定する関数
	引数：float speed (スクロール速度)
*/
void FIELD::SetFieldSpeed(float speed)
{
	Speed = speed;
}

