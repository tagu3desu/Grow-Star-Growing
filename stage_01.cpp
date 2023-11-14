#include "stage_01.h"
#include "progress.h"

#include "kirakira.h"
#include "Boss.h"
#include "enemy.h"
#include "tutorial.h"

BOOL Stage_01Use[15];

Stage_01 S01;

D3DXVECTOR2 pos;

void Stage_01::InitEnemyflag()
{
	for (int i = 0; i < 15; i++) {
		Stage_01Use[i] = false; //������
	}
	
}


//=======================================================
//�G�l�~�[�̏o���^�C�~���O���ꏊ�̏���
void Stage_01::Pop_EnemyBOX()
{
	int x = Get_time() / 13;

	if (Stage_01Use[x] == false)//�܂��o�����Ă��Ȃ��Ȃ�
	{
		switch (x)
		{
		case 1:

			SetEnemy(1, 1, 960.0f, 270.0f);//�^��

			SetEnemy(1, 1, 1360.0f, 100.0f);//��
			SetEnemy(1, 1, 1360.0f, 400.0f);//��
			
			break;

		case 2:
			Set_BG(2);
			break;


		case 3://�z���g��3
			 pos = D3DXVECTOR2(960, 270);

			Kirakira_bone(pos, 20);
			

			break;

		case 4:

			//����
			SetEnemy(1, 1, 960.0f, 200.0f);//��
			SetEnemy(1, 1, 960.0f, 400.0f);//��

			//����
			SetEnemy(1, 1, 1260.0f, 100.0f);//��
			SetEnemy(1, 1, 1260.0f, 300.0f);//��
			SetEnemy(1, 1, 1260.0f, 500.0f);//��


			break;


		case 5:

			SetEnemy(3, 1, 760.0f, 560.0f);//�ォ��
			
			SetEnemy(4, 1, 840.0f, -80.0f);//������

			break;

		case 6:

			//�������̏W�c
			SetEnemy(3, 1, 760.0f, 560.0f);//1
			SetEnemy(3, 1, 780.0f, 580.0f);//2
			SetEnemy(3, 1, 800.0f, 600.0f);//3


			//�ォ�牺�̏W�c
			SetEnemy(4, 1, 820.0f, -60.0f);//1
			SetEnemy(4, 1, 840.0f, -80.0f);//2
			SetEnemy(4, 1, 860.0f, -100.0f);//3

			break;


		case 7:

			//1���
			SetEnemy(1, 1, 960.0f, 270.0f);

			//2���
			SetEnemy(1, 1, 1160.0f, 210.0f);//��
			SetEnemy(1, 1, 1160.0f, 330.0f);//��

			//3���
			SetEnemy(1, 1, 1360.0f, 150.0f);//��
			SetEnemy(1, 1, 1360.0f, 390.0f);//��

			//4���
			SetEnemy(1, 1, 1560.0f, 90.0f);//��
			SetEnemy(1, 1, 1560.0f, 450.0f);//��

			break;

		case 8:

			//2���
			SetEnemy(1, 1, 1160.0f, 210.0f);//��
			SetEnemy(1, 1, 1160.0f, 330.0f);//��

			//3���
			SetEnemy(1, 1, 1360.0f, 150.0f);//��
			SetEnemy(1, 1, 1360.0f, 390.0f);//��

			//4���
			SetEnemy(1, 1, 1560.0f, 90.0f);//��
			SetEnemy(1, 1, 1560.0f, 450.0f);//��

			break;

		case 9:

			//2���
			SetEnemy(1, 1, 1160.0f, 210.0f);//��
			SetEnemy(1, 1, 1160.0f, 330.0f);//��

			//3���
			SetEnemy(1, 1, 1360.0f, 150.0f);//��
			SetEnemy(1, 1, 1360.0f, 390.0f);//��

			//4���
			SetEnemy(1, 1, 1560.0f, 90.0f);//��
			SetEnemy(1, 1, 1560.0f, 450.0f);//��
			break;

		case 10:

			//2���
			SetEnemy(1, 1, 1160.0f, 210.0f);//��
			SetEnemy(1, 1, 1160.0f, 330.0f);//��

			//3���
			SetEnemy(1, 1, 1360.0f, 150.0f);//��
			SetEnemy(1, 1, 1360.0f, 390.0f);//��

			//4���
			SetEnemy(1, 1, 1560.0f, 90.0f);//��
			SetEnemy(1, 1, 1560.0f, 450.0f);//��
			break;

		case 11:

			//2���
			SetEnemy(1, 1, 1160.0f, 210.0f);//��
			SetEnemy(1, 1, 1160.0f, 330.0f);//��

			//3���
			SetEnemy(1, 1, 1360.0f, 150.0f);//��
			SetEnemy(1, 1, 1360.0f, 390.0f);//��

			//4���
			SetEnemy(1, 1, 1560.0f, 90.0f);//��
			SetEnemy(1, 1, 1560.0f, 450.0f);//��
			break;

		case 12:

				Set_BG(3);
				break;


		case 0:
		
			Set_BG(1);

			break;
		default:
			break;
		}

		Stage_01Use[x] = true;//�d�l�����Ɛ錾
	}



}


//��������������������������������������������������
//�ЂȌ`

/*
case 0:


	break;
*/