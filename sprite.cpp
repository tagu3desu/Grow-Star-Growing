
#include	"renderer.h"
#include	"main.h"


//========================
//マクロ定義
//=========================
#define		NUM_VERTEX (4)

//========================
//グローバル変数
//=========================
static	ID3D11Buffer		*g_VertexBufferTriangle = NULL;

//========================
//プロトタイプ宣言
//========================


//=================================================
//スプライト描画処理
//in
//	表示座標X, 表示座標Y, 横サイズ, 縦サイズ, 回転角度, カラー
//パターン番号、パターン横サイズ、パターン縦サイズ
//横に並ぶパターンの数
//=================================================
void	DrawSpriteColorRotate(float posx, float posy,
	int size_w, int size_h,
	float kakudo, D3DXCOLOR col,
	float PaternNo,
	float uv_w, float uv_h,
	int NumPatern)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//頂点バッファへの書き込み許可をもらう
	GetDeviceContext()->Map(g_VertexBufferTriangle, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//頂点構造体の型にポインター型を変換をする
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;


	//頂点 V0をセット
	vertex[0].Position = D3DXVECTOR3(-size_w / 2, -size_h / 2, 0.0f);
	vertex[0].Diffuse = col;	// D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	//頂点 V1をセット
	vertex[1].Position = D3DXVECTOR3(+size_w / 2, -size_h / 2, 0.0f);
	vertex[1].Diffuse = col;	// D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	//頂点 V2をセット
	vertex[2].Position = D3DXVECTOR3(-size_w / 2, +size_h / 2, 0.0f);
	vertex[2].Diffuse = col;	// D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
;
	//頂点 V3をセット
	vertex[3].Position = D3DXVECTOR3(+size_w / 2, +size_h / 2, 0.0f);
	vertex[3].Diffuse = col;	// D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);





	int		no = PaternNo;//整数値へ変換（小数点以下が切り落とされる）
	int     patan =
		(uv_w / (uv_w * uv_w)) * (uv_h / (uv_h * uv_h));


	



	if (PaternNo >= patan)//パターン番号が4以上になったら
	{	//
		PaternNo -= patan;//パターン番号を0へ戻す
	}
	

	//左上（LEFT-TOP）のUV座標を計算
	float	uv_left = (no % NumPatern) * uv_w;	//左上U座標
	float	uv_top = (no / NumPatern) * uv_h;	//左上V座標

	//テクスチャ座標を書き換える
	vertex[0].TexCoord = D3DXVECTOR2(uv_left, uv_top);	//LEFT-TOP
	vertex[1].TexCoord = D3DXVECTOR2(uv_left + uv_w, uv_top);	//RIGHT-TOP
	vertex[2].TexCoord = D3DXVECTOR2(uv_left, uv_top + uv_h);	//LEFT-BOTTOM
	vertex[3].TexCoord = D3DXVECTOR2(uv_left + uv_w, uv_top + uv_h);	//RIGHT-BOTTOM

	//度をラジアンへ変換
	float	rad = D3DXToRadian(kakudo);
	float	x, y;

	for (int i = 0; i < 4; i++)
	{
		x = vertex[i].Position.x * cosf(rad) - vertex[i].Position.y * sinf(rad);
		y = vertex[i].Position.y * cosf(rad) + vertex[i].Position.x * sinf(rad);

		vertex[i].Position.x = x + posx;
		vertex[i].Position.y = y + posy;
	}

	GetDeviceContext()->Unmap(g_VertexBufferTriangle, 0);//書き込み終了


	// 表示したいポリゴンの頂点バッファを設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferTriangle, &stride, &offset);
	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_VERTEX, 0);

}

//==================================
//スプライト初期化
//==================================
void	InitSprite()
{
	{// 頂点バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX;//頂点1個＊頂点数のサイズで作る
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferTriangle);
	}
}

//==================================
//スプライト終了処理
//==================================
void	UninitSprite()
{
	if (g_VertexBufferTriangle)
	{
		g_VertexBufferTriangle->Release();//使い終わったので解放する
		g_VertexBufferTriangle = NULL;
	}
}

