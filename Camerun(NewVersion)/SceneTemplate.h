//*============================================================================
//SceneTemplate.h
//*============================================================================
//[history]
//	08/11/11  �쐬
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
//	�Q�[���V�[���e���v���[�g�N���X
//=============================================================================
class CSceneTemplate :	public CSceneBase
{
	protected:
	
		/*�X�e�[�g���\�b�h�|�C���^*/
		void ( CSceneTemplate::*m_pStateFunc )( Uint32 );
		
		//�V�[���̏��
		eSceneState m_eSceneState;
		
	public:
	
		CSceneTemplate();//�R���X�g���N�^
		CSceneTemplate( string strFileName );//�R���X�g���N�^
		virtual ~CSceneTemplate(void);//�f�X�g���N�^
		
	public:
	
		/*�I�u�W�F�N�g�f�[�^�̏�����*/
		virtual void InitObjectData( Uint32 dt ) = 0;
		
		/*������*/
		virtual void Init( Uint32 dt ) = 0;
		
		/*�ҋ@��*/
		virtual void Idle( Uint32 dt ) = 0;
		
		/*��~��*/
		//virtual void Resume( Uint32 dt );
		
		/*�����_�����O*/
		virtual void Rendering() = 0;
		
		/*�I��*/
		virtual void End( Uint32 dt );
		
		/*�X�V*/
		virtual eSceneState UpDate();
		
		/*����*/
		void Exec();
			

	public:
		
		/*��Ԃ̃Z�b�g*/
		void SetState( void ( CSceneTemplate::*pState_Func )( Uint32 ) )
		{
			m_pStateFunc = pState_Func;
		}
		
		/*�V�[���̏�Ԃ̐ݒ�*/
		void SetSceneState( eSceneState eState )
		{
			m_eSceneState = eState;
		}
	
		// �t�F�[�h����
		void FadeExec(void);
	};
