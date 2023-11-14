#pragma once

void initSound();

void StopS();



enum Effect
{
	Ebullet, //0
	Tap,		 //1
	Bom,      //2
	OKvol,     //3
	Not
};

enum BGM
{
	Title,

	stege_01,
	stege_02,
	stege_03,
	stege_04,

	BOSS_001,
	BOSS_002,
	BOSS_003,
	BOSS_004,

	Select,

	Result


};
void PlayBGM(BGM num, float vol);
void PlayEffect(Effect num, float vol);//再生するエフェクト、ボリューム