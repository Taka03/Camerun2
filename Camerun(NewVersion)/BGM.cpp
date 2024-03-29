//*============================================================================
//BGM.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "BGM.h"

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	pName:データ名
//=============================================================================
CBGM::CBGM( const char *pName ) 
 :m_pBGM(NULL),
  CSoundObject( pName )
{
}


//=============================================================================
//デストラクタ
//=============================================================================
CBGM::~CBGM(void)
{
	SAFE_RELEASE( m_pBGM );
}

//=============================================================================
//サウンドの読み込み
//=============================================================================
//[input]
//	pCore:コアデバイス
//	pFileMgr:ファイルマネージャー
//=============================================================================
void CBGM::LoadSound( ICore *pCore, File::IFileManager *pFileMgr )
{
	if( !m_strFileName.empty() )
	{	
		pFileMgr->SetCurrentPath("BGM");
		
		printf("LOAD BGM[%s]", m_strFileName.c_str() );
	
		m_pBGM = pCore->CreateStreamSoundFromFile( m_strFileName.c_str(), false, "OggVorbis" );
		
		printf( "                 : -> %s\n", m_pBGM->IsInvalid() ? "Failed" : "Succeeded" );
		
	}
	
}

//=============================================================================
//サウンドの再生
//=============================================================================
//[input]
//	pTbl:再生テーブル
//	count:テーブル数
//=============================================================================
void CBGM::Play( Sound::SPlayBlock *pTbl, int count )
{
	m_pBGM->Play( pTbl, count );
}

//=============================================================================
//処理
//=============================================================================
void CBGM::Exec()
{
	m_pBGM->Play(-1);
}

//=============================================================================
//フェードアウト
//=============================================================================
void CBGM::FadeOut()
{
	static int count = 0;
	
	while( count <= 60 )
	{
	
		float fVolume = Interpolation::Flat( 100.0f, 0.0f, 60, count );
		
		m_pBGM->SetVolume( fVolume );
		
		count++;
		
	
	}
	
	if( count >= 60 )
	{
		count = 0;
	}

	
}

//=============================================================================
//参照カウンタの増加
//=============================================================================
void CBGM::AddRef()
{
	m_pBGM->AddRef();
}






