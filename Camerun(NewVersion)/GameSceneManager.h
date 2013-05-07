//*============================================================================
//GameSceneManager.h
//*============================================================================
//[history]
//	08/03/05�@�쐬
//	08/10/08  �C���J�n	
//[author]
//	Taka
//[ref]
// ���~����[�ǂ��ƃR���@http://marupeke296.com/
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "gameobject.h"
#include "SceneBase.h"
#include "SceneGameTitle.h"
#include "SceneGameMain.h"
#include "ScenePhoto.h"
#include "SceneResult.h"
#include "ScenePause.h"
#include "SceneTutorial.h"
#include "SceneShowMission.h"
#include "SceneNewComponent.h"

//=============================================================================
//define
//=============================================================================


//=============================================================================
//using
//=============================================================================
using namespace std;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�Q�[���V�[���Ǘ��p�N���X
//=============================================================================
class CGameSceneManager :public CSceneBase
{
	public:
	
	private:
	
		CSceneGameTitle *m_pGameTitle;//�Q�[���^�C�g��
		CSceneGameMain *m_pGameMain;//�Q�[�����C��
		CScenePhoto *m_pPhotoCheck;//�ʐ^�m�F���
		CSceneResult *m_pResult;//���ʉ��
		CScenePause *m_pPause;//�|�[�Y���
		CSceneShowMission *m_pShowMission;//�~�b�V�����\��
		CSceneNewComponent *m_pNewComp;//�V�v�f�\��
	
	private:
	
		eSceneState m_eSceneState;//�V�[���̏��
		
	public:
	
		CColor			  m_Color;//�F
		Sint32			  m_Time;//�^�C���J�E���^�[
		Sint32			  m_TimeLast;//�ő�^�C��
		
		
	private:
	
		void Title();//�^�C�g��
		void ShowMission();//�~�b�V�����X�^�[�g���
		void GameMain();//�Q�[�����C��
		void PhotoCheck();//�ʐ^�m�F���
		void Result();//���ʉ��
		void NewComp();//�V�v�f�\�����
		void Pause(void);// �X�^�[�g���j���[
		void Exit();//�I��
		
		void DrawNowLoading();//�ǂݍ��݉�ʂ̕`��

	private:
	
		void LoadStatus( );//�X�e�[�^�X�̃��[�h
		void SaveStatus( );//�X�e�[�^�X�̃Z�[�u
		
	private:
	
		/*�X�N���v�g���\�b�h*/
		typedef void (CSceneGameMain::*ScriptFunc)();

		string ScriptExec( string strSource );//�X�N���v�g����
		void TutorialExec();//�`���[�g���A������
		
	private:
	
		virtual void SetFadeIn( Sint32 Time, CColor Color, void ( CGameSceneManager::*pStateFunc )() );//�t�F�[�h�C���̐ݒ�
		virtual void SetFadeOut( Sint32 Time, CColor Color, void ( CGameSceneManager::*pStateFunc )() );//�t�F�[�h�A�E�g�̐ݒ�
		virtual Bool IsFade( void );//�t�F�[�h�����ǂ���
		void FadeIn();//�t�F�[�h�C��
		void FadeOut();//�t�F�[�h�A�E�g
		
		void FadeExec();//�t�F�[�h����
	
		
	public:
	
		CGameSceneManager( CSceneBase *pScene );//�R���X�g���N�^
		
		CGameSceneManager( );//�R���X�g���N�^

		~CGameSceneManager();//�f�X�g���N�^
		
		void Rendering();//�����_�����O
		
		eSceneState UpDate();//�X�V
		
		/*�V�[���̐ݒ�*/
		void SetStateFunc( void ( CGameSceneManager::*pStateFunc )() )
		{
			m_pStateFunc = pStateFunc;
		}
		
		/*�`��̐ݒ�*/
		void SetRenderFunc( void ( CGameSceneManager::*pRenderFunc )() )
		{
			m_pRenderFunc = pRenderFunc;
		}
		
	public:
	
		//�X�e�[�g���\�b�h�|�C���^		
		void ( CGameSceneManager::*m_pStateFunc )();	
		
		//�`�惁�\�b�h�|�C���^
		void ( CGameSceneManager::*m_pRenderFunc )();
		
		// �`���[�g���A�����
		void Tutorial(void);
		
};