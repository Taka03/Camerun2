//*============================================================================
//Photo.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Photo.h"

using namespace std;

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	pName:データ名
//	vPos:位置
//	vecCheckData:写真の判定データ
//==============================================================================
CPhoto::CPhoto( const char *pName, Math::Vector2D vPos, vector< PhotoCheckData > vecCheckData ) 
:CSprite( pName, vPos ),
 m_vecPhotoData( vecCheckData )
{
	m_Score = 0;
}

//============================================================================
//ファイル読み込み
//============================================================================
//[input]
//	pRender:レンダラー用デバイス
//	pFileMgr:ファイル管理用デバイス
//===========================================================================
void CPhoto::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	CSprite::Load( pRender, pFileMgr );
	
	#if defined( RELEASE_TEST )
		
	#else
	
		//DeleteFileA( m_strFileName.c_str() );
	
	#endif
	
}

//============================================================================
//写真情報のセット
//============================================================================
 void CPhoto::SetPhotoInfo()
 {
	vector< PhotoCheckData >::iterator it = m_vecPhotoData.begin();
	
	for( it = m_vecPhotoData.begin();it != m_vecPhotoData.end();++it )
	{
		 CPhoto::PhotoCheckData datPhoto = *it;
		 
		 m_vecTargetName.push_back( datPhoto.m_strTargetName );
		 
		 char Temp[10];
		 
		 sprintf_s( Temp, 10, "%dp", datPhoto.m_Score );
		 
		 m_vecTargetScore.push_back( Temp );
		 
		 m_Score += datPhoto.m_Score;
		 
	}
	
 }
