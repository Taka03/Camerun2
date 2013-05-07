//*============================================================================
//SceneChat.h
//*============================================================================
//[history]
//	08/05/23�@�쐬
//	08/11/01  �C��
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "SceneBase.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	��b��ʃN���X
//=============================================================================
class CSceneChat : public CSceneBase
{
	private:
	
		/*�X�e�[�g���\�b�h�|�C���^*/
		void ( CSceneChat::*m_pStateFunc )( Uint32 );
		
		//�V�[���̏��
		eSceneState m_eSceneState;
		
	private:
	
		CSprite *m_pBG;//�w�i
		CFontSprite *m_pChatFont;//��b�t�H���g
		CBGM *m_pMusic;//BGM
	
	public:
	
		CSceneChat();//�R���X�g���N�^
		CSceneChat( CResourceManager *pResMgr, CMissionManager *pMissionMgr );//�R���X�g���N�^
		~CSceneChat(void);//�f�X�g���N�^
		
		/*������*/
		void Init( Uint32 dt );
		
		/*�ҋ@��*/
		void Idle( Uint32 dt );
		
		/*�I��*/
		void End( Uint32 dt );
		
		/*�����_�����O*/
		void Rendering();
		
		/*�X�V*/
		virtual eSceneState UpDate();
		
	public:
	
		/*��Ԃ̃Z�b�g*/
		void SetState( void ( CSceneChat::*pState_Func )( Uint32 ) )
		{
			m_pStateFunc = pState_Func;
		}

};
