//*============================================================================
//ScenePause.h
//*============================================================================
//[history]
//	08/11/27  �쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "SceneTemplate.h"

//=============================================================================
//const
//=============================================================================
const int SKILL_MAX = 5;//�X�L���̍ő吔

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�|�[�Y���
//=============================================================================
class CScenePause :	public CSceneTemplate
{

	public:
	
		/*���j���[����*/
		enum eSelectScene
		{
			SCENE_RETURNGAME,//�Q�[���ɖ߂�
			SCENE_RETRY,//���g���C
			SCENE_RETURNTITLE,//�^�C�g���ɖ߂�
		};
		
		enum ePauseScene
		{
			SCENE_CHECK,
			SCENE_NONE,
		};
		
	
	private:
	
		// ���j���[�t�H���g�p�X�v���C�g
		//CFontSprite *m_pMenuFontSpr;
		
		/*�|�[�Y���j���[*/
		CMenu *m_pPauseMenu;
		
		/*�m�F���j���[*/
		CMenu *m_pCheckMenu;
		
		// �Z���N�g�V�[��
		eSelectScene m_eSelectScene;
		
		/*���j���[�̕\���̗L��*/
		bool m_IsShowMenu;
		
		CSprite *m_pNextBtnSpr;//�ʐ^�����ɑ���{�^��
		
		CSprite *m_pSkillSpr[SKILL_MAX];//�X�L���\���X�v���C�g
		
		CSprite *m_pClearSpr;//�N���A�|�C���g�X�v���C�g
		
		CFontSprite *m_pFontSpr;//�t�H���g�X�v���C�g
		
		CFontSprite *m_pClrPntFontSpr;//�t�H���g�X�v���C�g
		
		CSprite *m_pSkillExpSpr;//�X�L������
		CSprite *m_pTargetSpr;//�^�[�Q�b�g�X�v���C�g
		
		Uint32 m_PhotoIdx;//�ʐ^�̃C���f�b�N�X
		
		

	public:
	
		CScenePause( string strFileName );//�R���X�g���N�^
		virtual ~CScenePause(void);//�f�X�g���N�^
		
	public:
	
		/*�I�u�W�F�N�g�f�[�^�̏�����*/
		void InitObjectData( Uint32 dt );
		
		/*������*/
		void Init( Uint32 dt );
		
		/*�ҋ@��*/
		void Idle( Uint32 dt );
		
		/*�����_�����O*/
		void Rendering();
		
		// �|�[�Y���j���[�̐ݒ�
		void SetPauseMenu(void);
		
		/*�m�F��ʂ̏���*/
		void CheckMenuExec();
		
		/*�ʐ^�̕`��*/
		void DrawPhoto();
		
		/*�l�N�X�g�{�^���̏���*/
		void NextBtnExec();
		
		// �V�[���̈ړ�
		void MoveScene(eSelectScene eScene);
		
		/*�|�[�Y���j���[�\���X�N���v�g*/
		void PauseMenuScript();
		
		//�^�[�Q�b�g�̕\��
		void DrawTarget();
		
		//�X�L�������̕\��
		void DrawSkillExp( int no );
		
		//�X�L���̕`��
		void DrawSkill();
		
	public:
	
		/*�Z���N�g�V�[���̐ݒ�*/
		void SetSelectScene( eSelectScene eScene )
		{
			m_eSelectScene = eScene;
		} 
		
	public:
	
		/*�Z���N�g�V�[���̎擾*/
		eSelectScene GetSelectScene() const
		{
			return m_eSelectScene;
		}
		
};
