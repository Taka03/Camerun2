//*============================================================================
//SceneMissionSelect.h
//*============================================================================
//[history]
//	08/05/01�@�쐬
//	08/10/21  �C��
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
//	�~�b�V�����Z���N�g��ʃN���X
//=============================================================================
class CSceneMissionSelect : public CSceneBase
{
	private:
	
		/*�X�e�[�g���\�b�h�|�C���^*/
		void ( CSceneMissionSelect::*m_pStateFunc )( Uint32 );
		
		//�V�[���̏��
		eSceneState m_eSceneState;
		
	private:
	
		CSprite *m_pMissionSelSpr;//�~�b�V�����Z���N�g���
		CSprite *m_pPinSpr;//�s��
		CFontSprite *m_pNumFont;//�����t�H���g
		CFontSprite *m_pMiContFont;//�~�b�V�������e�\���t�H���g
		
		CBGM *m_pTitleMusic;//�Q�[��BGM
	
	
	public:
	
		CSceneMissionSelect();//�R���X�g���N�^
		~CSceneMissionSelect(void);//�f�X�g���N�^
		
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
		
		/*�~�b�V�����̒ǉ�*/
		void AppendMission();
		
		/*�~�b�V�����̑I��*/
		void SelectMission( Peripheral::IMouse *pMouse );
		
		/*�~�b�V�����̌���*/
		void DecideMission( Peripheral::IMouse *pMouse );
		
		
	public:
	
		/*��Ԃ̃Z�b�g*/
		void SetState( void ( CSceneMissionSelect::*pState_Func )( Uint32 ) )
		{
			m_pStateFunc = pState_Func;
		}

	
		
		
			
};
