#include "player_vs_enemy.h" //�v���C���[�ƃG�l�~�[�̓����蔻��

#include "kirakira.h"//�L���L��

#include "Boss.h"//�{�X�{��
#include "boss_parts.h"//�{�X�̕���
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
	//�X�R�A���l�����z�̐ݒ�
	int Score = GetData()->PlayerScore;
	SCORE* score = dynamic_cast<SCORE*>(Game_01_RESULT[1]);		//�_�E���L���X�g
	score->AddScore(Score);		//�X�R�A�f�[�^������
	score->SettingScore(D3DXVECTOR2(570.0f, 56.0f), 32.0f, 6, TRUE);

	SCORE* score_2 = dynamic_cast<SCORE*>(Game_01_RESULT[2]);		//�_�E���L���X�g
	score_2->AddScore(Score / 10);		//�������f�[�^������
	score_2->SettingScore(D3DXVECTOR2(570.0f, 165.0f), 32.0f, 6, TRUE);
	int c_money = GetData()->Money;					//���̏��������擾
	SetData(Score / 10 + c_money, -1, -1, -1);		//���������Z
	
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
	//�Z���N�g��ʂ�
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
