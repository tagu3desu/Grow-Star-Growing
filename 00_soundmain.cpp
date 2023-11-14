
#include "main.h"
#include "00_soundmain.h"
#include "sound.h"


int EffectBox[20];

int BGMBox[20];

void initSound()
{
	EffectBox[0] = LoadSound((char*)"data\\SE\\shot000.wav");
	EffectBox[1] = LoadSound((char*)"data\\BGM\\���ʉ�\\�^�b�v��_01.wav");
	EffectBox[2] = LoadSound((char*)"data\\BGM\\���ʉ�\\�|�b�v�ȃh�{���I_01.wav");
	EffectBox[3] = LoadSound((char*)"data\\BGM\\���ʉ�\\OK�I��.wav");
	EffectBox[4] = LoadSound((char*)"data\\BGM\\���ʉ�\\LAPUTA_alert_01.wav");



	BGMBox[0] = LoadSound((char*)"data\\BGM\\00_�^�C�g��.wav");
	BGMBox[1] = LoadSound((char*)"data\\BGM\\01_�X�e�[�W.wav");
	BGMBox[2] = LoadSound((char*)"data\\BGM\\02_�X�e�[�W.wav");
	BGMBox[3] = LoadSound((char*)"data\\BGM\\03_�X�e�[�W.wav");
	BGMBox[4] = LoadSound((char*)"data\\BGM\\04_�X�e�[�W.wav");

	BGMBox[5] = LoadSound((char*)"data\\BGM\\01_BOSS.wav");
	BGMBox[6] = LoadSound((char*)"data\\BGM\\02_BOSS.wav");
	BGMBox[7] = LoadSound((char*)"data\\BGM\\03_BOSS.wav");
	BGMBox[8] = LoadSound((char*)"data\\BGM\\04_BOSS.wav");

	BGMBox[9] = LoadSound((char*)"data\\BGM\\05_�Z���N�g.wav");
}



//���ʉ��̏W��
void PlayEffect(Effect num, float vol)//�Đ�����G�t�F�N�g�A�{�����[��
{
	SetVolume(EffectBox[num], vol);
	PlaySound(EffectBox[num], 0);//�T�E���h�Đ�
}

void PlayBGM(BGM num, float vol) {
	SetVolume(BGMBox[num], vol);
	PlaySound(BGMBox[num], -1);//�T�E���h�Đ�
}

void StopS()
{
	StopSoundAll();
}
