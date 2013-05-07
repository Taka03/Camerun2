//*============================================================================
//character.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "character.h"
#include "SceneManager.h"

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	pName:データ名
//	vPos:設定する座標
//=============================================================================
CCharacter::CCharacter( const char *pName, Math::Vector3D vPos ) 
:m_pModel(NULL),
 m_pLine3D(NULL),
 m_IsMoving( false ),
 CDraw3DObject( pName, vPos )
{
	//std::fill( m_pActorModel, m_pActorModel, 0 ); 
	//std::fill( m_pActorLine,  m_pActorLine + SCREEN_MAX, NULL ); 
	
	
	//memset( m_pActorModel, NULL, SCREEN_MAX );
	//memset( m_pActorLine, NULL, sizeof( Scene::IPrimitiveActor ) * SCREEN_MAX );
	
	for( int numActor = 0;numActor < SCREEN_MAX;++numActor )
	{
		m_pActorModel[numActor] = NULL;
		m_pActorLine[numActor] = NULL;
	}
	
	m_vDirection.Set( 0.0f, 0.0f, 0.0f );
	
	m_fSpeed = 0.0f;
	
	m_fStSpeed = 0.0001f;
	
	m_fWeight = 0.0f;
	
	m_fGravity = 0.0f;
	
	m_IsExistAnim = false;
	
	m_IsFly = false;
	
	//memset( m_fAnimTime, 1.0f, sizeof( float ) * ANIM_MAX );
	memset( m_AnimID, 0, sizeof( int ) * ANIM_MAX );
	
	for( int Anim = 0;Anim < ANIM_MAX;++Anim )
	{
		m_fAnimTime[Anim] = 1.0f;
	//	m_AnimID[Anim] = 0;
	} 
	//
	m_eAnimState = ANIM_STANDBY;
	
}

//=============================================================================
//デストラクタ
//=============================================================================
CCharacter::~CCharacter()
{
	printf( "%s:デストラクタ",  m_strFileName.c_str() );
	
	for( int numActor = 0;numActor < SCREEN_MAX;++numActor )
	{
		SAFE_RELEASE( m_pActorLine[numActor] );
		
		SAFE_RELEASE( m_pActorModel[numActor] ); 
	}
	
	SAFE_RELEASE( m_pLine3D );
	
	SAFE_RELEASE( m_pModel );
	
}

//=============================================================================
//初期化
//=============================================================================
void CCharacter::Init()
{
	CDrawObject::Init();
}

//=============================================================================
//処理
//=============================================================================
void CCharacter::Exec()
{
	SetActorSetting();
}

//=============================================================================
//アクター設定のセット
//=============================================================================
void CCharacter::SetActorSetting()
{
	/*姿勢のリセット*/
	m_pActorModel[m_ActorIndex]->TransformReset();
	
	/*X軸周りに回転*/
	m_pActorModel[m_ActorIndex]->RotationX( m_Rot.y );
	
	/*Y軸周りに回転*/
	m_pActorModel[m_ActorIndex]->RotationY( m_Rot.x );
	
	/*拡大縮小*/
	m_pActorModel[m_ActorIndex]->Scaling( m_vScale.x, m_vScale.y, m_vScale.z );
	
	/*移動*/
	m_pActorModel[m_ActorIndex]->Translation( m_vPos );
	
	if( m_IsExistAnim )
	{
		// キャラに対してアニメーションを更新
		m_pActorModel[m_ActorIndex]->UpdateAnimation( m_AnimID[ANIM_NOW], m_fAnimTime[ANIM_NOW] );
	}
	
	/*正面ベクトルの取得*/
	m_pActorModel[m_ActorIndex]->GetFront( m_vFront );
	
	/*右面ベクトルの取得*/
	m_pActorModel[m_ActorIndex]->GetRight( m_vRight );
	
	/*姿勢の更新*/
	m_pActorModel[m_ActorIndex]->TransformUpdate();
	
}

//=============================================================================
//レンダリング
//=============================================================================
void CCharacter::Rendering( )
{
	if( m_IsVisible )
	{
		m_pActorModel[m_ActorIndex]->RenderingRequest();
		
		#if defined ( DEBUG ) | ( _DEBUG )
		
			m_pActorLine[m_ActorIndex]->RenderingRequest();
		
		#endif 
	}
}

