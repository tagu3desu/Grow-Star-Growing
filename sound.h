
#pragma once

#include <windows.h>
#include "xaudio2.h"


bool InitSound(HWND hWnd);//�T�E���h�̏�����
void UninitSound(void);//�T�E���h�̏I��

int LoadSound(char* pFilename);//�f�[�^�̃��[�h
void PlaySound(int index, int loopCount);//�f�[�^�̍Đ��A�t���O0��1��A-1�Ń��[�v�Đ�
void StopSound(int index);//�f�[�^�̍Đ���~


void StopSoundAll(void);//���ׂĂ̍Đ����~
void SetVolume(int index, float vol);//�{�����[���̕ύX


//�T�E���h�̒ǉ�
//1�@�R���g���[���Ɠ����^�C�~���O�ŏ��������I���������s��
//2�@�^�C�g���Ȃǂ̃V�[���̏������Ńf�[�^���[�h���Đ��J�n�iBGM�j
//�@�@�I�������ōĐ���~�iBGM)
//3�@�ʁE�����Ȃǂ��V�[���̏������Ń��[�h�̂��Ă����B
//�Đ��͂��ꂼ��̃^�C�~���O�ōs�����A���[�v��̓�Đ�����Ȃ��悤�ɒ��ӂ��K�v
//�@���l�Ƀ��[�h����������1��݂̂ɂȂ�l����