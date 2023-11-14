#include "Enemy_PopALL.h"
#include "stage_01.h"
#include "stage_02.h"
#include "stage_03.h"
#include "stage_04.h"

#include "main.h"

#include "00_soundmain.h"

#include "progress.h"



Stage_BOX BOX;

Stage_00* stage[] = {new Stage_01, new Stage_02, new Stage_03, new Stage_04};

int SetStege = 0;


HRESULT  Stage_BOX::InitGame()
{


	switch (GetScene())
	{

	case SCENE_GAME:
		SetStege = 0;
		PlayBGM(stege_01, 1.0f);
		break;

	case SCENE_STAGE02:
		SetStege = 1;
		PlayBGM(stege_02, 1.0f);
		break;

	case SCENE_STAGE03:
		SetStege = 2;
		PlayBGM(stege_03, 1.0f);
		break;

	case SCENE_STAGE04:
		SetStege = 3;
		PlayBGM(stege_04, 1.0f);
		break;


	default:
		break;
	}

	stage[SetStege]->InitEnemyflag();

	
	return S_OK;
}

void Stage_BOX::UninitGame()
{

	StopS();

}

void Stage_BOX::UpdateGame()
{

		stage[SetStege]->Pop_EnemyBOX();


	
}

void Stage_BOX::DrawGame()
{

	


}
