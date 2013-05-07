//*============================================================================
//player.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "player.h"
#include <math.h>
#include "camera.h"
#include <fstream>
#include "SceneGameMain.h"

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	pName:データ名
//	vPos:位置
//=============================================================================
CPlayer::CPlayer( const char *pName, Math::Vector3D vPos ) 
 :CCharacter( pName, vPos )
{
	m_IsDead = false;
	m_IsExistAnim = true;
	
	m_vScale.Set( 0.5f, 0.5f, 0.5f );
	
	m_vInitScale = m_vScale;
	
	m_Rot.x = DEG_TO_ANGLE( 0 );
	
	m_InitRot = m_Rot;
	
	m_fGravity = 0.0f;
	
	m_fAccel = 0.01f;
	
	m_fStSpeed = 0.001f;
	
	m_fMaxSpeed = 1.0f;
	
	m_eAnimState = ANIM_STANDBY;
	
	m_pCapedEnemy = NULL;
	
	m_IsJumpFlag = false;
	m_IsDead = false;
	m_IsCapture = false;
	m_eAnimState = ANIM_STANDBY;
	m_eState = STATE_NONE;
	
	m_RelCount = 0;
	
	
	m_pMinSpr = new CSprite( "mini_player.dds", Math::Vector2D( m_vPos.x, m_vPos.y ) );
	
}


//=============================================================================
//デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
	SAFE_DELETE( m_pMinSpr );
}

//=============================================================================
//初期化
//=============================================================================
void CPlayer::Init()
{
	if( CSceneBase::GetTutorialFlag() )
	{
		m_vInitPos = Math::Vector3D( 46, 7, -16 );
	}
	
	else
	{
		m_vInitPos = Math::Vector3D( 0, 7, -70 );
	
	}

	m_vPos = m_vInitPos;
	
	
	m_vScale = m_vInitScale;
	
	m_IsJumpFlag = false;
	m_IsDead = false;
	m_IsCapture = false;
	m_eAnimState = ANIM_STANDBY;
	m_eState = STATE_NONE;
	
	m_Rot = m_InitRot;
	
	m_fGravity = 0.0f;
	
	m_RelCount = 0;
	
}

//============================================================================
//ファイル読み込み
//============================================================================
//[input]
//	pRender:レンダラー用デバイス
//	pFileMgr:ファイル管理用デバイス
//===========================================================================
void CPlayer::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	CCharacter::Load( pRender, pFileMgr );
	
	m_pMinSpr->Load( pRender, pFileMgr );
}

	
//=============================================================================
//処理
//=============================================================================
void CPlayer::Exec()
{
	if( m_IsCapture )
	{
		SetPosition( m_pCapedEnemy->GetCatchPos() );
	}
	
	for( int Anim = 0;Anim < ANIM_MAX;++Anim )
	{
		m_fAnimTime[Anim] += 0.5f;
		
		float fLast = m_pActorModel[m_ActorIndex]->GetAnimationLastTime( m_AnimID[Anim] );
		
		/*時間が最後まで到達*/
		while( m_fAnimTime[Anim] > fLast ) 
		{
			/*最初に戻す*/
			m_fAnimTime[Anim] -= fLast;
		}
		
	}

	/*状態の処理*/
	StateExec();
	
	/*捕獲判定ボックスの生成*/
	CreateCapBox();
	
	CCharacter::Exec();
}


//=============================================================================
//ミニキャラの表示
//=============================================================================
void CPlayer::ShowMiniChara()
{
	m_pMinSpr->Exec();
	
	m_pMinSpr->Rendering();
}

//=============================================================================
//レンダリング
//=============================================================================
void CPlayer::Rendering()
{
	#if defined ( DEBUG ) | ( _DEBUG )
	
		Collision::CBox Box[] =
		{
			m_CapChkBox,
			m_ShootChkBox,
		};
		
		CColor Color[] =
		{
			CColor( 255, 255, 255 ),
			CColor( 255, 0, 0 ),
		};
		
		const int BOX_NUM = 2;//ボックスの数
		
		/*デバッグ用の箱の描画*/
		m_pLine3D->Begin();
		
		for( int i = 0;i < BOX_NUM;++i )
		{
			m_pLine3D->PushBox( Box[i], Color[i] );
		}
		
		m_pLine3D->End();
		
	#endif
		
	CCharacter::Rendering();
	
	
}


