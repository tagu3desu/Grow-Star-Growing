
#include "main.h"
#include "00_soundmain.h"
#include "sound.h"


int EffectBox[20];

int BGMBox[20];

void initSound()
{
	EffectBox[0] = LoadSound((char*)"data\\SE\\shot000.wav");
	EffectBox[1] = LoadSound((char*)"data\\BGM\\効果音\\タップ音_01.wav");
	EffectBox[2] = LoadSound((char*)"data\\BGM\\効果音\\ポップなドボン！_01.wav");
	EffectBox[3] = LoadSound((char*)"data\\BGM\\効果音\\OKオン.wav");
	EffectBox[4] = LoadSound((char*)"data\\BGM\\効果音\\LAPUTA_alert_01.wav");



	BGMBox[0] = LoadSound((char*)"data\\BGM\\00_タイトル.wav");
	BGMBox[1] = LoadSound((char*)"data\\BGM\\01_ステージ.wav");
	BGMBox[2] = LoadSound((char*)"data\\BGM\\02_ステージ.wav");
	BGMBox[3] = LoadSound((char*)"data\\BGM\\03_ステージ.wav");
	BGMBox[4] = LoadSound((char*)"data\\BGM\\04_ステージ.wav");

	BGMBox[5] = LoadSound((char*)"data\\BGM\\01_BOSS.wav");
	BGMBox[6] = LoadSound((char*)"data\\BGM\\02_BOSS.wav");
	BGMBox[7] = LoadSound((char*)"data\\BGM\\03_BOSS.wav");
	BGMBox[8] = LoadSound((char*)"data\\BGM\\04_BOSS.wav");

	BGMBox[9] = LoadSound((char*)"data\\BGM\\05_セレクト.wav");
}



//効果音の集合
void PlayEffect(Effect num, float vol)//再生するエフェクト、ボリューム
{
	SetVolume(EffectBox[num], vol);
	PlaySound(EffectBox[num], 0);//サウンド再生
}

void PlayBGM(BGM num, float vol) {
	SetVolume(BGMBox[num], vol);
	PlaySound(BGMBox[num], -1);//サウンド再生
}

void StopS()
{
	StopSoundAll();
}
