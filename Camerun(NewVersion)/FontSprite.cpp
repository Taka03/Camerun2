//*============================================================================
//FontSprite.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "FontSprite.h"

//============================================================================
//コンストラクタ
//============================================================================
//[input]
//	pName:データ名
//	vPos:位置
//===========================================================================
CFontSprite::CFontSprite( const char *pName, Math::Vector2D vPos ) 
:m_pFontSpr(NULL),
  CDraw2DObject( pName, vPos )

{
	m_Str = "";
	
	m_vecText.clear();
	
	m_FontColor = CColor( 255, 255, 255 );
	
	m_HitRect.Set( 0.0f, 0.0f, 0.0f, 0.0f );
	
	m_RefCount = 0;
	
	m_StrCount = 1;
	
	m_IsTextEnd = false;
}


//============================================================================
//デストラクタ
//============================================================================
CFontSprite::~CFontSprite(void)
{
	SAFE_RELEASE( m_pFontSpr );
}

//============================================================================
//ファイル読み込み
//============================================================================
//[input]
//	pRender:レンダラー用デバイス
//	pFileMgr:ファイル管理用デバイス
//===========================================================================
void CFontSprite::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	pFileMgr->SetCurrentPath("Font");
	
	printf("LOAD FONT[%s]", m_strFileName.c_str() );
	
	m_pFontSpr = pRender->CreateFontSprite2DFromFile( m_strFileName.c_str(), "tga", 1024 );
	
	printf( "                 : -> %s\n", m_pFontSpr->IsInvalid() ? "Failed" : "Succeeded" );
}


//============================================================================
//処理
//============================================================================
void CFontSprite::Exec()
{
	if( m_pFontSpr != NULL )
	{
		/*描画開始*/
		m_pFontSpr->Begin();
		
		/*描画キューに追加*/
		m_pFontSpr->DrawString( m_Str.c_str(), Math::Point2DF( m_vPos.x, m_vPos.y ), m_FontColor );
		
		/*描画終了*/
		m_pFontSpr->End();
	}	
}

//============================================================================
//レンダリング
//============================================================================
void CFontSprite::Rendering()
{
	if( m_pFontSpr != NULL )
	{
		if( GetVisibleFlag() )
		{	
			m_pFontSpr->Rendering();
		}
	}
}