//============================================================================
//ファイル読み込み
//============================================================================
//[input]
//	pRender:レンダラー用デバイス
//	pFileMgr:ファイル管理用デバイス
//===========================================================================
void CCharacter::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	printf("LOAD MODEL[%s]", m_strFileName.c_str() );
	
	pFileMgr->SetCurrentPath("Model");
	
	m_pModel = pRender->CreateModelFromFile( m_strFileName.c_str() );
	
	printf( "                 : -> %s\n", m_pModel->IsInvalid() ? "Failed" : "Succeeded" );
	
	#if defined ( DEBUG ) | ( _DEBUG )
	
		/*3Dラインの生成*/
		m_pLine3D = pRender->CreateLine3D( 10000, true );
	
	#endif
	
	//アクターの生成
	for( int i = 0;i < SCREEN_MAX;++i )
	{
		CreateActor( i, CCommonObject::GetSceneMgr( i )->GetSceneMgr() );
	}
	
}

//==============================================================================
//アクターの生成
//==============================================================================
//[input]
//	index:生成するアクターインデックス
//	pSceneMgr:シーン管理デバイス
//==============================================================================
void CCharacter::CreateActor( int index, Scene::ISceneManager *pSceneMgr )
{
	if( m_pModel != NULL )
	{
		m_pActorModel[index] = pSceneMgr->CreateActor( m_pModel );
		
		//コリジョンの生成
		CreateCollision( index );
	}
	
	#if defined ( DEBUG ) | ( _DEBUG )
	
		m_pActorLine[index] = pSceneMgr->CreateActor( m_pLine3D );
	
	#endif
}

//==============================================================================
//箱の描画
//==============================================================================
//[input]
//	index:生成するアクターインデックス
//	pSceneMgr:シーン管理デバイス
//==============================================================================
void CCharacter::DrawBox( Collision::CBox Box[], int num )
{
	#if defined ( _DEBUG ) | ( _DEBUG )
		
		/*ライン描画開始*/
		m_pLine3D->Begin();
		
		/*デバッグボックスの追加*/
		for( int i = 0;i < num;++i )
		{
			m_pLine3D->PushBox( Box[i], CColor( 255, 255, 255 ) );
		}
		
		/*当たり判定の描画*/
		m_pActorModel[SCREEN_MAIN]->Collision_Rendering( m_pLine3D );
	
		/*ライン描画終了*/
		m_pLine3D->End();
		
	#endif
		
}

//=============================================================================
//コリジョンデータの作成
//=============================================================================
//[input]
//	index:設定するインデックス
//=============================================================================
void CCharacter::CreateCollision( int index )
{
	GetModelActor( index )->Collision_Create();
}

//=============================================================================
//参照カウンタの増加
//=============================================================================
void CCharacter::AddRef()
{
	m_pModel->AddRef();
	
	for( int actornum = 0;actornum < SCREEN_MAX;++actornum )
	{
		m_pActorModel[actornum]->AddRef();
	}	
}

//=============================================================================
//アクターインデックスのセット
//=============================================================================
//[input]
//	index:設定するインデックス
//=============================================================================
void CCharacter::SetActorIndex( int index )
{
	m_ActorIndex = index;
}

//==============================================================================
//距離チェック
//==============================================================================
//[input]
//	pChara:チェックするキャラクター
//[return]
//	距離
//==============================================================================
float CCharacter::CheckDistance( CCharacter *pChara )
{
	Math::Vector3D vDirection = pChara->GetPosition() - m_vPos;
	
	return vDirection.Length();
	
}

//==============================================================================
//移動処理
//==============================================================================
//[input]
//	vTargetPos:対象位置
//	pCam:カメラデバイス
//	pField:チェックするマップ
//==============================================================================
bool CCharacter::Move( Selene::Math::Vector3D vTargetPos, CCamera *pCam, CField *pField )
{
	m_vDirection.x = vTargetPos.x * pCam->GetRight().x + vTargetPos.y * (-pCam->GetFront().x);
	m_vDirection.y = 0.0f;
	m_vDirection.z = vTargetPos.x * pCam->GetRight().z + vTargetPos.y * (-pCam->GetFront().z);
	
	m_Rot.x = Math::ATan2( -m_vDirection.z, -m_vDirection.x );
	
	float fLength = m_vDirection.Length();
	
	m_fSpeed = fLength * 0.001f ;
	
	if( m_fSpeed > 2.0f )
	{
		m_fSpeed = 2.0f;
	}
	
	
	/*移動チェック*/
	if( m_vDirection.LengthSq() > 0.0f )
	{
		
		/*正規化*/
		m_vDirection /= fLength;
		
		/*移動(-1の場合は通れる)*/
		if( MoveCheck( pField ) == -1 )
		{
			m_vPos += m_vDirection * m_fSpeed;
			m_IsMoving = true;
			return true;
		}
		
		else
		{
			m_fSpeed = 0.0f;
			m_IsMoving = false;
			
		}
		
	}
	
	else
	{
		m_IsMoving = false;
	}
	
	return false;
	
}


