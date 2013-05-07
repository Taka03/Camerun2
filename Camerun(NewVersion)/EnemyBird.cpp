//*=============================================================================
//EnemyBird.cpp
//*=============================================================================

//==============================================================================
//include
//==============================================================================
#include "EnemyBird.h"
#include <fstream>

//==============================================================================
//enum
//==============================================================================
//鳥アニメーションタイプ
enum eBirdAnimType
{
	ANIM_STAND,
	ANIM_WALK,
	ANIM_FLY_START,
	ANIM_FLY,
	ANIM_FLY_END,
	ANIM_STUN,
};


//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	pName:データ名
//	vPos:設定する座標
//	pResFile:敵の動きのファイル
//=============================================================================
CEnemyBird::CEnemyBird( const char *pName, Math::Vector3D vPos, File::IResourceFile *pResFile ) 
: CEnemy( pName, vPos, pResFile ) 
{
	m_TypeName = "sl";//トリ
	
	m_StTypeName = "トリ";
	
	m_IsFly = true;
	
}


//=============================================================================
//初期化
//=============================================================================
void CEnemyBird::Init()
{
	CEnemy::Init();
	
	m_AnimID[ANIM_NOW] = ANIM_FLY;
	
	SetRootKey();
	
}

//=============================================================================
//処理
//=============================================================================
void CEnemyBird::Exec()
{
	m_vCatchPos = m_vPos + Math::Vector3D( 0, 0.1f, 0 ) + m_vFront * 0.8f;

	CEnemy::Exec();	
	
}

//==============================================================================
//移動処理
//==============================================================================
//[input]
//	vTargetPos:対象位置
//	pCam:カメラデバイス
//	pField:チェックするマップ
//	IsShowMark:移動マーカーが表示されているか
//==============================================================================
bool CEnemyBird::Move( Selene::Math::Vector3D vTargetPos, CCamera *pCam, CField *pField, bool IsShowMark )
{
	m_GravityCnt++;
	
	const int TIME_MAX = 60 * 5;
	
	const float fGRAVITY_MIN = 0.1f;
	const float fGRAVITY_MAX = 0.3f;
	
	if( m_GravityCnt > TIME_MAX )
	{
		m_GravityCnt = TIME_MAX;
	}
	
	
	if( IsShowMark )
	{
		m_vDirection.x = vTargetPos.x * pCam->GetRight().x + vTargetPos.y * (-pCam->GetFront().x);
		m_vDirection.z = vTargetPos.x * pCam->GetRight().z + vTargetPos.y * (-pCam->GetFront().z);
		
		m_vPos.y += ::Interpolation::Add( fGRAVITY_MIN, fGRAVITY_MAX, TIME_MAX, m_GravityCnt );
	}
	
	else
	{
		m_vPos.y -= ::Interpolation::Add( fGRAVITY_MIN, fGRAVITY_MAX, TIME_MAX, m_GravityCnt );
	}
	
	if( m_vPos.y < 0.0f )
	{
		m_vPos.y = 0.0f;		
	}
	
	if( m_vPos.y > 210.0f )
	{
		m_vPos.y = 210.0f;
	}
	
	
	
	m_Rot.x = toF( Math::ATan2( -m_vDirection.z, -m_vDirection.x ) );
	
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
//移動処理
//=============================================================================
void CEnemyBird::MoveExec()
{
	MoveRoot();
}


//=============================================================================
//壁との判定
//=============================================================================
//[input]
//	pField:フィールド
//[return]
//	壁に当たっているかどうか
//=============================================================================
bool CEnemyBird::HitCheckWall( CField *pField )
{
	m_HitRay.vStart = m_vPos + Math::Vector3D( 0.0f, 3.0f, 0.0f );
	m_HitRay.vEnd = m_HitRay.vStart + m_vFront * 0.2f;
	
	Renderer::SCollisionResultExtend RetEx;
	
	Bool HitCheck = MoveCheck( pField );
	
	//通れる箇所の設定
	if( HitCheck == MASK_LAKE || HitCheck == -1 )
	{
		return false;
	}
	
	else
	{
		return true;
	}
	
}


//=============================================================================
//鳥の鳴き声の再生
//=============================================================================
//[input]
//	pSound:サウンドデバイス
//	fDistance:距離
//=============================================================================
void CEnemyBird::PlaySnd(Selene::Sound::ISound *pSound, float fDistance )
{
	static float Pan = -100.0f;
	
	Pan += 1.0f;
	
	if( Pan >= 100 )
	{
		Pan = 100;
	}
	
	pSound->SetVolume( 0, 100 - (fDistance * 0.5f) );
	
	pSound->Play( 0, true );
	
	
}
