#include "Stage_04.h"
#include "progress.h"

#include "kirakira.h"
#include "Boss.h"
#include "enemy.h"
#include "tutorial.h"

BOOL Stage_04Use[15];

Stage_04 S04;

D3DXVECTOR2 pos04;

void Stage_04::InitEnemyflag()
{

	for (int i = 0; i < 15; i++) {
		Stage_04Use[i] = false; //初期化
	}
}


//=======================================================
//エネミーの出現タイミング＆場所の処理
void Stage_04::Pop_EnemyBOX()
{
	int x = Get_time() / 13;

	if (Stage_04Use[x] == false)//まだ出現していないなら
	{
		switch (x)
		{
		case 1:

			SetEnemy(1, 1, 960.0f, 270.0f);//真ん中

			SetEnemy(1, 1, 1360.0f, 100.0f);//上
			SetEnemy(1, 1, 1360.0f, 400.0f);//下
			
			break;

		case 2://ホントは3
			 pos04 = D3DXVECTOR2(960, 270);

			Kirakira_bone(pos04, 20);
			

			break;

		case 3:

			//一列目
			SetEnemy(1, 1, 960.0f, 200.0f);//上
			SetEnemy(1, 1, 960.0f, 400.0f);//下

			//二列目
			SetEnemy(1, 1, 1260.0f, 100.0f);//上
			SetEnemy(1, 1, 1260.0f, 300.0f);//中
			SetEnemy(1, 1, 1260.0f, 500.0f);//下


			break;


		case 4:

			SetEnemy(3, 1, 760.0f, 560.0f);//上から
			
			SetEnemy(4, 1, 840.0f, -80.0f);//下から

			break;

		case 5:

			//下から上の集団
			SetEnemy(3, 1, 760.0f, 560.0f);//1
			SetEnemy(3, 1, 780.0f, 580.0f);//2
			SetEnemy(3, 1, 800.0f, 600.0f);//3


			//上から下の集団
			SetEnemy(4, 1, 820.0f, -60.0f);//1
			SetEnemy(4, 1, 840.0f, -80.0f);//2
			SetEnemy(4, 1, 860.0f, -100.0f);//3

			break;


		case 6:

			//1列目
			SetEnemy(1, 1, 960.0f, 270.0f);

			//2列目
			SetEnemy(1, 1, 1160.0f, 210.0f);//上
			SetEnemy(1, 1, 1160.0f, 330.0f);//下

			//3列目
			SetEnemy(1, 1, 1360.0f, 150.0f);//上
			SetEnemy(1, 1, 1360.0f, 390.0f);//下

			//4列目
			SetEnemy(1, 1, 1560.0f, 90.0f);//上
			SetEnemy(1, 1, 1560.0f, 450.0f);//下

			break;

		case 7:


			break;

		case 8:


			break;
		case 0:
		
			SetEnemy(1, 1, 960.0f, 270.0f);//真ん中
			Set_BG(1);

			break;
		default:
			break;
		}

		Stage_04Use[x] = true;//仕様したと宣言
	}



}


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ひな形

/*
case 0:


	break;
*/