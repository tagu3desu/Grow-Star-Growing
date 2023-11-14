#include "main.h"
#include "01_Scene.h"

//================================
//�}�N����`
//================================
//#define		KIRAKIRA_MAX		(3)		//�ő吔
//#define		KIRAKIRA_SPEED	 (10.0f)	//�ړ����x
//#define		KIRAKIRA_SIZE_W	(40)	
//#define		KIRAKIRA_SIZE_H	(40)	
//#define		KIRAKIRA_ANIME_MAX (1)

static const int KIRAKIRA_SIZE_W = 40;
static const int KIRAKIRA_SIZE_H = 40;
static const int KIRAKIRA_MAX = 30;
static const float KIRAKIRA_MOVE = 2.0f;

//�\���̒�`
class KIRAKIRA :public Game
{
public:
	virtual HRESULT InitGame();	//������
	virtual void	UninitGame();//�I������
	virtual void	UpdateGame();//�X�V����
	virtual void    DrawGame();//�`�揈��


	bool		Use;	//�g�p���t���O

	D3DXVECTOR2 Pos;	//�\�����W
	D3DXVECTOR2 Size;	//�T�C�Y
	float		Rot;	//��]�p�x

	int			AnimePatern;	//�A�j���[�V�����p�^�[��
	int			Texno;	//�e�N�X�`���ԍ�

	int			countK;	   //���X�|�[���܂ł̎���

	D3DXVECTOR2 collision_size;   //�����蔻��p�T�C�Y


	//float			AnimeSpeed;	//�A�j���[�V�����X�s�[�h
};


//================================
//�v���g�^�C�v�錾
//================================



void   AgeinInitKirakira(int num);	//�ēx������
void Kirakira_bone(D3DXVECTOR2 Epos, int bone_ster);//�G�l�~�[�̃|�W�V�������擾����, �������鐯�̐�

void player_get_kirakira(int num);//�v���C���[���L���L���ƐڐG�����Ƃ��̏���

KIRAKIRA* GetKirakira();					//�\���̂̐擪�|�C���^���擾