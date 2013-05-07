//*============================================================================
//camera.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "camera.h"
#include "player.h"
#include "enemy.h"

#if defined(DEBUG) | (_DEBUG)
	namespace
	{
		Math::Vector3D vDebugPos( 0.0f, 5.0f, 8.0f );
	}
#endif

//=============================================================================
//コンストラクタ
//=============================================================================
CCamera::CCamera() :m_pCamera(NULL)
{
	m_vPos.Set( 0, 50.0f, 50.0f );
	m_vInitPos = m_vPos;
	m_InitRot = m_Rot;
	
	m_vDirection.Set( 0.0f, 0.0f, 8.0f );
	
	m_IsChangeTopView = false;
	
	
}


//=============================================================================
//デストラクタ
//=============================================================================
CCamera::~CCamera()
{
	SAFE_RELEASE( m_pCamera ); 
}

//=============================================================================
//初期化
//=============================================================================
void CCamera::Init()
{
	m_vPos = m_vInitPos;
	m_Rot = m_InitRot;
	
	m_CamCnt = 0;
	
}

//=============================================================================
//処理
//=============================================================================
void CCamera::Exec()
{

}


//=============================================================================
//カメラのセット
//=============================================================================
//[input]
//	pScene:シーン管理デバイス
//=============================================================================
void CCamera::SetCamera( Scene::ISceneManager *pScene )
{
	/*シーンからカメラを取得*/
	m_pCamera = pScene->GetCamera();
	
}

//=============================================================================
//カメラのセット
//=============================================================================
//[input]
//	pScene:シーン管理デバイス
//=============================================================================
//void CCamera::SetCamera( Scene::ICustomizedSceneManager *pScene )
//{
//	/*シーンからカメラを取得*/
//	m_pCamera = pScene->GetCamera();
//	
//}

//=============================================================================
//プロジェクションの設定
//=============================================================================
//[input]
//	fNear:近Z平面クリップ
//	fFar:遠Z面クリップ
//	fov:視野角
//	Width:画面幅
//	Height:画面高さ
//=============================================================================
void CCamera::SetProjection( float fNear, float fFar, Sint32 fov, Sint32 Width, Sint32 Height )
{
	if( m_pCamera != NULL )
	{
		m_pCamera->UpdateProjection( fNear, fFar, DEG_TO_ANGLE(fov), Width, Height );
	}
}

//=============================================================================
//変形の設定
//=============================================================================
//[input]
//	style:姿勢データ
//=============================================================================
void CCamera::SetTransform( Math::Style style )
{
	if( m_pCamera != NULL )
	{
		/*カメラの状態のリセット*/
		m_pCamera->Reset();
		
		/*変形を適用*/
		m_pCamera->SetTransform( style );
		
		/*カメラの更新*/
		m_pCamera->Update();
	}
}

