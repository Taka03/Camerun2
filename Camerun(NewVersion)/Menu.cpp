//*============================================================================
//Menu.h
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Menu.h"
#include "SceneBase.h"


//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	pName:データ名
//	vPos:表示位置
//	pMouse:マウスデバイス
//===========================================================================
CMenu::CMenu( const char *pName, Math::Vector2D vPos, Peripheral::IMouse *pMouse ) 
 :m_pFontSpr(NULL),
  m_pMouse( pMouse ),
  CSprite( "window.png", vPos )
//  m_IsCheckMenu( false )
{
	m_pMouse->AddRef();	
	
	m_IsHitString = false;
	
	m_IsShowFrame = false;
	
	m_SelectIdx = 0;
	
	m_pFontSpr = new CFontSprite( pName, vPos );
	
	m_vecDrawStr.clear();
	
	m_strTitle.clear();

}

//=============================================================================
//デストラクタ
//=============================================================================
CMenu::~CMenu()
{
	SAFE_RELEASE( m_pMouse );
	SAFE_DELETE( m_pFontSpr );
}

//============================================================================
//ファイル読み込み
//============================================================================
//[input]
//	pRender:レンダラー用デバイス
//	pFileMgr:ファイル管理用デバイス
//===========================================================================
void CMenu::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	CSprite::Load( pRender, pFileMgr );
	
	m_pFontSpr->Load( pRender, pFileMgr );
}


//=============================================================================
//初期化
//=============================================================================
void CMenu::Init()
{
	CSprite::Init();
	
	m_pFontSpr->Init();
	
}

//=============================================================================
//レンダリング
//=============================================================================
void CMenu::Rendering()
{
	/*フォントをメニューと連動*/
	m_pFontSpr->SetVisibleFlag( GetVisibleFlag() );
	
	if( m_IsShowFrame )	
	{
		CSprite::Rendering();
	}
	
	if( m_pFontSpr->GetVisibleFlag() )
	{	
		m_pFontSpr->Rendering();	
	}
}

//=============================================================================
//処理
//=============================================================================
void CMenu::Exec( )
{
	CSprite::Exec();
	
	/*メニューの表示*/
	DrawMenu();
	
}

//=============================================================================
//メニューの描画
//=============================================================================
void CMenu::DrawMenu()
{
		
	/*描画開始*/
	m_pFontSpr->GetFontSprite()->Begin();
	
	const float fMARGIN = 30.0f;
	
	Math::Vector2D vMousePos( toF( m_pMouse->GetPosX() ), toF( m_pMouse->GetPosY() ) );
	
	Uint32 MenuCount = 0;
	
	const Math::Point2DF fMARGIN_WIN( 190.0f, 10.0f );//ウィンドウからの余白
	
	/*メニュータイトル名の描画*/
	if( m_strTitle.length() > 0 )
	{
		Math::Point2DF Pos( m_vPos.x + fMARGIN_WIN.x, m_vPos.y + fMARGIN_WIN.y );
		
		m_pFontSpr->GetFontSprite()->DrawString( m_strTitle.c_str(), Pos, CColor( 255, 255, 255 ) );
	}
	
	/*メニュー項目の描画*/
	for( vector<StringList>::iterator i = m_vecDrawStr.begin();i != m_vecDrawStr.end();++i )
	{
		
		StringList strList = *i;
		
		string strTemp = strList.m_Str;
		
		Math::Point2DF Pos = strList.m_Pos;
								 
		Math::Rect2DF HitRect = strList.m_HitRect;
		
		bool IsEnable = strList.m_IsEnable;
		
		/*メニューとの当たり判定*/
		if( IsEnable )
		{
			if( ::Collision::Point_Rect( vMousePos, HitRect ) && GetVisibleFlag() )
			{
				m_pFontSpr->GetFontSprite()->DrawString( strTemp.c_str(), Pos, CColor( 220, 0, 0 ) );
				m_SelectIdx = strList.priority;
				
				MenuCount = 0;
				
				m_IsHitString = true;
			
			}
		
			else
			{
				m_pFontSpr->GetFontSprite()->DrawString( strTemp.c_str(), Pos, CColor( 255, 255, 255 ) );
				
				MenuCount++;
				
				if( MenuCount == m_vecDrawStr.size() )
				{
					m_IsHitString = false;
				}
				
			}
		}
		
		else
		{
			if( ::Collision::Point_Rect( vMousePos, HitRect ) && GetVisibleFlag() )
			{
				
				MenuCount = 0;
				
				m_IsHitString = true;
			
			}
		
			else
			{
				MenuCount++;
				
				if( MenuCount == m_vecDrawStr.size() )
				{
					m_IsHitString = false;
				}
				
			}
			
			m_pFontSpr->GetFontSprite()->DrawString( strTemp.c_str(), Pos, CColor( 128, 128, 128, 128 ) );
			
		}
		
	}
	
	/*描画終了*/
	m_pFontSpr->GetFontSprite()->End();
	
}

//=============================================================================
//確認メニューの設定
//=============================================================================
//[input]
//	strTitle:タイトル名
//===========================================================================
void CMenu::SetCheckMenu( string strTitle )
{
	const int CHECK_MENU_MAX = 2;
	
	CMenu::StringList strList;
	
	Math::Point2DF Pos[CHECK_MENU_MAX];//メニューの表示位置
	
	/*メニュー項目名*/
	string strMenu[] =
	{
		"f e",//ハイ
		"e e 5",//イイエ
	};
	
	const float fMARGIN = 290.0f;
	const Math::Point2DF fMARGIN_WIN( 150.0f, 50.0f );//ウィンドウからの余白
	
	//タイトル名の設定
	m_strTitle = strTitle;
		
	for( int i = 0;	i < CHECK_MENU_MAX;++i )
	{
		Pos[i] = Math::Point2DF( m_vPos.x + toF( i * fMARGIN ) + fMARGIN_WIN.x, 
								 m_vPos.y + fMARGIN_WIN.y );
		
		
		strList.priority = i;
		strList.m_Pos = Pos[i];
		strList.m_Str = strMenu[i];
		strList.m_IsEnable = true;
		
		CFontSprite *pFontSpr = GetMenuFont();
		
		Math::Point2DF fSize = pFontSpr->GetFontSprite()->GetStringSize( strMenu[i].c_str() );
		
		strList.m_HitRect.Set( Pos[i].x, Pos[i].y, fSize.x, fSize.y );
		
		/*描画文字列リストに追加*/
		SetStringList( strList );
		
	}
	
	/*確認画面の時は、一旦消去しておく*/
	SetVisibleFlag( false );
}







