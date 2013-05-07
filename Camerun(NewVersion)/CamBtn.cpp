//*============================================================================
//CamBtn.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "CamBtn.h"
#include "ResourceManager.h"
#include "mouse.h"

//=============================================================================
//namespace
//=============================================================================
namespace
{
	Math::Vector2D vMousePos( 0.0f, 0.0f );
	Math::Vector2D vDir( 0.0f, 0.0f );
	Math::Vector2D vPos( 0.0f, 0.0f );
	
}

//============================================================================
//コンストラクタ
//============================================================================
//[input]
//	pName:データ名
//	vPos:表示位置
//===========================================================================
CCamButton::CCamButton( const char *pName, Math::Vector2D vPos ) 
 :CSprite( pName, vPos ),
  m_IsCamMove( false )
{
	m_pMarkerSpr = new CCamBar( "bar.png", Math::Vector2D( 699, 509 ) );
	m_pRollSpr = new CSprite( "roll.png", Math::Vector2D( 640, 450 ) );
	m_pResetBtnSpr = new CSprite( "reset.png", Math::Vector2D( 625, 438 ) );
	
}

//============================================================================
//デストラクタ
//============================================================================
CCamButton::~CCamButton()
{
	SAFE_DELETE( m_pResetBtnSpr );
	SAFE_DELETE( m_pRollSpr );
	SAFE_DELETE( m_pMarkerSpr );
}

//============================================================================
//ファイル読み込み
//============================================================================
//[input]
//	pRender:レンダラー用デバイス
//	pFileMgr:ファイル管理用デバイス
//===========================================================================
void CCamButton::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	CSprite::Load( pRender, pFileMgr );
	
	m_pMarkerSpr->Load( pRender, pFileMgr );
	
	m_pRollSpr->Load( pRender, pFileMgr );
	
	m_pResetBtnSpr->Load( pRender, pFileMgr );
	
	m_pResetBtnSpr->SetDivNumX( 3 ); 
	
	
	
}

//============================================================================
//初期化
//============================================================================
void CCamButton::Init()
{
	m_pRollSpr->SetVisibleFlag( false );
}

//============================================================================
//処理
//============================================================================
void CCamButton::Exec()
{
	CSprite::Exec();
	
	m_pRollSpr->Exec();
	
	m_pMarkerSpr->Exec();	
	
	m_pResetBtnSpr->Exec();
	
}

//============================================================================
//レンダリング
//============================================================================
void CCamButton::Rendering()
{
	CSprite::Rendering();
	
	m_pRollSpr->Rendering();
	
	m_pMarkerSpr->Rendering();
	
	m_pResetBtnSpr->Rendering();
}

//============================================================================
//カメラリセット
//============================================================================
//[input]
//	pCam:カメラデータ
//	pPlayer:プレイヤーオブジェクト
//===========================================================================
void CCamButton::Reset( CCamera *pCam[], CPlayer *pPlayer )
{
	/*カメラリセット*/
	if( ::Collision::Point_Rect( vMousePos, m_pResetBtnSpr->GetHitRect() ) )
	{
		Math::Point3DI Rot;
		
		Rot.x = pPlayer->GetRotate().y;
		Rot.y = NORMALIZE_ANGLE( pPlayer->GetRotate().x );
		Rot.z = pPlayer->GetRotate().z;
		
		if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
		{
			m_IsCamReset = true;
		
			for( int i = 0;i < SCREEN_MAX;++i )
			{	
				pCam[i]->SetRotate( Rot );
			}
			
			
		}
		
		else
		{
			GetResetButton()->SetAnimXID( 2 );
		}
	}
	
	else if( CCommonObject::GetMouse()->GetMouse()->GetStateW() == MOUSE_PUSH )
	{
		Math::Point3DI Rot;
		
		Rot.x = pPlayer->GetRotate().y;
		Rot.y = NORMALIZE_ANGLE( pPlayer->GetRotate().x );
		Rot.z = pPlayer->GetRotate().z;
		
		m_IsCamReset = true;
	
		for( int i = 0;i < SCREEN_MAX;++i )
		{	
			pCam[i]->SetRotate( Rot );
		}
	}
	
	else
	{
		m_IsCamReset = false;
		GetResetButton()->SetAnimXID( 1 );
		
		
	}

}

