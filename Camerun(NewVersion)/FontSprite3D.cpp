//*============================================================================
//FontSprite3D.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "FontSprite3D.h"
#include "SceneManager.h"

//============================================================================
//コンストラクタ
//============================================================================
//[input]
//	pName:データ名
//===========================================================================
CFontSprite3D::CFontSprite3D( const char *pName, Math::Vector3D vPos ) 
 :m_pFontSpr3D(NULL),
  CDraw3DObject( pName, vPos )
{
	m_Str = "あああああ";
	
	for( int i = 0;i < SCREEN_MAX;++i )
	{
		m_pActorFont[i] = NULL;
	}
	
	m_fSize.x = 1.0f;
	m_fSize.y = -11.0f;
}


//============================================================================
//デストラクタ
//============================================================================
CFontSprite3D::~CFontSprite3D(void)
{
	for( int i = 0;i < SCREEN_MAX;++i )
	{	
		SAFE_RELEASE( m_pActorFont[i] );
	}
	
	SAFE_RELEASE( m_pFontSpr3D );
	
	SAFE_RELEASE( m_pRender ); 
}

//============================================================================
//ファイル読み込み
//============================================================================
//[input]
//	pRender:レンダラー用デバイス
//	pFileMgr:ファイル管理用デバイス
//===========================================================================
void CFontSprite3D::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	pFileMgr->SetCurrentPath("Font");
	
	m_pFontSpr3D = pRender->CreateFontSprite3DFromFile( m_strFileName.c_str(), "tga", 1024 );
	
	m_pRender = pRender;
	
	m_pRender->AddRef();
	
	//アクターの生成
	for( int i = 0;i < SCREEN_MAX;++i )
	{
		CreateActor( i, CCommonObject::GetSceneMgr( i )->GetSceneMgr() );
	}
}

//============================================================================
//ファイル読み込み
//============================================================================
//[input]
//	pRender:レンダラー用デバイス
//===========================================================================
void CFontSprite3D::CreateActor( int index, Scene::ISceneManager *pSceneMgr )
{
	m_pActorFont[index] = pSceneMgr->CreateActor( m_pFontSpr3D );
}

//============================================================================
//処理
//============================================================================
void CFontSprite3D::Exec()
{
	if( m_pFontSpr3D != NULL )
	{
		// 文字列描画用のステート
		m_pRender->SetDrawType( DRAW_TYPE_BLEND );
		m_pRender->SetAlphaTestEnable( true );
		m_pRender->SetDepthTestEnable( true );
		m_pRender->SetDepthWriteEnable( true );
		m_pRender->SetCullType( CULL_FRONT );
		
		/*描画開始*/
		m_pFontSpr3D->Begin();
		
		/*描画キューに追加*/
		m_pFontSpr3D->DrawString( m_Str.c_str(), m_vPos, m_fSize, CColor(255, 255, 255) );
		
		/*描画終了*/
		m_pFontSpr3D->End();
	}	
}

//============================================================================
//レンダリング
//============================================================================
void CFontSprite3D::Rendering()
{
	if( GetVisibleFlag() )
	{	
		m_pActorFont[m_ActorIndex]->RenderingRequest();
	}
}

//============================================================================
//アクターインデックスのセット
//============================================================================
void CFontSprite3D::SetActorIndex( int index )
{
	m_ActorIndex = index;
}




