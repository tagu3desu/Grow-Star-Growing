#include "texture.h"


//=========================
//�}�N����`
//=========================
#define		MAX_TEXTURE_NUM		(100)	//���[�h���E��

//=========================
//�O���[�o���ϐ�
//=========================

//�e�N�X�`�����̃|�C���^�̔z��
static	ID3D11ShaderResourceView*	g_pTexture[MAX_TEXTURE_NUM];

//���[�h�ς݂̃e�N�X�`���̐�
//UINT = unsigned int
static	UINT	g_TextureIndex;

//�e�N�X�`���t�@�C�����̃o�b�t�@	MAX_TEXTURE_NUM=100�Ȃ̂ŉ摜��100������@�t�@�C����255�����܂�
static	char	g_TextureName[MAX_TEXTURE_NUM][256];

//===============================
//�w��̃e�N�X�`�������擾
//in	�g�p�������e�N�X�`���n���h��
//out	�e�N�X�`�����̃|�C���^�̓������|�C���^�ϐ��̃|�C���^
//===============================
ID3D11ShaderResourceView** GetTexture(int index)//ID3D11ShaderResourceView**�̓|�C���^�ϐ��̃|�C���^
{
	//�G���[�`�F�b�N
	if (index < 0)
	{
		return NULL;	//0����
	}
	if (index >= g_TextureIndex)
	{
		return NULL;	//���[�h���̃I�[�o�[
	}

	//�C���f�b�N�X�������ꏊ�̔z��̃|�C���^��Ԃ�
	return	&g_pTexture[index];
}
//==================================
//�e�N�X�`���̏I������
//���[�h�ς݂̃e�N�X�`����S�ĉ��
//==================================
void	UninitTexture()
{
	for (int i = 0; i < g_TextureIndex; i++)//�S��
	{
		if (g_pTexture[i] != NULL)		//�����f�[�^�������Ă���
		{
			g_pTexture[i]->Release();	//�������
			g_pTexture[i] = NULL;		//���������Ă���
		}

	}


}
//===================================
//in �e�N�X�`���t�@�C���̐擪�|�C���^
//out	���[�h�����e�N�X�`���n���h��
int LoadTexture(char* filename)
{
	//���łɓǂݍ��܂ꂽ�e�N�X�`�����𒲂ׂē�����
	//�e�N�X�`���������݂����ꍇ�́A�e�N�X�`������
	//�i�[���ꂽ�z��̔ԍ���Ԃ�

	for (int i = 0; i < g_TextureIndex; i++)
	{//�e�N�X�`�����̔�r
		if (strcmp(g_TextureName[i], filename) == 0)
		{
			return i;
		}
	}
	//�ǂݍ��ݐ������E�𒴂��Ă��Ȃ������`�F�b�N����
	if (g_TextureIndex == MAX_TEXTURE_NUM)
	{
		return -1;//�G���[�R�[�h��Ԃ�
	}

	//�e�N�X�`���̃��[�h
	HRESULT  hr = D3DX11CreateShaderResourceViewFromFile(
		GetDevice(),
		filename,
		NULL,
		NULL,
		&g_pTexture[g_TextureIndex],
		NULL
	);
	if (hr != S_OK)
	{
		return -1;//�ǂݍ��ݎ��s
	}

	//���[�h�����e�N�X�`�����̓o�^
	strcpy_s(g_TextureName[g_TextureIndex], 256, filename);

	int retIndex = g_TextureIndex; //�ꎞ�ޔ�
	g_TextureIndex++;              //���݂̐��𑝂₵�Ă���

	return retIndex;               //�ޔ����Ă����l��Ԃ�

}