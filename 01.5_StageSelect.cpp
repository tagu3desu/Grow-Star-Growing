 #include "01.5_StageSelect.h"
#include "texture.h"

#include "00_soundmain.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//static	ID3D11ShaderResourceView* g_StageSelectTexture = NULL;
//
//static	ID3D11ShaderResourceView* g_SelectButtonTexture1 = NULL;
//static	ID3D11ShaderResourceView* g_SelectButtonTexture2 = NULL;
//static	ID3D11ShaderResourceView* g_SelectButtonTexture3 = NULL;
//static	ID3D11ShaderResourceView* g_SelectButtonTexture4 = NULL;

#define STEGE_MAX (6)




static	char* g_StageSelectTextureName =   (char*)"data\\texture\\haikei01.png";//テクスチャファイルパス
static	char* g_SelectButtonTextureName = (char*)"data\\texture\\button1.png";//テクスチャファイルパス
static	char* g_SelectButtonTextureName2 = (char*)"data\\texture\\button2.png";//テクスチャファイルパス
static	char* g_SelectButtonTextureName3 = (char*)"data\\texture\\button3.png";//テクスチャファイルパス
static	char* g_SelectButtonTextureName4 = (char*)"data\\texture\\button4.png";//テクスチャファイルパス
static	char* g_SelectButtonTextureName5 = (char*)"data\\texture\\buttonShop.png";//テクスチャファイルパス
static	char* g_SelectButtonTextureName6 = (char*)"data\\texture\\buttonSelect.png";//テクスチャファイルパス

STAGESELECTBG* SS;

SELECTBUTTON  SB[STEGE_MAX];


int	TextureNoSS = 0;



int stageslect_Replica; //セレクト番号超過の阻止用

HRESULT InitStageSelect()
{
	PlayBGM(Select, 1.0f);

	{
		//セレクト画面の背景
		SS = new STAGESELECTBG;
		
		SS->Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
		SS->Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
		SS->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		SS->Rotate = 0;
		SS->Stageselect = 1;
		SS->SelectCount = 0;
		SS->SelectFlag = false;

		TextureNoSS= LoadTexture(g_StageSelectTextureName);
		if (TextureNoSS == -1) {
			//読み込みエラー
			exit(999);
		}
	}
	
	
	for (int i = 0; i < STEGE_MAX; i++)
	{
		int yoko = 1 + (i % 3);
		int tate = 1 + (i / 3);

		SB[i].Position = D3DXVECTOR2(240 * yoko, 180 * tate);
		SB[i].Size = D3DXVECTOR2(200, 100);
		SB[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		SB[i].Rotate = 0;

		SB[i].TextureNoSB = LoadTexture(g_SelectButtonTextureName);

	}
	SB[0].TextureNoSB = LoadTexture(g_SelectButtonTextureName);
	SB[1].TextureNoSB = LoadTexture(g_SelectButtonTextureName2);
	SB[2].TextureNoSB = LoadTexture(g_SelectButtonTextureName3);
	SB[3].TextureNoSB = LoadTexture(g_SelectButtonTextureName4);
	SB[4].TextureNoSB = LoadTexture(g_SelectButtonTextureName5);
	SB[5].TextureNoSB = LoadTexture(g_SelectButtonTextureName6);


	
	return S_OK;
}
void UninitStageSelect()
{

	StopS();
	if (SS)
	{
		delete SS;
		SS = NULL;
	}
	
	
	
	
}
void UpdateStageSelect()
{
	
	//==============================================================
	//ステージセレクトの処理
	{
		if ((Keyboard_TriggerKeyDown(KK_RIGHT) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_RIGHT)) && SS->SelectFlag == false)//右ボタン
		{
			stageslect_Replica = SS->Stageselect + 1;
			SS->SelectFlag = true;
			PlayEffect(Tap, 1.0f);

		}
		else if ((Keyboard_TriggerKeyDown(KK_DOWN) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_DOWN)) && SS->SelectFlag == false)//下ボタン
		{
			stageslect_Replica = SS->Stageselect + STEGE_MAX / 2;
				SS->SelectFlag = true;
			PlayEffect(Tap, 1.0f);
		}
		else if ((Keyboard_TriggerKeyDown(KK_LEFT) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_LEFT)) && SS->SelectFlag == false)//左ボタン
		{
			stageslect_Replica = SS->Stageselect - 1;
				SS->SelectFlag = true;
			PlayEffect(Tap, 1.0f);
		}
		else if ((Keyboard_TriggerKeyDown(KK_UP) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_UP)) && SS->SelectFlag == false)//上ボタン
		{
			stageslect_Replica = SS->Stageselect - STEGE_MAX / 2;
				SS->SelectFlag = true;
			PlayEffect(Tap, 1.0f);
		}

		if (stageslect_Replica >= 0 && stageslect_Replica < STEGE_MAX)//上限を上回らないように
		{
			SS->Stageselect = stageslect_Replica;
		}

		//===============================
	//セレクトの時の待機処理
		if (SS->SelectFlag == true)
		{
			SS->SelectCount++;
		}

		if (SS->SelectCount >= 10)
		{
			SS->SelectCount = 0;
			SS->SelectFlag = false;
		}


		//===========================================================
		//未セレクト画面の処理とグレーダウン処理
		{
			for (int i = 0; i < STEGE_MAX; i++)
			{
				SB[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//明るくする
			}

			SB[SS->Stageselect].Color = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);//グレーダウン

			
		}
	}


	//=============================================================
	//ステージ移行処理
	{
		if (Keyboard_TriggerKeyDown(KK_SPACE) || IsButtonTriggered(0, XINPUT_GAMEPAD_B))
		{
			switch (SS->Stageselect)
			{
			case 0:
				SetScene(SCENE_GAME);
				break;
			case 1:
				//ステージ２
				SetScene(SCENE_STAGE02);
				break;
			case 2:
				//ステージ３
				SetScene(SCENE_STAGE03);
				break;
			case 3:
				//ステージ4
				SetScene(SCENE_STAGE03);

				break;
			case 4:
				//武器ショップ
				SetScene(SCENE_SHOP);
				break;
			case 5:
				//スキルセット画面
				SetScene(SCENE_SKILL_SET);
			default:
				break;
			}
		}
	}




	
}
void DrawStageSelect()
{
	//========================================================================
	//ステージ背景表示
	{
		//テクスチャのセット
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextureNoSS));

		DrawSpriteColorRotate
		(
			SS->Position.x,
			SS->Position.y,
			SS->Size.x,
			SS->Size.y,
			SS->Rotate,
			SS->Color,
			0,
			1.0f,
			1.0f,
			1
		);
	}

	//==========================================================================
	//ステージセレクト用ボタン
	{

		for (int i = 0; i < STEGE_MAX; i++)
		{
			//テクスチャのセット
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(SB[i].TextureNoSB));

			DrawSpriteColorRotate
			(
				SB[i].Position.x,
				SB[i].Position.y,
				SB[i].Size.x,
				SB[i].Size.y,
				SB[i].Rotate,
				SB[i].Color,
				0,
				1.0f,
				1.0f,
				1
			);
		}
		
	}

}
