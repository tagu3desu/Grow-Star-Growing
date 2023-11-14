/*==============================================================================

   全体データ管理処理[data.h]
												 Author :	AT12G_25_髙橋建次
												 Date   :	2023_01_19
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#include "main.h"

//グローバル変数
static const int	WEAPON_MAX = 4;		//購入可能な武器の最大数
static const int	SKILL_TYPE_MAX = 3;	//セットするスキルの最大数

HRESULT InitData();
void UninitData();
void UpdateData();
void DrawData();

typedef struct
{
	//ゲーム全体の共有データ
	int		Money;					//プレイヤーの所持金
	int		ClearedStage;			//クリアしたステージ
	BOOL	Ownership[WEAPON_MAX];	//ショットの購入状況
	int		SkillType[3];			//現在セットされているショット

	//ステージごとのデータ
	int		Energy;					//キラキラの残量
	int		PlayerScore;				//獲得スコア
}G_DATA;

void SetData(int money, int cleared_stage, int energy, int player_score);//お金,クリアしたステージ, エナジー, スコア
void SetWeaponData(BOOL ownership[]);
void SetSkillType(BOOL skill_type[SKILL_TYPE_MAX]);
void ResetStageData();
G_DATA* GetData();

