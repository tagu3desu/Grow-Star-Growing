#pragma once
#include "01_Scene.h"

#include"polygon.h"
#include"renderer.h"
#include "texture.h"
//#include"main.h"
/*==============================================================================

   フィールド処理 [field.h]		プロトタイプ版
														 Author :	髙橋建次
														 Date   :	2022_10_27
--------------------------------------------------------------------------------

==============================================================================*/

//*****************************************************************************
// クラス定義
//*****************************************************************************
class FIELD : public Game
{
public:
	FIELD();					//コンストラクタ
	~FIELD();					//デストラクタ
	void UninitGame();
	void UpdateGame();
	void DrawGame();
	HRESULT InitGame();
	void SetFieldSpeed(float speed);		//フィールドのスクロール速度を設定する関数	引数：float speed (スクロール速度)
private:
	/*	定数	*/
	//テクスチャ
	static const int MAX_FIELD_TEXTURE = 2;		//フィールド背景テクスチャの最大数
	//BGM
	static const int MAX_FIELD_BGM = 1;			//フィールドBGMの最大数

	/*	変数	*/
	D3DXVECTOR3		Position;	//表示座標
	D3DXVECTOR2		Size;		//サイズ
	D3DXCOLOR		Color;		//色
	float			Rotate;		//角度
	float			Speed;		//スクロール速度(基本的に数値はマイナス～0)
	//テクスチャ
	char* g_FieldTextureName[MAX_FIELD_TEXTURE];	//テクスチャファイルパス
	int				TextureNoField[MAX_FIELD_TEXTURE];		//テクスチャインデックス
	int				CurrentTexture;							//使用するテクスチャ番号
	//BGM
	char* g_FieldBGMName[MAX_FIELD_BGM];			//BGMファイルパス
	int				mainBGM[MAX_FIELD_BGM];					//BGMインデックス
	int				CurrentBGM;								//使用するBGM
};