//============================================================================
//ノベル風に描画
//============================================================================
//[input]
//	pCore:設定するコアデバイス
//===========================================================================
bool CFontSprite::DrawNovelStyle( ICore *pCore )
{
	Peripheral::IMouse *pMouse = pCore->GetMouse();
	
	/*文字の進む間隔*/
	if( (pCore->GetSyncCount() % 5) == 0 )
	{
		m_StrCount ++;
	}
	
	if( m_pFontSpr != NULL )
	{
		Uint32 Cnt = m_StrCount;
		const char *pStr = m_vecText.at( m_RefCount ).c_str();//(char *)( m_Str.c_str() );
		
		Math::Rect2DF Dst( m_vPos.x, m_vPos.y, 0, 0 );
		
		/*描画開始*/
		m_pFontSpr->Begin();
		
		while( (*pStr != '\0') && (Cnt > 0) )
		{
			
			/*2Byte文字かどうか*/
			Bool Is2Byte = Is2ByteChara( (unsigned char)(*pStr) );
			
			//Math::Point2DF Size = m_pFontSpr->GetStringSize( pStr );
			
			Sint32 FontSize = m_pFontSpr->GetSize();//21;//m_pFontSpr->gt;//フォントサイズ
			
			if( !Is2Byte )
			{
				/*改行かどうか*/
				if( *pStr == '\n' )
				{
					//Dst.y += toF( Size.y );	
					//Dst.y += FontSize;
					//Dst.x = m_vPos.x;
					pStr += 1;
					continue;
				}
				
				/*改行*/
				else if( *pStr == 'B' )
				{
					
					Dst.x = m_vInitPos.x;
					Dst.y += FontSize;
					pStr += 1;
					//m_pFontSpr->Begin();
					
					continue;
					
				}
				
				/*左クリックの場合*/
				else if( *pStr == 'L' )
				{
					if( pMouse->GetStateL() == MOUSE_PUSH )
					{
						pStr += 1;
					}
					
					continue;

				}
				
				else if( *pStr == '@')
				{
					//IsStop = true;
					pStr += 1;
					
					continue;
				}
				
				/*終了フラグ*/
				else if( *pStr == 'E')
				{
					m_IsTextEnd = true;
					return true;
				}
				
				
			}
			
			Dst.x += FontSize;
			
			//Dst.x += Size;
			
			
		//	Math::Point2DF Size = m_pFontSpr->GetStringSize( Str2.c_str() );
	
			Dst.w = toF( FontSize );
			Dst.h = toF( FontSize );
			
			/*一文字描画*/
			m_pFontSpr->DrawChara( pStr, Dst, CColor(0, 0, 0 ));
			
			Dst.x -= FontSize;
			
			if( Is2Byte )
			{
				//Dst.x += Size.y;
				
				Dst.x += FontSize;
			}
			
			else
			{
				Dst.x += FontSize;
			}
			
			if( Dst.x >= 700 - FontSize * 2 )
			{
				Dst.x = m_vInitPos.x;
				Dst.y += FontSize;
			}
			
			pStr += Is2Byte ? 2 : 1;
			
			Cnt--;
			
		}
		
		/*描画終了*/
		m_pFontSpr->End();
		
		if( Cnt > 0 && !m_IsTextEnd )
		{
			
			if( pCore->GetMouse()->GetClickL() )
			{	
				m_StrCount = 1;
				m_RefCount++;
				
			}
		}
		
		if( m_RefCount >= m_vecText.size() -1)
		{
			m_RefCount = m_vecText.size() -1;
		}
		
	}	
	
	return false;
	
}


//============================================================================
//ノベル風に描画
//============================================================================
bool CFontSprite::DrawNovelStyle( ICore *pCore, Peripheral::IInputController *pCtrl )
{
	
	if( (pCore->GetSyncCount() % 5) == 0 )
	{
		m_StrCount ++;
	}
	
	//if( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_R1 ) )
	//{
	//	if( pCore->GetSyncCount() % 3 == 0 )
	//	{	
	//		m_StrCount += 1;
	//	}
	//}
	
	if( m_pFontSpr != NULL )
	{
		Uint32 Cnt = m_StrCount;
		const char *pStr = m_vecText.at( m_RefCount ).c_str();//(char *)( m_Str.c_str() );
		
		Math::Rect2DF Dst( m_vPos.x, m_vPos.y, 0, 0 );
		
		/*描画開始*/
		m_pFontSpr->Begin();
		
		while( (*pStr != '\0') && (Cnt > 0) )
		{
			
			/*2Byte文字かどうか*/
			Bool Is2Byte = Is2ByteChara( (unsigned char)(*pStr) );
			
			//Math::Point2DF Size = m_pFontSpr->GetStringSize( pStr );
			
			Sint32 FontSize = m_pFontSpr->GetSize();//21;//m_pFontSpr->gt;//フォントサイズ
			
			if( !Is2Byte )
			{
				/*改行かどうか*/
				if( *pStr == '\n' )
				{
					//Dst.y += toF( Size.y );	
					//Dst.y += FontSize;
					//Dst.x = m_vPos.x;
					pStr += 1;
					continue;
				}
				
				/*改行*/
				else if( *pStr == 'B' )
				{
					
					Dst.x = m_vInitPos.x;
					Dst.y += FontSize;
					pStr += 1;
					//m_pFontSpr->Begin();
					
					continue;
					
				}
				
				else if( *pStr == '@')
				{
					//IsStop = true;
					pStr += 1;
					
					continue;
				}
				
				/*終了フラグ*/
				else if( *pStr == 'E')
				{
					m_IsTextEnd = true;
					return true;
				}
				
				
			}
			
			Dst.x += FontSize;
			
			//Dst.x += Size;
			
			
		//	Math::Point2DF Size = m_pFontSpr->GetStringSize( Str2.c_str() );
	
			Dst.w = toF( FontSize );
			Dst.h = toF( FontSize );
			
			/*一文字描画*/
			m_pFontSpr->DrawChara( pStr, Dst, CColor(0, 0, 0 ));
			
			Dst.x -= FontSize;
			
			if( Is2Byte )
			{
				//Dst.x += Size.y;
				
				Dst.x += FontSize;
			}
			
			else
			{
				Dst.x += FontSize;
			}
			
			if( Dst.x >= 700 - FontSize * 2 )
			{
				Dst.x = m_vInitPos.x;
				Dst.y += FontSize;
			}
			
			pStr += Is2Byte ? 2 : 1;
			
			Cnt--;
			
		}
		
		/*描画終了*/
		m_pFontSpr->End();
		
		if( Cnt > 0 && !m_IsTextEnd )
		{
			
			//if( pCtrl->GetState( BUTTON_STATE_PUSH, BUTTON_R2 ) )
			//{	
			//	m_StrCount = 1;
			//	m_RefCount++;
			//	
			//}
		}
		
		if( m_RefCount >= m_vecText.size() -1)
		{
			m_RefCount = m_vecText.size() -1;
		}
		
		
		
	}	
	
	return false;
	
}

