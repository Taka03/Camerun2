//*============================================================================
//Particle.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Particle.h"
#include "SceneManager.h"


//============================================================================
//コンストラクタ
//============================================================================
//[input]
//	pName:データ名
//	vPos:表示位置
//===========================================================================
CParticle::CParticle( const char *pName, Math::Vector3D vPos ) 
:m_pTex(NULL), 
 m_pParticle(NULL),
 CDraw3DObject( pName, vPos ),
 m_Alpha( 255, 255, 255 )
{
	memset( m_pActorParticle, NULL, SCREEN_MAX );
	
	
}

//============================================================================
//デストラクタ
//============================================================================
CParticle::~CParticle(void)
{
	for( int i = 0;i < SCREEN_MAX;++i )
	{	
		SAFE_RELEASE( m_pActorParticle[i] );
	}
	
	SAFE_RELEASE( m_pParticle );
	SAFE_RELEASE( m_pTex );
	
	
}

//============================================================================
//ファイル読み込み
//============================================================================
//[input]
//	pRender:レンダラー用デバイス
//	pFileMgr:ファイル管理用デバイス
//===========================================================================
void CParticle::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	pFileMgr->SetCurrentPath("Texture");
	
	m_pTex = pRender->CreateTextureFromFile( m_strFileName.c_str() );
	
	m_Width = m_pTex->GetOriginalSize().x;
	m_Height = m_pTex->GetOriginalSize().y;
	
	/*パーティクルの生成*/
	m_pParticle = pRender->CreateParticle( 128, m_pTex, PARTICLE_TYPE_VOLUME, true ); 
	
	//アクターの生成
	for( int i = 0;i < SCREEN_MAX;++i )
	{
		CreateActor( i, CCommonObject::GetSceneMgr( i )->GetSceneMgr() );
	}
	
}

//============================================================================
//アクター生成
//============================================================================
//[input]
//	index:インデックス
//	pSceneMgr:シーンマネージャ
//===========================================================================
void CParticle::CreateActor( int index, Scene::ISceneManager *pSceneMgr )
{
	m_pActorParticle[index] = pSceneMgr->CreateActor( m_pParticle );
}

//============================================================================
//処理
//============================================================================
void CParticle::Exec()
{
	static int count = 0;
	
	if( m_pParticle != NULL )
	{
		if( m_IsVisible )
		{
			
			m_pParticle->Begin();
			
			//m_Alpha.x = Interpolation::Flat( m_Alpha.y, m_Alpha.z, BOMB_ALIVE_TIME, count );
			//m_Rot.x = DEG_TO_ANGLE(0);
			//m_Alpha.x = 255;
			//m_vScale.x = Interpolation::Flat( m_vScale.y, m_vScale.z, BOMB_ALIVE_TIME, count );
			
			//m_vPos.z = Interpolation::Flat( m_vPos.z, m_vPos.z + 1, BOMB_ALIVE_TIME, count );
		
			Math::Rect2DI SrcRect( 0, 0, m_Width, m_Height );
			
			m_pParticle->DrawRotate( m_vPos, Math::Point2DF( m_vScale.x, m_vScale.y ), SrcRect, CColor( 255, 255, 255, m_Alpha.x ), toI( m_Rot.x ) );
			
			m_pParticle->End();
		}
	}
}

//============================================================================
//レンダリング
//============================================================================
void CParticle::Rendering( int index )
{
	m_pRender->SetDrawType( DRAW_TYPE_BLEND );	// 描画モード（加算
	m_pRender->SetAlphaTestEnable( true );		// アルファテストON
	m_pRender->SetDepthTestEnable( true );		// 深度テストON
	m_pRender->SetDepthWriteEnable( false );		// 深度書き込みOFF
	
	m_pActorParticle[index]->RenderingRequest();
	
	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );	
	
}
