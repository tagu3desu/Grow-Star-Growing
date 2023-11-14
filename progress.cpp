#include "progress.h"
#include "sprite.h"
#include "texture.h"
#include "main.h"

#define PROGRESS_SIZE_W	(600.0f)
#define PROGRESS_SIZE_H	(80.0f)

#define	STAR_SIZE_W		(40.0f)
#define	STAR_SIZE_H		(40.0f)

#define	BOSS_SIZE_W		(1.0f)
#define	BOSS_SIZE_H		(1.0f)

Progress	g_Progress;
Progress	g_Star;
Progress	g_Boss;
STAGE		g_Stage = STAGE_00;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Progress::InitGame(void)
{
	g_Progress.pos = D3DXVECTOR2(SCREEN_WIDTH / 2.0f, 40.0f);
	g_Progress.size.x = PROGRESS_SIZE_W;
	g_Progress.size.y = PROGRESS_SIZE_H;
	g_Progress.rot = 0.0f;
	g_Progress.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Progress.texNo = LoadTexture((char*)"data\\texture\\kk_SINKOU.png");
	g_Progress.use = true;

	g_Progress.time = 0;//時間計測


	g_Star.pos.x = g_Progress.pos.x - (PROGRESS_SIZE_W - 100) / 2.0f;
	g_Star.pos.y = 30.0f;
	g_Star.size.x = STAR_SIZE_W;
	g_Star.size.y = STAR_SIZE_H;
	g_Star.rot = 0.0f;
	g_Star.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Star.texNo = LoadTexture((char*)"data\\texture\\kakurin_sinnkou star.png");
	g_Star.use = true;

	g_Boss.pos.x = g_Progress.pos.x + (PROGRESS_SIZE_W - 100) / 2.0f;
	g_Boss.pos.y = g_Progress.pos.y;
	g_Boss.size.x = BOSS_SIZE_W;
	g_Boss.size.y = BOSS_SIZE_H;
	g_Boss.rot = 0.0f;
	g_Boss.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Boss.texNo = LoadTexture((char*)"data\\texture\\インベーダー.png");
	g_Boss.use = true;

	
	Set_stage(GetScene());



	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Progress::UninitGame(void)
{

}


//=============================================================================
// 更新処理
//=============================================================================
void Progress::UpdateGame(void)
{



	//================================================
	//ボスステージへの移行処理

	if (g_Star.pos.x >= g_Boss.pos.x)//ボスより右なら
	{
		switch (g_Stage)
		{
		case STAGE_00:
			break;

		case STAGE_01:
			SetScene(SCENE_BOSS01);
			break;

		case STAGE_02:
			SetScene(SCENE_BOSS02);
			break;

		case STAGE_03:
			SetScene(SCENE_BOSS03);
			break;

		case STAGE_04:
			SetScene(SCENE_BOSS04);
			break;
		}
	}

	g_Star.pos.x += 500.0f / (g_Star.time * 60);//一定時間ごとに右へ

	g_Progress.time++;
}

//=============================================================================
// 描画処理
//=============================================================================
void Progress::DrawGame(void)
{
	//ゲージ
	if (g_Progress.use == true)
	{
		//テクスチャのセット
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Progress.texNo));
		
		//描画
		DrawSpriteColorRotate
		(
			g_Progress.pos.x,
			g_Progress.pos.y,
			g_Progress.size.x,
			g_Progress.size.y,
			g_Progress.rot,
			g_Progress.color,
			1.0f,
			1.0f,
			1.0f,
			1
		);
	}

	//スター
	if (g_Star.use == true)
	{
		//テクスチャのセット
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Star.texNo));

		//描画
		DrawSpriteColorRotate
		(
			g_Star.pos.x,
			g_Star.pos.y,
			g_Star.size.x,
			g_Star.size.y,
			g_Star.rot,
			g_Star.color,
			1.0f,
			1.0f,
			1.0f,
			1
		);
	}

	//ボス
	if (g_Boss.use == true)
	{
		//テクスチャのセット
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Boss.texNo));

		//描画
		DrawSpriteColorRotate
		(
			g_Boss.pos.x,
			g_Boss.pos.y,
			g_Boss.size.x,
			g_Boss.size.y,
			g_Boss.rot,
			g_Boss.color,
			1.0f,
			1.0f,
			1.0f,
			1
		);
	}
}

void Set_BOSSstage(STAGE stage_num)
{
	g_Stage = stage_num;

	switch (g_Stage)
	{
	case STAGE_00:
		break;

	case STAGE_01:
		g_Star.time = 150.0f;
		break;

	case STAGE_02:
		g_Star.time = 150.0f;
		break;

	case STAGE_03:
		g_Star.time = 150.0f;
		break;

	case STAGE_04:
		g_Star.time = 200.0f;
		break;
	}
}


//わからんかったけどたぶんこんな感じやろ
void Set_stage(SCENE scene)
{
	switch (scene)
	{
	case SCENE_NONE:
		break;

	case SCENE_GAME:
		g_Stage = STAGE_01;
		g_Star.time = 150.0f;
		break;

	case SCENE_STAGE02:
		g_Stage = STAGE_02;
		g_Star.time = 150.0f;
		break;

	case SCENE_STAGE03:
		g_Stage = STAGE_03;
		g_Star.time = 150.0f;
		break;

	case SCENE_STAGE04:
		g_Stage = STAGE_04;
		g_Star.time = 200.0f;
		break;


	
	}
	/*
	switch (scene)
	{
	case SCENE_STAGE00:
		break;
	case SCENE_STAGE01:
		g_Star.time = 3.0f;
		break;
	case SCENE_STAGE02:
		g_Star.time = 150.0f;
	}
	//*/
}

int Get_time()//秒計測（60fで1秒）
{
	return g_Progress.time / 60;//1秒に変換
}