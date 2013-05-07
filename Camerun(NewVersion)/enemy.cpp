//*=============================================================================
//enemy.cpp
//*=============================================================================


//==============================================================================
//include
//==============================================================================
#include "enemy.h"
#include "player.h"
#include "FileLoader.h"

//==============================================================================
//namespace
//==============================================================================
using namespace std;

namespace
{
	Math::Vector3D vOldPos;//位置の保存
	
	int RootCount = 0;//ルート数のカウント
	
	int RootSpeed = 1;//ルートのスピード
	
	Math::Vector3D vHitPos( 0, 0, 0 );//写真判定位置
	
}

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	pName:データ名
//	vPos:設定する座標
//	pResFile:リソースファイル
//=============================================================================
CEnemy::CEnemy( const char *pName, Math::Vector3D vPos, File::IResourceFile *pResFile ) 
:CCharacter( pName, vPos ),
 m_pCatchSpr3D(NULL),
 m_pAnimX(NULL),
 m_pAnimZ(NULL),
 m_eState(STATE_NONE)
 
{
	CFileLoader FileLoader;
	
	m_fKeyTime = 0.0f;
	m_IsExistAnim = true;
	m_IsHitWall = false;
	m_IsCatchable = true;
	m_IsEndPhoto = false;
	
	m_vNextPoint.Set( 0, 0, 0 );
	
	m_RootCount = 0;
	m_RootSpeed = 1;
	
	
	m_pCatchSpr3D = new CSprite3D( "catch.png", m_vPos );
	m_pPntFontSpr3D = new CFontSprite3D("NumFont.sff", m_vPos );
	m_pLockOnSpr3D = new CSprite3D( "pointa.bmp", m_vPos );
	m_pMinSpr = new CSprite( "mini_enemy.png", Math::Vector2D( m_vPos.x, m_vPos.y ) );

	m_IsCaptured = false;
	m_vCatchPos.Set( 0.0f, 0.0f, 0.0f );
	m_vCatchBefPos.Set( 0, 0, 0 );
	
	string FileName = pResFile->GetNamePointer();
	
	/*設定ファイルの読み込み*/
	FileLoader.Load( FileName );
	
	SAFE_RELEASE( pResFile );
	
	vector<string> list = FileLoader.GetStrList();
	vector<string>::iterator it = list.begin();
	
	m_fStSpeed = atof( list.at(0).c_str() );
	m_PhotoPoint = atoi( list.at(1).c_str() );
	
	/*リソースの読み込み*/
	for( it = list.begin() + 2;it != list.end();++it )
	{	
		vector<string> strSource = FileLoader.SplitString( *it, "," );
		
		Math::Vector3D vPos;
		
		vPos.x = atof( strSource[0].c_str() );
		vPos.y = m_vPos.y;
		vPos.z = atof( strSource[1].c_str() );
		
		m_vecKey.push_back( vPos );
	}
	
	
}

//=============================================================================
//デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{
	SAFE_DELETE( m_pCatchSpr3D );
	SAFE_DELETE( m_pLockOnSpr3D );
	SAFE_DELETE( m_pPntFontSpr3D );
	SAFE_DELETE( m_pMinSpr );

}

//============================================================================
//ファイル読み込み
//============================================================================
//[input]
//	pRender:レンダラー用デバイス
//	pFileMgr:ファイル管理用デバイス
//===========================================================================
void CEnemy::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr ) 
{
	CCharacter::Load( pRender, pFileMgr );
	
	m_pCatchSpr3D->Load( pRender, pFileMgr );
	
	m_pPntFontSpr3D->Load( pRender, pFileMgr );
	
	m_pLockOnSpr3D->Load( pRender, pFileMgr );
	
	m_pMinSpr->Load( pRender, pFileMgr );

}


//=============================================================================
//初期化
//=============================================================================
void CEnemy::Init()
{
	CCharacter::Init();
	
	m_IsCaptured = false;
	m_IsEndPhoto = false;
	m_IsLockOn = false;
	
	m_fKeyTime = 0.0f;
	
	m_RootCount = 0;
	
	m_ReleaseCnt = 0;
	
}


//=============================================================================
//レンダリング
//=============================================================================
void CEnemy::Rendering()
{
	/*状態毎の処理*/
	StateExec();
	
	/*レンダリング*/
	CCharacter::Rendering();
	
	if( m_IsCaptured )
	{
		m_pCatchSpr3D->SetVisibleFlag( false );
	}
}

