//*============================================================================
//MiniMap.h
//*============================================================================
//[history]
//	08/03/19　作成
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Sprite.h"
#include "character.h"


//=============================================================================
//class
//=============================================================================
//[Desc]
//	ミニマップ描画用オブジェクト
//=============================================================================
class CMiniMap :	public CSprite
{
	private:
	
		Math::Point2DF m_Scroll;//スクロール座標
		Math::Point2DF m_MapScroll;//マップスクロール
		Math::Point2DF m_DrawSize;//描画サイズ
		
		Renderer::IRender *m_pRender;//レンダラー用デバイス
	
	public:
	
		CMiniMap( const char *pName, Math::Vector2D vPos );//コンストラクタ
		~CMiniMap();//デストラクタ

		void Init(){};//初期化
		void Exec();//処理
		void Rendering();//レンダリング
		void Move( CCharacter *pChara );//スクロール
		
		void ScrollAdjust();//スクロール補正
		
		void SetMiniCharaPos( CCharacter *pChara, CSprite *pSpr, bool IsPlayer );//キャラクターのミニマップ位置の設定
		
	/*Set系*/
	public:
	
		/*レンダラーのセット*/
		void SetRenderer( Renderer::IRender *pRender )
		{
			m_pRender = pRender;
			pRender->AddRef();
		}
	
	/*Get系*/
	public:
	
		/*スクロール座標の取得*/
		Math::Point2DF GetScroll() const
		{
			return m_Scroll;
		}
		
		/*描画サイズの取得*/
		Math::Point2DF GetDrawSize() const
		{
			return m_DrawSize;
		}

		
		
};
