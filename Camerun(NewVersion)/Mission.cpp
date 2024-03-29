//*============================================================================
//Mission.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Mission.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CMission::CMission(void)
{

}

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	pTarget:ターゲットとなるオブジェクト
//=============================================================================
CMission::CMission( CDraw3DObject *pTarget, MissionData datMission ) :m_pTarget( pTarget ), m_datMission( datMission )
{
	m_IsGameClear = false;
	
	m_HiScore = 0;	
	
	m_IsFirstPlay = true;
	
	//m_ExistScore = 0;
	//m_PosScore = 0;
	//m_DistScore = 0;
	
	m_PhotoIndex = 0;
}




//=============================================================================
//デストラクタ
//=============================================================================
CMission::~CMission(void)
{
	//SAFE_DELETE( m_pTarget );
}

//=============================================================================
//レンダリング
//=============================================================================
void CMission::Rendering()
{
	m_datMission.m_pPhotoSpr->Rendering();
	
	m_datMission.m_pFontSpr->Rendering();
	
}

//=============================================================================
//処理
//=============================================================================
void CMission::Exec()
{
	m_datMission.m_pFontSpr->Exec();
	
	m_datMission.m_pPhotoSpr->Exec();
}

