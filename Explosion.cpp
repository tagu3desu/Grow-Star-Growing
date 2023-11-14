#include "Explosion.h"
#include "main.h"
#include "sprite.h"

#include "00_soundmain.h"
//======================
//グローバル変数
//======================
EXPLOSION	g_Explosion[EXPLOSION_MAX];	//爆発構造体配列

//======================
//初期化
//======================
HRESULT EXPLOSION::InitGame()
{
	//テクスチャのロード
	int texno = LoadTexture((char*)"data\\TEXTURE\\fgh_BOOMkansei.png");
	//爆発構造体の初期化
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		g_Explosion[i].use = false;	//フラグを未使用にする
		g_Explosion[i].size.x = EXPLOSION_SIZE_W;	//横サイズ
		g_Explosion[i].size.y = EXPLOSION_SIZE_Y;	//縦サイズ
		g_Explosion[i].pos = D3DXVECTOR2(0, 0);	//表示座標
		g_Explosion[i].rot = 0.0f;
		g_Explosion[i].texNo = texno;	//テクスチャ番号
		g_Explosion[i].move = D3DXVECTOR2(0.0f, 0.0f);	//移動スピード
		g_Explosion[i].AnimePattern = 0;
		g_Explosion[i].AnimeSpeed = 0;
	}
	return S_OK;
}
//=============================
//終了処理
//=============================
void EXPLOSION::UninitGame()
{

}

//=============================
//更新処理
//=============================
void EXPLOSION::UpdateGame()
{
	//構造体を全て処理
	for (int i = 0; i < EXPLOSION_MAX; i++) {
		if (g_Explosion[i].use == true) {

			//座標の更新
			g_Explosion[i].pos += g_Explosion[i].move;


			//アニメーションの更新
			g_Explosion[i].AnimePattern += g_Explosion[i].AnimeSpeed;
			if (g_Explosion[i].AnimePattern > EXPLOSION_ANIME_MAX)
			{
				g_Explosion[i].use = false;
			}
		}
	}
}
//======================
//描画処理
//======================
void EXPLOSION::DrawGame()
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_Explosion[i].use == true) {
			//テクスチャのセット
			GetDeviceContext()->PSSetShaderResources(0, 1,
				GetTexture(g_Explosion[i].texNo));

			//スプライトの描画
			DrawSpriteColorRotate
			(
				g_Explosion[i].pos.x,
				g_Explosion[i].pos.y,
				g_Explosion[i].size.x,
				g_Explosion[i].size.y,
				g_Explosion[i].rot,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),//とりあえずの色
				(int)g_Explosion[i].AnimePattern,		//パターン番号
				1.0f / 4,	//パターンの横サイズ
				1.0f / 5,	//パターンの縦サイズ
				16		//パターン横の数
			);


		}

	}
}
//=========================
//構造体のポインタ取得
//=========================
EXPLOSION* GetExplosion()
{
	return &g_Explosion[0]; //return	g_Bullet;
}
//======================
//弾の発生
//
//in	発生座標、アニメーションスピード
//======================
void	SetExplosion(D3DXVECTOR2	pos, float animspeed)
{
	//構造体を全て調べる
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_Explosion[i].use == false)//未使用の構造体を見つける
		{
			g_Explosion[i].pos = pos;//発生座標
			g_Explosion[i].use = true;//使用中
			g_Explosion[i].AnimeSpeed = animspeed;//アニメーションスピード
			g_Explosion[i].AnimePattern = 0;//パターンをリセット

			return;					//一つ作ったら終了
		}
	}



}