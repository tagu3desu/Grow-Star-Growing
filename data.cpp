/*==============================================================================

   全体データ管理処理[data.cpp]
												 Author :	AT12G_25_髙橋建次
												 Date   :	2023_01_19
--------------------------------------------------------------------------------

==============================================================================*/
#include	"data.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
G_DATA	g_Data;

HRESULT InitData()
{
	//初回起動時のみ実行
	g_Data.Money = 99999;		//所持金
	g_Data.ClearedStage = 0;	//クリアしたステージ
	for (int i = 0; i < WEAPON_MAX; i++)
	{
		g_Data.Ownership[i] = FALSE;	//ショットの購入状況
	}
	
	g_Data.SkillType[0] = 0;			//0番目		通常弾
	g_Data.SkillType[1] = 1;			//1番目		三股砲弾
	g_Data.SkillType[2] = 3;			//2番目		回転弾
	
	//ステージごとに共有
	g_Data.Energy = 0;
	g_Data.PlayerScore = 0;

	return S_OK;	//正常終了
}

void UninitData()
{

}

void UpdateData()
{

}

void DrawData()
{

}

void SetData(int money, int cleared_stage, int energy, int player_score)
{
	if (money >= 0)
	{
		g_Data.Money = money;
	}

	if (cleared_stage >= 0)
	{
		g_Data.ClearedStage = cleared_stage;
	}

	if (energy >= 0)
	{
		g_Data.Energy = energy;
	}

	if (player_score)
	{
		g_Data.PlayerScore = player_score;
	}
}

void SetWeaponData(BOOL ownership[])
{
	for (int i = 0; i < WEAPON_MAX; i++)
	{
		g_Data.Ownership[i] = ownership[i];
	}
}

void SetSkillType(BOOL skill_type[SKILL_TYPE_MAX])
{
	for (int i = 0; i < SKILL_TYPE_MAX; i++)
	{
		g_Data.SkillType[i] = skill_type[i];
	}
}

void ResetStageData()
{
	g_Data.Energy = 0;
	g_Data.PlayerScore = 0;
}

//データ構造体のポインタを取得
G_DATA* GetData()
{
	return &g_Data;
}