//=============================================================================
//アニメーション用処理
//=============================================================================
void CPlayer::AnimExec()
{
	
	//if( m_eAnimState == ANIM_STANDBY )
	//{
	//
	//}	
	//
	//else if( m_eAnimState == ANIM_CHANGESTART )
	//{
	//	m_fAnimTime[ANIM_NEXT] = 0.0f;
	//	m_fWeight = 0.0f;
	//	
	//	m_eAnimState = ANIM_CHANGE;
	//}
	//
	//else if( m_eAnimState == ANIM_CHANGE )
	//{
	//	UpdateAnimation();
	//}
	//
	
}

//=============================================================================
//状態毎の処理
//=============================================================================
void CPlayer::StateExec()
{
	switch( m_eState )
	{
		/*何もしてない状態*/
		case STATE_NONE:
		{
			m_AnimID[ANIM_NOW] = ANIM_STAND;
			
			break;
		}
		
		/*捕獲開始*/
		case STATE_CAPSTART:
		{
			static int count = 0;
			
			const int MAX_COUNT = 60 * 2;
			
			m_AnimID[ANIM_NOW] = ANIM_CAPMOVE;
			
			count++;
			
			//if( count < 60 )
			//{	
			//	m_vPos.y += 1.0f;
			//}
			//
			//else if( count > 60 )
			//{	
			//	m_vPos.x += ( m_pCapedEnemy->GetCatchPos().x - m_vPos.x ) * 0.01f;
			//}
			
			/*ブースト音の再生*/
			
			
			m_vPos.x = Interpolation::Add( m_vCapedPos.x, m_pCapedEnemy->GetCatchPos().x, MAX_COUNT, count  );
			m_vPos.y = Interpolation::Sin( m_vCapedPos.y , m_pCapedEnemy->GetCatchPos().y + 5.0f, MAX_COUNT, count);
			//m_vPos.y = Interpolation::Neville( m_vCapedPos.y, m_vCapedPos.y + m_pCapedEnemy->GetCatchPos().y + 2.0, 
			//									 m_pCapedEnemy->GetCatchPos().y, count );

			m_vPos.z = Interpolation::Add( m_vCapedPos.z, m_pCapedEnemy->GetCatchPos().z, MAX_COUNT, count );
			m_Rot.y = Math::ATan2( m_vCapedPos.y, m_vCapedPos.z );
			//Interpolation::Flat( DEG_TO_ANGLE( 90 ), DEG_TO_ANGLE( -80 ), MAX_COUNT, count );
			
			//if( count < 30 )
			//{
			//	CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_BOOST );
			//}
			
			
			if( m_vPos.y < m_pCapedEnemy->GetCatchPos().y  && count > MAX_COUNT / 2 )
			{
				/*小さくする*/
				const float fSCALE = 0.3f;
				
				SetScale( Math::Vector3D( fSCALE, fSCALE, fSCALE ) );
				
				/*噛み付き音の再生*/
				CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_BITE );
				
				SetState( STATE_CAPTURE );
				
				m_IsCapture = true;
				
				count = 0;	
				
			}
			
			break;
		}
		
		/*捕獲中の時*/
		case STATE_CAPTURE:
		{
			
			m_AnimID[ANIM_NOW] = ANIM_CAPING;
				
			break;
		}
		
		/*解放開始*/
		case STATE_RELSTART:
		{
			m_AnimID[ANIM_NOW] = ANIM_CAPSTART;
			
			const Uint32 MAX_COUNT = 60 * 3;
			
			m_RelCount++;
			
			m_vPos.y = Interpolation::Sin( m_pCapedEnemy->GetPosition().y,
										   m_pCapedEnemy->GetPosition().y + 5.0f,
										   MAX_COUNT, m_RelCount );
			
			m_vPos.x = Interpolation::Flat( m_pCapedEnemy->GetPosition().x,
											 m_pCapedEnemy->GetPosition().x - m_vFront.x, MAX_COUNT, m_RelCount );
			
			m_vPos.z = Interpolation::Flat( m_pCapedEnemy->GetPosition().z, 
											m_pCapedEnemy->GetPosition().z - m_vFront.z, MAX_COUNT, m_RelCount );
			
			m_Rot.y = Interpolation::Flat( DEG_TO_ANGLE( -80 ), DEG_TO_ANGLE( 0 ), MAX_COUNT, m_RelCount );
			
			if( m_RelCount > MAX_COUNT )
			{
				m_eState = STATE_RELEASE;
				
				/*スケールを元に戻す*/
				SetScale( m_vInitScale );
				
				m_RelCount = 0;
			}
			
			
			break;
		}
		
		/*解放時*/
		case STATE_RELEASE:
		{
			m_IsCapture = false;
			
			m_pCapedEnemy->SetCapdFlag( false );
	
			m_pCapedEnemy->SetState( CEnemy::STATE_RELEASE );
			
			m_eState = STATE_NONE;
		
			
			break;
		}
		
		/*移動中の時*/
		case STATE_MOVING:
		{
			m_AnimID[ANIM_NOW] = ANIM_WALK;
			
			break;
		}
		
		
		
		/*停止中*/
		case STATE_STOP:
		{
			break;
		}
		
		/*電車に当たったとき*/
		case STATE_HIT_TRAIN:
		{
			static int count = 0;
			
			m_vPos.y += 1;
			
			if( ++count > 60 * 1 )
			{
				count = 0;
				m_eState = STATE_NONE;
			}
				
			break;
		}
		
		/*敵に当たったとき*/
		case STATE_HIT_ENEMY:
		{
			static int count = 0;
			
			//m_fSpeed = 0.0f;

			m_vPos += GetFront() * 0.01f;
			
			if( ++count > 30 )
			{
				count = 0;
				m_eState = STATE_NONE;
			}
			
			break;
		}
		
		
	}
	
	
}

