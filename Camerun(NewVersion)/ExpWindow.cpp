//*============================================================================
//ExpWindow.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "ExpWindow.h"
#include "FileLoader.h"
#include <fstream>

//=============================================================================
//namespace
//=============================================================================
namespace
{
	Math::Vector2D vMousePos( 0.0f, 0.0f );
	Math::Vector2D vDir( 0.0f, 0.0f );
	Math::Vector3D vPos( 0.0f, 0.0f, 0.0f );
	::Peripheral::IMouse *pMouse = NULL;
	
}

//============================================================================
//コンストラクタ
//============================================================================
//[input]
//	pName:データ名
//	vPos:表示位置
//===========================================================================
CExpWindow::CExpWindow( const char *pName, Math::Vector2D vPos ) 
 :CSprite( pName, vPos ),
  m_StrCount( 0 ),
  m_OldStrCount( 0 )

{
	const float fMARGIN = 20.0f;
	
	m_pTrlFontSpr = new CFontSprite( "TutorialFont.sff", vPos + Math::Vector2D( fMARGIN, fMARGIN ) );
}

//============================================================================
//デストラクタ
//============================================================================
CExpWindow::~CExpWindow()
{
	SAFE_DELETE( m_pTrlFontSpr );
}

//============================================================================
//ファイル読み込み
//============================================================================
//[input]
//	pRender:レンダラー用デバイス
//	pFileMgr:ファイル管理用デバイス
//============================================================================
void CExpWindow::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	CSprite::Load( pRender, pFileMgr );
	
	m_pTrlFontSpr->Load( pRender, pFileMgr );
	
}

//============================================================================
//処理
//============================================================================
void CExpWindow::Init()
{
	m_StrCount = 0;
	m_OldStrCount = 0;
}


//============================================================================
//処理
//============================================================================
void CExpWindow::Exec()
{
	CSprite::Exec();
	
	m_pTrlFontSpr->SetVisibleFlag( GetVisibleFlag() );
	
	/*文字カウント補正*/
	if( m_StrCount > m_pTrlFontSpr->GetVecString().size() - 1 )
	{
		m_StrCount = m_pTrlFontSpr->GetVecString().size() - 1;
	}
	
	/*描画文字列*/
	string strDraw = m_pTrlFontSpr->GetDrawString();
	
	string::size_type index = strDraw.find("Br");
	
	/*Br文字列が見つかったら、文字列を分解する*/
	if( index != string::npos )
	{
		vector<string> strRet =  CFileLoader::SplitString( strDraw, "Br" );
		
		m_pTrlFontSpr->DrawMultiLine( strRet );
		
	}
	
	/*通常通り描画*/
	else
	{
		m_pTrlFontSpr->Exec();
	}
}

//============================================================================
//レンダリング
//============================================================================
void CExpWindow::Rendering()
{
	CSprite::Rendering();
	
	if( m_pTrlFontSpr->GetVisibleFlag() )
	{	
		m_pTrlFontSpr->Rendering();
	}
}

//=============================================================================
//チュートリアル説明文のセット
//=============================================================================
//[input]
//	pFileMgr:ファイル管理用デバイス
//=============================================================================
void CExpWindow::SetTutorialExp( File::IFileManager *pFileMgr )
{
	char Temp[1024];
	std::vector<string> vecText;
	
	File::IResourceFile *pResFile = NULL;
	
	pFileMgr->SetCurrentPath("Text");
	
	pResFile = 	pFileMgr->FileOpen("TutorialFont.txt");
	
	ifstream ifs( pResFile->GetNamePointer() );
	
	SAFE_RELEASE( pResFile );
	
	while( !ifs.eof() )
	{
		ifs >> Temp;
		vecText.push_back( Temp );
	}
	
	m_pTrlFontSpr->SetVecTextChat( vecText );
}
