//*============================================================================
//Menu.h
//*============================================================================
//[history]
//	08/03/05　作成
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "FontSprite.h"
#include "Sprite.h"

//=============================================================================
//using
//=============================================================================
using namespace std;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	メニュー用
//=============================================================================
class CMenu : public CSprite
{
	public:
	
		/*文字列リスト*/
		struct StringList
		{
			Uint32 priority;//順番
			Math::Point2DF m_Pos;//文字位置
			string m_Str;//文字列
			Math::Rect2DF m_HitRect;//当たり判定領域
			bool m_IsEnable;//メニューが利用できるか
			bool m_IsHitString;//文字列に当たっているか
			
			StringList()
			{	
				m_Pos.x = 0;
				m_Pos.y = 0;
				m_Str.clear();
				m_HitRect.Set( 0, 0, 0, 0 );
				m_IsEnable = true;
				m_IsHitString = false;
			}
			
		};
		
	private:
	
		CFontSprite *m_pFontSpr;//フォントスプライト
		string m_strTitle;//タイトル名
		vector<StringList> m_vecDrawStr;//メニュー文字列
		int m_SelectIdx;//セレクト項目
		bool m_IsHitString;//文字列に当たっているか
		bool m_IsShowFrame;//フレームを表示させるか
		//bool m_IsCheckMenu;//確認メニューかどうか
		Peripheral::IMouse *m_pMouse;//マウスデバイス
		
	
	public:
	
		CMenu( const char *pName, Math::Vector2D vPos, Peripheral::IMouse *pMouse );//コンストラクタ
		~CMenu();//デストラクタ
		
		void Init();//初期化
		void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );//ファイル読み込み
		void Rendering();//レンダリング
		void Exec();//処理
		
		void SetCheckMenu( string strTitle );//確認メニューの設定
		
		void DrawMenu();//メニューの描画
		void DrawCheckMenu();//チェックメニューの描画
		
	
	public:
	
		//描画文字列リストの設定
		void SetStringList( StringList strList )
		{
			m_vecDrawStr.push_back( strList );
		}
		
		/*タイトル名の設定*/
		void SetTitleString( string strTitle )
		{
			m_strTitle = strTitle;
		}
		
		//フレームを表示するか設定
		void SetShowFrameFlag( bool flag )
		{
			m_IsShowFrame = flag;
		}
			
		///*確認メニューかどうか設定*/
		//void SetIsCheckMenu( bool flag )
		//{
		//	m_IsCheckMenu = flag;
		//}
		//
	public:
	
		/*メニューフォントの取得*/
		CFontSprite *GetMenuFont() const
		{
			return m_pFontSpr;
		}
	
		/*セレクト項目の取得*/
		int GetSelectIndex() const
		{
			return m_SelectIdx;
		}
		
		/*文字列に当たっているかどうかの取得*/
		bool GetHitStringFlag() const
		{
			return m_IsHitString;
		}
		
		//文字列リストの取得
		StringList GetStringList( int No ) const
		{
			m_vecDrawStr.at( No );
		}
		
		void SetStringFlag( int No, bool flag )
		{
			m_vecDrawStr.at( No ).m_IsEnable = flag;
		}
		
		
		
		
		
};