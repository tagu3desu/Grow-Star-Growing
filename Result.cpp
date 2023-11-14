#include "player_vs_enemy.h" //プレイヤーとエネミーの当たり判定

#include "kirakira.h"//キラキラ

#include "Boss.h"//ボス本体
#include "boss_parts.h"//ボスの部位
#include "score.h"
#include "field.h"
#include "Result.h"
#include "data.h"
Game* Game_01_RESULT[] = { new FIELD, new SCORE, new SCORE };


HRESULT	InitResultScene()
{
	for (int i = 0; i < MAX_RESULT_HEDDER; i++) {

		Game_01_RESULT[i]->InitGame();
	}
	//スコア＆獲得金額の設定
	int Score = GetData()->PlayerScore;
	SCORE* score = dynamic_cast<SCORE*>(Game_01_RESULT[1]);		//ダウンキャスト
	score->AddScore(Score);		//スコアデータを入れる
	score->SettingScore(D3DXVECTOR2(570.0f, 56.0f), 32.0f, 6, TRUE);

	SCORE* score_2 = dynamic_cast<SCORE*>(Game_01_RESULT[2]);		//ダウンキャスト
	score_2->AddScore(Score / 10);		//所持金データを入れる
	score_2->SettingScore(D3DXVECTOR2(570.0f, 165.0f), 32.0f, 6, TRUE);
	int c_money = GetData()->Money;					//元の所持金を取得
	SetData(Score / 10 + c_money, -1, -1, -1);		//所持金加算
	
	return S_OK;
}

void	UninitResultScene()
{
	for (int i = 0; i < MAX_RESULT_HEDDER; i++) {

		Game_01_RESULT[i]->UninitGame();

	}
}

void	UpdateResultScene()
{
	for (int i = 0; i < MAX_RESULT_HEDDER; i++) {
		Game_01_RESULT[i]->UpdateGame();
	}
	//セレクト画面へ
	if (Keyboard_TriggerKeyDown(KK_SPACE) || IsButtonTriggered(0, XINPUT_GAMEPAD_B)) {
		SetScene(SCENE_SELECT);
	}
}

void	DrawResultScene()
{
	for (int i = 0; i < MAX_RESULT_HEDDER; i++) {

		Game_01_RESULT[i]->DrawGame();
	}
}
