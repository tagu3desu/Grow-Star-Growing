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
	/*	�萔	*/
	static const int INVINCIBLE_TIME_MAX = 180;		//�v���C���[�̖��G���Ԃ̍ő�l(3�b��)
	static const int DAMAGE = 2;					//�����������̃_���[�W��

	/*	�ϐ�	*/
	int	invincible_time = 0;	//�v���C���[�̖��G����
};