//============================================================================
//複数文字列の描画
//============================================================================
void CFontSprite::DrawMultiLine(  )
{
	m_pFontSpr->Begin();
	
	for( Uint32 i = 0; i < m_vecText.size();++i )
	{	
		m_pFontSpr->DrawString( m_vecText.at(i).c_str(), Math::Point2DF( m_vPos.x, m_vPos.y + i * 30 ), CColor( 255, 255, 255 ) );
	}
	
	m_pFontSpr->End();
}

//============================================================================
//複数文字列の描画
//============================================================================
//[input]
//	vPos:設定する位置
//===========================================================================
void CFontSprite::DrawMultiLine( Math::Point2DF vPos[] )
{
	m_pFontSpr->Begin();
	
	for( Uint32 i = 0; i < m_vecText.size();++i )
	{	
		m_pFontSpr->DrawString( m_vecText.at(i).c_str(), vPos[i], CColor( 255, 255, 255 ) );
	}
	
	m_pFontSpr->End();
}

//============================================================================
//複数文字列の描画
//============================================================================
//[input]
//	vPos:設定する位置
//	Str:設定する文字列
//	num:描画する数
//===========================================================================
void CFontSprite::DrawMultiLine( Math::Point2DF vPos[], string Str[], int num )
{
	m_pFontSpr->Begin();
	
	for( int i = 0; i < num;++i )
	{	
		m_pFontSpr->DrawString( Str[i].c_str(), vPos[i], CColor( 255, 255, 255 ) );
	}
	
	m_pFontSpr->End();
}

//============================================================================
//複数文字列の描画
//============================================================================
//[input]
//	vecStr:描画する文字
//===========================================================================
void CFontSprite::DrawMultiLine( vector<string> vecStr )
{
	m_pFontSpr->Begin();
	
	const float fMARGIN = 20.0f;//文字の余白
	
	for( Uint32 i = 0; i < vecStr.size();++i )
	{	
		m_pFontSpr->DrawString( vecStr.at(i).c_str(), Math::Point2DF( m_vPos.x, m_vPos.y + i * fMARGIN ),
								CColor( 255, 255, 255 ) );
	}
	
	m_pFontSpr->End();
}



//============================================================================
//表示する文字の設定
//============================================================================
//[input]
//	str:設定する文字列
//===========================================================================
void CFontSprite::SetDrawString(std::string str)
{
	m_Str = str;
}

