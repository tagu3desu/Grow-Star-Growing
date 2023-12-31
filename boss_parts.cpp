/*==============================================================================

   GΜ[boss_parts.cpp]
														 Author :ϋό΄
														 Date   :2022/12/22
--------------------------------------------------------------------------------

==============================================================================*/

#include "boss_parts.h"
#include "sprite.h"
#include "texture.h"
#include "enemybullet.h"
#include "player.h"
#include "bullet.h"

#include "collision.h"

//======================
//}Nθ`
//======================
// 
//======================
//vg^CvιΎ
//======================
// 
//======================
//O[oΟ
//======================
 
static BOSS_PARTS g_BossParts[BOSS_PARTS_MAX]; //{XΚIuWFNg


//==========================
//ϊ»
//==========================
HRESULT BOSS_PARTS::InitGame()
{
	for (int i = 0; i < BOSS_PARTS_MAX; i++)
	{
		//eNX`[h
		g_BossParts[i].Texno = LoadTexture((char*)"data\\texture\\target_circle.png");

		//\’ΜΜϊ»
		g_BossParts[i].Pos.x = 0.0f;
		g_BossParts[i].Pos.y = 0.0f;
		g_BossParts[i].Use = false;
		g_BossParts[i].countE = 0;
		g_BossParts[i].FrameWait = 0;
		g_BossParts[i].bulletrate = 0;
		g_BossParts[i].BulletType = 0;
		g_BossParts[i].size.x = BOSS_PARTS_SIZE_W;
		g_BossParts[i].size.y = BOSS_PARTS_SIZE_H;
		g_BossParts[i].BossPartsNo = 1;
		g_BossParts[i].move = D3DXVECTOR2(0.0f, 0.0f);
		g_BossParts[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_BossParts[i].Rot = 0;
		g_BossParts[i].HP = 0;
		g_BossParts[i].BossPos = D3DXVECTOR2(0.0f, 0.0f);
		g_BossParts[i].tacklehit = false;
		g_BossParts[i].tacklecount = 0;
		
		

	}
	return S_OK;	//³νIΉ
}
//=============================
//IΉ
//=============================
void BOSS_PARTS::UninitGame()
{

}
//==============================
//XV
//==============================
void BOSS_PARTS::UpdateGame()
{
	for (int i = 0; i < BOSS_PARTS_MAX; i++)
	{
		
		if (g_BossParts[i].Use == true)	//{XΚͺtrueΜ
		{
			BossParts_damege_reaction(i);//{XΚͺobhΙ½ΑΔΘ’©©Δ©η
			
			if (g_BossParts[i].tacklehit == true)
			{
				g_BossParts[i].tacklecount++;
			}
			if (g_BossParts[i].tacklecount >= 60)
			{
				g_BossParts[i].tacklehit = false;
				g_BossParts[i].tacklecount=0;
			}

			g_BossParts[i].Rot += 2;

			//{XΚΜνή²ΖΙ­Λ·ιeπΟX
			switch (g_BossParts[i].BossPartsNo)
			{
			case 1:
				g_BossParts[i].bulletrate += 1.0f;
				if (((int)g_BossParts[i].bulletrate % 100) == 99)
				{
					Set_Enemybullet(g_BossParts[i].BulletType, GetPlayer()->Position, (g_BossParts[i].Pos + g_BossParts[i].BossPos));
				}
				break;
			default:
				g_BossParts[i].bulletrate += 1.0f;
				if (((int)g_BossParts[i].bulletrate % 100) == 99)
				{
					Set_Enemybullet(g_BossParts[i].BulletType, GetPlayer()->Position, (g_BossParts[i].Pos + g_BossParts[i].BossPos));
				}
				break;
			}
		}
	}
}
//================================
//`ζ
//================================
void BOSS_PARTS::DrawGame()
{
	for (int i = 0; i < BOSS_PARTS_MAX; i++)
	{


		if (g_BossParts[i].Use == true)	//{XΚͺtrueΜΜέ
		{
				//eNX`ΜZbg
				GetDeviceContext()->PSSetShaderResources(0, 1,
					GetTexture(g_BossParts[i].Texno));

				//XvCgΜ`ζ
				DrawSpriteColorRotate
				(
					g_BossParts[i].Pos.x + g_BossParts[i].BossPos.x,
					g_BossParts[i].Pos.y + g_BossParts[i].BossPos.y,
					g_BossParts[i].size.x,
					g_BossParts[i].size.y,
					g_BossParts[i].Rot,
					g_BossParts[i].color,	//Ζθ ¦ΈΜF
					0,	//p^[Τ
					1.0f,	//p^[Μ‘TCY
					1.0f,	//p^[ΜcTCY
					1		//p^[Μ‘Μ
				);
		}
	}
}
//================================
//\’ΜΜζͺΜ|C^πΤ·
//================================
BOSS_PARTS* GetBossParts(int num)
{
	return &g_BossParts[num];
}

//==========================================
//{XΚΜΔΡo΅Iπ
// ΐWX,ΐWY,HP,{XΜSΐW
//
//==========================================
int SetBossParts(float posx, float posy, int HP, D3DXVECTOR2 BOSSposs)
{
	for (int i = 0; i < BOSS_PARTS_MAX; i++)
	{
		if (g_BossParts[i].Use == false) {

			g_BossParts[i].Pos = D3DXVECTOR2(posx, posy);
			g_BossParts[i].HP = HP;
			g_BossParts[i].BossPos = BOSSposs;
			g_BossParts[i].BulletType = 1;
			g_BossParts[i].Use = true;
			return i;
		}
	}
}


//==============================================
//{XΜp[cΜcΆmF
//==============================================
bool Get_BossPartslivis()
{
	for (int i = 0; i < BOSS_PARTS_MAX; i++)
	{
		if (g_BossParts[i].Use == true) {//Ά«Δ’ιp[cͺκΒΕΰ κΞ

			return true;//’ιΖΤ·
		}
	}

	return false;
}


//==================================================
//{XΚΜ_[Wreaction
//==================================================

void BossParts_damege_reaction(int num)
{
	
	if (GetPlayer()->SizeUp == true && g_BossParts[num].tacklehit==false)
	{
		if (CollisionBB(GetPlayer()->Position, (g_BossParts[num].Pos + g_BossParts[num].BossPos),
			GetPlayer()->size, g_BossParts[num].size) == true)//½Α½η
		{
			//_[W
			g_BossParts[num].HP -= GetPlayer()->TackleDamege;
			g_BossParts[num].tacklehit = true;
			if (g_BossParts[num].HP <= 0)
			{
				g_BossParts[num].HP = 0;
				g_BossParts[num].Use = false;//Α·
			}

		}
	}
	else
	{
		for (int i = 0; i < MAX_BULLET; i++)//obhSΜπ©ι
		{
			if (GetBullet(i)->use == true)//gpσΤΕ
			{
				if (CollisionBB(GetBullet(i)->pos, (g_BossParts[num].Pos + g_BossParts[num].BossPos),
					GetBullet(i)->size, g_BossParts[num].size) == true)//½Α½η
				{
					//_[W
					g_BossParts[num].HP -= GetBullet(i)->damage;
					if (g_BossParts[num].HP <= 0)
					{
						g_BossParts[num].HP = 0;
						g_BossParts[num].Use = false;//Α·
					}
					GetBullet(i)->use = false;
					break;
				}
			}
		}
	}
	
	
}


