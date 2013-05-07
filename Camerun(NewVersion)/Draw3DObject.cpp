//*===========================================================================
//Draw3DObject.cpp
//*===========================================================================

//============================================================================
//include
//============================================================================
#include "Draw3DObject.h"
#include <list>

//============================================================================
//コンストラクタ
//============================================================================
//[input]
//	pName:データ名
//	vPos:位置
//===========================================================================
CDraw3DObject::CDraw3DObject( const char *pName, Math::Vector3D vPos ) 
: CDrawObject( pName ),
  m_vPos( vPos ),
  m_vInitPos( vPos ),
  m_Rot( 0, 0, 0 ),
  m_InitRot( m_Rot ),
  m_vScale( 1.0f, 1.0f, 1.0f ),
  m_vInitScale( m_vScale ),
  m_ActorIndex( SCREEN_MAIN )
{
	
}

//=============================================================================
//デストラクタ
//=============================================================================
CDraw3DObject::~CDraw3DObject(void)
{
}

//=============================================================================
//初期化
//=============================================================================
void CDraw3DObject::Init()
{
	m_vPos = m_vInitPos;
	m_Rot = m_InitRot;
	m_vScale = m_vInitScale;
}


//=============================================================================
//処理
//=============================================================================
void CDraw3DObject::Exec()
{
}

//=============================================================================
//移動処理
//=============================================================================
void CDraw3DObject::MoveExec()
{
}



//=============================================================================
//レンダリング
//=============================================================================
void CDraw3DObject::Rendering( )
{
	
}

//=============================================================================
//ファイル読み込み
//=============================================================================
//[input]
//	pRender:レンダリング用デバイス
//	pFileMgr:ファイル管理デバイス
//=============================================================================
void CDraw3DObject::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	
}

//=============================================================================
//アクターの生成
//=============================================================================
//[input]
//	pSceneMgr:シーン管理用デバイス
//=============================================================================
void CDraw3DObject::CreateActor( int index, Scene::ISceneManager *pSceneMgr )
{
}


//=============================================================================
//当たり判定のチェック
//=============================================================================
//[input/output]
//	ppChara:判定するキャラ
//[return]
//	当たったかどうか
//=============================================================================
bool CDraw3DObject::HitCheck( CDraw3DObject **ppChara )
{
	//list<ListData>::iterator i;
	//
	//for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	//{
	//	CDraw3DObject *obj = dynamic_cast<CDraw3DObject *>( i->gameobj );
	//	
	//	if( obj->GetObjectType() == OBJ_ENEMY && this->HitCheck( &obj ) )
	//	{
	//		*ppChara = obj;
	//		return true;
	//	}
	//		
	//}
	
	return false;
}

//=============================================================================
//当たり判定のチェック
//=============================================================================
//[input]
//	vRay:判定用のレイ
//[return]
//	当たったかどうか
//=============================================================================
bool CDraw3DObject::HitCheck( Collision::CLine3D &vRay )
{
	//list<ListData>::iterator i;
	//
	//for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	//{
	//	CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
	//	
	//	if( pChara->HitCheck( vRay ) )
	//	{
	//		return true;
	//	}
	//}
	
	return false;
}

//=============================================================================
//当たり判定のチェック
//=============================================================================
//[input]
//	vRay:判定用のレイ
//	ppHitObj:当たったオブジェクトの取得
//[output]
//	obj:衝突したオブジェクト	
//[return]
//	当たったかどうか
//=============================================================================
bool CDraw3DObject::HitCheck( Selene::Collision::CLine3D &vRay, CDraw3DObject **ppHitObj )
{
	//list<ListData>::iterator i;
	//
	//for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	//{
	//	CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
	//	
	//	if( pChara->HitCheck( vRay ) )
	//	{
	//		*ppHitObj = pChara;
	//		return true;
	//	}
	//}
	
	return false;
}


//=============================================================================
//当たり判定のチェック
//=============================================================================
//[input]
//	vRay:判定用のレイ
//	Out:衝突判定の結果
//[return]
//	当たったかどうか
//=============================================================================
bool CDraw3DObject::HitCheck( Collision::CLine3D &vRay, Renderer::SCollisionResult &Out )
{
	//list<ListData>::iterator i;
	//
	//for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	//{
	//	CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
	//	
	//	if( pChara->HitCheck( vRay, Out ) )
	//	{
	//		return true;
	//	}
	//}
	
	return false;
}

//=============================================================================
//当たり判定のチェック
//=============================================================================
//[input]
//	vRay:判定用のレイ
//	Out:衝突判定の結果
//[output]
//	ppHitObj:当たったオブジェクト
//[return]
//	当たったかどうか
//=============================================================================
bool CDraw3DObject::HitCheck( Collision::CLine3D &vRay, Renderer::SCollisionResult &Out, CDraw3DObject **ppHitObj )
{
	//list<ListData>::iterator i;
	//
	//for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	//{
	//	CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
	//	
	//	if( pChara->HitCheck( vRay, Out ) )
	//	{
	//		*ppHitObj = pChara;
	//		
	//		return true;
	//	}
	//}
	
	return false;
}

//=============================================================================
//アクターインデックスのセット
//=============================================================================
//[input]
//	index:設定するインデックス
//=============================================================================
void CDraw3DObject::SetActorIndex( int index )
{
	m_ActorIndex = index;
	//list<ListData>::iterator i;
	//
	//for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	//{
	//	CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
	//	
	//	pChara->SetActorIndex( index );		
	//}
}
