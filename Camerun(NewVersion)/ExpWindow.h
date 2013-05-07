//*============================================================================
//ExpWindow.h
//*============================================================================
//[history]
//	08/12/13　作成
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Sprite.h"
#include "FontSprite.h"

//=============================================================================
//variable
//=============================================================================
class CResourceManager;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	ウィンドウ描画用オブジェクト
//=============================================================================
class CExpWindow :	public CSprite
{
	private:
	
		CFontSprite *m_pTrlFontSpr;//チュートリアル用フォント
		Uint32 m_StrCount;//文字列カウント
		Uint32 m_OldStrCount;//文字列カウントバックアップ
	
	public:
	
		CExpWindow( const char *pName, Math::Vector2D vPos );//コンストラクタ
		~CExpWindow(void);//デストラクタ
		
		void Init();//初期化
		
		/*読み込み*/
		void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );
		
		/*レンダリング*/
		void Rendering();
		
		/*処理*/
		void Exec();
		
		/*チュートリアル文の設定*/
		void SetTutorialExp( File::IFileManager *pFileMgr );
		
		/*文字列カウントの増加*/
		//[input]
		//	dt:増加させる幅
		void AddStrCount( int dt )
		{
			m_StrCount += dt;
		}
		
		//文字列カウントの設定
		void SetStrCount( Uint32 count )
		{
			m_StrCount = count;
		}
		
		//文字列カウント(バックアップ)の設定
		void SetOldStrCount( Uint32 count )
		{
			m_OldStrCount = count;
		}
		
	public:
	
		/*文字列カウントの取得*/
		Uint32 GetStrCount() const
		{
			return m_StrCount;
		}
		
		//バックアップ用文字列カウントの取得
		Uint32 GetInitStrCount() const
		{
			return m_OldStrCount;
		}

		
		/*チュートリアルフォントの取得*/
		CFontSprite *GetTrlFont() const
		{
			return m_pTrlFontSpr;
		}
		
		/*現在の文字列の取得*/
		string GetNowString() const
		{
			return m_pTrlFontSpr->GetVecString().at( m_StrCount );
		}
		
	
	
		
};