//==============================================================================
//移動チェック
//==============================================================================
//[input]
//	pChara:チェックするキャラ
//[return]
//	移動先に障害物があるか
//==============================================================================
bool CCharacter::MoveCheck( CCharacter *pChara )
{
	Renderer::SCollisionResultExtend RetEx;
	Renderer::SCollisionResult Ret;
	Collision::CLine3D vRay[6];
	
	Collision::CBox Box;
	
	Math::Vector3D vCharaFront(0, 0, 0);
	Math::Vector3D vCharaRight;
	
	this->GetModelActor(SCREEN_MAIN)->GetFront( vCharaFront );
	m_pActorModel[SCREEN_MAIN]->GetRight( vCharaRight );
	
	
	//if ( m_vDirection.LengthSq() > 0.0f )
	//{
		// 移動量
		m_vDirection *= m_fSpeed;
		
		//------------------------------------------------
		// 移動に関してのマップとコリジョンを取る
		//  キャラの腰付近から足元へレイを飛ばして判定する。
		//------------------------------------------------
		// コリジョン抜け対策でループ
		Math::Vector3D vMove = m_vDirection;
		Math::Vector3D vPos = m_vPos;
		Sint32 Limit = 10;
		
		vRay[0].vStart = Math::Vector3D( 0.0f,0.8f, 0.0f ) + m_vPos + vCharaFront * 0.2f;
		vRay[0].vEnd   = vRay[0].vStart + vMove;
		
		vRay[1].vStart = vRay[0].vStart ;
		vRay[1].vEnd   = vRay[0].vStart + vMove + vCharaRight * 0.2f;
		
		vRay[2].vStart = vRay[0].vStart ;
		vRay[2].vEnd   = vRay[2].vStart + vMove - vCharaRight * 0.2f;
		
		vRay[3].vStart = Math::Vector3D( 0.0f,0.8f, 0.0f ) + m_vPos + vCharaFront * 0.1f;
		vRay[3].vEnd   = vRay[3].vStart + vMove;
		
		vRay[4].vStart = vRay[3].vStart;
		vRay[4].vEnd   = vRay[4].vStart + vMove + vCharaRight * 0.1f;
		
		vRay[5].vStart = vRay[3].vStart;
		vRay[5].vEnd   = vRay[5].vStart + vMove - vCharaRight * 0.1f;
		
		
		
		//for ( ; ; )
		//{
				
			if( pChara->GetVisibleFlag() )
			{
			
				if ( pChara->GetModelActor(m_ActorIndex)->HitCheckByRay( vRay[0], RetEx ) || 
					 pChara->GetModelActor(m_ActorIndex)->HitCheckByRay( vRay[1], RetEx ) || 
					 pChara->GetModelActor(m_ActorIndex)->HitCheckByRay( vRay[2], RetEx ) ||
					 pChara->GetModelActor(m_ActorIndex)->HitCheckByRay( vRay[3], RetEx ) ||
					 pChara->GetModelActor(m_ActorIndex)->HitCheckByRay( vRay[4], RetEx ) ||
					 pChara->GetModelActor(m_ActorIndex)->HitCheckByRay( vRay[5], RetEx )  )
				{
					// 衝突位置に移動
					Math::Vector3D RetPos = RetEx.vSlidePosition + (RetEx.vNormal * 0.03f);
					vMove = RetPos - vPos;
					vMove.y = 0.0f;
					//vMove.Set( 0.0, 0.0, 0.0 );
					m_fSpeed = 0.1f;
					
					return true;				
				}
				
				else
				{
					// 移動
					m_vPos += vMove;
						//IsHit = false;
					
				}
			
				
				//if ( this->GetModelActor(SCREEN_MAIN)->Collision_Check( pChara->GetModelActor(SCREEN_MAIN) )  )
				//{
				//	//m_fSpeed = 0.0f;
				//	//
				//	//m_vDirection.Set( 0, 0, 0 );
				//	//
				//	m_vPos = (pChara->GetPosition() - m_vPos);
				//	
				//	
				//	vMove.Set( 0.0, 0.0, 0.0 );
				//	
				//	return true;				
				//}
				//
				//else
				//{
				//	m_vPos += vMove;
				//		
				//	break;
				//	
				//}
			}
			
			//// 限界数突破
			//if ( --Limit ==  0 )
			//{
			//	// どうやっても埋まるので移動せずに脱出
			//	break;
			//}
		
	//}
	
	
	return false;
}


