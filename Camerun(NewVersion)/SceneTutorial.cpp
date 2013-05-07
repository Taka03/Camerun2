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
//	float fMoveDistance = 0.0f;//���̋���
//	Sint32 MoveAngle = 0;//���̌����Ă���ʒu	
//	Math::Vector3D vMousePos( 0, 0, 0 );//�}�E�X�̈ʒu
//	Math::Vector3D vOldMousePos( 0, 0, 0 );
//	Math::Vector3D vMovePos( 0, 0, 0 );//�ړ��ʒu
//	Peripheral::IMouse *pMouse;//�}�E�X�f�o�C�X
//	Math::Vector3D vTargetPos( 0, 0, 0 );
//}
//
//
//
////=============================================================================
////�R���X�g���N�^
////=============================================================================
////[input]
////	strFileName:�t�@�C����
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
////�f�X�g���N�^
////=============================================================================
//CSceneGameTutorial::~CSceneGameTutorial(void)
//{
//}
//
////=============================================================================
////������
////=============================================================================
//void CSceneGameTutorial::Init( Uint32 dt )
//{
//	printf("[GameTutorial]::Init\n");
//	
//	const int CLEAR_OBJECT = 4;//��\���ɂ���I�u�W�F�N�g��
//	
//	/*�]�v�ȃI�u�W�F�N�g���\���ɂ���*/
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
//	/*�ړ��@�\�����ǉ����Ă���*/
//	m_IsAddFunc[FUNC_MOVE] = true;
//	
//	/*���̑��̋@�\�́A�ŏ��͋@�\�����Ȃ�*/
//	for( int i = 1;i < FUNC_MAX;++i )
//	{
//		m_IsAddFunc[i] = false;
//	} 
//	
//	/*2��ڈȍ~�̓��j���[�@�\��\��*/
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
////�ҋ@��
////=============================================================================
//void CSceneGameTutorial::Idle( Uint32 dt )
//{
//	CSceneGameMain::Idle( dt );
//	
//}
//
////=============================================================================
////�X�V
////=============================================================================
//eSceneState CSceneGameTutorial::UpDate()
//{
//	( this->*m_pStateFunc )( 1 );
//	return m_eSceneState;
//}
//
//
////=============================================================================
////�����_�����O
////=============================================================================
//void CSceneGameTutorial::Rendering()
//{
//
//}
