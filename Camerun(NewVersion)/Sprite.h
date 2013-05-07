//*============================================================================
//Sprite.h
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
#include "draw2dobject.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	スプライト描画用オブジェクト
//=============================================================================
class CSprite :	public CDraw2DObject
{
	private:
	
	protected:
	
		Selene::Renderer::ITexture *m_pTex;//テクスチャ用ハンドル
		Selene::Renderer::Object::ISprite2D *m_pSpr;//スプライト用ハンドル
	
	protected:
	
		Math::Point2DI m_DivNum;//分割数
		Math::Point2DI m_Anim;//アニメID
	
		Math::Point2DF m_fSize;//画像サイズ
		
		Math::Rect2DF m_DstRect;//描画先矩形
		Math::Rect2DF m_SrcRect;//描画元矩形
				
		Sint32 m_AnimTime;//アニメーション時間
		Sint32 m_AnimCount;//アニメーションカウンタ
		
		Math::Rect2DF m_HitRect;//当たり判定用矩形
		
		bool m_IsAnim;//アニメーションさせるか
		
	public:
	
		CSprite( const char *pName, Math::Vector2D vPos );//コンストラクタ
		CSprite( const char *pName, Math::Vector2D vPos, Math::Point2DI DivNum );//コンストラクタ
		~CSprite(void);//デストラクタ
		
		virtual void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );//ファイル読み込み

		void Init(){};//初期化
		void Exec();//処理
		void Rendering();//レンダリング
		void Draw();//描画
		
		void DrawGrayScale( Renderer::IRender *pRender );//グレースケール描画
		
		void CreateSprite( Renderer::IRender *pRender, Uint32 Num );//スプライトの生成 
		
		void AddRef();//参照カウンタの増加
		
		void SetAnimation();//アニメーションの設定
		
	/*Set系*/
	public:
		
		/*テクスチャハンドルの設定*/
		void SetTexture( Renderer::ITexture *pTex )
		{
			m_pTex = pTex;
		}
		
		//分割数の設定	
		void SetDivNum( Math::Point2DI divnum )
		{
			m_DivNum = divnum;
			
			m_fSize.x = toF( m_pTex->GetOriginalSize().x / divnum.x );
			m_fSize.y = toF( m_pTex->GetOriginalSize().y / divnum.y );
			
		}
		
		/*X方向分割数の設定*/
		void SetDivNumX( int x )
		{
			SetDivNum( Math::Point2DI( x, m_DivNum.y ) );
		}
		
		/*Y方向分割数の設定*/
		void SetDivNumY( int y )
		{
			SetDivNum(  Math::Point2DI( m_DivNum.x, y ) );
		}
		
		//アニメーションIDの設定
		void SetAnimID( Math::Point2DI anim )
		{
			m_Anim = anim;
		}
		
		//アニメーションID(X座標)の設定
		void SetAnimXID( int x )
		{
			SetAnimID( Math::Point2DI( x, m_Anim.y ) );
		}
		
		//アニメーションID(Y座標)の設定
		void SetAnimYID( int y )
		{
			SetAnimID( Math::Point2DI( m_Anim.x, y ) );
		}
		
		/*画像サイズの設定*/
		void SetGraphSize( Math::Point2DF Size )
		{
			m_fSize = Size;
		}
		
		/*アニメーションフラグの設定*/
		void SetAnimFlag( bool flag )
		{
			m_IsAnim = flag;
		}
		
		/*描画先矩形の設定*/
		void SetDstRect( Math::Rect2DF Dst )
		{
			m_DstRect = Dst;
		}
		
		/*描画元矩形の設定*/
		void SetSrcRect( Math::Rect2DF Src )
		{
			m_SrcRect = Src;
		}
		
	/*Get系*/
	public:

		//テクスチャ用ハンドルの取得
		Selene::Renderer::ITexture *GetTexture() const
		{
			return m_pTex;
		}
		
		//スプライト用ハンドルの取得
		Selene::Renderer::Object::ISprite2D *GetSprite() const
		{
			return m_pSpr;
		}
		
		/*画像サイズの取得*/
		Math::Point2DF GetSize() const
		{
			return m_fSize;
		}
		
		/*当たり判定矩形の取得*/
		Math::Rect2DF GetHitRect() const
		{
			return m_HitRect;
		}
		
		//アニメIDの取得
		Math::Point2DI GetAnimID() const
		{
			return m_Anim;
		}
		
};