//==============================================================================
//移動チェック
//==============================================================================
//[input]
//	pField:チェックするマップ
//[return]
//	移動先の壁属性
//==============================================================================
Bool CCharacter::MoveCheck( CField *pField )
{
	Renderer::SCollisionResult RetEx;
	Collision::CLine3D vRay[6];
	
	//------------------------------------------------
	// 移動に関してのマップとコリジョンを取る
	//  キャラの腰付近から足元へレイを飛ばして判定する。
	//------------------------------------------------

	Math::Vector3D vMove = m_vDirection;
	Math::Vector3D vPos = m_vPos;
	
	vRay[0].vStart = Math::Vector3D( 0.0f,0.8f, 0.0f ) + m_vPos + m_vFront * 0.2f;
	vRay[0].vEnd   = vRay[0].vStart + vMove;
	
	vRay[1].vStart = vRay[0].vStart ;
	vRay[1].vEnd   = vRay[0].vStart + vMove + m_vRight * 0.2f;
	
	vRay[2].vStart = vRay[0].vStart ;
	vRay[2].vEnd   = vRay[2].vStart + vMove - m_vRight * 0.2f;
	
	vRay[3].vStart = Math::Vector3D( 0.0f,0.8f, 0.0f ) + m_vPos + m_vFront * 0.1f;
	vRay[3].vEnd   = vRay[3].vStart + vMove;
	
	vRay[4].vStart = vRay[3].vStart;
	vRay[4].vEnd   = vRay[4].vStart + vMove + m_vRight * 0.1f;
	
	vRay[5].vStart = vRay[3].vStart;
	vRay[5].vEnd   = vRay[5].vStart + vMove - m_vRight * 0.1f;
	
	/*レイを飛ばして、当たっているか判定*/
	if ( pField->GetMapActor(SCREEN_MAIN)->HitCheckByRay( vRay[0], RetEx ) || 
		 pField->GetMapActor(SCREEN_MAIN)->HitCheckByRay( vRay[1], RetEx ) || 
		 pField->GetMapActor(SCREEN_MAIN)->HitCheckByRay( vRay[2], RetEx ) ||
		 pField->GetMapActor(SCREEN_MAIN)->HitCheckByRay( vRay[3], RetEx ) ||
		 pField->GetMapActor(SCREEN_MAIN)->HitCheckByRay( vRay[4], RetEx ) ||
		 pField->GetMapActor(SCREEN_MAIN)->HitCheckByRay( vRay[5], RetEx )  )
	{
		return RetEx.Attribute;				
	}
	
	return -1;
}



//==============================================================================
//地面チェック
//==============================================================================
//[input]
//	pChara:判定するキャラクター
//[return]
//	地面に衝突物があったか
//==============================================================================
bool CCharacter::GroundCheck( CCharacter *pChara )
{
	Renderer::SCollisionResult Ret;
	Collision::CLine3D vRay;
	
	//------------------------------------------------
	// 重力加速度
	//------------------------------------------------
	//m_fGravity += GRAVITY;
	//
	//if ( m_fGravity > 1.0f )
	//{
	//	// 一定値以上にしない（ゲーム的演出）
	//	m_fGravity = 1.0f;
	//}

	//------------------------------------------------
	// キャラの自由落下
	//------------------------------------------------
	//m_vPos.y -= m_fGravity;

	//------------------------------------------------
	// 落下に関してのマップとコリジョンを取る
	//  キャラの腰付近から足元へレイを飛ばして判定する。
	//------------------------------------------------
	vRay.vStart = m_vPos + Math::Vector3D(0.0f,5.0f,0.0f);
	vRay.vEnd   = m_vPos;
	
	if ( pChara->GetModelActor(SCREEN_MAIN)->HitCheckByRay( vRay, Ret ) )
	{
		if( Ret.Attribute == 2 )
		{
			// 衝突位置に移動
			m_vPos = Ret.vHitPosition;
			
			m_vPos.z -= pChara->GetSpeed() * 2;
		
		
		//m_vDirection += pChara->GetSpeed();
		// 重力加速初期化
		
			return true;
		}
	}
	
	return false;

}

