#include "Draw2DObject.h"

//============================================================================
//コンストラクタ
//============================================================================
//[input]
//	pName:ファイル名
//	vPos:表示位置
//===========================================================================
CDraw2DObject::CDraw2DObject( const char *pName, Math::Vector2D vPos ) 
:CDrawObject( pName ),
 m_vPos( vPos ),
 m_vInitPos( m_vPos ),
 m_Rot( 0, 0 ),
 m_InitRot( m_Rot ),
 m_vScale( 1.0f, 1.0f ),
 m_vInitScale( m_vScale )
 
{
	
}

//============================================================================
//デストラクタ
//============================================================================
CDraw2DObject::~CDraw2DObject( ) 
{
	
}


//============================================================================
//初期化
//============================================================================
void CDraw2DObject::Init()
{
	m_vPos = m_vInitPos;
	m_Rot = m_InitRot;
	m_vScale = m_vInitScale;
}

