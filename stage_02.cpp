#include "stage_02.h"
#include "progress.h"

#include "kirakira.h"
#include "Boss.h"
#include "enemy.h"
#include "tutorial.h"

BOOL Stage_02Use[15];

Stage_02 S02;

D3DXVECTOR2 pos02;

void Stage_02::InitEnemyflag()
{

	for (int i = 0; i < 15; i++) {
		Stage_02Use[i] = false; //初期化
	}
}


///=======================================================
//エネミーの出現タイミング＆場所の処理
void Stage_02::Pop_EnemyBOX()
{
	int x = Get_time() / 13;

	if (Stage_02Use[x] == false)//まだ出現していないなら
	{
		switch (x)
		{
		case 1:

			SetEnemy(1, 1, 960.0f, 100.0f);
			SetEnemy(1, 1, 960.0f, 500.0f);

			SetEnemy(1, 1, 1260.0f, 250.0f);

			SetEnemy(1, 1, 1560.0f, 200.0f);
			SetEnemy(1, 1, 1560.0f, 400.0f);

			SetEnemy(1, 1, 1580.0f, 500.0f);

			break;

		case 2://ホントは3

			SetEnemy(1, 1, 960.0f, 100.0f);
			SetEnemy(1, 1, 960.0f, 500.0f);

			SetEnemy(1, 1, 1260.0f, 250.0f);

			SetEnemy(1, 1, 1560.0f, 200.0f);
			SetEnemy(1, 1, 1560.0f, 400.0f);
			SetEnemy(1, 1, 1560.0f, 300.0f);

			break;

		case 3:

			SetEnemy(1, 1, 960.0f, 100.0f);
			SetEnemy(1, 1, 960.0f, 500.0f);

			SetEnemy(1, 1, 1040.0f, 200.0f);
			SetEnemy(1, 1, 1040.0f, 400.0f);

			SetEnemy(1, 1, 1120.0f, 250.0f);
			SetEnemy(1, 1, 1120.0f, 350.0f);

			break;


		case 4:

			SetEnemy(3, 1, 760.0f, 560.0f);
			SetEnemy(4, 1, 760.0f, 580.0f);
			SetEnemy(3, 1, 760.0f, 600.0f);
			SetEnemy(4, 1, 760.0f, -60.0f);
			SetEnemy(3, 1, 760.0f, -80.0f);
			SetEnemy(4, 1, 760.0f, -100.0f);

			break;

		case 5:

			SetEnemy(1, 1, 960.0f, 100.0f);

			SetEnemy(1, 1, 980.0f, 80.0f);
			SetEnemy(1, 1, 980.0f, 120.0f);

			SetEnemy(1, 1, 1000.0f, 100.0f);

			SetEnemy(1, 1, 1020.0f, 60.0f);
			SetEnemy(1, 1, 1020.0f, 140.0f);

			break;


		case 6:

			SetEnemy(1, 1, 960.0f, 250.0f);

			SetEnemy(1, 1, 980.0f, 250.0f);

			SetEnemy(1, 1, 1000.0f, 250.0f);

			SetEnemy(1, 1, 1020.0f, 250.0f);

			SetEnemy(1, 1, 1040.0f, 250.0f);

			SetEnemy(1, 1, 1080.0f, 250.0f);

			break;

		case 7:

			SetEnemy(1, 1, 960.0f, 250.0f);

			SetEnemy(1, 1, 1260.0f, 200.0f);
			SetEnemy(1, 1, 1260.0f, 300.0f);

			SetEnemy(1, 1, 1280.0f, 250.0f);
			SetEnemy(1, 1, 1280.0f, 350.0f);
			SetEnemy(1, 1, 1280.0f, 300.0f);

			break;

		case 8:

			SetEnemy(1, 1, 1160.0f, 90.0f);
			SetEnemy(1, 1, 1160.0f, 110.0f);
			SetEnemy(1, 1, 1160.0f, 130.0f);
			SetEnemy(1, 1, 1160.0f, 460.0f);
			SetEnemy(1, 1, 1160.0f, 480.0f);
			SetEnemy(1, 1, 1160.0f, 500.0f);

			break;

		case 9:

			SetEnemy(3, 1, 960.0f, 560.0f);

			SetEnemy(3, 1, 1000.0f, 580.0f);

			SetEnemy(3, 1, 1040.0f, 600.0f);

			SetEnemy(3, 1, 1080.0f, 620.0f);

			SetEnemy(3, 1, 1120.0f, 640.0f);

			SetEnemy(3, 1, 1160.0f, 660.0f);

			break;

		case 10:

			SetEnemy(4, 1, 960.0f, -60.0f);

			SetEnemy(4, 1, 1000.0f, -80.0f);

			SetEnemy(4, 1, 1040.0f, -100.0f);

			SetEnemy(4, 1, 1080.0f, -120.0f);

			SetEnemy(4, 1, 1120.0f, -140.0f);

			SetEnemy(4, 1, 1120.0f, -160.0f);

			break;

		case 11:

			SetEnemy(1, 1, 960.0f, 130.0f);

			SetEnemy(1, 1, 1000.0f, 90.0f);

			SetEnemy(1, 1, 1040.0f, 230.0f);

			SetEnemy(1, 1, 1080.0f, 150.0f);

			SetEnemy(1, 1, 1120.0f, 420.0f);

			SetEnemy(1, 1, 1160.0f, 390.0f);

			break;

		case 0:

			SetEnemy(1, 1, 960.0f, 270.0f);//真ん中
			Set_BG(1);

			break;
		default:
			break;
		}

		Stage_02Use[x] = true;//仕様したと宣言
	}



}


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ひな形

/*
case 0:


	break;
*/