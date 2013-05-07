//*============================================================================
//gameobject.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "gameobject.h"
#include "selene.h"

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	pName:データ名
//===========================================================================
CGameObject::CGameObject( const char *pName ) 
: m_strFileName( pName )
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CGameObject::~CGameObject()
{
	
}


