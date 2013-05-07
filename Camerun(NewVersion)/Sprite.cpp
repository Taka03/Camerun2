//*============================================================================
//Sprite.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Sprite.h"


//============================================================================
//コンストラクタ
//============================================================================
//[input]
//	pName:データ名
//	vPos:表示位置
//	DivNum:分割数
//===========================================================================
CSprite::CSprite( const char *pName, Math::Vector2D vPos, Math::Point2DI DivNum )  
:m_pTex(NULL),
 m_pSpr(NULL),
 CDraw2DObject( pName, vPos ),
 m_DivNum( DivNum ),
 m_AnimTime( 30 ),
 m_AnimCount( 0 ),
 m_Anim( 0, 0 ),
 m_fSize( 0, 0 ),
 m_HitRect( 0, 0, 0, 0 ),
 m_DstRect( 0, 0, 0, 0 ),
 m_SrcRect( 0, 0, 0, 0 ),
 m_IsAnim( false )
{
	/*エラー防止*/
	if( DivNum.x < 0 || DivNum.y < 0 )
	{
		m_DivNum.x = 1;
		m_DivNum.y = 1;
	}
}


//============================================================================
//コンストラクタ
//============================================================================
//[input]
//	pName:データ名
//	vPos:表示位置
//===========================================================================
CSprite::CSprite( const char *pName, Math::Vector2D vPos )  
:m_pTex(NULL),
 m_pSpr(NULL),
 CDraw2DObject( pName, vPos ),
 m_DivNum( 1, 1 ),
 m_AnimTime( 60 ),
 m_AnimCount( 0 ),
 m_Anim( 0, 0 ),
 m_fSize( 0, 0 ),
 m_HitRect( 0, 0, 0, 0 ),
 m_DstRect( 0, 0, 0, 0 ),
 m_SrcRect( 0, 0, 0, 0 ),
 m_IsAnim( false )
{

}

//============================================================================
//デストラクタ
//============================================================================
CSprite::~CSprite(void)
{
	SAFE_RELEASE( m_pSpr );
	SAFE_RELEASE( m_pTex );
}

//============================================================================
//ファイル読み込み
//============================================================================
//[input]
//	pRender:レンダラー用デバイス
//	pFileMgr:ファイル管理用デバイス
//===========================================================================
void CSprite::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	pFileMgr->SetCurrentPath("Texture");
	
	printf("LOAD TEXTURE[%s]", m_strFileName.c_str() );
	
	m_pTex = pRender->CreateTextureFromFile( m_strFileName.c_str() );
	
	printf( "                 : -> %s\n", m_pTex->IsInvalid() ? "Failed" : "Succeeded" );
	
	/*サイズの設定*/
	m_fSize.x = toF( m_pTex->GetOriginalSize().x / m_DivNum.x );
	m_fSize.y = toF( m_pTex->GetOriginalSize().y / m_DivNum.y );
	
	m_SrcRect.Set( 0, 0, m_fSize.x, m_fSize.y ),
	
	/*スプライトの生成*/
	CreateSprite( pRender, 1000 );
	
}

//============================================================================
//ファイル読み込み
//============================================================================
//[input]
//	pRender:レンダラー用デバイス
//	Num:スプライト数
//===========================================================================
void CSprite::CreateSprite( Renderer::IRender *pRender, Uint32 Num )
{
	if( m_pTex != NULL )
	{	
		m_pSpr = pRender->CreateSprite2D( Num, m_pTex ); 
	}
}

//============================================================================
//処理
//============================================================================
void CSprite::Exec()
{
	if( m_pSpr != NULL )
	{
		/*アニメーションの設定*/
		SetAnimation();
		
		/*描画先*/
		m_DstRect.Set( m_vPos.x, m_vPos.y, m_fSize.x, m_fSize.y );
		
		/*描画元*/
		m_SrcRect.Set( m_Anim.x * m_fSize.x, m_Anim.y * m_fSize.y, m_fSize.x, m_fSize.y );
		
		/*描画*/
		Draw();

	}
}

//============================================================================
//描画
//============================================================================
void CSprite::Draw()
{
	/*描画開始*/
	m_pSpr->Begin();

	/*回転付き描画*/
	m_pSpr->DrawSquareRotate( m_DstRect, m_SrcRect, CColor(255, 255, 255), toI( m_Rot.x ) ); 
	
	/*描画終了*/
	m_pSpr->End();
}

//============================================================================
//レンダリング
//============================================================================
void CSprite::Rendering( )
{
	if( GetVisibleFlag() )
	{	
		m_pSpr->Rendering();
	}
}


//============================================================================
//グレースケール描画
//============================================================================
//[input]
//	pRender:レンダラー用デバイス
//===========================================================================
void CSprite::DrawGrayScale( Renderer::IRender *pRender )
{
	Math::Rect2DF Dst( m_vPos.x, m_vPos.y, m_fSize.x, m_fSize.y );
	
	Math::Rect2DF Src( 0, 0, m_fSize.x, m_fSize.y );
	
	pRender->DrawGrayscale( Dst, CColor( 255, 255, 255 ), Src, m_pTex );
}

//============================================================================
//アニメーションの設定
//============================================================================
void CSprite::SetAnimation()
{
	static int Counter = 0;//内部カウンター
	
	/*当たり判定領域のセット*/
	m_HitRect.Set( m_vPos.x, m_vPos.y, m_fSize.x, m_fSize.y );
	
	if( m_IsAnim )
	{
		/*アニメーションカウンタの増加*/
		Counter++;
		
		if( Counter % m_AnimTime == 0 )
		{
			m_AnimCount ++;
		}
		
		m_Anim.x = m_AnimCount % m_DivNum.x;
		m_Anim.y = m_AnimCount % m_DivNum.y;
		
	}
	
}


//============================================================================
//参照カウンタの増加
//============================================================================
void CSprite::AddRef()
{
	m_pTex->AddRef();
	m_pSpr->AddRef();
}



