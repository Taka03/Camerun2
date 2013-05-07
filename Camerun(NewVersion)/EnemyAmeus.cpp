//*=============================================================================
//EnemyAmeus.cpp
//*=============================================================================

//==============================================================================
//include
//==============================================================================
#include "EnemyAmeus.h"
#include <fstream>
#include <vector>

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	pName:データ名
//	vPos:設定する座標
//	pResFile:敵の動きのファイル
//=============================================================================
CEnemyAmeus::CEnemyAmeus( const char *pName, Math::Vector3D vPos, File::IResourceFile *pResFile )
:CEnemy( pName, vPos, pResFile )  
{
	
	m_fSpeed = 0.05f;
	
	m_TypeName = "3/4r";//アメウス
	
	m_StTypeName = "アメウス";
	
	
	
}


//=============================================================================
//初期化
//=============================================================================
void CEnemyAmeus::Init()
{
	CEnemy::Init();
	
	//ルートの移動キーの設定
	SetRootKey();
	
	
}

//=============================================================================
//処理
//=============================================================================
void CEnemyAmeus::Exec()
{
	m_vCatchPos = m_vPos + Math::Vector3D( 0, -0.5f, 0 ) + m_vFront * 0.8f;
	
	CEnemy::Exec();
}

//=============================================================================
//壁との判定
//=============================================================================
//[input]
//	pField:フィールド
//[return]
//	壁に当たっているかどうか
//=============================================================================
bool CEnemyAmeus::HitCheckWall( CField *pField )
{
	m_HitRay.vStart = m_vPos + Math::Vector3D( 0.0f, 3.0f, 0.0f );
	m_HitRay.vEnd = m_HitRay.vStart + m_vFront * 0.2f;
	
	Renderer::SCollisionResultExtend RetEx;
	
	Bool HitCheck = MoveCheck( pField );
	
	//通れない箇所の設定
	if( HitCheck == MASK_LAKE || HitCheck == MASK_OUT )
	{
		return true;
	}
	
	else
	{
		return false;
	}
	
}


//=============================================================================
//移動
//=============================================================================
void CEnemyAmeus::MoveExec()
{
	static int count = 0;
	
	const int TIME_MAX = 240;
	
	++count;
	
	//m_vPos.x = ::Interpolation::Flat( m_vInitPos.x, m_vNextPoint.x, TIME_MAX, count );
	
	
	if( count > 0 && count <= TIME_MAX / 2 )
	{
		SetVisibleFlag( true );
	}
	
	else if( count > TIME_MAX / 2 && count <= TIME_MAX )
	{
		SetVisibleFlag( false );
	}
	
	else if( count > TIME_MAX )
	{
		count = 0;
	}
	
	
	/*ランダムウォーク*/
	//MoveRandom();	
	
	
	MoveRoot();
	
	if( m_vPos.y < 0.0f )
	{
		m_vPos.y = 0.0f;
	}
	
	
	//Sint32 Alpha = Interpolation::Flat( 255L, 0L, TIME_MAX, count );
	//
	//SetAlphaColor( Alpha );
	//
	//if( count > TIME_MAX )
	//{
	//	count = 0;
	//}
	
}

