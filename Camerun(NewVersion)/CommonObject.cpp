//*============================================================================
//CommonObject.cpp
//*============================================================================


//=============================================================================
//include
//=============================================================================
#include "CommonObject.h"
#include "GameSceneManager.h"
#include "SoundManager.h"
#include "ResourceManager.h"
#include "Application.h"
#include "camera.h"
#include "SceneManager.h"
#include "Mouse.h"

//=============================================================================
//variable
//=============================================================================
CApplication *CCommonObject::m_pApp = NULL;
CSoundManager *CCommonObject::m_pSndMgr = NULL;
CResourceManager *CCommonObject::m_pResMgr = NULL;
CCamera *CCommonObject::m_pCamera[SCREEN_MAX];
CSceneManager *CCommonObject::m_pSceneMgr[SCREEN_MAX];
CGameSceneManager *CCommonObject::m_pGameSceneMgr = NULL;
CMouse *CCommonObject::m_pMouse = NULL;

//=============================================================================
//コンストラクタ
//=============================================================================
CCommonObject::CCommonObject(void) 
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CCommonObject::~CCommonObject(void)
{

}

//=============================================================================
//初期化処理
//=============================================================================
void CCommonObject::Initialize()
{
	memset( m_pSceneMgr, NULL, SCREEN_MAX );
	memset( m_pCamera, NULL, SCREEN_MAX );
}


//=============================================================================
//終了処理
//=============================================================================
void CCommonObject::Finalize()
{
	SAFE_DELETE( m_pGameSceneMgr );
	
	
	SAFE_DELETE( m_pSndMgr );
	
	SAFE_DELETE( m_pResMgr );
	
	for( int i = 0;i < SCREEN_MAX;++i )
	{	
		SAFE_DELETE( m_pCamera[i] );
		SAFE_DELETE( m_pSceneMgr[i] );
	}
	
	
	SAFE_DELETE( m_pMouse );
	
	SAFE_DELETE( m_pApp );
}


//=============================================================================
//アプリケーションクラスの取得
//=============================================================================
//[return]
//	アプリケーションクラス
//=============================================================================
CApplication *CCommonObject::GetAppli()
{
	if( m_pApp == NULL )
	{
		m_pApp = new CApplication( SCREEN_WIDTH, SCREEN_HEIGHT );
	}
	
	return m_pApp;
}

//=============================================================================
//マウスクラスの取得
//=============================================================================
//[return]
//	マウスクラス
//=============================================================================
CMouse *CCommonObject::GetMouse()
{
	if( m_pMouse == NULL )
	{
		m_pMouse = new CMouse( GetAppli()->GetCore() );
		
	}
	
	return m_pMouse;
}



//=============================================================================
//リソースマネージャーの取得
//=============================================================================
//[return]
//	リソースマネージャー
//=============================================================================
CResourceManager *CCommonObject::GetResMgr()
{
	if( m_pResMgr == NULL )
	{
		m_pResMgr = new CResourceManager( );
	}
	
	return m_pResMgr;
}

//=============================================================================
//シーンマネージャーの取得
//=============================================================================
//[input]
//	index:取得するシーン番号
//[return]
//	シーンマネージャー
//=============================================================================
CSceneManager *CCommonObject::GetSceneMgr( int index )
{
	static bool IsFirst = true;//初回呼び出しフラグ
	
	if( IsFirst )
	{
		//テクスチャに描画するか
		bool IsRenderTex[] =
		{
			false,
			true,	
		};
	
		for( int i = 0;i < SCREEN_MAX;++i )
		{	
			m_pSceneMgr[i] = new CSceneManager( GetAppli()->GetRenderer() );
			
			//デバイスの生成
			m_pSceneMgr[i]->CreateDevice( IsRenderTex[i] );
			
			m_pSceneMgr[i]->SetInitParameter();
		
		}
		
		IsFirst = false;
				
	}
	
	return m_pSceneMgr[index];
}

//=============================================================================
//カメラの取得
//=============================================================================
//[input]
//	index:取得するカメラ番号
//[return]
//	カメラ
//=============================================================================
CCamera *CCommonObject::GetCamera( int index )
{
	static bool IsFirst = true;//初回呼び出しフラグ
	
	if( IsFirst )
	{
		for( int i = 0;i < SCREEN_MAX;++i )
		{	
			m_pCamera[i] = new CCamera();
			
			//デバイスの生成
			m_pCamera[i]->SetCamera( GetSceneMgr( i )->GetSceneMgr() );
			
			//プロジェクションの設定
			m_pCamera[i]->SetProjection( 1.0f, 300.0f, 45, SCREEN_WIDTH, SCREEN_HEIGHT ); 
			
		}
		
		IsFirst = false;
				
	}
	
	return m_pCamera[index];
	
}

//=============================================================================
//サウンドマネージャーの取得
//=============================================================================
//[return]
//	サウンドマネージャー
//=============================================================================
CSoundManager *CCommonObject::GetSoundMgr() 
{
	if( m_pSndMgr == NULL )
	{
		m_pSndMgr = new CSoundManager();
	}
	
	return m_pSndMgr;
}

//=============================================================================
//ゲームシーンマネージャーの取得
//=============================================================================
//[return]
//	ゲームシーンマネージャー
//=============================================================================
CGameSceneManager *CCommonObject::GetGameSceneMgr()
{
	if( m_pGameSceneMgr == NULL )
	{
		m_pGameSceneMgr = new CGameSceneManager( );
	}

	return m_pGameSceneMgr;
}


