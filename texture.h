//==============================
//�e�N�X�`���Ǘ�
//
//==============================
#pragma once

#include "renderer.h"

//==============================
//�e�N�X�`���̃��[�h
//in	�e�N�X�`���t�@�C�����̐擪�|�C���^
//out	���[�h�����e�N�X�`���n���h��
//							�񋟂��邽�߂̖��O
//==============================
int		LoadTexture(char* filename);

//==============================
//�e�N�X�`���̏I������
//���[�h�ς݂̃e�N�X�`����S�ĉ��
void	UninitTexture();

//===============================
//�w��̃e�N�X�`�������擾
//in	�g�p�������e�N�X�`���n���h��
//ID3D11ShaderResourceView**�Ł@�e�N�X�`����Ⴄ
//===============================
ID3D11ShaderResourceView** GetTexture(int index);//ID3D11ShaderResourceView**�̓|�C���^�ϐ��̃|�C���^
