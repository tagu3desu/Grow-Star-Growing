/*==============================================================================

   スコア（数字表示関係）処理[score.h]
														 Author :	AT12G_25_髙橋建次
														 Date   :	2022_09_29
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"
#include "01_Scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class	SCORE: public Game
{
public:
	SCORE();		//コンストラクタ
	~SCORE();		//デストラクタ
	HRESULT InitGame(void);
	void UninitGame(void);
	void UpdateGame(void);
	void DrawGame(void);
	void AddScore(int input_score);
	int GetScore(void) const;		//現在のスコアを返す
	void SettingScore(D3DXVECTOR2(pos), float size, int diz, BOOL animation);	// 設定を変更する
private:
	/*	定数	*/
	static const int SCORE_MAX = 10;			//スコアの最大桁数
	//テクスチャ
	static const int MAX_SCORE_TEXTURE = 1;		//フィールド背景テクスチャの最大数

	/*	変数	*/
	D3DXVECTOR2		Position;		// 表示座標
	float			w, h;			// サイズ
	D3DXCOLOR		Color;			// 色
	float			Rotate;			// 角度
	int				number;			// 格納する数
	int				display_number;	// 表示する数
	int				dizit;			// 桁数
	int				type;			// 表示タイプ(0 : 全桁を表示 1: 表示桁数を変動させる)
	BOOL			anime;			// アニメーションする/しない
	BOOL			use;			// 使用する/しない
	//テクスチャ
	char* g_ScoreTextureName[MAX_SCORE_TEXTURE];	//テクスチャファイルパス
	int				TextureNoScore[MAX_SCORE_TEXTURE];		//テクスチャインデックス
	int				CurrentTexture;							//使用するテクスチャ番号
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