//==============================================================================
//カメラモードの切り替え
//==============================================================================
//[input]
//	pSnd:再生するサウンド
//==============================================================================
void CPlayer::ChangeCameraMode( Sound::ISound *pSnd )
{
}

//=============================================================================
//アニメーションの更新
//=============================================================================
void CPlayer::UpdateAnimation()
{
	if( m_AnimID[ANIM_NOW] != m_AnimID[ANIM_NEXT] )
	{
		/*二秒で切り替える*/
		m_fWeight += 1.0f / 120.0f;
		
		if( m_fWeight >= 1.0f )
		{
			m_fWeight = 0.0f;
			m_fAnimTime[ANIM_NOW] = m_fAnimTime[ANIM_NEXT];
			m_AnimID[ANIM_NOW] = m_AnimID[ANIM_NEXT];
			m_eAnimState = ANIM_STANDBY;
		}
	}
}

//=============================================================================
//アニメーションの設定
//=============================================================================
//[input]
//	animID:設定するアニメーションID
//=============================================================================
void CPlayer::ChangeAnimation( int animID )
{
	m_AnimID[ANIM_NEXT] = animID;
}

//==============================================================================
//地面補正(プレイヤーのY座標が一定以下になったとき初期座標に戻してやる)
//==============================================================================
void CPlayer::GroundAdjust()
{
	if( GetCaptureFlag() )
	{
		if( m_vPos.y <= -30.0f )
		{
			SetState( STATE_RELSTART );
			
			m_fGravity = 0.0f;
			m_vPos = m_vInitPos;
			
		}
	}
	
	else
	{
		if( m_vPos.y <= -30.0f )
		{
			m_fGravity = 0.0f;
			m_vPos = m_vInitPos;
		}
	}
}

