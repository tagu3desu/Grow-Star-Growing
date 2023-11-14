#include "main.h"
#include "01_Scene.h"

//================================
//マクロ定義
//================================
//#define		KIRAKIRA_MAX		(3)		//最大数
//#define		KIRAKIRA_SPEED	 (10.0f)	//移動速度
//#define		KIRAKIRA_SIZE_W	(40)	
//#define		KIRAKIRA_SIZE_H	(40)	
//#define		KIRAKIRA_ANIME_MAX (1)

static const int KIRAKIRA_SIZE_W = 40;
static const int KIRAKIRA_SIZE_H = 40;
static const int KIRAKIRA_MAX = 30;
static const float KIRAKIRA_MOVE = 2.0f;

//構造体定義
class KIRAKIRA :public Game
{
public:
	virtual HRESULT InitGame();	//初期化
	virtual void	UninitGame();//終了処理
	virtual void	UpdateGame();//更新処理
	virtual void    DrawGame();//描画処理


	bool		Use;	//使用中フラグ

	D3DXVECTOR2 Pos;	//表示座標
	D3DXVECTOR2 Size;	//サイズ
	float		Rot;	//回転角度

	int			AnimePatern;	//アニメーションパターン
	int			Texno;	//テクスチャ番号

	int			countK;	   //リスポーンまでの時間

	D3DXVECTOR2 collision_size;   //当たり判定用サイズ


	//float			AnimeSpeed;	//アニメーションスピード
};


//================================
//プロトタイプ宣言
//================================



void   AgeinInitKirakira(int num);	//再度初期化
void Kirakira_bone(D3DXVECTOR2 Epos, int bone_ster);//エネミーのポジションを取得する, 生成する星の数

void player_get_kirakira(int num);//プレイヤーがキラキラと接触したときの処理

KIRAKIRA* GetKirakira();					//構造体の先頭ポインタを取得