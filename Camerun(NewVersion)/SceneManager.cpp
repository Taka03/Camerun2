//*============================================================================
//SceneManager.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneManager.h"
#include "prehead.h"

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	pRender:レンダラー用デバイス
//=============================================================================
CSceneManager::CSceneManager( Renderer::IRender *pRender ) 
 :m_pSceneMgr(NULL), 
  m_pRenderTex(NULL),
  m_pRender( pRender ),
  m_IsRenderTex( false )

{
	
	m_pRender->AddRef();
	
	m_RenderTargetWidth = SCREEN_WIDTH;
	m_RenderTargetHeight = SCREEN_HEIGHT;
}

//=============================================================================
//デストラクタ
//=============================================================================
CSceneManager::~CSceneManager(void)
{
	SAFE_RELEASE( m_pRenderTex );
	SAFE_RELEASE( m_pSceneMgr );
	SAFE_RELEASE( m_pRender );
}

//=============================================================================
//デバイスの設定
//=============================================================================
//[input]
//	IsRenderTex:テクスチャにレンダリングするか
//=============================================================================
void CSceneManager::CreateDevice( bool IsRenderTex )
{
	m_pSceneMgr = m_pRender->CreateSceneManager( 512, false );
	
	if( IsRenderTex )
	{
		m_IsRenderTex = IsRenderTex;
		
		m_pRenderTex = m_pRender->CreateTextureRenderTarget( m_RenderTargetWidth, m_RenderTargetHeight, 
														   FORMAT_TARGET_32BIT );
	}
		
}

//=============================================================================
//初期パラメーターの設定
//=============================================================================
void CSceneManager::SetInitParameter( )
{
	if( m_pSceneMgr != NULL )
	{
		if( m_IsRenderTex )
		{

			m_pSceneMgr->InitParameter_RenderTargetData(
				m_pRenderTex,												// レンダリングターゲットのテクスチャ（NULLでバックバッファへ直接）
				Math::Point2DI( m_RenderTargetWidth, m_RenderTargetHeight ),		// 描画先のレンダリングターゲットサイズ（↑が指定されている時は↑のテクスチャサイズに自動変換）
				false );											// 描画先のテクスチャサイズを２の累乗にするかどうか
		}
		
		else
		{
			m_pSceneMgr->InitParameter_RenderTargetData(
				NULL,												// レンダリングターゲットのテクスチャ（NULLでバックバッファへ直接）
				Math::Point2DI( m_RenderTargetWidth, m_RenderTargetHeight ),		// 描画先のレンダリングターゲットサイズ（↑が指定されている時は↑のテクスチャサイズに自動変換）
				false );											// 描画先のテクスチャサイズを２の累乗にするかどうか
		
		}

		// シーンに対するエフェクトの初期化
		//   シーンに対して行う各種レンダリングエフェクトはここで行います。
		m_pSceneMgr->InitParameter_Shading( SHADING_TYPE_NORMAL );							// シェーディング
		//m_pSceneMgr->InitParameter_Fog( FOG_TYPE_DISABLE, FOG_EFFECT_LINEAR );				// フォグ
		//m_pSceneMgr->InitParameter_HighDynamicRange( HDR_TYPE_ENABLE, HDR_EFFECT_CROSS );		// HDRレンダリング
	//		m_pSceneMgr->InitParameter_MotionBlur( MOTION_BLUR_TYPE_DISABLE );					// モーションブラー
	//		m_pSceneMgr->InitParameter_DepthOfField( DOF_TYPE_DISABLE );							// 被写界深度
		m_pSceneMgr->InitParameter_Shadow( SHADOW_TYPE_SHADOWMAP, SHADOW_QUARITY_MIDDLE );	// 影生成
	//		m_pSceneMgr->InitParameter_AntiAliasType( AA_TYPE_DISABLE, 0.0f );					// アンチエイリアス

		// シーンの初期化系パラメーターの更新
		m_pSceneMgr->InitParameter_Update();
		
		
	}
}

//=============================================================================
//スカイドームの生成
//=============================================================================
//[input]
//	pTex:テクスチャハンドル
//=============================================================================
void CSceneManager::CreateSkyDoom( Renderer::ITexture *pTex )
{

	if( m_pSceneMgr != NULL && pTex != NULL )
	{
		// スカイドーム生成
		//  空を表現するためのスカイドームを生成します。
		m_pSceneMgr->SceneSkydoom_Create(
			10.0f,						// 半径
			CColor(121,154,255),		// 地表色
			CColor(121,154,255),		// 天頂色
			pTex );					// 空テクスチャ
	}
		
}

//=============================================================================
//パラメーターの設定
//=============================================================================
void CSceneManager::SetParameter()
{
	if( m_pSceneMgr != NULL )
	{
		m_pSceneMgr->Reset();

		// シーンの背景の色
		m_pSceneMgr->SetParameter_BGColor( Math::Vector4D(0.0f,0.0f,0.0f,1.0f) );
		
		/*描画先領域*/
		m_pSceneMgr->SetParameter_RenderRect( Math::Rect2DF( 0, 0,
															 toF( m_RenderTargetWidth ), toF( m_RenderTargetHeight ) ) );
		
		//m_pSceneMgr->SetParameter_Fog(
		//	Math::Vector3D( 0.8f, 0.8f, 0.8f ),		// フォグ色
		//	50.0f,									// フォグ開始位置
		//	300.0f );								// フォグ終了位置
		//	
		
	}
}



//=============================================================================
//描画領域サイズの設定
//=============================================================================
//[input]
//	width:設定する幅
//	height:設定する高さ
//=============================================================================
void CSceneManager::SetRenderSize( Sint32 width, Sint32 height )
{
	m_RenderTargetWidth = width;
	m_RenderTargetHeight = height;
}