//==============================================================================
//移動処理
//==============================================================================
//[input]
//	vTargetPos:対象位置
//	pCam:カメラデバイス
//	pField:チェックするマップ
//	IsShowMark:マークが表示されているか
//[return]
//	移動中かどうか
//==============================================================================
bool CPlayer::Move( Selene::Math::Vector3D vTargetPos, CCamera *pCam, 
					CField *pField, bool IsShowMark )
{
	if( IsShowMark )
	{
		/*カメラ方向を基準に移動*/
		
		m_vDirection.x = vTargetPos.x * pCam->GetRight().x + vTargetPos.y * (-pCam->GetFront().x);
		m_vDirection.y = 0.0f;
		m_vDirection.z = vTargetPos.x * pCam->GetRight().z + vTargetPos.y * (-pCam->GetFront().z);
		
		//
		
		
		float fLength = m_vDirection.Length();
		
		m_fSpeed = fLength * m_fStSpeed ;
		
		if( m_fSpeed > 2.0f )
		{
			m_fSpeed = 2.0f;
		}
		
		
		/*移動チェック*/
		if( m_vDirection.Length() > 0.0f )
		{
			if( vTargetPos.Length() > 0.5f )
			{	
				m_Rot.x = toF( Math::ATan2( -m_vDirection.z, -m_vDirection.x ) );
			}
			
			/*正規化*/
			m_vDirection /= fLength;
			
			/*移動(-1の場合は通れる)*/
			if( MoveCheck( pField ) == -1 )
			{
				m_vPos += m_vDirection * m_fSpeed;
				//CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_PLAYERMOVE );
				return true;
			}
			
			else
			{
				m_fSpeed = 0.0f;
				
			}
			
		
		}
	}
		
	return false;
	
}

//==============================================================================
//移動処理(ツール用)
//==============================================================================
//[input]
//	pCam:カメラデバイス
//	pMouse:マウスデバイス
//	pField:フィールド
//	pSceneMgr:シーン管理デバイス
//==============================================================================
void CPlayer::Move( CCamera *pCam, Peripheral::IMouse *pMouse, CField *pField, Scene::ISceneManager *pSceneMgr )
{
	
	Collision::CLine3D vRay( 
			pSceneMgr->TransformFromScreen( Math::Vector3D(toF(pMouse->GetPosX()), toF(pMouse->GetPosY()), 0.0f) ),
			pSceneMgr->TransformFromScreen( Math::Vector3D(toF(pMouse->GetPosX()), toF(pMouse->GetPosY()), 1.0f) ) );
			
		
	Renderer::SCollisionResult Ret;
	
	if( pField->GetMapActor( SCREEN_MAIN )->HitCheckByRay( vRay, Ret ) )
	{
		m_vTarget = Ret.vHitPosition;
	}
				
	
	m_vDirection.x = m_vTarget.x - m_vPos.x;
	m_vDirection.y = 0.0f;
	m_vDirection.z = m_vTarget.z - m_vPos.z;
	
	m_fSpeed = 0.3f ;
	
	/*移動チェック*/
	if( m_vDirection.LengthSq() > 0.0f )
	{
		m_Rot.x = toF( Math::ATan2( m_vDirection.z, m_vDirection.x ) );
		
		float fLength = m_vDirection.Length();
		
		/*正規化*/
		m_vDirection /= fLength;
		
		if( pMouse->GetClickL() )
		{	
			m_vPos += m_vDirection * m_fSpeed;
		}
	}
		
	
	
}

//==============================================================================
//移動位置の設定
//==============================================================================
//[input]
//	pMouse:マウス用デバイス
//	pEnemy:敵クラス
//	pSceneMgr:シーン管理デバイス
//==============================================================================
void CPlayer::SetTargetPos( Selene::Peripheral::IMouse *pMouse, CEnemy *pEnemy, Scene::ISceneManager *pSceneMgr )
{
	Collision::CLine3D vRay( 
			pSceneMgr->TransformFromScreen( Math::Vector3D(toF(pMouse->GetPosX()), toF(pMouse->GetPosY()), 0.0f) ),
			pSceneMgr->TransformFromScreen( Math::Vector3D(toF(pMouse->GetPosX()), toF(pMouse->GetPosY()), 1.0f) ) );
	
	
	/*左クリックで乗り移り*/
	if( pMouse->GetStateL() == MOUSE_PUSH && pEnemy->GetModelActor( SCREEN_MAIN )->Collision_Check( vRay ))
	{
				
		/*捕獲フラグを設定*/
		pEnemy->SetCapdFlag( true );
		
		/*捕獲位置をバックアップ*/
		pEnemy->SetCatchBeforePos( pEnemy->GetPosition() );
		
		m_vCapedPos = m_vPos;
		
		/*状態を捕獲状態にする*/
		SetState( STATE_CAPSTART );
				
		/*捕獲した敵を代入*/
		m_pCapedEnemy = pEnemy;
		
	}	
}