//=============================================================================
//ミニキャラの表示
//=============================================================================
void CEnemy::ShowMiniChara()
{
	if( GetVisibleFlag() )
	{
		m_pMinSpr->Exec();
		
		m_pMinSpr->Rendering();
	}
}


//=============================================================================
//キャッチマークのレンダリング
//=============================================================================
void CEnemy::RenderingCatchMark()
{
	/*処理*/
	m_pCatchSpr3D->Exec();
	
	//m_pLockOnSpr3D->Exec();
	
	/*キャッチマークのレンダリング*/
	m_pCatchSpr3D->Rendering();

}

//=============================================================================
//得点のレンダリング
//=============================================================================
void CEnemy::RenderingPoint()
{
	if( !m_IsCaptured )
	{	
		m_pPntFontSpr3D->SetVisibleFlag( true );
	}
	
	char Temp[5];
	
	sprintf_s( Temp, 5, "%d", m_PhotoPoint );
	
	/*得点をセット*/
	m_pPntFontSpr3D->SetDrawString( Temp );
	
	/*処理*/
	m_pPntFontSpr3D->Exec();
	
	/*ポイントのレンダリング*/
	m_pPntFontSpr3D->Rendering();
	

}

//==============================================================================
//ロックオンマークのレンダリング
//==============================================================================
void CEnemy::RenderingLockOn()
{
	//if( m_IsLockOn )
	//{
	//	m_pLockOnSpr3D->SetVisibleFlag( true );
	//	
	//}
	//
	//else
	//{
	//	m_pLockOnSpr3D->SetVisibleFlag( false );
	//}
	//
	
	//m_pLockOnSpr3D->Rendering();
	

}

