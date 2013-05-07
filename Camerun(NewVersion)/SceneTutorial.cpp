////*============================================================================
////SceneTutorial.cpp
////*============================================================================
//
////=============================================================================
////include
////=============================================================================
//#include "SceneTutorial.h"
//#include <math.h>
//#include <iostream>
//#include <fstream>
//
////=============================================================================
////namespace
////=============================================================================
//namespace 
//{
//	int time = 0;
//	float fMoveDistance = 0.0f;//矢印の距離
//	Sint32 MoveAngle = 0;//矢印の向いている位置	
//	Math::Vector3D vMousePos( 0, 0, 0 );//マウスの位置
//	Math::Vector3D vOldMousePos( 0, 0, 0 );
//	Math::Vector3D vMovePos( 0, 0, 0 );//移動位置
//	Peripheral::IMouse *pMouse;//マウスデバイス
//	Math::Vector3D vTargetPos( 0, 0, 0 );
//}
//
//
//
////=============================================================================
////コンストラクタ
////=============================================================================
////[input]
////	strFileName:ファイル名
////===========================================================================
//CSceneGameTutorial::CSceneGameTutorial( string strFileName )
//: CSceneTemplate( strFileName )
//{
//	SetState( &CSceneTemplate::Init );
//}
//
//
//
////=============================================================================
////デストラクタ
////=============================================================================
//CSceneGameTutorial::~CSceneGameTutorial(void)
//{
//}
//
////=============================================================================
////初期化
////=============================================================================
//void CSceneGameTutorial::Init( Uint32 dt )
//{
//	printf("[GameTutorial]::Init\n");
//	
//	const int CLEAR_OBJECT = 4;//非表示にするオブジェクト数
//	
//	/*余計なオブジェクトを非表示にする*/
//	CDraw3DObject *pClearObj[] =
//	{
//		m_pField,
//		m_pTrain,
//		m_pFountObj,
//		m_pIsLand,
//		
//	};
//	
//	for( int i = 0;i < CLEAR_OBJECT;++i )
//	{
//		pClearObj[i]->SetVisibleFlag( false );
//	}
//		
//	for( vector<CEnemy *>::iterator i = m_pVecCatchEnemy.begin();i != m_pVecCatchEnemy.end();++i )
//	{
//		CEnemy *pEnemy = *i;
//		
//		pEnemy->SetVisibleFlag( false );
//	}
//	
//	
//	/*移動機能だけ追加しておく*/
//	m_IsAddFunc[FUNC_MOVE] = true;
//	
//	/*その他の機能は、最初は機能させない*/
//	for( int i = 1;i < FUNC_MAX;++i )
//	{
//		m_IsAddFunc[i] = false;
//	} 
//	
//	/*2回目以降はメニュー機能を表示*/
//	if( !GetFirstGameFlag() )
//	{
//		m_IsAddFunc[FUNC_MENU] = true;
//	}
//	
//	m_pArrowExpSpr->SetVisibleFlag( false );
//	
//	m_pTrlField->SetVisibleFlag( true );
//	
//	m_pField = m_pTrlField;
//}
//
////=============================================================================
////待機中
////=============================================================================
//void CSceneGameTutorial::Idle( Uint32 dt )
//{
//	CSceneGameMain::Idle( dt );
//	
//}
//
////=============================================================================
////更新
////=============================================================================
//eSceneState CSceneGameTutorial::UpDate()
//{
//	( this->*m_pStateFunc )( 1 );
//	return m_eSceneState;
//}
//
//
////=============================================================================
////レンダリング
////=============================================================================
//void CSceneGameTutorial::Rendering()
//{
//
//}