//==============================================================================
//捕獲していた敵の解放
//==============================================================================
void CPlayer::ReleaseEnemy()
{
	SetState( CPlayer::STATE_RELSTART );
		
}

//==============================================================================
//捕獲判定ボックスの生成
//==============================================================================
void CPlayer::CreateCapBox()
{
	Math::Matrix matTemp;
	Math::Matrix matWorld;
	
	/*初期化*/
	matTemp.Identity();
	matWorld.Identity();
	
	/*回転*/
	matTemp.RotationY( toI( m_Rot.x - DEG_TO_ANGLE( 180 ) ) );
	
	matWorld *= matTemp;
	
	/*移動*/
	matTemp.Translation( m_vPos.x, m_vPos.y, m_vPos.z );
	
	matWorld *= matTemp;
	
	/*ボックスの生成*/
	m_CapChkBox.CreateBox( Math::Vector3D( -2, 0, 0 ), Math::Vector3D( 2, 5, 30 ), matWorld );
	

}

//==============================================================================
//捕獲判定ボックスの生成
//==============================================================================
//[input]
//	pCam:カメラクラス
//==============================================================================
void CPlayer::CreateShootBox( CCamera *pCam, CSceneManager *pSceneMgr )
{
	Math::Matrix matTemp;
	Math::Matrix matWorld;
	
	/*初期化*/
	matTemp.Identity();
	matWorld.Identity();
	
	//matWorld = pCam->GetCamera()->WorldToView();
	
	//GetModelActor( 0 )->Collision_Check(
	
	//matWorld = pCam->GetCamera()->WorldToView();
	
	///*X軸回転*/
	matTemp.RotationX( toI( pCam->GetRotate().x ) );
	//
	matWorld *= matTemp;
	//
	///*Y軸回転*/
	matTemp.RotationY( toI( m_Rot.x - DEG_TO_ANGLE( 180 ) ) );
	
	matWorld *= matTemp;
	
	/*移動*/
	matTemp.Translation( m_vPos.x, m_vPos.y, m_vPos.z );
	
	matWorld *= matTemp;
	
	//Math::Vector3D vPt1 = pSceneMgr->GetSceneMgr()->TransformFromScreen( Math::Vector3D( 0, 0, 0 ) );
	//Math::Vector3D vPt2 = pSceneMgr->GetSceneMgr()->TransformFromScreen( Math::Vector3D( SCREEN_WIDTH, SCREEN_HEIGHT, 2.0f ) );
	
	/*ボックスの生成*/
	//m_ShootChkBox.
//	m_ShootChkBox.CreateBox( vPt1, vPt2, matWorld );
}


//==============================================================================
//写真撮影判定用レイの生成
//==============================================================================
//[input]
//	pMouse:マウスデバイス
//	pSceneMgr:シーン管理デバイス
//==============================================================================
void CPlayer::CreateShootRay( Scene::ISceneManager *pSceneMgr )
{
	Math::Vector3D vPt0( toF( SCREEN_WIDTH / 2 ), toF( SCREEN_HEIGHT / 2 ), 0.0f );
	Math::Vector3D vPt1( vPt0.x, vPt0.y, 1.0f );
	
	m_ShootChkRay.vStart = pSceneMgr->TransformFromScreen( vPt0 );
	m_ShootChkRay.vEnd = pSceneMgr->TransformFromScreen( vPt1 );
}