//==============================================================================
//地面チェック
//==============================================================================
//[input]
//	pActor:チェックするマップアクター
//[return]
//	地面に衝突物があったか
//==============================================================================
bool CCharacter::GroundCheck( CField *pField )
{
	Renderer::SCollisionResultExtend RetEx;
	Collision::CLine3D vRay;
	
	const float GRAVITY = 0.01f;
	
	//------------------------------------------------
	// 重力加速度
	//------------------------------------------------
	if( !m_IsFly )
	{
		m_fGravity += GRAVITY;
		
		if ( m_fGravity > 0.7f )
		{
			// 一定値以上にしない（ゲーム的演出）
			m_fGravity = 0.7f;
			
		}
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
	vRay.vStart = m_vPos + Math::Vector3D(0.0f,1.5f,0.0f);
	vRay.vEnd   = m_vPos;
	
	if ( pField->GetMapActor(m_ActorIndex)->HitCheckByRay( vRay, RetEx ) )
	{
		if( RetEx.Attribute == 0 || RetEx.Attribute == 2 )
		{
			 //衝突位置に移動
			m_vPos = RetEx.vHitPosition;
			 //重力加速初期化
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
	
	return false;

}

//==============================================================================
//当たり判定
//==============================================================================
//[input]
//	pChara:判定するキャラクター
//[return]
//	キャラに衝突したか
//==============================================================================
bool CCharacter::HitCheck( CCharacter *pChara )
{
	if( this->GetModelActor(SCREEN_MAIN)->Collision_Check( pChara->GetModelActor( SCREEN_MAIN ) )
		&& GetVisibleFlag() )
	{
		return true;
	}
	
	return false;

}

//==============================================================================
//当たり判定
//==============================================================================
//[input/output]
//	ppChara:判定するキャラクター
//[return]
//	キャラに衝突したか
//==============================================================================
bool CCharacter::HitCheck( CDraw3DObject **ppChara )
{
	CCharacter *obj = dynamic_cast<CCharacter *>( *ppChara );
	
	if( this->GetModelActor(SCREEN_MAIN)->Collision_Check( obj->GetModelActor( SCREEN_MAIN ) ) )
	{
		return true;
	}
	
	return false;

}

//==============================================================================
//当たり判定
//==============================================================================
//[input]
//	vRay:判定用のレイ
//[return]
//	キャラに衝突したか
//==============================================================================
bool CCharacter::HitCheck( Selene::Collision::CLine3D &vRay )
{
	if( this->GetModelActor(SCREEN_MAIN)->HitCheckByRay( vRay ) )
	{
		return true;
	}	
	
	return false;
}

//==============================================================================
//当たり判定
//==============================================================================
//[input]
//	vRay:判定用のレイ
//	Out:衝突結果格納用
//[return]
//	キャラに衝突したか
//==============================================================================
bool CCharacter::HitCheck( Selene::Collision::CLine3D &vRay, Renderer::SCollisionResult &Out )
{
	if( this->GetModelActor(SCREEN_MAIN)->HitCheckByRay( vRay, Out ) )
	{
		return true;
	}	
	
	return false;
}

//==============================================================================
//アルファ値の設定
//==============================================================================
//[input]
//	alpha:設定するアルファ値
//==============================================================================
void CCharacter::SetAlphaColor( Sint32 alpha )
{
	Sint32 meshcount = m_pActorModel[m_ActorIndex]->GetMeshCount();
	
	for( int i = 0;i < meshcount;++i )
	{
		Sint32 mtrlcount = m_pActorModel[m_ActorIndex]->GetMeshMaterialCount( i );
		
		for( int j = 0;j < mtrlcount;++j )
		{
			m_pActorModel[m_ActorIndex]->MeshMaterial_SetDrawType( i, j, DRAW_TYPE_ADD );
			
			m_pActorModel[m_ActorIndex]->MeshMaterial_SetEmissiveColor( i, j, Math::Vector4D( 255, 255, 255, alpha ) );
		}
	}
}