//=============================================================================
//変形の設定
//=============================================================================
void CCamera::SetTransform( )
{
	if( m_pCamera != NULL )
	{
		// カメラの目標位置
		Math::Vector3D vDirection( 0.0f, 0.0f, 8.0f );
		Math::Matrix mTemp;
		mTemp.RotationX( toI( m_Rot.x ) );
		
		vDirection.TransformNormal( mTemp );
		mTemp.RotationY( toI( m_Rot.y )  );
		vDirection.TransformNormal( mTemp );
		
		//mTemp.RotationX( m_Rot.z );
		//vDirection.TransformNormal( mTemp );

		Math::Vector3D vCameraTarget = m_vTarget + vDirection;

		//// ちょっとずつ近づく感じに
		//if( vCameraTarget.y > 3.0 )
		//{	
		//	m_vPos.y =  m_vTarget.y + 3;
		//	mTemp.RotationX( DEG_TO_ANGLE( 60 ) );
		//	vDirection.TransformNormal( mTemp );
		//}
		
		//if( vCameraTarget
		
			m_vPos += ( vCameraTarget - m_vPos ) * 0.1f;
		
		

		// カメラのトランスフォーム
		m_Style.TransformReset();

		m_Style.LookAt(
			m_vPos,				// カメラ位置
			m_vTarget,							// カメラターゲット（キャラの頭）
			Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// 上方向
			
		m_Style.GetFront( m_vFront );
		m_Style.GetRight( m_vRight );
		m_Style.GetUp( m_vUp );
			
		/*カメラの状態のリセット*/
		m_pCamera->Reset();
		
		/*変形を適用*/
		m_pCamera->SetTransform( m_Style );
		
		/*カメラの更新*/
		m_pCamera->Update();
	}
}

//=============================================================================
//変形の設定
//=============================================================================
//[input]
//	pPlayer:プレイヤーオブジェクト
//=============================================================================
void CCamera::SetTransform( CPlayer *pPlayer )
{
	if( m_pCamera != NULL )
	{
		// カメラの目標位置
		Math::Vector3D vDirection( 0.0f, 0.0f, 8.0f );
		Math::Matrix mTemp;
		mTemp.RotationX( toI( m_Rot.x ) );
		
		vDirection.TransformNormal( mTemp );
		mTemp.RotationY( toI( m_Rot.y )  );
		vDirection.TransformNormal( mTemp );
		
		static float fZoom = 0.1f;
		
		//mTemp.RotationX( m_Rot.z );
		//vDirection.TransformNormal( mTemp );
		
		//m_vDirection = vDirection;
		
		
		if( pPlayer->GetRotate().x > DEG_TO_ANGLE( 90 ) && pPlayer->GetRotate().x < DEG_TO_ANGLE( 270 ) ) 
		{
			fZoom += 0.1f;
		}
		
		else
		{
			fZoom -= 0.1f;
		}
		
		const float fMAX_ZOOM = 0.0f;
		const float fMIN_ZOOM = 0.0f;
		
		if( fZoom > fMAX_ZOOM )
		{
			fZoom = fMAX_ZOOM;
		}
		
		else if( fZoom < fMIN_ZOOM )
		{
			fZoom = fMIN_ZOOM;
		}
		
		Math::Vector3D vZoom( 0.0f, 0.0f, fZoom );
		
		Math::Vector3D vCameraTarget = m_vTarget + vDirection + vZoom;
		
		Math::Vector3D vCamDir = ( vCameraTarget - m_vPos );
		
		m_vPos += vCamDir * 0.1f;
		
		

		// カメラのトランスフォーム
		m_Style.TransformReset();

		m_Style.LookAt(
			m_vPos,				// カメラ位置
			m_vTarget,							// カメラターゲット（キャラの頭）
			Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// 上方向
			
		m_Style.GetFront( m_vFront );
		m_Style.GetRight( m_vRight );
			
		/*カメラの状態のリセット*/
		m_pCamera->Reset();
		
		/*変形を適用*/
		m_pCamera->SetTransform( m_Style );
		
		/*カメラの更新*/
		m_pCamera->Update();
	}

}

//=============================================================================
//変形の設定
//=============================================================================
//[input]
//	Angle:回転角度
//	IsCamMove:カメラが移動中かどうか
//=============================================================================
void CCamera::SetTransform( Sint32 Angle, bool IsCamMove )
{
	if( m_pCamera != NULL )
	{
	
		// カメラの目標位置
		Math::Vector3D vDirection( 0.0f, 0.0f, 8.0f );
		Math::Matrix mTemp;

		static float fZoom = 0.1f;
		
		//mTemp.RotationX( m_Rot.z );
		//vDirection.TransformNormal( mTemp );
		
		//m_vDirection = vDirection;
		
		
		
		if( IsCamMove )
		{
			if( Angle > DEG_TO_ANGLE( 90 ) && 
				Angle < DEG_TO_ANGLE( 270 ) ) 
			{
				fZoom += 0.1f;
			}
			
			else
			{
				fZoom -= 0.1f;
			}
		}
		
		else
		{
			fZoom = 0.0f;
		}
		
		const float fMAX_ZOOM = 5.0f;
		const float fMIN_ZOOM = 0.0f;
		
		if( fZoom > fMAX_ZOOM )
		{
			fZoom = fMAX_ZOOM;
		}
		
		else if( fZoom < fMIN_ZOOM )
		{
			fZoom = fMIN_ZOOM;
		}
		
		
		mTemp.RotationX( toI( m_Rot.x ) );
		
		vDirection.TransformNormal( mTemp );
		mTemp.RotationY( toI( m_Rot.y ) );
		
		vDirection.TransformNormal( mTemp );
		
	
		Math::Vector3D vCameraTarget = m_vTarget + vDirection - m_vFront * fZoom;
		
		
		Math::Vector3D vCamDir = ( vCameraTarget - m_vPos );
		
		m_vPos += vCamDir * 0.1f;
		
		// カメラのトランスフォーム
		m_Style.TransformReset();

		m_Style.LookAt(
			m_vPos,				// カメラ位置
			m_vTarget,							// カメラターゲット（キャラの頭）
			Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// 上方向
			
		m_Style.GetFront( m_vFront );
		m_Style.GetRight( m_vRight );
			
		/*カメラの状態のリセット*/
		m_pCamera->Reset();
		
		/*変形を適用*/
		m_pCamera->SetTransform( m_Style );
		
		/*カメラの更新*/
		m_pCamera->Update();
	}

}

//=============================================================================
//変形の設定(トリの場合)
//=============================================================================
//[input]
//	Angle:回転角度
//	IsCamMove:カメラが移動中かどうか
//=============================================================================
void CCamera::SetTransformBird( Sint32 Angle, bool IsCamMove )
{
	if( m_pCamera != NULL )
	{
	
		// カメラの目標位置
		Math::Vector3D vDirection( 0.0f, 0.0f, 8.0f );
		Math::Matrix mTemp;

		static float fZoom = 0.1f;
		
		//mTemp.RotationX( m_Rot.z );
		//vDirection.TransformNormal( mTemp );
		
		//m_vDirection = vDirection;
		
		
		
		if( IsCamMove )
		{
			if( Angle > DEG_TO_ANGLE( 90 ) && 
				Angle < DEG_TO_ANGLE( 270 ) ) 
			{
				fZoom += 0.1f;
			}
			
			else
			{
				fZoom -= 0.1f;
			}
		}
		
		else
		{
			fZoom = 0.0f;
		}
		
		const float fMAX_ZOOM = 5.0f;
		const float fMIN_ZOOM = 0.0f;
		
		if( fZoom > fMAX_ZOOM )
		{
			fZoom = fMAX_ZOOM;
		}
		
		else if( fZoom < fMIN_ZOOM )
		{
			fZoom = fMIN_ZOOM;
		}
		
		
		mTemp.RotationX( toI( m_Rot.x ) );
		
		vDirection.TransformNormal( mTemp );
		mTemp.RotationY( toI( m_Rot.y ) );
		
		vDirection.TransformNormal( mTemp );
		
	
		Math::Vector3D vCameraTarget = m_vTarget + vDirection - m_vFront * fZoom;
		
		
		Math::Vector3D vCamDir = ( vCameraTarget - m_vPos );
		
		m_vPos += vCamDir * 0.1f;
		
		// カメラのトランスフォーム
		m_Style.TransformReset();

		m_Style.LookAt(
			m_vPos + Math::Vector3D( 0, 2, 0 ),				// カメラ位置
			m_vTarget,							// カメラターゲット（キャラの頭）
			Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// 上方向
			
		m_Style.GetFront( m_vFront );
		m_Style.GetRight( m_vRight );
			
		/*カメラの状態のリセット*/
		m_pCamera->Reset();
		
		/*変形を適用*/
		m_pCamera->SetTransform( m_Style );
		
		/*カメラの更新*/
		m_pCamera->Update();
	}

}


//=============================================================================
//キャプチャー時のカメラ変形
//=============================================================================
//[input]
//	pPlayer:プレイヤーオブジェクト
//	pTarget:ターゲットオブジェクト
//=============================================================================
void CCamera::SetTransformCap( CPlayer *pPlayer, CEnemy *pTarget )
{
	// カメラの目標位置
	Math::Vector3D vDirection( 0.0f, 0.0f, 8.0f );
	Math::Matrix mTemp;

	static float fZoom = 0.1f;
	
	//mTemp.RotationX( m_Rot.z );
	//vDirection.TransformNormal( mTemp );
	
	//m_vDirection = vDirection;
	
	
	const float fMAX_ZOOM = 5.0f;
	const float fMIN_ZOOM = 0.0f;
	
	if( fZoom > fMAX_ZOOM )
	{
		fZoom = fMAX_ZOOM;
	}
	
	else if( fZoom < fMIN_ZOOM )
	{
		fZoom = fMIN_ZOOM;
	}
	
	
	mTemp.RotationX( toI( m_Rot.x ) );
	
	vDirection.TransformNormal( mTemp );
	mTemp.RotationY( toI( m_Rot.y ) );
	
	vDirection.TransformNormal( mTemp );
	

	Math::Vector3D vCameraTarget = m_vTarget + vDirection - m_vFront * fZoom;
	
	
	Math::Vector3D vCamDir = ( vCameraTarget - m_vPos );
	
	m_vPos += vCamDir * 0.1f;
	
	// カメラのトランスフォーム
	m_Style.TransformReset();

	m_Style.LookAt(
		m_vPos,				// カメラ位置
		m_vTarget,							// カメラターゲット（キャラの頭）
		Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// 上方向
		
	m_Style.GetFront( m_vFront );
	m_Style.GetRight( m_vRight );
		
	/*カメラの状態のリセット*/
	m_pCamera->Reset();
	
	/*変形を適用*/
	m_pCamera->SetTransform( m_Style );
	
	/*カメラの更新*/
	m_pCamera->Update();

}



//=============================================================================
//カメラの回転
//=============================================================================
//[input]
//	Type:カメラの回転タイプ
//=============================================================================
void CCamera::RotateCamera( eRollType Type )
{
	if( m_pCamera != NULL )
	{
		/*左回転の場合*/
		if( Type == ROLL_LEFT )
		{
			m_Rot.y -= DEG_TO_ANGLE(1);
		}
		
		/*右回転の場合*/
		else if( Type == ROLL_RIGHT )
		{
			m_Rot.y += DEG_TO_ANGLE(1);
		}
		
		
		/*上回転の場合*/
		else if( Type == ROLL_UP )
		{
			m_Rot.x -= DEG_TO_ANGLE(1);
		}
		
		/*下回転の場合*/
		else if( Type == ROLL_DOWN )
		{
			m_Rot.x += DEG_TO_ANGLE(1);
		}
	}
}

//=============================================================================
//カメラの回転補正
//=============================================================================
void CCamera::RotateAdjust()
{
	const int MAX_ANGLE = 30;//カメラの最大角度
	
	if( m_Rot.x > DEG_TO_ANGLE( MAX_ANGLE - 1 ) )
	{
		m_Rot.x = DEG_TO_ANGLE( MAX_ANGLE - 1 );
	}
	
	else if( m_Rot.x < DEG_TO_ANGLE( -MAX_ANGLE + 1 ) )
	{
		m_Rot.x = DEG_TO_ANGLE( -MAX_ANGLE + 1 );
	}
	
	if( m_Rot.y >= DEG_TO_ANGLE( 360 ) )
	{
		m_Rot.y = DEG_TO_ANGLE( 0 );
	}
	
	if( m_Rot.y <= DEG_TO_ANGLE( -360 ) )
	{
		m_Rot.y = DEG_TO_ANGLE( 0 );
	}
	
	
}



//=============================================================================
//変形の設定
//=============================================================================
void CCamera::SetTransform2( )
{
	if( m_pCamera != NULL )
	{
		// カメラの目標位置
		Math::Vector3D vDirection( 0.0f, 0.0f, 8.0f );
		Math::Matrix mTemp;
		mTemp.RotationX( toI( m_Rot.x ) );
		
		vDirection.TransformNormal( mTemp );
		mTemp.RotationY( toI( -m_Rot.y ) );
		vDirection.TransformNormal( mTemp );

		Math::Vector3D vCameraTarget = m_vTarget + vDirection;

		/*ちょっとずつ近づく感じに*/
		m_vPos = m_vTarget + Math::Vector3D( 0.0f, 0.8f, 0.0f );
		
		// カメラのトランスフォーム
		m_Style.TransformReset();
		
		m_Style.LookAt(
			m_vPos,				// カメラ位置
			vCameraTarget,							// カメラターゲット（キャラの頭）
			Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// 上方向
			

		/*カメラの状態のリセット*/
		m_pCamera->Reset();
		
		/*変形を適用*/
		m_pCamera->SetTransform( m_Style );
		
		/*カメラの更新*/
		m_pCamera->Update();
	}
}

//=============================================================================
//変形の設定
//=============================================================================
void CCamera::SetTransform3( )
{
	if( m_pCamera != NULL )
	{
		// カメラの目標位置
		Math::Vector3D vDirection( 0.0f, 100.0f, 0.0f );
		Math::Matrix mTemp;
		mTemp.RotationX( toI( m_Rot.x ) );
		
		vDirection.TransformNormal( mTemp );
		mTemp.RotationY( toI( m_Rot.y ) );
		vDirection.TransformNormal( mTemp );
		
		//mTemp.RotationX( m_Rot.z );
		//vDirection.TransformNormal( mTemp );

		Math::Vector3D vCameraTarget = m_vTarget + vDirection;

		// ちょっとずつ近づく感じに
		m_vPos = vCameraTarget;

		// カメラのトランスフォーム
		m_Style.TransformReset();

		m_Style.LookAt(
			m_vPos,				// カメラ位置
			m_vTarget,							// カメラターゲット（キャラの頭）
			Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// 上方向

		/*カメラの状態のリセット*/
		m_pCamera->Reset();
		
		/*変形を適用*/
		m_pCamera->SetTransform( m_Style );
		
		/*カメラの更新*/
		m_pCamera->Update();
	}
}

//=============================================================================
//変形の設定(デモ用)
//=============================================================================
void CCamera::SetTransformDemo( CEnemy *pEnemy )
{
	if( m_pCamera != NULL )
	{
		m_CamCnt++;
		
		const Sint32 TIME_MAX = 60 * 3;
		
		// カメラの目標位置
		Math::Vector3D vDirection( 0.0f, 0.0f, 8.0f );
		Math::Matrix mTemp;
		mTemp.RotationX( toI( m_Rot.x ) );
		
		vDirection.TransformNormal( mTemp );
		
		mTemp.RotationY( ::Interpolation::Flat( DEG_TO_ANGLE(0), DEG_TO_ANGLE( 180 ), TIME_MAX, m_CamCnt ) );
		vDirection.TransformNormal( mTemp );
		
		if( m_CamCnt > TIME_MAX )
		{
			m_CamCnt = 0;
		}
		
		//mTemp.RotationX( m_Rot.z );
		//vDirection.TransformNormal( mTemp );

		Math::Vector3D vCameraTarget = m_vTarget + vDirection;

		//// ちょっとずつ近づく感じに
		//if( vCameraTarget.y > 3.0 )
		//{	
		//	m_vPos.y =  m_vTarget.y + 3;
		//	mTemp.RotationX( DEG_TO_ANGLE( 60 ) );
		//	vDirection.TransformNormal( mTemp );
		//}
		//
		//m_vPos += Math::Vector3D( 0, 0, -2 );
		//
		//m_vPos += ( vCameraTarget - m_vPos ) * 0.1f;

		// カメラのトランスフォーム
		m_Style.TransformReset();

		if( pEnemy->GetStTypeName().compare( "アメウス" ) == 0 )
		{
			m_Style.LookAt(
				pEnemy->GetPosition() + Math::Vector3D( 5.0f, 10.0, -5.0f ),				// カメラ位置
				pEnemy->GetPosition(),							// カメラターゲット（キャラの頭）
				Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// 上方向
		}
		
		else
		{
			m_Style.LookAt(
				pEnemy->GetPosition() + Math::Vector3D( 10.0f, 10.0, -10.0f ),				// カメラ位置
				pEnemy->GetPosition(),							// カメラターゲット（キャラの頭）
				Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// 上方向
		}
				
		/*カメラの状態のリセット*/
		m_pCamera->Reset();
		
		/*変形を適用*/
		m_pCamera->SetTransform( m_Style );
		
		/*カメラの更新*/
		m_pCamera->Update();
	}
}





//=============================================================================
//位置の設定
//=============================================================================
//[input]
//	vPos:位置
//=============================================================================
void CCamera::SetPosition( Math::Vector3D vPos )
{
	m_vPos = vPos;
}

//=============================================================================
//回転角度の設定
//=============================================================================
//[input]
//	Rot:回転角度
//=============================================================================
void CCamera::SetRotate( Math::Point3DI Rot )
{
	m_Rot = Rot;
}

//=============================================================================
//ターゲットの設定
//=============================================================================
//[input]
//	vTarget:ターゲットの位置
//=============================================================================
void CCamera::SetTargetPos( Math::Vector3D vTarget )
{
	m_vTarget = vTarget;
}

//=============================================================================
//姿勢データ設定	
//=============================================================================
//[input]
//	style:姿勢データ
//=============================================================================
void CCamera::SetStyle( Math::Style style )	
{
	m_Style = style;
}