//==============================================================================
//地面チェック
//==============================================================================
//[input]
//	pField:チェックするマップ
//[return]
//	地面に衝突物があったか
//==============================================================================
bool CPlayer::GroundCheck( CField *pField )
{
	Renderer::SCollisionResultExtend RetEx;
	Collision::CLine3D vRay;
	
	const float GRAVITY = 0.01f;
	
	//------------------------------------------------
	// 重力加速度
	//------------------------------------------------
	m_fGravity += GRAVITY;
	
	if ( m_fGravity > 1.0f )
	{
		// 一定値以上にしない（ゲーム的演出）
		m_fGravity = 1.0f;
		
	}
	

	//------------------------------------------------
	// キャラの自由落下
	//------------------------------------------------
	#if defined(DEBUG_MAP_EDIT)
	
	#else
		m_vPos.y -= m_fGravity;
	#endif
	
	//------------------------------------------------
	// 落下に関してのマップとコリジョンを取る
	//  キャラの腰付近から足元へレイを飛ばして判定する。
	//------------------------------------------------
	vRay.vStart = m_vPos + Math::Vector3D(0.0f,1.2f,0.0f);
	vRay.vEnd   = m_vPos;
	
	if ( pField->GetMapActor(m_ActorIndex)->HitCheckByRay( vRay, RetEx ) )
	{
		if( m_IsJumpFlag )
		{
			m_IsJumpFlag = false;

			CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_GETDOWN );
		}
		
		if( RetEx.Attribute == 0 || RetEx.Attribute == 2 )
		{
			// 衝突位置に移動
			m_vPos = RetEx.vHitPosition;
			// 重力加速初期化
			m_fGravity = 0.0f;
		}
		
		else if( RetEx.Attribute == 6 )
		{
			if( m_vPos.y < -10.0f )
			{
				m_vPos = Math::Vector3D( -104.8f, 0.0f, -415.0f );
				
				// 重力加速初期化
				m_fGravity = 0.0f;

			}
		}

		return true;
	}
	
	else
	{
		if( m_vPos.y >= RetEx.vHitPosition.y + 0.5 )
		{
			m_IsJumpFlag = true;
		}
		
	}
	
	return false;

}

//==============================================================================
//地面チェック
//==============================================================================
//[input]
//	
//[return]
//	地面に衝突物があったか
//==============================================================================
bool CPlayer::GroundCheck( CCharacter *pChara )
{
	Renderer::SCollisionResultExtend RetEx;
	Collision::CLine3D vRay;
	
	const float GRAVITY = 0.01f;
	
	//------------------------------------------------
	// 重力加速度
	//------------------------------------------------
	m_fGravity += GRAVITY;
	
	if ( m_fGravity > 1.0f )
	{
		// 一定値以上にしない（ゲーム的演出）
		m_fGravity = 1.0f;
		
	}
	
	//------------------------------------------------
	// キャラの自由落下
	//------------------------------------------------
	#if defined(DEBUG_MAP_EDIT)
	
	#else
		m_vPos.y -= m_fGravity;
	#endif
	
	//------------------------------------------------
	// 落下に関してのマップとコリジョンを取る
	//  キャラの腰付近から足元へレイを飛ばして判定する。
	//------------------------------------------------
	vRay.vStart = m_vPos + Math::Vector3D(0.0f,1.2f,0.0f);
	vRay.vEnd   = m_vPos;
	
	if ( pChara->GetModelActor(m_ActorIndex)->HitCheckByRay( vRay, RetEx ) )
	{
		if( m_IsJumpFlag )
		{
			m_IsJumpFlag = false;

			if( !GetCaptureFlag() )
			{	
				CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_GETDOWN );
			}
		}
		
		// 衝突位置に移動
		m_vPos = RetEx.vHitPosition;
		// 重力加速初期化
		m_fGravity = 0.0f;

		return true;
	}
	
	else
	{
		if( m_vPos.y >= RetEx.vHitPosition.y + 0.5 )
		{
			m_IsJumpFlag = true;
		}
		
	}
	
	return false;

}


//==============================================================================
//移動補正
//==============================================================================
void CPlayer::MoveAdjust()
{
	if( m_vPos.x <= -359 )
	{
		m_vPos.x = -359;
	}
	
	if( m_vPos.x >= 359 )
	{
		m_vPos.x = 359;
	}
	
	if( m_vPos.z >= 0 )
	{
		m_vPos.z = 0;
	}
	
	if( m_vPos.z <= -528 )
	{
		if( m_IsDead )
		{
			
		}
		
		else
		{	
			m_vPos.z = -528;
		}	
			
	}
}



	
