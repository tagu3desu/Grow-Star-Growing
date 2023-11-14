/*==============================================================================

   プレイヤーバレットとエネミーの当たり判定処理 [p_bullet_vs_enemy.h]
														 Author :	AT12G_25_髙橋建次
														 Date   :	2022_12_1
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#include "01_Scene.h" 
#include "player.h"
#include "enemy.h"

class P_BulletVSEnemy : public Game
{
public:
	P_BulletVSEnemy();
	~P_BulletVSEnemy();
	HRESULT InitGame(void);
	void UninitGame(void);
	void UpdateGame(void);
	void DrawGame(void);

private:
	/*	定数	*/

	/*	変数	*/
};


