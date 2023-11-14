#pragma once
#include "01_Scene.h" 
#include "player.h"
#include "enemy.h"

class PlayerVSEnemy : public Game
{
public:
	PlayerVSEnemy();
	~PlayerVSEnemy();
	HRESULT InitGame(void);
	void UninitGame(void);
	void UpdateGame(void);
	void DrawGame(void);

private:
	/*	定数	*/
	static const int INVINCIBLE_TIME_MAX = 180;		//プレイヤーの無敵時間の最大値(3秒間)
	static const int DAMAGE = 2;					//当たった時のダメージ量

	/*	変数	*/
	int	invincible_time = 0;	//プレイヤーの無敵時間
};