//============================================================================
//移動
//============================================================================
//[input]
//	pCam:カメラデータ
//	pResMgr:リソース管理デバイス
//	pPlayer:プレイヤーオブジェクト
//===========================================================================
void CCamButton::Move( CCamera *pCam[], CResourceManager *pResMgr, CPlayer *pPlayer )
{
	
	vMousePos = CCommonObject::GetMouse()->GetMousePos();
	
	Math::Point3DI TargetRot( DEG_TO_ANGLE(0), DEG_TO_ANGLE(0), DEG_TO_ANGLE(0) );//ターゲットの回転方向
	
	Math::Rect2DF HitRect = m_pRollSpr->GetHitRect();
	
	HitRect.x = m_pRollSpr->GetHitRect().x + 10.0f;
	HitRect.y = m_pRollSpr->GetHitRect().y + 10.0f;
	
	/*カメラ回転条件*/
	if( Collision::Point_Rect( vMousePos, HitRect ) )

	{
		if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
		{	
			m_IsCamMove = true;
		}
		
		m_pRollSpr->SetVisibleFlag( true );
		
	}
	
	else
	{
		m_pRollSpr->SetVisibleFlag( false );
	}
	
	/*カメラ移動状態のとき、カメラマーカーを移動させる*/
	if( m_IsCamMove )
	{
		vPos = Math::Vector2D( vMousePos.x - 2.0f, vMousePos.y - 2.0f ) - m_pMarkerSpr->GetInitPos();
		
		const float fROT_SPEED = 0.8f;
		
		TargetRot.y = toI( vPos.x * fROT_SPEED );
		TargetRot.x = toI( -vPos.y * fROT_SPEED );
		
		m_pMarkerSpr->MoveAdjust( vPos );
		
		Sint32 Angle = Math::ATan2( vPos.x, vPos.y );
		
		#if defined( DEBUG ) | (_DEBUG )
			CCommonObject::GetAppli()->GetRenderer()->DebugPrint( Math::Point2DI( 0, 200 ), CColor( 255, 255, 255 ),
												 "vPos:x:%f, y:%f", vPos.x, vPos.y );
												 
			CCommonObject::GetAppli()->GetRenderer()->DebugPrint( Math::Point2DI( 0, 120 ), CColor( 255, 255, 255 ),
												 "Angle:%d", Angle );
												 
												 
											
		#endif
		
		
		/*カメラ回転する*/
		for( int i = 0;i < SCREEN_MAX;++i )
		{	
			pCam[i]->AddRotate( TargetRot );
		}
		
		//カメラとキャラの回転を同期(X方向のみ)
		if( pPlayer->GetCaptureFlag() )
		{
			pPlayer->GetCapedEnemy()->SetRotate( Math::Point3DI( pCam[SCREEN_MAIN]->GetRotate().y, 
												pPlayer->GetCapedEnemy()->GetRotate().y,
												pPlayer->GetCapedEnemy()->GetRotate().z ) );
												
			pPlayer->SetRotate( Math::Point3DI( pCam[SCREEN_MAIN]->GetRotate().y, 
												pPlayer->GetCapedEnemy()->GetRotate().y,
												pPlayer->GetCapedEnemy()->GetRotate().z ) );
												
		}
		
		else
		{
			pPlayer->SetRotate( Math::Point3DI( pCam[SCREEN_MAIN]->GetRotate().y, 
												pPlayer->GetRotate().y,
												pPlayer->GetRotate().z ) );
		}
		
		//pPlayer->AddRotate( Math::Vector3D( vTargetRot.y,0, 0 ) );
		
		if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_FREE )
		{
			m_IsCamMove = false;
		}
	
	}
	
	else
	{
		m_pMarkerSpr->SetPosition( m_pMarkerSpr->GetInitPos() );
	}
	
	
}