//==============================================================================
//ルートの移動箇所キーの設定
//==============================================================================
void CEnemy::SetRootKey()
{

	/*次に進む場所を設定*/
	m_vNextPoint = m_vecKey.at( 1 );
	
	m_vInitPoint = m_vPos;

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
bool CEnemy::Move( Selene::Math::Vector3D vTargetPos, CCamera *pCam, CField *pField, bool IsShowMark )
{
	if( IsShowMark )
	{
		m_vDirection.x = vTargetPos.x * pCam->GetRight().x + vTargetPos.y * (-pCam->GetFront().x);
		m_vDirection.y = 0.0f;
		m_vDirection.z = vTargetPos.x * pCam->GetRight().z + vTargetPos.y * (-pCam->GetFront().z);
	}
	
	m_Rot.x = toF( Math::ATan2( -m_vDirection.z, -m_vDirection.x ) );
	
	float fLength = m_vDirection.Length();
	
	m_fSpeed = fLength * m_fStSpeed ;
	
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
		if( !HitCheckWall( pField ) )
		{
			if( IsShowMark )
			{	
				m_vPos += m_vDirection * m_fSpeed;
				
			}

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


//=============================================================================
//状態毎の処理
//=============================================================================
void CEnemy::Exec()
{
	m_vCatchMrkPos.x = m_vPos.x;
	m_vCatchMrkPos.z = m_vPos.z;
	
	static int count = 0;
	
	const int COUNT_MAX = 60 * 5;
	
	++count;
	
	m_vCatchMrkPos.y = ::Interpolation::Sub( m_vPos.y + 2.0f, m_vPos.y + 2.5f, COUNT_MAX, count );
	
	if( count >= COUNT_MAX )
	{
		count = 0;
	}
	
	m_vLockMrkPos = m_vPos - m_vFront;
	
	/*ポイント表示位置を設定*/
	m_pPntFontSpr3D->SetPosition( m_vCatchMrkPos + Math::Vector3D( 0, 3.0, 0 ) );

	/*キャッチマークの表示位置を設定*/
	m_pCatchSpr3D->SetPosition( m_vCatchMrkPos );
	
	/*ロックオンマークの設定*/
	m_pLockOnSpr3D->SetPosition( m_vLockMrkPos );
	
	if( m_IsExistAnim )
	{
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
	}
	
	/*アクターの設定のセット*/
	SetActorSetting();
	
	if( m_IsCaptured )
	{
		m_IsStop = true;
	}
	
	else
	{
		m_IsStop = false;
	}
	
}

//=============================================================================
//状態毎の処理
//=============================================================================
void CEnemy::StateExec()
{
	switch( m_eState )
	{
		/*何もない状態のとき*/
		case STATE_NONE:
		{
			break;
		}
		
		/*解放時*/
		case STATE_RELEASE:
		{
			Math::Vector3D vMovePos = GetPosition();
			
			const int MAX_COUNT = 60*5;//最大カウント数
			
			m_ReleaseCnt ++;
			
			/*等速で移動*/
			m_vPos.x = Interpolation::Flat( vMovePos.x, m_vCatchBefPos.x, MAX_COUNT, m_ReleaseCnt );
			m_vPos.y = Interpolation::Flat( vMovePos.y, m_vCatchBefPos.y, MAX_COUNT, m_ReleaseCnt );
			m_vPos.z = Interpolation::Flat( vMovePos.z, m_vCatchBefPos.z, MAX_COUNT, m_ReleaseCnt );
			
			if( m_ReleaseCnt >= MAX_COUNT )
			{
				m_eState = STATE_NONE;
				m_ReleaseCnt = 0;
			}
			
			break;
		}
		
		//敵との判定処理
		case STATE_HITENEMY:
		{
			static int count = 0;
			
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

//=============================================================================
//ルートでの移動
//=============================================================================
void CEnemy::MoveRoot()
{
	m_fKeyTime += 1.0f;
	
	const float fTIME_MAX = 240;
	
	m_vDirection = m_vNextPoint - m_vInitPoint;
	
	m_Rot.x = toF( Math::ATan2( -m_vDirection.z, -m_vDirection.x ) );
	m_vPos.x = ::Interpolation::Flat( m_vInitPoint.x, m_vNextPoint.x, fTIME_MAX, m_fKeyTime );
	m_vPos.z = ::Interpolation::Flat( m_vInitPoint.z, m_vNextPoint.z, fTIME_MAX, m_fKeyTime );
	
	//if( m_RootCount >= m_vecKey.size() - 2 )
	//{
	//	m_RootSpeed *= -1;
	//}
	//
	//else if( m_RootCount < 0 )
	//{
	//	m_RootSpeed *= -1;
	//}
	//
	//
	if( m_fKeyTime > fTIME_MAX )
	{
		m_vInitPoint = m_vNextPoint;
		
		m_RootCount += m_RootSpeed;
		
		if( m_RootCount < m_vecKey.size() )
		{	
			m_vNextPoint = m_vecKey.at( m_RootCount );
		}
		
		else
		{
			m_RootCount = 0;
		}
		
		m_fKeyTime = 0;
	}
	
	
	
	
	
	////
	//m_vDirection = m_vNextPoint - m_vInitPoint;
	////
	////float fDis = m_vDirection.Length();
	////
	////float Time = fDis / m_fSpeed;
	////
	//const float fTIME = 60;
	//
	////m_Rot.x = toF( Math::ATan2( -m_vDirection.z, -m_vDirection.x ) );
	////
	//m_vPos.x = m_pAnimX->GetParameter( m_fKeyTime, ANIMATION_TYPE_LINEAR, 0.0f );
	//m_vPos.z = m_pAnimZ->GetParameter( m_fKeyTime, ANIMATION_TYPE_LINEAR, 0.0f );
	
	//m_vPos.x = Interpolation::Flat( m_vPos.x, m_vNextPoint.x, fTIME, m_fKeyTime );
	//
	//m_vPos.z = Interpolation::Flat( m_vPos.z, m_vNextPoint.z, fTIME, m_fKeyTime );
	
	//m_vPos += m_vDirection * 0.4f/* * m_fStSpeed*/;
	
	//if( RootCount > 2 )
	//{
	//	RootCount = 0;
	//}
	
	
	//if( m_fKeyTime >= fTIME )
	//{
	//	
	//	m_vInitPoint = m_vNextPoint;

	//	Math::Vector3D vPoint = m_vecKey.at( RootCount );
	//	
	//	RootCount++;
	//	
	//	m_vNextPoint = vPoint;
	//}
	//
}

//=============================================================================
//ランダムウォーク
//=============================================================================
void CEnemy::MoveRandom()
{
	static float count = 0.0f;
	m_vDirection = m_vNextPoint - m_vPos;
	
	/*次の移動ポイントの設定*/

	m_Rot.x = toF( Math::ATan2( -m_vDirection.z, -m_vDirection.x ) );
	
	float fDis = m_vDirection.Length();
	
	//float Time = fDis / 0.0001f;
	
	float Time = 60 * 8;
	
	count += 1.0f;
	
	m_vPos.x = ::Interpolation::Flat( m_vInitPoint.x, m_vNextPoint.x, Time, count );
	
	if( m_IsFly )
	{
		m_vPos.y = ::Interpolation::Flat( m_vInitPoint.y, m_vNextPoint.y, Time, count );
	}
	
	m_vPos.z = ::Interpolation::Flat( m_vInitPoint.z, m_vNextPoint.z, Time, count );
	
	if( count > Time )
	{
		m_vInitPoint = m_vNextPoint;
		
		SetNextPoint();
	
		count = 0;
	}
	
	//m_vPos += m_vDirection * 0.7f/* * m_fStSpeed*/;
	
}



//=============================================================================
//移動処理
//=============================================================================
void CEnemy::MoveExec()
{
	if( !m_IsCaptured )
	{
		//m_vDirection = m_vNextPoint - m_vPos;
		
		m_vDirection = -m_vFront;
		
		static int count = 0;
		
		count ++;
		
		const int TIME = 60 * 5;
		
		static Sint32 Hit = 1;
		
		
		//m_vPos.x = Interpolation::Flat( vOldPos.x, m_vNextPoint.x, TIME, count ) * 0.1;
		//m_vPos.z = Interpolation::Flat( vOldPos.z, m_vNextPoint.z, TIME, count ) * 0.1;
		
		if( m_IsHitWall )
		{
			m_Rot.x += DEG_TO_ANGLE( Hit );
		}
		
		else
		{
			m_vPos += m_vDirection * m_fSpeed;
			
			//Hit = Rand.GetInt( -1, 1 );
			
			
		}
		
		if( count > TIME )
		{
			
			Sint32 Rot = m_Rand.GetInt( -20, 20 );
			
			m_Rot.x += DEG_TO_ANGLE( Rot );
			
			count = 0;
		}
		
		
		
	}

}

//=============================================================================
//捕獲対象かチェック
//=============================================================================
//[input]
//	Box:判定するボックス
//=============================================================================
void CEnemy::CheckCatch( Collision::CBox Box )
{
	if( GetVisibleFlag() && GetCatchableFlag() )
	{
		if( GetModelActor( SCREEN_MAIN )->Collision_Check( Box ) )
		{
			m_pCatchSpr3D->SetVisibleFlag( true );
		}
		
		else
		{
			m_pCatchSpr3D->SetVisibleFlag( false );
		}
	}	
		
}

//=============================================================================
//敵の得点計算
//=============================================================================
//[input]
//	pPlayer:プレイヤー
//[return]
//	計算されたスコア
//=============================================================================
int CEnemy::CalcScore( CPlayer *pPlayer )
{
	int Score = 0;
	
	float fLength = ( pPlayer->GetPosition() - this->GetPosition() ).Length();
	
	float fCheckDis = fCHECK_DISTANCE - fLength;
	
	Score = m_PhotoPoint + fCheckDis + CheckPosScore();
	
	return Score;
}

//=============================================================================
//写真の位置での得点計算
//=============================================================================
//[return]
//	スコア
//=============================================================================
int CEnemy::CheckPosScore()
{
	int Score = 0;
	
	Math::Vector2D vHitPos2D( vHitPos.x, vHitPos.y );
	
	const float fMARGIN = 20.0f;
	
	//映す範囲を制限する
	if( ( vHitPos2D.x > fMARGIN && vHitPos2D.x < SCREEN_WIDTH - fMARGIN ) && 
		( vHitPos2D.y > fMARGIN && vHitPos2D.y < SCREEN_HEIGHT - fMARGIN ) )
	{
		
		/*真ん中エリアの範囲*/
		const Math::Point2DF fMIDDLE_AREA( 200, 150 );		
		
		//真ん中エリアの範囲の設定
		Math::Rect2DF HitRect( SCREEN_WIDTH / 2 - fMIDDLE_AREA.x, SCREEN_HEIGHT / 2 - fMIDDLE_AREA.y, 
							   fMIDDLE_AREA.x * 2, fMIDDLE_AREA.y * 2 );
							   
		//真ん中の場合
		if( Collision::Point_Rect( vHitPos2D, HitRect ) )
		{
			Score = 100;
		}

		//その他の場合
		else
		{
			Score = 20;
		}
		
	}
	
	return Score;
	
}


//=============================================================================
//敵の得点計算
//=============================================================================
//[input]
//	pSceneMgr:判定するシーン管理クラス
//[return]
//	写真撮影可能かどうか
//=============================================================================
bool CEnemy::CheckShoot( CSceneManager *pSceneMgr )
{
	Math::Rect2DF HitRect( 0, 0, toF( SCREEN_WIDTH ), toF( SCREEN_HEIGHT ) );
	
	vHitPos = pSceneMgr->GetSceneMgr()->TransformToScreen( m_vPos );
	
	Math::Vector2D vHitPos2D( vHitPos.x, vHitPos.y );
	
	if( GetVisibleFlag() && 
		Collision::Point_Rect( vHitPos2D, HitRect ) )
	{
		return true;
	}

	return false;
	
}

////=============================================================================
////敵の得点計算
////=============================================================================
////[input]
////	pPlayer:判定するプレイヤー
////[return]
////	写真撮影可能かどうか
////=============================================================================
//bool CEnemy::CheckShoot( CPlayer *pPlayer )
//{
//	const int CHECK_POINT_MAX = 9;
//	
//	/*写真判定ポイント*/
//	Math::Vector2D CheckPointTbl[] =
//	{
//		Math::Vector2D(400, 300),
//		Math::Vector2D(350, 300),
//		Math::Vector2D(450, 300),
//		Math::Vector2D(400, 250),
//		Math::Vector2D(400, 350),
//		Math::Vector2D(350, 250),
//		Math::Vector2D(350, 350),
//		Math::Vector2D(450, 250),
//		Math::Vector2D(450, 350),
//		
//	};
//	
//	for( int i = 0;i < CHECK_POINT_MAX;++i )
//	{
//		if( GetVisibleFlag() && 
//			GetModelActor( SCREEN_MAIN )->Collision_Check( pPlayer->GetShootChkBox() ) )
//		{
//			return true;
//		}
//		
//	}
//	
//	return false;
//	
//}



//=============================================================================
//アクターインデックスのセット
//=============================================================================
//[input]
//	index:設定するインデックス
//=============================================================================
void CEnemy::SetActorIndex( int index )
{
	m_ActorIndex = index;
	m_pCatchSpr3D->SetActorIndex( index );
	m_pPntFontSpr3D->SetActorIndex( index );
}


//=============================================================================
//アニメーションの切り替え
//=============================================================================
void CEnemy::ChangeAnimation()
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
		}
	}
}

//=============================================================================
//次の移動ポイントの設定
//=============================================================================
void CEnemy::SetNextPoint( )
{
	const float fMOVEAREA = 20.0f;//移動範囲
	
	m_vNextPoint.x = m_Rand.GetFloat( m_vInitPos.x - fMOVEAREA, m_vInitPos.x + fMOVEAREA );
	m_vNextPoint.z = m_Rand.GetFloat( m_vInitPos.z - fMOVEAREA, m_vInitPos.z + fMOVEAREA );
	
	if( m_IsFly )
	{
		m_vNextPoint.y = m_Rand.GetFloat( m_vInitPos.y - fMOVEAREA / 2, m_vInitPos.y + fMOVEAREA / 2 );
	}
		
}

//=============================================================================
//壁との判定
//=============================================================================
//[input]
//	pField:フィールド
//[return]
//	壁に当たっているかどうか
//=============================================================================
bool CEnemy::HitCheckWall( CField *pField )
{
	m_HitRay.vStart = m_vPos + Math::Vector3D( 0.0f, 3.0f, 0.0f );
	m_HitRay.vEnd = m_HitRay.vStart + m_vFront * 0.2f;
	
	Renderer::SCollisionResultExtend RetEx;
	
	//通れる箇所の設定
	if( MoveCheck( pField ) == -1 )
	{
		return false;
	}
	
	else
	{
		return true;
	}
	
}



//=============================================================================
//乱数の種の設定
//=============================================================================
//[input]
//	pCore:コアデバイス
//=============================================================================
void CEnemy::SetSeed( ICore *pCore )
{
	m_Rand.Seed( pCore->GetSyncCount() );
}

