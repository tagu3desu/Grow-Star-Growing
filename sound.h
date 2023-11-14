
#pragma once

#include <windows.h>
#include "xaudio2.h"


bool InitSound(HWND hWnd);//サウンドの初期化
void UninitSound(void);//サウンドの終了

int LoadSound(char* pFilename);//データのロード
void PlaySound(int index, int loopCount);//データの再生、フラグ0で1回、-1でループ再生
void StopSound(int index);//データの再生停止


void StopSoundAll(void);//すべての再生を停止
void SetVolume(int index, float vol);//ボリュームの変更


//サウンドの追加
//1　コントローラと同じタイミングで初期化＆終了処理を行う
//2　タイトルなどのシーンの初期化でデータロード＆再生開始（BGM）
//　　終了処理で再生停止（BGM)
//3　玉・爆発などもシーンの初期化でロードのしておく。
//再生はそれぞれのタイミングで行うが、ループ後の二再生されないように注意が必要
//　同様にロードも初期化の1回のみになる様注意